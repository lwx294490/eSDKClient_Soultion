#include "stdafx.h"
#include "UCSignalRecvProxy.h"
#include "UCCommon.h"
#include "UCStructCopy.h"
#include "eSDKLog.h"
#include "UCSDKAbsProxy.h"


UCSignalRecvProxy* UCSignalRecvProxy::m_pUCSignalRecvProxy = NULL;

UCSignalRecvProxy::UCSignalRecvProxy()
: m_fpClientSignInNotify(NULL)
, m_fpStatusChanged(NULL)
, m_fpIncreContactsChanged(NULL)
, m_fpAVSessAdded(NULL)
, m_fpAVSessionConnected(NULL)
, m_fpAVSessionClosed(NULL)
, m_fpConvMemberStatusChanged(NULL)
, m_fpConvMemAllowSpeak(NULL)
, m_fpConvMemForbidSpeak(NULL)
, m_fpConvMemCurSpeaker(NULL)
, m_fpConvGroupMemberChanged(NULL)
, m_fpReceivedIMMessage(NULL)
, m_fpInstantSessRemoved(NULL)
, m_fpInstantSessAdded(NULL)
, m_fpSysMsgRecved(NULL)
, m_fpGroupInvitation(NULL)
, m_fpGroupInvitationRes(NULL)
, m_fpLeaveFromFixedGroup(NULL)
, m_fpJoinFixedGroupRequest(NULL)
, m_fpJoinFixedGroupRes(NULL)
, m_fpMemberAdded(NULL)
, m_fpMemberRemoved(NULL)
, m_fpMemberFlowChanged(NULL)
, m_fpFixedGroupInfoChanged(NULL)
, m_fpNewFileRercved(NULL)
, m_fpFileAccept(NULL)
, m_fpFileCancel(NULL)
, m_fpFileProgress(NULL)
{

}

UCSignalRecvProxy* UCSignalRecvProxy::Instance()
{
	if (NULL == m_pUCSignalRecvProxy)
	{
		m_pUCSignalRecvProxy = new UCSignalRecvProxy;

		//注册C++回调函数实例
		UCSDKAbsProxy* pUCSDKAbsProxy = UCSDKAbsProxy::GetInstance();
		if (NULL != pUCSDKAbsProxy)
		{
			pUCSDKAbsProxy->SetUCSignalRecvAbsProxy(m_pUCSignalRecvProxy);
		}
	}

	return m_pUCSignalRecvProxy;
}

void UCSignalRecvProxy::Destroy()
{
	if (NULL != m_pUCSignalRecvProxy)
	{
		delete m_pUCSignalRecvProxy;
		m_pUCSignalRecvProxy = NULL;
	}
}

void UCSignalRecvProxy::OnClientSignInNotify(int state, const std::string& reason)
{
	DEBUG_LOG() << "--- ENTER";
	CHECK_POINTER_VOID(m_fpClientSignInNotify);

	m_fpClientSignInNotify(state, reason.c_str());

	DEBUG_LOG() << "--- LEAVE";
}

void UCSignalRecvProxy::OnStatusChanged(CONTACT_AVAILABILITY_E state, const std::string& desc, const UCSDKContact& contact, const std::string& param)
{
	DEBUG_LOG() << "--- ENTER";
	CHECK_POINTER_VOID(m_fpStatusChanged);

	UCContact ucContact;
	memset(&ucContact, 0, sizeof(ucContact));
	UCStructCopy::Copy_UCContact(ucContact, contact);
	m_fpStatusChanged((int)state, desc.c_str(), &ucContact, param.c_str());

	DEBUG_LOG() << "--- LEAVE";
}

void UCSignalRecvProxy::OnIncreContactsChanged(void)
{
	DEBUG_LOG() << "--- ENTER";
	CHECK_POINTER_VOID(m_fpIncreContactsChanged);

	m_fpIncreContactsChanged();

	DEBUG_LOG() << "--- LEAVE";
}

void UCSignalRecvProxy::OnAVSessAdded(const ConversationPropMap& propMap, const AccountList& memberlist, const STAudioVideoParam& avParam)
{
	DEBUG_LOG() << "--- ENTER";
	CHECK_POINTER_VOID(m_fpAVSessAdded);

	UCConversationPropMap ucMap;
	UCAccountList ucList;
	UCAudioVideoParam ucParam;
	memset(&ucMap, 0, sizeof(ucMap));
	memset(&ucList, 0, sizeof(ucList));
	memset(&ucParam, 0, sizeof(ucParam));

	UCStructCopy::Copy_UCConversationPropMap(ucMap, propMap);
	UCStructCopy::Copy_UCAccountList(ucList, memberlist);
	UCStructCopy::Copy_UCAudioVideoParam(ucParam, avParam);

	m_fpAVSessAdded(&ucMap, &ucList, &ucParam);

	UCStructCopy::Free_UCAccountList(ucList);

	DEBUG_LOG() << "--- LEAVE";
}

