#include "stdafx.h"
#include "UCSignalRecv.h"
#include "UCSignalRecvProxy.h"
#include "UCCommon.h"
#include "eSDKLog.h"


#pragma comment(linker, "/EXPORT:OnClientSignInNotify=_OnClientSignInNotify@4")
#pragma comment(linker, "/EXPORT:OnStatusChanged=_OnStatusChanged@4")
#pragma comment(linker, "/EXPORT:OnIncreContactsChanged=_OnIncreContactsChanged@4")
#pragma comment(linker, "/EXPORT:OnAVSessAdded=_OnAVSessAdded@4")
#pragma comment(linker, "/EXPORT:OnAVSessionConnected=_OnAVSessionConnected@4")
#pragma comment(linker, "/EXPORT:OnAVSessionClosed=_OnAVSessionClosed@4")
#pragma comment(linker, "/EXPORT:OnConvMemberStatusChanged=_OnConvMemberStatusChanged@4")
#pragma comment(linker, "/EXPORT:OnConvMemAllowSpeak=_OnConvMemAllowSpeak@4")
#pragma comment(linker, "/EXPORT:OnConvMemForbidSpeak=_OnConvMemForbidSpeak@4")
#pragma comment(linker, "/EXPORT:OnConvMemCurSpeaker=_OnConvMemCurSpeaker@4")
#pragma comment(linker, "/EXPORT:OnConvGroupMemberChanged=_OnConvGroupMemberChanged@4")
#pragma comment(linker, "/EXPORT:OnReceivedIMMessage=_OnReceivedIMMessage@4")
#pragma comment(linker, "/EXPORT:OnInstantSessRemoved=_OnInstantSessRemoved@4")
#pragma comment(linker, "/EXPORT:OnInstantSessRemoved=_OnInstantSessRemoved@4")
#pragma comment(linker, "/EXPORT:OnInstantSessAdded=_OnInstantSessAdded@4")
#pragma comment(linker, "/EXPORT:OnSysMsgRecved=_OnSysMsgRecved@4")
#pragma comment(linker, "/EXPORT:OnGroupInvitation=_OnGroupInvitation@4")
#pragma comment(linker, "/EXPORT:OnGroupInvitationRes=_OnGroupInvitationRes@4")
#pragma comment(linker, "/EXPORT:OnLeaveFromFixedGroup=_OnLeaveFromFixedGroup@4")
#pragma comment(linker, "/EXPORT:OnJoinFixedGroupRequest=_OnJoinFixedGroupRequest@4")
#pragma comment(linker, "/EXPORT:OnJoinFixedGroupRes=_OnJoinFixedGroupRes@4")
#pragma comment(linker, "/EXPORT:OnMemberAdded=_OnMemberAdded@4")
#pragma comment(linker, "/EXPORT:OnMemberRemoved=_OnMemberRemoved@4")
#pragma comment(linker, "/EXPORT:OnMemberFlowChanged=_OnMemberFlowChanged@4")
#pragma comment(linker, "/EXPORT:OnFixedGroupInfoChanged=_OnFixedGroupInfoChanged@4")
#pragma comment(linker, "/EXPORT:OnNewFileRercved=_OnNewFileRercved@4")
#pragma comment(linker, "/EXPORT:OnFileAccept=_OnFileAccept@4")
#pragma comment(linker, "/EXPORT:OnFileCancel=_OnFileCancel@4")
#pragma comment(linker, "/EXPORT:OnFileProgress=_OnFileProgress@4")


int UCSDK_CALL OnClientSignInNotify(const UCClientSignInNotify fpClientSignInNotify)
{
	DEBUG_LOG() << "--- ENTER";

	CHECK_POINTER(fpClientSignInNotify, UC_InvalidParam);
	UCSignalRecvProxy* pUCSignalRecvProxy = UCSignalRecvProxy::Instance();
	CHECK_POINTER(pUCSignalRecvProxy, UC_Fail);

	pUCSignalRecvProxy->m_fpClientSignInNotify = fpClientSignInNotify;

	DEBUG_LOG() << "--- LEAVE";
	return UC_Succ;
}

