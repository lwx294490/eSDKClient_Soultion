#ifndef _UC_MEETING_PROXY_H_
#define _UC_MEETING_PROXY_H_

#include "UCMeetingAbsProxy.h"


namespace eSDK {
	namespace UC {


class UCMeetingProxy : public UCMeetingAbsProxy
{
private:
	UCMeetingProxy();
	~UCMeetingProxy();

public:
	static UCMeetingProxy* Instance();
	static void Destroy();

public:
	//����������ʱȺ��
	virtual int MakeMeetingGroup(const UCSDKContactList& memberlist, std::string& convId);
	//��ʼ����
	virtual int StartMeeting(const std::string& convId);
	//���ջ�������
	virtual int AcceptMeeting(const std::string& convId);
	//���ӻ����Ա
	virtual int AddParticipant(const UCSDKContact& member, const std::string& convId);
	//������������Ա
	virtual int ConnectParticipant(const UCSDKContact& member, const std::string& convId);
	//ɾ������Ա
	virtual int RemoveParticipant(const UCSDKContact& member, const std::string& convId);
	//ǿ������Ա�ǳ�
	virtual int KickParticipant(const UCSDKContact& member, const std::string& convId);

	//������Ա����
	virtual int Mute(const UCSDKContact& member, const std::string& convId);
	//������Աȡ������
	virtual int UnMute(const UCSDKContact& member, const std::string& convId);

	//��ȡԤԼ�����б�
	virtual int GetBookConfList(UCSDKBookConfList& bookConfList);
	//����ԤԼ����
	virtual int JoinMeeting(std::string& convId, const UCSDKBookConfInfo& meetingInfo);
	//�뿪ԤԼ����
	virtual int LeaveMeeting(const std::string& convId);

public:
	int Init();
	int UnInit();

	//��������
private:
	uc::model::conversation::Conversation* GetConversation(const std::string& convId);
	uc::model::conversation::AVSession* GetAVSession(const std::string& convId);
	uc::model::conversation::AVSession* GetAVSession(conversation::Conversation* pConversation) const;
	int FindContact(Contact& contact, const UCSDKContact& member) const;
	void CopyContactToContact(const Contact& first, Contact& second) const;

private:
	uc::model::UCClient* m_pUCClient;
	uc::model::conversation::ConversationMgr* m_pConvManager;

private:
	static UCMeetingProxy* m_pUCMeetingProxy;
};

}
}

#endif
