#ifndef _UC_MEETING_HEADER_
#define _UC_MEETING_HEADER_

#include "DataDef.h"


#ifdef __cplusplus
extern "C"
{
#endif

	/**
	 *����������ʱȺ��
	 * 
	 *�ú������ڴ���������ʱȺ�飬�ɷ��ͼ�ʱ��Ϣ�Ļ���
	 *
	 *@param[in] 	memberlist	����Ա�б�
	 *@param[out] 	convId		����ỰconversationID
	 *@return 		�ɹ���0		ʧ�ܣ���0,�ο�������
	 *@attention	������������ʱ����MakeMeetingGroup()��Ȼ��StartMeeting()
	 *@par 			��
	**/
	UCSDK_API int UCSDK_CALL MakeMeetingGroup(const UCContactList* memberlist, char convId[CONVID_LENGTH]);

	/**
	 *��ʼ��������
	 * 
	 *�ú������ڿ�ʼ��������
	 *
	 *@param[in] 	convId		����ỰconversationID
	 *@return 		�ɹ���0		ʧ�ܣ���0,�ο�������
	 *@attention	��ʹ��MakeMeetingGroup��ȡconvId
	 *@par 			��
	**/
	UCSDK_API int UCSDK_CALL StartMeeting(const char* convId);

	/**
	 *���ջ�������
	 * 
	 *�ú������ڽ��ջ�������
	 *
	 *@param[in] 	convId
	 *@return 		�ɹ���0		ʧ�ܣ���0,�ο�������
	 *@attention	Ҳ����ʹ��UCVoIPAbsProxy::Accept();
	 *@par 			��
	**/
	UCSDK_API int UCSDK_CALL AcceptMeeting(const char* convId);

	/**
	 *��������Ա
	 * 
	 *�ú���������������Ա
	 *
	 *@param[in] 	member
	 *@param[in] 	convId
	 *@return 		�ɹ���0		ʧ�ܣ���0,�ο�������
	 *@attention	��
	 *@par 			��
	**/
	UCSDK_API int UCSDK_CALL AddParticipant(const UCContact* member, const char* convId);

	/**
	 *��������Ա
	 * 
	 *�ú���������������Ա
	 *
	 *@param[in] 	member
	 *@param[in] 	convId
	 *@return 		�ɹ���0		ʧ�ܣ���0,�ο�������
	 *@attention	��
	 *@par 			��
	**/
	UCSDK_API int UCSDK_CALL ConnectParticipant(const UCContact* member, const char* convId);

	/**
	 *ɾ������Ա
	 * 
	 *�ú�������ɾ������Ա
	 *
	 *@param[in] 	member
	 *@param[in] 	convId
	 *@return 		�ɹ���0		ʧ�ܣ���0,�ο�������
	 *@attention	��
	 *@par 			��
	**/
	UCSDK_API int UCSDK_CALL RemoveParticipant(const UCContact* member, const char* convId);

	/**
	 *ǿ������Ա�ǳ�
	 * 
	 *�ú�������ǿ������Ա�ǳ�
	 *
	 *@param[in] 	member
	 *@param[in] 	convId
	 *@return 		�ɹ���0		ʧ�ܣ���0,�ο�������
	 *@attention	��
	 *@par 			��
	**/
	UCSDK_API int UCSDK_CALL KickParticipant(const UCContact* member, const char* convId);

	/**
	 *������Ա����
	 * 
	 *�ú������ڶ�����Ա����
	 *
	 *@param[in] 	member
	 *@param[in] 	convId
	 *@return 		�ɹ���0		ʧ�ܣ���0,�ο�������
	 *@attention	��
	 *@par 			��
	**/
	UCSDK_API int UCSDK_CALL MuteMeeting(const UCContact* member, const char* convId);

	/**
	 *������Աȡ������
	 * 
	 *�ú������ڶ�����Աȡ������
	 *
	 *@param[in] 	member
	 *@param[in] 	convId
	 *@return 		�ɹ���0		ʧ�ܣ���0,�ο�������
	 *@attention	��
	 *@par 			��
	**/
	UCSDK_API int UCSDK_CALL UnMuteMeeting(const UCContact* member, const char* convId);

	/**
	 *��ȡԤԼ�����б�
	 * 
	 *�ú������ڻ�ȡԤԼ�����б�
	 *
	 *@param[in]	iFrom		��ʼindex
	 *@param[in]	iTo			����index	��Χ����[iFrom, iTo]
	 *@param[out] 	bookConfList
	 *@return 		�ɹ���0		ʧ�ܣ���0,�ο�������
	 *@attention	ȷ��iFrom��iTo��Ч����bookConfList�ڴ汣��һ��,UCBookConfList�����UCBookConf�����attendeelistʹ������GetBookConfAttendeelistById��ȡ
	 *@par 			��
	**/
	UCSDK_API int UCSDK_CALL GetBookConfList(int iFrom, int iTo, UCBookConfList* bookConfList);

	/**
	 *����ԤԼ����
	 * 
	 *�ú������ڼ���ԤԼ����
	 *
	 *@param[in] 	meetingInfo
	 *@param[out] 	convId
	 *@return 		�ɹ���0		ʧ�ܣ���0,�ο�������
	 *@attention	��
	 *@par 			��
	**/
	UCSDK_API int UCSDK_CALL JoinMeeting(const UCBookConf* meetingInfo, char convId[CONVID_LENGTH]);

	/**
	 *�뿪����
	 * 
	 *�ú��������뿪����
	 *
	 *@param[in] 	convId
	 *@return 		�ɹ���0		ʧ�ܣ���0,�ο�������
	 *@attention	��
	 *@par 			��
	**/
	UCSDK_API int UCSDK_CALL LeaveMeeting(const char* convId);


#ifdef __cplusplus
}
#endif 


#endif