int UCSDK_CALL OnStatusChanged(const UCStatusChanged fpUCStatusChanged)
{
	DEBUG_LOG() << "--- ENTER";

	CHECK_POINTER(fpUCStatusChanged, UC_InvalidParam);
	UCSignalRecvProxy* pUCSignalRecvProxy = UCSignalRecvProxy::Instance();
	CHECK_POINTER(pUCSignalRecvProxy, UC_Fail);

	pUCSignalRecvProxy->m_fpStatusChanged = fpUCStatusChanged;

	DEBUG_LOG() << "--- LEAVE";
	return UC_Succ;
}

int UCSDK_CALL OnIncreContactsChanged(const UCIncreContactsChanged fpIncreContactsChanged)
{
	DEBUG_LOG() << "--- ENTER";

	CHECK_POINTER(fpIncreContactsChanged, UC_InvalidParam);
	UCSignalRecvProxy* pUCSignalRecvProxy = UCSignalRecvProxy::Instance();
	CHECK_POINTER(pUCSignalRecvProxy, UC_Fail);

	pUCSignalRecvProxy->m_fpIncreContactsChanged = fpIncreContactsChanged;

	DEBUG_LOG() << "--- LEAVE";
	return UC_Succ;
}

int UCSDK_CALL OnAVSessAdded(const UCAVSessAdded fpAVSessAdded)
{
	DEBUG_LOG() << "--- ENTER";

	CHECK_POINTER(fpAVSessAdded, UC_InvalidParam);
	UCSignalRecvProxy* pUCSignalRecvProxy = UCSignalRecvProxy::Instance();
	CHECK_POINTER(pUCSignalRecvProxy, UC_Fail);

	pUCSignalRecvProxy->m_fpAVSessAdded = fpAVSessAdded;

	DEBUG_LOG() << "--- LEAVE";
	return UC_Succ;
}

int UCSDK_CALL OnAVSessionConnected(const UCAVSessionConnected fpAVSessionConnected)
{
	DEBUG_LOG() << "--- ENTER";

	CHECK_POINTER(fpAVSessionConnected, UC_InvalidParam);
	UCSignalRecvProxy* pUCSignalRecvProxy = UCSignalRecvProxy::Instance();
	CHECK_POINTER(pUCSignalRecvProxy, UC_Fail);

	pUCSignalRecvProxy->m_fpAVSessionConnected = fpAVSessionConnected;

	DEBUG_LOG() << "--- LEAVE";
	return UC_Succ;
}

int UCSDK_CALL OnAVSessionClosed(const UCAVSessionClosed fpAVSessionClosed)
{
	DEBUG_LOG() << "--- ENTER";

	CHECK_POINTER(fpAVSessionClosed, UC_InvalidParam);
	UCSignalRecvProxy* pUCSignalRecvProxy = UCSignalRecvProxy::Instance();
	CHECK_POINTER(pUCSignalRecvProxy, UC_Fail);

	pUCSignalRecvProxy->m_fpAVSessionClosed = fpAVSessionClosed;

	DEBUG_LOG() << "--- LEAVE";
	return UC_Succ;
}

int UCSDK_CALL OnConvMemberStatusChanged(const UCConvMemberStatusChanged fpConvMemberStatusChanged)
{
	DEBUG_LOG() << "--- ENTER";

	CHECK_POINTER(fpConvMemberStatusChanged, UC_InvalidParam);
	UCSignalRecvProxy* pUCSignalRecvProxy = UCSignalRecvProxy::Instance();
	CHECK_POINTER(pUCSignalRecvProxy, UC_Fail);

	pUCSignalRecvProxy->m_fpConvMemberStatusChanged = fpConvMemberStatusChanged;

	DEBUG_LOG() << "--- LEAVE";
	return UC_Succ;
}

int UCSDK_CALL OnConvMemAllowSpeak(const UCConvMemAllowSpeak fpConvMemAllowSpeak)
{
	DEBUG_LOG() << "--- ENTER";

	CHECK_POINTER(fpConvMemAllowSpeak, UC_InvalidParam);
	UCSignalRecvProxy* pUCSignalRecvProxy = UCSignalRecvProxy::Instance();
	CHECK_POINTER(pUCSignalRecvProxy, UC_Fail);

	pUCSignalRecvProxy->m_fpConvMemAllowSpeak = fpConvMemAllowSpeak;

	DEBUG_LOG() << "--- LEAVE";
	return UC_Succ;
}

