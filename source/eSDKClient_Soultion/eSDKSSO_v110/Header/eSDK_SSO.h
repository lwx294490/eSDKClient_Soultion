#ifndef __ESDK_SSO_H__
#define __ESDK_SSO_H__

#ifdef ESDKSSO_EXPORTS
#define ESDK_SSO_API __declspec(dllexport)
#else
#define ESDK_SSO_API __declspec(dllimport)
#endif

#ifdef WIN32
#define __ESDK_SSO_CALL __stdcall
#else
#define __ESDK_SSO_CALL
#endif

typedef enum
{
	ESDK_SSO_SUCCESS = 0,
	ESDK_SSO_FAIL,
	ESDK_SSO_INTERNAL_ERROR
} ESDK_SSO_ERR_CODE_E;

typedef enum
{
	ESDK_SSO_LOGIN_SSO = 0,
	ESDK_SSO_LOGIN_SERVICE
} ESDK_SSO_LOGIN_TYPE_E;

typedef enum
{
	ESDK_SSO_SERVICE_PASSWORD_LOGIN = 0,
	ESDK_SSO_SERVICE_TOKEN_LOGIN
} ESDK_SSO_PDU_LOGIN_TYPE_E;

#ifdef __cplusplus
extern "C"
{
#endif
	/**
	 *SSO��ʼ��
	 * 
	 *�ú�������SSO��ʼ��
	 *
	 
	 *@return						    ESDK_SSO_SUCCESS:       Success 
	                                    ESDK_SSO_FAIL:          Failed
										ESDK_SSO_INTERNAL_ERROR:�ڲ�����
	 *@attention					    ��
	 *@par							    ��
	**/
	ESDK_SSO_API int __ESDK_SSO_CALL eSDKSSO_Init(void);
	
	/**
	 *SSOȥ��ʼ��
	 * 
	 *�ú�������SSOȥ��ʼ��
	 *
	 
	 *@return						    ESDK_SSO_SUCCESS:       Success 
	                                    ESDK_SSO_FAIL:          Failed
										ESDK_SSO_INTERNAL_ERROR:�ڲ�����
	 *@attention					    ��
	 *@par							    ��
	**/
	ESDK_SSO_API int __ESDK_SSO_CALL eSDKSSO_Uninit(void);
	
	/**
	 *ʹ��token���е�¼
	 * 
	 *�ú�������ʹ��token����ҵ���¼�ĳ���
	 *
	 *@param[in] token	                ��¼token
	 *@return						    ESDK_SSO_SUCCESS:       Success 
	                                    ESDK_SSO_FAIL:          Failed
										ESDK_SSO_INTERNAL_ERROR:�ڲ�����
	 *@attention					    ��
	 *@par							    ��
	**/
	ESDK_SSO_API int __ESDK_SSO_CALL eSDKSSO_LoginByToken(const char* token);
	
	/**
	 *ʹ���û���������е�¼
	 * 
	 *�ú����ȿ�����ʹ���û��������¼ҵ��Ҳ������ʹ���û��������¼SSO������
	 *
	 *@param[in] name	                �û���
	 *@param[in] password	            ����
	 *@param[in] type	                ��¼���ͣ�ȡֵ���£�
	                                    ESDK_SSO_LOGIN_SSO����¼SSO Server
										ESDK_SSO_LOGIN_SERVICE����¼ҵ��

	 *@return						    ESDK_SSO_SUCCESS:       Success 
	                                    ESDK_SSO_FAIL:          Failed
										ESDK_SSO_INTERNAL_ERROR:�ڲ�����
	 *@attention					    ��
	 *@par							    ��
	**/
	ESDK_SSO_API int __ESDK_SSO_CALL eSDKSSO_LoginByNamePassword(const char* name, const char* password, int type);

	/**
	 *�ǳ�
	 * 
	 *�ú������ڵǳ�
	 *
	 
	 *@return						    ESDK_SSO_SUCCESS:       Success 
	                                    ESDK_SSO_FAIL:          Failed
										ESDK_SSO_INTERNAL_ERROR:�ڲ�����
	 *@attention					    ��
	 *@par							    ��
	**/
	ESDK_SSO_API int __ESDK_SSO_CALL eSDKSSO_Logout(void);

	/**
	 *����SSO Server Url
	 * 
	 *�ú�����������SSO Server Url
	 *
	 *@param[in] url	                SSO Server Url
	 *@return						    ESDK_SSO_SUCCESS:       Success 
	                                    ESDK_SSO_FAIL:          Failed
										ESDK_SSO_INTERNAL_ERROR:�ڲ�����
	 *@attention					    ��
	 *@par							    URL����"https://10.135.42.58:18643/"
	**/
	ESDK_SSO_API int __ESDK_SSO_CALL eSDKSSO_SetSSOServerUrl(const char* url);

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
	ESDK_SSO_API int __ESDK_SSO_CALL eSDKSSO_SetHostIP(const char* ip);

	/**
	 *��ȡҵ����
	 * 
	 *�ú������ڸ���ҵ�����ֻ�ȡ���ص�ҵ����
	 *
	 *@param[in] serviceName	        ҵ������
	 *@return						    ҵ����
	 *@attention					    ��
	 *@par							    ��
	**/
	ESDK_SSO_API unsigned long __ESDK_SSO_CALL eSDKSSO_GetServiceHandleByName(const char* serviceName);

#ifdef __cplusplus
}
#endif 

#endif
