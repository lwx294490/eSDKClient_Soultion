#ifndef _UC_SIGNIN_HEADER_
#define _UC_SIGNIN_HEADER_

#include "DataDef.h"


#ifdef __cplusplus
extern "C"
{
#endif

	/**
	 *��ʼ��
	 * 
	 *�ú������ڳ�ʼ��UCSDK����ҵ�񣬴�������ҵ��ʵ��
	 *
	 *@return 		�ɹ���0		ʧ�ܣ���0,�ο�������
	 *@attention	��
	 *@par 			��
	**/
	UCSDK_API int UCSDK_CALL Init();

	/**
	 *ȥ��ʼ��
	 * 
	 *�ú�������ȥ��ʼ��UCSDK����ҵ��
	 *
	 *@return 		�ɹ���0		ʧ�ܣ���0,�ο�������
	 *@attention	��
	 *@par 			��
	**/
	UCSDK_API int UCSDK_CALL UnInit();

	/**
	 *��½
	 * 
	 *�ú�������ʹ��token���е����½
	 *
	 *@param[in] 	token	�����½token
	 *@return 		�ɹ���0		ʧ�ܣ���0,�ο�������
	 *@attention	��
	 *@par 			��
	**/
	UCSDK_API int UCSDK_CALL LoginByToken(const char* token);

	/**
	 *��½
	 * 
	 *�ú�������ʹ���˺�������е�½
	 *
	 *@param[in] 	account		��½�˻�
	 *@param[in] 	passwd		��½����
	 *@return 		�ɹ���0		ʧ�ܣ���0,�ο�������
	 *@attention	��
	 *@par 			��
	**/
	UCSDK_API int UCSDK_CALL LoginByPasswd(const char* account, const char* passwd);

	/**
	 *�ǳ�
	 * 
	 *�ú������ڵǳ�
	 *
	 *@return 		�ɹ���0		ʧ�ܣ���0,�ο�������
	 *@attention	��
	 *@par 			��
	**/
	UCSDK_API int UCSDK_CALL Logout();

	/**
	 *���õ�½������Url
	 * 
	 *�ú����������õ�½������Url
	 *
	 *@param[in] 	srvUrl		������Url
	 *@return 		�ɹ���0		ʧ�ܣ���0,�ο�������
	 *@attention	��
	 *@par 			��
	**/
	UCSDK_API int UCSDK_CALL Config(const char* srvUrl);

	/**
	 *���õ�½����
	 * 
	 *�ú����������õ�½����
	 *
	 *@param[in] 	lang		����
	 *@return 		�ɹ���0		ʧ�ܣ���0,�ο�������
	 *@attention	��
	 *@par 			��
	**/
	UCSDK_API int UCSDK_CALL SetLang(const char* lang);


#ifdef __cplusplus
}
#endif 


#endif