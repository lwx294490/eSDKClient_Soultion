#ifndef _UC_MESSAGE_SIGNAL_PROCESS_H_
#define _UC_MESSAGE_SIGNAL_PROCESS_H_

#include "UCSignalRecvAbsProxy.h"


namespace eSDK {
	namespace UC {


class UCMessageSignalProcess : public has_slots<sigslot::multi_threaded_local>
{
public:
	UCMessageSignalProcess();
	~UCMessageSignalProcess();

	//Sign In Signal
public:
	void OnSignInNotify(UCClient::SignInState _state, std::string _reason);

	//StatusChange Signal
public:	
	void OnStatusChanged(ContactAvailability _state,std::string _desc,const Contact& _contact, std::string _param);
	
	//Contact Sync
public:
	void OnIncreContactsChanged(std::string param);

	//AVSession Signal
public:
	void OnAVSessionRinged(conversation::Conversation* _con);
	void OnAVSessAdded(conversation::Conversation* _con,  conversation::sAudioVideoParam _param);
	void OnAVSessionConnected(conversation::Conversation* _con);
	void OnAVSessionClosed(conversation::Conversation* _con,conversation::sMsgAVSessionClosedParam _param);

	//conference  Signal
public:
	void OnConvMemberStatusChanged(conversation::Conversation* _con, int _chgtype, std::string _uri);
	void OnConvMemAllowSpeak(conversation::Conversation* _con, conversation::Participant _parti);
	void OnConvMemForbidSpeak(conversation::Conversation* _con, conversation::Participant _parti);
	void OnConvMemCurSpeaker(conversation::Conversation* _con, std::string _uri);
	void OnConvGroupMemberChanged(conversation::Conversation* _con,std::vector<std::string> _kicklist,std::vector<std::string> _addlist);	

	//InstantMessage Signal
public:
	void OnInstantSessAdded(conversation::Conversation* _con);
	void OnInstantSessRemoved(conversation::Conversation* _con);
	void OnReceivedIMMessage(std::string _converstationID, conversation::sImMsgItem _ImMessage);
	void OnSystemMsgReceived(const sSysMsgItem& _item);

	//FixedGroup Signal
public:
	void OnGroupInvitation(const uc::model::FixedGroup _group, std::string _uri, std::string _name, std::string _direct);
	void OnGroupInvitationRes(const uc::model::FixedGroup _group, std::string invitername, int result);
	void OnLeaveFromFixedGroup(const uc::model::FixedGroup _group, int reason);
	void OnJoinFixedGroupRequest(const uc::model::FixedGroup _group, std::string inviteruri, std::string invitername);
	void OnJoinFixedGroupRes(const uc::model::FixedGroup _group, std::string invitername, int result);
	void OnMemberAdded(const uc::model::FixedGroup _group, uc::model::Contact _contact);
	void OnMemberRemoved(const uc::model::FixedGroup _group, uc::model::Contact _contact);
	void OnMemberFlowChanged(const uc::model::FixedGroup _group, uc::model::Contact _contact);
	void OnFixedGroupInfoChanged(const uc::model::FixedGroup _group);

	//File  Signal
public:
	void OnNewFileRercved();
	void OnFileAccept();
	void OnFileCancel();
	void OnFileProgress();

public:
	void SetUCSignalRecvAbsProxy(UCSignalRecvAbsProxy* pUCSignalRecvAbsProxy) { m_pUCSignalRecvAbsProxy = pUCSignalRecvAbsProxy; }

private:
	INSTANT_MSG_TYPE_E InstantMsgType2INSTANT_MSG_TYPE_E(uc::model::conversation::InstantMsgType type);

private:
	UCSignalRecvAbsProxy* m_pUCSignalRecvAbsProxy;
};

}
}

#endif
