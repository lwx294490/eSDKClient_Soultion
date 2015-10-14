#include "stdafx.h"
#include "UCIM.h"
#include "UCIMAbsProxy.h"
#include "UCStructCopy.h"
#include "eSDKLog.h"
#include "UCCommon.h"


#pragma comment(linker, "/EXPORT:SendIMMessage=_SendIMMessage@12")
#pragma comment(linker, "/EXPORT:CloseConversation=_CloseConversation@4")
#pragma comment(linker, "/EXPORT:AcceptFile=_AcceptFile@8")
#pragma comment(linker, "/EXPORT:CancelFile=_CancelFile@4")
#pragma comment(linker, "/EXPORT:RejectFile=_RejectFile@4")
#pragma comment(linker, "/EXPORT:TransferFile=_TransferFile@20")


int UCSDK_CALL SendIMMessage(const char* pMsg, const UCAccountList* accountList, char convId[CONVID_LENGTH])
{
	DEBUG_LOG() << "--- ENTER";
	CHECK_POINTER(pMsg, UC_InvalidParam);
	CHECK_POINTER(accountList, UC_InvalidParam);
	CHECK_POINTER(convId, UC_InvalidParam);

	UCIMAbsProxy* pUCIMAbsProxy = UCIMAbsProxy::GetInstance();
	CHECK_POINTER(pUCIMAbsProxy, UC_NullPoint);

	std::string sConvId = convId;
	AccountList acclist;

	if (sConvId.empty())
	{
		UCStructCopy::Copy_AccountList(acclist, *accountList);
	}	
	int iRet = pUCIMAbsProxy->SendIMMessage(pMsg, acclist, sConvId);
	CHECK_RETURN(iRet, UC_Succ, "SendIMMessage");

	if (0 == strlen(convId))
	{
		UCStructCopy::UCMemCopy(convId, sConvId, CONVID_LENGTH);
	}

	DEBUG_LOG() << "--- LEAVE";
	return UC_Succ;
}

int UCSDK_CALL CloseConversation(const char* convId)
{
	DEBUG_LOG() << "--- ENTER";
	CHECK_POINTER(convId, UC_InvalidParam);

	UCIMAbsProxy* pUCIMAbsProxy = UCIMAbsProxy::GetInstance();
	CHECK_POINTER(pUCIMAbsProxy, UC_NullPoint);

	int iRet = pUCIMAbsProxy->CloseConversation(convId);
	CHECK_RETURN(iRet, UC_Succ, "CloseConversation");

	DEBUG_LOG() << "--- LEAVE";
	return UC_Succ;
}

int UCSDK_CALL AcceptFile(const char* fileId, const char* filePath)
{
	DEBUG_LOG() << "--- ENTER";
	CHECK_POINTER(fileId, UC_InvalidParam);
	CHECK_POINTER(filePath, UC_InvalidParam);

	UCIMAbsProxy* pUCIMAbsProxy = UCIMAbsProxy::GetInstance();
	CHECK_POINTER(pUCIMAbsProxy, UC_NullPoint);

	int iRet = pUCIMAbsProxy->AcceptFile(fileId, filePath);
	CHECK_RETURN(iRet, UC_Succ, "AcceptFile");

	DEBUG_LOG() << "--- LEAVE";
	return UC_Succ;
}

int UCSDK_CALL CancelFile(const char* fileId)
{
	DEBUG_LOG() << "--- ENTER";
	CHECK_POINTER(fileId, UC_InvalidParam);

	UCIMAbsProxy* pUCIMAbsProxy = UCIMAbsProxy::GetInstance();
	CHECK_POINTER(pUCIMAbsProxy, UC_NullPoint);

	int iRet = pUCIMAbsProxy->CancelFile(fileId);
	CHECK_RETURN(iRet, UC_Succ, "CancelFile");

	DEBUG_LOG() << "--- LEAVE";
	return UC_Succ;
}

int UCSDK_CALL RejectFile(const char* fileId)
{
	DEBUG_LOG() << "--- ENTER";
	CHECK_POINTER(fileId, UC_InvalidParam);

	UCIMAbsProxy* pUCIMAbsProxy = UCIMAbsProxy::GetInstance();
	CHECK_POINTER(pUCIMAbsProxy, UC_NullPoint);

	int iRet = pUCIMAbsProxy->RejectFile(fileId);
	CHECK_RETURN(iRet, UC_Succ, "RejectFile");

	DEBUG_LOG() << "--- LEAVE";
	return UC_Succ;
}

int UCSDK_CALL TransferFile(const char* pAcc,const char* filePath,
							const char* transType, int bIsOfflineFile, char fileId[FILEID_LENGTH])
{
	DEBUG_LOG() << "--- ENTER";
	CHECK_POINTER(fileId, UC_InvalidParam);
	CHECK_POINTER(pAcc, UC_InvalidParam);
	CHECK_POINTER(filePath, UC_InvalidParam);
	CHECK_POINTER(transType, UC_InvalidParam);

	UCIMAbsProxy* pUCIMAbsProxy = UCIMAbsProxy::GetInstance();
	CHECK_POINTER(pUCIMAbsProxy, UC_NullPoint);

	bool IsOffline = true;
	if (0 == bIsOfflineFile)
	{
		IsOffline = false;
	}

	std::string sFileId = pUCIMAbsProxy->TransferFile(pAcc, filePath, transType, IsOffline);
	if (sFileId.empty())
	{
		ERROR_LOG() << "TransferFile file failed.";
		DEBUG_LOG() << "--- LEAVE";
		return UC_Fail;
	}

	UCStructCopy::UCMemCopy(fileId, sFileId, FILEID_LENGTH);

	DEBUG_LOG() << "--- LEAVE";
	return UC_Succ;
}
