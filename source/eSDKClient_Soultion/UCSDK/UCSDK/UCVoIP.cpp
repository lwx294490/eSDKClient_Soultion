#include "stdafx.h"
#include "UCVoIP.h"
#include "UCVoIPAbsProxy.h"
#include "UCStructCopy.h"
#include "eSDKLog.h"
#include "UCCommon.h"

#pragma comment(linker, "/EXPORT:MakeCall=_MakeCall@20")
#pragma comment(linker, "/EXPORT:Accept=_Accept@16")
#pragma comment(linker, "/EXPORT:Reject=_Reject@8")
#pragma comment(linker, "/EXPORT:Hangup=_Hangup@8")
#pragma comment(linker, "/EXPORT:Hold=_Hold@4")
#pragma comment(linker, "/EXPORT:Resume=_Resume@4")
#pragma comment(linker, "/EXPORT:Forward=_Forward@8")
#pragma comment(linker, "/EXPORT:StartRecord=_StartRecord@8")
#pragma comment(linker, "/EXPORT:StopRecord=_StopRecord@4")
#pragma comment(linker, "/EXPORT:MuteVoIP=_MuteVoIP@4")
#pragma comment(linker, "/EXPORT:UnMuteVoIP=_UnMuteVoIP@4")


int UCSDK_CALL MakeCall(const UCContact* member, int iType, const UCVideoWindow* localWnd,
						const UCVideoWindow* remoteWnd, char convId[CONVID_LENGTH])
{
	DEBUG_LOG() << "--- ENTER";
	CHECK_POINTER(convId, UC_InvalidParam);
	CHECK_POINTER(member, UC_InvalidParam);
	if (UC_Video != iType && UC_Audio != iType)
	{
		ERROR_LOG() << "iType is neither audio nor video.";
		DEBUG_LOG() << "--- LEAVE";
		return UC_InvalidParam;
	}
	if (UC_Video == iType)
	{
		CHECK_POINTER(localWnd, UC_InvalidParam);
		CHECK_POINTER(remoteWnd, UC_InvalidParam);
	}

	UCVoIPAbsProxy* pUCVoIPAbsProxy = UCVoIPAbsProxy::GetInstance();
	CHECK_POINTER(pUCVoIPAbsProxy, UC_NullPoint);

	std::string sConvId = convId;
	UCSDKContact contact;
	STVideoWindow localw;
	STVideoWindow remotew;
	ctk::MemSet(&localw, 0, sizeof(localw));
	ctk::MemSet(&remotew, 0, sizeof(remotew));
	UCStructCopy::Copy_UCSDKContact(contact, *member);
	if (UC_Video == iType)
	{
		UCStructCopy::Copy_STVideoWindow(localw, *localWnd);
		UCStructCopy::Copy_STVideoWindow(remotew, *remoteWnd);
	}

	int iRet = pUCVoIPAbsProxy->MakeCall(sConvId, contact, iType, localw, remotew);
	CHECK_RETURN(iRet, UC_Succ, "MakeCall");

	UCStructCopy::UCMemCopy(convId, sConvId, CONVID_LENGTH);

	DEBUG_LOG() << "--- LEAVE";
	return UC_Succ;
}

int UCSDK_CALL Accept(const char* convId, int iType, const UCVideoWindow* localWnd, const UCVideoWindow* remoteWnd)
{
	DEBUG_LOG() << "--- ENTER";
	CHECK_POINTER(convId, UC_InvalidParam);
	if (UC_Video != iType && UC_Audio != iType)
	{
		ERROR_LOG() << "iType is neither audio nor video.";
		DEBUG_LOG() << "--- LEAVE";
		return UC_InvalidParam;
	}
	if (UC_Video == iType)
	{
		CHECK_POINTER(localWnd, UC_InvalidParam);
		CHECK_POINTER(remoteWnd, UC_InvalidParam);
	}

	STVideoWindow localw;
	STVideoWindow remotew;
	ctk::MemSet(&localw, 0, sizeof(localw));
	ctk::MemSet(&remotew, 0, sizeof(remotew));
	if (UC_Video == iType)
	{
		UCStructCopy::Copy_STVideoWindow(localw, *localWnd);
		UCStructCopy::Copy_STVideoWindow(remotew, *remoteWnd);
	}

	UCVoIPAbsProxy* pUCVoIPAbsProxy = UCVoIPAbsProxy::GetInstance();
	CHECK_POINTER(pUCVoIPAbsProxy, UC_NullPoint);

	int iRet = pUCVoIPAbsProxy->Accept(convId, iType, localw, remotew);
	CHECK_RETURN(iRet, UC_Succ, "Accept");

	DEBUG_LOG() << "--- LEAVE";
	return UC_Succ;
}

int UCSDK_CALL Reject(const char* convId, int iType)
{
	DEBUG_LOG() << "--- ENTER";
	CHECK_POINTER(convId, UC_InvalidParam);
	if (UC_Video != iType && UC_Audio != iType)
	{
		ERROR_LOG() << "iType is neither audio nor video.";
		DEBUG_LOG() << "--- LEAVE";
		return UC_InvalidParam;
	}

	UCVoIPAbsProxy* pUCVoIPAbsProxy = UCVoIPAbsProxy::GetInstance();
	CHECK_POINTER(pUCVoIPAbsProxy, UC_NullPoint);

	int iRet = pUCVoIPAbsProxy->Reject(convId, iType);
	CHECK_RETURN(iRet, UC_Succ, "Reject");

	DEBUG_LOG() << "--- LEAVE";
	return UC_Succ;
}

