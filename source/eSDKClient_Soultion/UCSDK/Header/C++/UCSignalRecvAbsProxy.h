#ifndef _UC_SIGNALRECV_ABS_PROXY_H_
#define _UC_SIGNALRECV_ABS_PROXY_H_

#include "DataType.h"


namespace eSDK {
	namespace UC {


/**
 *�źŹ�����
 * 
 *�������ڶ����źŻص�����
 *
 *@attention	��
 *@par 			��
**/
class UCSDK_API UCSignalRecvAbsProxy
{
public:

	/**
	 *��¼�ǳ��ص�����
	 * 
	 *�ú������ڵ�¼�ǳ��ص�����
	 *
	 *@param[in] 	state		��½״̬ �ο�UCSDK_SIGNIN_STATE_E
	 *@param[in] 	reason		�ο� DataType.h ����UCSDK_SIGNIN_NOK
	 *@attention	��
	 *@par 			��
	**/
	virtual void OnClientSignInNotify(int state, const std::string& reason) = 0;

	/**
	 *��ϵ��״̬�ı�ص�����
	 * 
	 *�ú���������ϵ��״̬�ı�ص�����
	 *
	 *@param[in] 	state		״̬
	 *@param[in] 	desc		
	 *@param[in] 	contact
	 *@param[in] 	param
	 *@attention	��
	 *@par 			��
	**/
	virtual void OnStatusChanged(CONTACT_AVAILABILITY_E state, const std::string& desc, const UCSDKContact& contact, const std::string& param) = 0;

	/**
	 *��ϵ���б����ص�����
	 * 
	 *�ú���������ϵ���б����ص�����
	 *
	 *@attention	��
	 *@par 			��
	**/
	virtual void OnIncreContactsChanged(void) = 0;

	/**
	 *�������磨�����������VoIP���ص�����
	 * 
	 *�ú��������������磨�����������VoIP���ص�����
	 *
	 *@param[in] 	propMap		
	 *@param[in] 	memberlist	��Ա�б�����ǻ�����memberlist[0]�ǻ�����ϯ
	 *@param[in] 	avParam		��Ƶ����
	 *@attention	��
	 *@par 			��
	**/
	virtual void OnAVSessAdded(const ConversationPropMap& propMap, const AccountList& memberlist, const STAudioVideoParam& avParam) = 0;

	/**
	 *����ͨ�������������������VoIP���ص�����
	 * 
	 *�ú�����������ͨ�������������������VoIP���ص�����
	 *
	 *@param[in] 	convId		�ỰID
	 *@attention	��
	 *@par 			��
	**/
	virtual void OnAVSessionConnected(const std::string& convId) = 0;

	/**
	 *����ͨ���رգ������������VoIP���ص�����
	 * 
	 *�ú�����������ͨ���رգ������������VoIP���ص�����
	 *
	 *@param[in] 	convId		�ỰID
	 *@attention	��
	 *@par 			��
	**/
	virtual void OnAVSessionClosed(const std::string& convId) = 0;

	/**
	 *�����Ա״̬�仯�ص�����
	 * 
	 *�ú������ڻ����Ա״̬�仯�ص�����
	 *
	 *@param[in] 	convId		�ỰID
	 *@param[in] 	chgtype		����״̬ �ο�MEM_CHG_STATUS_E
	 *@param[in] 	memberuri	�����Աuri
	 *@attention	��
	 *@par 			��
	**/
	virtual void OnConvMemberStatusChanged(const std::string& convId, int chgtype, const std::string& memberuri) = 0;

	/**
	 *����������Իص�����
	 * 
	 *�ú�����������������Իص�����
	 *
	 *@param[in] 	convId		�ỰID
	 *@param[in] 	member		����Ա
	 *@attention	��
	 *@par 			��
	**/
	virtual void OnConvMemAllowSpeak(const std::string& convId, const UCSDKContact& member) = 0;

	/**
	 *����߽�ֹ���Իص�����
	 * 
	 *�ú�����������߽�ֹ���Իص�����
	 *
	 *@param[in] 	convId		�ỰID
	 *@param[in] 	member		����Ա
	 *@attention	��
	 *@par 			��
	**/
	virtual void OnConvMemForbidSpeak(const std::string& convId, const UCSDKContact& member) = 0;

