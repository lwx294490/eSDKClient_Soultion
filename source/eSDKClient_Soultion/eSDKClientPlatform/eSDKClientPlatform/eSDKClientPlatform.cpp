
#include <string>
#include "eSDKClient_Platform.h"
#include "eSDKClientPlatform.h"
#include "eSDKLog.h"

#pragma comment(linker, "/EXPORT:eSDKClientPlatform_Init=_eSDKClientPlatform_Init@0")
#pragma comment(linker, "/EXPORT:eSDKClientPlatform_Uninit=_eSDKClientPlatform_Uninit@0")
#pragma comment(linker, "/EXPORT:eSDKClientPlatform_LoginByToken=_eSDKClientPlatform_LoginByToken@4")
#pragma comment(linker, "/EXPORT:eSDKClientPlatform_LoginByPassword=_eSDKClientPlatform_LoginByPassword@12")
#pragma comment(linker, "/EXPORT:eSDKClientPlatform_Logout=_eSDKClientPlatform_Logout@0")
#pragma comment(linker, "/EXPORT:eSDKClientPlatform_SetSSOServerUrl=_eSDKClientPlatform_SetSSOServerUrl@4")
#pragma comment(linker, "/EXPORT:eSDKClientPlatform_SetHostIP=_eSDKClientPlatform_SetHostIP@4")
#pragma comment(linker, "/EXPORT:eSDKClientPlatform_SetUpdateServer=_eSDKClientPlatform_SetUpdateServer@4")
#pragma comment(linker, "/EXPORT:eSDKClientPlatform_SetMessageCallBack=_eSDKClientPlatform_SetMessageCallBack@4")

extern void UninitAllPtr(void);

int __ESDKCLIENTPLATFORM_CALL eSDKClientPlatform_Init(void)
{
	eSDKClientPlatform* peSDKClient = eSDKClientPlatform::getInstance();
	if (NULL == peSDKClient)
	{
		return ESDKCLIENTPLATFORM_FAIL;
	}

	int iRet = peSDKClient->init();
	return iRet;
}

int __ESDKCLIENTPLATFORM_CALL eSDKClientPlatform_Uninit(void)
{
	DEBUG_LOG() << "--- ENTER";
	eSDKClientPlatform* peSDKClient = eSDKClientPlatform::getInstance();
	if (NULL == peSDKClient)
	{
		ERROR_LOG() << "Instance eSDKClientPlatform fail.";
		return ESDKCLIENTPLATFORM_FAIL;
	}

	int iRet = peSDKClient->uninit();
	if (ESDKCLIENT_PLATFORM_SUCCESS != iRet)
	{
		ERROR_LOG() << "Uninit eSDKClientPlatform fail.";
		return iRet;
	}
	
	eSDKClientPlatform::ReleaseInstance();

	UninitAllPtr();
	return iRet;
}

