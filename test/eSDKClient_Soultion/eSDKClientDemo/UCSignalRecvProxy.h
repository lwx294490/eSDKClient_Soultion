/*****************************************************************
 filename    :    UCSignalRecvProxy.h
 author      :    yWX200189
 created     :    2014/05/14
 description :    信号管理实现类，用于创建实例对象注册到UCSDK中，实现消息回调
 copyright   :    Copyright (c) 2012-2016 Huawei Tech.Co.,Ltd
 history     :    2014/05/14 初始版本
*****************************************************************/

#ifndef _UC_SIGNAL_RECV_PROXY_HEADER_
#define _UC_SIGNAL_RECV_PROXY_HEADER_


class UCSignalRecvProxy : public UCSignalRecvAbsProxy
{
public:
	UCSignalRecvProxy();
	~UCSignalRecvProxy();

public:
	//登录登出
	virtual void OnClientSignInNotify(int state, const std::string& reason);
	//联系人状态改变
	virtual void OnStatusChanged(CONTACT_AVAILABILITY_E state, const std::string& desc, const UCSDKContact& contact, const std::string& param);
	//联系人列表变更
	virtual void OnIncreContactsChanged(void);
	//语音视频来电
	virtual void OnAVSessAdded(const ConversationPropMap& propMap, const AccountList& memberlist, const STAudioVideoParam& avParam);
	//语音视频通话建立
	virtual void OnAVSessionConnected(const std::string& convId);
	//语音视频通话断开
	virtual void OnAVSessionClosed(const std::string& convId);
	//会议成员状态变动
	virtual void OnConvMemberStatusChanged(const std::string& convId, int chgtype, const std::string& memberuri);
	//会议成员允许发言
	virtual void OnConvMemAllowSpeak(const std::string& convId, const UCSDKContact& member);
	//会议成员禁止发言
	virtual void OnConvMemForbidSpeak(const std::string& convId, const UCSDKContact& member);
	//会议成员正在发言
	virtual void OnConvMemCurSpeaker(const std::string& convId, const UCSDKContact& member);
	//会议成员离开或者加入
	virtual void OnConvGroupMemberChanged(const std::string& convId, int chgtype, const std::string& memberuri);
	//即时消息接收
	virtual void OnReceivedIMMessage(const ConversationPropMap& propMap, const AccountList& memberlist, const IMMessage& ImMessage);
	//临时群组关闭
	virtual void OnInstantSessRemoved(const std::string& convId);
	//加入临时群组
	virtual void OnInstantSessAdded(const std::string& convId, const UCSDKContact& member);
	//系统消息接收
	virtual void OnSysMsgRecved(const std::string& origin, const std::string& subject, const std::string& content, const std::string& rcv_time, const std::string& msgid, int msgtype);
	//固定群组邀请
	virtual void OnGroupInvitation(const UCSDKFixedGroup& fixedGroup);
	//固定群组邀请返回
	virtual void OnGroupInvitationRes(const UCSDKFixedGroup& fixedGroup, const std::string& invitername, int result);
	//离开固定群组或者固定群组解散
	virtual void OnLeaveFromFixedGroup(const UCSDKFixedGroup& fixedGroup, int reason);
	//加入固定群组请求
	virtual void OnJoinFixedGroupRequest(const UCSDKFixedGroup& fixedGroup, const std::string& inviteruri);
	//加入固定群组请求返回
	virtual void OnJoinFixedGroupRes(const UCSDKFixedGroup& fixedGroup, const std::string& invitername, int result);
	//固定群组成员增加
	virtual void OnMemberAdded(const UCSDKFixedGroup& fixedGroup, const UCSDKContact& member);
	//固定群组成员离开
	virtual void OnMemberRemoved(const UCSDKFixedGroup& fixedGroup, const UCSDKContact& member);
	//固定群组管理员变更
	virtual void OnMemberFlowChanged(const UCSDKFixedGroup& fixedGroup, const UCSDKContact& member);
	//固定群组信息变更
	virtual void OnFixedGroupInfoChanged(const UCSDKFixedGroup& fixedGroup);
	//收到文件传输
	virtual void OnNewFileRercved(const std::string& fileid, const std::string& filename, int filesize, const std::string& originName);
	//文件同意接收
	virtual void OnFileAccept(const std::string& fileid);
	//文件拒绝接收
	virtual void OnFileCancel(const std::string& fileid, const std::string& reason, const std::string& errcode);
	//文件传输进度
	virtual void OnFileProgress(const std::string& fileid, const std::string& procent);

public:
	CDialog* m_pDlg;	//CBaseDlg类指针
};

#endif