int UCSDK_CALL OnConvMemForbidSpeak(const UCConvMemForbidSpeak fpConvMemForbidSpeak)
{
	DEBUG_LOG() << "--- ENTER";

	CHECK_POINTER(fpConvMemForbidSpeak, UC_InvalidParam);
	UCSignalRecvProxy* pUCSignalRecvProxy = UCSignalRecvProxy::Instance();
	CHECK_POINTER(pUCSignalRecvProxy, UC_Fail);

	pUCSignalRecvProxy->m_fpConvMemForbidSpeak = fpConvMemForbidSpeak;

	DEBUG_LOG() << "--- LEAVE";
	return UC_Succ;
}

int UCSDK_CALL OnConvMemCurSpeaker(const UCConvMemCurSpeaker fpConvMemCurSpeaker)
{
	DEBUG_LOG() << "--- ENTER";

	CHECK_POINTER(fpConvMemCurSpeaker, UC_InvalidParam);
	UCSignalRecvProxy* pUCSignalRecvProxy = UCSignalRecvProxy::Instance();
	CHECK_POINTER(pUCSignalRecvProxy, UC_Fail);

	pUCSignalRecvProxy->m_fpConvMemCurSpeaker = fpConvMemCurSpeaker;

	DEBUG_LOG() << "--- LEAVE";
	return UC_Succ;
}

int UCSDK_CALL OnConvGroupMemberChanged(const UCConvGroupMemberChanged fpConvGroupMemberChanged)
{
	DEBUG_LOG() << "--- ENTER";

	CHECK_POINTER(fpConvGroupMemberChanged, UC_InvalidParam);
	UCSignalRecvProxy* pUCSignalRecvProxy = UCSignalRecvProxy::Instance();
	CHECK_POINTER(pUCSignalRecvProxy, UC_Fail);

	pUCSignalRecvProxy->m_fpConvGroupMemberChanged = fpConvGroupMemberChanged;

	DEBUG_LOG() << "--- LEAVE";
	return UC_Succ;
}

int UCSDK_CALL OnReceivedIMMessage(const UCReceivedIMMessage fpReceivedIMMessage)
{
	DEBUG_LOG() << "--- ENTER";

	CHECK_POINTER(fpReceivedIMMessage, UC_InvalidParam);
	UCSignalRecvProxy* pUCSignalRecvProxy = UCSignalRecvProxy::Instance();
	CHECK_POINTER(pUCSignalRecvProxy, UC_Fail);

	pUCSignalRecvProxy->m_fpReceivedIMMessage = fpReceivedIMMessage;

	DEBUG_LOG() << "--- LEAVE";
	return UC_Succ;
}

int UCSDK_CALL OnInstantSessRemoved(const UCInstantSessRemoved fpInstantSessRemoved)
{
	DEBUG_LOG() << "--- ENTER";

	CHECK_POINTER(fpInstantSessRemoved, UC_InvalidParam);
	UCSignalRecvProxy* pUCSignalRecvProxy = UCSignalRecvProxy::Instance();
	CHECK_POINTER(pUCSignalRecvProxy, UC_Fail);

	pUCSignalRecvProxy->m_fpInstantSessRemoved = fpInstantSessRemoved;

	DEBUG_LOG() << "--- LEAVE";
	return UC_Succ;
}

int UCSDK_CALL OnInstantSessAdded(const UCInstantSessAdded fpInstantSessAdded)
{
	DEBUG_LOG() << "--- ENTER";

	CHECK_POINTER(fpInstantSessAdded, UC_InvalidParam);
	UCSignalRecvProxy* pUCSignalRecvProxy = UCSignalRecvProxy::Instance();
	CHECK_POINTER(pUCSignalRecvProxy, UC_Fail);

	pUCSignalRecvProxy->m_fpInstantSessAdded = fpInstantSessAdded;

	DEBUG_LOG() << "--- LEAVE";
	return UC_Succ;
}