	/**
	 *��������ڷ��Իص�����
	 * 
	 *�ú���������������ڷ��Իص�����
	 *
	 *@param[in] 	convId		�ỰID
	 *@param[in] 	member		����Ա
	 *@attention	��
	 *@par 			��
	**/
	virtual void OnConvMemCurSpeaker(const std::string& convId, const UCSDKContact& member) = 0;

	/**
	 *����Ա�䶯�ص�����
	 * 
	 *�ú�����������Ա�䶯�ص�����
	 *
	 *@param[in] 	convId		�ỰID
	 *@param[in] 	chgtype		�ο� GROUP_MEM_CHANGED_E
	 *@param[in] 	memberuri	�����Աuri
	 *@attention	��
	 *@par 			��
	**/
	virtual void OnConvGroupMemberChanged(const std::string& convId, int chgtype, const std::string& memberuri) = 0;

	/**
	 *���ռ�ʱ��Ϣ�ص�����
	 * 
	 *�ú������ڽ��ռ�ʱ��Ϣ�ص�����
	 *
	 *@param[in] 	propMap
	 *@param[in] 	memberlist	��Ա�б�����ǻ�����memberlist[0]�ǻ�����ϯ
	 *@param[in] 	ImMessage	IM��Ϣ
	 *@attention	��
	 *@par 			��
	**/
	virtual void OnReceivedIMMessage(const ConversationPropMap& propMap, const AccountList& memberlist, const IMMessage& ImMessage) = 0;

	/**
	 *��ʱȺ��رջص�����
	 * 
	 *�ú���������ʱȺ��رջص�����
	 *
	 *@param[in] 	convId
	 *@attention	��
	 *@par 			��
	**/
	virtual void OnInstantSessRemoved(const std::string& convId) = 0;

	/**
	 *������ʱȺ��ص�����
	 * 
	 *�ú������ڼ�����ʱȺ��ص�����
	 *
	 *@param[in] 	convId
	 *@param[in] 	member
	 *@attention	��
	 *@par 			��
	**/
	virtual void OnInstantSessAdded(const std::string& convId, const UCSDKContact& member) = 0;

	/**
	 *����ϵͳ��Ϣ�ص�����
	 * 
	 *�ú������ڽ���ϵͳ��Ϣ�ص�����
	 *
	 *@param[in] 	origin
	 *@param[in] 	subject
	 *@param[in] 	content
	 *@param[in] 	rcv_time
	 *@param[in] 	msgid
	 *@param[in] 	msgtype
	 *@attention	�ο� IMMessage
	 *@par 			��
	**/
	virtual void OnSysMsgRecved(const std::string& origin, const std::string& subject, const std::string& content, const std::string& rcv_time, const std::string& msgid, int msgtype) = 0;

	/**
	 *���������Ⱥ��ص�����
	 * 
	 *�ú������ڱ��������Ⱥ��ص�����
	 *
	 *@param[in] 	fixedGroup
	 *@attention	��
	 *@par 			��
	**/
	virtual void OnGroupInvitation(const UCSDKFixedGroup& fixedGroup) = 0;

	/**
	 *���������ϵ��Ӧ�����Ⱥ��ص�����
	 * 
	 *�ú������ڱ��������ϵ��Ӧ�����Ⱥ��ص�����
	 *
	 *@param[in] 	fixedGroup
	 *@param[in] 	invitername
	 *@param[in] 	result			1ͬ�⣬�����ܾ�
	 *@attention	��
	 *@par 			��
	**/
	virtual void OnGroupInvitationRes(const UCSDKFixedGroup& fixedGroup, const std::string& invitername, int result) = 0;

	/**
	 *�뿪�̶�Ⱥ��ص�����
	 * 
	 *�ú��������뿪�̶�Ⱥ��ص�����
	 *
	 *@param[in] 	fixedGroup
	 *@param[in] 	reason			0: ���߳�Ⱥ��, 1: Ⱥ���ɢ
	 *@attention	��
	 *@par 			��
	**/
	virtual void OnLeaveFromFixedGroup(const UCSDKFixedGroup& fixedGroup, int reason) = 0;

