#include "stdafx.h"
#include "UCSignalRecvProxy.h"


UCSignalRecvProxy::UCSignalRecvProxy()
	: m_pDlg(NULL)
{

}

UCSignalRecvProxy::~UCSignalRecvProxy()
{

}

void UCSignalRecvProxy::OnClientSignInNotify(int state, const std::string& reason)
{
	if (!m_pDlg)
		return;

	CString* pszReason = new CString(reason.c_str());
	::PostMessage(m_pDlg->GetSafeHwnd(), WM_SIGNIN_NOTIFY, (WPARAM)state, (LPARAM)pszReason);
}

void UCSignalRecvProxy::OnStatusChanged(CONTACT_AVAILABILITY_E state, const std::string& desc, const UCSDKContact& contact, const std::string& param)
{
	if (!m_pDlg)
		return;

	CString* pszAcc = new CString(contact.ucAcc_.c_str());
	::PostMessage(m_pDlg->GetSafeHwnd(), WM_STATUS_CHANGED, (WPARAM)state, (LPARAM)pszAcc);
}

void UCSignalRecvProxy::OnIncreContactsChanged(void)
{
	if (!m_pDlg)
		return;
}

void UCSignalRecvProxy::OnAVSessAdded(const ConversationPropMap& propMap, const AccountList& memberlist, const STAudioVideoParam& avParam)
{
	if (!m_pDlg)
		return;

	AVSessAddedInfo* pAVAdd = new AVSessAddedInfo;
	STAudioVideoParam* pAVParam = &pAVAdd->avParam;
	pAVParam->caller_ = avParam.caller_;
	pAVParam->callername_ = avParam.callername_;
	pAVParam->callalertinfo_ = avParam.callalertinfo_;
	pAVParam->callmode_ = avParam.callmode_;
	pAVParam->autoanswerdelay = avParam.autoanswerdelay;
	pAVParam->lineindex_ = avParam.lineindex_;
	pAVParam->isdataconf_ = avParam.isdataconf_;
	pAVParam->isvideo_ = avParam.isvideo_;

	pAVAdd->propMap = propMap;
	pAVAdd->memlist = memberlist;

	::PostMessage(m_pDlg->GetSafeHwnd(), WM_AVSESSION_ADDED, 0, (LPARAM)pAVAdd);
}

void UCSignalRecvProxy::OnAVSessionConnected(const std::string& convId)
{
	if (!m_pDlg)
		return;

	CString* pszConvId = new CString(convId.c_str());
	::PostMessage(m_pDlg->GetSafeHwnd(), WM_AVSESSION_CONNECTED, 0, (LPARAM)pszConvId);
}

void UCSignalRecvProxy::OnAVSessionClosed(const std::string& convId)
{
	if (!m_pDlg)
		return;

	CString* pszConvId = new CString(convId.c_str());
	::PostMessage(m_pDlg->GetSafeHwnd(), WM_AVSESSION_CLOSED, 0, (LPARAM)pszConvId);
}

void UCSignalRecvProxy::OnConvMemberStatusChanged(const std::string& convId, int chgtype, const std::string& memberuri)
{
	if (!m_pDlg)
		return;

	ConfMemChgInfo *pConfMemChgInfo = new ConfMemChgInfo;
	pConfMemChgInfo->convId = convId;
	pConfMemChgInfo->state = chgtype;
	pConfMemChgInfo->memUri = memberuri;

	::PostMessage(m_pDlg->GetSafeHwnd(), WM_CONF_STATUS_CHANGE, 0, (LPARAM)pConfMemChgInfo);
}

void UCSignalRecvProxy::OnConvMemAllowSpeak(const std::string& convId, const UCSDKContact& member)
{
	if (!m_pDlg)
		return;

	ConfMemSpkInfo* pConfMemSpkInfo = new ConfMemSpkInfo;
	pConfMemSpkInfo->convId = convId;
	pConfMemSpkInfo->state = Conf_AllowSpk;
	pConfMemSpkInfo->ucAcc = member.ucAcc_;

	::PostMessage(m_pDlg->GetSafeHwnd(), WM_CONF_ALLOW_SPEAK, 0, (LPARAM)pConfMemSpkInfo);
}

