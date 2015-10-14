
#include <iostream>
#include <stdlib.h>
#include "eSDKTool.h"
#include "eSDKLog.h"
#include "ServiceFactory.h"
#include "eSDKSSO.h"
#include "eSDKClientPlatformExecute.h"
#include "ProductSDK.h"

#pragma comment(lib, "UpdateVersion.lib")
#pragma comment(lib, "eSDKTool.lib")

int g_iLogInstanceIndex = 0;

eSDKClientPlatform::eSDKClientPlatform()
{

}

eSDKClientPlatform::~eSDKClientPlatform()
{

}

eSDKClientPlatform* eSDKClientPlatform::getInstance()
{
	return dynamic_cast<eSDKClientPlatform*>(eSDKClientPlatformExecute::Instance());
}

void eSDKClientPlatform::ReleaseInstance()
{
	eSDKClientPlatformExecute::Destroy();
}

eSDKClientPlatformExecute* eSDKClientPlatformExecute::m_eSDKClientPlatform = NULL;

eSDKClientPlatformExecute::eSDKClientPlatformExecute()
	:m_eSDKSSO(NULL)
	,m_UpdateVersion(NULL)
	,hDll(NULL)
	,m_pMsgCallBack(NULL)
{

}

eSDKClientPlatformExecute::~eSDKClientPlatformExecute()
{
	try
	{
		if (NULL != m_eSDKSSO)
		{
			ReleaseClass pReleaseInstance = ServiceFactory::ReleaseClassByName("eSDKSSOExecute");
			if (NULL == pReleaseInstance)
			{
				ERROR_LOG() << "Release eSDKSSO fail";
				m_eSDKSSO = NULL;
			}
			else
			{
				(*pReleaseInstance)();
				m_eSDKSSO = NULL;
			}		
		}
		
		if (NULL != m_UpdateVersion)
		{
			UpdateVersion::ReleaseUpdateVersion();
			m_UpdateVersion = NULL;
		}
		
		if (NULL != hDll)
		{
			FreeLibrary(hDll);
			hDll = NULL;
		}

		m_pMsgCallBack = NULL;
		ServiceFactory::DestroyClass();
	}
	catch (...)
	{
		m_eSDKSSO = NULL;
		m_UpdateVersion = NULL;
		hDll = NULL;
		m_pMsgCallBack = NULL;
	}	
}

eSDKClientPlatformExecute* eSDKClientPlatformExecute::Instance()
{
	if (NULL == m_eSDKClientPlatform)
	{
		m_eSDKClientPlatform = new eSDKClientPlatformExecute;
	}

	return m_eSDKClientPlatform;
}

void eSDKClientPlatformExecute::Destroy()
{
	if (NULL != m_eSDKClientPlatform)
	{
		delete m_eSDKClientPlatform;
		m_eSDKClientPlatform = NULL;
	}
}

