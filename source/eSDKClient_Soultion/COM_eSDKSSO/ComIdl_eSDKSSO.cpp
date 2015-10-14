// ComIdl_eSDKSSO.cpp : CComIdl_eSDKSSO 的实现

#include "stdafx.h"
#include <comutil.h>
#include <string>

#include "ComIdl_eSDKSSO.h"
#include "TokenManager.h"
#include "eSDKSSO.h"

#pragma comment(lib,"comsuppw")
#pragma comment(lib,"eSDKSSO.lib")
// CComIdl_eSDKSSO
STDMETHODIMP CComIdl_eSDKSSO::WriteToken(BSTR Credential)
{
	// TODO: 在此添加实现代码
	if (NULL == Credential)
	{
		return S_FALSE;
	}

	TokenManager* pTokenMgr = TokenManager::getInstance();
	if (NULL == pTokenMgr)
	{
		return S_FALSE;
	}

	if(!pTokenMgr->init())
	{
		return S_FALSE;
	}
	
	char *pcToken = _com_util::ConvertBSTRToString(Credential);
	if (NULL == pcToken)
	{
		return S_FALSE;
	}
	
	std::string strToken = pcToken;
	delete[] pcToken;
	if(!pTokenMgr->WriteToken(strToken))
	{
		return S_FALSE;
	}
	return S_OK;
}

STDMETHODIMP CComIdl_eSDKSSO::ClearToken(void)
{
	// TODO: 在此添加实现代码
	TokenManager* pTokenMgr = TokenManager::getInstance();
	if (NULL == pTokenMgr)
	{
		return S_FALSE;
	}

	if(!pTokenMgr->init())
	{
		return S_FALSE;
	}
	
	if (!pTokenMgr->ClearToken())
	{
		return S_FALSE;
	}
	return S_OK;
}

STDMETHODIMP CComIdl_eSDKSSO::GetToken(BSTR* Token)
{
	// TODO: 在此添加实现代码
	if (NULL == Token)
	{
		return S_FALSE;
	}

	TokenManager* pTokenMgr = TokenManager::getInstance();
	if (NULL == pTokenMgr)
	{
		return S_FALSE;
	}

	if(!pTokenMgr->init())
	{
		return S_FALSE;
	}

	std::string strToken;
	if (!pTokenMgr->GetToken(strToken))
	{
		return S_FALSE;
	}
	
	if (NULL != *Token)
	{
		SysFreeString(*Token);
	}

	*Token = _com_util::ConvertStringToBSTR(strToken.c_str());

	return S_OK;
}

STDMETHODIMP CComIdl_eSDKSSO::SSOLogin(BSTR name, BSTR password, BSTR SSOuri)
{
	// TODO: 在此添加实现代码
	if ((NULL == name) || (NULL == password) || (NULL == SSOuri))
	{
		return S_FALSE;
	}

	eSDKSSO *pSSOInstance = eSDKSSO::getInstance();
	if (NULL == pSSOInstance)
	{
		return S_FALSE;
	}

	if (ESDKSSO_SUCCESS != pSSOInstance->init())
	{
		return S_FALSE;
	}
	
	char *pcName = _com_util::ConvertBSTRToString(name);
	if (NULL == pcName)
	{
		return S_FALSE;
	}

	char *pcPassword = _com_util::ConvertBSTRToString(password);
	if (NULL == pcPassword)
	{
		delete[] pcName;
		return S_FALSE;
	}

	char *pcUri = _com_util::ConvertBSTRToString(SSOuri);
	if (NULL == pcUri)
	{
		delete[] pcName;
		delete[] pcPassword;
		return S_FALSE;
	}

	std::string strName = pcName;
	std::string strPassword = pcPassword;
	std::string strUri = pcUri;
	delete[] pcName;
	delete[] pcPassword;
	delete[] pcUri;
	if(ESDKSSO_SUCCESS != pSSOInstance->setConfig(strUri))
	{
		return S_FALSE;
	}

	if (ESDKSSO_SUCCESS != pSSOInstance->login(strName, strPassword, ESDKSSO_LOGIN_SSO))
	{
		return S_FALSE;
	}

	return S_OK;
}
