#include <algorithm>
#include <iostream>
#include <stdlib.h>
#include "eSDKSSOExecute.h"
#include "ProductSDK.h"
#include "ServiceFactory.h"
#include "eSDKLog.h"
#include "eSDKTool.h"
#include "SSOAdapter.h"
#include "TokenManager.h"

#pragma comment(lib, "SSOAdapter.lib")
#pragma comment(lib, "eSDKTool.lib")

IMPLEMENT_RUNTIME(eSDKSSOExecute, eSDKSSOExecute)

int g_iLogInstanceIndex = 0;

////////////////////////////////////////////////////
eSDKSSO::eSDKSSO()
{

}

eSDKSSO::~eSDKSSO()
{

}

eSDKSSO* eSDKSSO::getInstance(void)
{
	return dynamic_cast<eSDKSSO*>(eSDKSSOExecute::CreateInstance());
}

void eSDKSSO::ReleaseInstance(void)
{
	eSDKSSOExecute::DestroyInstance();
}

////////////////////////////////////////////////////

eSDKSSOExecute* eSDKSSOExecute::m_eSDKSSO = NULL;

eSDKSSOExecute* eSDKSSOExecute::CreateInstance()
{
	if (NULL == m_eSDKSSO)
	{
		m_eSDKSSO = new eSDKSSOExecute;
	}

	return m_eSDKSSO;
}

void eSDKSSOExecute::DestroyInstance()
{
	if (NULL != m_eSDKSSO)
	{
		delete m_eSDKSSO;
		m_eSDKSSO = NULL;
	}
}

eSDKSSOExecute::eSDKSSOExecute(void)
	:bInitFlag(false)
{
	
}

eSDKSSOExecute::~eSDKSSOExecute(void)
{
	
}

void eSDKSSOExecute::loadPDUSDK()
{
	DEBUG_LOG() << "--- ENTRY";
	//��ȡeSDKSSO��̬���ļ���Ŀ¼
	std::string Path;
	eSDKTool::getModulePath("eSDKSSO.dll", Path);
	Path.append("\\SDK\\");
	DEBUG_LOG() << "PATH=" << Path;
	
	std::map<std::string, std::string> sIniFiles;
	std::vector<std::string> sDllFiles;

	//��ȡeSDKSSO��̬��Ŀ¼�����в�ƷSDK��ini�ļ���dll�ļ�
	eSDKTool::FindFiles(sIniFiles, sDllFiles, Path);
	
	
	//��ÿһ����Ҫ���صĲ�Ʒini�ļ�����ȡ��Ӧ����
	std::map<std::string, std::string>::iterator iter = sIniFiles.begin();
	std::map<std::string, std::string>::iterator itEnd = sIniFiles.end();
	for(; iter != itEnd; iter++)
	{
		const int LENGTH = 32;
		char acClassName[LENGTH] = {0};
		std::string strFileName = iter->first;
		std::string strDirect = iter->second;		
		DEBUG_LOG() << "File = " << strFileName;
		DEBUG_LOG() << "Directory = " << strDirect;
		DWORD dwNum = ::GetPrivateProfileStringA("class","name","",acClassName,LENGTH-1,strFileName.c_str());
		if (0 != dwNum)
		{
			DEBUG_LOG() << "Read PDU SDK success, SDK = " << acClassName;
			
			std::string strLoadDll = strDirect + acClassName;
			strLoadDll.append(".dll");
			//lint -e864
			//�����������������Ĳ�ƷSDK��̬��
			std::vector<std::string>::iterator itFind = std::find(sDllFiles.begin(), sDllFiles.end(), strLoadDll);
			if (itFind == sDllFiles.end())
			{
				ERROR_LOG() << "PDU SDK file not exist, file = " << strLoadDll;
				continue;
			}
			//lint +e864
			//���ó�������Ŀ¼Ϊ��ƷSDKĿ¼������̬���ز�ƷSDK��ʧ��
			if (!SetCurrentDirectory(strDirect.c_str()))
			{
				ERROR_LOG() << "Set current directory fail, path = " << strDirect;
				continue;
			}
			//��̬���ز�ƷSDK
			HINSTANCE hDll = LoadLibrary((*itFind).c_str());
			DWORD iError = GetLastError();
			DEBUG_LOG() << "Load dll result = " << iError;
			if (NULL == hDll)
			{
				ERROR_LOG() << "Load PDU SDK DLL fail, file = " << (*itFind) << "!!!";
				continue;
			}

			DEBUG_LOG() << "Load PDU SDK DLL success, file = " << (*itFind);
			m_vecClassName.push_back(acClassName);
			(void)m_vecDllHandle.insert(std::pair<std::string, HINSTANCE>(acClassName, hDll));
			(void)m_ServiceWorkDirectMap.insert(std::pair<std::string, std::string>(acClassName, strDirect));
			//������ƷSDK֧�ֵĵ�¼��ʽ��0���û��������¼��1��token��¼
			char acLoginType[LENGTH] = {0};
			dwNum = ::GetPrivateProfileStringA("class","login","",acLoginType,LENGTH-1,strFileName.c_str());
			if (0 != dwNum)
			{
				ESDKSSO_PDU_LOGIN_TYPE_E eLoginValue = static_cast<ESDKSSO_PDU_LOGIN_TYPE_E>(atoi(acLoginType));
				DEBUG_LOG() << "Read PDU SDK Login method success, method = " << eLoginValue;
				
				(void)m_vecPDULoginType.insert(std::pair<std::string, ESDKSSO_PDU_LOGIN_TYPE_E>(acClassName, eLoginValue));
			}
			else
			{
				WARN_LOG() << "Read PDU SDK Login method fail, use default value = " << ESDKSSO_SERVICE_PASSWORD_LOGIN;
				(void)m_vecPDULoginType.insert(std::pair<std::string, ESDKSSO_PDU_LOGIN_TYPE_E>(acClassName, ESDKSSO_SERVICE_PASSWORD_LOGIN));
			}			
		}		
	}
	//���ó�������Ŀ¼ΪISV������Ŀ¼
	SetCurrentDirectory(m_CurrentDirect.c_str());	
	DEBUG_LOG() << "--- LEAVE";
	return;
}

