#include "stdafx.h"
#include "UCMeeting.h"
#include "UCMeetingAbsProxy.h"
#include "UCStructCopy.h"
#include "eSDKLog.h"
#include "UCCommon.h"


#pragma comment(linker, "/EXPORT:MakeMeetingGroup=_MakeMeetingGroup@8")
#pragma comment(linker, "/EXPORT:StartMeeting=_StartMeeting@4")
#pragma comment(linker, "/EXPORT:AcceptMeeting=_AcceptMeeting@4")
#pragma comment(linker, "/EXPORT:AddParticipant=_AddParticipant@8")
#pragma comment(linker, "/EXPORT:ConnectParticipant=_ConnectParticipant@8")
#pragma comment(linker, "/EXPORT:RemoveParticipant=_RemoveParticipant@8")
#pragma comment(linker, "/EXPORT:KickParticipant=_KickParticipant@8")
#pragma comment(linker, "/EXPORT:MuteMeeting=_MuteMeeting@8")
#pragma comment(linker, "/EXPORT:UnMuteMeeting=_UnMuteMeeting@8")
#pragma comment(linker, "/EXPORT:GetBookConfList=_GetBookConfList@12")
#pragma comment(linker, "/EXPORT:JoinMeeting=_JoinMeeting@8")
#pragma comment(linker, "/EXPORT:LeaveMeeting=_LeaveMeeting@4")


int UCSDK_CALL MakeMeetingGroup(const UCContactList* memberlist, char convId[CONVID_LENGTH])
{
	DEBUG_LOG() << "--- ENTER";
	CHECK_POINTER(memberlist, UC_InvalidParam);
	CHECK_POINTER(convId, UC_InvalidParam);

	UCMeetingAbsProxy* pUCMeetingAbsProxy = UCMeetingAbsProxy::GetInstance();
	CHECK_POINTER(pUCMeetingAbsProxy, UC_NullPoint);

	UCSDKContactList contactlist;
	UCStructCopy::Copy_UCSDKContactList(contactlist, *memberlist);

	std::string sConvId = convId;
	int iRet = pUCMeetingAbsProxy->MakeMeetingGroup(contactlist, sConvId);
	CHECK_RETURN(iRet, UC_Succ, "MakeMeetingGroup");

	UCStructCopy::UCMemCopy(convId, sConvId, CONVID_LENGTH);

	DEBUG_LOG() << "--- LEAVE";
	return UC_Succ;
}

int UCSDK_CALL StartMeeting(const char* convId)
{
	DEBUG_LOG() << "--- ENTER";
	CHECK_POINTER(convId, UC_InvalidParam);

	UCMeetingAbsProxy* pUCMeetingAbsProxy = UCMeetingAbsProxy::GetInstance();
	CHECK_POINTER(pUCMeetingAbsProxy, UC_NullPoint);

	int iRet = pUCMeetingAbsProxy->StartMeeting(convId);
	CHECK_RETURN(iRet, UC_Succ, "StartMeeting");

	DEBUG_LOG() << "--- LEAVE";
	return UC_Succ;
}

int UCSDK_CALL AcceptMeeting(const char* convId)
{
	DEBUG_LOG() << "--- ENTER";
	CHECK_POINTER(convId, UC_InvalidParam);

	UCMeetingAbsProxy* pUCMeetingAbsProxy = UCMeetingAbsProxy::GetInstance();
	CHECK_POINTER(pUCMeetingAbsProxy, UC_NullPoint);

	int iRet = pUCMeetingAbsProxy->AcceptMeeting(convId);
	CHECK_RETURN(iRet, UC_Succ, "AcceptMeeting");

	DEBUG_LOG() << "--- LEAVE";
	return UC_Succ;
}

