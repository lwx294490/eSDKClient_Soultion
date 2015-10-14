#ifndef _UC_MEETING_HEADER_
#define _UC_MEETING_HEADER_

#include "DataDef.h"


#ifdef __cplusplus
extern "C"
{
#endif

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
	UCSDK_API int UCSDK_CALL MakeMeetingGroup(const UCContactList* memberlist, char convId[CONVID_LENGTH]);

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
	UCSDK_API int UCSDK_CALL StartMeeting(const char* convId);

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
	UCSDK_API int UCSDK_CALL AcceptMeeting(const char* convId);

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
	UCSDK_API int UCSDK_CALL AddParticipant(const UCContact* member, const char* convId);

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
	UCSDK_API int UCSDK_CALL ConnectParticipant(const UCContact* member, const char* convId);

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
	UCSDK_API int UCSDK_CALL RemoveParticipant(const UCContact* member, const char* convId);

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
	UCSDK_API int UCSDK_CALL KickParticipant(const UCContact* member, const char* convId);

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
	UCSDK_API int UCSDK_CALL MuteMeeting(const UCContact* member, const char* convId);

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
	UCSDK_API int UCSDK_CALL UnMuteMeeting(const UCContact* member, const char* convId);

	/**
	 *获取预约会议列表
	 * 
	 *该函数用于获取预约会议列表
	 *
	 *@param[in]	iFrom		起始index
	 *@param[in]	iTo			结束index	范围区间[iFrom, iTo]
	 *@param[out] 	bookConfList
	 *@return 		成功：0		失败：非0,参考返回码
	 *@attention	确保iFrom和iTo有效，与bookConfList内存保持一致,UCBookConfList里面的UCBookConf里面的attendeelist使用下面GetBookConfAttendeelistById获取
	 *@par 			无
	**/
	UCSDK_API int UCSDK_CALL GetBookConfList(int iFrom, int iTo, UCBookConfList* bookConfList);

	/**
	 *加入预约会议
	 * 
	 *该函数用于加入预约会议
	 *
	 *@param[in] 	meetingInfo
	 *@param[out] 	convId
	 *@return 		成功：0		失败：非0,参考返回码
	 *@attention	无
	 *@par 			无
	**/
	UCSDK_API int UCSDK_CALL JoinMeeting(const UCBookConf* meetingInfo, char convId[CONVID_LENGTH]);

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
	UCSDK_API int UCSDK_CALL LeaveMeeting(const char* convId);


#ifdef __cplusplus
}
#endif 


#endif