int eSDKSSOExecute::init()
{
	if (bInitFlag)
	{
		return ESDKSSO_SUCCESS;
	}

	eSDKLog *pLog = eSDKLog::getInstance();
	if (NULL == pLog)
	{
		return ESDKSSO_FAIL;
	}
	int iRet = pLog->init("eSDKSSO", g_iLogInstanceIndex);
	if (ESDKLOG_SUCCESS != iRet)
	{
		return ESDKSSO_FAIL;
	}	
	DEBUG_LOG() << "--- ENTRY";
	
	//��ȡ���������Ŀ¼
	const int iDirectLen = 256;
	char acCurrentDirect[iDirectLen] = {0};
	if (0 == GetCurrentDirectory(iDirectLen, acCurrentDirect))
	{
		ERROR_LOG() << "Get current directory fail!!!";
		return ESDKSSO_FAIL;
	}
	
	m_CurrentDirect = acCurrentDirect;

	loadPDUSDK();

	int iRet1 = ESDKSSO_FAIL;
	//���÷������ʵ�ֶ�̬���������
	std::vector<std::string>::iterator iter = m_vecClassName.begin();
	std::vector<std::string>::iterator itEnd = m_vecClassName.end();
	for(; iter != itEnd; iter++)
	{
		//ͨ�����������๤�����ȡ���������ʵ���ķ���
		CreateClass pInstance = ServiceFactory::GetClassByName(*iter);//lint !e611
		if (NULL == pInstance)
		{
			ERROR_LOG() << "Not register PDU SDK on eSDKClient platform, SDK = " << (*iter) << "!!!";
			break;
		}		
		//ʵ����ҵ���Ʒ
		ProductSDK *pPDUSDK = (ProductSDK *)(*pInstance)();
		if (NULL == pPDUSDK)
		{
			ERROR_LOG() << "Instance PDU SDK fail, SDK = " << (*iter) << "!!!";
			break;
		}
		//���ó�������Ŀ¼Ϊ��ƷSDKĿ¼�������ƷSDKҵ���ʧ��
		iRet1 = setWorkDirctoryByClassName(*iter);
		if (ESDKSSO_SUCCESS != iRet1)
		{
			ERROR_LOG() << "Set PDU SDK directory fail, SDK = " << (*iter) << "!!!";
			break;
		}
		
		iRet1 = pPDUSDK->Init();
		if (ESDKSSO_SUCCESS != iRet1)
		{			
			ERROR_LOG() << "Init PDU SDK fail, SDK = " << (*iter) << "!!!";
			break;
		}
		DEBUG_LOG() << "Init PDU SDK success, SDK = " << (*iter);
		(void)m_vecClassInstance.insert(std::pair<std::string, ProductSDK*>(*iter, pPDUSDK));
	}

	if (iter != itEnd)
	{
		//�����Ѿ������ɹ���ҵ��ʵ��
		ClassInstanceMap::iterator iterTmp = m_vecClassInstance.begin();
		ClassInstanceMap::iterator itEndTmp = m_vecClassInstance.end();
		for(; iterTmp != itEndTmp; iterTmp++)
		{
			ProductSDK *pPDUSDK = iterTmp->second;
			if (NULL == pPDUSDK)
			{
				ERROR_LOG() << "Not register PDU SDK on eSDKClient platform, SDK = " << iterTmp->first;
				continue;
			}
			//���ó�������Ŀ¼Ϊ��ƷSDKĿ¼�������ƷSDKҵ���ʧ��
			iRet1 = setWorkDirctoryByClassName(iterTmp->first);
			if (ESDKSSO_SUCCESS != iRet1)
			{
				ERROR_LOG() << "Set PDU SDK directory fail, SDK = " << iterTmp->first;
				continue;
			}
			//ȥ��ʼ����ƷSDK
			if (0 != pPDUSDK->UnInit())
			{
				ERROR_LOG() << "PDU SDK Uninit fail, SDK = " << iterTmp->first;
				continue;
			}

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

		return ESDKSSO_FAIL;
	}
	//���ó�������Ŀ¼ΪISV������Ŀ¼
	SetCurrentDirectory(m_CurrentDirect.c_str());
	
	TokenManager *pTokenMgr = TokenManager::getInstance();
	if (NULL == pTokenMgr)
	{
		ERROR_LOG() << "Instance token manager fail.";
		return ESDKSSO_FAIL;
	}

	if (!pTokenMgr->init())
	{
		ERROR_LOG() << "Initial token manager fail.";
		return ESDKSSO_FAIL;
	}
	
	bInitFlag = true;
	DEBUG_LOG() << "Init eSDKSSO success";
	DEBUG_LOG() << "--- LEAVE";
	return ESDKSSO_SUCCESS;
}

int eSDKSSOExecute::uninit()
{
	DEBUG_LOG() << "--- ENTRY";

	if (!bInitFlag)
	{
		ERROR_LOG() << "Not initial eSDKSSO.";
		return ESDKSSO_FAIL;
	}
	
	//�ͷų�ʼ�������������������
	ClassInstanceMap::iterator iter = m_vecClassInstance.begin();
	ClassInstanceMap::iterator itEnd = m_vecClassInstance.end();
	for(; iter != itEnd; iter++)
	{
		ProductSDK *pPDUSDK = iter->second;
		if (NULL == pPDUSDK)
		{
			ERROR_LOG() << "Not register PDU SDK on eSDKClient platform, SDK = " << iter->first;
			continue;
		}
		
		int iRet = setWorkDirctoryByClassName(iter->first);
		if (ESDKSSO_SUCCESS != iRet)
		{
			ERROR_LOG() << "Set PDU SDK directory fail, SDK = " << iter->first;
			continue;
		}

		if (0 != pPDUSDK->UnInit())
		{
			ERROR_LOG() << "PDU SDK Uninit fail, SDK = " << iter->first;
			continue;
		}

		ReleaseClass pReleaseInstance = ServiceFactory::ReleaseClassByName(iter->first);
		if (NULL == pReleaseInstance)
		{
			ERROR_LOG() << "Unload PDU SDK fail, SDK = " << iter->first;
			continue;
		}

		(*pReleaseInstance)();		
		DEBUG_LOG() << "Unload PDU SDK success, SDK = " << (iter->first);
	}	

	SetCurrentDirectory(m_CurrentDirect.c_str());

	//�رռ��صĲ�ƷSDK��dll��
	std::map<std::string, HINSTANCE>::iterator iterDll = m_vecDllHandle.begin();
	std::map<std::string, HINSTANCE>::iterator itEndDll = m_vecDllHandle.end();
	for (; iterDll != itEndDll; iterDll++)
	{
		FreeLibrary(iterDll->second);
	}

	m_vecDllHandle.clear();
	m_vecClassName.clear();
	m_vecClassInstance.clear();
	m_ServiceWorkDirectMap.clear();
	m_CurrentDirect.clear();

	TokenManager *pTokenMgr = TokenManager::getInstance();
	if (NULL == pTokenMgr)
	{
		ERROR_LOG() << "Instance token manager fail.";
		return ESDKSSO_FAIL;
	}

	if (!pTokenMgr->uninit())
	{
		ERROR_LOG() << "Uninitial token manager fail.";
		return ESDKSSO_FAIL;
	}
	
	TokenManager::ReleaseInstance();	
	DEBUG_LOG() << "Uninit eSDKSSO success";
	DEBUG_LOG() << "--- LEAVE";	
	eSDKLog::destroyInstance();
	bInitFlag = false;
	return ESDKSSO_SUCCESS;
}

int eSDKSSOExecute::login(const std::string &token)
{
	DEBUG_LOG() << "--- ENTRY";
	
	//������token�ĺϷ���
	if (0 == token.length())
	{
		ERROR_LOG() << "Invalid parameter";
		return ESDKSSO_FAIL;
	}

	LoginTypeMap::iterator iter = m_vecPDULoginType.begin();
	LoginTypeMap::iterator itEnd = m_vecPDULoginType.end();
	for(; iter != itEnd; iter++)
	{
		switch(iter->second)
		{
		case ESDKSSO_SERVICE_PASSWORD_LOGIN:
			{
				std::string strName("");
				std::string strPassword("");
				std::string strPDUName = iter->first;
				const int LENGTH = 128;
				char acName[LENGTH] = {0};
				char acPassword[LENGTH] = {0};

				//����������֤����ȡ��Ʒ���û���������
				int iRet = SSOAuthenticate(token.c_str(),strPDUName.c_str(), acName, acPassword, LENGTH);
				//int iRet = ESDKSSO::getSharedInstance().SSOAuthenticate(token, strPDUName, strName, strPassword);
				if (SSOADAPTER_SUCCESS != iRet)
				{
					ERROR_LOG() << " Authenticate PDU SDK fail, SDK = " << iter->first << "!!!"; 
					return ESDKSSO_FAIL;
				}
				
				strName = acName;
				strPassword = acPassword;
				
				//ʹ���û��������¼��Ʒ
				ClassInstanceMap::iterator nPos = m_vecClassInstance.find(iter->first);
				if(nPos != m_vecClassInstance.end())
				{
					ProductSDK *pPDUSDK = nPos->second;
					if (NULL == pPDUSDK)
					{
						ERROR_LOG() << "PDU SDK not exist, SDK = " << (iter->first) << "!!!";
						return ESDKSSO_FAIL;
					}

					iRet = setWorkDirctoryByClassName(iter->first);
					if (ESDKSSO_SUCCESS != iRet)
					{
						ERROR_LOG() << "Set PDU SDK directory fail, SDK = " << (iter->first) << "!!!";
						return ESDKSSO_FAIL;
					}
					
					iRet = pPDUSDK->Login(strName,strPassword);
					if (ESDKSSO_SUCCESS != iRet)
					{
						ERROR_LOG() << "Login PDU SDK fail, SDK = " << (iter->first) << "!!!"; 
						return ESDKSSO_INTERNAL_ERROR;
					}

					DEBUG_LOG() << "Login PDU SDK success, SDK = " << (iter->first);
				}
				else
				{
					ERROR_LOG() << "PDU SDK not exist, SDK = " << (iter->first) << "!!!";
					return ESDKSSO_FAIL;
				}
				break;
			}
		case ESDKSSO_SERVICE_TOKEN_LOGIN:
			{
				//ʹ��token��¼��Ʒ
				ClassInstanceMap::iterator nPos = m_vecClassInstance.find(iter->first);
				if(nPos != m_vecClassInstance.end())
				{
					ProductSDK *pPDUSDK = nPos->second;
					if (NULL == pPDUSDK)
					{
						ERROR_LOG() << "PDU SDK not exist, SDK = " << (iter->first) << "!!!";
						return ESDKSSO_FAIL;
					}
					
					int iRet = setWorkDirctoryByClassName(iter->first);
					if (ESDKSSO_SUCCESS != iRet)
					{
						ERROR_LOG() << "Set PDU SDK directory fail, SDK = " << (iter->first) << "!!!";
						return ESDKSSO_FAIL;
					}

					iRet = pPDUSDK->Login(token);
					if (ESDKSSO_SUCCESS != iRet)
					{
						ERROR_LOG() << "Login PDU SDK fail, SDK = " << (iter->first) << "!!!"; 
						return ESDKSSO_INTERNAL_ERROR;
					}

					DEBUG_LOG() << "Login PDU SDK success, SDK = " << (iter->first);
				}
				else
				{
					ERROR_LOG() << "PDU SDK not exist, SDK = " << (iter->first) << "!!!";
					return ESDKSSO_FAIL;
				}
				
				break;
			}
		default:
			{
				ERROR_LOG() << "Invalid Login method and login PDU SDK fail, (SDK = " << (iter->first) << ", Login method = " << (iter->second) << ")!!!";
				return ESDKSSO_FAIL;
			}
		}
		
	}

	SetCurrentDirectory(m_CurrentDirect.c_str());
	//����û�������
	clearUserInfo();
	//����token
	(void)setToken(token.c_str());

	DEBUG_LOG() << "--- LEAVE";
	return ESDKSSO_SUCCESS;
}

int eSDKSSOExecute::login(const std::string &name, const std::string &password, int type)
{
	DEBUG_LOG() << "--- ENTRY";
	INFO_PARAM2(name, type);
	
	switch(type)
	{
	case ESDKSSO_LOGIN_SERVICE:
		{
			ClassInstanceMap::iterator iter = m_vecClassInstance.begin();
			ClassInstanceMap::iterator itEnd = m_vecClassInstance.end();
			//ʹ���û��������¼��Ʒ
			for(; iter != itEnd; iter++)
			{
				ProductSDK *pPDUSDK = iter->second;
				if (NULL == pPDUSDK)
				{
					ERROR_LOG() << "PDU SDK not exist, SDK = " << (iter->first) << "!!!";
					return ESDKSSO_FAIL;
				}
				
				int iRet = setWorkDirctoryByClassName(iter->first);
				if (ESDKSSO_SUCCESS != iRet)
				{
					ERROR_LOG() << "Set PDU SDK directory fail, SDK = " << (iter->first) << "!!!";
					return ESDKSSO_FAIL;
				}

				iRet = pPDUSDK->Login(name, password);
				if (ESDKSSO_SUCCESS != iRet)
				{
					ERROR_LOG() << "Login PDU SDK fail, (user = "<< name << ", SDK = " << (iter->first) << ")!!!"; 
					return ESDKSSO_INTERNAL_ERROR;
				}

				DEBUG_LOG() << "Login PDU SDK success, (user = " << name << ", SDK = " << (iter->first) << ")";
			}
			
			SetCurrentDirectory(m_CurrentDirect.c_str());
			break;
		}
	case ESDKSSO_LOGIN_SSO:
		{
			//ʹ���û��������¼eSDK SSO server
			int iRet = SSOLogin(name.c_str(), password.c_str());
			if (SSOADAPTER_SUCCESS != iRet)
			{
				ERROR_LOG() << "Login SSO Server fail, user = "<< name << "!!!"; 
				return ESDKSSO_INTERNAL_ERROR;
			}

			DEBUG_LOG() << "Login SSO Server success, user = " << name;
			const int LENGTH = 256;
			char acToken[LENGTH] = {0};
			iRet = getToken(acToken, LENGTH);
			if (SSOADAPTER_SUCCESS != iRet)
			{
				ERROR_LOG() << "Get token fail!!!"; 
				return ESDKSSO_FAIL;
			}
			
			TokenManager *pTokenMgr = TokenManager::getInstance();
			if (NULL == pTokenMgr)
			{
				ERROR_LOG() << "Instance token manager fail.";
				return ESDKSSO_FAIL;
			}

			if (!pTokenMgr->WriteToken(acToken))
			{
				ERROR_LOG() << "Write token fail.";
				return ESDKSSO_FAIL;
			}			
			break;
		}
	default:
		{
			ERROR_LOG() << "Error login type, type = " << type << "!!!";
			return ESDKSSO_FAIL;
		}
	}
	DEBUG_LOG() << "Login eSDKClient platform success";
	DEBUG_LOG() << "--- LEAVE";
	return ESDKSSO_SUCCESS;
}

int eSDKSSOExecute::logout()
{
	DEBUG_LOG() << "--- ENTRY";
	
	ClassInstanceMap::iterator iter = m_vecClassInstance.begin();
	ClassInstanceMap::iterator itEnd = m_vecClassInstance.end();
	for(; iter != itEnd; iter++)
	{
		ProductSDK *pPDUSDK = iter->second;
		if (NULL == pPDUSDK)
		{
			ERROR_LOG() << "PDU SDK not exist, SDK = " << (iter->first) << "!!!";
			return ESDKSSO_FAIL;
		}
		
		int iRet = setWorkDirctoryByClassName(iter->first);
		if (ESDKSSO_SUCCESS != iRet)
		{
			ERROR_LOG() << "Set PDU SDK directory fail, SDK = " << (iter->first) << "!!!";
			return ESDKSSO_FAIL;
		}

		iRet = pPDUSDK->Logout();
		if (ESDKSSO_SUCCESS != iRet)
		{
			ERROR_LOG() << "Logout PDU SDK fail, SDK = " << (iter->first) << "!!!"; 
			return ESDKSSO_INTERNAL_ERROR;
		}
		DEBUG_LOG() << "Logout PDU SDK success, SDK = " << (iter->first);
	}
	
	SetCurrentDirectory(m_CurrentDirect.c_str());

	DEBUG_LOG() << "Logout eSDKClient platform success";
	DEBUG_LOG() << "--- LEAVE";
	return ESDKSSO_SUCCESS;
}
//����eSDK server
int eSDKSSOExecute::setConfig(const std::string &param)
{
	DEBUG_LOG() << "--- ENTRY";
	INFO_PARAM1(param);
	//����http_client����
	
	if (param.empty())
	{
		ERROR_LOG() << "param is invalid.";
		return ESDKSSO_FAIL;
	}

	int iRet = InstanceSSO(param.c_str());
	if (SSOADAPTER_SUCCESS != iRet)
	{
		ERROR_LOG() << "Instance SSO adapter fail!!!";
		return ESDKSSO_FAIL;
	}
	
	DEBUG_LOG() << "Instance SSO adapter success";
	DEBUG_LOG() << "--- LEAVE";
	return ESDKSSO_SUCCESS;
}

int eSDKSSOExecute::setHostIP(const std::string &ip)
{
	DEBUG_LOG() << "--- ENTRY";
	bool bRet = eSDKTool::CheckIPValid(ip);
	if (!bRet)
	{
		ERROR_LOG() << "IP is invalid";
		return ESDKSSO_FAIL;
	}

	int iRet = ::setHostIP(ip.c_str());
	if (SSOADAPTER_SUCCESS != iRet)
	{
		ERROR_LOG() << "Set host IP fail!!!";
		return ESDKSSO_FAIL;
	}
	DEBUG_LOG() << "Set host IP success.";
	DEBUG_LOG() << "--- LEAVE";
	return ESDKSSO_SUCCESS;
}

int eSDKSSOExecute::setWorkDirctoryByClassName(const std::string &className)
{
	DEBUG_LOG() << "--- ENTRY";
	std::map<std::string, std::string>::iterator nPos = m_ServiceWorkDirectMap.find(className);
	if (nPos == m_ServiceWorkDirectMap.end())
	{
		ERROR_LOG() << "Get service work directory fail, service = " << className << "!!!";
		return ESDKSSO_FAIL;
	}

	if (!SetCurrentDirectory((nPos->second).c_str()))
	{
		ERROR_LOG() << "Set service word directory fail, service = " << className << "!!!";
		return ESDKSSO_FAIL;
	}

	DEBUG_LOG() << "--- LEAVE";
	return ESDKSSO_SUCCESS;

}

unsigned long eSDKSSOExecute::getServiceHandleByName(const std::string& strServiceName)
{
	std::map<std::string, HINSTANCE>::iterator iter = m_vecDllHandle.find(strServiceName);
	if (iter == m_vecDllHandle.end())
	{
		return NULL;
	}

	return (unsigned long)(iter->second);

}
