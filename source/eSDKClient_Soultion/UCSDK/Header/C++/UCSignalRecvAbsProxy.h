#ifndef _UC_SIGNALRECV_ABS_PROXY_H_
#define _UC_SIGNALRECV_ABS_PROXY_H_

#include "DataType.h"


namespace eSDK {
	namespace UC {


/**
 *信号管理类
 * 
 *该类用于定义信号回调函数
 *
 *@attention	无
 *@par 			无
**/
class UCSDK_API UCSignalRecvAbsProxy
{
public:

	/**
	 *登录登出回调函数
	 * 
	 *该函数用于登录登出回调函数
	 *
	 *@param[in] 	state		登陆状态 参考UCSDK_SIGNIN_STATE_E
	 *@param[in] 	reason		参考 DataType.h 定义UCSDK_SIGNIN_NOK
	 *@attention	无
	 *@par 			无
	**/
	virtual void OnClientSignInNotify(int state, const std::string& reason) = 0;

	/**
	 *联系人状态改变回调函数
	 * 
	 *该函数用于联系人状态改变回调函数
	 *
	 *@param[in] 	state		状态
	 *@param[in] 	desc		
	 *@param[in] 	contact
	 *@param[in] 	param
	 *@attention	无
	 *@par 			无
	**/
	virtual void OnStatusChanged(CONTACT_AVAILABILITY_E state, const std::string& desc, const UCSDKContact& contact, const std::string& param) = 0;

	/**
	 *联系人列表变更回调函数
	 * 
	 *该函数用于联系人列表变更回调函数
	 *
	 *@attention	无
	 *@par 			无
	**/
	virtual void OnIncreContactsChanged(void) = 0;

	/**
	 *语音来电（包括：会议和VoIP）回调函数
	 * 
	 *该函数用于语音来电（包括：会议和VoIP）回调函数
	 *
	 *@param[in] 	propMap		
	 *@param[in] 	memberlist	成员列表，如果是会议则memberlist[0]是会议主席
	 *@param[in] 	avParam		视频参数
	 *@attention	无
	 *@par 			无
	**/
	virtual void OnAVSessAdded(const ConversationPropMap& propMap, const AccountList& memberlist, const STAudioVideoParam& avParam) = 0;

	/**
	 *语音通话建立（包括：会议和VoIP）回调函数
	 * 
	 *该函数用于语音通话建立（包括：会议和VoIP）回调函数
	 *
	 *@param[in] 	convId		会话ID
	 *@attention	无
	 *@par 			无
	**/
	virtual void OnAVSessionConnected(const std::string& convId) = 0;

	/**
	 *语音通话关闭（包括：会议和VoIP）回调函数
	 * 
	 *该函数用于语音通话关闭（包括：会议和VoIP）回调函数
	 *
	 *@param[in] 	convId		会话ID
	 *@attention	无
	 *@par 			无
	**/
	virtual void OnAVSessionClosed(const std::string& convId) = 0;

	/**
	 *会议成员状态变化回调函数
	 * 
	 *该函数用于会议成员状态变化回调函数
	 *
	 *@param[in] 	convId		会话ID
	 *@param[in] 	chgtype		会议状态 参考MEM_CHG_STATUS_E
	 *@param[in] 	memberuri	会议成员uri
	 *@attention	无
	 *@par 			无
	**/
	virtual void OnConvMemberStatusChanged(const std::string& convId, int chgtype, const std::string& memberuri) = 0;

	/**
	 *与会者允许发言回调函数
	 * 
	 *该函数用于与会者允许发言回调函数
	 *
	 *@param[in] 	convId		会话ID
	 *@param[in] 	member		与会成员
	 *@attention	无
	 *@par 			无
	**/
	virtual void OnConvMemAllowSpeak(const std::string& convId, const UCSDKContact& member) = 0;