int UCSDK_CALL OnSysMsgRecved(const UCSysMsgRecved fpSysMsgRecved)
{
	DEBUG_LOG() << "--- ENTER";

	CHECK_POINTER(fpSysMsgRecved, UC_InvalidParam);
	UCSignalRecvProxy* pUCSignalRecvProxy = UCSignalRecvProxy::Instance();
	CHECK_POINTER(pUCSignalRecvProxy, UC_Fail);

	pUCSignalRecvProxy->m_fpSysMsgRecved = fpSysMsgRecved;

	DEBUG_LOG() << "--- LEAVE";
	return UC_Succ;
}

int UCSDK_CALL OnGroupInvitation(const UCGroupInvitation fpGroupInvitation)
{
	DEBUG_LOG() << "--- ENTER";

	CHECK_POINTER(fpGroupInvitation, UC_InvalidParam);
	UCSignalRecvProxy* pUCSignalRecvProxy = UCSignalRecvProxy::Instance();
	CHECK_POINTER(pUCSignalRecvProxy, UC_Fail);

	pUCSignalRecvProxy->m_fpGroupInvitation = fpGroupInvitation;

	DEBUG_LOG() << "--- LEAVE";
	return UC_Succ;
}

int UCSDK_CALL OnGroupInvitationRes(const UCGroupInvitationRes fpGroupInvitationRes)
{
	DEBUG_LOG() << "--- ENTER";

	CHECK_POINTER(fpGroupInvitationRes, UC_InvalidParam);
	UCSignalRecvProxy* pUCSignalRecvProxy = UCSignalRecvProxy::Instance();
	CHECK_POINTER(pUCSignalRecvProxy, UC_Fail);

	pUCSignalRecvProxy->m_fpGroupInvitationRes = fpGroupInvitationRes;

	DEBUG_LOG() << "--- LEAVE";
	return UC_Succ;
}

int UCSDK_CALL OnLeaveFromFixedGroup(const UCLeaveFromFixedGroup fpLeaveFromFixedGroup)
{
	DEBUG_LOG() << "--- ENTER";

	CHECK_POINTER(fpLeaveFromFixedGroup, UC_InvalidParam);
	UCSignalRecvProxy* pUCSignalRecvProxy = UCSignalRecvProxy::Instance();
	CHECK_POINTER(pUCSignalRecvProxy, UC_Fail);

	pUCSignalRecvProxy->m_fpLeaveFromFixedGroup = fpLeaveFromFixedGroup;

	DEBUG_LOG() << "--- LEAVE";
	return UC_Succ;
}

int UCSDK_CALL OnJoinFixedGroupRequest(const UCJoinFixedGroupRequest fpJoinFixedGroupRequest)
{
	DEBUG_LOG() << "--- ENTER";

	CHECK_POINTER(fpJoinFixedGroupRequest, UC_InvalidParam);
	UCSignalRecvProxy* pUCSignalRecvProxy = UCSignalRecvProxy::Instance();
	CHECK_POINTER(pUCSignalRecvProxy, UC_Fail);

	pUCSignalRecvProxy->m_fpJoinFixedGroupRequest = fpJoinFixedGroupRequest;

	DEBUG_LOG() << "--- LEAVE";
	return UC_Succ;
}

int UCSDK_CALL OnJoinFixedGroupRes(const UCJoinFixedGroupRes fpJoinFixedGroupRes)
{
	DEBUG_LOG() << "--- ENTER";

	CHECK_POINTER(fpJoinFixedGroupRes, UC_InvalidParam);
	UCSignalRecvProxy* pUCSignalRecvProxy = UCSignalRecvProxy::Instance();
	CHECK_POINTER(pUCSignalRecvProxy, UC_Fail);

	pUCSignalRecvProxy->m_fpJoinFixedGroupRes = fpJoinFixedGroupRes;

	DEBUG_LOG() << "--- LEAVE";
	return UC_Succ;
}

int UCSDK_CALL OnMemberAdded(const UCMemberAdded fpMemberAdded)
{
	DEBUG_LOG() << "--- ENTER";

	CHECK_POINTER(fpMemberAdded, UC_InvalidParam);
	UCSignalRecvProxy* pUCSignalRecvProxy = UCSignalRecvProxy::Instance();
	CHECK_POINTER(pUCSignalRecvProxy, UC_Fail);

	pUCSignalRecvProxy->m_fpMemberAdded = fpMemberAdded;

	DEBUG_LOG() << "--- LEAVE";
	return UC_Succ;
}

