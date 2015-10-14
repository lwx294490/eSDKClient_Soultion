#include "stdafx.h"
#include "SignalMgr.h"

CDialog* SignalMgr::m_pCBaseDlg = NULL;

void CALLBACK SignalMgr::OnLoginCB(int state, const char* reason)
{
	CString* pszReason = new CString(reason);
	::PostMessage(m_pCBaseDlg->GetSafeHwnd(), WM_SIGNIN_NOTIFY, (WPARAM)state, (LPARAM)pszReason);
}

void CALLBACK SignalMgr::OnStatusCB(int state, const char* desc, const UCContact* contact, const char* param)
{
	CString* pszAcc = new CString(contact->ucAcc_);
	::PostMessage(m_pCBaseDlg->GetSafeHwnd(), WM_STATUS_CHANGED, (WPARAM)state, (LPARAM)pszAcc);
}

void CALLBACK SignalMgr::OnAVSessAdded(const UCConversationPropMap* propMap, const UCAccountList* memberlist, const UCAudioVideoParam* avParam)
{
	AVSessAddedInfo* pAVAdd = new AVSessAddedInfo;
	AVParam* pAVParam = &pAVAdd->avParam;
	pAVParam->caller_ = avParam->caller_;
	pAVParam->callername_ = avParam->callername_;
	pAVParam->callalertinfo_ = avParam->callalertinfo_;
	pAVParam->callmode_ = avParam->callmode_==0?false:true;
	pAVParam->autoanswerdelay = avParam->autoanswerdelay;
	pAVParam->lineindex_ = avParam->lineindex_;
	pAVParam->isdataconf_ = avParam->isdataconf_==0?false:true;
	pAVParam->isvideo_ = avParam->isvideo_==0?false:true;

	for (int i=0; i<PROP_LENGTH; i++)
	{
		for (int j=0; j<PROP_INFO_LENGTH; j++)
		{
			if (propMap->prop[i][j] != 0)
				pAVAdd->propMap.insert(std::make_pair((UC_CONVERSATION_PROPERTY_E)i, propMap->prop[i]));
		}
	}

	for (int i=0; i<memberlist->iTotal; i++)
	{
		pAVAdd->memlist.push_back(memberlist->account[i].str);
	}

	::PostMessage(m_pCBaseDlg->GetSafeHwnd(), WM_AVSESSION_ADDED, 0, (LPARAM)pAVAdd);
}

void CALLBACK SignalMgr::OnAVSessConnected(const char* convId)
{
	CString* pszConvId = new CString(convId);
	::PostMessage(m_pCBaseDlg->GetSafeHwnd(), WM_AVSESSION_CONNECTED, 0, (LPARAM)pszConvId);
}

void CALLBACK SignalMgr::OnAVSessClosed(const char* convId)
{
	CString* pszConvId = new CString(convId);
	::PostMessage(m_pCBaseDlg->GetSafeHwnd(), WM_AVSESSION_CLOSED, 0, (LPARAM)pszConvId);
}

void CALLBACK SignalMgr::OnReceivedIM(const UCConversationPropMap* propMap, const UCAccountList* memberlist, const UCIMMessage* ImMessage)
{
	IMMessageInfo* pIMMessageInfo = new IMMessageInfo;
	pIMMessageInfo->imMsg.chatType = ImMessage->chatType;
	pIMMessageInfo->imMsg.content = ImMessage->content;
	pIMMessageInfo->imMsg.msgid = ImMessage->msgid;
	pIMMessageInfo->imMsg.name = ImMessage->name;
	pIMMessageInfo->imMsg.origin = ImMessage->origin;
	pIMMessageInfo->imMsg.rcv_time = ImMessage->rcv_time;
	pIMMessageInfo->imMsg.target = ImMessage->target;

	for (int i=0; i<PROP_LENGTH; i++)
	{
		for (int j=0; j<PROP_INFO_LENGTH; j++)
		{
			if (propMap->prop[i][0] != 0)
				pIMMessageInfo->propMap.insert(std::make_pair((UC_CONVERSATION_PROPERTY_E)i, propMap->prop[i]));
		}
	}

	for (int i=0; i<memberlist->iTotal; i++)
	{
		pIMMessageInfo->memlist.push_back(memberlist->account[i].str);
	}

	::PostMessage(m_pCBaseDlg->GetSafeHwnd(), WM_RECV_IM, 0, (LPARAM)pIMMessageInfo);
}

