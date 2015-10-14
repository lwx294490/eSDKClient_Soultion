#include <string>
#include "eSDKSSO.h"
#include "eSDK_SSO.h"
#include "eSDKLog.h"

#pragma comment(linker, "/EXPORT:eSDKSSO_Init=_eSDKSSO_Init@0")
#pragma comment(linker, "/EXPORT:eSDKSSO_Uninit=_eSDKSSO_Uninit@0")
#pragma comment(linker, "/EXPORT:eSDKSSO_LoginByToken=_eSDKSSO_LoginByToken@4")
#pragma comment(linker, "/EXPORT:eSDKSSO_LoginByNamePassword=_eSDKSSO_LoginByNamePassword@12")
#pragma comment(linker, "/EXPORT:eSDKSSO_Logout=_eSDKSSO_Logout@0")
#pragma comment(linker, "/EXPORT:eSDKSSO_SetSSOServerUrl=_eSDKSSO_SetSSOServerUrl@4")
#pragma comment(linker, "/EXPORT:eSDKSSO_SetHostIP=_eSDKSSO_SetHostIP@4")
#pragma comment(linker, "/EXPORT:eSDKSSO_GetServiceHandleByName=_eSDKSSO_GetServiceHandleByName@4")

int __ESDK_SSO_CALL eSDKSSO_Init()
{
	eSDKSSO* pSSO = eSDKSSO::getInstance();
	if (NULL == pSSO)
	{
		return ESDK_SSO_FAIL;
	}

	int iRet = pSSO->init();
	return iRet;
}

int __ESDK_SSO_CALL eSDKSSO_Uninit()
{
	DEBUG_LOG() << "--- ENTER";
	eSDKSSO* pSSO = eSDKSSO::getInstance();
	if (NULL == pSSO)
	{
		ERROR_LOG() << "Instance eSDKSSO fail.";
		return ESDK_SSO_FAIL;
	}

	int iRet = pSSO->uninit();
	if (ESDKSSO_SUCCESS != iRet)
	{
		ERROR_LOG() << "Uninit eSDKSSO fail.";
		return iRet;
	}
	
	eSDKSSO::ReleaseInstance();
	return iRet;
}

int __ESDK_SSO_CALL eSDKSSO_LoginByToken(const char* token)
{
	DEBUG_LOG() << "--- ENTER";
	if (NULL == token)
	{
		ERROR_LOG() << "token is null.";
		return ESDK_SSO_FAIL;
	}

	eSDKSSO* pSSO = eSDKSSO::getInstance();
	if (NULL == pSSO)
	{
		ERROR_LOG() << "Instance eSDKSSO fail.";
		return ESDK_SSO_FAIL;
	}

	std::string strToken = token;
	int iRet = pSSO->login(strToken);
	if (ESDKSSO_SUCCESS != iRet)
	{
		ERROR_LOG() << "Login by token fail.";
	}
	else
	{
		DEBUG_LOG() << "Login by token success.";
	}

	DEBUG_LOG() << "--- LEAVE";
	return iRet;

}

int __ESDK_SSO_CALL eSDKSSO_LoginByNamePassword(const char* name, const char* password, int type)
{
	DEBUG_LOG() << "--- ENTER";
	if (NULL == name)
	{
		ERROR_LOG() << "name is null.";
		return ESDK_SSO_FAIL;
	}
	
	if (NULL == password)
	{
		ERROR_LOG() << "password is null.";
		return ESDK_SSO_FAIL;
	}

	eSDKSSO* pSSO = eSDKSSO::getInstance();
	if (NULL == pSSO)
	{
		ERROR_LOG() << "Instance eSDKSSO fail.";
		return ESDK_SSO_FAIL;
	}

	std::string strName = name;
	std::string strPassword = password;
	int iRet = pSSO->login(strName, strPassword, type);
	if (ESDKSSO_SUCCESS != iRet)
	{
		ERROR_LOG() << "Login by password fail.";
	}
	else
	{
		DEBUG_LOG() << "Login by password success.";
	}

	DEBUG_LOG() << "--- LEAVE";
	return iRet;
}

int __ESDK_SSO_CALL eSDKSSO_Logout()
{
	DEBUG_LOG() << "--- ENTER";
	
	eSDKSSO* pSSO = eSDKSSO::getInstance();
	if (NULL == pSSO)
	{
		ERROR_LOG() << "Instance eSDKSSO fail.";
		return ESDK_SSO_FAIL;
	}

	int iRet = pSSO->logout();
	if (ESDKSSO_SUCCESS != iRet)
	{
		ERROR_LOG() << "Logout fail.";
	}
	else
	{
		DEBUG_LOG() << "Logout success.";
	}

	DEBUG_LOG() << "--- LEAVE";
	return iRet;
}

int __ESDK_SSO_CALL eSDKSSO_SetSSOServerUrl(const char* url)
{
	DEBUG_LOG() << "--- ENTER";
	if (NULL == url)
	{
		ERROR_LOG() << "url is null.";
		return ESDK_SSO_FAIL;
	}
	
	eSDKSSO* pSSO = eSDKSSO::getInstance();
	if (NULL == pSSO)
	{
		ERROR_LOG() << "Instance eSDKSSO fail.";
		return ESDK_SSO_FAIL;
	}

	std::string strUrl = url;
	int iRet = pSSO->setConfig(strUrl);
	if (ESDKSSO_SUCCESS != iRet)
	{
		ERROR_LOG() << "Set SSO Server url fail.";
	}
	else
	{
		DEBUG_LOG() << "Set SSO Server url success.";
	}

	DEBUG_LOG() << "--- LEAVE";
	return iRet;
}

int __ESDK_SSO_CALL eSDKSSO_SetHostIP(const char* ip)
{
	DEBUG_LOG() << "--- ENTER";
	if (NULL == ip)
	{
		ERROR_LOG() << "ip is null.";
		return ESDK_SSO_FAIL;
	}

	eSDKSSO* pSSO = eSDKSSO::getInstance();
	if (NULL == pSSO)
	{
		ERROR_LOG() << "Instance eSDKSSO fail.";
		return ESDK_SSO_FAIL;
	}

	std::string strIp = ip;
	int iRet = pSSO->setHostIP(strIp);
	if (ESDKSSO_SUCCESS != iRet)
	{
		ERROR_LOG() << "Set host ip fail.";
	}
	else
	{
		DEBUG_LOG() << "Set host ip success.";
	}
	
	DEBUG_LOG() << "--- LEAVE";
	return iRet;
}

unsigned long __ESDK_SSO_CALL eSDKSSO_GetServiceHandleByName(const char* serviceName)
{
	DEBUG_LOG() << "--- ENTER";
	if ((NULL == serviceName) || (0 == strlen(serviceName)))
	{
		ERROR_LOG() << "serviceName is null or empty.";
		return NULL;
	}
	
	eSDKSSO* pSSO = eSDKSSO::getInstance();
	if (NULL == pSSO)
	{
		ERROR_LOG() << "Instance eSDKSSO fail.";
		return NULL;
	}

	std::string strServiceName = serviceName;
	unsigned long ulHandle = pSSO->getServiceHandleByName(strServiceName);
	if (NULL == ulHandle)
	{
		ERROR_LOG() << "getServiceHandleByName fail.";
	}
	else
	{
		DEBUG_LOG() << "getServiceHandleByName success.";
	}	
	DEBUG_LOG() << "--- LEAVE";
	return ulHandle;
}