int eSDKClientPlatformExecute::UpdateService()
{
	DEBUG_LOG() << "--- ENTRY";
	std::string Path;
	eSDKTool::getModulePath("eSDKClientPlatform.dll", Path);
	
	std::string eSDKDirect = Path + "\\";
	std::string eSDKIniFile = eSDKDirect + ESDKSSO_INI_FILE;
	
	std::map<std::string, std::string> sIniFiles;
	//std::vector<std::string> sIniFiles;
	std::vector<std::string> sDllFiles;	
	
	Path.append("\\SDK\\");
	DEBUG_LOG() << "PATH=" << Path;

	//获取ESDKClient动态库目录下所有产品SDK的ini文件和dll文件
	eSDKTool::FindFiles(sIniFiles, sDllFiles, Path);

	//sIniFiles.insert(std::pair<std::string, std::string>(eSDKIniFile, eSDKDirect));
	
	m_vecClassName.clear();
	m_vecVersion.clear();
	m_vecServiceName.clear();

	//打开每一个需要加载的产品ini文件，获取相应类名
	std::map<std::string, std::string>::iterator iter = sIniFiles.begin();
	std::map<std::string, std::string>::iterator itEnd = sIniFiles.end();
	for(; iter != itEnd; iter++)
	{
		const int LENGTH = 32;
		char acClassName[LENGTH] = {0};
		char acVersion[LENGTH] = {0};
		std::string strFileName = iter->first;
		DWORD dwNum0 = ::GetPrivateProfileStringA("class","name","",acClassName,LENGTH-1,strFileName.c_str());
		DWORD dwNum1 = ::GetPrivateProfileStringA("class","version","",acVersion,LENGTH-1,strFileName.c_str());
		if ((0 == dwNum0) || (0 == dwNum1))
		{
			//ERROR_LOG() << "Read version information fail, path = " << (*iter);
			continue;
		}
		
		DEBUG_LOG() << "Read version information success, Service = " << acClassName << ", version = " << acVersion;
		m_vecClassName.push_back(acClassName);
		m_vecVersion.push_back(acVersion);
		m_vecServiceName.push_back(acClassName);
	}

	const int LENGTH = 32;
	char acClassName[LENGTH] = {0};
	char acVersion[LENGTH] = {0};
	DWORD dwNum0 = ::GetPrivateProfileStringA("class","name","",acClassName,LENGTH-1,eSDKIniFile.c_str());
	DWORD dwNum1 = ::GetPrivateProfileStringA("class","version","",acVersion,LENGTH-1,eSDKIniFile.c_str());
	if ((0 != dwNum0) && (0 != dwNum1))
	{
		m_vecClassName.push_back(acClassName);
		m_vecVersion.push_back(acVersion);
		DEBUG_LOG() << "Read version information success, Service = " << acClassName << ", version = " << acVersion;
	}
	
	m_UpdateVersion = UpdateVersion::GetUpdateVersion();
	if (NULL == m_UpdateVersion)
	{
		ERROR_LOG() << "Instance Update component fail!!!";
		return ESDKCLIENT_PLATFORM_FAIL;
	}

	if (!m_UpdateVersion->Init(m_vecClassName, m_vecVersion))
	{
		ERROR_LOG() << "Initial Update component fail!!!";
		return ESDKCLIENT_PLATFORM_FAIL;
	}

	if (!m_UpdateVersion->SetMessageCallBack(m_pMsgCallBack))
	{
		ERROR_LOG() << "Initial Update SetMessageCallBack fail!!!";
		return ESDKCLIENT_PLATFORM_FAIL;
	}

	if (!m_UpdateVersion->Start())
	{
		ERROR_LOG() << "Start update fail!!!";
		return ESDKCLIENT_PLATFORM_FAIL;
	}

	DEBUG_LOG() << "Update successful";
	DEBUG_LOG() << "--- LEAVE";
	return ESDKCLIENT_PLATFORM_SUCCESS;

}

int eSDKClientPlatformExecute::init()
{
	eSDKLog *pLog = eSDKLog::getInstance();
	if (NULL == pLog)
	{
		return ESDKCLIENT_PLATFORM_FAIL;
	}
	int iRet = pLog->init("eSDKClientPlatform", g_iLogInstanceIndex);
	if (ESDKLOG_SUCCESS != iRet)
	{
		return ESDKCLIENT_PLATFORM_FAIL;
	}
	DEBUG_LOG() << "--- ENTRY";
	
	iRet = UpdateService();
	DEBUG_LOG() << "Update finish, ret = " << iRet;
	

	std::string Path;
	eSDKTool::getModulePath("eSDKClientPlatform.dll", Path);
	std::string eSDKDllFile = Path + "\\" + ESDKSSO_DLL_FILE;
	hDll = LoadLibrary(eSDKDllFile.c_str());
	DWORD tempErr = GetLastError();
	DEBUG_LOG() << "Load dll result = " << tempErr;
	if (NULL == hDll)
	{
		ERROR_LOG() << "Load DLL fail, path = " << eSDKDllFile;
		return ESDKCLIENT_PLATFORM_FAIL;
	}
	
	DEBUG_LOG() << "Load DLL success, file = " << eSDKDllFile;

	CreateClass pInstance = ServiceFactory::GetClassByName("eSDKSSOExecute");
	if (NULL == pInstance)
	{
		ERROR_LOG() << "Not register eSDKSSOExecute on eSDKClient platform!!!";
		return ESDKCLIENT_PLATFORM_FAIL;
	}

	m_eSDKSSO = (eSDKSSO *)(*pInstance)();
	if (NULL == m_eSDKSSO)
	{
		ERROR_LOG() << "Instance eSDKSSOExecute fail!!!";
		return ESDKCLIENT_PLATFORM_FAIL;
	}
	
	iRet = m_eSDKSSO->init();
	if (ESDKSSO_SUCCESS != iRet)
	{
		ERROR_LOG() << "Initial eSDKSSOExecute fail";
		return ESDKCLIENT_PLATFORM_FAIL;
	}
	
	DEBUG_LOG() << "Initial eSDKSSO success";

	std::vector<std::string>::iterator iter_b = m_vecServiceName.begin();
	std::vector<std::string>::iterator iter_e = m_vecServiceName.end();
	for (; iter_b != iter_e; iter_b++)
	{
		//通过类名，从类工厂里获取创建类对象实例的方法
		pInstance = ServiceFactory::GetClassByName(*iter_b);//lint !e611
		if (NULL == pInstance)
		{
			ERROR_LOG() << "Not register PDU SDK on eSDKClient platform, SDK = " << (*iter_b) << "!!!";
			break;
		}		
		//实例化业务产品
		ProductSDK *pPDUSDK = (ProductSDK *)(*pInstance)();
		if (NULL == pPDUSDK)
		{
			ERROR_LOG() << "Instance PDU SDK fail, SDK = " << (*iter_b) << "!!!";
			break;
		}

		(void)m_vecClassInstance.insert(std::pair<std::string, ProductSDK*>(*iter_b, pPDUSDK));
	}

	if (iter_b != iter_e)
	{
		//销毁已经创建成功的业务实例
		ClassInstanceMap::iterator iterTmp = m_vecClassInstance.begin();
		ClassInstanceMap::iterator itEndTmp = m_vecClassInstance.end();
		for(; iterTmp != itEndTmp; iterTmp++)
		{
			ReleaseClass pReleaseInstance = ServiceFactory::ReleaseClassByName(iterTmp->first);
			if (NULL == pReleaseInstance)
			{
				ERROR_LOG() << "Unload PDU SDK fail, SDK = " << iterTmp->first;
				continue;
			}

			(*pReleaseInstance)();
			DEBUG_LOG() << "Unload PDU SDK success, SDK = " << (iterTmp->first);
		}

		m_vecClassInstance.clear();

		return ESDKCLIENT_PLATFORM_FAIL;
	}
	DEBUG_LOG() << "--- LEAVE";
	return ESDKCLIENT_PLATFORM_SUCCESS;	
}