int UCSDK_CALL AddParticipant(const UCContact* member, const char* convId)
{
	DEBUG_LOG() << "--- ENTER";
	CHECK_POINTER(member, UC_InvalidParam);
	CHECK_POINTER(convId, UC_InvalidParam);

	UCMeetingAbsProxy* pUCMeetingAbsProxy = UCMeetingAbsProxy::GetInstance();
	CHECK_POINTER(pUCMeetingAbsProxy, UC_NullPoint);

	UCSDKContact contact;
	UCStructCopy::Copy_UCSDKContact(contact, *member);

	int iRet = pUCMeetingAbsProxy->AddParticipant(contact, convId);
	CHECK_RETURN(iRet, UC_Succ, "AddParticipant");

	DEBUG_LOG() << "--- LEAVE";
	return UC_Succ;
}

int UCSDK_CALL ConnectParticipant(const UCContact* member, const char* convId)
{
	DEBUG_LOG() << "--- ENTER";
	CHECK_POINTER(member, UC_InvalidParam);
	CHECK_POINTER(convId, UC_InvalidParam);

	UCMeetingAbsProxy* pUCMeetingAbsProxy = UCMeetingAbsProxy::GetInstance();
	CHECK_POINTER(pUCMeetingAbsProxy, UC_NullPoint);

	UCSDKContact contact;
	UCStructCopy::Copy_UCSDKContact(contact, *member);

	int iRet = pUCMeetingAbsProxy->ConnectParticipant(contact, convId);
	CHECK_RETURN(iRet, UC_Succ, "ConnectParticipant");

	DEBUG_LOG() << "--- LEAVE";
	return UC_Succ;
}

int UCSDK_CALL RemoveParticipant(const UCContact* member, const char* convId)
{
	DEBUG_LOG() << "--- ENTER";
	CHECK_POINTER(member, UC_InvalidParam);
	CHECK_POINTER(convId, UC_InvalidParam);

	UCMeetingAbsProxy* pUCMeetingAbsProxy = UCMeetingAbsProxy::GetInstance();
	CHECK_POINTER(pUCMeetingAbsProxy, UC_NullPoint);

	UCSDKContact contact;
	UCStructCopy::Copy_UCSDKContact(contact, *member);

	int iRet = pUCMeetingAbsProxy->RemoveParticipant(contact, convId);
	CHECK_RETURN(iRet, UC_Succ, "RemoveParticipant");

	DEBUG_LOG() << "--- LEAVE";
	return UC_Succ;
}

int UCSDK_CALL KickParticipant(const UCContact* member, const char* convId)
{
	DEBUG_LOG() << "--- ENTER";
	CHECK_POINTER(member, UC_InvalidParam);
	CHECK_POINTER(convId, UC_InvalidParam);

	UCMeetingAbsProxy* pUCMeetingAbsProxy = UCMeetingAbsProxy::GetInstance();
	CHECK_POINTER(pUCMeetingAbsProxy, UC_NullPoint);

	UCSDKContact contact;
	UCStructCopy::Copy_UCSDKContact(contact, *member);

	int iRet = pUCMeetingAbsProxy->KickParticipant(contact, convId);
	CHECK_RETURN(iRet, UC_Succ, "KickParticipant");

	DEBUG_LOG() << "--- LEAVE";
	return UC_Succ;
}

int UCSDK_CALL MuteMeeting(const UCContact* member, const char* convId)
{
	DEBUG_LOG() << "--- ENTER";
	CHECK_POINTER(member, UC_InvalidParam);
	CHECK_POINTER(convId, UC_InvalidParam);

	UCMeetingAbsProxy* pUCMeetingAbsProxy = UCMeetingAbsProxy::GetInstance();
	CHECK_POINTER(pUCMeetingAbsProxy, UC_NullPoint);

	UCSDKContact contact;
	UCStructCopy::Copy_UCSDKContact(contact, *member);

	int iRet = pUCMeetingAbsProxy->Mute(contact, convId);
	CHECK_RETURN(iRet, UC_Succ, "Mute");

	DEBUG_LOG() << "--- LEAVE";
	return UC_Succ;
}

