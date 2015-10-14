#include <Windows.h>
#include <io.h>
#include <direct.h>
#include <fstream>
#include <Shlwapi.h>
#include "DownloadVersion.h"
//#include "UpdateServerConfig.h"
#include "eSDKLog.h"

#pragma comment( lib, "wininet.lib" )
#pragma comment(lib, "Shlwapi.lib")

#define HTTP_OK			200
#define MAXRECVBUFF		(4096*10)  //���ջ����С
#define REQUEST_COUNT	3


DownloadVersion::DownloadVersion()
	: m_fout(NULL)
	, m_hOpen(NULL)
	, m_hOpenUrl(NULL)
	, m_hConnect(NULL)
	, m_hRequest(NULL)
{
	
}

DownloadVersion::~DownloadVersion()
{
	if (NULL != m_hOpenUrl)
	{
		InternetCloseHandle(m_hOpenUrl); 
		m_hOpenUrl = NULL;
	}

	if (NULL != m_hRequest)
	{
		InternetCloseHandle(m_hRequest); 
		m_hRequest = NULL;
	}

	if (NULL != m_hConnect)
	{
		InternetCloseHandle(m_hConnect); 
		m_hConnect = NULL;
	}	

	if (NULL != m_hOpen)
	{
		InternetCloseHandle(m_hOpen);
		m_hOpen = NULL;
	}

	if (NULL != m_fout)
	{
		fclose(m_fout);
		m_fout = NULL;
	}
}


bool DownloadVersion::Download(const std::string& strDownloadPath, const std::string& strDownloadUrl)
{
	DEBUG_LOG() << "--- ENTRY";

	// ����ж�
	if (strDownloadPath.empty())
	{
		ERROR_LOG() << "strDownloadPath is empty.";
		return false;
	}
	if (strDownloadUrl.empty())
	{
		ERROR_LOG() << "strDownloadUrl is empty.";
		return false;
	}

	// ���������ļ�����Ŀ¼
	if (!::PathFileExistsA(strDownloadPath.c_str()))
	{
		if (0 != _mkdir(strDownloadPath.c_str()))
		{
			ERROR_LOG() << "Create Download Dir fail";
			return false;
		}
		INFO_LOG() << "Create Download Dir succ.";
	}

	// https����
	bool bRet;
	if (std::string::npos != strDownloadUrl.find("https:"))
	{
		bRet = HttpsDownload(strDownloadPath, strDownloadUrl);
	}
	// http����
	else
	{
		bRet = HttpDownload(strDownloadPath, strDownloadUrl);
	}

	DEBUG_LOG() << "--- LEAVE";
	return bRet;
}


void DownloadVersion::CloseResourceWhenThreadTerminate(void)
{
	if (NULL != m_hOpenUrl)
	{
		InternetCloseHandle(m_hOpenUrl);			
		m_hOpenUrl = NULL;
	}

	if (NULL != m_hRequest)
	{
		InternetCloseHandle(m_hRequest); 
		m_hRequest = NULL;
	}

	if (NULL != m_hConnect)
	{
		InternetCloseHandle(m_hConnect); 
		m_hConnect = NULL;
	}	

	if (NULL != m_hOpen)
	{
		InternetCloseHandle(m_hOpen);
		m_hOpen = NULL;
	}

	Sleep(500);

	if (NULL != m_fout)
	{
		fclose(m_fout);
		m_fout = NULL;
	}

	return;
}