int eSDKClientPlatformExecute::login(const std::string &token)
{
	DEBUG_LOG() << "--- ENTRY";
	if (NULL == m_eSDKSSO)
	{
		ERROR_LOG() << "Bad pointer";
		return ESDKCLIENT_PLATFORM_FAIL;
	}

	int iRet = m_eSDKSSO->login(token);
	if (ESDKSSO_SUCCESS != iRet)
	{
		ERROR_LOG() << "Login eSDKClient platform fail";
		return ESDKCLIENT_PLATFORM_FAIL;
	}
		
	DEBUG_LOG() << "Login eSDKClient platform success";
	DEBUG_LOG() << "--- LEAVE";
	return ESDKCLIENT_PLATFORM_SUCCESS;	
}

int eSDKClientPlatformExecute::login(const std::string &name, const std::string &password, int type)
{
	DEBUG_LOG() << "--- ENTRY";
	if (NULL == m_eSDKSSO)
	{
		ERROR_LOG() << "Bad pointer";
		return ESDKCLIENT_PLATFORM_FAIL;
	}

	int iRet = m_eSDKSSO->login(name, password, type);
	if (ESDKSSO_SUCCESS != iRet)
	{
		ERROR_LOG() << "Login eSDKClient platform fail";
		return ESDKCLIENT_PLATFORM_FAIL;
	}

	DEBUG_LOG() << "Login eSDKClient platform success";
	DEBUG_LOG() << "--- LEAVE";
	return ESDKCLIENT_PLATFORM_SUCCESS;	
}

int eSDKClientPlatformExecute::logout()
{
	DEBUG_LOG() << "--- ENTRY";
	if (NULL == m_eSDKSSO)
	{
		ERROR_LOG() << "Bad pointer";
		return ESDKCLIENT_PLATFORM_FAIL;
	}
	
	int iRet = m_eSDKSSO->logout();
	if (ESDKSSO_SUCCESS != iRet)
	{
		ERROR_LOG() << "Logout eSDKClient platform fail";
		return ESDKCLIENT_PLATFORM_FAIL;
	}

	DEBUG_LOG() << "Logout eSDKClient platform success";
	DEBUG_LOG() << "--- LEAVE";

	return ESDKCLIENT_PLATFORM_SUCCESS;
}

int eSDKClientPlatformExecute::setConfig(const std::string &param)
{
	DEBUG_LOG() << "--- ENTRY";
	if (NULL == m_eSDKSSO)
	{
		ERROR_LOG() << "Bad pointer";
		return ESDKCLIENT_PLATFORM_FAIL;
	}

	int iRet =  m_eSDKSSO->setConfig(param);
	if (ESDKSSO_SUCCESS != iRet)
	{
		ERROR_LOG() << "Set eSDK SSO Server Url fail";
		return ESDKCLIENT_PLATFORM_FAIL;
	}

	DEBUG_LOG() << "Set eSDK SSO Server Url success";
	DEBUG_LOG() << "--- LEAVE";

	return ESDKCLIENT_PLATFORM_SUCCESS;
}