void UCSignalRecvProxy::OnConvMemForbidSpeak(const std::string& convId, const UCSDKContact& member)
{
	if (!m_pDlg)
		return;

	ConfMemSpkInfo* pConfMemSpkInfo = new ConfMemSpkInfo;
	pConfMemSpkInfo->convId = convId;
	pConfMemSpkInfo->state = Conf_ForbidSpk;
	pConfMemSpkInfo->ucAcc = member.ucAcc_;

	::PostMessage(m_pDlg->GetSafeHwnd(), WM_CONF_FORBID_SPEAK, 0, (LPARAM)pConfMemSpkInfo);
}

void UCSignalRecvProxy::OnConvMemCurSpeaker(const std::string& convId, const UCSDKContact& member)
{
	if (!m_pDlg)
		return;

	ConfMemSpkInfo* pConfMemSpkInfo = new ConfMemSpkInfo;
	pConfMemSpkInfo->convId = convId;
	pConfMemSpkInfo->state = Conf_CurSpker;
	pConfMemSpkInfo->ucAcc = member.ucAcc_;

	::PostMessage(m_pDlg->GetSafeHwnd(), WM_CONF_CUR_SPEAKER, 0, (LPARAM)pConfMemSpkInfo);
}

void UCSignalRecvProxy::OnConvGroupMemberChanged(const std::string& convId, int chgtype, const std::string& memberuri)
{
	if (!m_pDlg)
		return;

	ConfMemChgInfo *pConfMemChgInfo = new ConfMemChgInfo;
	pConfMemChgInfo->convId = convId;
	pConfMemChgInfo->state = chgtype;
	pConfMemChgInfo->memUri = memberuri;

	::PostMessage(m_pDlg->GetSafeHwnd(), WM_CONF_STATUS_CHANGE, 0, (LPARAM)pConfMemChgInfo);
}

void UCSignalRecvProxy::OnReceivedIMMessage(const ConversationPropMap& propMap, const AccountList& memberlist, const IMMessage& ImMessage)
{
	if (!m_pDlg)
		return;

	IMMessageInfo* pIMMessageInfo = new IMMessageInfo;
	pIMMessageInfo->imMsg.chatType = ImMessage.chatType;
	pIMMessageInfo->imMsg.content = ImMessage.content;
	pIMMessageInfo->imMsg.msgid = ImMessage.msgid;
	pIMMessageInfo->imMsg.name = ImMessage.name;
	pIMMessageInfo->imMsg.origin = ImMessage.origin;
	pIMMessageInfo->imMsg.rcv_time = ImMessage.rcv_time;
	pIMMessageInfo->imMsg.target = ImMessage.target;
	pIMMessageInfo->propMap = propMap;
	pIMMessageInfo->memlist = memberlist;

	::PostMessage(m_pDlg->GetSafeHwnd(), WM_RECV_IM, 0, (LPARAM)pIMMessageInfo);
}

void UCSignalRecvProxy::OnInstantSessRemoved(const std::string& convId)
{
	if (!m_pDlg)
		return;

	CString* pszConvId = new CString(convId.c_str());

	::PostMessage(m_pDlg->GetSafeHwnd(), WM_IM_SESS_REMOVE, 0, (LPARAM)pszConvId);
}

void UCSignalRecvProxy::OnInstantSessAdded(const std::string& convId, const UCSDKContact& member)
{
	if (!m_pDlg)
		return;
}

void UCSignalRecvProxy::OnSysMsgRecved(const std::string& origin, const std::string& subject, const std::string& content, const std::string& rcv_time, const std::string& msgid, int msgtype)
{
	if (!m_pDlg)
		return;
}