void CALLBACK SignalMgr::OnConvMemberStatusChanged(const char* convId, int chgtype, const char* memberuri)
{
	ConfMemChgInfo *pConfMemChgInfo = new ConfMemChgInfo;
	pConfMemChgInfo->convId = convId;
	pConfMemChgInfo->state = chgtype;
	pConfMemChgInfo->memUri = memberuri;

	::PostMessage(m_pCBaseDlg->GetSafeHwnd(), WM_CONF_STATUS_CHANGE, 0, (LPARAM)pConfMemChgInfo);
}

void CALLBACK SignalMgr::OnConvMemAllowSpeak(const char* convId, const UCContact* member)
{
	ConfMemSpkInfo* pConfMemSpkInfo = new ConfMemSpkInfo;
	pConfMemSpkInfo->convId = convId;
	pConfMemSpkInfo->state = UC_AllowSpk;
	pConfMemSpkInfo->ucAcc = member->ucAcc_;

	::PostMessage(m_pCBaseDlg->GetSafeHwnd(), WM_CONF_ALLOW_SPEAK, 0, (LPARAM)pConfMemSpkInfo);
}

void CALLBACK SignalMgr::OnConvMemForbidSpeak(const char* convId, const UCContact* member)
{
	ConfMemSpkInfo* pConfMemSpkInfo = new ConfMemSpkInfo;
	pConfMemSpkInfo->convId = convId;
	pConfMemSpkInfo->state = UC_ForbidSpk;
	pConfMemSpkInfo->ucAcc = member->ucAcc_;

	::PostMessage(m_pCBaseDlg->GetSafeHwnd(), WM_CONF_FORBID_SPEAK, 0, (LPARAM)pConfMemSpkInfo);
}

void CALLBACK SignalMgr::OnConvMemCurSpeaker(const char* convId, const UCContact* member)
{
	ConfMemSpkInfo* pConfMemSpkInfo = new ConfMemSpkInfo;
	pConfMemSpkInfo->convId = convId;
	pConfMemSpkInfo->state = UC_CurSpker;
	pConfMemSpkInfo->ucAcc = member->ucAcc_;

	::PostMessage(m_pCBaseDlg->GetSafeHwnd(), WM_CONF_CUR_SPEAKER, 0, (LPARAM)pConfMemSpkInfo);
}

void CALLBACK SignalMgr::OnConvGroupMemberChanged(const char* convId, int chgtype, const char* memberuri)
{
	ConfMemChgInfo *pConfMemChgInfo = new ConfMemChgInfo;
	pConfMemChgInfo->convId = convId;
	pConfMemChgInfo->state = chgtype;
	pConfMemChgInfo->memUri = memberuri;

	::PostMessage(m_pCBaseDlg->GetSafeHwnd(), WM_CONF_STATUS_CHANGE, 0, (LPARAM)pConfMemChgInfo);
}

void CALLBACK SignalMgr::OnInstantSessRemoved(const char* convId)
{
	CString* pszConvId = new CString(convId);

	::PostMessage(m_pCBaseDlg->GetSafeHwnd(), WM_IM_SESS_REMOVE, 0, (LPARAM)pszConvId);
}

void CALLBACK SignalMgr::OnGroupInvitation(const UCFixedGroup* fixedGroup)
{
	FixedGroupInfo* pFixedGroupInfo = new FixedGroupInfo;
	pFixedGroupInfo->name_ = fixedGroup->name_;
	pFixedGroupInfo->id_ = fixedGroup->id_;
	pFixedGroupInfo->type_ = fixedGroup->type_;
	pFixedGroupInfo->readonly_ = fixedGroup->readonly_==0?false:true;
	pFixedGroupInfo->creator_ = fixedGroup->creator_;
	pFixedGroupInfo->uri_ = fixedGroup->uri_;
	pFixedGroupInfo->groupno_ = fixedGroup->groupno_;
	pFixedGroupInfo->desc_ = fixedGroup->desc_;
	pFixedGroupInfo->bulletin_ = fixedGroup->bulletin_;
	pFixedGroupInfo->owneruri_ = fixedGroup->owneruri_;
	pFixedGroupInfo->capacity_ = fixedGroup->capacity_;
	pFixedGroupInfo->needpermit_ = fixedGroup->needpermit_;

	::PostMessage(m_pCBaseDlg->GetSafeHwnd(), WM_GROUP_INVITATION, 0, (LPARAM)pFixedGroupInfo);
}

