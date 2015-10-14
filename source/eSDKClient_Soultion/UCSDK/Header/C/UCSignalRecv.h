#ifndef _UC_SIGNALRECV_HEADER_
#define _UC_SIGNALRECV_HEADER_

#include "DataDef.h"


#ifdef __cplusplus
extern "C"
{
#endif

	/**
	 *���õ�¼�ǳ��ص�����
	 * 
	 *�ú����������õ�¼�ǳ��ص�����
	 *
	 *@param[in] 	fpSignInNotify	����ָ��
	 *@return 		�ɹ���0		ʧ�ܣ���0,�ο�������
	 *@attention	����ָ�����Ͳο�DataType.h
	 *@par 			��
	**/
	UCSDK_API int UCSDK_CALL OnClientSignInNotify(const UCClientSignInNotify fpClientSignInNotify);

	/**
	 *������ϵ��״̬�ı�ص�����
	 * 
	 *�ú�������������ϵ��״̬�ı�ص�����
	 *
	 *@param[in] 	fpStatusChanged	����ָ��
	 *@return 		�ɹ���0		ʧ�ܣ���0,�ο�������
	 *@attention	����ָ�����Ͳο�DataType.h
	 *@par 			��
	**/
	UCSDK_API int UCSDK_CALL OnStatusChanged(const UCStatusChanged fpStatusChanged);

	/**
	 *������ϵ���б����ص�����
	 * 
	 *�ú�������������ϵ���б����ص�����
	 *
	 *@param[in] 	fpIncreContactsChanged	����ָ��
	 *@return 		�ɹ���0		ʧ�ܣ���0,�ο�������
	 *@attention	����ָ�����Ͳο�DataType.h
	 *@par 			��
	**/
	UCSDK_API int UCSDK_CALL OnIncreContactsChanged(const UCIncreContactsChanged fpIncreContactsChanged);

	/**
	 *�����������磨�����������VoIP���ص�����
	 * 
	 *�ú�������������������ص�����
	 *
	 *@param[in] 	fpAVSessAdded	����ָ��
	 *@return 		�ɹ���0		ʧ�ܣ���0,�ο�������
	 *@attention	����ָ�����Ͳο�DataType.h
	 *@par 			��
	**/
	UCSDK_API int UCSDK_CALL OnAVSessAdded(const UCAVSessAdded fpAVSessAdded);

	/**
	 *��������ͨ�������������������VoIP���ص�����
	 * 
	 *�ú���������������ͨ�������ص�����
	 *
	 *@param[in] 	fpAVSessionConnected	����ָ��
	 *@return 		�ɹ���0		ʧ�ܣ���0,�ο�������
	 *@attention	����ָ�����Ͳο�DataType.h
	 *@par 			��
	**/
	UCSDK_API int UCSDK_CALL OnAVSessionConnected(const UCAVSessionConnected fpAVSessionConnected);

	/**
	 *��������ͨ���رգ������������VoIP���ص�����
	 * 
	 *�ú���������������ͨ���رջص�����
	 *
	 *@param[in] 	fpAVSessionClosed	����ָ��
	 *@return 		�ɹ���0		ʧ�ܣ���0,�ο�������
	 *@attention	����ָ�����Ͳο�DataType.h
	 *@par 			��
	**/
	UCSDK_API int UCSDK_CALL OnAVSessionClosed(const UCAVSessionClosed fpAVSessionClosed);

	/**
	 *���û����Ա״̬�仯�ص�����
	 * 
	 *�ú����������û����Ա״̬�仯�ص�����
	 *
	 *@param[in] 	fpConvMemberStatusChanged	����ָ��
	 *@return 		�ɹ���0		ʧ�ܣ���0,�ο�������
	 *@attention	����ָ�����Ͳο�DataType.h
	 *@par 			��
	**/
	UCSDK_API int UCSDK_CALL OnConvMemberStatusChanged(const UCConvMemberStatusChanged fpConvMemberStatusChanged);

	/**
	 *��������������Իص�����
	 * 
	 *�ú���������������������Իص�����
	 *
	 *@param[in] 	fpConvMemAllowSpeak	����ָ��
	 *@return 		�ɹ���0		ʧ�ܣ���0,�ο�������
	 *@attention	����ָ�����Ͳο�DataType.h
	 *@par 			��
	**/
	UCSDK_API int UCSDK_CALL OnConvMemAllowSpeak(const UCConvMemAllowSpeak fpConvMemAllowSpeak);

	/**
	 *��������߽�ֹ���Իص�����
	 * 
	 *�ú���������������߽�ֹ���Իص�����
	 *
	 *@param[in] 	fpConvMemForbidSpeak	����ָ��
	 *@return 		�ɹ���0		ʧ�ܣ���0,�ο�������
	 *@attention	����ָ�����Ͳο�DataType.h
	 *@par 			��
	**/
	UCSDK_API int UCSDK_CALL OnConvMemForbidSpeak(const UCConvMemForbidSpeak fpConvMemForbidSpeak);

	/**
	 *������������ڷ��Իص�����
	 * 
	 *�ú�������������������ڷ��Իص�����
	 *
	 *@param[in] 	fpConvMemCurSpeaker	����ָ��
	 *@return 		�ɹ���0		ʧ�ܣ���0,�ο�������
	 *@attention	����ָ�����Ͳο�DataType.h
	 *@par 			��
	**/
	UCSDK_API int UCSDK_CALL OnConvMemCurSpeaker(const UCConvMemCurSpeaker fpConvMemCurSpeaker);

	/**
	 *��������Ա�䶯�ص�����
	 * 
	 *�ú���������������Ա�䶯�ص�����
	 *
	 *@param[in] 	fpConvGroupMemberChanged	����ָ��
	 *@return 		�ɹ���0		ʧ�ܣ���0,�ο�������
	 *@attention	����ָ�����Ͳο�DataType.h
	 *@par 			��
	**/
	UCSDK_API int UCSDK_CALL OnConvGroupMemberChanged(const UCConvGroupMemberChanged fpConvGroupMemberChanged);

	/**
	 *���ý��ռ�ʱ��Ϣ�ص�����
	 * 
	 *�ú����������ý��ռ�ʱ��Ϣ�ص�����
	 *
	 *@param[in] 	fpReceivedIMMessage	����ָ��
	 *@return 		�ɹ���0		ʧ�ܣ���0,�ο�������
	 *@attention	����ָ�����Ͳο�DataType.h
	 *@par 			��
	**/
	UCSDK_API int UCSDK_CALL OnReceivedIMMessage(const UCReceivedIMMessage fpReceivedIMMessage);

	/**
	 *������ʱȺ��رջص�����
	 * 
	 *�ú�������������ʱȺ��رջص�����
	 *
	 *@param[in] 	fpInstantSessRemoved	����ָ��
	 *@return 		�ɹ���0		ʧ�ܣ���0,�ο�������
	 *@attention	����ָ�����Ͳο�DataType.h
	 *@par 			��
	**/
	UCSDK_API int UCSDK_CALL OnInstantSessRemoved(const UCInstantSessRemoved fpInstantSessRemoved);

	/**
	 *���ü�����ʱȺ��ص�����
	 * 
	 *�ú����������ü�����ʱȺ��ص�����
	 *
	 *@param[in] 	fpInstantSessAdded	����ָ��
	 *@return 		�ɹ���0		ʧ�ܣ���0,�ο�������
	 *@attention	����ָ�����Ͳο�DataType.h
	 *@par 			��
	**/
	UCSDK_API int UCSDK_CALL OnInstantSessAdded(const UCInstantSessAdded fpInstantSessAdded);

	/**
	 *���ý���ϵͳ��Ϣ�ص�����
	 * 
	 *�ú����������ý���ϵͳ��Ϣ�ص�����
	 *
	 *@param[in] 	fpSysMsgRecved	����ָ��
	 *@return 		�ɹ���0		ʧ�ܣ���0,�ο�������
	 *@attention	����ָ�����Ͳο�DataType.h
	 *@par 			��
	**/
	UCSDK_API int UCSDK_CALL OnSysMsgRecved(const UCSysMsgRecved fpSysMsgRecved);

	/**
	 *���ñ��������Ⱥ��ص�����
	 * 
	 *�ú����������ñ��������Ⱥ��ص�����
	 *
	 *@param[in] 	fpGroupInvitation	����ָ��
	 *@return 		�ɹ���0		ʧ�ܣ���0,�ο�������
	 *@attention	����ָ�����Ͳο�DataType.h
	 *@par 			��
	**/
	UCSDK_API int UCSDK_CALL OnGroupInvitation(const UCGroupInvitation fpGroupInvitation);

	/**
	 *���ñ��������ϵ��Ӧ�����Ⱥ��ص�����
	 * 
	 *�ú����������ñ��������ϵ��Ӧ�����Ⱥ��ص�����
	 *
	 *@param[in] 	fpGroupInvitationRes	����ָ��
	 *@return 		�ɹ���0		ʧ�ܣ���0,�ο�������
	 *@attention	����ָ�����Ͳο�DataType.h
	 *@par 			��
	**/
	UCSDK_API int UCSDK_CALL OnGroupInvitationRes(const UCGroupInvitationRes fpGroupInvitationRes);

	/**
	 *�����뿪�̶�Ⱥ��ص�����
	 * 
	 *�ú������������뿪�̶�Ⱥ��ص�����
	 *
	 *@param[in] 	fpLeaveFromFixedGroup	����ָ��
	 *@return 		�ɹ���0		ʧ�ܣ���0,�ο�������
	 *@attention	����ָ�����Ͳο�DataType.h
	 *@par 			��
	**/
	UCSDK_API int UCSDK_CALL OnLeaveFromFixedGroup(const UCLeaveFromFixedGroup fpLeaveFromFixedGroup);

	/**
	 *�����������̶�Ⱥ��ص�����
	 * 
	 *�ú������������������̶�Ⱥ��ص�����
	 *
	 *@param[in] 	fpJoinFixedGroupRequest	����ָ��
	 *@return 		�ɹ���0		ʧ�ܣ���0,�ο�������
	 *@attention	����ָ�����Ͳο�DataType.h
	 *@par 			��
	**/
	UCSDK_API int UCSDK_CALL OnJoinFixedGroupRequest(const UCJoinFixedGroupRequest fpJoinFixedGroupRequest);

	/**
	 *�����������̶�Ⱥ�鷵�ػص�����
	 * 
	 *�ú������������������̶�Ⱥ�鷵�ػص�����
	 *
	 *@param[in] 	fpJoinFixedGroupRes	����ָ��
	 *@return 		�ɹ���0		ʧ�ܣ���0,�ο�������
	 *@attention	����ָ�����Ͳο�DataType.h
	 *@par 			��
	**/
	UCSDK_API int UCSDK_CALL OnJoinFixedGroupRes(const UCJoinFixedGroupRes fpJoinFixedGroupRes);

	/**
	 *����Ⱥ���Ա���ӻص�����
	 * 
	 *�ú�����������Ⱥ���Ա���ӻص�����
	 *
	 *@param[in] 	fpMemberAdded	����ָ��
	 *@return 		�ɹ���0		ʧ�ܣ���0,�ο�������
	 *@attention	����ָ�����Ͳο�DataType.h
	 *@par 			��
	**/
	UCSDK_API int UCSDK_CALL OnMemberAdded(const UCMemberAdded fpMemberAdded);

	/**
	 *����Ⱥ���Ա�뿪�ص�����
	 * 
	 *�ú�����������Ⱥ���Ա�뿪�ص�����
	 *
	 *@param[in] 	fpMemberRemoved	����ָ��
	 *@return 		�ɹ���0		ʧ�ܣ���0,�ο�������
	 *@attention	����ָ�����Ͳο�DataType.h
	 *@par 			��
	**/
	UCSDK_API int UCSDK_CALL OnMemberRemoved(const UCMemberRemoved fpMemberRemoved);

	/**
	 *����Ⱥ�����Ա����ص�����
	 * 
	 *�ú�����������Ⱥ�����Ա����ص�����
	 *
	 *@param[in] 	fpMemberFlowChanged	����ָ��
	 *@return 		�ɹ���0		ʧ�ܣ���0,�ο�������
	 *@attention	����ָ�����Ͳο�DataType.h
	 *@par 			��
	**/
	UCSDK_API int UCSDK_CALL OnMemberFlowChanged(const UCMemberFlowChanged fpMemberFlowChanged);

	/**
	 *����Ⱥ����Ϣ����ص�����
	 * 
	 *�ú�����������Ⱥ����Ϣ����ص�����
	 *
	 *@param[in] 	fpFixedGroupInfoChanged	����ָ��
	 *@return 		�ɹ���0		ʧ�ܣ���0,�ο�������
	 *@attention	����ָ�����Ͳο�DataType.h
	 *@par 			��
	**/
	UCSDK_API int UCSDK_CALL OnFixedGroupInfoChanged(const UCFixedGroupInfoChanged fpFixedGroupInfoChanged);

	/**
	 *�����յ��ļ�����ص�����
	 * 
	 *�ú������������յ��ļ�����ص�����
	 *
	 *@param[in] 	fpNewFileRercved	����ָ��
	 *@return 		�ɹ���0		ʧ�ܣ���0,�ο�������
	 *@attention	����ָ�����Ͳο�DataType.h
	 *@par 			��
	**/
	UCSDK_API int UCSDK_CALL OnNewFileRercved(const UCNewFileRercved fpNewFileRercved);

	/**
	 *���ý����ļ��ص�����
	 * 
	 *�ú����������ý����ļ��ص�����
	 *
	 *@param[in] 	fpFileAccept	����ָ��
	 *@return 		�ɹ���0		ʧ�ܣ���0,�ο�������
	 *@attention	����ָ�����Ͳο�DataType.h
	 *@par 			��
	**/
	UCSDK_API int UCSDK_CALL OnFileAccept(const UCFileAccept fpFileAccept);

	/**
	 *����ȡ���ļ�����ص�����
	 * 
	 *�ú�����������ȡ���ļ�����ص�����
	 *
	 *@param[in] 	fpFileCancel	����ָ��
	 *@return 		�ɹ���0		ʧ�ܣ���0,�ο�������
	 *@attention	����ָ�����Ͳο�DataType.h
	 *@par 			��
	**/
	UCSDK_API int UCSDK_CALL OnFileCancel(const UCFileCancel fpFileCancel);

	/**
	 *�����ļ�������Ȼص�����
	 * 
	 *�ú������������ļ�������Ȼص�����
	 *
	 *@param[in] 	fpFileProgress	����ָ��
	 *@return 		�ɹ���0		ʧ�ܣ���0,�ο�������
	 *@attention	����ָ�����Ͳο�DataType.h
	 *@par 			��
	**/
	UCSDK_API int UCSDK_CALL OnFileProgress(const UCFileProgress fpFileProgress);


#ifdef __cplusplus
}
#endif 


#endif