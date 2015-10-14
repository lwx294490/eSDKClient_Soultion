#ifndef _UC_IM_HEADER_
#define _UC_IM_HEADER_

#include "DataDef.h"


#ifdef __cplusplus
extern "C"
{
#endif

	/**
	 *���ͼ�ʱ��Ϣ
	 * 
	 *�ú������ڷ��ͼ�ʱ��Ϣ
	 *
	 *@param[in]	pMsg
	 *@param[in]	accountList
	 *@param[in/out]convId
	 *@return		�ɹ���0		ʧ�ܣ���0,�ο�������
	 *@attention	1.��convIdΪ��ʱ��Ҫʹ��accountList����convId��Ϊ��ʱ��ʹ��accountList
	 *				2.��pMsgΪ�գ�convIdΪ��ʱ�ᴴ��conversation�����طǿ�convId
	 *				3.accountList�ڴ��С��accountList->iFrom��accountList->iTo����һ��
	 *@par			��
	**/
	UCSDK_API int UCSDK_CALL SendIMMessage(const char* pMsg, const UCAccountList* accountList, char convId[CONVID_LENGTH]);

	/**
	 *����conversationID�رջỰ��conversation��
	 * 
	 *�ú������ڸ���conversationID�رջỰ��conversation��
	 *
	 *@param[in] 	convId
	 *@return 		�ɹ���0		ʧ�ܣ���0,�ο�������
	 *@attention	�ر�conversation�������Ự���IMSession��AVSession��
	 *@par 			��
	**/
	UCSDK_API int UCSDK_CALL CloseConversation(const char* convId);

	/**
	 *�����ļ�
	 * 
	 *�ú������ڽ����ļ�
	 *
	 *@param[in] 	fileId
	 *@param[in] 	filePath
	 *@return 		�ɹ���0		ʧ�ܣ���0,�ο�������
	 *@attention	��
	 *@par 			��
	**/
	UCSDK_API int UCSDK_CALL AcceptFile(const char* fileId, const char* filePath);

	/**
	 *ȡ�����ͻ�����ļ�
	 * 
	 *�ú�������ȡ�����ͻ�����ļ�
	 *
	 *@param[in] 	fileId
	 *@return 		�ɹ���0		ʧ�ܣ���0,�ο�������
	 *@attention	��
	 *@par 			��
	**/
	UCSDK_API int UCSDK_CALL CancelFile(const char* fileId);

	/**
	 *�ܾ������ļ�
	 * 
	 *�ú������ھܾ������ļ�
	 *
	 *@param[in] 	fileId
	 *@return 		�ɹ���0		ʧ�ܣ���0,�ο�������
	 *@attention	��
	 *@par 			��
	**/
	UCSDK_API int UCSDK_CALL RejectFile(const char* fileId);

	/**
	 *�����ļ�
	 * 
	 *�ú������ڷ����ļ�
	 *
	 *@param[in] 	pAcc
	 *@param[in] 	filePath
	 *@param[in] 	transType
	 *@param[in] 	bIsOfflineFile	//1:�� 0:����
	 *@param[out] 	fileId
	 *@return 		�ɹ���0		ʧ�ܣ���0,�ο�������
	 *@attention	��
	 *@par 			��
	**/
	UCSDK_API int UCSDK_CALL TransferFile(const char* pAcc,const char* filePath,
							const char* transType, int bIsOfflineFile, char fileId[FILEID_LENGTH]);


#ifdef __cplusplus
}
#endif 


#endif