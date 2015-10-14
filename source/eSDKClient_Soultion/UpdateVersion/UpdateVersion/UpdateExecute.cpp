#ifdef _WINDOWS
#include <Windows.h>
#endif

#include <io.h>
#include <direct.h>
#include <Shlwapi.h>
#include "Common.h"
#include "UpdateExecute.h"
#include "UpdateServerConfig.h"
#include "eSDKLog.h"
#include "eSDKTool.h"


#include "unzip.h"

#define WRITEBUFFERSIZE (8192)

#ifdef _WIN32
//#define USEWIN32IOAPI
//#include "iowin32.h"
#endif


#pragma comment(lib, "Shlwapi.lib")
#ifdef _DEBUG
#pragma comment(lib, "zlibwapi.lib")
#else
#pragma comment(lib, "zlibwapi.lib")
#endif

#pragma comment(lib, "eSDKTool.lib")
int g_iLogInstanceIndex = 0;

UpdateExecute* UpdateExecute::m_pUpdateExecute = NULL;

//////////////////////////////////////////////////////////////////////////
UpdateVersion::UpdateVersion()
{

}

UpdateVersion::~UpdateVersion()
{

}

UpdateVersion* UpdateVersion::GetUpdateVersion()
{
	return dynamic_cast<UpdateVersion*>(UpdateExecute::Instance());
}

void UpdateVersion::ReleaseUpdateVersion()
{
	UpdateExecute::Destroy();
}

//////////////////////////////////////////////////////////////////////////
UpdateExecute::UpdateExecute()
	: m_fpMsgCB(NULL)
	, m_strReadMeTxt("")
	, m_hThreadHandle(NULL)
{

}

UpdateExecute::~UpdateExecute()
{
	try{
		if (NULL != m_hThreadHandle)
		{
			DWORD dwThreadExitCode = 0;
			GetExitCodeThread(m_hThreadHandle, &dwThreadExitCode);
			if (STILL_ACTIVE == dwThreadExitCode)
			{
				//释放下载未完成的资源，如文件指针、http连接句柄等
				m_DownloadVersion.CloseResourceWhenThreadTerminate();
				//终止升级线程
				TerminateThread(m_hThreadHandle, 0);						
				//清理下载目录
				(void)ClearAllTempFile();
			}
			CloseHandle(m_hThreadHandle);
			m_hThreadHandle = NULL;
		}
	}
	catch(...)
	{

	}
}

UpdateExecute* UpdateExecute::Instance()
{
	if (NULL == m_pUpdateExecute)
	{
		m_pUpdateExecute = new UpdateExecute;
	}

	return m_pUpdateExecute;
}

void UpdateExecute::Destroy()
{
	if (NULL != m_pUpdateExecute)
	{
		delete m_pUpdateExecute;
		m_pUpdateExecute = NULL;
	}
}

bool UpdateExecute::Init(const std::vector<std::string>& vecNameList, const std::vector<std::string>& vecVersionList)
{
	//初始化日志
	eSDKLog* pLog = eSDKLog::getInstance();
	if (NULL == pLog)
	{
		return false;
	}

	int iRet = pLog->init("UpdateVersion", g_iLogInstanceIndex);
	if (ESDKLOG_SUCCESS != iRet)
	{
		return false;
	}
	DEBUG_LOG() << "--- ENTER";

	//修改本地配置文件
	if (vecNameList.size() != vecVersionList.size())
	{
		ERROR_LOG() << "vecIDList and vecVersionList is not be equal in size.";
		return false;
	}

	//初始化本地数据
	m_fpMsgCB = NULL;
	if (NULL != m_hThreadHandle)
	{
		DWORD dwThreadExitCode = 0UL;
		GetExitCodeThread(m_hThreadHandle, &dwThreadExitCode);
		if (STILL_ACTIVE == dwThreadExitCode)
		{
			//释放下载未完成的资源，如文件指针、http连接句柄等
			m_DownloadVersion.CloseResourceWhenThreadTerminate();
			//终止升级线程
			TerminateThread(m_hThreadHandle, 0);						
			//清理下载目录
			(void)ClearAllTempFile();
		}
		CloseHandle(m_hThreadHandle);
		m_hThreadHandle = NULL;
	}
	m_strReadMeTxt.clear();
	(void)ReadProductInfo();

	size_t size = vecNameList.size();
	for (size_t i=0; i<size; i++)
	{
		if (!WriteFile(vecNameList[i], vecVersionList[i]))
		{
			ERROR_LOG() << "Write file failed.";
			return false;
		}
	}

	DEBUG_LOG() << "--- LEAVE";
	return true;
}

bool UpdateExecute::UnInit(void)
{
	DEBUG_LOG() << "--- ENTER";
	//初始化本地数据
	m_fpMsgCB = NULL;
	m_strReadMeTxt.clear();
	m_mapProductInfo.clear();

	if (NULL != m_hThreadHandle)
	{
		DWORD dwThreadExitCode = 0;
		GetExitCodeThread(m_hThreadHandle, &dwThreadExitCode);
		if (STILL_ACTIVE == dwThreadExitCode)
		{
			//释放下载未完成的资源，如文件指针、http连接句柄等
			m_DownloadVersion.CloseResourceWhenThreadTerminate();
			//终止升级线程
			TerminateThread(m_hThreadHandle, 0);
			//清理下载目录
			if (!ClearAllTempFile())
			{
				ERROR_LOG() << "Clear all temp file failed.";				
			}			
		}
		CloseHandle(m_hThreadHandle);
		m_hThreadHandle = NULL;
	}

	DEBUG_LOG() << "--- LEAVE";
	eSDKLog::destroyInstance();

	return true;
}

