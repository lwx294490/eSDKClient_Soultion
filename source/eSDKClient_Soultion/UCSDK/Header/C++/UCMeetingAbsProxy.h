#ifndef _UC_MEETING_ABS_PROXY_H_
#define _UC_MEETING_ABS_PROXY_H_

#include "DataType.h"


namespace eSDK {
	namespace UC {


/**
 *会议管理类
 * 
 *该类用于会议管理
 *
 *@attention	无
 *@par			无
**/
class UCSDK_API UCMeetingAbsProxy
{
protected:
	UCMeetingAbsProxy();
	virtual ~UCMeetingAbsProxy();

public:
	/**
	 *获取会议管理类单实例
	 * 
	 *该函数用于获取会议管理类单实例
	 *
	 *@return 		成功：会议管理类单实例指针， 失败：NULL
	 *@attention	无
	 *@par 			无
	**/
	static UCMeetingAbsProxy* GetInstance();

	/**
	 *释放会议管理类单实例
	 * 
	 *该函数用于释放会议管理类单实例
	 *
	 *@attention	在调用UCSDKAbsProxy::ReleaseInstance()时候，会跟着一起释放
	 *@par 			无
	**/
	static void ReleaseInstance();

public:
	/**
	 *创建会议临时群组
	 * 
	 *该函数用于创建会议临时群组，可发送即时消息的会议
	 *
	 *@param[in] 	memberlist	与会成员列表
	 *@param[out] 	convId		会议会话conversationID
	 *@return 		成功：0		失败：非0,参考返回码
	 *@attention	创建语音会议时，先MakeMeetingGroup()，然后StartMeeting()
	 *@par 			无
	**/
	virtual int MakeMeetingGroup(const UCSDKContactList& memberlist, std::string& convId) = 0;

	/**
	 *开始语音会议
	 * 
	 *该函数用于开始语音会议
	 *
	 *@param[in] 	convId		会议会话conversationID
	 *@return 		成功：0		失败：非0,参考返回码
	 *@attention	先使用MakeMeetingGroup获取convId
	 *@par 			无
	**/
	virtual int StartMeeting(const std::string& convId) = 0;

	/**
	 *接收会议邀请
	 * 
	 *该函数用于接收会议邀请
	 *
	 *@param[in] 	convId
	 *@return 		成功：0		失败：非0,参考返回码
	 *@attention	也可以使用UCVoIPAbsProxy::Accept();
	 *@par 			无
	**/
	virtual int AcceptMeeting(const std::string& convId) = 0;

	/**
	 *增加与会成员
	 * 
	 *该函数用于增加与会成员
	 *
	 *@param[in] 	member
	 *@param[in] 	convId
	 *@return 		成功：0		失败：非0,参考返回码
	 *@attention	无
	 *@par 			无
	**/
	virtual int AddParticipant(const UCSDKContact& member, const std::string& convId) = 0;

	/**
	 *邀请与会成员
	 * 
	 *该函数用于邀请与会成员
	 *
	 *@param[in] 	member
	 *@param[in] 	convId
	 *@return 		成功：0		失败：非0,参考返回码
	 *@attention	无
	 *@par 			无
	**/
	virtual int ConnectParticipant(const UCSDKContact& member, const std::string& convId) = 0;

	/**
	 *删除与会成员
	 * 
	 *该函数用于删除与会成员
	 *
	 *@param[in] 	member
	 *@param[in] 	convId
	 *@return 		成功：0		失败：非0,参考返回码
	 *@attention	无
	 *@par 			无
	**/
	virtual int RemoveParticipant(const UCSDKContact& member, const std::string& convId) = 0;

	/**
	 *强制与会成员登出
	 * 
	 *该函数用于强制与会成员登出
	 *
	 *@param[in] 	member
	 *@param[in] 	convId
	 *@return 		成功：0		失败：非0,参考返回码
	 *@attention	无
	 *@par 			无
	**/
	virtual int KickParticipant(const UCSDKContact& member, const std::string& convId) = 0;

	/**
	 *对与会成员静音
	 * 
	 *该函数用于对与会成员静音
	 *
	 *@param[in] 	member
	 *@param[in] 	convId
	 *@return 		成功：0		失败：非0,参考返回码
	 *@attention	无
	 *@par 			无
	**/
	virtual int Mute(const UCSDKContact& member, const std::string& convId) = 0;

	/**
	 *对与会成员取消静音
	 * 
	 *该函数用于对与会成员取消静音
	 *
	 *@param[in] 	member
	 *@param[in] 	convId
	 *@return 		成功：0		失败：非0,参考返回码
	 *@attention	无
	 *@par 			无
	**/
	virtual int UnMute(const UCSDKContact& member, const std::string& convId) = 0;

	/**
	 *获取预约会议列表
	 * 
	 *该函数用于获取预约会议列表
	 *
	 *@param[in] 	bookConfList
	 *@return 		成功：0		失败：非0,参考返回码
	 *@attention	无
	 *@par 			无
	**/
	virtual int GetBookConfList(UCSDKBookConfList& bookConfList) = 0;

	/**
	 *加入预约会议
	 * 
	 *该函数用于加入预约会议
	 *
	 *@param[out] 	convId
	 *@param[in] 	meetingInfo
	 *@return 		成功：0		失败：非0,参考返回码
	 *@attention	无
	 *@par 			无
	**/
	virtual int JoinMeeting(std::string& convId, const UCSDKBookConfInfo& meetingInfo) = 0;

	/**
	 *离开会议
	 * 
	 *该函数用于离开会议
	 *
	 *@param[in] 	convId
	 *@return 		成功：0		失败：非0,参考返回码
	 *@attention	无
	 *@par 			无
	**/
	virtual int LeaveMeeting(const std::string& convId) = 0;
};

}
}

#endif