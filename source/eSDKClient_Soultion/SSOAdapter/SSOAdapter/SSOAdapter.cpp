
#include "SSOAdapter.h"
#include "eSDKSSOAdapter.h"
#include "eSDKHost.h"
#include "eSDKTool.h"

#pragma comment(linker, "/EXPORT:InstanceSSO=_InstanceSSO@4")
#pragma comment(linker, "/EXPORT:SSOLogin=_SSOLogin@8")
#pragma comment(linker, "/EXPORT:SSOAuthenticate=_SSOAuthenticate@20")
#pragma comment(linker, "/EXPORT:getToken=_getToken@8")
#pragma comment(linker, "/EXPORT:setToken=_setToken@4")
#pragma comment(linker, "/EXPORT:clearUserInfo=_clearUserInfo@0")
#pragma comment(linker, "/EXPORT:setHostIP=_setHostIP@4")

int __SSOADAPTER_CALL InstanceSSO(const char *pSSOUri)
{
	if (NULL == pSSOUri)
	{
		return SSOADAPTER_FAIL;
	}
	std::string szStr = pSSOUri;
	std::wstring wszStr;
	wszStr = eSDKTool::StringToWString(szStr);
	if(!uri::validate(wszStr))
	{
		return SSOADAPTER_FAIL;
	}

	if (!eSDKSSOAdapter::CheckUriValid(wszStr))
	{
		return SSOADAPTER_FAIL;
	}

	(void)eSDKSSOAdapter::getSharedInstance(pSSOUri);

	return SSOADAPTER_SUCCESS;
}

int __SSOADAPTER_CALL SSOLogin(const char *pchName, const char *pchPassword)
{
	if ((NULL == pchName) || (NULL == pchPassword))
	{
		return SSOADAPTER_FAIL;
	}

	int iRet = eSDKSSOAdapter::getSharedInstance().SSOLogin(pchName, pchPassword);
	if (ESDKSSO_ADAPTER_SUCCESS != iRet)
	{
		return SSOADAPTER_FAIL;
	}
	return SSOADAPTER_SUCCESS;

}

int __SSOADAPTER_CALL SSOAuthenticate(const char *token, const char *pchPDUName,char *pchName, char *pchPassword, int iBufLen)
{	
	if ((NULL == token) || (NULL == pchPDUName) || (NULL == pchName) || (NULL == pchPassword) || (0 == strlen(token)) || (0 == strlen(pchPDUName)))
	{
		return SSOADAPTER_FAIL;
	}


	std::string strName("");
	std::string strPassword("");
	int iRet = eSDKSSOAdapter::getSharedInstance().SSOAuthenticate(token, pchPDUName, strName, strPassword);
	if (ESDKSSO_ADAPTER_SUCCESS != iRet)
	{
		return SSOADAPTER_FAIL;
	}

	int iLen = strName.size();
	if (iLen >= iBufLen)
	{
		return SSOADAPTER_FAIL;
	}
	
	memcpy(pchName, strName.c_str(), iLen);
	pchName[iLen] = '\0';

	iLen = strPassword.size();
	if (iLen >= iBufLen)
	{
		return SSOADAPTER_FAIL;
	}
	
	memcpy(pchPassword, strPassword.c_str(), iLen);
	pchPassword[iLen] = '\0';

	return SSOADAPTER_SUCCESS;
}

int __SSOADAPTER_CALL getToken(char *pTokenBuf, int iBufLen)
{
	if (NULL == pTokenBuf)
	{
		return SSOADAPTER_FAIL;
	}

	std::string strToken("");
	strToken = eSDKSSOAdapter::getSharedInstance().getToken();

	int iLen = strToken.size();
	if (iLen >= iBufLen)
	{
		return SSOADAPTER_FAIL;
	}
	memcpy(pTokenBuf, strToken.c_str(), iLen);
	pTokenBuf[iLen] = '\0';
	
	return SSOADAPTER_SUCCESS;
}

int __SSOADAPTER_CALL setToken(const char *pToken)
{
	if (NULL == pToken)
	{
		return SSOADAPTER_FAIL;
	}

	eSDKSSOAdapter::getSharedInstance().setToken(pToken);

	return SSOADAPTER_SUCCESS;
}

void __SSOADAPTER_CALL clearUserInfo(void)
{
	eSDKSSOAdapter::getSharedInstance().clearUserInfo();

	return;
}


int __SSOADAPTER_CALL setHostIP(const char *pchIp)
{
	if (NULL == pchIp)
	{
		return SSOADAPTER_FAIL;
	}


	eSDKHost::setHostIP(pchIp);

	return SSOADAPTER_SUCCESS;
}
