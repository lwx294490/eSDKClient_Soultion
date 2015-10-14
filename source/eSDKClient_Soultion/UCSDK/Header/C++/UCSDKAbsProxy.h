#ifndef _UC_SDK_ABS_PROXY_H_
#define _UC_SDK_ABS_PROXY_H_

#include "DataType.h"
#include "UCSignalRecvAbsProxy.h"

#ifdef ESDKCLIENT_PLATFORM_DEPEND
#include "ProductSDK.h"
#endif


namespace eSDK {
	namespace UC {


/**
 *鉴权管理类，在平台中使用时是UCSDK业务总管理类
 * 
 *该类用于登陆登出鉴权，是UCSDK的总入口
 *
 *@attention	无
 *@par 			无
**/
#ifdef ESDKCLIENT_PLATFORM_DEPEND
class UCSDK_API UCSDKAbsProxy : public ProductSDK
#else
class UCSDK_API UCSDKAbsProxy
#endif
{
protected:
	UCSDKAbsProxy();
	virtual ~UCSDKAbsProxy();

public:
	/**
	 *获取鉴权管理类单实例
	 * 
	 *该函数用于获取鉴权管理类单实例
	 *
	 *@return 		成功鉴权管理类单实例指针， 失败：NULL
	 *@attention	无
	 *@par 			无
	**/
	static UCSDKAbsProxy* GetInstance();

	/**
	 *释放鉴权管理类单实例
	 * 
	 *该函数用于释放鉴权管理类单实例
	 *
	 *@attention	同时释放UCSDK所有业务类实例
	 *@par 			无
	**/
	static void ReleaseInstance();

public:
	/**
	 *初始化
	 * 
	 *该函数用于初始化UCSDK所有业务，创建所有业务实例
	 *
	 *@return 		成功：0		失败：非0,参考返回码
	 *@attention	无
	 *@par 			无
	**/
	virtual int Init() = 0;

	/**
	 *去初始化
	 * 
	 *该函数用于去初始化UCSDK所有业务
	 *
	 *@return 		成功：0		失败：非0,参考返回码
	 *@attention	无
	 *@par 			无
	**/
	virtual int UnInit() = 0;

	/**
	 *登陆
	 * 
	 *该函数用于使用token进行单点登陆
	 *
	 *@param[in] 	strToken	单点登陆token
	 *@return 		成功：0		失败：非0,参考返回码
	 *@attention	无
	 *@par 			无
	**/
	virtual int Login(const std::string& strToken) = 0;

	/**
	 *登陆
	 * 
	 *该函数用于使用账号密码进行登陆
	 *
	 *@param[in] 	strName		登陆账户
	 *@param[in] 	strPassword	登陆密码
	 *@return 		成功：0		失败：非0,参考返回码
	 *@attention	无
	 *@par 			无
	**/
	virtual int Login(const std::string& strName, const std::string& strPassword) = 0;

	/**
	 *登出
	 * 
	 *该函数用于登出
	 *
	 *@return 		成功：0		失败：非0,参考返回码
	 *@attention	无
	 *@par 			无
	**/
	virtual int Logout() = 0;

	/**
	 *设置登陆服务器Url
	 * 
	 *该函数用于设置登陆服务器Url
	 *
	 *@param[in] 	strSrvUrl	服务器Url
	 *@return 		成功：0		失败：非0,参考返回码
	 *@attention	无
	 *@par 			无
	**/
	virtual int Config(const std::string& strSrvUrl) = 0;

	/**
	 *设置登陆语言
	 * 
	 *该函数用于设置登陆语言
	 *
	 *@param[in] 	strLang		语言
	 *@return 		成功：0		失败：非0,参考返回码
	 *@attention	无
	 *@par 			无
	**/
	virtual int SetLang(const std::string& strLang) = 0;

	/**
	 *设置信号回调实例指针
	 * 
	 *该函数用于设置信号回调实例指针
	 *
	 *@param[in] 	pUCSignalRecvAbsProxy	信号实例指针
	 *@return 		成功：0		失败：非0,参考返回码
	 *@attention	UCSignalRecvAbsProxy由ISV实现，建立信号实例后，传入实例指针
	 *@par 			示例代码
	**/
	virtual int SetUCSignalRecvAbsProxy(UCSignalRecvAbsProxy* pUCSignalRecvAbsProxy) = 0;
};

}
}

#endif