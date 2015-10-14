#ifndef __UT_UC_SIGNAL_RECV_H__
#define __UT_UC_SIGNAL_RECV_H__

class UT_UCSignalRecv
{
public:
	static void CALLBACK OnLoginCB(int state, const char* reason);
	static void CALLBACK OnStatusCB(int state, const char* desc, const UCContact* contact, const char* param);
	static void CALLBACK OnAVSessAdded(const UCConversationPropMap* propMap, const UCAccountList* memberlist, const UCAudioVideoParam* avParam);
	static void CALLBACK OnAVSessConnected(const char* convId);
	static void CALLBACK OnAVSessClosed(const char* convId);
	static void CALLBACK OnReceivedIM(const UCConversationPropMap* propMap, const UCAccountList* memberlist, const UCIMMessage* ImMessage);
	static void CALLBACK OnConvMemberStatusChanged(const char* convId, int chgtype, const char* memberuri);
	static void CALLBACK OnConvMemAllowSpeak(const char* convId, const UCContact* member);
	static void CALLBACK OnConvMemForbidSpeak(const char* convId, const UCContact* member);
	static void CALLBACK OnConvMemCurSpeaker(const char* convId, const UCContact* member);
	static void CALLBACK OnConvGroupMemberChanged(const char* convId, int chgtype, const char* memberuri);
	static void CALLBACK OnInstantSessRemoved(const char* convId);
	static void CALLBACK OnGroupInvitation(const UCFixedGroup* fixedGroup);
	static void CALLBACK OnGroupInvitationRes(const UCFixedGroup* fixedGroup, const char* invitername, int result);
	static void CALLBACK OnLeaveFromFixedGroup(const UCFixedGroup* fixedGroup, int reason);
	static void CALLBACK OnJoinFixedGroupRequest(const UCFixedGroup* fixedGroup, const char* inviteruri);
	static void CALLBACK OnJoinFixedGroupRes(const UCFixedGroup* fixedGroup, const char* invitername, int result);
	static void CALLBACK OnMemberAdded(const UCFixedGroup* fixedGroup, const UCContact* member);
	static void CALLBACK OnMemberRemoved(const UCFixedGroup* fixedGroup, const UCContact* member);
	static void CALLBACK OnMemberFlowChanged(const UCFixedGroup* fixedGroup, const UCContact* member);
	static void CALLBACK OnFixedGroupInfoChanged(const UCFixedGroup* fixedGroup);	
};

#endif