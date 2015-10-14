#ifndef _UC_VOIP_HEADER_
#define _UC_VOIP_HEADER_

#include "DataDef.h"


#ifdef __cplusplus
extern "C"
{
#endif

	/**
	 *创建VoIP音视频呼叫
	 * 
	 *该函数用于创建VoIP音视频呼叫
	 *
	 *@param[in] 	member		呼叫成员
	 *@param[in] 	iType		呼叫类型：参考CALL_TYPE_E
	 *@param[in] 	localWnd	本地视频窗口
	 *@param[in] 	remoteWnd	远程视频窗口
	 *@param[out] 	convId		VoIP呼叫会话ID
	 *@return 		成功：0		失败：非0,参考返回码
	 *@attention	如果iType是Call_Audio（语音呼叫）时，不使用localWnd和remoteWnd参数
	 *@par 			无
	**/
	UCSDK_API int UCSDK_CALL MakeCall(const UCContact* member, int iType, const UCVideoWindow* localWnd,
										const UCVideoWindow* remoteWnd, char convId[CONVID_LENGTH]);

	/**
	 *呼叫应答
	 * 
	 *该函数用于呼叫应答
	 *
	 *@param[in] 	convId		VoIP呼叫会话ID
	 *@param[in] 	iType		呼叫类型：参考CALL_TYPE_E
	 *@param[in] 	localWnd	本地视频窗口
	 *@param[in] 	remoteWnd	远程视频窗口
	 *@return 		成功：0		失败：非0,参考返回码
	 *@attention	如果iType是Call_Audio（语音呼叫）时，不使用localWnd和remoteWnd参数
	 *@par 			无
	**/
	UCSDK_API int UCSDK_CALL Accept(const char* convId, int iType, const UCVideoWindow* localWnd, const UCVideoWindow* remoteWnd);

	/**
	 *拒绝接听
	 * 
	 *该函数用于拒绝接听
	 *
	 *@param[in] 	convId		VoIP呼叫会话ID
	 *@param[in] 	iType		呼叫类型：参考CALL_TYPE_E
	 *@return 		成功：0		失败：非0,参考返回码
	 *@attention	拒绝视频和语音呼叫是都使用iType=Call_Audio（语音呼叫），Call_Video（视频呼叫）暂时保留
	 *@par 			无
	**/
	UCSDK_API int UCSDK_CALL Reject(const char* convId, int iType);

	/**
	 *断开通话
	 * 
	 *该函数用于断开通话
	 *
	 *@param[in] 	convId		VoIP呼叫会话ID
	 *@param[in] 	iType		呼叫类型：参考CALL_TYPE_E
	 *@return 		成功：0		失败：非0,参考返回码
	 *@attention	如果iType=Call_Video（视频呼叫）仅关闭视频，用于视频通话转语音通话
	 *@par 			无
	**/
	UCSDK_API int UCSDK_CALL Hangup(const char* convId, int iType);

	/**
	 *通话保持
	 * 
	 *该函数用于通话保持
	 *
	 *@param[in] 	convId		VoIP呼叫会话ID
	 *@return 		成功：0		失败：非0,参考返回码
	 *@attention	无
	 *@par 			无
	**/
	UCSDK_API int UCSDK_CALL Hold(const char* convId);

	/**
	 *恢复通话
	 * 
	 *该函数用于恢复通话
	 *
	 *@param[in] 	convId		VoIP呼叫会话ID
	 *@return 		成功：0		失败：非0,参考返回码
	 *@attention	无
	 *@par 			无
	**/
	UCSDK_API int UCSDK_CALL Resume(const char* convId);

	/**
	 *呼叫前转
	 * 
	 *该函数用于呼叫前转
	 *
	 *@param[in] 	convId		VoIP呼叫会话ID
	 *@param[in] 	account		前转用户
	 *@return 		成功：0		失败：非0,参考返回码
	 *@attention	无
	 *@par 			无
	**/
	UCSDK_API int UCSDK_CALL Forward(const char* convId, const char* account);

	/**
	 *开始录音
	 * 
	 *该函数用于开始录音
	 *
	 *@param[in] 	convId		VoIP呼叫会话ID
	 *@param[in] 	filePath	录音文件保存的路径
	 *@return 		成功：0		失败：非0,参考返回码
	 *@attention	无
	 *@par 			无
	**/
	UCSDK_API int UCSDK_CALL StartRecord(const char* convId, const char* filePath);

	/**
	 *停止录音
	 * 
	 *该函数用于停止录音
	 *
	 *@param[in] 	convId		VoIP呼叫会话ID
	 *@return 		成功：0		失败：非0,参考返回码
	 *@attention	无
	 *@par 			无
	**/
	UCSDK_API int UCSDK_CALL StopRecord(const char* convId);

	/**
	 *静音
	 * 
	 *该函数用于静音
	 *
	 *@param[in] 	iType		静音类型，参考MUTE_DEVICE_E
	 *@return 		成功：0		失败：非0,参考返回码
	 *@attention	无
	 *@par 			无
	**/
	UCSDK_API int UCSDK_CALL MuteVoIP(int iType);

	/**
	 *取消静音
	 * 
	 *该函数用于取消静音
	 *
	 *@param[in] 	iType		取消静音类型，参考MUTE_DEVICE_E
	 *@return 		成功：0		失败：非0,参考返回码
	 *@attention	无
	 *@par 			无
	**/
	UCSDK_API int UCSDK_CALL UnMuteVoIP(int iType);


#ifdef __cplusplus
}
#endif 


#endif