void UCSignalRecvProxy::OnGroupInvitation(const UCSDKFixedGroup& fixedGroup)
{
	if (!m_pDlg)
		return;

	FixedGroupInfo* pFixedGroupInfo = new FixedGroupInfo;
	pFixedGroupInfo->name_ = fixedGroup.name_;
	pFixedGroupInfo->id_ = fixedGroup.id_;
	pFixedGroupInfo->type_ = fixedGroup.type_;
	pFixedGroupInfo->readonly_ = fixedGroup.readonly_;
	pFixedGroupInfo->creator_ = fixedGroup.creator_;
	pFixedGroupInfo->uri_ = fixedGroup.uri_;
	pFixedGroupInfo->groupno_ = fixedGroup.groupno_;
	pFixedGroupInfo->desc_ = fixedGroup.desc_;
	pFixedGroupInfo->bulletin_ = fixedGroup.bulletin_;
	pFixedGroupInfo->owneruri_ = fixedGroup.owneruri_;
	pFixedGroupInfo->capacity_ = fixedGroup.capacity_;
	pFixedGroupInfo->needpermit_ = fixedGroup.needpermit_;

	::PostMessage(m_pDlg->GetSafeHwnd(), WM_GROUP_INVITATION, 0, (LPARAM)pFixedGroupInfo);
}

void UCSignalRecvProxy::OnGroupInvitationRes(const UCSDKFixedGroup& fixedGroup, const std::string& invitername, int result)
{
	if (!m_pDlg)
		return;

	InvitationResInfo* pInvitationResInfo = new InvitationResInfo;
	FixedGroupInfo* pFixedGroupInfo = &pInvitationResInfo->group;
	pFixedGroupInfo->name_ = fixedGroup.name_;
	pFixedGroupInfo->id_ = fixedGroup.id_;
	pFixedGroupInfo->type_ = fixedGroup.type_;
	pFixedGroupInfo->readonly_ = fixedGroup.readonly_;
	pFixedGroupInfo->creator_ = fixedGroup.creator_;
	pFixedGroupInfo->uri_ = fixedGroup.uri_;
	pFixedGroupInfo->groupno_ = fixedGroup.groupno_;
	pFixedGroupInfo->desc_ = fixedGroup.desc_;
	pFixedGroupInfo->bulletin_ = fixedGroup.bulletin_;
	pFixedGroupInfo->owneruri_ = fixedGroup.owneruri_;
	pFixedGroupInfo->capacity_ = fixedGroup.capacity_;
	pFixedGroupInfo->needpermit_ = fixedGroup.needpermit_;

	pInvitationResInfo->invName = invitername;
	pInvitationResInfo->result = result;

	::PostMessage(m_pDlg->GetSafeHwnd(), WM_GROUP_INVITATIONRES, 0, (LPARAM)pInvitationResInfo);
}

void UCSignalRecvProxy::OnLeaveFromFixedGroup(const UCSDKFixedGroup& fixedGroup, int reason)
{
	if (!m_pDlg)
		return;

	LeaveFromFixedGroupInfo* pLeaveFromFixedGroupInfo = new LeaveFromFixedGroupInfo;
	FixedGroupInfo* pFixedGroupInfo = &pLeaveFromFixedGroupInfo->group;
	pFixedGroupInfo->name_ = fixedGroup.name_;
	pFixedGroupInfo->id_ = fixedGroup.id_;
	pFixedGroupInfo->type_ = fixedGroup.type_;
	pFixedGroupInfo->readonly_ = fixedGroup.readonly_;
	pFixedGroupInfo->creator_ = fixedGroup.creator_;
	pFixedGroupInfo->uri_ = fixedGroup.uri_;
	pFixedGroupInfo->groupno_ = fixedGroup.groupno_;
	pFixedGroupInfo->desc_ = fixedGroup.desc_;
	pFixedGroupInfo->bulletin_ = fixedGroup.bulletin_;
	pFixedGroupInfo->owneruri_ = fixedGroup.owneruri_;
	pFixedGroupInfo->capacity_ = fixedGroup.capacity_;
	pFixedGroupInfo->needpermit_ = fixedGroup.needpermit_;

	pLeaveFromFixedGroupInfo->reason = reason;

	::PostMessage(m_pDlg->GetSafeHwnd(), WM_GROUP_LEAVE_FIXED, 0, (LPARAM)pLeaveFromFixedGroupInfo);
}