int eSDKClientPlatformExecute::setHostIP(const std::string &ip)
{
	DEBUG_LOG() << "--- ENTRY";
	if (NULL == m_eSDKSSO)
	{
		ERROR_LOG() << "Bad pointer";
		return ESDKCLIENT_PLATFORM_FAIL;
	}

	int iRet = m_eSDKSSO->setHostIP(ip);
	if (ESDKSSO_SUCCESS != iRet)
	{
		ERROR_LOG() << "Set host ip fail";
		return ESDKCLIENT_PLATFORM_FAIL;
	}

	DEBUG_LOG() << "Set host ip success";
	DEBUG_LOG() << "--- LEAVE";
	return ESDKCLIENT_PLATFORM_SUCCESS;
}

int eSDKClientPlatformExecute::uninit()
{
	DEBUG_LOG() << "--- ENTRY";
	if (NULL != m_eSDKSSO)
	{
		int iRet = m_eSDKSSO->uninit();
		
		ReleaseClass pReleaseInstance = ServiceFactory::ReleaseClassByName("eSDKSSOExecute");
		if (NULL == pReleaseInstance)
		{
			ERROR_LOG() << "Release eSDKSSO fail";
		}
		else
		{
			(*pReleaseInstance)();
			m_eSDKSSO = NULL;
			DEBUG_LOG() << "Uninitial eSDKSSO finish, ret = " << iRet;
		}		
	}
	
	if (NULL != m_UpdateVersion)
	{
		m_UpdateVersion->UnInit();

		UpdateVersion::ReleaseUpdateVersion();
		m_UpdateVersion = NULL;
	}
	
	if (NULL != hDll)
	{
		FreeLibrary(hDll);
		hDll = NULL;
	}

	ServiceFactory::DestroyClass();

	DEBUG_LOG() << "Uninitial eSDKClient platform success";
	DEBUG_LOG() << "--- LEAVE";
	eSDKLog::destroyInstance();

	return ESDKCLIENT_PLATFORM_SUCCESS;
}

int eSDKClientPlatformExecute::setUpdateServer(const std::string &UpdateServer)
{
	DEBUG_LOG() << "--- ENTRY";
	if (NULL == m_UpdateVersion)
	{
		m_UpdateVersion = UpdateVersion::GetUpdateVersion();
		if (NULL == m_UpdateVersion)
		{
			ERROR_LOG() << "Instance Update component fail";
			return ESDKCLIENT_PLATFORM_FAIL;
		}
	}

	if (!m_UpdateVersion->SetServerUrl(UpdateServer))
	{
		ERROR_LOG() << "Set Update server url fail";
		return ESDKCLIENT_PLATFORM_FAIL;
	}

	DEBUG_LOG() << "Set Update server url success";
	DEBUG_LOG() << "--- LEAVE";
	return ESDKCLIENT_PLATFORM_SUCCESS;
}


bool eSDKClientPlatformExecute::SetMessageCallBack(eSDKMessageCallBack fpMsgCB)
{
	DEBUG_LOG() << "--- ENTRY";
	m_pMsgCallBack = fpMsgCB;

	DEBUG_LOG() << "Set update message callback success";
	DEBUG_LOG() << "--- LEAVE";
	return true;
}

ProductSDK* eSDKClientPlatformExecute::getServiceByName(const std::string& strServiceName)
{
	DEBUG_LOG() << "--- ENTRY";
	
	if (strServiceName.empty())
	{
		ERROR_LOG() << "Service name is empty!!!";
		return NULL;
	}

	ClassInstanceMap::iterator iter = m_vecClassInstance.find(strServiceName);
	if (iter == m_vecClassInstance.end())
	{
		ERROR_LOG() << "Not register service on eSDKClient platform, service = " << strServiceName << "!!!";
		return NULL;
	}

	DEBUG_LOG() << "--- LEAVE";
	return iter->second;

}

HINSTANCE eSDKClientPlatformExecute::getServiceHandleByName(const std::string& strServiceName)
{
	DEBUG_LOG() << "--- ENTRY";
	
	if (NULL == m_eSDKSSO)
	{
		ERROR_LOG() << "Bad pointer";
		return NULL;
	}

	HINSTANCE hTmpHandle = (HINSTANCE)m_eSDKSSO->getServiceHandleByName(strServiceName);

	DEBUG_LOG() << "--- LEAVE";
	return hTmpHandle;

}

