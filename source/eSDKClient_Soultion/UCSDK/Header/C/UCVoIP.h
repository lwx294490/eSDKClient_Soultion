#ifndef _UC_VOIP_HEADER_
#define _UC_VOIP_HEADER_

#include "DataDef.h"


#ifdef __cplusplus
extern "C"
{
#endif

	/**
	 *����VoIP����Ƶ����
	 * 
	 *�ú������ڴ���VoIP����Ƶ����
	 *
	 *@param[in] 	member		���г�Ա
	 *@param[in] 	iType		�������ͣ��ο�CALL_TYPE_E
	 *@param[in] 	localWnd	������Ƶ����
	 *@param[in] 	remoteWnd	Զ����Ƶ����
	 *@param[out] 	convId		VoIP���лỰID
	 *@return 		�ɹ���0		ʧ�ܣ���0,�ο�������
	 *@attention	���iType��Call_Audio���������У�ʱ����ʹ��localWnd��remoteWnd����
	 *@par 			��
	**/
	UCSDK_API int UCSDK_CALL MakeCall(const UCContact* member, int iType, const UCVideoWindow* localWnd,
										const UCVideoWindow* remoteWnd, char convId[CONVID_LENGTH]);

	/**
	 *����Ӧ��
	 * 
	 *�ú������ں���Ӧ��
	 *
	 *@param[in] 	convId		VoIP���лỰID
	 *@param[in] 	iType		�������ͣ��ο�CALL_TYPE_E
	 *@param[in] 	localWnd	������Ƶ����
	 *@param[in] 	remoteWnd	Զ����Ƶ����
	 *@return 		�ɹ���0		ʧ�ܣ���0,�ο�������
	 *@attention	���iType��Call_Audio���������У�ʱ����ʹ��localWnd��remoteWnd����
	 *@par 			��
	**/
	UCSDK_API int UCSDK_CALL Accept(const char* convId, int iType, const UCVideoWindow* localWnd, const UCVideoWindow* remoteWnd);

	/**
	 *�ܾ�����
	 * 
	 *�ú������ھܾ�����
	 *
	 *@param[in] 	convId		VoIP���лỰID
	 *@param[in] 	iType		�������ͣ��ο�CALL_TYPE_E
	 *@return 		�ɹ���0		ʧ�ܣ���0,�ο�������
	 *@attention	�ܾ���Ƶ�����������Ƕ�ʹ��iType=Call_Audio���������У���Call_Video����Ƶ���У���ʱ����
	 *@par 			��
	**/
	UCSDK_API int UCSDK_CALL Reject(const char* convId, int iType);

	/**
	 *�Ͽ�ͨ��
	 * 
	 *�ú������ڶϿ�ͨ��
	 *
	 *@param[in] 	convId		VoIP���лỰID
	 *@param[in] 	iType		�������ͣ��ο�CALL_TYPE_E
	 *@return 		�ɹ���0		ʧ�ܣ���0,�ο�������
	 *@attention	���iType=Call_Video����Ƶ���У����ر���Ƶ��������Ƶͨ��ת����ͨ��
	 *@par 			��
	**/
	UCSDK_API int UCSDK_CALL Hangup(const char* convId, int iType);

	/**
	 *ͨ������
	 * 
	 *�ú�������ͨ������
	 *
	 *@param[in] 	convId		VoIP���лỰID
	 *@return 		�ɹ���0		ʧ�ܣ���0,�ο�������
	 *@attention	��
	 *@par 			��
	**/
	UCSDK_API int UCSDK_CALL Hold(const char* convId);

	/**
	 *�ָ�ͨ��
	 * 
	 *�ú������ڻָ�ͨ��
	 *
	 *@param[in] 	convId		VoIP���лỰID
	 *@return 		�ɹ���0		ʧ�ܣ���0,�ο�������
	 *@attention	��
	 *@par 			��
	**/
	UCSDK_API int UCSDK_CALL Resume(const char* convId);

	/**
	 *����ǰת
	 * 
	 *�ú������ں���ǰת
	 *
	 *@param[in] 	convId		VoIP���лỰID
	 *@param[in] 	account		ǰת�û�
	 *@return 		�ɹ���0		ʧ�ܣ���0,�ο�������
	 *@attention	��
	 *@par 			��
	**/
	UCSDK_API int UCSDK_CALL Forward(const char* convId, const char* account);

	/**
	 *��ʼ¼��
	 * 
	 *�ú������ڿ�ʼ¼��
	 *
	 *@param[in] 	convId		VoIP���лỰID
	 *@param[in] 	filePath	¼���ļ������·��
	 *@return 		�ɹ���0		ʧ�ܣ���0,�ο�������
	 *@attention	��
	 *@par 			��
	**/
	UCSDK_API int UCSDK_CALL StartRecord(const char* convId, const char* filePath);

	/**
	 *ֹͣ¼��
	 * 
	 *�ú�������ֹͣ¼��
	 *
	 *@param[in] 	convId		VoIP���лỰID
	 *@return 		�ɹ���0		ʧ�ܣ���0,�ο�������
	 *@attention	��
	 *@par 			��
	**/
	UCSDK_API int UCSDK_CALL StopRecord(const char* convId);

	/**
	 *����
	 * 
	 *�ú������ھ���
	 *
	 *@param[in] 	iType		�������ͣ��ο�MUTE_DEVICE_E
	 *@return 		�ɹ���0		ʧ�ܣ���0,�ο�������
	 *@attention	��
	 *@par 			��
	**/
	UCSDK_API int UCSDK_CALL MuteVoIP(int iType);

	/**
	 *ȡ������
	 * 
	 *�ú�������ȡ������
	 *
	 *@param[in] 	iType		ȡ���������ͣ��ο�MUTE_DEVICE_E
	 *@return 		�ɹ���0		ʧ�ܣ���0,�ο�������
	 *@attention	��
	 *@par 			��
	**/
	UCSDK_API int UCSDK_CALL UnMuteVoIP(int iType);


#ifdef __cplusplus
}
#endif 


#endif