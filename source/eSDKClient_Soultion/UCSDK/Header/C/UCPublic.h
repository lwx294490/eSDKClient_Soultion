#ifndef _UC_PUBLIC_HEADER_
#define _UC_PUBLIC_HEADER_

#include "DataDef.h"


#ifdef __cplusplus
extern "C"
{
#endif

	/**
	 *����������Ϣ
	 * 
	 *�ú������ڷ���������Ϣ
	 *
	 *@param[in] 	publishInfoMap
	 *@return 		�ɹ���0		ʧ�ܣ���0,�ο�������
	 *@attention	��
	 *@par 			��
	**/
	UCSDK_API int UCSDK_CALL PublishSelfInformation(const UCPublishInfoMap* publishInfoMap);

	/**
	 *ͨ����ϵ��uri��ȡ��ϵ״̬
	 * 
	 *�ú�������ͨ����ϵ��uri��ȡ��ϵ״̬
	 *
	 *@param[in] 	_uri		��ϵ��uri
	 *@param[out] 	_status		��ϵ��״̬
	 *@return 		�ɹ���0		ʧ�ܣ���0,�ο�������
	 *@attention	��
	 *@par 			��
	**/
	UCSDK_API int UCSDK_CALL GetContactStatus(const char* _uri, int* _status);


#ifdef __cplusplus
}
#endif 


#endif