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
	ESDKCLIENTPLATFORM_UPGRADE_ASK = 0,			//升级询问
	ESDKCLIENTPLATFORM_UPGRADE_START,			//升级开始
	ESDKCLIENTPLATFORM_UPGRADE_FINISHED			//升级完成
} ESDKMESSAGE_CODE_E;

/**
 *版本升级提示消息回调函数
 * 
 *该函数用于设置版本升级提示消息回调函数
 *
 *@param[in] iMsgID				消息ID,参考MESSAGE_CODE_E定义
 *@param[in] pchDescription		消息内容，仅在UPDATE_FINISHED（升级完成）时有内容（从readme.txt读取），其他为空
 *@return						UPDATE_ASK（升级询问）会进行阻塞，升级返回true，不升级返回false。非UPDATE_ASK返回true。
 *@attention					在UPDATE_ASK（升级询问）时要进行阻塞，比如：在该函数内使用MessageBox提示用户是否升级，用户选择YES返回true，NO返回false。
 *@par							无
**/
typedef bool (CALLBACK *eSDKClientMessageCallBack)(int iMsgID, char* pchDescription);

#ifdef __cplusplus
extern "C"
{
#endif
	/**
	 *客户端平台初始化
	 * 
	 *该函数用于客户端平台初始化
	 *
	 
	 *@return						    ESDKCLIENTPLATFORM_SUCCESS:       Success 
	                                    ESDKCLIENTPLATFORM_FAIL:          Failed
										ESDKCLIENTPLATFORM_INTERNAL_ERROR:内部错误
	 *@attention					    无
	 *@par							    无
	**/
	ESDKCLIENTPLATFORM_API int __ESDKCLIENTPLATFORM_CALL eSDKClientPlatform_Init(void);

	/**
	 *客户端平台去初始化
	 * 
	 *该函数用于客户端平台去初始化
	 *
	 
	 *@return						    ESDKCLIENTPLATFORM_SUCCESS:       Success 
	                                    ESDKCLIENTPLATFORM_FAIL:          Failed
										ESDKCLIENTPLATFORM_INTERNAL_ERROR:内部错误
	 *@attention					    无
	 *@par							    无
	**/
	ESDKCLIENTPLATFORM_API int __ESDKCLIENTPLATFORM_CALL eSDKClientPlatform_Uninit(void);

	/**
	 *使用token进行登录
	 * 
	 *该函数用于使用token进行业务登录的场景
	 *
	 *@param[in] token	                登录token
	 *@return						    ESDKCLIENTPLATFORM_SUCCESS:       Success 
										ESDKCLIENTPLATFORM_FAIL:          Failed
										ESDKCLIENTPLATFORM_INTERNAL_ERROR:内部错误
	 *@attention					    无
	 *@par							    无
	**/
	ESDKCLIENTPLATFORM_API int __ESDKCLIENTPLATFORM_CALL eSDKClientPlatform_LoginByToken(const char* token);

	/**
	 *使用用户名密码进行登录
	 * 
	 *该函数既可用于使用用户名密码登录业务，也可用于使用用户名密码登录SSO服务器
	 *
	 *@param[in] name	                用户名
	 *@param[in] password	            密码
	 *@param[in] type	                登录类型，取值如下：
	                                    0：登录SSO Server
										1：登录业务

	*@return						    ESDKCLIENTPLATFORM_SUCCESS:       Success 
										ESDKCLIENTPLATFORM_FAIL:          Failed
										ESDKCLIENTPLATFORM_INTERNAL_ERROR:内部错误
	 *@attention					    无
	 *@par							    无
	**/
	ESDKCLIENTPLATFORM_API int __ESDKCLIENTPLATFORM_CALL eSDKClientPlatform_LoginByPassword(const char* name, const char* password, const int type);
	
	/**
	 *登出
	 * 
	 *该函数用于登出
	 *
	 
	 *@return						    ESDKCLIENTPLATFORM_SUCCESS:       Success 
										ESDKCLIENTPLATFORM_FAIL:          Failed
										ESDKCLIENTPLATFORM_INTERNAL_ERROR:内部错误
	 *@attention					    无
	 *@par							    无
	**/
	ESDKCLIENTPLATFORM_API int __ESDKCLIENTPLATFORM_CALL eSDKClientPlatform_Logout();

	/**
	 *设置SSO Server Url
	 * 
	 *该函数用于设置SSO Server Url
	 *
	 *@param[in] url	                SSO Server Url
	 *@return						    ESDKCLIENTPLATFORM_SUCCESS:       Success 
										ESDKCLIENTPLATFORM_FAIL:          Failed
										ESDKCLIENTPLATFORM_INTERNAL_ERROR:内部错误
	 *@attention					    无
	 *@par							    URL例："https://10.135.42.58:18643/"
	**/
	ESDKCLIENTPLATFORM_API int __ESDKCLIENTPLATFORM_CALL eSDKClientPlatform_SetSSOServerUrl(const char* url);

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
	ESDKCLIENTPLATFORM_API int __ESDKCLIENTPLATFORM_CALL eSDKClientPlatform_SetHostIP(const char* ip);

	/**
	 *设置升级服务器URL
	 * 
	 *该函数用于设置升级服务器URL
	 *
	 *@param[in] pchServerUrl	升级服务器URL
	 *@return			        ESDKCLIENTPLATFORM_SUCCESS:       Success 
								ESDKCLIENTPLATFORM_FAIL:          Failed
								ESDKCLIENTPLATFORM_INTERNAL_ERROR:内部错误
	 *@attention		        无
	 *@par				        URL例："http://10.135.43.43:8080/"
	**/
	ESDKCLIENTPLATFORM_API int __ESDKCLIENTPLATFORM_CALL eSDKClientPlatform_SetUpdateServer(const char* pchServerUrl);

	/**
	 *设置版本升级提示消息回调函数
	 * 
	 *该函数用于设置版本升级提示消息回调函数
	 *
	 *@param[in] fpMsgCB			版本升级提示消息回调函数指针
	 *@return						true:  Success ; false: Failed
	 *@attention					参考函数指针eSDKClientMessageCallBack定义
	 *@par							无
	**/
	ESDKCLIENTPLATFORM_API bool __ESDKCLIENTPLATFORM_CALL eSDKClientPlatform_SetMessageCallBack(eSDKClientMessageCallBack fpMsgCB);

#ifdef __cplusplus
}
#endif 

#endif

