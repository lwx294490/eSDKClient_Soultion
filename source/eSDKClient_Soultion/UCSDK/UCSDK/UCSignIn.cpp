#include "stdafx.h"
#include "UCSignIn.h"
#include "UCSDKAbsProxy.h"
#include "UCSignalRecvProxy.h"
#include "eSDKLog.h"
#include "UCCommon.h"


#pragma comment(linker, "/EXPORT:Init=_Init@0")
#pragma comment(linker, "/EXPORT:UnInit=_UnInit@0")
#pragma comment(linker, "/EXPORT:LoginByToken=_LoginByToken@4")
#pragma comment(linker, "/EXPORT:LoginByPasswd=_LoginByPasswd@8")
#pragma comment(linker, "/EXPORT:Logout=_Logout@0")
#pragma comment(linker, "/EXPORT:Config=_Config@4")
#pragma comment(linker, "/EXPORT:SetLang=_SetLang@4")


int UCSDK_CALL Init()
{
	UCSDKAbsProxy* pUCSDKAbsProxy = UCSDKAbsProxy::GetInstance();
	if (NULL == pUCSDKAbsProxy)
	{
		return UC_NullPoint;
	}

	int iRet = pUCSDKAbsProxy->Init();
	if (UC_Succ != iRet)
	{
		return iRet;
	}

	//已经移动到UCSignalRecvProxy::Instance()中
	////设置回调函数
	//UCSignalRecvAbsProxy* pUCSignalRecvAbsProxy = dynamic_cast<UCSignalRecvAbsProxy*>(UCSignalRecvProxy::Instance());
	//iRet = pUCSDKAbsProxy->SetUCSignalRecvAbsProxy(pUCSignalRecvAbsProxy);
	//CHECK_RETURN(iRet, UC_Succ, "SetUCSignalRecvAbsProxy");

	DEBUG_LOG() << "Init Success.";
	DEBUG_LOG() << "--- LEAVE";
	return UC_Succ;
}

int UCSDK_CALL UnInit()
{
	DEBUG_LOG() << "--- ENTER";

	UCSDKAbsProxy* pUCSDKAbsProxy = UCSDKAbsProxy::GetInstance();
	CHECK_POINTER(pUCSDKAbsProxy, UC_NullPoint);

	int iRet = pUCSDKAbsProxy->UnInit();
	if (UC_Succ != iRet)
	{
		return iRet;
	}

	UCSignalRecvProxy::Destroy();

	return UC_Succ;
}

int UCSDK_CALL LoginByToken(const char* token)
{
	DEBUG_LOG() << "--- ENTER";
	
	CHECK_POINTER(token, UC_InvalidParam);

	UCSDKAbsProxy* pUCSDKAbsProxy = UCSDKAbsProxy::GetInstance();
	CHECK_POINTER(pUCSDKAbsProxy, UC_NullPoint);

	int iRet = pUCSDKAbsProxy->Login(token);
	CHECK_RETURN(iRet, UC_Succ, "Login");

	DEBUG_LOG() << "--- LEAVE";
	return UC_Succ;
}

int UCSDK_CALL LoginByPasswd(const char* account, const char* passwd)
{
	DEBUG_LOG() << "--- ENTER";

	CHECK_POINTER(account, UC_InvalidParam);
	CHECK_POINTER(passwd, UC_InvalidParam);

	UCSDKAbsProxy* pUCSDKAbsProxy = UCSDKAbsProxy::GetInstance();
	CHECK_POINTER(pUCSDKAbsProxy, UC_NullPoint);

	int iRet = pUCSDKAbsProxy->Login(account, passwd);
	CHECK_RETURN(iRet, UC_Succ, "Login");

	DEBUG_LOG() << "--- LEAVE";
	return UC_Succ;
}

int UCSDK_CALL Logout()
{
	DEBUG_LOG() << "--- ENTER";

	UCSDKAbsProxy* pUCSDKAbsProxy = UCSDKAbsProxy::GetInstance();
	CHECK_POINTER(pUCSDKAbsProxy, UC_NullPoint);

	int iRet = pUCSDKAbsProxy->Logout();
	CHECK_RETURN(iRet, UC_Succ, "Logout");

	DEBUG_LOG() << "--- LEAVE";
	return UC_Succ;
}

int UCSDK_CALL Config(const char* srvUrl)
{
	DEBUG_LOG() << "--- ENTER";

	CHECK_POINTER(srvUrl, UC_InvalidParam);

	UCSDKAbsProxy* pUCSDKAbsProxy = UCSDKAbsProxy::GetInstance();
	CHECK_POINTER(pUCSDKAbsProxy, UC_NullPoint);

	int iRet = pUCSDKAbsProxy->Config(srvUrl);
	CHECK_RETURN(iRet, UC_Succ, "Config");

	DEBUG_LOG() << "--- LEAVE";
	return UC_Succ;
}

int UCSDK_CALL SetLang(const char* lang)
{
	DEBUG_LOG() << "--- ENTER";

	CHECK_POINTER(lang, UC_InvalidParam);

	UCSDKAbsProxy* pUCSDKAbsProxy = UCSDKAbsProxy::GetInstance();
	CHECK_POINTER(pUCSDKAbsProxy, UC_NullPoint);

	int iRet = pUCSDKAbsProxy->SetLang(lang);
	CHECK_RETURN(iRet, UC_Succ, "SetLang");

	DEBUG_LOG() << "--- LEAVE";
	return UC_Succ;
}