void CALLBACK SignalMgr::OnGroupInvitationRes(const UCFixedGroup* fixedGroup, const char* invitername, int result)
{
	InvitationResInfo* pInvitationResInfo = new InvitationResInfo;
	FixedGroupInfo* pFixedGroupInfo = &pInvitationResInfo->group;
	pFixedGroupInfo->name_ = fixedGroup->name_;
	pFixedGroupInfo->id_ = fixedGroup->id_;
	pFixedGroupInfo->type_ = fixedGroup->type_;
	pFixedGroupInfo->readonly_ = fixedGroup->readonly_==0?false:true;
	pFixedGroupInfo->creator_ = fixedGroup->creator_;
	pFixedGroupInfo->uri_ = fixedGroup->uri_;
	pFixedGroupInfo->groupno_ = fixedGroup->groupno_;
	pFixedGroupInfo->desc_ = fixedGroup->desc_;
	pFixedGroupInfo->bulletin_ = fixedGroup->bulletin_;
	pFixedGroupInfo->owneruri_ = fixedGroup->owneruri_;
	pFixedGroupInfo->capacity_ = fixedGroup->capacity_;
	pFixedGroupInfo->needpermit_ = fixedGroup->needpermit_;

	pInvitationResInfo->invName = invitername;
	pInvitationResInfo->result = result;

	::PostMessage(m_pCBaseDlg->GetSafeHwnd(), WM_GROUP_INVITATIONRES, 0, (LPARAM)pInvitationResInfo);
}

void CALLBACK SignalMgr::OnLeaveFromFixedGroup(const UCFixedGroup* fixedGroup, int reason)
{
	LeaveFromFixedGroupInfo* pLeaveFromFixedGroupInfo = new LeaveFromFixedGroupInfo;
	FixedGroupInfo* pFixedGroupInfo = &pLeaveFromFixedGroupInfo->group;
	pFixedGroupInfo->name_ = fixedGroup->name_;
	pFixedGroupInfo->id_ = fixedGroup->id_;
	pFixedGroupInfo->type_ = fixedGroup->type_;
	pFixedGroupInfo->readonly_ = fixedGroup->readonly_==0?false:true;
	pFixedGroupInfo->creator_ = fixedGroup->creator_;
	pFixedGroupInfo->uri_ = fixedGroup->uri_;
	pFixedGroupInfo->groupno_ = fixedGroup->groupno_;
	pFixedGroupInfo->desc_ = fixedGroup->desc_;
	pFixedGroupInfo->bulletin_ = fixedGroup->bulletin_;
	pFixedGroupInfo->owneruri_ = fixedGroup->owneruri_;
	pFixedGroupInfo->capacity_ = fixedGroup->capacity_;
	pFixedGroupInfo->needpermit_ = fixedGroup->needpermit_;

	pLeaveFromFixedGroupInfo->reason = reason;

	::PostMessage(m_pCBaseDlg->GetSafeHwnd(), WM_GROUP_LEAVE_FIXED, 0, (LPARAM)pLeaveFromFixedGroupInfo);
}

void CALLBACK SignalMgr::OnJoinFixedGroupRequest(const UCFixedGroup* fixedGroup, const char* inviteruri)
{
	JoinFixedGroupReqInfo* pJoinFixedGroupReqInfo = new JoinFixedGroupReqInfo;
	FixedGroupInfo* pFixedGroupInfo = &pJoinFixedGroupReqInfo->group;
	pFixedGroupInfo->name_ = fixedGroup->name_;
	pFixedGroupInfo->id_ = fixedGroup->id_;
	pFixedGroupInfo->type_ = fixedGroup->type_;
	pFixedGroupInfo->readonly_ = fixedGroup->readonly_==0?false:true;
	pFixedGroupInfo->creator_ = fixedGroup->creator_;
	pFixedGroupInfo->uri_ = fixedGroup->uri_;
	pFixedGroupInfo->groupno_ = fixedGroup->groupno_;
	pFixedGroupInfo->desc_ = fixedGroup->desc_;
	pFixedGroupInfo->bulletin_ = fixedGroup->bulletin_;
	pFixedGroupInfo->owneruri_ = fixedGroup->owneruri_;
	pFixedGroupInfo->capacity_ = fixedGroup->capacity_;
	pFixedGroupInfo->needpermit_ = fixedGroup->needpermit_;

	pJoinFixedGroupReqInfo->uri = inviteruri;

	::PostMessage(m_pCBaseDlg->GetSafeHwnd(), WM_GROUP_JOIN_FIXED_REQ, 0, (LPARAM)pJoinFixedGroupReqInfo);
}

