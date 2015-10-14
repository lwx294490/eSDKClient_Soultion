//lint -e1762
#include "stdafx.h"
#include "UCMessageSignalProcess.h"
#include "UCMeetingProxy.h"
#include "UCContactMgrProxy.h"
#include "UCVoIPProxy.h"
#include "UCGroupProxy.h"
#include "UCSDK.h"
#include "eSDKLog.h"
#include "UCCommon.h"

namespace eSDK {
	namespace UC {


UCMessageSignalProcess::UCMessageSignalProcess()
	: m_pUCSignalRecvAbsProxy(NULL)
{

}

UCMessageSignalProcess::~UCMessageSignalProcess()
{
	m_pUCSignalRecvAbsProxy = NULL;
}

void UCMessageSignalProcess::OnSignInNotify(UCClient::SignInState _state, std::string _reason)
{
	DEBUG_LOG() << "--- ENTER";	

	UCVoIPProxy* pUCVoIPProxy = UCVoIPProxy::Instance();
	CHECK_POINTER_VOID(pUCVoIPProxy);

#ifdef ESDKCLIENT_PLATFORM_DEPEND
	UCSDK* pUCSDK = UCSDK::CreateInstance();
	CHECK_POINTER_VOID(pUCSDK)
#else
	UCSDK* pUCSDK = UCSDK::Instance();
	CHECK_POINTER_VOID(pUCSDK)
#endif

	if (UCClient::Client_SignedIn == _state)
	{
		//登陆成功后初始化联系人和设备
		(void)pUCVoIPProxy->DeviceMgrInit();
		pUCSDK->InitSubContactlist();

		//关联信号
		(void)pUCSDK->ConnectAVSess();
		(void)pUCSDK->ConnectInstantMessage();
		(void)pUCSDK->ConnectGroup();
	}
	else
	{
		(void)pUCVoIPProxy->DeviceMgrUnInit();
		pUCSDK->DisConnectAll();
		pUCSDK->UninitContactSub();
	}

#ifdef ESDKCLIENT_PLATFORM_DEPEND
	pUCSDK->SetSignEvent((int)_state, _reason);
#endif

	CHECK_POINTER_VOID(m_pUCSignalRecvAbsProxy);

	DEBUG_LOG() << "SignInNotify callback --- ENTER.";
	m_pUCSignalRecvAbsProxy->OnClientSignInNotify(_state, _reason);
	DEBUG_LOG() << "SignInNotify callback --- LEAVE.";

	DEBUG_LOG() << "--- LEAVE";
}

void UCMessageSignalProcess::OnStatusChanged(ContactAvailability _state,std::string _desc,const Contact& _contact, std::string _param)
{
	DEBUG_LOG() << "--- ENTER";

	CHECK_POINTER_VOID(m_pUCSignalRecvAbsProxy);

	UCSDKContact member;
	UCContactMgrProxy::CopyContactToUCSDKContact(_contact, member);
	DEBUG_LOG() << "StatusChanged callback --- ENTER.";
	m_pUCSignalRecvAbsProxy->OnStatusChanged((CONTACT_AVAILABILITY_E)_state, _desc, member, _param);
	DEBUG_LOG() << "StatusChanged callback --- LEAVE.";

	DEBUG_LOG() << "--- LEAVE";
}

void UCMessageSignalProcess::OnIncreContactsChanged(std::string /*param*/)
{
	DEBUG_LOG() << "--- ENTER";

	CHECK_POINTER_VOID(m_pUCSignalRecvAbsProxy);

	DEBUG_LOG() << "IncreContactsChanged callback --- ENTER.";
	m_pUCSignalRecvAbsProxy->OnIncreContactsChanged();
	DEBUG_LOG() << "IncreContactsChanged callback --- LEAVE.";

	DEBUG_LOG() << "--- LEAVE";
}

void UCMessageSignalProcess::OnAVSessionRinged(conversation::Conversation* /*_con*/)
{
	return;
}//lint !e1762

void UCMessageSignalProcess::OnAVSessAdded(conversation::Conversation* _con,  conversation::sAudioVideoParam _param)
{
	DEBUG_LOG() << "--- ENTER";

	CHECK_POINTER_VOID(_con);
	CHECK_POINTER_VOID(m_pUCSignalRecvAbsProxy);
	INFO_PARAM3(_param.caller_, _param.isdataconf_, _param.isvideo_);

	STAudioVideoParam avParam;
	avParam.caller_			= _param.caller_;
	avParam.callername_		= _param.callername_;
	avParam.callalertinfo_	= _param.callalertinfo_;
	avParam.autoanswerdelay = _param.autoanswerdelay;
	avParam.lineindex_		= _param.lineindex_;
	avParam.isvideo_		= _param.isvideo_;
	avParam.callmode_		= _param.callmode_;
	avParam.isdataconf_		= _param.isdataconf_;

	ConversationPropMap propMap;
	conversation::Conversation::ConvProperties_::iterator it_b = _con->propmap_.begin();
	conversation::Conversation::ConvProperties_::iterator it_e = _con->propmap_.end();
	for (; it_b != it_e; it_b++)
	{
		(void)propMap.insert(std::make_pair((CONVERSATION_PROPERTY_E)it_b->first, it_b->second));
	}

	UCContactMgrProxy* pUCContactMgrProxy = UCContactMgrProxy::Instance();
	if (NULL == pUCContactMgrProxy)
	{
		ERROR_LOG() << "Get UCContactMgrProxy instance failed.";
		DEBUG_LOG() << "--- LEAVE";
		return;
	}
	AccountList memlist;//来电用户列表，如果是会议则把会议主持人放在memlist的index为0的位置
	conversation::Conversation::MemList_::iterator iter_b = _con->members_.begin();
	conversation::Conversation::MemList_::iterator iter_e = _con->members_.end();
	for (; iter_b != iter_e; iter_b++)
	{
		Participant* part = iter_b->second;
		if ("1" == part->propmap_[conversation::ParIsLeader])
		{
			Contact contact;
			int iRet = pUCContactMgrProxy->GetContactByUri(contact, part->contact_.uri_);
			CHECK_RETURN_VOID(iRet, UCSDK_Succ, "GetContactByUri");
			(void)memlist.insert(memlist.begin(), contact.ucAcc_);
		}
		else
		{
			Contact contact;
			int iRet = pUCContactMgrProxy->GetContactByUri(contact, part->contact_.uri_);
			CHECK_RETURN_VOID(iRet, UCSDK_Succ, "GetContactByUri");
			memlist.push_back(contact.ucAcc_);
		}
	}

	DEBUG_LOG() << "AVSessAdded callback --- ENTER.";
	m_pUCSignalRecvAbsProxy->OnAVSessAdded(propMap, memlist, avParam);
	DEBUG_LOG() << "AVSessAdded callback --- LEAVE.";

	DEBUG_LOG() << "--- LEAVE";
}

void UCMessageSignalProcess::OnAVSessionConnected(conversation::Conversation* _con)
{
	DEBUG_LOG() << "--- ENTER";

	CHECK_POINTER_VOID(_con);
	CHECK_POINTER_VOID(m_pUCSignalRecvAbsProxy);

	std::string convId = _con->propmap_[conversation::ConvIdentifier];
	DEBUG_LOG() << "AVSessionConnected callback --- ENTER.";
	m_pUCSignalRecvAbsProxy->OnAVSessionConnected(convId);
	DEBUG_LOG() << "AVSessionConnected callback --- LEAVE.";

	DEBUG_LOG() << "--- LEAVE";
}

void UCMessageSignalProcess::OnAVSessionClosed(conversation::Conversation* _con,conversation::sMsgAVSessionClosedParam /*_param*/)
{
	DEBUG_LOG() << "--- ENTER";

	CHECK_POINTER_VOID(_con);
	CHECK_POINTER_VOID(m_pUCSignalRecvAbsProxy);

	std::string convId = _con->propmap_[conversation::ConvIdentifier];
	DEBUG_LOG() << "AVSessionClosed callback --- ENTER.";
	m_pUCSignalRecvAbsProxy->OnAVSessionClosed(convId);
	DEBUG_LOG() << "AVSessionClosed callback --- LEAVE.";

	DEBUG_LOG() << "--- LEAVE";
}

void UCMessageSignalProcess::OnConvMemberStatusChanged(conversation::Conversation* _con, int /*_chgtype*/, std::string /*_uri*/)
{
	DEBUG_LOG() << "--- ENTER";

	CHECK_POINTER_VOID(_con);
	CHECK_POINTER_VOID(m_pUCSignalRecvAbsProxy);

	uc::model::conversation::Conversation::MemList_::iterator itor_b = _con->members_.begin();
	uc::model::conversation::Conversation::MemList_::iterator itor_e = _con->members_.end();
	for (; itor_b != itor_e; itor_b++)
	{
		conversation::Participant* part = itor_b->second;
		CHECK_POINTER_VOID(part);

		std::string state = part->propmap_[conversation::PartConfState];
		int chgState = -1;

		if (conversation::PART_CONFSTATE_INVITING == state)
		{
			chgState = Conf_Inviting;
		}
		else if (conversation::PART_CONFSTATE_HANGUP == state)
		{
			chgState = Conf_Hangup;
		}
		else if (conversation::PART_CONFSTATE_INCONF == state)
		{
			//chgState = Conf_InConf;
			std::string muteString = part->propmap_[PartIsMuted];
			if(conversation::PART_AUDIO_MUTED == muteString)
			{
				chgState = Conf_ForbidSpk;
			}
			else
			{
				chgState = Conf_AllowSpk;
			}				
		}
		else if (conversation::PART_CONFSTATE_QUIT == state)
		{
			chgState = Conf_Quit;
		}
		else if (conversation::PART_CONFSTATE_INHOLD == state )
		{
			chgState = Conf_InHold;
		}
		else if (conversation::PART_CONFSTATE_NEEDREFER == state)
		{
			chgState = Conf_Needreffer;
		}

		std::string convId = _con->propmap_[conversation::ConvIdentifier];

		DEBUG_LOG() << "ConvMemberStatusChanged callback --- ENTER.";
		m_pUCSignalRecvAbsProxy->OnConvMemberStatusChanged(convId, chgState, part->contact_.uri_);
		DEBUG_LOG() << "ConvMemberStatusChanged callback --- LEAVE.";
	}

	DEBUG_LOG() << "--- LEAVE";
}

void UCMessageSignalProcess::OnConvMemAllowSpeak(conversation::Conversation* _con, conversation::Participant _parti)
{
	DEBUG_LOG() << "--- ENTER";

	CHECK_POINTER_VOID(_con);
	CHECK_POINTER_VOID(m_pUCSignalRecvAbsProxy);

	std::string convId = _con->propmap_[conversation::ConvIdentifier];
	UCSDKContact member;
	UCContactMgrProxy::CopyContactToUCSDKContact(_parti.contact_, member);

	DEBUG_LOG() << "ConvMemAllowSpeak callback --- ENTER.";
	m_pUCSignalRecvAbsProxy->OnConvMemAllowSpeak(convId, member);
	DEBUG_LOG() << "ConvMemAllowSpeak callback --- LEAVE.";

	DEBUG_LOG() << "--- LEAVE";
}

void UCMessageSignalProcess::OnConvMemForbidSpeak(conversation::Conversation* _con, conversation::Participant _parti)
{
	DEBUG_LOG() << "--- ENTER";

	CHECK_POINTER_VOID(_con);
	CHECK_POINTER_VOID(m_pUCSignalRecvAbsProxy);

	std::string convId = _con->propmap_[conversation::ConvIdentifier];
	UCSDKContact member;
	UCContactMgrProxy::CopyContactToUCSDKContact(_parti.contact_, member);

	DEBUG_LOG() << "ConvMemForbidSpeak callback --- ENTER.";
	m_pUCSignalRecvAbsProxy->OnConvMemForbidSpeak(convId, member);
	DEBUG_LOG() << "ConvMemForbidSpeak callback --- LEAVE.";

	DEBUG_LOG() << "--- LEAVE";
}

void UCMessageSignalProcess::OnConvMemCurSpeaker(conversation::Conversation* _con, std::string _uri)
{
	DEBUG_LOG() << "--- ENTER";

	CHECK_POINTER_VOID(_con);
	CHECK_POINTER_VOID(m_pUCSignalRecvAbsProxy);

	std::string convId = _con->propmap_[conversation::ConvIdentifier];

	UCContactMgrProxy* pUCContactMgrProxy = UCContactMgrProxy::Instance();
	CHECK_POINTER_VOID(pUCContactMgrProxy);

	Contact contact;
	int iRet = pUCContactMgrProxy->GetContactByUri(contact, _uri);
	CHECK_RETURN_VOID(iRet, UCSDK_Succ, "GetContactByUri");

	UCSDKContact member;
	UCContactMgrProxy::CopyContactToUCSDKContact(contact, member);

	DEBUG_LOG() << "ConvMemCurSpeaker callback --- ENTER.";
	m_pUCSignalRecvAbsProxy->OnConvMemCurSpeaker(convId, member);
	DEBUG_LOG() << "ConvMemCurSpeaker callback --- LEAVE.";

	DEBUG_LOG() << "--- LEAVE";
}

void UCMessageSignalProcess::OnConvGroupMemberChanged(conversation::Conversation* _con,std::vector<std::string> _kicklist,std::vector<std::string> _addlist)
{
	DEBUG_LOG() << "--- ENTER";

	CHECK_POINTER_VOID(_con);
	CHECK_POINTER_VOID(m_pUCSignalRecvAbsProxy);

	std::string convId = _con->propmap_[conversation::ConvIdentifier];

	std::vector<std::string>::iterator itor_b = _kicklist.begin();
	std::vector<std::string>::iterator itor_e = _kicklist.end();
	for (; itor_b != itor_e; itor_b++)
	{
		std::string& uri = *itor_b;

		DEBUG_LOG() << "ConvGroupMemberChanged callback --- ENTER.";
		m_pUCSignalRecvAbsProxy->OnConvGroupMemberChanged(convId, Conf_MemDel, uri);
		DEBUG_LOG() << "ConvGroupMemberChanged callback --- LEAVE.";
	}

	itor_b = _addlist.begin();
	itor_e = _addlist.end();
	for (; itor_b != itor_e; itor_b++)
	{
		std::string& uri = *itor_b;

		DEBUG_LOG() << "ConvGroupMemberChanged callback --- ENTER.";
		m_pUCSignalRecvAbsProxy->OnConvGroupMemberChanged(convId, Conf_MemAdd, uri);
		DEBUG_LOG() << "ConvGroupMemberChanged callback --- LEAVE.";
	}

	DEBUG_LOG() << "--- LEAVE";
}

void UCMessageSignalProcess::OnInstantSessAdded(conversation::Conversation* /*_con*/)
{
	return;
}//lint !e1762

void UCMessageSignalProcess::OnInstantSessRemoved(conversation::Conversation* _con)
{
	DEBUG_LOG() << "--- ENTER";

	CHECK_POINTER_VOID(_con);
	CHECK_POINTER_VOID(m_pUCSignalRecvAbsProxy);

	std::string convId = _con->propmap_[conversation::ConvIdentifier];
	DEBUG_LOG() << "InstantSessRemoved callback --- ENTER.";
	m_pUCSignalRecvAbsProxy->OnInstantSessRemoved(convId);
	DEBUG_LOG() << "InstantSessRemoved callback --- LEAVE.";

	DEBUG_LOG() << "--- LEAVE";
}

void UCMessageSignalProcess::OnReceivedIMMessage(std::string _converstationID, conversation::sImMsgItem _ImMessage)
{
	DEBUG_LOG() << "--- ENTER";

	CHECK_POINTER_VOID(m_pUCSignalRecvAbsProxy);

	uc::model::UCClient* pUCClient = uc::model::UCClient::GetClient();
	CHECK_POINTER_VOID(pUCClient);
	uc::model::conversation::ConversationMgr* pConvMgr = pUCClient->ConvManager;
	CHECK_POINTER_VOID(pConvMgr);
	conversation::Conversation* _con = pConvMgr->GetConversation(_converstationID);
	CHECK_POINTER_VOID(_con);

	ConversationPropMap propMap;
	conversation::Conversation::ConvProperties_::iterator it_b = _con->propmap_.begin();
	conversation::Conversation::ConvProperties_::iterator it_e = _con->propmap_.end();
	for (; it_b != it_e; it_b++)
	{
		(void)propMap.insert(std::make_pair((CONVERSATION_PROPERTY_E)it_b->first, it_b->second));
	}

	UCContactMgrProxy* pUCContactMgrProxy = UCContactMgrProxy::Instance();
	if (NULL == pUCContactMgrProxy)
	{
		ERROR_LOG() << "Get UCContactMgrProxy instance failed.";
		DEBUG_LOG() << "--- LEAVE";
		return;
	}
	AccountList memlist;
	conversation::Conversation::MemList_::iterator iter_b = _con->members_.begin();
	conversation::Conversation::MemList_::iterator iter_e = _con->members_.end();
	for (; iter_b != iter_e; iter_b++)
	{
		Participant* part = iter_b->second;
		if ("1" == part->propmap_[conversation::ParIsLeader])
		{
			Contact contact;
			int iRet = pUCContactMgrProxy->GetContactByUri(contact, part->contact_.uri_);
			CHECK_RETURN_VOID(iRet, UCSDK_Succ, "GetContactByUri");
			(void)memlist.insert(memlist.begin(), contact.ucAcc_);
		}
		else
		{
			Contact contact;
			int iRet = pUCContactMgrProxy->GetContactByUri(contact, part->contact_.uri_);
			CHECK_RETURN_VOID(iRet, UCSDK_Succ, "GetContactByUri");
			memlist.push_back(contact.ucAcc_);
		}
	}

	IMMessage ImMessage;
	ImMessage.chatType = InstantMsgType2INSTANT_MSG_TYPE_E(_ImMessage.chatType);
	ImMessage.content = _ImMessage.content;
	ImMessage.msgid = _ImMessage.msgid;
	ImMessage.name = _ImMessage.name;
	ImMessage.origin = _ImMessage.origin;
	ImMessage.rcv_time = _ImMessage.rcv_time;
	ImMessage.target = _ImMessage.target;

	DEBUG_LOG() << "ReceivedIMMessage callback --- ENTER.";
	m_pUCSignalRecvAbsProxy->OnReceivedIMMessage(propMap, memlist, ImMessage);
	DEBUG_LOG() << "ReceivedIMMessage callback --- LEAVE.";

	DEBUG_LOG() << "--- LEAVE";
}

void UCMessageSignalProcess::OnSystemMsgReceived(const sSysMsgItem& _item)
{
	DEBUG_LOG() << "--- ENTER";

	CHECK_POINTER_VOID(m_pUCSignalRecvAbsProxy);

	DEBUG_LOG() << "SysMsgRecved callback --- ENTER.";
	m_pUCSignalRecvAbsProxy->OnSysMsgRecved(_item.origin, _item.subject, _item.content, _item.rcv_time, _item.msgid, _item.msgtype);
	DEBUG_LOG() << "SysMsgRecved callback --- LEAVE.";

	DEBUG_LOG() << "--- LEAVE";
}

void UCMessageSignalProcess::OnGroupInvitation(const uc::model::FixedGroup _group, std::string /*_uri*/, std::string /*_name*/, std::string /*_direct*/)
{
	DEBUG_LOG() << "--- ENTER";

	CHECK_POINTER_VOID(m_pUCSignalRecvAbsProxy);

	UCSDKFixedGroup fixedGroup;
	UCGroupProxy::CopyFixedGroupToUCSDKFixedGroup(_group, fixedGroup);

	DEBUG_LOG() << "GroupInvitation callback --- ENTER.";
	m_pUCSignalRecvAbsProxy->OnGroupInvitation(fixedGroup);
	DEBUG_LOG() << "GroupInvitation callback --- LEAVE.";

	DEBUG_LOG() << "--- LEAVE";
}

void UCMessageSignalProcess::OnGroupInvitationRes(const uc::model::FixedGroup _group, std::string invitername, int result)
{
	DEBUG_LOG() << "--- ENTER";

	CHECK_POINTER_VOID(m_pUCSignalRecvAbsProxy);

	UCSDKFixedGroup fixedGroup;
	UCGroupProxy::CopyFixedGroupToUCSDKFixedGroup(_group, fixedGroup);

	DEBUG_LOG() << "GroupInvitationRes callback --- ENTER.";
	m_pUCSignalRecvAbsProxy->OnGroupInvitationRes(fixedGroup, invitername, result);
	DEBUG_LOG() << "GroupInvitationRes callback --- LEAVE.";

	DEBUG_LOG() << "--- LEAVE";
}

void UCMessageSignalProcess::OnLeaveFromFixedGroup(const uc::model::FixedGroup _group, int reason)
{
	DEBUG_LOG() << "--- ENTER";

	CHECK_POINTER_VOID(m_pUCSignalRecvAbsProxy);

	UCSDKFixedGroup fixedGroup;
	UCGroupProxy::CopyFixedGroupToUCSDKFixedGroup(_group, fixedGroup);

	DEBUG_LOG() << "LeaveFromFixedGroup callback --- ENTER.";
	m_pUCSignalRecvAbsProxy->OnLeaveFromFixedGroup(fixedGroup, reason);
	DEBUG_LOG() << "LeaveFromFixedGroup callback --- LEAVE.";

	DEBUG_LOG() << "--- LEAVE";
}

void UCMessageSignalProcess::OnJoinFixedGroupRequest(const uc::model::FixedGroup _group, std::string inviteruri, std::string /*invitername*/)
{
	DEBUG_LOG() << "--- ENTER";

	CHECK_POINTER_VOID(m_pUCSignalRecvAbsProxy);

	UCSDKFixedGroup fixedGroup;
	UCGroupProxy::CopyFixedGroupToUCSDKFixedGroup(_group, fixedGroup);

	DEBUG_LOG() << "JoinFixedGroupRequest callback --- ENTER.";
	m_pUCSignalRecvAbsProxy->OnJoinFixedGroupRequest(fixedGroup, inviteruri);
	DEBUG_LOG() << "JoinFixedGroupRequest callback --- LEAVE.";

	DEBUG_LOG() << "--- LEAVE";
}

void UCMessageSignalProcess::OnJoinFixedGroupRes(const uc::model::FixedGroup _group, std::string invitername, int result)
{
	DEBUG_LOG() << "--- ENTER";

	CHECK_POINTER_VOID(m_pUCSignalRecvAbsProxy);

	UCSDKFixedGroup fixedGroup;
	UCGroupProxy::CopyFixedGroupToUCSDKFixedGroup(_group, fixedGroup);

	DEBUG_LOG() << "JoinFixedGroupRes callback --- ENTER.";
	m_pUCSignalRecvAbsProxy->OnJoinFixedGroupRes(fixedGroup, invitername, result);
	DEBUG_LOG() << "JoinFixedGroupRes callback --- LEAVE.";

	DEBUG_LOG() << "--- LEAVE";
}

void UCMessageSignalProcess::OnMemberAdded(const uc::model::FixedGroup _group, uc::model::Contact _contact)
{
	DEBUG_LOG() << "--- ENTER";

	CHECK_POINTER_VOID(m_pUCSignalRecvAbsProxy);

	UCSDKFixedGroup fixedGroup;
	UCGroupProxy::CopyFixedGroupToUCSDKFixedGroup(_group, fixedGroup);
	UCSDKContact member;
	UCContactMgrProxy::CopyContactToUCSDKContact(_contact, member);

	DEBUG_LOG() << "MemberAdded callback --- ENTER.";
	m_pUCSignalRecvAbsProxy->OnMemberAdded(fixedGroup, member);
	DEBUG_LOG() << "MemberAdded callback --- LEAVE.";

	DEBUG_LOG() << "--- LEAVE";
}

void UCMessageSignalProcess::OnMemberRemoved(const uc::model::FixedGroup _group, uc::model::Contact _contact)
{
	DEBUG_LOG() << "--- ENTER";

	CHECK_POINTER_VOID(m_pUCSignalRecvAbsProxy);

	UCSDKFixedGroup fixedGroup;
	UCGroupProxy::CopyFixedGroupToUCSDKFixedGroup(_group, fixedGroup);
	UCSDKContact member;
	UCContactMgrProxy::CopyContactToUCSDKContact(_contact, member);

	DEBUG_LOG() << "MemberRemoved callback --- ENTER.";
	m_pUCSignalRecvAbsProxy->OnMemberRemoved(fixedGroup, member);
	DEBUG_LOG() << "MemberRemoved callback --- LEAVE.";
	DEBUG_LOG() << "--- LEAVE";
}

void UCMessageSignalProcess::OnMemberFlowChanged(const uc::model::FixedGroup _group, uc::model::Contact _contact)
{
	DEBUG_LOG() << "--- ENTER";

	CHECK_POINTER_VOID(m_pUCSignalRecvAbsProxy);

	UCSDKFixedGroup fixedGroup;
	UCGroupProxy::CopyFixedGroupToUCSDKFixedGroup(_group, fixedGroup);
	UCSDKContact member;
	UCContactMgrProxy::CopyContactToUCSDKContact(_contact, member);

	DEBUG_LOG() << "MemberFlowChanged callback --- ENTER.";
	//m_pUCSignalRecvAbsProxy->OnMemberFlowChanged(fixedGroup, member);
	//这里实际上是添加联系人到固定群组，对方接受返回。
	m_pUCSignalRecvAbsProxy->OnGroupInvitationRes(fixedGroup, _contact.name_, 1);
	DEBUG_LOG() << "MemberFlowChanged callback --- LEAVE.";

	DEBUG_LOG() << "--- LEAVE";
}

void UCMessageSignalProcess::OnFixedGroupInfoChanged(const uc::model::FixedGroup _group)
{
	DEBUG_LOG() << "--- ENTER";

	CHECK_POINTER_VOID(m_pUCSignalRecvAbsProxy);

	UCSDKFixedGroup fixedGroup;
	UCGroupProxy::CopyFixedGroupToUCSDKFixedGroup(_group, fixedGroup);

	DEBUG_LOG() << "FixedGroupInfoChanged callback --- ENTER.";
	m_pUCSignalRecvAbsProxy->OnFixedGroupInfoChanged(fixedGroup);
	DEBUG_LOG() << "FixedGroupInfoChanged callback --- LEAVE.";

	DEBUG_LOG() << "--- LEAVE";
}

INSTANT_MSG_TYPE_E UCMessageSignalProcess::InstantMsgType2INSTANT_MSG_TYPE_E(uc::model::conversation::InstantMsgType type)
{
	switch(type)
	{
	case ChatP2PIM:
		{
			return IM_ChatP2PIM;
		}
	case ChatFixedGroup:
		{
			return IM_ChatFixedGroup;
		}
	case ChatInputStatus:
		{
			return IM_ChatInputStatus;
		}
	case ChatOfflineFile:
		{
			return IM_ChatOfflineFile;
		}
	case ChatAddFriend:
		{
			return IM_ChatAddFriend;
		}
	default:
		{
			return IM_ChatErrorMsg;
		}
	}
}

}
}
