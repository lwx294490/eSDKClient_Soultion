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
	//创建会议临时群组
	virtual int MakeMeetingGroup(const UCSDKContactList& memberlist, std::string& convId);
	//开始会议
	virtual int StartMeeting(const std::string& convId);
	//接收会议邀请
	virtual int AcceptMeeting(const std::string& convId);
	//增加会议成员
	virtual int AddParticipant(const UCSDKContact& member, const std::string& convId);
	//重新邀请与会成员
	virtual int ConnectParticipant(const UCSDKContact& member, const std::string& convId);
	//删除与会成员
	virtual int RemoveParticipant(const UCSDKContact& member, const std::string& convId);
	//强制与会成员登出
	virtual int KickParticipant(const UCSDKContact& member, const std::string& convId);

	//对与会成员静音
	virtual int Mute(const UCSDKContact& member, const std::string& convId);
	//对与会成员取消静音
	virtual int UnMute(const UCSDKContact& member, const std::string& convId);

	//获取预约会议列表
	virtual int GetBookConfList(UCSDKBookConfList& bookConfList);
	//加入预约会议
	virtual int JoinMeeting(std::string& convId, const UCSDKBookConfInfo& meetingInfo);
	//离开预约会议
	virtual int LeaveMeeting(const std::string& convId);

public:
	int Init();
	int UnInit();

	//辅助函数
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
