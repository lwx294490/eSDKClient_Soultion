#ifndef _UC_SIGNAL_RECV_PROXY_HEADER_
#define _UC_SIGNAL_RECV_PROXY_HEADER_

#include "UCSignalRecvAbsProxy.h"
#include "DataDef.h"

using namespace eSDK::UC;


class UCSignalRecvProxy : public UCSignalRecvAbsProxy
{
public:
	static UCSignalRecvProxy* Instance();
	static void Destroy();

public:
	virtual void OnClientSignInNotify(int state, const std::string& reason);
	virtual void OnStatusChanged(CONTACT_AVAILABILITY_E state, const std::string& desc, const UCSDKContact& contact, const std::string& param);
	virtual void OnIncreContactsChanged(void);
	virtual void OnAVSessAdded(const ConversationPropMap& propMap, const AccountList& memberlist, const STAudioVideoParam& avParam);
	virtual void OnAVSessionConnected(const std::string& convId);
	virtual void OnAVSessionClosed(const std::string& convId);
	virtual void OnConvMemberStatusChanged(const std::string& convId, int chgtype, const std::string& memberuri);
	virtual void OnConvMemAllowSpeak(const std::string& convId, const UCSDKContact& member);
	virtual void OnConvMemForbidSpeak(const std::string& convId, const UCSDKContact& member);
	virtual void OnConvMemCurSpeaker(const std::string& convId, const UCSDKContact& member);
	virtual void OnConvGroupMemberChanged(const std::string& convId, int chgtype, const std::string& memberuri);
	virtual void OnReceivedIMMessage(const ConversationPropMap& propMap, const AccountList& memberlist, const IMMessage& ImMessage);
	virtual void OnInstantSessRemoved(const std::string& convId);
	virtual void OnInstantSessAdded(const std::string& convId, const UCSDKContact& member);
	virtual void OnSysMsgRecved(const std::string& origin, const std::string& subject, const std::string& content, const std::string& rcv_time, const std::string& msgid, int msgtype);
	virtual void OnGroupInvitation(const UCSDKFixedGroup& fixedGroup);
	virtual void OnGroupInvitationRes(const UCSDKFixedGroup& fixedGroup, const std::string& invitername, int result);
	virtual void OnLeaveFromFixedGroup(const UCSDKFixedGroup& fixedGroup, int reason);
	virtual void OnJoinFixedGroupRequest(const UCSDKFixedGroup& fixedGroup, const std::string& inviteruri);
	virtual void OnJoinFixedGroupRes(const UCSDKFixedGroup& fixedGroup, const std::string& invitername, int result);
	virtual void OnMemberAdded(const UCSDKFixedGroup& fixedGroup, const UCSDKContact& member);
	virtual void OnMemberRemoved(const UCSDKFixedGroup& fixedGroup, const UCSDKContact& member);
	virtual void OnMemberFlowChanged(const UCSDKFixedGroup& fixedGroup, const UCSDKContact& member);
	virtual void OnFixedGroupInfoChanged(const UCSDKFixedGroup& fixedGroup);
	virtual void OnNewFileRercved(const std::string& fileid, const std::string& filename, int filesize, const std::string& originName);
	virtual void OnFileAccept(const std::string& fileid);
	virtual void OnFileCancel(const std::string& fileid, const std::string& reason, const std::string& errcode);
	virtual void OnFileProgress(const std::string& fileid, const std::string& procent);

public:
	//保存ISV设置的回调函数指针
	UCClientSignInNotify			m_fpClientSignInNotify;
	UCStatusChanged					m_fpStatusChanged;
	UCIncreContactsChanged			m_fpIncreContactsChanged;
	UCAVSessAdded					m_fpAVSessAdded;
	UCAVSessionConnected			m_fpAVSessionConnected;
	UCAVSessionClosed				m_fpAVSessionClosed;
	UCConvMemberStatusChanged		m_fpConvMemberStatusChanged;
	UCConvMemAllowSpeak				m_fpConvMemAllowSpeak;
	UCConvMemForbidSpeak			m_fpConvMemForbidSpeak;
	UCConvMemCurSpeaker				m_fpConvMemCurSpeaker;
	UCConvGroupMemberChanged		m_fpConvGroupMemberChanged;
	UCReceivedIMMessage				m_fpReceivedIMMessage;
	UCInstantSessRemoved			m_fpInstantSessRemoved;
	UCInstantSessAdded				m_fpInstantSessAdded;
	UCSysMsgRecved					m_fpSysMsgRecved;
	UCGroupInvitation				m_fpGroupInvitation;
	UCGroupInvitationRes			m_fpGroupInvitationRes;
	UCLeaveFromFixedGroup			m_fpLeaveFromFixedGroup;
	UCJoinFixedGroupRequest			m_fpJoinFixedGroupRequest;
	UCJoinFixedGroupRes				m_fpJoinFixedGroupRes;
	UCMemberAdded					m_fpMemberAdded;
	UCMemberRemoved					m_fpMemberRemoved;
	UCMemberFlowChanged				m_fpMemberFlowChanged;
	UCFixedGroupInfoChanged			m_fpFixedGroupInfoChanged;
	UCNewFileRercved				m_fpNewFileRercved;
	UCFileAccept					m_fpFileAccept;
	UCFileCancel					m_fpFileCancel;
	UCFileProgress					m_fpFileProgress;

private:
	UCSignalRecvProxy();
	static UCSignalRecvProxy* m_pUCSignalRecvProxy;
};

#endif