	/**
	 *�������̶�Ⱥ��ص�����
	 * 
	 *�ú��������������̶�Ⱥ��ص�����
	 *
	 *@param[in] 	fixedGroup
	 *@param[in] 	inviteruri
	 *@attention	��
	 *@par 			��
	**/
	virtual void OnJoinFixedGroupRequest(const UCSDKFixedGroup& fixedGroup, const std::string& inviteruri) = 0;

	/**
	 *�������̶�Ⱥ�鷵�ػص�����
	 * 
	 *�ú��������������̶�Ⱥ�鷵�ػص�����
	 *
	 *@param[in] 	fixedGroup
	 *@param[in] 	invitername
	 *@param[in] 	result			1ͬ�⣬�����ܾ�
	 *@attention	��
	 *@par 			��
	**/
	virtual void OnJoinFixedGroupRes(const UCSDKFixedGroup& fixedGroup, const std::string& invitername, int result) = 0;

	/**
	 *Ⱥ���Ա���ӻص�����
	 * 
	 *�ú�������Ⱥ���Ա���ӻص�����
	 *
	 *@param[in] 	fixedGroup
	 *@param[in] 	member
	 *@attention	��
	 *@par 			��
	**/
	virtual void OnMemberAdded(const UCSDKFixedGroup& fixedGroup, const UCSDKContact& member) = 0;

	/**
	 *Ⱥ���Ա�뿪�ص�����
	 * 
	 *�ú�������Ⱥ���Ա�뿪�ص�����
	 *
	 *@param[in] 	fixedGroup
	 *@param[in] 	member
	 *@attention	��
	 *@par 			��
	**/
	virtual void OnMemberRemoved(const UCSDKFixedGroup& fixedGroup, const UCSDKContact& member) = 0;

	/**
	 *Ⱥ�����Ա����ص�����
	 * 
	 *�ú�������Ⱥ�����Ա����ص�����
	 *
	 *@param[in] 	fixedGroup
	 *@param[in] 	member
	 *@attention	��
	 *@par 			��
	**/
	virtual void OnMemberFlowChanged(const UCSDKFixedGroup& fixedGroup, const UCSDKContact& member) = 0;

	/**
	 *Ⱥ����Ϣ����ص�����
	 * 
	 *�ú�������Ⱥ����Ϣ����ص�����
	 *
	 *@param[in] 	fixedGroup
	 *@attention	��
	 *@par 			��
	**/
	virtual void OnFixedGroupInfoChanged(const UCSDKFixedGroup& fixedGroup) = 0;

	/**
	 *�յ��ļ�����ص�����
	 * 
	 *�ú��������յ��ļ�����ص�����
	 *
	 *@param[in] 	fileid
	 *@param[in] 	filename
	 *@param[in] 	filesize
	 *@param[in] 	originName
	 *@attention	��
	 *@par 			��
	**/
	virtual void OnNewFileRercved(const std::string& fileid, const std::string& filename, int filesize, const std::string& originName) = 0;

	/**
	 *�����ļ��ص�����
	 * 
	 *�ú������ڽ����ļ��ص�����
	 *
	 *@param[in] 	fileid
	 *@attention	��
	 *@par 			��
	**/
	virtual void OnFileAccept(const std::string& fileid) = 0;

	/**
	 *ȡ���ļ�����ص�����
	 * 
	 *�ú�������ȡ���ļ�����ص�����
	 *
	 *@param[in] 	fileid
	 *@param[in] 	reason
	 *@param[in] 	errcode
	 *@attention	��
	 *@par 			��
	**/
	virtual void OnFileCancel(const std::string& fileid, const std::string& reason, const std::string& errcode) = 0;

	/**
	 *�ļ�������Ȼص�����
	 * 
	 *�ú��������ļ�������Ȼص�����
	 *
	 *@param[in] 	fileid
	 *@param[in] 	procent
	 *@attention	��
	 *@par 			��
	**/
	virtual void OnFileProgress(const std::string& fileid, const std::string& procent) = 0;
};

}
}

#endif
