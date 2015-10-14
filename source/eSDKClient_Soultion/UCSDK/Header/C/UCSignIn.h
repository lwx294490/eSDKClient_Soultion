#ifndef _UC_SIGNIN_HEADER_
#define _UC_SIGNIN_HEADER_

#include "DataDef.h"


#ifdef __cplusplus
extern "C"
{
#endif

	/**
	 *初始化
	 * 
	 *该函数用于初始化UCSDK所有业务，创建所有业务实例
	 *
	 *@return 		成功：0		失败：非0,参考返回码
	 *@attention	无
	 *@par 			无
	**/
	UCSDK_API int UCSDK_CALL Init();

	/**
	 *去初始化
	 * 
	 *该函数用于去初始化UCSDK所有业务
	 *
	 *@return 		成功：0		失败：非0,参考返回码
	 *@attention	无
	 *@par 			无
	**/
	UCSDK_API int UCSDK_CALL UnInit();

	/**
	 *登陆
	 * 
	 *该函数用于使用token进行单点登陆
	 *
	 *@param[in] 	token	单点登陆token
	 *@return 		成功：0		失败：非0,参考返回码
	 *@attention	无
	 *@par 			无
	**/
	UCSDK_API int UCSDK_CALL LoginByToken(const char* token);

	/**
	 *登陆
	 * 
	 *该函数用于使用账号密码进行登陆
	 *
	 *@param[in] 	account		登陆账户
	 *@param[in] 	passwd		登陆密码
	 *@return 		成功：0		失败：非0,参考返回码
	 *@attention	无
	 *@par 			无
	**/
	UCSDK_API int UCSDK_CALL LoginByPasswd(const char* account, const char* passwd);

	/**
	 *登出
	 * 
	 *该函数用于登出
	 *
	 *@return 		成功：0		失败：非0,参考返回码
	 *@attention	无
	 *@par 			无
	**/
	UCSDK_API int UCSDK_CALL Logout();

	/**
	 *设置登陆服务器Url
	 * 
	 *该函数用于设置登陆服务器Url
	 *
	 *@param[in] 	srvUrl		服务器Url
	 *@return 		成功：0		失败：非0,参考返回码
	 *@attention	无
	 *@par 			无
	**/
	UCSDK_API int UCSDK_CALL Config(const char* srvUrl);

	/**
	 *设置登陆语言
	 * 
	 *该函数用于设置登陆语言
	 *
	 *@param[in] 	lang		语言
	 *@return 		成功：0		失败：非0,参考返回码
	 *@attention	无
	 *@par 			无
	**/
	UCSDK_API int UCSDK_CALL SetLang(const char* lang);


#ifdef __cplusplus
}
#endif 


#endif