bool UpdateExecute::Start(void)
{
	DEBUG_LOG() << "--- ENTER";

	//本地文件升级
	if (!UpdateByLocalFile())
	{
		ERROR_LOG() << "Update by local file failed.";

		//清理文件
		if (!ClearAllTempFile())
		{
			ERROR_LOG() << "Clear all temp file failed.";
		}

		DEBUG_LOG() << "--- LEAVE";
		return false;
	}

	//清理文件
	if (!ClearAllTempFile())
	{
		ERROR_LOG() << "Clear all temp file failed.";
		DEBUG_LOG() << "--- LEAVE";
		return false;
	}

	//创建线程，进入防浪涌时间等待后，进行下载升级。
	m_hThreadHandle = CreateThread(NULL, 0, UpdateThread, NULL, 0, NULL);

	DEBUG_LOG() << "--- LEAVE";
	return true;
}

DWORD WINAPI UpdateExecute::UpdateThread(LPVOID)
{
	DEBUG_LOG() << "--- ENTER";
	if (NULL == m_pUpdateExecute)
	{
		ERROR_LOG() << "m_UpdateExecute is null, return the thread.";
		DEBUG_LOG() << "--- LEAVE";
		return THREAD_EXIT_SUCC;
	}

	//防浪涌时间等待(5分钟到1小时)
	HCRYPTPROV hCryptProv = 0;
	UINT uiRandValue = 0;
	if (!::CryptAcquireContextW(&hCryptProv, 0, 0, PROV_RSA_FULL, CRYPT_VERIFYCONTEXT | CRYPT_SILENT))
	{
		ERROR_LOG() << "CryptAcquireContextW fail.";
		DEBUG_LOG() << "--- LEAVE";
		return THREAD_EXIT_SUCC;
	}

	if (!CryptGenRandom(hCryptProv, sizeof(uiRandValue), (BYTE *)&uiRandValue))
	{
		(void)::CryptReleaseContext(hCryptProv, 0);
		ERROR_LOG() << "CryptGenRandom fail.";
		DEBUG_LOG() << "--- LEAVE";
		return THREAD_EXIT_SUCC;	
	}

	int iMaxTime = 0;
	int iMinTime = 0;
	(void)GetAvertSurgeTime(iMaxTime, iMinTime);
	
	(void)::CryptReleaseContext(hCryptProv, 0);
	UINT uiWaitTime = 0;
	if(iMaxTime>iMinTime)
	{
		uiWaitTime = (unsigned int)iMinTime + uiRandValue%((unsigned int)((unsigned int)iMaxTime - (unsigned int)iMinTime));
	}
	else
	{
		ERROR_LOG() << "iMaxTime <  iMinTime.";
		DEBUG_LOG() << "--- LEAVE";
		return (DWORD)THREAD_EXIT_ERR;
	}
	
	DEBUG_LOG() << "Enter avert swell time. the wait time is " << uiWaitTime;
	Sleep(uiWaitTime*1000);

	//下载升级
	if (NULL != m_pUpdateExecute && !m_pUpdateExecute->UpdateByDownload())
	{
		ERROR_LOG() << "Update by Download failed.";
		DEBUG_LOG() << "--- LEAVE";
		return (DWORD)THREAD_EXIT_ERR;
	}

	DEBUG_LOG() << "--- LEAVE";
	return THREAD_EXIT_SUCC;
}

bool UpdateExecute::SetServerUrl(const std::string& url)
{
	DEBUG_LOG() << "--- ENTER";
	INFO_PARAM1(url);

	UpdateServerConfig::SetServerUrl(url);

	DEBUG_LOG() << "--- LEAVE";
	return true;
}

std::string UpdateExecute::GetServerUrl()
{
	DEBUG_LOG() << "--- ENTER";

	std::string strServerUrl = UpdateServerConfig::GetServerUrl();
	INFO_PARAM1(strServerUrl);

	DEBUG_LOG() << "--- LEAVE";
	return strServerUrl;
}

bool UpdateExecute::SetMessageCallBack(MessageCallBack fpMsgCB)
{
	DEBUG_LOG() << "--- ENTER";

	if (NULL == fpMsgCB)
	{
		ERROR_LOG() << "MessageCallBack is null.";
		return false;
	}

	m_fpMsgCB = fpMsgCB;

	DEBUG_LOG() << "--- LEAVE";
	return true;
}

//////////////////////////////////////////////////////////////////////////

