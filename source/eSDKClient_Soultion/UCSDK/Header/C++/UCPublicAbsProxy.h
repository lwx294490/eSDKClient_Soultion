#ifndef _UC_PUBLIC_ABS_PROXY_H_
#define _UC_PUBLIC_ABS_PROXY_H_

#include "DataType.h"


namespace eSDK {
	namespace UC {


/**
 *公共接口管理类
 * 
 *该类用于公共接口管理
 *
 *@attention	无
 *@par 			无
**/
class UCSDK_API UCPublicAbsProxy
{
protected:
	UCPublicAbsProxy();
	virtual ~UCPublicAbsProxy();

public:
	/**
	 *获取公共接口管理类单实例
	 * 
	 *该函数用于获取公共接口管理类单实例
	 *
	 *@return 		成功：公共接口管理类单实例指针， 失败：NULL
	 *@attention	无
	 *@par 			无
	**/
	static UCPublicAbsProxy* GetInstance();

	/**
	 *释放公共接口管理类单实例
	 * 
	 *该函数用于释放公共接口管理类单实例
	 *
	 *@attention	在调用UCSDKAbsProxy::ReleaseInstance()时候，会跟着一起释放
	 *@par 			示例代码
	**/
	static void ReleaseInstance();

public:
	/**
	 *发布个人信息
	 * 
	 *该函数用于发布个人信息
	 *
	 *@param[in] 	publishInfoMap
	 *@return 		成功：0		失败：非0,参考返回码
	 *@attention	无
	 *@par 			无
	**/
	virtual int PublishSelfInformation(const PublishInfoMap& publishInfoMap) = 0;

	/**
	 *通过联系人uri获取联系状态
	 * 
	 *该函数用于通过联系人uri获取联系状态
	 *
	 *@param[in] 	_uri		联系人uri
	 *@param[out] 	_status		联系人状态
	 *@return 		成功：0		失败：非0,参考返回码
	 *@attention	无
	 *@par 			无
	**/
	virtual int GetContactStatus(const std::string& _uri, int& _status) = 0;
};

}
}

#endif