void UCSignalRecvProxy::OnAVSessionConnected(const std::string& convId)
{
	DEBUG_LOG() << "--- ENTER";
	CHECK_POINTER_VOID(m_fpAVSessionConnected);

	m_fpAVSessionConnected(convId.c_str());

	DEBUG_LOG() << "--- LEAVE";
}

void UCSignalRecvProxy::OnAVSessionClosed(const std::string& convId)
{
	DEBUG_LOG() << "--- ENTER";
	CHECK_POINTER_VOID(m_fpAVSessionClosed);

	m_fpAVSessionClosed(convId.c_str());

	DEBUG_LOG() << "--- LEAVE";
}

void UCSignalRecvProxy::OnConvMemberStatusChanged(const std::string& convId, int chgtype, const std::string& memberuri)
{
	DEBUG_LOG() << "--- ENTER";
	CHECK_POINTER_VOID(m_fpConvMemberStatusChanged);

	m_fpConvMemberStatusChanged(convId.c_str(), chgtype, memberuri.c_str());

	DEBUG_LOG() << "--- LEAVE";
}

void UCSignalRecvProxy::OnConvMemAllowSpeak(const std::string& convId, const UCSDKContact& member)
{
	DEBUG_LOG() << "--- ENTER";
	CHECK_POINTER_VOID(m_fpConvMemAllowSpeak);

	UCContact ucContact;
	memset(&ucContact, 0, sizeof(ucContact));
	UCStructCopy::Copy_UCContact(ucContact, member);
	m_fpConvMemAllowSpeak(convId.c_str(), &ucContact);

	DEBUG_LOG() << "--- LEAVE";
}

void UCSignalRecvProxy::OnConvMemForbidSpeak(const std::string& convId, const UCSDKContact& member)
{
	DEBUG_LOG() << "--- ENTER";
	CHECK_POINTER_VOID(m_fpConvMemForbidSpeak);

	UCContact ucContact;
	memset(&ucContact, 0, sizeof(ucContact));
	UCStructCopy::Copy_UCContact(ucContact, member);
	m_fpConvMemForbidSpeak(convId.c_str(), &ucContact);

	DEBUG_LOG() << "--- LEAVE";
}

void UCSignalRecvProxy::OnConvMemCurSpeaker(const std::string& convId, const UCSDKContact& member)
{
	DEBUG_LOG() << "--- ENTER";
	CHECK_POINTER_VOID(m_fpConvMemCurSpeaker);

	UCContact ucContact;
	memset(&ucContact, 0, sizeof(ucContact));
	UCStructCopy::Copy_UCContact(ucContact, member);
	m_fpConvMemCurSpeaker(convId.c_str(), &ucContact);

	DEBUG_LOG() << "--- LEAVE";
}

void UCSignalRecvProxy::OnConvGroupMemberChanged(const std::string& convId, int chgtype, const std::string& memberuri)
{
	DEBUG_LOG() << "--- ENTER";
	CHECK_POINTER_VOID(m_fpConvGroupMemberChanged);

	m_fpConvGroupMemberChanged(convId.c_str(), chgtype, memberuri.c_str());

	DEBUG_LOG() << "--- LEAVE";
}

void UCSignalRecvProxy::OnReceivedIMMessage(const ConversationPropMap& propMap, const AccountList& memberlist, const IMMessage& ImMessage)
{
	DEBUG_LOG() << "--- ENTER";
	CHECK_POINTER_VOID(m_fpReceivedIMMessage);

	UCConversationPropMap ucMap;
	UCAccountList ucList;
	UCIMMessage ucIM;
	memset(&ucMap, 0, sizeof(ucMap));
	memset(&ucList, 0, sizeof(ucList));
	memset(&ucIM, 0, sizeof(ucIM));

	UCStructCopy::Copy_UCConversationPropMap(ucMap, propMap);
	UCStructCopy::Copy_UCAccountList(ucList, memberlist);
	UCStructCopy::Copy_UCIMMessage(ucIM, ImMessage);

	m_fpReceivedIMMessage(&ucMap, &ucList, &ucIM);

	UCStructCopy::Free_UCAccountList(ucList);

	DEBUG_LOG() << "--- LEAVE";
}

