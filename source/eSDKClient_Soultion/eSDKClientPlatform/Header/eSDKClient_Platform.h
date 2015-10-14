#ifndef __ESDK_CLIENT_PLATFORM_H__
#define __ESDK_CLIENT_PLATFORM_H__

#include <string>

#ifdef ESDKCLIENTPLATFORM_EXPORTS
#define ESDKCLIENTPLATFORM_API __declspec(dllexport)
#else
#define ESDKCLIENTPLATFORM_API __declspec(dllimport)
#endif

#ifndef ESDKCLIENT_PLATFORM_DEPEND
#define ESDKCLIENT_PLATFORM_DEPEND
#endif

#ifdef WIN32
#define __ESDKCLIENTPLATFORM_CALL __stdcall
#else
#define __ESDKCLIENTPLATFORM_CALL
#endif

#ifndef CALLBACK
#define CALLBACK				__stdcall
#endif

typedef enum
{
	ESDKCLIENTPLATFORM_SUCCESS = 0,
	ESDKCLIENTPLATFORM_FAIL,
	ESDKCLIENTPLATFORM_INTERNAL_ERROR
} ESDKCLINETPLATFORM_ERR_CODE_E;


typedef enum
{
	ESDKCLIENTPLATFORM_UPGRADE_ASK = 0,			//����ѯ��
	ESDKCLIENTPLATFORM_UPGRADE_START,			//������ʼ
	ESDKCLIENTPLATFORM_UPGRADE_FINISHED			//�������
} ESDKMESSAGE_CODE_E;

/**
 *�汾������ʾ��Ϣ�ص�����
 * 
 *�ú����������ð汾������ʾ��Ϣ�ص�����
 *
 *@param[in] iMsgID				��ϢID,�ο�MESSAGE_CODE_E����
 *@param[in] pchDescription		��Ϣ���ݣ�����UPDATE_FINISHED��������ɣ�ʱ�����ݣ���readme.txt��ȡ��������Ϊ��
 *@return						UPDATE_ASK������ѯ�ʣ��������������������true������������false����UPDATE_ASK����true��
 *@attention					��UPDATE_ASK������ѯ�ʣ�ʱҪ�������������磺�ڸú�����ʹ��MessageBox��ʾ�û��Ƿ��������û�ѡ��YES����true��NO����false��
 *@par							��
**/
typedef bool (CALLBACK *eSDKClientMessageCallBack)(int iMsgID, char* pchDescription);