int __ESDKCLIENTPLATFORM_CALL eSDKClientPlatform_LoginByToken(const char* token)
{
	DEBUG_LOG() << "--- ENTER";
	if (NULL == token)
	{
		ERROR_LOG() << "token is NULL.";
		return ESDKCLIENTPLATFORM_FAIL;			
	}
	
	eSDKClientPlatform* peSDKClient = eSDKClientPlatform::getInstance();
	if (NULL == peSDKClient)
	{
		ERROR_LOG() << "Instance eSDKClientPlatform fail.";
		return ESDKCLIENTPLATFORM_FAIL;
	}

	std::string strToken = token;
	int iRet = peSDKClient->login(strToken);
	if (ESDKCLIENT_PLATFORM_SUCCESS != iRet)
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

int __ESDKCLIENTPLATFORM_CALL eSDKClientPlatform_LoginByPassword(const char* name, const char* password, const int type)
{
	DEBUG_LOG() << "--- ENTER";
	if (NULL == name)
	{
		ERROR_LOG() << "name is NULL.";
		return ESDKCLIENTPLATFORM_FAIL;			
	}

	if (NULL == password)
	{
		ERROR_LOG() << "password is NULL.";
		return ESDKCLIENTPLATFORM_FAIL;			
	}

	eSDKClientPlatform* peSDKClient = eSDKClientPlatform::getInstance();
	if (NULL == peSDKClient)
	{
		ERROR_LOG() << "Instance eSDKClientPlatform fail.";
		return ESDKCLIENTPLATFORM_FAIL;
	}

	std::string strName = name;
	std::string strPassword = password;
	int iRet = peSDKClient->login(strName, strPassword, type);
	if (ESDKCLIENT_PLATFORM_SUCCESS != iRet)
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

int __ESDKCLIENTPLATFORM_CALL eSDKClientPlatform_Logout()
{
	DEBUG_LOG() << "--- ENTER";
	eSDKClientPlatform* peSDKClient = eSDKClientPlatform::getInstance();
	if (NULL == peSDKClient)
	{
		ERROR_LOG() << "Instance eSDKClientPlatform fail.";
		return ESDKCLIENTPLATFORM_FAIL;
	}

	int iRet = peSDKClient->logout();
	if (ESDKCLIENT_PLATFORM_SUCCESS != iRet)
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

int __ESDKCLIENTPLATFORM_CALL eSDKClientPlatform_SetSSOServerUrl(const char* url)
{
	DEBUG_LOG() << "--- ENTER";
	if (NULL == url)
	{
		ERROR_LOG() << "url is NULL.";
		return ESDKCLIENTPLATFORM_FAIL;	
	}

	eSDKClientPlatform* peSDKClient = eSDKClientPlatform::getInstance();
	if (NULL == peSDKClient)
	{
		ERROR_LOG() << "Instance eSDKClientPlatform fail.";
		return ESDKCLIENTPLATFORM_FAIL;
	}

	std::string strUrl = url;
	int iRet = peSDKClient->setConfig(strUrl);
	if (ESDKCLIENT_PLATFORM_SUCCESS != iRet)
	{
		ERROR_LOG() << "set SSO server url fail.";
	}
	else
	{
		DEBUG_LOG() << "set SSO server url success.";
	}


	DEBUG_LOG() << "--- LEAVE";
	return iRet;
}


int __ESDKCLIENTPLATFORM_CALL eSDKClientPlatform_SetHostIP(const char* ip)
{
	DEBUG_LOG() << "--- ENTER";
	if (NULL == ip)
	{
		ERROR_LOG() << "ip is NULL.";
		return ESDKCLIENTPLATFORM_FAIL;	
	}

	eSDKClientPlatform* peSDKClient = eSDKClientPlatform::getInstance();
	if (NULL == peSDKClient)
	{
		ERROR_LOG() << "Instance eSDKClientPlatform fail.";
		return ESDKCLIENTPLATFORM_FAIL;
	}
	
	std::string strIP = ip;
	int iRet = peSDKClient->setHostIP(strIP);
	if (ESDKCLIENT_PLATFORM_SUCCESS != iRet)
	{
		ERROR_LOG() << "set host ip fail.";
	}
	else
	{
		DEBUG_LOG() << "set host ip success.";
	}
	DEBUG_LOG() << "--- LEAVE";
	return iRet;
}

int __ESDKCLIENTPLATFORM_CALL eSDKClientPlatform_SetUpdateServer(const char* pchServerUrl)
{
	DEBUG_LOG() << "--- ENTER";
	if (NULL == pchServerUrl)
	{
		ERROR_LOG() << "Server url is NULL.";
		return ESDKCLIENTPLATFORM_FAIL;	
	}

	eSDKClientPlatform* peSDKClient = eSDKClientPlatform::getInstance();
	if (NULL == peSDKClient)
	{
		ERROR_LOG() << "Instance eSDKClientPlatform fail.";
		return ESDKCLIENTPLATFORM_FAIL;
	}

	std::string strUrl = pchServerUrl;
	int iRet = peSDKClient->setUpdateServer(strUrl);
	if (ESDKCLIENT_PLATFORM_SUCCESS != iRet)
	{
		ERROR_LOG() << "set update server url fail.";
	}
	else
	{
		DEBUG_LOG() << "set update server url success.";
	}

	DEBUG_LOG() << "--- LEAVE";
	return iRet;
}

//存储用户传入的回调函数指针
eSDKClientMessageCallBack g_fpMsgCallback = NULL;

//消息回调函数桩，将此桩函数设置到升级组件中，在调用用户设定的回调函数之前，先将参数转换成C的数据类型，然后再调用
bool CALLBACK MessageCallBackStub(int iMsgID, std::string strDescription)
{
	if (NULL == g_fpMsgCallback)
	{
		return false;
	}
	//string类型转换成char类型
	size_t iLen = strDescription.size();
	char *pchDescription = (char *)malloc(sizeof(char) * (iLen + 1));
	if (NULL == pchDescription)
	{
		return false;
	}

	memcpy(pchDescription, strDescription.c_str(), iLen);
	pchDescription[iLen] = '\0';
	//调用用户传入的回调函数
	bool bRet = (*g_fpMsgCallback)(iMsgID, pchDescription);

	free(pchDescription);

	return bRet;
}


bool __ESDKCLIENTPLATFORM_CALL eSDKClientPlatform_SetMessageCallBack(eSDKClientMessageCallBack fpMsgCB)
{
	DEBUG_LOG() << "--- ENTER";
	if (NULL == fpMsgCB)
	{
		ERROR_LOG() << "fpMsgCB  is NULL.";
		return false;	
	}

	g_fpMsgCallback = fpMsgCB;
	eSDKClientPlatform* peSDKClient = eSDKClientPlatform::getInstance();
	if (NULL == peSDKClient)
	{
		ERROR_LOG() << "Instance eSDKClientPlatform fail.";
		return false;
	}

	bool bRet = peSDKClient->SetMessageCallBack(MessageCallBackStub);
	if (!bRet)
	{
		ERROR_LOG() << "Set MessageCallBack fail.";
	}
	else
	{
		DEBUG_LOG() << "Set MessageCallBack success.";
	}

	DEBUG_LOG() << "--- LEAVE";
	return bRet;
}