bool UpdateExecute::UpdateByLocalFile(void)
{
	DEBUG_LOG() << "--- ENTER";

	//设置升级文件路径
	std::string strPath("");
	eSDKTool::getModulePath("UpdateVersion.dll", strPath);
	strPath.append(DOWNLOAD_DIR_NAME);
	if (!::PathFileExistsA(strPath.c_str()))
	{
		DEBUG_LOG() << "--- LEAVE";
		return true;
	}

	std::string strFindName = strPath + "\\*.zip";

	//查找升级包文件
	_WIN32_FIND_DATAA findData;
	HANDLE hFindRar = ::FindFirstFileA(strFindName.c_str(), &findData);
	if (INVALID_HANDLE_VALUE == hFindRar)
	{
		DEBUG_LOG() << "--- LEAVE";
		return true;
	}

	//提示升级开始
	DEBUG_LOG() << "Update by local file.";
	if (NULL != m_fpMsgCB)
	{
		DEBUG_LOG() << "Clew update_start begin.";
		(void)m_fpMsgCB(UPDATE_START, "");
		DEBUG_LOG() << "Clew update_start end.";
	}	

	do 
	{
		//解压安装包
		std::string zipName = strPath + "\\" + findData.cFileName;
		if (!Extract(zipName))
		{
			ERROR_LOG() << "Extract zip file failed.";
			DEBUG_LOG() << "--- LEAVE";
			::FindClose(hFindRar);
			return false;
		}

		//执行升级
		std::string tempPath = zipName.substr(0, zipName.rfind('.')) + "\\";
		if (!RunBat(tempPath))
		{
			ERROR_LOG() << "RunBat failed.";
			DEBUG_LOG() << "--- LEAVE";
			::FindClose(hFindRar);
			return false;
		}

		//修改配置文件
		if (!ChangeFile(tempPath))
		{
			ERROR_LOG() << "Change Version info failed.";
			DEBUG_LOG() << "--- LEAVE";
			::FindClose(hFindRar);
			return false;
		}

		//读取Readme.txt
		if (!ReadReadMeTxt(tempPath))
		{
			ERROR_LOG() << "Read readme.txt failed.";
		}

	} while (::FindNextFile(hFindRar, &findData));
	::FindClose(hFindRar);

	//提示升级完成
	if (NULL != m_fpMsgCB)
	{
		DEBUG_LOG() << "Clew update_finished start.";
		(void)m_fpMsgCB(UPDATE_FINISHED, m_strReadMeTxt);
		DEBUG_LOG() << "Clew update_finished end.";
	}

	DEBUG_LOG() << "--- LEAVE";
	return true;
}

bool UpdateExecute::UpdateByDownload(void)
{
	DEBUG_LOG() << "--- ENTER";

	//从配置文件获取所有版本信息
	std::map<std::string, std::string> mapProductList;
	(void)GetProductList(mapProductList);
	if (mapProductList.empty())
	{
		ERROR_LOG() << "Product list is empty.";
		DEBUG_LOG() << "--- LEAVE";
		return false;
	}

	//缓存下载信息
	std::map<std::string, std::string> mapDownload;

	bool bForceUpdate = false;
	std::map<std::string, std::string>::const_iterator iter_begin = mapProductList.begin();
	std::map<std::string, std::string>::const_iterator iter_end = mapProductList.end();
	for (; iter_begin != iter_end; iter_begin++)
	{
		std::string strDownloadUrl("");
		std::string strForceUpdate("");
		if (!m_ClientVersionManage.CompareVersion(iter_begin->first, iter_begin->second, strDownloadUrl, strForceUpdate))
		{
			//DEBUG_LOG() << iter_begin->first << "is the last version.";
			continue;
		}

		//大小写转换
		if (NULL != strlwr(const_cast<char*>(strForceUpdate.c_str())))
		{
			if (!bForceUpdate && "true" == strForceUpdate)
			{
				bForceUpdate = true;
			}
		}		

		mapDownload.insert(std::make_pair(iter_begin->first, strDownloadUrl));//lint !e534
	}

	if (mapDownload.empty())
	{
		DEBUG_LOG() << "Not have update job.";
		DEBUG_LOG() << "--- LEAVE";
		return true;
	}

	//判断是否强制升级
	if (!bForceUpdate)
	{
		bool bAnswer = false;

		if (NULL != m_fpMsgCB)
		{
			DEBUG_LOG() << "Clew update_ask begin.";
			bAnswer = m_fpMsgCB(UPDATE_ASK, "");
			DEBUG_LOG() << "Clew update_ask end.";
		}		

		if (!bAnswer)	//不同意升级
		{
			DEBUG_LOG() << "User not agree to update version.";
			DEBUG_LOG() << "--- LEAVE";
			return true;
		}
	}
	
	std::string strPath("");
	eSDKTool::getModulePath("UpdateVersion.dll", strPath);
	strPath.append(DOWNLOAD_DIR_NAME);
	if (!::PathFileExistsA(strPath.c_str()))
	{
		if (0 != _mkdir(strPath.c_str()))
		{
			ERROR_LOG() << "Create download file path failed.";
			return false;
		}
	}

	//下载升级包
	iter_begin = mapDownload.begin();
	iter_end = mapDownload.end();
	for (; iter_begin != iter_end; iter_begin++)
	{
		if (!m_DownloadVersion.Download(strPath, iter_begin->second))
		{
			ERROR_LOG() << "Download failed.";
			DEBUG_LOG() << "--- LEAVE";
			return false;
		}
	}

	//执行升级
	if (!Execute(strPath))
	{
		ERROR_LOG() << "Execute failed.";
		DEBUG_LOG() << "--- LEAVE";
		return false;
	}

	DEBUG_LOG() << "--- LEAVE";
	return true;
}