void UCSignalRecvProxy::OnInstantSessRemoved(const std::string& convId)
{
	DEBUG_LOG() << "--- ENTER";
	CHECK_POINTER_VOID(m_fpInstantSessRemoved);

	m_fpInstantSessRemoved(convId.c_str());

	DEBUG_LOG() << "--- LEAVE";
}

void UCSignalRecvProxy::OnInstantSessAdded(const std::string& convId, const UCSDKContact& member)
{
	DEBUG_LOG() << "--- ENTER";
	CHECK_POINTER_VOID(m_fpInstantSessAdded);

	UCContact ucContact;
	memset(&ucContact, 0, sizeof(ucContact));
	UCStructCopy::Copy_UCContact(ucContact, member);
	m_fpInstantSessAdded(convId.c_str(), &ucContact);

	DEBUG_LOG() << "--- LEAVE";
}

void UCSignalRecvProxy::OnSysMsgRecved(const std::string& origin, const std::string& subject, const std::string& content, const std::string& rcv_time, const std::string& msgid, int msgtype)
{
	DEBUG_LOG() << "--- ENTER";
	CHECK_POINTER_VOID(m_fpSysMsgRecved);

	m_fpSysMsgRecved(origin.c_str(), subject.c_str(), content.c_str(), rcv_time.c_str(), msgid.c_str(), msgtype);

	DEBUG_LOG() << "--- LEAVE";
}

void UCSignalRecvProxy::OnGroupInvitation(const UCSDKFixedGroup& fixedGroup)
{
	DEBUG_LOG() << "--- ENTER";
	CHECK_POINTER_VOID(m_fpGroupInvitation);

	UCFixedGroup ucGroup;
	memset(&ucGroup, 0, sizeof(ucGroup));
	UCStructCopy::Copy_UCFixedGroup(ucGroup, fixedGroup);
	m_fpGroupInvitation(&ucGroup);

	DEBUG_LOG() << "--- LEAVE";
}

void UCSignalRecvProxy::OnGroupInvitationRes(const UCSDKFixedGroup& fixedGroup, const std::string& invitername, int result)
{
	DEBUG_LOG() << "--- ENTER";
	CHECK_POINTER_VOID(m_fpGroupInvitationRes);

	UCFixedGroup ucGroup;
	memset(&ucGroup, 0, sizeof(ucGroup));
	UCStructCopy::Copy_UCFixedGroup(ucGroup, fixedGroup);
	m_fpGroupInvitationRes(&ucGroup, invitername.c_str(), result);

	DEBUG_LOG() << "--- LEAVE";
}

void UCSignalRecvProxy::OnLeaveFromFixedGroup(const UCSDKFixedGroup& fixedGroup, int reason)
{
	DEBUG_LOG() << "--- ENTER";
	CHECK_POINTER_VOID(m_fpLeaveFromFixedGroup);

	UCFixedGroup ucGroup;
	memset(&ucGroup, 0, sizeof(ucGroup));
	UCStructCopy::Copy_UCFixedGroup(ucGroup, fixedGroup);
	m_fpLeaveFromFixedGroup(&ucGroup, reason);

	DEBUG_LOG() << "--- LEAVE";
}

void UCSignalRecvProxy::OnJoinFixedGroupRequest(const UCSDKFixedGroup& fixedGroup, const std::string& inviteruri)
{
	DEBUG_LOG() << "--- ENTER";
	CHECK_POINTER_VOID(m_fpJoinFixedGroupRequest);

	UCFixedGroup ucGroup;
	memset(&ucGroup, 0, sizeof(ucGroup));
	UCStructCopy::Copy_UCFixedGroup(ucGroup, fixedGroup);
	m_fpJoinFixedGroupRequest(&ucGroup, inviteruri.c_str());

	DEBUG_LOG() << "--- LEAVE";
}

void UCSignalRecvProxy::OnJoinFixedGroupRes(const UCSDKFixedGroup& fixedGroup, const std::string& invitername, int result)
{
	DEBUG_LOG() << "--- ENTER";
	CHECK_POINTER_VOID(m_fpJoinFixedGroupRes);

	UCFixedGroup ucGroup;
	memset(&ucGroup, 0, sizeof(ucGroup));
	UCStructCopy::Copy_UCFixedGroup(ucGroup, fixedGroup);
	m_fpJoinFixedGroupRes(&ucGroup, invitername.c_str(), result);

	DEBUG_LOG() << "--- LEAVE";
}