void UCSignalRecvProxy::OnJoinFixedGroupRequest(const UCSDKFixedGroup& fixedGroup, const std::string& inviteruri)
{
	if (!m_pDlg)
		return;

	JoinFixedGroupReqInfo* pJoinFixedGroupReqInfo = new JoinFixedGroupReqInfo;
	FixedGroupInfo* pFixedGroupInfo = &pJoinFixedGroupReqInfo->group;
	pFixedGroupInfo->name_ = fixedGroup.name_;
	pFixedGroupInfo->id_ = fixedGroup.id_;
	pFixedGroupInfo->type_ = fixedGroup.type_;
	pFixedGroupInfo->readonly_ = fixedGroup.readonly_;
	pFixedGroupInfo->creator_ = fixedGroup.creator_;
	pFixedGroupInfo->uri_ = fixedGroup.uri_;
	pFixedGroupInfo->groupno_ = fixedGroup.groupno_;
	pFixedGroupInfo->desc_ = fixedGroup.desc_;
	pFixedGroupInfo->bulletin_ = fixedGroup.bulletin_;
	pFixedGroupInfo->owneruri_ = fixedGroup.owneruri_;
	pFixedGroupInfo->capacity_ = fixedGroup.capacity_;
	pFixedGroupInfo->needpermit_ = fixedGroup.needpermit_;

	pJoinFixedGroupReqInfo->uri = inviteruri;

	::PostMessage(m_pDlg->GetSafeHwnd(), WM_GROUP_JOIN_FIXED_REQ, 0, (LPARAM)pJoinFixedGroupReqInfo);
}

void UCSignalRecvProxy::OnJoinFixedGroupRes(const UCSDKFixedGroup& fixedGroup, const std::string& invitername, int result)
{
	if (!m_pDlg)
		return;

	JoinFixedGroupRspInfo* pJoinFixedGroupRspInfo = new JoinFixedGroupRspInfo;
	FixedGroupInfo* pFixedGroupInfo = &pJoinFixedGroupRspInfo->group;
	pFixedGroupInfo->name_ = fixedGroup.name_;
	pFixedGroupInfo->id_ = fixedGroup.id_;
	pFixedGroupInfo->type_ = fixedGroup.type_;
	pFixedGroupInfo->readonly_ = fixedGroup.readonly_;
	pFixedGroupInfo->creator_ = fixedGroup.creator_;
	pFixedGroupInfo->uri_ = fixedGroup.uri_;
	pFixedGroupInfo->groupno_ = fixedGroup.groupno_;
	pFixedGroupInfo->desc_ = fixedGroup.desc_;
	pFixedGroupInfo->bulletin_ = fixedGroup.bulletin_;
	pFixedGroupInfo->owneruri_ = fixedGroup.owneruri_;
	pFixedGroupInfo->capacity_ = fixedGroup.capacity_;
	pFixedGroupInfo->needpermit_ = fixedGroup.needpermit_;

	pJoinFixedGroupRspInfo->name = invitername;
	pJoinFixedGroupRspInfo->result = result;

	::PostMessage(m_pDlg->GetSafeHwnd(), WM_GROUP_JOIN_FIXED_RSP, 0, (LPARAM)pJoinFixedGroupRspInfo);
}