bool UpdateExecute::Execute(const std::string& filePath)
{
	DEBUG_LOG() << "--- ENTER";

	std::string strFileName = filePath + "\\*.zip";
	_WIN32_FIND_DATAA findData;
	HANDLE hFind = ::FindFirstFileA(strFileName.c_str(), &findData);
	if (INVALID_HANDLE_VALUE == hFind)
	{
		ERROR_LOG() << " not find the *.zip";
		DEBUG_LOG() << "--- LEAVE";
		return false;
	}
	::FindClose(hFind);

	//无多个exe场景，无exe和bat同时出现场景，因此进行流程简化
	//解压压缩包
	std::string tempName = filePath + "\\" + findData.cFileName;
	if (!Extract(tempName))
	{
		ERROR_LOG() << "Extract zip file failed.";
		DEBUG_LOG() << "--- LEAVE";
		return false;
	}

	//读取version.txt
	std::string path = tempName.substr(0, tempName.rfind('.')) + "\\" + VERSION_INFO_FILE;
	FILE* stream = NULL;
	errno_t err = fopen_s(&stream, path.c_str(), "r");
	if (0 != err)
	{
		ERROR_LOG() << "fopen failed.";
		DEBUG_LOG() << "--- LEAVE";
		return false;
	}

	char Name[VERSION_READ_LENGTH] = {0};
	char Id[VERSION_READ_LENGTH] = {0};
	char Version[VERSION_READ_LENGTH] = {0}; 
	char Date[VERSION_READ_LENGTH] = {0};
	char IsforceUpdate[VERSION_READ_LENGTH] = {0};
	char IsInstancePackage[VERSION_READ_LENGTH] = {0};
	char line[VERSION_READ_LENGTH] = {0};

	while ( 0 == feof(stream) )
	{
		memset(line, 0, VERSION_READ_LENGTH);
		fgets(line, VERSION_READ_LENGTH, stream);
		if (0x0A == line[strlen(line)-1] || 0x0D == line[strlen(line)-1])
		{
			line[strlen(line)-1] = 0;
		}

		if (0 == strncmp(line, VERSION_NAME_FIELD, strlen(VERSION_NAME_FIELD)))
		{
			memcpy(Name, line+strlen(VERSION_NAME_FIELD), strlen(line) - strlen(VERSION_NAME_FIELD));
		}
		if (0 == strncmp(line, VERSION_ID_FIELD, strlen(VERSION_ID_FIELD)))
		{
			memcpy(Id, line+strlen(VERSION_ID_FIELD), strlen(line) - strlen(VERSION_ID_FIELD));
		}
		if (0 == strncmp(line, VERSION_VERSION_FIELD, strlen(VERSION_VERSION_FIELD)))
		{
			memcpy(Version, line+strlen(VERSION_VERSION_FIELD), strlen(line) - strlen(VERSION_VERSION_FIELD));
		}
		if (0 == strncmp(line, VERSION_DATE_FIELD, strlen(VERSION_DATE_FIELD)))
		{
			memcpy(Date, line+strlen(VERSION_DATE_FIELD), strlen(line) - strlen(VERSION_DATE_FIELD));
		}
		if (0 == strncmp(line, VERSION_FORCE_FIELD, strlen(VERSION_FORCE_FIELD)))
		{
			memcpy(IsforceUpdate, line+strlen(VERSION_FORCE_FIELD), strlen(line) - strlen(VERSION_FORCE_FIELD));
		}
		if (0 == strncmp(line, VERSION_INSTALL_FIELD, strlen(VERSION_INSTALL_FIELD)))
		{
			memcpy(IsInstancePackage, line+strlen(VERSION_INSTALL_FIELD), strlen(line) - strlen(VERSION_INSTALL_FIELD));
		}
	}
	INFO_PARAM6(Name,Id,Version,Date,IsforceUpdate,IsInstancePackage);
	fclose(stream);

	if (NULL == strlwr(IsInstancePackage))
	{
		ERROR_LOG() << "strlwr " << IsInstancePackage << " failed.";
		DEBUG_LOG() << "--- LEAVE";
		return false;
	}

	if (0 == strcmp(IsInstancePackage, "true"))
	{
		//删除压缩包
		if (!::DeleteFile(tempName.c_str()))
		{
			ERROR_LOG() << "Delete temp file failed.";
			DEBUG_LOG() << "--- LEAVE";
			return false;
		}

		//执行安装程序
		if (!RunMsi(tempName.substr(0, tempName.rfind('.')) + "\\"))
		{
			ERROR_LOG() << "RunMis failed.";
			DEBUG_LOG() << "--- LEAVE";
			return false;
		}
	}
	else if (0 == strcmp(IsInstancePackage, "false"))
	{
		//删除解压后的文件夹
		std::string strPath = tempName.substr(0, tempName.rfind('.')) + "\\";
		if (0 != DeleteDirectory(strPath))
		{
			ERROR_LOG() << "Remove temp directory failed.";
			return false;
		}
		DEBUG_LOG() << "Remove temp directory success.";
	}
	else
	{
		ERROR_LOG() << "read IsInstancePackage failed.";
		DEBUG_LOG() << "--- LEAVE";
		return false;
	}

	DEBUG_LOG() << "--- LEAVE";
	return true;
}

bool UpdateExecute::RunMsi(const std::string& filePath)const
{
	DEBUG_LOG() << "--- ENTER";

	std::string strFileName = filePath + "*.msi";
	_WIN32_FIND_DATAA findData;
	HANDLE hFind = ::FindFirstFileA(strFileName.c_str(), &findData);
	if (INVALID_HANDLE_VALUE == hFind)
	{
		strFileName = filePath + "*.exe";
		HANDLE hF = ::FindFirstFileA(strFileName.c_str(), &findData);
		if (INVALID_HANDLE_VALUE == hF)
		{
			ERROR_LOG() << "Neither find the *.msi nor the *.exe";
			DEBUG_LOG() << "--- LEAVE";
			return false;
		}
		::FindClose(hF);
	}
	::FindClose(hFind);

	strFileName = filePath + findData.cFileName;

	//提示升级开始
	DEBUG_LOG() << "Update by local file.";
	if (NULL != m_fpMsgCB)
	{
		DEBUG_LOG() << "Clew update_start begin.";
		(void)m_fpMsgCB(UPDATE_START, "");
		DEBUG_LOG() << "Clew update_start end.";
	}

	//执行安装包*.msi or *.exe
	HANDLE  h = ShellExecute(NULL, "open", strFileName.c_str(), NULL, NULL, SW_SHOW);

	if (h <= (HANDLE)SHELL_EXECUTE_HANDLE)
	{
		ERROR_LOG() << "Can't ShellExecute";
		DEBUG_LOG() << "--- LEAVE";
		return false;
	} 

	DEBUG_LOG() << "--- LEAVE";
	return true;
}