	/**
	 *与会者禁止发言回调函数
	 * 
	 *该函数用于与会者禁止发言回调函数
	 *
	 *@param[in] 	convId		会话ID
	 *@param[in] 	member		与会成员
	 *@attention	无
	 *@par 			无
	**/
	virtual void OnConvMemForbidSpeak(const std::string& convId, const UCSDKContact& member) = 0;

	/**
	 *与会者正在发言回调函数
	 * 
	 *该函数用于与会者正在发言回调函数
	 *
	 *@param[in] 	convId		会话ID
	 *@param[in] 	member		与会成员
	 *@attention	无
	 *@par 			无
	**/
	virtual void OnConvMemCurSpeaker(const std::string& convId, const UCSDKContact& member) = 0;

	/**
	 *与会成员变动回调函数
	 * 
	 *该函数用于与会成员变动回调函数
	 *
	 *@param[in] 	convId		会话ID
	 *@param[in] 	chgtype		参考 GROUP_MEM_CHANGED_E
	 *@param[in] 	memberuri	会议成员uri
	 *@attention	无
	 *@par 			无
	**/
	virtual void OnConvGroupMemberChanged(const std::string& convId, int chgtype, const std::string& memberuri) = 0;

	/**
	 *接收即时消息回调函数
	 * 
	 *该函数用于接收即时消息回调函数
	 *
	 *@param[in] 	propMap
	 *@param[in] 	memberlist	成员列表，如果是会议则memberlist[0]是会议主席
	 *@param[in] 	ImMessage	IM消息
	 *@attention	无
	 *@par 			无
	**/
	virtual void OnReceivedIMMessage(const ConversationPropMap& propMap, const AccountList& memberlist, const IMMessage& ImMessage) = 0;

	/**
	 *临时群组关闭回调函数
	 * 
	 *该函数用于临时群组关闭回调函数
	 *
	 *@param[in] 	convId
	 *@attention	无
	 *@par 			无
	**/
	virtual void OnInstantSessRemoved(const std::string& convId) = 0;

	/**
	 *加入临时群组回调函数
	 * 
	 *该函数用于加入临时群组回调函数
	 *
	 *@param[in] 	convId
	 *@param[in] 	member
	 *@attention	无
	 *@par 			无
	**/
	virtual void OnInstantSessAdded(const std::string& convId, const UCSDKContact& member) = 0;

	/**
	 *接收系统消息回调函数
	 * 
	 *该函数用于接收系统消息回调函数
	 *
	 *@param[in] 	origin
	 *@param[in] 	subject
	 *@param[in] 	content
	 *@param[in] 	rcv_time
	 *@param[in] 	msgid
	 *@param[in] 	msgtype
	 *@attention	参考 IMMessage
	 *@par 			无
	**/
	virtual void OnSysMsgRecved(const std::string& origin, const std::string& subject, const std::string& content, const std::string& rcv_time, const std::string& msgid, int msgtype) = 0;

	/**
	 *被邀请加入群组回调函数
	 * 
	 *该函数用于被邀请加入群组回调函数
	 *
	 *@param[in] 	fixedGroup
	 *@attention	无
	 *@par 			无
	**/
	virtual void OnGroupInvitation(const UCSDKFixedGroup& fixedGroup) = 0;

	/**
	 *被邀请的联系人应答加入群组回调函数
	 * 
	 *该函数用于被邀请的联系人应答加入群组回调函数
	 *
	 *@param[in] 	fixedGroup
	 *@param[in] 	invitername
	 *@param[in] 	result			1同意，其他拒绝
	 *@attention	无
	 *@par 			无
	**/
	virtual void OnGroupInvitationRes(const UCSDKFixedGroup& fixedGroup, const std::string& invitername, int result) = 0;

	/**
	 *离开固定群组回调函数
	 * 
	 *该函数用于离开固定群组回调函数
	 *
	 *@param[in] 	fixedGroup
	 *@param[in] 	reason			0: 被踢出群组, 1: 群组解散
	 *@attention	无
	 *@par 			无
	**/
	virtual void OnLeaveFromFixedGroup(const UCSDKFixedGroup& fixedGroup, int reason) = 0;