void UCSignalRecvProxy::OnMemberAdded(const UCSDKFixedGroup& fixedGroup, const UCSDKContact& member)
{
	if (!m_pDlg)
		return;

	GroupMemberChangedInfo* pGroupMemberChangedInfo = new GroupMemberChangedInfo;
	FixedGroupInfo* pFixedGroupInfo = &pGroupMemberChangedInfo->group;
	pFixedGroupInfo->name_ = fixedGroup.name_;
	pFixedGroupInfo->id_ = fixedGroup.id_;
	pFixedGroupInfo->type_ = fixedGroup.type_;
	pFixedGroupInfo->readonly_ = fixedGroup.readonly_;
	pFixedGroupInfo->creator_ = fixedGroup.creator_;
	pFixedGroupInfo->uri_ = fixedGroup.uri_;
	pFixedGroupInfo->groupno_ = fixedGroup.groupno_;
	pFixedGroupInfo->desc_ = fixedGroup.desc_;
	pFixedGroupInfo->bulletin_ = fixedGroup.bulletin_;
	pFixedGroupInfo->owneruri_ = fixedGroup.owneruri_;
	pFixedGroupInfo->capacity_ = fixedGroup.capacity_;
	pFixedGroupInfo->needpermit_ = fixedGroup.needpermit_;

	pGroupMemberChangedInfo->name_ = member.name_;
	pGroupMemberChangedInfo->ucAcc_ = member.ucAcc_;
	pGroupMemberChangedInfo->id_ = member.id_;
	pGroupMemberChangedInfo->uri_ = member.uri_;
	pGroupMemberChangedInfo->type = 0;

	::PostMessage(m_pDlg->GetSafeHwnd(), WM_GROUP_MEMBER_CHANGED, 0, (LPARAM)pGroupMemberChangedInfo);
}

void UCSignalRecvProxy::OnMemberRemoved(const UCSDKFixedGroup& fixedGroup, const UCSDKContact& member)
{
	if (!m_pDlg)
		return;

	GroupMemberChangedInfo* pGroupMemberChangedInfo = new GroupMemberChangedInfo;
	FixedGroupInfo* pFixedGroupInfo = &pGroupMemberChangedInfo->group;
	pFixedGroupInfo->name_ = fixedGroup.name_;
	pFixedGroupInfo->id_ = fixedGroup.id_;
	pFixedGroupInfo->type_ = fixedGroup.type_;
	pFixedGroupInfo->readonly_ = fixedGroup.readonly_;
	pFixedGroupInfo->creator_ = fixedGroup.creator_;
	pFixedGroupInfo->uri_ = fixedGroup.uri_;
	pFixedGroupInfo->groupno_ = fixedGroup.groupno_;
	pFixedGroupInfo->desc_ = fixedGroup.desc_;
	pFixedGroupInfo->bulletin_ = fixedGroup.bulletin_;
	pFixedGroupInfo->owneruri_ = fixedGroup.owneruri_;
	pFixedGroupInfo->capacity_ = fixedGroup.capacity_;
	pFixedGroupInfo->needpermit_ = fixedGroup.needpermit_;

	pGroupMemberChangedInfo->name_ = member.name_;
	pGroupMemberChangedInfo->ucAcc_ = member.ucAcc_;
	pGroupMemberChangedInfo->type = 1;

	::PostMessage(m_pDlg->GetSafeHwnd(), WM_GROUP_MEMBER_CHANGED, 0, (LPARAM)pGroupMemberChangedInfo);
}

void UCSignalRecvProxy::OnMemberFlowChanged(const UCSDKFixedGroup& fixedGroup, const UCSDKContact& member)
{
	if (!m_pDlg)
		return;
}

void UCSignalRecvProxy::OnFixedGroupInfoChanged(const UCSDKFixedGroup& fixedGroup)
{
	if (!m_pDlg)
		return;
}

void UCSignalRecvProxy::OnNewFileRercved(const std::string& fileid, const std::string& filename, int filesize, const std::string& originName)
{
	if (!m_pDlg)
		return;
}

void UCSignalRecvProxy::OnFileAccept(const std::string& fileid)
{
	if (!m_pDlg)
		return;
}
void UCSignalRecvProxy::OnFileCancel(const std::string& fileid, const std::string& reason, const std::string& errcode)
{
	if (!m_pDlg)
		return;
}

void UCSignalRecvProxy::OnFileProgress(const std::string& fileid, const std::string& procent)
{
	if (!m_pDlg)
		return;
}