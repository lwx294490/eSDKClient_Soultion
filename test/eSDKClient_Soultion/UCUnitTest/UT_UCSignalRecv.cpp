#include "stdafx.h"
#include "UT_UCSignalRecv.h"

void CALLBACK UT_UCSignalRecv::OnLoginCB(int state, const char* reason)
{

}
void CALLBACK UT_UCSignalRecv::OnStatusCB(int state, const char* desc, const UCContact* contact, const char* param)
{

}
void CALLBACK UT_UCSignalRecv::OnAVSessAdded(const UCConversationPropMap* propMap, const UCAccountList* memberlist, const UCAudioVideoParam* avParam)
{

}
void CALLBACK UT_UCSignalRecv::OnAVSessConnected(const char* convId)
{

}
void CALLBACK UT_UCSignalRecv::OnAVSessClosed(const char* convId)
{

}
void CALLBACK UT_UCSignalRecv::OnReceivedIM(const UCConversationPropMap* propMap, const UCAccountList* memberlist, const UCIMMessage* ImMessage)
{

}
void CALLBACK UT_UCSignalRecv::OnConvMemberStatusChanged(const char* convId, int chgtype, const char* memberuri)
{

}
void CALLBACK UT_UCSignalRecv::OnConvMemAllowSpeak(const char* convId, const UCContact* member)
{

}
void CALLBACK UT_UCSignalRecv::OnConvMemForbidSpeak(const char* convId, const UCContact* member)
{

}
void CALLBACK UT_UCSignalRecv::OnConvMemCurSpeaker(const char* convId, const UCContact* member)
{

}
void CALLBACK UT_UCSignalRecv::OnConvGroupMemberChanged(const char* convId, int chgtype, const char* memberuri)
{

}
void CALLBACK UT_UCSignalRecv::OnInstantSessRemoved(const char* convId)
{

}
void CALLBACK UT_UCSignalRecv::OnGroupInvitation(const UCFixedGroup* fixedGroup)
{

}
void CALLBACK UT_UCSignalRecv::OnGroupInvitationRes(const UCFixedGroup* fixedGroup, const char* invitername, int result)
{

}
void CALLBACK UT_UCSignalRecv::OnLeaveFromFixedGroup(const UCFixedGroup* fixedGroup, int reason)
{

}
void CALLBACK UT_UCSignalRecv::OnJoinFixedGroupRequest(const UCFixedGroup* fixedGroup, const char* inviteruri)
{

}
void CALLBACK UT_UCSignalRecv::OnJoinFixedGroupRes(const UCFixedGroup* fixedGroup, const char* invitername, int result)
{

}
void CALLBACK UT_UCSignalRecv::OnMemberAdded(const UCFixedGroup* fixedGroup, const UCContact* member)
{

}
void CALLBACK UT_UCSignalRecv::OnMemberRemoved(const UCFixedGroup* fixedGroup, const UCContact* member)
{

}
void CALLBACK UT_UCSignalRecv::OnMemberFlowChanged(const UCFixedGroup* fixedGroup, const UCContact* member)
{

}
void CALLBACK UT_UCSignalRecv::OnFixedGroupInfoChanged(const UCFixedGroup* fixedGroup)
{

}