int UCSDK_CALL Hangup(const char* convId, int iType)
{
	DEBUG_LOG() << "--- ENTER";
	CHECK_POINTER(convId, UC_InvalidParam);
	if (UC_Video != iType && UC_Audio != iType)
	{
		ERROR_LOG() << "iType is neither audio nor video.";
		DEBUG_LOG() << "--- LEAVE";
		return UC_InvalidParam;
	}

	UCVoIPAbsProxy* pUCVoIPAbsProxy = UCVoIPAbsProxy::GetInstance();
	CHECK_POINTER(pUCVoIPAbsProxy, UC_NullPoint);

	int iRet = pUCVoIPAbsProxy->Hangup(convId, iType);
	CHECK_RETURN(iRet, UC_Succ, "Hangup");

	DEBUG_LOG() << "--- LEAVE";
	return UC_Succ;
}

int UCSDK_CALL Hold(const char* convId)
{
	DEBUG_LOG() << "--- ENTER";
	CHECK_POINTER(convId, UC_InvalidParam);

	UCVoIPAbsProxy* pUCVoIPAbsProxy = UCVoIPAbsProxy::GetInstance();
	CHECK_POINTER(pUCVoIPAbsProxy, UC_NullPoint);

	int iRet = pUCVoIPAbsProxy->Hold(convId);
	CHECK_RETURN(iRet, UC_Succ, "Hold");

	DEBUG_LOG() << "--- LEAVE";
	return UC_Succ;
}

int UCSDK_CALL Resume(const char* convId)
{
	DEBUG_LOG() << "--- ENTER";
	CHECK_POINTER(convId, UC_InvalidParam);

	UCVoIPAbsProxy* pUCVoIPAbsProxy = UCVoIPAbsProxy::GetInstance();
	CHECK_POINTER(pUCVoIPAbsProxy, UC_NullPoint);

	int iRet = pUCVoIPAbsProxy->Resume(convId);
	CHECK_RETURN(iRet, UC_Succ, "Resume");

	DEBUG_LOG() << "--- LEAVE";
	return UC_Succ;
}

int UCSDK_CALL Forward(const char* convId, const char* account)
{
	DEBUG_LOG() << "--- ENTER";
	CHECK_POINTER(convId, UC_InvalidParam);
	CHECK_POINTER(account, UC_InvalidParam);

	UCVoIPAbsProxy* pUCVoIPAbsProxy = UCVoIPAbsProxy::GetInstance();
	CHECK_POINTER(pUCVoIPAbsProxy, UC_NullPoint);

	int iRet = pUCVoIPAbsProxy->Forward(convId, account);
	CHECK_RETURN(iRet, UC_Succ, "Forward");

	DEBUG_LOG() << "--- LEAVE";
	return UC_Succ;
}

int UCSDK_CALL StartRecord(const char* convId, const char* filePath)
{
	DEBUG_LOG() << "--- ENTER";
	CHECK_POINTER(convId, UC_InvalidParam);
	CHECK_POINTER(filePath, UC_InvalidParam);

	UCVoIPAbsProxy* pUCVoIPAbsProxy = UCVoIPAbsProxy::GetInstance();
	CHECK_POINTER(pUCVoIPAbsProxy, UC_NullPoint);

	int iRet = pUCVoIPAbsProxy->StartRecord(convId, filePath);
	CHECK_RETURN(iRet, UC_Succ, "StartRecord");

	DEBUG_LOG() << "--- LEAVE";
	return UC_Succ;
}

int UCSDK_CALL StopRecord(const char* convId)
{
	DEBUG_LOG() << "--- ENTER";
	CHECK_POINTER(convId, UC_InvalidParam);

	UCVoIPAbsProxy* pUCVoIPAbsProxy = UCVoIPAbsProxy::GetInstance();
	CHECK_POINTER(pUCVoIPAbsProxy, UC_NullPoint);

	int iRet = pUCVoIPAbsProxy->StopRecord(convId);
	CHECK_RETURN(iRet, UC_Succ, "StopRecord");

	DEBUG_LOG() << "--- LEAVE";
	return UC_Succ;
}

int UCSDK_CALL MuteVoIP(int iType)
{
	DEBUG_LOG() << "--- ENTER";
	if (UC_Video != iType && UC_Audio != iType)
	{
		ERROR_LOG() << "iType is neither audio nor video.";
		DEBUG_LOG() << "--- LEAVE";
		return UC_InvalidParam;
	}

	UCVoIPAbsProxy* pUCVoIPAbsProxy = UCVoIPAbsProxy::GetInstance();
	CHECK_POINTER(pUCVoIPAbsProxy, UC_NullPoint);

	int iRet = pUCVoIPAbsProxy->Mute(iType);
	CHECK_RETURN(iRet, UC_Succ, "Mute");

	DEBUG_LOG() << "--- LEAVE";
	return UC_Succ;
}

int UCSDK_CALL UnMuteVoIP(int iType)
{
	DEBUG_LOG() << "--- ENTER";
	if (UC_Video != iType && UC_Audio != iType)
	{
		ERROR_LOG() << "iType is neither audio nor video.";
		DEBUG_LOG() << "--- LEAVE";
		return UC_InvalidParam;
	}

	UCVoIPAbsProxy* pUCVoIPAbsProxy = UCVoIPAbsProxy::GetInstance();
	CHECK_POINTER(pUCVoIPAbsProxy, UC_NullPoint);

	int iRet = pUCVoIPAbsProxy->UnMute(iType);
	CHECK_RETURN(iRet, UC_Succ, "UnMute");

	DEBUG_LOG() << "--- LEAVE";
	return UC_Succ;
}