void CALLBACK SignalMgr::OnJoinFixedGroupRes(const UCFixedGroup* fixedGroup, const char* invitername, int result)
{
	JoinFixedGroupRspInfo* pJoinFixedGroupRspInfo = new JoinFixedGroupRspInfo;
	FixedGroupInfo* pFixedGroupInfo = &pJoinFixedGroupRspInfo->group;
	pFixedGroupInfo->name_ = fixedGroup->name_;
	pFixedGroupInfo->id_ = fixedGroup->id_;
	pFixedGroupInfo->type_ = fixedGroup->type_;
	pFixedGroupInfo->readonly_ = fixedGroup->readonly_==0?false:true;
	pFixedGroupInfo->creator_ = fixedGroup->creator_;
	pFixedGroupInfo->uri_ = fixedGroup->uri_;
	pFixedGroupInfo->groupno_ = fixedGroup->groupno_;
	pFixedGroupInfo->desc_ = fixedGroup->desc_;
	pFixedGroupInfo->bulletin_ = fixedGroup->bulletin_;
	pFixedGroupInfo->owneruri_ = fixedGroup->owneruri_;
	pFixedGroupInfo->capacity_ = fixedGroup->capacity_;
	pFixedGroupInfo->needpermit_ = fixedGroup->needpermit_;

	pJoinFixedGroupRspInfo->name = invitername;
	pJoinFixedGroupRspInfo->result = result;

	::PostMessage(m_pCBaseDlg->GetSafeHwnd(), WM_GROUP_JOIN_FIXED_RSP, 0, (LPARAM)pJoinFixedGroupRspInfo);
}

void CALLBACK SignalMgr::OnMemberAdded(const UCFixedGroup* fixedGroup, const UCContact* member)
{
	GroupMemberChangedInfo* pGroupMemberChangedInfo = new GroupMemberChangedInfo;
	FixedGroupInfo* pFixedGroupInfo = &pGroupMemberChangedInfo->group;
	pFixedGroupInfo->name_ = fixedGroup->name_;
	pFixedGroupInfo->id_ = fixedGroup->id_;
	pFixedGroupInfo->type_ = fixedGroup->type_;
	pFixedGroupInfo->readonly_ = fixedGroup->readonly_==0?false:true;
	pFixedGroupInfo->creator_ = fixedGroup->creator_;
	pFixedGroupInfo->uri_ = fixedGroup->uri_;
	pFixedGroupInfo->groupno_ = fixedGroup->groupno_;
	pFixedGroupInfo->desc_ = fixedGroup->desc_;
	pFixedGroupInfo->bulletin_ = fixedGroup->bulletin_;
	pFixedGroupInfo->owneruri_ = fixedGroup->owneruri_;
	pFixedGroupInfo->capacity_ = fixedGroup->capacity_;
	pFixedGroupInfo->needpermit_ = fixedGroup->needpermit_;

	pGroupMemberChangedInfo->name_ = member->name_;
	pGroupMemberChangedInfo->ucAcc_ = member->ucAcc_;
	pGroupMemberChangedInfo->id_ = member->id_;
	pGroupMemberChangedInfo->uri_ = member->uri_;
	pGroupMemberChangedInfo->type = 0;

	::PostMessage(m_pCBaseDlg->GetSafeHwnd(), WM_GROUP_MEMBER_CHANGED, 0, (LPARAM)pGroupMemberChangedInfo);
}

void CALLBACK SignalMgr::OnMemberRemoved(const UCFixedGroup* fixedGroup, const UCContact* member)
{
	GroupMemberChangedInfo* pGroupMemberChangedInfo = new GroupMemberChangedInfo;
	FixedGroupInfo* pFixedGroupInfo = &pGroupMemberChangedInfo->group;
	pFixedGroupInfo->name_ = fixedGroup->name_;
	pFixedGroupInfo->id_ = fixedGroup->id_;
	pFixedGroupInfo->type_ = fixedGroup->type_;
	pFixedGroupInfo->readonly_ = fixedGroup->readonly_==0?false:true;
	pFixedGroupInfo->creator_ = fixedGroup->creator_;
	pFixedGroupInfo->uri_ = fixedGroup->uri_;
	pFixedGroupInfo->groupno_ = fixedGroup->groupno_;
	pFixedGroupInfo->desc_ = fixedGroup->desc_;
	pFixedGroupInfo->bulletin_ = fixedGroup->bulletin_;
	pFixedGroupInfo->owneruri_ = fixedGroup->owneruri_;
	pFixedGroupInfo->capacity_ = fixedGroup->capacity_;
	pFixedGroupInfo->needpermit_ = fixedGroup->needpermit_;

	pGroupMemberChangedInfo->name_ = member->name_;
	pGroupMemberChangedInfo->ucAcc_ = member->ucAcc_;
	pGroupMemberChangedInfo->type = 1;

	::PostMessage(m_pCBaseDlg->GetSafeHwnd(), WM_GROUP_MEMBER_CHANGED, 0, (LPARAM)pGroupMemberChangedInfo);
}

void CALLBACK SignalMgr::OnMemberFlowChanged(const UCFixedGroup* fixedGroup, const UCContact* member)
{

}

void CALLBACK SignalMgr::OnFixedGroupInfoChanged(const UCFixedGroup* fixedGroup)
{

}