#ifndef _UC_PUBLIC_HEADER_
#define _UC_PUBLIC_HEADER_

#include "DataDef.h"


#ifdef __cplusplus
extern "C"
{
#endif

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
	UCSDK_API int UCSDK_CALL PublishSelfInformation(const UCPublishInfoMap* publishInfoMap);

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
	UCSDK_API int UCSDK_CALL GetContactStatus(const char* _uri, int* _status);


#ifdef __cplusplus
}
#endif 


#endif