int UCSDK_CALL OnMemberRemoved(const UCMemberRemoved fpMemberRemoved)
{
	DEBUG_LOG() << "--- ENTER";

	CHECK_POINTER(fpMemberRemoved, UC_InvalidParam);
	UCSignalRecvProxy* pUCSignalRecvProxy = UCSignalRecvProxy::Instance();
	CHECK_POINTER(pUCSignalRecvProxy, UC_Fail);

	pUCSignalRecvProxy->m_fpMemberRemoved = fpMemberRemoved;

	DEBUG_LOG() << "--- LEAVE";
	return UC_Succ;
}

int UCSDK_CALL OnMemberFlowChanged(const UCMemberFlowChanged fpMemberFlowChanged)
{
	DEBUG_LOG() << "--- ENTER";

	CHECK_POINTER(fpMemberFlowChanged, UC_InvalidParam);
	UCSignalRecvProxy* pUCSignalRecvProxy = UCSignalRecvProxy::Instance();
	CHECK_POINTER(pUCSignalRecvProxy, UC_Fail);

	pUCSignalRecvProxy->m_fpMemberFlowChanged = fpMemberFlowChanged;

	DEBUG_LOG() << "--- LEAVE";
	return UC_Succ;
}

int UCSDK_CALL OnFixedGroupInfoChanged(const UCFixedGroupInfoChanged fpFixedGroupInfoChanged)
{
	DEBUG_LOG() << "--- ENTER";

	CHECK_POINTER(fpFixedGroupInfoChanged, UC_InvalidParam);
	UCSignalRecvProxy* pUCSignalRecvProxy = UCSignalRecvProxy::Instance();
	CHECK_POINTER(pUCSignalRecvProxy, UC_Fail);

	pUCSignalRecvProxy->m_fpFixedGroupInfoChanged = fpFixedGroupInfoChanged;

	DEBUG_LOG() << "--- LEAVE";
	return UC_Succ;
}

int UCSDK_CALL OnNewFileRercved(const UCNewFileRercved fpNewFileRercved)
{
	DEBUG_LOG() << "--- ENTER";

	CHECK_POINTER(fpNewFileRercved, UC_InvalidParam);
	UCSignalRecvProxy* pUCSignalRecvProxy = UCSignalRecvProxy::Instance();
	CHECK_POINTER(pUCSignalRecvProxy, UC_Fail);

	pUCSignalRecvProxy->m_fpNewFileRercved = fpNewFileRercved;

	DEBUG_LOG() << "--- LEAVE";
	return UC_Succ;
}

int UCSDK_CALL OnFileAccept(const UCFileAccept fpFileAccept)
{
	DEBUG_LOG() << "--- ENTER";

	CHECK_POINTER(fpFileAccept, UC_InvalidParam);
	UCSignalRecvProxy* pUCSignalRecvProxy = UCSignalRecvProxy::Instance();
	CHECK_POINTER(pUCSignalRecvProxy, UC_Fail);

	pUCSignalRecvProxy->m_fpFileAccept = fpFileAccept;

	DEBUG_LOG() << "--- LEAVE";
	return UC_Succ;
}

int UCSDK_CALL OnFileCancel(const UCFileCancel fpFileCancel)
{
	DEBUG_LOG() << "--- ENTER";

	CHECK_POINTER(fpFileCancel, UC_InvalidParam);
	UCSignalRecvProxy* pUCSignalRecvProxy = UCSignalRecvProxy::Instance();
	CHECK_POINTER(pUCSignalRecvProxy, UC_Fail);

	pUCSignalRecvProxy->m_fpFileCancel = fpFileCancel;

	DEBUG_LOG() << "--- LEAVE";
	return UC_Succ;
}

int UCSDK_CALL OnFileProgress(const UCFileProgress fpFileProgress)
{
	DEBUG_LOG() << "--- ENTER";

	CHECK_POINTER(fpFileProgress, UC_InvalidParam);
	UCSignalRecvProxy* pUCSignalRecvProxy = UCSignalRecvProxy::Instance();
	CHECK_POINTER(pUCSignalRecvProxy, UC_Fail);

	pUCSignalRecvProxy->m_fpFileProgress = fpFileProgress;

	DEBUG_LOG() << "--- LEAVE";
	return UC_Succ;
}