	/**
	 *请求加入固定群组回调函数
	 * 
	 *该函数用于请求加入固定群组回调函数
	 *
	 *@param[in] 	fixedGroup
	 *@param[in] 	inviteruri
	 *@attention	无
	 *@par 			无
	**/
	virtual void OnJoinFixedGroupRequest(const UCSDKFixedGroup& fixedGroup, const std::string& inviteruri) = 0;

	/**
	 *请求加入固定群组返回回调函数
	 * 
	 *该函数用于请求加入固定群组返回回调函数
	 *
	 *@param[in] 	fixedGroup
	 *@param[in] 	invitername
	 *@param[in] 	result			1同意，其他拒绝
	 *@attention	无
	 *@par 			无
	**/
	virtual void OnJoinFixedGroupRes(const UCSDKFixedGroup& fixedGroup, const std::string& invitername, int result) = 0;

	/**
	 *群组成员增加回调函数
	 * 
	 *该函数用于群组成员增加回调函数
	 *
	 *@param[in] 	fixedGroup
	 *@param[in] 	member
	 *@attention	无
	 *@par 			无
	**/
	virtual void OnMemberAdded(const UCSDKFixedGroup& fixedGroup, const UCSDKContact& member) = 0;

	/**
	 *群组成员离开回调函数
	 * 
	 *该函数用于群组成员离开回调函数
	 *
	 *@param[in] 	fixedGroup
	 *@param[in] 	member
	 *@attention	无
	 *@par 			无
	**/
	virtual void OnMemberRemoved(const UCSDKFixedGroup& fixedGroup, const UCSDKContact& member) = 0;

	/**
	 *群组管理员变更回调函数
	 * 
	 *该函数用于群组管理员变更回调函数
	 *
	 *@param[in] 	fixedGroup
	 *@param[in] 	member
	 *@attention	无
	 *@par 			无
	**/
	virtual void OnMemberFlowChanged(const UCSDKFixedGroup& fixedGroup, const UCSDKContact& member) = 0;

	/**
	 *群组信息变更回调函数
	 * 
	 *该函数用于群组信息变更回调函数
	 *
	 *@param[in] 	fixedGroup
	 *@attention	无
	 *@par 			无
	**/
	virtual void OnFixedGroupInfoChanged(const UCSDKFixedGroup& fixedGroup) = 0;

	/**
	 *收到文件传输回调函数
	 * 
	 *该函数用于收到文件传输回调函数
	 *
	 *@param[in] 	fileid
	 *@param[in] 	filename
	 *@param[in] 	filesize
	 *@param[in] 	originName
	 *@attention	无
	 *@par 			无
	**/
	virtual void OnNewFileRercved(const std::string& fileid, const std::string& filename, int filesize, const std::string& originName) = 0;

	/**
	 *接收文件回调函数
	 * 
	 *该函数用于接收文件回调函数
	 *
	 *@param[in] 	fileid
	 *@attention	无
	 *@par 			无
	**/
	virtual void OnFileAccept(const std::string& fileid) = 0;

	/**
	 *取消文件传输回调函数
	 * 
	 *该函数用于取消文件传输回调函数
	 *
	 *@param[in] 	fileid
	 *@param[in] 	reason
	 *@param[in] 	errcode
	 *@attention	无
	 *@par 			无
	**/
	virtual void OnFileCancel(const std::string& fileid, const std::string& reason, const std::string& errcode) = 0;

	/**
	 *文件传输进度回调函数
	 * 
	 *该函数用于文件传输进度回调函数
	 *
	 *@param[in] 	fileid
	 *@param[in] 	procent
	 *@attention	无
	 *@par 			无
	**/
	virtual void OnFileProgress(const std::string& fileid, const std::string& procent) = 0;
};

}
}

#endif