bool UpdateExecute::RunBat(const std::string& filePath)const
{
	DEBUG_LOG() << "--- ENTER";

	std::string strFileName = filePath + "*.bat";
	_WIN32_FIND_DATAA findData;
	HANDLE hFind = ::FindFirstFileA(strFileName.c_str(), &findData);
	if (INVALID_HANDLE_VALUE == hFind)
	{
		ERROR_LOG() << "Not find the *.bat";
		DEBUG_LOG() << "--- LEAVE";
		return false;
	}
	::FindClose(hFind);

	strFileName = filePath + findData.cFileName;	

	//执行安装包*.bat
	SHELLEXECUTEINFO ShExecInfo = {0};
	ShExecInfo.cbSize = sizeof(SHELLEXECUTEINFO);
	ShExecInfo.fMask = SEE_MASK_NOCLOSEPROCESS;
	ShExecInfo.hwnd = NULL;
	ShExecInfo.lpVerb = NULL;
	ShExecInfo.lpFile = strFileName.c_str(); 
	ShExecInfo.lpParameters = ""; 
	ShExecInfo.lpDirectory = filePath.c_str();
	ShExecInfo.nShow = SW_HIDE;
	ShExecInfo.hInstApp = NULL; 


	ShellExecuteEx(&ShExecInfo);
	WaitForSingleObject(ShExecInfo.hProcess, INFINITE);

	//HANDLE  h = ShellExecute(NULL, "open", strFileName.c_str(), NULL, NULL, SW_SHOW);


	//if (h <= (HANDLE)SHELL_EXECUTE_HANDLE)
	//{
	//	ERROR_LOG() << "Can't ShellExecute";
	//	DEBUG_LOG() << "--- LEAVE";
	//	return false;
	//}

	//Sleep(5000);

	DEBUG_LOG() << "--- LEAVE";
	return true;
}

bool UpdateExecute::Extract(const std::string& fileName)
{
	DEBUG_LOG() << "--- ENTER";

	unzFile uf = unzOpen(fileName.c_str());
	if (NULL == uf)
	{
		ERROR_LOG() << "unzOpen failed.";
		DEBUG_LOG() << "--- LEAVE";
		return false;
	}

	unz_global_info64 gi;

	int err = unzGetGlobalInfo64(uf, &gi);
	if (UNZ_OK != err)
	{
		ERROR_LOG() << "unzGetGlobalInfo64 failed.";
		DEBUG_LOG() << "--- LEAVE";
		unzClose(uf);
		return false;
	}

	std::string pathDir = fileName.substr(0,fileName.rfind('\\')+1);
	//some zipfile don't contain directory alone before file
	//if ( )
	//{
	//	std::string tempName = fileName.substr(0, fileName.rfind('.'));
	//	_mkdir(tempName.c_str());
	//	pathDir = tempName;
	//}
	
	//删除已有的目录
	std::string oldPathDir = fileName.substr(0,fileName.rfind('.'));
	oldPathDir.append("\\");
	if (::PathFileExistsA(oldPathDir.c_str()))
	{
		if (0 != DeleteDirectory(oldPathDir))
		{
			ERROR_LOG() << "Remove old path directory failed.";
			return false;
		}
		DEBUG_LOG() << "Remove old path directory success.";
	}


	for (uLong i=0; i<gi.number_entry; i++)
	{
		//do_extract_currentfile
		if (UNZ_OK != do_extract_currentfile(uf, pathDir.c_str()))
		{
			ERROR_LOG() << "do_extract_currentfile failed.";
			DEBUG_LOG() << "--- LEAVE";
			unzClose(uf);
			return false;
		}

		if ((i+1) < gi.number_entry)//lint !e776
		{
			err = unzGoToNextFile(uf);
			if (UNZ_OK != err)
			{
				ERROR_LOG() << "unzGoToNextFile failed.";
				DEBUG_LOG() << "--- LEAVE";
				unzClose(uf);
				return false;
			}
		}
	}

	unzClose(uf);

	DEBUG_LOG() << "--- LEAVE";
	return true;//lint !e438
}

int UpdateExecute::do_extract_currentfile(unzFile uf, const char* pathDir)const
{
	if (NULL == pathDir)
	{
		ERROR_LOG() << "pathDir is null";
		return UNZ_ERRNO;
	}

	char filename_inzip[256];
	unz_file_info64 file_info;
	int err = unzGetCurrentFileInfo64(uf, &file_info, filename_inzip, sizeof(filename_inzip), NULL, 0, NULL, 0);
	if (UNZ_OK != err)
	{
		ERROR_LOG() << "unzGetCurrentFileInfo64 failed.";
		return err;
	}

	std::string fileName(pathDir);
	fileName.append(filename_inzip);
	if ('\\' == *fileName.rbegin() || '/' == *fileName.rbegin())
	{
		if (0 != _mkdir(fileName.c_str()))
		{
			ERROR_LOG() << "Create file failed.";
			return UNZ_ERRNO;
		}
	}
	else
	{
		err = unzOpenCurrentFilePassword(uf, NULL);
		if (UNZ_OK != err)
		{
			ERROR_LOG() << "unzOpenCurrentFilePassword failed.";
			return err;
		}

		FILE* fout=fopen64(fileName.c_str(),"wb");
		if (NULL == fout)
		{
			ERROR_LOG() << "fopen64 failed.";
			err = UNZ_ERRNO;
			return err;
		}

		uInt size_buf = WRITEBUFFERSIZE;
		void* buf = (void*)malloc(size_buf);
		if (NULL == buf)
		{
			ERROR_LOG() << "Error allocating memory.";
			fclose(fout);
			return UNZ_INTERNALERROR;
		}

		do
		{
			err = unzReadCurrentFile(uf, buf, size_buf);
			if (err < 0)
			{
				ERROR_LOG() << "error with zipfile in unzReadCurrentFile";
				break;
			}
			if (err > 0)
			{
				if (1 != fwrite(buf, (unsigned int)err, 1, fout))
				{
					ERROR_LOG() << "error in writing extracted file";
					err = UNZ_ERRNO;
					break;
				}
			}
		} while(err > 0);

		fclose(fout);

		if (UNZ_OK != err)
		{
			unzCloseCurrentFile(uf); /* don't lose the error */
		}
		else
		{
			change_file_date(fileName.c_str(), file_info.dosDate, file_info.tmu_date);

			err = unzCloseCurrentFile (uf);
			if (UNZ_OK != err)
			{
				ERROR_LOG() << "unzCloseCurrentFile failed.";
			}
		}
		free(buf);
	}

	return err;
}