bool DownloadVersion::HttpDownload(const std::string& strDownloadPath, const std::string& strDownloadUrl)
{
	DEBUG_LOG() << "--- ENTRY";

	// ������
	m_hOpen = ::InternetOpen("DownloadVersion", INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, 0);
	if (NULL == m_hOpen)
	{
		ERROR_LOG() << "InternetOpen failed. (" << GetLastError() << ")";
		return false;
	}

	m_hOpenUrl = ::InternetOpenUrl(m_hOpen, strDownloadUrl.c_str(), NULL, 0, INTERNET_FLAG_RELOAD, 0);
	if (NULL == m_hOpenUrl)
	{
		ERROR_LOG() << "InternetOpenUrl failed. (" << GetLastError() << ")";
		::InternetCloseHandle(m_hOpen);
		m_hOpen = NULL;
		return false;
	}

	// ��ȡ�ļ���С
	unsigned long long dwTotalSize = 0; // ���ط�����ļ���С
	DWORD dwSizeOfRq = 4;
	DWORD dwStatus = 0;
	BOOL bRet = ::HttpQueryInfo(m_hOpenUrl, HTTP_QUERY_STATUS_CODE | HTTP_QUERY_FLAG_NUMBER, (LPVOID)&dwStatus, &dwSizeOfRq, NULL); // ��ѯhttp״̬
	if (!bRet)
	{
		::InternetCloseHandle(m_hOpenUrl);
		m_hOpenUrl = NULL;
		::InternetCloseHandle(m_hOpen);
		m_hOpen = NULL;
		ERROR_LOG() << "HttpQueryInfo STATUS_CODE failed. (" << GetLastError() << ")";
		return false;
	}
	if (HTTP_OK != dwStatus)
	{
		::InternetCloseHandle(m_hOpenUrl);  
		m_hOpenUrl = NULL;
		::InternetCloseHandle(m_hOpen);
		m_hOpen = NULL;
		ERROR_LOG() << "HttpQueryInfo HTTP_STATUS_CODE failed. (" << GetLastError() << ")";
		return false;
	}
	char buffer[MAX_PATH] = {0};
	DWORD dwLengthSizeBuffer = sizeof(buffer);
	// ��ѯ������ļ���С
	bRet = ::HttpQueryInfo(m_hOpenUrl, HTTP_QUERY_CONTENT_LENGTH, buffer, &dwLengthSizeBuffer, NULL); 
	dwTotalSize = (unsigned long long)_atoi64(buffer);//lint !e838

	// ��ȡ�ļ���
	memset(buffer, 0, MAX_PATH);
	dwLengthSizeBuffer = sizeof(buffer);
	// ��ѯ������ļ���С
	bRet = ::HttpQueryInfo(m_hOpenUrl, HTTP_QUERY_CONTENT_DISPOSITION, buffer, &dwLengthSizeBuffer, NULL);   //lint !e838
	std::string strFileName;
	std::string strFilePath = strDownloadPath;
	if (bRet)
	{
		strFileName = buffer;
		strFileName = strFileName.substr(strFileName.find("filename=")+strlen("filename="), strFileName.find(".zip")+strlen(".zip"));	
		strFilePath.append("\\");
		strFilePath.append(strFileName);
	}
	else
	{
		strFileName = strDownloadUrl.substr(strDownloadUrl.rfind("/")+1, std::string::npos);
		strFilePath.append("\\");
		strFilePath.append(strFileName);
	}

	// �����ļ�
	DWORD dwRead = 0;
	unsigned long long dwCurTotal = 0;
	char *pBuffer = new char[MAXRECVBUFF];
	memset(pBuffer, 0, MAXRECVBUFF);
	try
	{
		std::string strTempName = strFilePath + ".tmp";
		//write to the Download dir
		m_fout = fopen(strTempName.c_str(), "wb");
		if (NULL == m_fout)
		{
			ERROR_LOG() << "Open File Failed.";
			::InternetCloseHandle(m_hOpenUrl); 
			m_hOpenUrl = NULL;
			::InternetCloseHandle(m_hOpen);
			m_hOpen = NULL;
			delete []pBuffer;
			pBuffer = NULL;
			return false;
		}

		do 
		{
			if (!::InternetReadFile(m_hOpenUrl, pBuffer, MAXRECVBUFF-1, &dwRead))
			{
				ERROR_LOG() << "InternetReadFile failed.";
				WARN_LOG() << "Server file size : " << dwTotalSize << "bytes, Download : " << dwCurTotal << "bytes";

				::InternetCloseHandle(m_hOpenUrl); 
				m_hOpenUrl = NULL;
				::InternetCloseHandle(m_hOpen);
				m_hOpen = NULL;

				delete []pBuffer;
				pBuffer = NULL;

				fclose(m_fout);
				m_fout = NULL;
				(void)::DeleteFile(strTempName.c_str());
				return false;
			}
			if (NULL == m_fout && dwRead > 0)
			{
				if (NULL != m_hOpenUrl)
				{
					::InternetCloseHandle(m_hOpenUrl); 
					m_hOpenUrl = NULL;
				}
				if (NULL != m_hOpen)
				{
					::InternetCloseHandle(m_hOpen); 
					m_hOpenUrl = NULL;
				}

				delete []pBuffer;
				pBuffer = NULL;
				(void)::DeleteFile(strTempName.c_str());
				return false;
			}

			pBuffer[dwRead] = 0;
			fwrite(pBuffer, sizeof(char), dwRead, m_fout);
			memset(pBuffer, 0, MAXRECVBUFF);
			dwCurTotal += dwRead;
			//DEBUG_LOG() << "Download : " << (dwCurTotal*100)/dwTotalSize << "%";
		} while (dwRead > 0);

		delete []pBuffer;
		pBuffer = NULL;
		fclose(m_fout);
		m_fout = NULL;
		DEBUG_LOG() << "Server file size : " << dwTotalSize << "bytes, Download : " << dwCurTotal << "bytes";

		// ������ɺ��޸��ļ���
		if (dwTotalSize == dwCurTotal)
		{
			rename(strTempName.c_str(), strFilePath.c_str());
		}
		else
		{
			::InternetCloseHandle(m_hRequest);
			m_hRequest = NULL;
			::InternetCloseHandle(m_hConnect);
			m_hConnect = NULL;
			::InternetCloseHandle(m_hOpen);
			m_hOpen = NULL;
			return false;	
		}
	}
	catch( ... )
	{
		::InternetCloseHandle(m_hOpenUrl);  
		m_hOpenUrl = NULL;
		::InternetCloseHandle(m_hOpen);
		m_hOpen = NULL;

		delete []pBuffer;
		pBuffer = NULL;

		if (NULL != m_fout)
		{
			fclose(m_fout);
			m_fout = NULL;
		}

		ERROR_LOG() << "Download file exception.";
		return false;//lint !e438
	}

	::InternetCloseHandle(m_hOpenUrl); 
	m_hOpenUrl = NULL;
	::InternetCloseHandle(m_hOpen);
	m_hOpen = NULL;

	DEBUG_LOG() << "--- LEAVE";
	return true;
}