void UCSignalRecvProxy::OnMemberAdded(const UCSDKFixedGroup& fixedGroup, const UCSDKContact& member)
{
	DEBUG_LOG() << "--- ENTER";
	CHECK_POINTER_VOID(m_fpMemberAdded);

	UCFixedGroup ucGroup;
	UCContact ucContact;
	memset(&ucGroup, 0, sizeof(ucGroup));
	memset(&ucContact, 0, sizeof(ucContact));

	UCStructCopy::Copy_UCFixedGroup(ucGroup, fixedGroup);
	UCStructCopy::Copy_UCContact(ucContact, member);

	m_fpMemberAdded(&ucGroup, &ucContact);

	DEBUG_LOG() << "--- LEAVE";
}

void UCSignalRecvProxy::OnMemberRemoved(const UCSDKFixedGroup& fixedGroup, const UCSDKContact& member)
{
	DEBUG_LOG() << "--- ENTER";
	CHECK_POINTER_VOID(m_fpMemberRemoved);

	UCFixedGroup ucGroup;
	UCContact ucContact;
	memset(&ucGroup, 0, sizeof(ucGroup));
	memset(&ucContact, 0, sizeof(ucContact));

	UCStructCopy::Copy_UCFixedGroup(ucGroup, fixedGroup);
	UCStructCopy::Copy_UCContact(ucContact, member);

	m_fpMemberRemoved(&ucGroup, &ucContact);

	DEBUG_LOG() << "--- LEAVE";
}

void UCSignalRecvProxy::OnMemberFlowChanged(const UCSDKFixedGroup& fixedGroup, const UCSDKContact& member)
{
	DEBUG_LOG() << "--- ENTER";
	CHECK_POINTER_VOID(m_fpMemberFlowChanged);

	UCFixedGroup ucGroup;
	UCContact ucContact;
	memset(&ucGroup, 0, sizeof(ucGroup));
	memset(&ucContact, 0, sizeof(ucContact));

	UCStructCopy::Copy_UCFixedGroup(ucGroup, fixedGroup);
	UCStructCopy::Copy_UCContact(ucContact, member);

	m_fpMemberFlowChanged(&ucGroup, &ucContact);

	DEBUG_LOG() << "--- LEAVE";
}

void UCSignalRecvProxy::OnFixedGroupInfoChanged(const UCSDKFixedGroup& fixedGroup)
{
	DEBUG_LOG() << "--- ENTER";
	CHECK_POINTER_VOID(m_fpFixedGroupInfoChanged);

	UCFixedGroup ucGroup;
	memset(&ucGroup, 0, sizeof(ucGroup));
	UCStructCopy::Copy_UCFixedGroup(ucGroup, fixedGroup);
	m_fpFixedGroupInfoChanged(&ucGroup);

	DEBUG_LOG() << "--- LEAVE";
}

void UCSignalRecvProxy::OnNewFileRercved(const std::string& fileid, const std::string& filename, int filesize, const std::string& originName)
{
	DEBUG_LOG() << "--- ENTER";
	CHECK_POINTER_VOID(m_fpNewFileRercved);

	m_fpNewFileRercved(fileid.c_str(), filename.c_str(), filesize, originName.c_str());

	DEBUG_LOG() << "--- LEAVE";
}

void UCSignalRecvProxy::OnFileAccept(const std::string& fileid)
{
	DEBUG_LOG() << "--- ENTER";
	CHECK_POINTER_VOID(m_fpFileAccept);

	m_fpFileAccept(fileid.c_str());

	DEBUG_LOG() << "--- LEAVE";
}
void UCSignalRecvProxy::OnFileCancel(const std::string& fileid, const std::string& reason, const std::string& errcode)
{
	DEBUG_LOG() << "--- ENTER";
	CHECK_POINTER_VOID(m_fpFileCancel);

	m_fpFileCancel(fileid.c_str(), reason.c_str(), errcode.c_str());

	DEBUG_LOG() << "--- LEAVE";
}

void UCSignalRecvProxy::OnFileProgress(const std::string& fileid, const std::string& procent)
{
	DEBUG_LOG() << "--- ENTER";
	CHECK_POINTER_VOID(m_fpFileProgress);

	m_fpFileProgress(fileid.c_str(), procent.c_str());

	DEBUG_LOG() << "--- LEAVE";
}