void UpdateExecute::change_file_date(const char *filename, uLong dosdate,const tm_unz& tmu_date)const
{
	HANDLE hFile;
	FILETIME ftm,ftLocal,ftCreate,ftLastAcc,ftLastWrite;

	hFile = CreateFileA(filename,GENERIC_READ | GENERIC_WRITE,
		0,NULL,OPEN_EXISTING,0,NULL);
	GetFileTime(hFile,&ftCreate,&ftLastAcc,&ftLastWrite);
	DosDateTimeToFileTime((WORD)(dosdate>>16),(WORD)dosdate,&ftLocal);
	LocalFileTimeToFileTime(&ftLocal,&ftm);
	SetFileTime(hFile,&ftm,&ftLastAcc,&ftm);
	CloseHandle(hFile);
}

bool UpdateExecute::ReadReadMeTxt(const std::string& filePath)
{
	DEBUG_LOG() << "--- ENTER";

	std::string strReadMeTxt = filePath + README_TXT_FILE;
	FILE* stream = NULL;
	errno_t err = fopen_s(&stream, strReadMeTxt.c_str(), "r");
	if (0 != err)
	{
		ERROR_LOG() << "fopen txt file failed.";
		DEBUG_LOG() << "--- LEAVE";
		return false;
	}

	if (NULL == stream)
	{
		ERROR_LOG() << "fopen txt file failed.";
		DEBUG_LOG() << "--- LEAVE";
		return false;
	}

	const int LENGTH = 256;
	char buf[LENGTH] = {0};
	while ( !feof(stream) )
	{
		unsigned int iCnt = fread(buf, sizeof(char), LENGTH-1, stream);
		if (0 == iCnt)
		{
			ERROR_LOG() << "fread txt file failed.";
			DEBUG_LOG() << "--- LEAVE";
			fclose(stream);
			return false;
		}

		m_strReadMeTxt.append(buf);
		memset(buf, 0, sizeof(char)*LENGTH);
	}
	m_strReadMeTxt.append("\n");
	fclose(stream);

	DEBUG_LOG() << "--- LEAVE";
	return true;
}

bool UpdateExecute::ClearAllTempFile()
{
	DEBUG_LOG() << "--- ENTER";

	std::string strPath("");
	eSDKTool::getModulePath("UpdateVersion.dll", strPath);
	strPath.append(DOWNLOAD_DIR_NAME);
	strPath.append("\\");

	if (::PathFileExistsA(strPath.c_str()))
	{
		if (0 != DeleteDirectory(strPath))
		{
			DEBUG_LOG() << "Remove temp directory failed.";
			return false;
		}
		DEBUG_LOG() << "Remove temp directory success.";
	}

	DEBUG_LOG() << "--- LEAVE";
	return true;
}