int UCSDK_CALL UnMuteMeeting(const UCContact* member, const char* convId)
{
	DEBUG_LOG() << "--- ENTER";
	CHECK_POINTER(member, UC_InvalidParam);
	CHECK_POINTER(convId, UC_InvalidParam);

	UCMeetingAbsProxy* pUCMeetingAbsProxy = UCMeetingAbsProxy::GetInstance();
	CHECK_POINTER(pUCMeetingAbsProxy, UC_NullPoint);

	UCSDKContact contact;
	UCStructCopy::Copy_UCSDKContact(contact, *member);

	int iRet = pUCMeetingAbsProxy->UnMute(contact, convId);
	CHECK_RETURN(iRet, UC_Succ, "UnMute");

	DEBUG_LOG() << "--- LEAVE";
	return UC_Succ;
}

int UCSDK_CALL GetBookConfList(int iFrom, int iTo, UCBookConfList* bookConfList)
{
	DEBUG_LOG() << "--- ENTER";
	CHECK_POINTER(bookConfList, UC_InvalidParam);
	if (0 > iFrom || iFrom > iTo)
	{
		INFO_PARAM2(iFrom, iTo);
		ERROR_LOG() << "iFrom or iTo is Invaild praram";
		DEBUG_LOG() << "--- LEAVE";
		return UC_InvalidParam;
	}

	UCMeetingAbsProxy* pUCMeetingAbsProxy = UCMeetingAbsProxy::GetInstance();
	CHECK_POINTER(pUCMeetingAbsProxy, UC_NullPoint);

	UCSDKBookConfList booklist;
	int iRet = pUCMeetingAbsProxy->GetBookConfList(booklist);
	CHECK_RETURN(iRet, UC_Succ, "GetBookConfList");

	int iTotalSize = (int)booklist.size();
	if (iTotalSize > 0 && iFrom > iTotalSize - 1)
	{
		ERROR_LOG() << "iFrom is greater than the total size.";
		DEBUG_LOG() << "--- LEAVE";
		return UC_InvalidParam;
	}
	//booklist.size() == 0 也包括在内
	int iEnd = iTo < (iTotalSize - 1) ? iTo : (iTotalSize - 1);
	for (int i=iFrom; i<=iEnd; i++)
	{
		//！！！bookConfList里面的UCBookConf里面的attendeelist无效，不使用
		UCStructCopy::Copy_UCBookConf(bookConfList->bookConf[i-iFrom], booklist[(unsigned int)i]);
	}
	bookConfList->iFrom = iFrom;
	bookConfList->iTo = iEnd;
	bookConfList->iTotal = iTotalSize;

	DEBUG_LOG() << "--- LEAVE";
	return UC_Succ;
}

int UCSDK_CALL JoinMeeting(const UCBookConf* meetingInfo, char convId[CONVID_LENGTH])
{
	DEBUG_LOG() << "--- ENTER";
	CHECK_POINTER(convId, UC_InvalidParam);
	CHECK_POINTER(meetingInfo, UC_InvalidParam);

	UCMeetingAbsProxy* pUCMeetingAbsProxy = UCMeetingAbsProxy::GetInstance();
	CHECK_POINTER(pUCMeetingAbsProxy, UC_NullPoint);

	UCSDKBookConfInfo bookinfo;
	UCStructCopy::Copy_UCSDKBookConfInfo(bookinfo, *meetingInfo);

	std::string sConvId = convId;
	int iRet = pUCMeetingAbsProxy->JoinMeeting(sConvId, bookinfo);
	CHECK_RETURN(iRet, UC_Succ, "JoinMeeting");

	UCStructCopy::UCMemCopy(convId, sConvId, CONVID_LENGTH);

	DEBUG_LOG() << "--- LEAVE";
	return UC_Succ;
}

int UCSDK_CALL LeaveMeeting(const char* convId)
{
	DEBUG_LOG() << "--- ENTER";
	CHECK_POINTER(convId, UC_InvalidParam);

	UCMeetingAbsProxy* pUCMeetingAbsProxy = UCMeetingAbsProxy::GetInstance();
	CHECK_POINTER(pUCMeetingAbsProxy, UC_NullPoint);

	int iRet = pUCMeetingAbsProxy->LeaveMeeting(convId);
	CHECK_RETURN(iRet, UC_Succ, "LeaveMeeting");

	DEBUG_LOG() << "--- LEAVE";
	return UC_Succ;
}
