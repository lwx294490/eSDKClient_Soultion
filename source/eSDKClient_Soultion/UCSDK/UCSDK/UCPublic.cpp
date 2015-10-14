#include "stdafx.h"
#include "UCPublic.h"
#include "UCPublicAbsProxy.h"
#include "UCStructCopy.h"
#include "eSDKLog.h"
#include "UCCommon.h"


#pragma comment(linker, "/EXPORT:PublishSelfInformation=_PublishSelfInformation@4")
#pragma comment(linker, "/EXPORT:GetContactStatus=_GetContactStatus@8")


int UCSDK_CALL PublishSelfInformation(const UCPublishInfoMap* publishInfoMap)
{
	DEBUG_LOG() << "--- ENTER";

	CHECK_POINTER(publishInfoMap, UC_InvalidParam);

	UCPublicAbsProxy* pUCPublicAbsProxy = UCPublicAbsProxy::GetInstance();
	CHECK_POINTER(pUCPublicAbsProxy, UC_NullPoint);

	PublishInfoMap pubinfo;
	UCStructCopy::Copy_PublishInfoMap(pubinfo, *publishInfoMap);
	
	int iRet = pUCPublicAbsProxy->PublishSelfInformation(pubinfo);
	CHECK_RETURN(iRet, UC_Succ, "PublishSelfInformation");

	DEBUG_LOG() << "--- LEAVE";
	return UC_Succ;
}

int UCSDK_CALL GetContactStatus(const char* _uri, int* _status)
{
	DEBUG_LOG() << "--- ENTER";

	CHECK_POINTER(_uri, UC_InvalidParam);
	CHECK_POINTER(_status, UC_InvalidParam);

	UCPublicAbsProxy* pUCPublicAbsProxy = UCPublicAbsProxy::GetInstance();
	CHECK_POINTER(pUCPublicAbsProxy, UC_NullPoint);

	int iRet = pUCPublicAbsProxy->GetContactStatus(_uri, *_status);
	CHECK_RETURN(iRet, UC_Succ, "GetContactStatus");

	DEBUG_LOG() << "--- LEAVE";
	return UC_Succ;
}
