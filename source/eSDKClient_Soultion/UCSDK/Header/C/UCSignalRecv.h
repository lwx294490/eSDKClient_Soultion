#ifndef _UC_SIGNALRECV_HEADER_
#define _UC_SIGNALRECV_HEADER_

#include "DataDef.h"


#ifdef __cplusplus
extern "C"
{
#endif

	/**
	 *设置登录登出回调函数
	 * 
	 *该函数用于设置登录登出回调函数
	 *
	 *@param[in] 	fpSignInNotify	函数指针
	 *@return 		成功：0		失败：非0,参考返回码
	 *@attention	函数指针类型参考DataType.h
	 *@par 			无
	**/
	UCSDK_API int UCSDK_CALL OnClientSignInNotify(const UCClientSignInNotify fpClientSignInNotify);

	/**
	 *设置联系人状态改变回调函数
	 * 
	 *该函数用于设置联系人状态改变回调函数
	 *
	 *@param[in] 	fpStatusChanged	函数指针
	 *@return 		成功：0		失败：非0,参考返回码
	 *@attention	函数指针类型参考DataType.h
	 *@par 			无
	**/
	UCSDK_API int UCSDK_CALL OnStatusChanged(const UCStatusChanged fpStatusChanged);

	/**
	 *设置联系人列表变更回调函数
	 * 
	 *该函数用于设置联系人列表变更回调函数
	 *
	 *@param[in] 	fpIncreContactsChanged	函数指针
	 *@return 		成功：0		失败：非0,参考返回码
	 *@attention	函数指针类型参考DataType.h
	 *@par 			无
	**/
	UCSDK_API int UCSDK_CALL OnIncreContactsChanged(const UCIncreContactsChanged fpIncreContactsChanged);

	/**
	 *设置语音来电（包括：会议和VoIP）回调函数
	 * 
	 *该函数用于设置语音来电回调函数
	 *
	 *@param[in] 	fpAVSessAdded	函数指针
	 *@return 		成功：0		失败：非0,参考返回码
	 *@attention	函数指针类型参考DataType.h
	 *@par 			无
	**/
	UCSDK_API int UCSDK_CALL OnAVSessAdded(const UCAVSessAdded fpAVSessAdded);

	/**
	 *设置语音通话建立（包括：会议和VoIP）回调函数
	 * 
	 *该函数用于设置语音通话建立回调函数
	 *
	 *@param[in] 	fpAVSessionConnected	函数指针
	 *@return 		成功：0		失败：非0,参考返回码
	 *@attention	函数指针类型参考DataType.h
	 *@par 			无
	**/
	UCSDK_API int UCSDK_CALL OnAVSessionConnected(const UCAVSessionConnected fpAVSessionConnected);

	/**
	 *设置语音通话关闭（包括：会议和VoIP）回调函数
	 * 
	 *该函数用于设置语音通话关闭回调函数
	 *
	 *@param[in] 	fpAVSessionClosed	函数指针
	 *@return 		成功：0		失败：非0,参考返回码
	 *@attention	函数指针类型参考DataType.h
	 *@par 			无
	**/
	UCSDK_API int UCSDK_CALL OnAVSessionClosed(const UCAVSessionClosed fpAVSessionClosed);

	/**
	 *设置会议成员状态变化回调函数
	 * 
	 *该函数用于设置会议成员状态变化回调函数
	 *
	 *@param[in] 	fpConvMemberStatusChanged	函数指针
	 *@return 		成功：0		失败：非0,参考返回码
	 *@attention	函数指针类型参考DataType.h
	 *@par 			无
	**/
	UCSDK_API int UCSDK_CALL OnConvMemberStatusChanged(const UCConvMemberStatusChanged fpConvMemberStatusChanged);

	/**
	 *设置与会者允许发言回调函数
	 * 
	 *该函数用于设置与会者允许发言回调函数
	 *
	 *@param[in] 	fpConvMemAllowSpeak	函数指针
	 *@return 		成功：0		失败：非0,参考返回码
	 *@attention	函数指针类型参考DataType.h
	 *@par 			无
	**/
	UCSDK_API int UCSDK_CALL OnConvMemAllowSpeak(const UCConvMemAllowSpeak fpConvMemAllowSpeak);

	/**
	 *设置与会者禁止发言回调函数
	 * 
	 *该函数用于设置与会者禁止发言回调函数
	 *
	 *@param[in] 	fpConvMemForbidSpeak	函数指针
	 *@return 		成功：0		失败：非0,参考返回码
	 *@attention	函数指针类型参考DataType.h
	 *@par 			无
	**/
	UCSDK_API int UCSDK_CALL OnConvMemForbidSpeak(const UCConvMemForbidSpeak fpConvMemForbidSpeak);

	/**
	 *设置与会者正在发言回调函数
	 * 
	 *该函数用于设置与会者正在发言回调函数
	 *
	 *@param[in] 	fpConvMemCurSpeaker	函数指针
	 *@return 		成功：0		失败：非0,参考返回码
	 *@attention	函数指针类型参考DataType.h
	 *@par 			无
	**/
	UCSDK_API int UCSDK_CALL OnConvMemCurSpeaker(const UCConvMemCurSpeaker fpConvMemCurSpeaker);

	/**
	 *设置与会成员变动回调函数
	 * 
	 *该函数用于设置与会成员变动回调函数
	 *
	 *@param[in] 	fpConvGroupMemberChanged	函数指针
	 *@return 		成功：0		失败：非0,参考返回码
	 *@attention	函数指针类型参考DataType.h
	 *@par 			无
	**/
	UCSDK_API int UCSDK_CALL OnConvGroupMemberChanged(const UCConvGroupMemberChanged fpConvGroupMemberChanged);

	/**
	 *设置接收即时消息回调函数
	 * 
	 *该函数用于设置接收即时消息回调函数
	 *
	 *@param[in] 	fpReceivedIMMessage	函数指针
	 *@return 		成功：0		失败：非0,参考返回码
	 *@attention	函数指针类型参考DataType.h
	 *@par 			无
	**/
	UCSDK_API int UCSDK_CALL OnReceivedIMMessage(const UCReceivedIMMessage fpReceivedIMMessage);

	/**
	 *设置临时群组关闭回调函数
	 * 
	 *该函数用于设置临时群组关闭回调函数
	 *
	 *@param[in] 	fpInstantSessRemoved	函数指针
	 *@return 		成功：0		失败：非0,参考返回码
	 *@attention	函数指针类型参考DataType.h
	 *@par 			无
	**/
	UCSDK_API int UCSDK_CALL OnInstantSessRemoved(const UCInstantSessRemoved fpInstantSessRemoved);

	/**
	 *设置加入临时群组回调函数
	 * 
	 *该函数用于设置加入临时群组回调函数
	 *
	 *@param[in] 	fpInstantSessAdded	函数指针
	 *@return 		成功：0		失败：非0,参考返回码
	 *@attention	函数指针类型参考DataType.h
	 *@par 			无
	**/
	UCSDK_API int UCSDK_CALL OnInstantSessAdded(const UCInstantSessAdded fpInstantSessAdded);

	/**
	 *设置接收系统消息回调函数
	 * 
	 *该函数用于设置接收系统消息回调函数
	 *
	 *@param[in] 	fpSysMsgRecved	函数指针
	 *@return 		成功：0		失败：非0,参考返回码
	 *@attention	函数指针类型参考DataType.h
	 *@par 			无
	**/
	UCSDK_API int UCSDK_CALL OnSysMsgRecved(const UCSysMsgRecved fpSysMsgRecved);

	/**
	 *设置被邀请加入群组回调函数
	 * 
	 *该函数用于设置被邀请加入群组回调函数
	 *
	 *@param[in] 	fpGroupInvitation	函数指针
	 *@return 		成功：0		失败：非0,参考返回码
	 *@attention	函数指针类型参考DataType.h
	 *@par 			无
	**/
	UCSDK_API int UCSDK_CALL OnGroupInvitation(const UCGroupInvitation fpGroupInvitation);

	/**
	 *设置被邀请的联系人应答加入群组回调函数
	 * 
	 *该函数用于设置被邀请的联系人应答加入群组回调函数
	 *
	 *@param[in] 	fpGroupInvitationRes	函数指针
	 *@return 		成功：0		失败：非0,参考返回码
	 *@attention	函数指针类型参考DataType.h
	 *@par 			无
	**/
	UCSDK_API int UCSDK_CALL OnGroupInvitationRes(const UCGroupInvitationRes fpGroupInvitationRes);

	/**
	 *设置离开固定群组回调函数
	 * 
	 *该函数用于设置离开固定群组回调函数
	 *
	 *@param[in] 	fpLeaveFromFixedGroup	函数指针
	 *@return 		成功：0		失败：非0,参考返回码
	 *@attention	函数指针类型参考DataType.h
	 *@par 			无
	**/
	UCSDK_API int UCSDK_CALL OnLeaveFromFixedGroup(const UCLeaveFromFixedGroup fpLeaveFromFixedGroup);

	/**
	 *设置请求加入固定群组回调函数
	 * 
	 *该函数用于设置请求加入固定群组回调函数
	 *
	 *@param[in] 	fpJoinFixedGroupRequest	函数指针
	 *@return 		成功：0		失败：非0,参考返回码
	 *@attention	函数指针类型参考DataType.h
	 *@par 			无
	**/
	UCSDK_API int UCSDK_CALL OnJoinFixedGroupRequest(const UCJoinFixedGroupRequest fpJoinFixedGroupRequest);

	/**
	 *设置请求加入固定群组返回回调函数
	 * 
	 *该函数用于设置请求加入固定群组返回回调函数
	 *
	 *@param[in] 	fpJoinFixedGroupRes	函数指针
	 *@return 		成功：0		失败：非0,参考返回码
	 *@attention	函数指针类型参考DataType.h
	 *@par 			无
	**/
	UCSDK_API int UCSDK_CALL OnJoinFixedGroupRes(const UCJoinFixedGroupRes fpJoinFixedGroupRes);

	/**
	 *设置群组成员增加回调函数
	 * 
	 *该函数用于设置群组成员增加回调函数
	 *
	 *@param[in] 	fpMemberAdded	函数指针
	 *@return 		成功：0		失败：非0,参考返回码
	 *@attention	函数指针类型参考DataType.h
	 *@par 			无
	**/
	UCSDK_API int UCSDK_CALL OnMemberAdded(const UCMemberAdded fpMemberAdded);

	/**
	 *设置群组成员离开回调函数
	 * 
	 *该函数用于设置群组成员离开回调函数
	 *
	 *@param[in] 	fpMemberRemoved	函数指针
	 *@return 		成功：0		失败：非0,参考返回码
	 *@attention	函数指针类型参考DataType.h
	 *@par 			无
	**/
	UCSDK_API int UCSDK_CALL OnMemberRemoved(const UCMemberRemoved fpMemberRemoved);

	/**
	 *设置群组管理员变更回调函数
	 * 
	 *该函数用于设置群组管理员变更回调函数
	 *
	 *@param[in] 	fpMemberFlowChanged	函数指针
	 *@return 		成功：0		失败：非0,参考返回码
	 *@attention	函数指针类型参考DataType.h
	 *@par 			无
	**/
	UCSDK_API int UCSDK_CALL OnMemberFlowChanged(const UCMemberFlowChanged fpMemberFlowChanged);

	/**
	 *设置群组信息变更回调函数
	 * 
	 *该函数用于设置群组信息变更回调函数
	 *
	 *@param[in] 	fpFixedGroupInfoChanged	函数指针
	 *@return 		成功：0		失败：非0,参考返回码
	 *@attention	函数指针类型参考DataType.h
	 *@par 			无
	**/
	UCSDK_API int UCSDK_CALL OnFixedGroupInfoChanged(const UCFixedGroupInfoChanged fpFixedGroupInfoChanged);

	/**
	 *设置收到文件传输回调函数
	 * 
	 *该函数用于设置收到文件传输回调函数
	 *
	 *@param[in] 	fpNewFileRercved	函数指针
	 *@return 		成功：0		失败：非0,参考返回码
	 *@attention	函数指针类型参考DataType.h
	 *@par 			无
	**/
	UCSDK_API int UCSDK_CALL OnNewFileRercved(const UCNewFileRercved fpNewFileRercved);

	/**
	 *设置接收文件回调函数
	 * 
	 *该函数用于设置接收文件回调函数
	 *
	 *@param[in] 	fpFileAccept	函数指针
	 *@return 		成功：0		失败：非0,参考返回码
	 *@attention	函数指针类型参考DataType.h
	 *@par 			无
	**/
	UCSDK_API int UCSDK_CALL OnFileAccept(const UCFileAccept fpFileAccept);

	/**
	 *设置取消文件传输回调函数
	 * 
	 *该函数用于设置取消文件传输回调函数
	 *
	 *@param[in] 	fpFileCancel	函数指针
	 *@return 		成功：0		失败：非0,参考返回码
	 *@attention	函数指针类型参考DataType.h
	 *@par 			无
	**/
	UCSDK_API int UCSDK_CALL OnFileCancel(const UCFileCancel fpFileCancel);

	/**
	 *设置文件传输进度回调函数
	 * 
	 *该函数用于设置文件传输进度回调函数
	 *
	 *@param[in] 	fpFileProgress	函数指针
	 *@return 		成功：0		失败：非0,参考返回码
	 *@attention	函数指针类型参考DataType.h
	 *@par 			无
	**/
	UCSDK_API int UCSDK_CALL OnFileProgress(const UCFileProgress fpFileProgress);


#ifdef __cplusplus
}
#endif 


#endif