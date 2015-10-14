/*****************************************************************
 filename    :    UCSignalRecvProxy.h
 author      :    yWX200189
 created     :    2014/05/14
 description :    �źŹ���ʵ���࣬���ڴ���ʵ������ע�ᵽUCSDK�У�ʵ����Ϣ�ص�
 copyright   :    Copyright (c) 2012-2016 Huawei Tech.Co.,Ltd
 history     :    2014/05/14 ��ʼ�汾
*****************************************************************/

#ifndef _UC_SIGNAL_RECV_PROXY_HEADER_
#define _UC_SIGNAL_RECV_PROXY_HEADER_


class UCSignalRecvProxy : public UCSignalRecvAbsProxy
{
public:
	UCSignalRecvProxy();
	~UCSignalRecvProxy();

public:
	//��¼�ǳ�
	virtual void OnClientSignInNotify(int state, const std::string& reason);
	//��ϵ��״̬�ı�
	virtual void OnStatusChanged(CONTACT_AVAILABILITY_E state, const std::string& desc, const UCSDKContact& contact, const std::string& param);
	//��ϵ���б���
	virtual void OnIncreContactsChanged(void);
	//������Ƶ����
	virtual void OnAVSessAdded(const ConversationPropMap& propMap, const AccountList& memberlist, const STAudioVideoParam& avParam);
	//������Ƶͨ������
	virtual void OnAVSessionConnected(const std::string& convId);
	//������Ƶͨ���Ͽ�
	virtual void OnAVSessionClosed(const std::string& convId);
	//�����Ա״̬�䶯
	virtual void OnConvMemberStatusChanged(const std::string& convId, int chgtype, const std::string& memberuri);
	//�����Ա������
	virtual void OnConvMemAllowSpeak(const std::string& convId, const UCSDKContact& member);
	//�����Ա��ֹ����
	virtual void OnConvMemForbidSpeak(const std::string& convId, const UCSDKContact& member);
	//�����Ա���ڷ���
	virtual void OnConvMemCurSpeaker(const std::string& convId, const UCSDKContact& member);
	//�����Ա�뿪���߼���
	virtual void OnConvGroupMemberChanged(const std::string& convId, int chgtype, const std::string& memberuri);
	//��ʱ��Ϣ����
	virtual void OnReceivedIMMessage(const ConversationPropMap& propMap, const AccountList& memberlist, const IMMessage& ImMessage);
	//��ʱȺ��ر�
	virtual void OnInstantSessRemoved(const std::string& convId);
	//������ʱȺ��
	virtual void OnInstantSessAdded(const std::string& convId, const UCSDKContact& member);
	//ϵͳ��Ϣ����
	virtual void OnSysMsgRecved(const std::string& origin, const std::string& subject, const std::string& content, const std::string& rcv_time, const std::string& msgid, int msgtype);
	//�̶�Ⱥ������
	virtual void OnGroupInvitation(const UCSDKFixedGroup& fixedGroup);
	//�̶�Ⱥ�����뷵��
	virtual void OnGroupInvitationRes(const UCSDKFixedGroup& fixedGroup, const std::string& invitername, int result);
	//�뿪�̶�Ⱥ����߹̶�Ⱥ���ɢ
	virtual void OnLeaveFromFixedGroup(const UCSDKFixedGroup& fixedGroup, int reason);
	//����̶�Ⱥ������
	virtual void OnJoinFixedGroupRequest(const UCSDKFixedGroup& fixedGroup, const std::string& inviteruri);
	//����̶�Ⱥ�����󷵻�
	virtual void OnJoinFixedGroupRes(const UCSDKFixedGroup& fixedGroup, const std::string& invitername, int result);
	//�̶�Ⱥ���Ա����
	virtual void OnMemberAdded(const UCSDKFixedGroup& fixedGroup, const UCSDKContact& member);
	//�̶�Ⱥ���Ա�뿪
	virtual void OnMemberRemoved(const UCSDKFixedGroup& fixedGroup, const UCSDKContact& member);
	//�̶�Ⱥ�����Ա���
	virtual void OnMemberFlowChanged(const UCSDKFixedGroup& fixedGroup, const UCSDKContact& member);
	//�̶�Ⱥ����Ϣ���
	virtual void OnFixedGroupInfoChanged(const UCSDKFixedGroup& fixedGroup);
	//�յ��ļ�����
	virtual void OnNewFileRercved(const std::string& fileid, const std::string& filename, int filesize, const std::string& originName);
	//�ļ�ͬ�����
	virtual void OnFileAccept(const std::string& fileid);
	//�ļ��ܾ�����
	virtual void OnFileCancel(const std::string& fileid, const std::string& reason, const std::string& errcode);
	//�ļ��������
	virtual void OnFileProgress(const std::string& fileid, const std::string& procent);

public:
	CDialog* m_pDlg;	//CBaseDlg��ָ��
};

#endif