int UpdateExecute::DeleteDirectory(const std::string &refcstrRootDirectory, bool bDeleteSubdirectories)
{
	bool            bSubdirectory = false;       // Flag, indicating whether
	// subdirectories have been found
	HANDLE          hFile;                       // Handle to directory
	std::string     strFilePath;                 // Filepath
	std::string     strPattern;                  // Pattern
	WIN32_FIND_DATA FileInformation = {0};       // File information


	strPattern = refcstrRootDirectory + "\\*.*";
	hFile = ::FindFirstFile(strPattern.c_str(), &FileInformation);
	if(hFile != INVALID_HANDLE_VALUE)
	{
		do
		{
			if(FileInformation.cFileName[0] != '.')
			{
				strFilePath.erase();
				strFilePath = refcstrRootDirectory + "\\" + FileInformation.cFileName;

				if(FileInformation.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
				{
					if(bDeleteSubdirectories)
					{
						// Delete subdirectory
						int iRC = DeleteDirectory(strFilePath, bDeleteSubdirectories);
						if(iRC)
						{
							::FindClose(hFile);
							return iRC;
						}
					}
					else
					{
						bSubdirectory = true;
					}
				}
				else
				{
					// Set file attributes
					if(::SetFileAttributes(strFilePath.c_str(),FILE_ATTRIBUTE_NORMAL) == FALSE)
					{
						::FindClose(hFile);
						return (int)::GetLastError();
					}

					// Delete file
					if(::DeleteFile(strFilePath.c_str()) == FALSE)
					{
						::FindClose(hFile);
						return (int)::GetLastError();
					}
				}
			}
		} while(::FindNextFile(hFile, &FileInformation) == TRUE);

		// Close handle
		::FindClose(hFile);

		DWORD dwError = ::GetLastError();
		if(dwError != ERROR_NO_MORE_FILES)
		{
			return (int)dwError;
		}
		else
		{
			if(!bSubdirectory)
			{
				// Set directory attributes
				if(::SetFileAttributes(refcstrRootDirectory.c_str(),FILE_ATTRIBUTE_NORMAL) == FALSE)
				{
					return (int)::GetLastError();
				}

				// Delete directory
				if(::RemoveDirectory(refcstrRootDirectory.c_str()) == FALSE)
				{
					return (int)::GetLastError();
				}
			}
		}
	}

	return 0;
}

bool UpdateExecute::ReadProductInfo()
{
	DEBUG_LOG() << "--- ENTER";

	m_mapProductInfo.clear();

	std::string strPath("");
	eSDKTool::getModulePath("UpdateVersion.dll", strPath);
	strPath.append(PRODUCT_INFO_FILE);

	const int SIZE = 1024*2;
	char* buffer = new char[SIZE];
	memset(buffer,0,SIZE);
	DWORD dwNum = ::GetPrivateProfileStringA(NULL, "", NULL, buffer, 1024*2-1, strPath.c_str());
	if (0 == dwNum)
	{
		ERROR_LOG() << "Read ProductInfo.ini failed.";
		DEBUG_LOG() << "--- LEAVE";
		delete []buffer;
		return false;
	}

	std::vector<std::string> vecSection;
	char* pTemp = buffer;
	vecSection.push_back(pTemp);
	for (DWORD i=0; i<dwNum-1; i++)
	{
		if (0 == buffer[i] && 0 != buffer[i+1])
		{
			pTemp = &buffer[i+1];
			vecSection.push_back(pTemp);
		}
	}
	delete []buffer;

	const int LENGTH = 32;
	char Id[LENGTH] = {0};
	size_t size = vecSection.size();
	for (size_t i=0; i<size; i++)
	{
		DWORD dwNumber = ::GetPrivateProfileStringA(vecSection[i].c_str(), PDU_INI_KEY_ID, NULL, Id, LENGTH-1, strPath.c_str());
		if (0 == dwNumber)
		{
			ERROR_LOG() << "Read Name in ProductInfo.ini failed.";
			DEBUG_LOG() << "--- LEAVE";
			return false;
		}

		m_mapProductInfo.insert(std::make_pair(vecSection[i], Id));//lint !e534
	}

	DEBUG_LOG() << "--- LEAVE";
	return true;
}

bool UpdateExecute::GetProductList(std::map<std::string, std::string>& mapProductList)const
{
	DEBUG_LOG() << "--- ENTER";

	std::string strPath("");
	eSDKTool::getModulePath("UpdateVersion.dll", strPath);
	strPath.append(VERSION_FILE_NAME);

	const int SIZE = 1024*2;
	char* buffer = new char[SIZE];
	memset(buffer,0,SIZE);
	DWORD dwNum = ::GetPrivateProfileStringA(NULL, "", NULL, buffer, 1024*2-1, strPath.c_str());
	if (0 == dwNum)
	{
		ERROR_LOG() << "Read version failed.";
		DEBUG_LOG() << "--- LEAVE";
		delete []buffer;
		return false;
	}

	std::vector<std::string> vecSection;
	char* pTemp = buffer;
	vecSection.push_back(pTemp);
	for (DWORD i=0; i<dwNum-1; i++)
	{
		if (0 == buffer[i] && 0 != buffer[i+1])
		{
			pTemp = &buffer[i+1];
			vecSection.push_back(pTemp);
		}
	}
	delete []buffer;

	const int LENGTH = 32;
	char Id[LENGTH] = {0};
	char Ver[LENGTH] = {0};
	size_t size = vecSection.size();
	for (size_t i=0; i<size; i++)
	{
		dwNum = ::GetPrivateProfileStringA(vecSection[i].c_str(), VER_INI_KEY_ID, NULL, Id, LENGTH-1, strPath.c_str());
		if (0 == dwNum)
		{
			ERROR_LOG() << "Read ID failed.";
			DEBUG_LOG() << "--- LEAVE";
			mapProductList.clear();
			return false;
		}

		dwNum = ::GetPrivateProfileStringA(vecSection[i].c_str(), VER_INI_KEY_VERSION, NULL, Ver, LENGTH-1, strPath.c_str());
		if (0 == dwNum)
		{
			ERROR_LOG() << "Read Version failed.";
			DEBUG_LOG() << "--- LEAVE";
			mapProductList.clear();
			return false;
		}

		mapProductList.insert(std::make_pair(Id, Ver));//lint !e534
	}

	DEBUG_LOG() << "--- LEAVE";
	return true;
}

bool UpdateExecute::WriteFile(const std::string& Name, const std::string& version)
{
	DEBUG_LOG() << "--- ENTER";
	INFO_PARAM2(Name, version);

	//获取产品ID
	std::map<std::string, std::string>::iterator iter = m_mapProductInfo.find(Name);
	if (m_mapProductInfo.end() == iter)
	{
		ERROR_LOG() << "Get product ID by Name failed.";
		return false;
	}
	std::string Id = iter->second;

	//获取配置文件路径
	std::string strPath("");
	eSDKTool::getModulePath("UpdateVersion.dll", strPath);
	strPath.append(VERSION_FILE_NAME);

	if (!::WritePrivateProfileStringA(Name.c_str(), VER_INI_KEY_ID, Id.c_str(), strPath.c_str()))
	{
		ERROR_LOG() << "Write Id failed.";
		DEBUG_LOG() << "--- LEAVE";
		return false;
	}
	if (!::WritePrivateProfileStringA(Name.c_str(), VER_INI_KEY_VERSION, version.c_str(), strPath.c_str()))
	{
		ERROR_LOG() << "Write Version failed.";
		DEBUG_LOG() << "--- LEAVE";
		return false;
	}

	DEBUG_LOG() << "--- LEAVE";
	return true;
}

bool UpdateExecute::ChangeFile(const std::string& filePath)const
{
	DEBUG_LOG() << "--- ENTER";
	INFO_PARAM1(filePath);

	//读取version.txt
	std::string path = filePath + VERSION_INFO_FILE;
	FILE* stream = NULL;
	errno_t err = fopen_s(&stream, path.c_str(), "r");
	if (0 != err)
	{
		ERROR_LOG() << "fopen failed.";
		DEBUG_LOG() << "--- LEAVE";
		return false;
	}

	char name[VERSION_READ_LENGTH] = {0};
	char ID[VERSION_READ_LENGTH] = {0};
	char version[VERSION_READ_LENGTH] = {0};
	char line[VERSION_READ_LENGTH] = {0};

	while ( !feof(stream) )
	{
		memset(line, 0, VERSION_READ_LENGTH);
		fgets(line, VERSION_READ_LENGTH, stream);
		if (0x0A == line[strlen(line)-1] || 0x0D == line[strlen(line)-1])
		{
			line[strlen(line)-1] = 0;
		}

		if (0 == strncmp(line, VERSION_NAME_FIELD, strlen(VERSION_NAME_FIELD)))
		{
			memcpy(name, line+strlen(VERSION_NAME_FIELD), strlen(line) - strlen(VERSION_NAME_FIELD));
		}
		if (0 == strncmp(line, VERSION_ID_FIELD, strlen(VERSION_ID_FIELD)))
		{
			memcpy(ID, line+strlen(VERSION_ID_FIELD), strlen(line) - strlen(VERSION_ID_FIELD));
		}
		if (0 == strncmp(line, VERSION_VERSION_FIELD, strlen(VERSION_VERSION_FIELD)))
		{
			memcpy(version, line+strlen(VERSION_VERSION_FIELD), strlen(line) - strlen(VERSION_VERSION_FIELD));
		}
		if (0 < strlen(name) && 0 < strlen(ID) && 0 < strlen(version))
		{
			break;
		}
	}
	INFO_PARAM3(name, ID, version);
	fclose(stream);

	if (0 == strlen(name) || 0 == strlen(ID) || 0 == strlen(version))
	{
		ERROR_LOG() << "Get version info from version.txt failed.";
		DEBUG_LOG() << "--- LEAVE";
		return false;
	}

	//获取配置文件路径
	std::string strPath("");
	eSDKTool::getModulePath("UpdateVersion.dll", strPath);
	strPath.append(VERSION_FILE_NAME);

	//老版本配置信息
	const int LENGTH = 32;
	char ver[LENGTH] = {0};
	DWORD dwNum = ::GetPrivateProfileStringA(name, VER_INI_KEY_VERSION, NULL, ver, LENGTH-1, strPath.c_str());
	if (0 == dwNum)
	{
		ERROR_LOG() << "Can not find the old version.";
		DEBUG_LOG() << "--- LEAVE";
		return false;
	}

	//更新配置文件信息
	if (!::WritePrivateProfileStringA(name, VER_INI_KEY_ID, ID, strPath.c_str()))
	{
		ERROR_LOG() << "Write Id failed.";
		DEBUG_LOG() << "--- LEAVE";
		return false;
	}
	if (!::WritePrivateProfileStringA(name, VER_INI_KEY_VERSION, version, strPath.c_str()))
	{
		ERROR_LOG() << "Write Version failed.";
		DEBUG_LOG() << "--- LEAVE";
		return false;
	}

	DEBUG_LOG() << "--- LEAVE";
	return true;
}

bool UpdateExecute::GetAvertSurgeTime(int& iMaxTime, int& iMinTime)
{
	DEBUG_LOG() << "--- ENTER";

	char path[MAX_PATH] = {0};
	GetModuleFileName(GetModuleHandle(DLL_FILE_NAME), path, MAX_PATH);
	std::string strPath(path);
	strPath = strPath.substr(0, strPath.rfind("\\")+1);
	strPath.append(CONF_FILE_NAME);

	const int VALUE_LENGTH = 16;
	char value[VALUE_LENGTH] = {0};
	DWORD iRet = GetPrivateProfileString(AVERT_SURGE_CONFIG_SECTION, AVERT_SURGE_CONFIG_KEYMAXT, "", value, VALUE_LENGTH, strPath.c_str());
	if (0 == iRet)
	{
		ERROR_LOG() << "Read avert surge time from config file failed.";
		iMaxTime = AVERT_SURGE_TIME_MAX;
		iMinTime = AVERT_SURGE_TIME_MIN;
		return false;
	}
	iMaxTime = atoi(value);

	memset(value, 0, VALUE_LENGTH);
	iRet = GetPrivateProfileString(AVERT_SURGE_CONFIG_SECTION, AVERT_SURGE_CONFIG_KEYMINT, "", value, VALUE_LENGTH, strPath.c_str());
	if (0 == iRet)
	{
		ERROR_LOG() << "Read avert surge time from config file failed.";
		iMaxTime = AVERT_SURGE_TIME_MAX;
		iMinTime = AVERT_SURGE_TIME_MIN;
		return false;
	}
	iMinTime = atoi(value);

	INFO_PARAM2(iMaxTime, iMinTime);	
	DEBUG_LOG() << "--- LEAVE";
	return true;
}


