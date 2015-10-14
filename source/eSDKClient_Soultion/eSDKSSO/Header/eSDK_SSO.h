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
	 *SSO初始化
	 * 
	 *该函数用于SSO初始化
	 *
	 
	 *@return						    ESDK_SSO_SUCCESS:       Success 
	                                    ESDK_SSO_FAIL:          Failed
										ESDK_SSO_INTERNAL_ERROR:内部错误
	 *@attention					    无
	 *@par							    无
	**/
	ESDK_SSO_API int __ESDK_SSO_CALL eSDKSSO_Init(void);
	
	/**
	 *SSO去初始化
	 * 
	 *该函数用于SSO去初始化
	 *
	 
	 *@return						    ESDK_SSO_SUCCESS:       Success 
	                                    ESDK_SSO_FAIL:          Failed
										ESDK_SSO_INTERNAL_ERROR:内部错误
	 *@attention					    无
	 *@par							    无
	**/
	ESDK_SSO_API int __ESDK_SSO_CALL eSDKSSO_Uninit(void);
	
	/**
	 *使用token进行登录
	 * 
	 *该函数用于使用token进行业务登录的场景
	 *
	 *@param[in] token	                登录token
	 *@return						    ESDK_SSO_SUCCESS:       Success 
	                                    ESDK_SSO_FAIL:          Failed
										ESDK_SSO_INTERNAL_ERROR:内部错误
	 *@attention					    无
	 *@par							    无
	**/
	ESDK_SSO_API int __ESDK_SSO_CALL eSDKSSO_LoginByToken(const char* token);
	
	/**
	 *使用用户名密码进行登录
	 * 
	 *该函数既可用于使用用户名密码登录业务，也可用于使用用户名密码登录SSO服务器
	 *
	 *@param[in] name	                用户名
	 *@param[in] password	            密码
	 *@param[in] type	                登录类型，取值如下：
	                                    ESDK_SSO_LOGIN_SSO：登录SSO Server
										ESDK_SSO_LOGIN_SERVICE：登录业务

	 *@return						    ESDK_SSO_SUCCESS:       Success 
	                                    ESDK_SSO_FAIL:          Failed
										ESDK_SSO_INTERNAL_ERROR:内部错误
	 *@attention					    无
	 *@par							    无
	**/
	ESDK_SSO_API int __ESDK_SSO_CALL eSDKSSO_LoginByNamePassword(const char* name, const char* password, int type);

	/**
	 *登出
	 * 
	 *该函数用于登出
	 *
	 
	 *@return						    ESDK_SSO_SUCCESS:       Success 
	                                    ESDK_SSO_FAIL:          Failed
										ESDK_SSO_INTERNAL_ERROR:内部错误
	 *@attention					    无
	 *@par							    无
	**/
	ESDK_SSO_API int __ESDK_SSO_CALL eSDKSSO_Logout(void);

	/**
	 *设置SSO Server Url
	 * 
	 *该函数用于设置SSO Server Url
	 *
	 *@param[in] url	                SSO Server Url
	 *@return						    ESDK_SSO_SUCCESS:       Success 
	                                    ESDK_SSO_FAIL:          Failed
										ESDK_SSO_INTERNAL_ERROR:内部错误
	 *@attention					    无
	 *@par							    URL例："https://10.135.42.58:18643/"
	**/
	ESDK_SSO_API int __ESDK_SSO_CALL eSDKSSO_SetSSOServerUrl(const char* url);

	/**
	 *设置主机IP地址
	 * 
	 *该函数用于设置主机IP地址
	 *
	 *@param[in] ip	                    IP地址
	 *@return						    无
	 *@attention					    目前只支持IPV4，不支持IPV6
	 *@par							    IP例："10.142.164.170"
	**/
	ESDK_SSO_API int __ESDK_SSO_CALL eSDKSSO_SetHostIP(const char* ip);

	/**
	 *获取业务句柄
	 * 
	 *该函数用于根据业务名字获取加载的业务句柄
	 *
	 *@param[in] serviceName	        业务名字
	 *@return						    业务句柄
	 *@attention					    无
	 *@par							    无
	**/
	ESDK_SSO_API unsigned long __ESDK_SSO_CALL eSDKSSO_GetServiceHandleByName(const char* serviceName);

#ifdef __cplusplus
}
#endif 

#endif