#ifdef __cplusplus
extern "C"
{
#endif
	/**
	 *�ͻ���ƽ̨��ʼ��
	 * 
	 *�ú������ڿͻ���ƽ̨��ʼ��
	 *
	 
	 *@return						    ESDKCLIENTPLATFORM_SUCCESS:       Success 
	                                    ESDKCLIENTPLATFORM_FAIL:          Failed
										ESDKCLIENTPLATFORM_INTERNAL_ERROR:�ڲ�����
	 *@attention					    ��
	 *@par							    ��
	**/
	ESDKCLIENTPLATFORM_API int __ESDKCLIENTPLATFORM_CALL eSDKClientPlatform_Init(void);

	/**
	 *�ͻ���ƽ̨ȥ��ʼ��
	 * 
	 *�ú������ڿͻ���ƽ̨ȥ��ʼ��
	 *
	 
	 *@return						    ESDKCLIENTPLATFORM_SUCCESS:       Success 
	                                    ESDKCLIENTPLATFORM_FAIL:          Failed
										ESDKCLIENTPLATFORM_INTERNAL_ERROR:�ڲ�����
	 *@attention					    ��
	 *@par							    ��
	**/
	ESDKCLIENTPLATFORM_API int __ESDKCLIENTPLATFORM_CALL eSDKClientPlatform_Uninit(void);

	/**
	 *ʹ��token���е�¼
	 * 
	 *�ú�������ʹ��token����ҵ���¼�ĳ���
	 *
	 *@param[in] token	                ��¼token
	 *@return						    ESDKCLIENTPLATFORM_SUCCESS:       Success 
										ESDKCLIENTPLATFORM_FAIL:          Failed
										ESDKCLIENTPLATFORM_INTERNAL_ERROR:�ڲ�����
	 *@attention					    ��
	 *@par							    ��
	**/
	ESDKCLIENTPLATFORM_API int __ESDKCLIENTPLATFORM_CALL eSDKClientPlatform_LoginByToken(const char* token);

	/**
	 *ʹ���û���������е�¼
	 * 
	 *�ú����ȿ�����ʹ���û��������¼ҵ��Ҳ������ʹ���û��������¼SSO������
	 *
	 *@param[in] name	                �û���
	 *@param[in] password	            ����
	 *@param[in] type	                ��¼���ͣ�ȡֵ���£�
	                                    0����¼SSO Server
										1����¼ҵ��

	*@return						    ESDKCLIENTPLATFORM_SUCCESS:       Success 
										ESDKCLIENTPLATFORM_FAIL:          Failed
										ESDKCLIENTPLATFORM_INTERNAL_ERROR:�ڲ�����
	 *@attention					    ��
	 *@par							    ��
	**/
	ESDKCLIENTPLATFORM_API int __ESDKCLIENTPLATFORM_CALL eSDKClientPlatform_LoginByPassword(const char* name, const char* password, const int type);
	
	/**
	 *�ǳ�
	 * 
	 *�ú������ڵǳ�
	 *
	 
	 *@return						    ESDKCLIENTPLATFORM_SUCCESS:       Success 
										ESDKCLIENTPLATFORM_FAIL:          Failed
										ESDKCLIENTPLATFORM_INTERNAL_ERROR:�ڲ�����
	 *@attention					    ��
	 *@par							    ��
	**/
	ESDKCLIENTPLATFORM_API int __ESDKCLIENTPLATFORM_CALL eSDKClientPlatform_Logout();

	/**
	 *����SSO Server Url
	 * 
	 *�ú�����������SSO Server Url
	 *
	 *@param[in] url	                SSO Server Url
	 *@return						    ESDKCLIENTPLATFORM_SUCCESS:       Success 
										ESDKCLIENTPLATFORM_FAIL:          Failed
										ESDKCLIENTPLATFORM_INTERNAL_ERROR:�ڲ�����
	 *@attention					    ��
	 *@par							    URL����"https://10.135.42.58:18643/"
	**/
	ESDKCLIENTPLATFORM_API int __ESDKCLIENTPLATFORM_CALL eSDKClientPlatform_SetSSOServerUrl(const char* url);

	/**
	 *��������IP��ַ
	 * 
	 *�ú���������������IP��ַ
	 *
	 *@param[in] ip	                    IP��ַ
	 *@return						    ��
	 *@attention					    Ŀǰֻ֧��IPV4����֧��IPV6
	 *@par							    IP����"10.142.164.170"
	**/
	ESDKCLIENTPLATFORM_API int __ESDKCLIENTPLATFORM_CALL eSDKClientPlatform_SetHostIP(const char* ip);

	/**
	 *��������������URL
	 * 
	 *�ú���������������������URL
	 *
	 *@param[in] pchServerUrl	����������URL
	 *@return			        ESDKCLIENTPLATFORM_SUCCESS:       Success 
								ESDKCLIENTPLATFORM_FAIL:          Failed
								ESDKCLIENTPLATFORM_INTERNAL_ERROR:�ڲ�����
	 *@attention		        ��
	 *@par				        URL����"http://10.135.43.43:8080/"
	**/
	ESDKCLIENTPLATFORM_API int __ESDKCLIENTPLATFORM_CALL eSDKClientPlatform_SetUpdateServer(const char* pchServerUrl);

	/**
	 *���ð汾������ʾ��Ϣ�ص�����
	 * 
	 *�ú����������ð汾������ʾ��Ϣ�ص�����
	 *
	 *@param[in] fpMsgCB			�汾������ʾ��Ϣ�ص�����ָ��
	 *@return						true:  Success ; false: Failed
	 *@attention					�ο�����ָ��eSDKClientMessageCallBack����
	 *@par							��
	**/
	ESDKCLIENTPLATFORM_API bool __ESDKCLIENTPLATFORM_CALL eSDKClientPlatform_SetMessageCallBack(eSDKClientMessageCallBack fpMsgCB);

#ifdef __cplusplus
}
#endif 

#endif