bool DownloadVersion::HttpsDownload(const std::string& strDownloadPath, const std::string& strDownloadUrl)
{
	DEBUG_LOG() << "--- ENTRY";

	// ��������
	m_hOpen = ::InternetOpen("DownloadVersion", INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0);
	if (NULL == m_hOpen)
	{
		ERROR_LOG() << "InternetOpen failed. (" << GetLastError() << ")";
		return false;
	}

	std::string strSubTemp = strDownloadUrl.substr(strDownloadUrl.find("https://")+strlen("https://"), std::string::npos);
	std::string strServerName = strSubTemp.substr(0, strSubTemp.find(":"));
	strSubTemp = strSubTemp.substr(strSubTemp.find(":")+1, std::string::npos);
	std::string strPort = strSubTemp.substr(0, strSubTemp.find("/"));
	m_hConnect = ::InternetConnect(m_hOpen, strServerName.c_str(), (INTERNET_PORT)atoi(strPort.c_str()), NULL, NULL, INTERNET_SERVICE_HTTP, 0, 0);
	if (NULL == m_hConnect)
	{
		ERROR_LOG() << "InternetConnect failed. (" << GetLastError() << ")";
		::InternetCloseHandle(m_hOpen);
		m_hOpen = NULL;
		return false;
	}

	// ��������
	strSubTemp = strSubTemp.substr(strSubTemp.find("/"), std::string::npos);
	DWORD dwFlags = INTERNET_FLAG_RELOAD | INTERNET_FLAG_NO_CACHE_WRITE | INTERNET_FLAG_KEEP_CONNECTION
		| INTERNET_FLAG_SECURE  | INTERNET_FLAG_IGNORE_CERT_CN_INVALID | INTERNET_FLAG_IGNORE_CERT_DATE_INVALID;
	LPCSTR sAcceptTypes = "*/*";
	m_hRequest = ::HttpOpenRequest(m_hConnect, "GET", strSubTemp.c_str(), HTTP_VERSION, NULL, &sAcceptTypes, dwFlags, 0);
	if (NULL == m_hRequest)
	{
		ERROR_LOG() << "HttpOpenRequest failed. (" << GetLastError() << ")";
		::InternetCloseHandle(m_hConnect);
		m_hConnect = NULL;
		::InternetCloseHandle(m_hOpen);
		m_hOpen = NULL;
		return false;
	}

	// �������
	std::string strHeaders = "Accept:*/*\r\nContent-Type:application/octet-stream;charset=UTF-8";
	BOOL bRet = ::HttpAddRequestHeaders(m_hRequest, strHeaders.c_str(), (DWORD)-1, HTTP_ADDREQ_FLAG_ADD | HTTP_ADDREQ_FLAG_REPLACE);
	if (!bRet)
	{
		ERROR_LOG() << "HttpAddRequestHeaders failed. (" << GetLastError() << ")";
		::InternetCloseHandle(m_hRequest);
		m_hRequest = NULL;
		::InternetCloseHandle(m_hConnect);
		m_hConnect = NULL;
		::InternetCloseHandle(m_hOpen);
		m_hOpen = NULL;
		return false;
	}

	// ��������
	unsigned int nLen = strDownloadUrl.length();
	int nErrorCount = 0; // ��������Ĵ���
	bRet = ::HttpSendRequest(m_hRequest, NULL, (DWORD)-1, (void*)strDownloadUrl.c_str(), (unsigned long)nLen);//lint !e1773
	while( !bRet && REQUEST_COUNT > nErrorCount)
	{
		nErrorCount++;
		DWORD dwError = GetLastError() ; 
		if (ERROR_INTERNET_CLIENT_AUTH_CERT_NEEDED == dwError)
		{
			LPVOID dwCert = NULL;
			::InternetErrorDlg(NULL,
								m_hRequest,
								ERROR_INTERNET_CLIENT_AUTH_CERT_NEEDED,
								FLAGS_ERROR_UI_FILTER_FOR_ERRORS | FLAGS_ERROR_UI_FLAGS_GENERATE_DATA | FLAGS_ERROR_UI_FLAGS_CHANGE_OPTIONS,
								&dwCert
								);
			::InternetSetOption(m_hRequest, INTERNET_OPTION_SECURITY_SELECT_CLIENT_CERT, dwCert, sizeof(dwCert));
		}
		else if (ERROR_INTERNET_INVALID_CA == dwError)
		{
			DWORD dwBuffLen = sizeof(dwFlags);
			::InternetQueryOption(m_hRequest, INTERNET_OPTION_SECURITY_FLAGS, (LPVOID)&dwFlags, &dwBuffLen);
			dwFlags |= SECURITY_FLAG_IGNORE_UNKNOWN_CA;
			::InternetSetOption(m_hRequest, INTERNET_OPTION_SECURITY_FLAGS, &dwFlags, sizeof(dwFlags));
		}
		else
		{
			break;
		}
	}

	if (!bRet)
	{
		bRet = ::HttpSendRequest(m_hRequest, NULL, (DWORD)-1, (void*)(const_cast<char*>(strDownloadUrl.c_str())), (unsigned long)nLen);
	}

	if (!bRet)
	{
		ERROR_LOG() << "HttpSendRequest failed. (" << GetLastError() << ")";
		::InternetCloseHandle(m_hRequest);
		m_hRequest = NULL;
		::InternetCloseHandle(m_hConnect);
		m_hConnect = NULL;
		::InternetCloseHandle(m_hOpen);
		m_hOpen = NULL;
		return false;
	}

	// ��ѯ������Ϣ
	DWORD dwSizeOfRq = 4;
	DWORD dwStatus = 0;
	bRet = ::HttpQueryInfo(m_hRequest, HTTP_QUERY_STATUS_CODE | HTTP_QUERY_FLAG_NUMBER, &dwStatus, &dwSizeOfRq, NULL);
	if (!bRet)
	{
		ERROR_LOG() << "HttpQueryInfo failed. (" << GetLastError() << ")";
		::InternetCloseHandle(m_hRequest);
		m_hRequest = NULL;
		::InternetCloseHandle(m_hConnect);
		m_hConnect = NULL;
		::InternetCloseHandle(m_hOpen);
		m_hOpen = NULL;
		return false;
	}

	// ����������ķ�����Ϣ,�õ�״̬������
	if (HTTP_STATUS_PROXY_AUTH_REQ == dwStatus)
	{
		// �����˺ź����룬�����²�ѯ
		// ���ﲻ����
		// .....
		ERROR_LOG() << "HttpQueryInfo failed. (" << GetLastError() << ")";
		::InternetCloseHandle(m_hRequest);
		m_hRequest = NULL;
		::InternetCloseHandle(m_hConnect);
		m_hConnect = NULL;
		::InternetCloseHandle(m_hOpen);
		m_hOpen = NULL;
		return false;
	}

	if (HTTP_STATUS_OK != dwStatus)
	{
		ERROR_LOG() << "HttpQueryInfo failed. (" << GetLastError() << ")";
		::InternetCloseHandle(m_hRequest);
		m_hRequest = NULL;
		::InternetCloseHandle(m_hConnect);
		m_hConnect = NULL;
		::InternetCloseHandle(m_hOpen);
		m_hOpen = NULL;
		return false;
	}

	// ��ȡ�ļ���С
	unsigned long long dwTotalSize = 0; // ���ط�����ļ���С
	char buffer[MAX_PATH] = {0};
	DWORD dwLengthSizeBuffer = sizeof(buffer);
	// ��ѯ������ļ���С
	bRet = ::HttpQueryInfo(m_hRequest, HTTP_QUERY_CONTENT_LENGTH, buffer, &dwLengthSizeBuffer, NULL); //lint !e838
	// �õ����Ĵ�С
	dwTotalSize = (unsigned long long)_atoi64(buffer);  //lint !e838

	// ��ȡ�ļ���
	std::string strFileName;
	std::string strFilePath = strDownloadPath;
	memset(buffer, 0, MAX_PATH);
	dwLengthSizeBuffer = sizeof(buffer);
	// ��ѯ������ļ���С
	bRet = ::HttpQueryInfo(m_hRequest, HTTP_QUERY_CONTENT_DISPOSITION, buffer, &dwLengthSizeBuffer, NULL); //lint !e838
	if (bRet)
	{
		strFileName = buffer;
		strFileName = strFileName.substr(strFileName.find("filename=")+strlen("filename="), strFileName.find(".zip")+strlen(".zip"));	
		strFilePath.append("\\");
		strFilePath.append(strFileName);
	}
	else
	{
		strFileName = strDownloadUrl.substr(strDownloadUrl.rfind("/")+1, std::string::npos);
		strFilePath.append("\\");
		strFilePath.append(strFileName);
	}

	// �����ļ�
	DWORD dwRead = 0;
	unsigned long long dwCurTotal = 0;
	char *pBuffer = new char[MAXRECVBUFF];
	memset(pBuffer, 0, MAXRECVBUFF);
	try
	{
		std::string strTempName = strFilePath + ".tmp";
		//write to the Download dir
		m_fout = fopen(strTempName.c_str(), "wb");
		if (NULL == m_fout)
		{
			ERROR_LOG() << "fopen failed. (" << GetLastError() << ")";
			::InternetCloseHandle(m_hRequest);
			m_hRequest = NULL;
			::InternetCloseHandle(m_hConnect);
			m_hConnect = NULL;
			::InternetCloseHandle(m_hOpen);
			m_hOpen = NULL;

			delete []pBuffer;
			pBuffer = NULL;
			return false;
		}

		do 
		{
			if (!::InternetReadFile(m_hRequest, pBuffer, MAXRECVBUFF-1, &dwRead))
			{
				ERROR_LOG() << "InternetReadFile failed.";
				WARN_LOG() << "Server file size : " << dwTotalSize << "bytes, Download : " << dwCurTotal << "bytes";

				::InternetCloseHandle(m_hRequest);
				m_hRequest = NULL;
				::InternetCloseHandle(m_hConnect);
				m_hConnect = NULL;
				::InternetCloseHandle(m_hOpen);
				m_hOpen = NULL;

				delete []pBuffer;
				pBuffer = NULL;

				fclose(m_fout);
				m_fout = NULL;
				(void)::DeleteFile(strTempName.c_str());
				return false;
			}
			if (NULL == m_fout && dwRead > 0)
			{
				if (NULL != m_hRequest)
				{
					::InternetCloseHandle(m_hRequest);
					m_hRequest = NULL;
				}
				if (NULL != m_hConnect)
				{
					::InternetCloseHandle(m_hConnect);
					m_hConnect = NULL;
				}
				if (NULL != m_hOpen)
				{
					::InternetCloseHandle(m_hOpen);
					m_hOpen = NULL;
				}

				delete []pBuffer;
				pBuffer = NULL;
				(void)::DeleteFile(strTempName.c_str());
				return false;
			}

			pBuffer[dwRead] = 0;
			fwrite(pBuffer, sizeof(char), dwRead, m_fout);
			memset(pBuffer, 0, MAXRECVBUFF);
			dwCurTotal += dwRead;
			//DEBUG_LOG() << strFileName << " Download : " << (dwCurTotal*100)/dwTotalSize << "%";
		} while (dwRead > 0);

		delete []pBuffer;
		pBuffer = NULL;
		fclose(m_fout);
		m_fout = NULL;
		DEBUG_LOG() << "Server file size : " << dwTotalSize << "bytes, Download : " << dwCurTotal << "bytes";

		// ������ɺ��޸��ļ���
		if (dwTotalSize == dwCurTotal)
		{
			rename(strTempName.c_str(), strFilePath.c_str());
		}
		else
		{
			::InternetCloseHandle(m_hRequest);
			m_hRequest = NULL;
			::InternetCloseHandle(m_hConnect);
			m_hConnect = NULL;
			::InternetCloseHandle(m_hOpen);
			m_hOpen = NULL;
			return false;	
		}
	}
	catch( ... )
	{
		::InternetCloseHandle(m_hRequest);
		m_hRequest = NULL;
		::InternetCloseHandle(m_hConnect);
		m_hConnect = NULL;
		::InternetCloseHandle(m_hOpen);
		m_hOpen = NULL;

		delete []pBuffer;
		pBuffer = NULL;

		if (NULL != m_fout)
		{
			fclose(m_fout);
			m_fout = NULL;
		}

		ERROR_LOG() << "Download file exception.";
		return false;//lint !e438
	}

	::InternetCloseHandle(m_hRequest);
	m_hRequest = NULL;
	::InternetCloseHandle(m_hConnect);
	m_hConnect = NULL;
	::InternetCloseHandle(m_hOpen);
	m_hOpen = NULL;

	DEBUG_LOG() << "--- LEAVE";
	return true;	
}
