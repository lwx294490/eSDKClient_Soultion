#ifndef _UC_VOIP_ABS_PROXY_H_
#define _UC_VOIP_ABS_PROXY_H_

#include "DataType.h"


namespace eSDK {
	namespace UC {


/**
 *VoIP管理类
 * 
 *该类用于VoIP通信操作，包括呼叫、接听、拒绝、挂断、恢复、保持等等
 *
 *@attention	无
 *@par 			无
**/
class UCSDK_API UCVoIPAbsProxy
{
protected:
	UCVoIPAbsProxy();
	virtual ~UCVoIPAbsProxy();

public:
	/**
	 *获取VoIP管理类单实例
	 * 
	 *该函数用于获取VoIP管理类单实例
	 *
	 *@return 		成功：VoIP管理类单实例指针， 失败：NULL
	 *@attention	无
	 *@par 			无
	**/
	static UCVoIPAbsProxy* GetInstance();

	/**
	 *释放VoIP管理类单实例
	 * 
	 *该函数用于释放VoIP管理类单实例
	 *
	 *@attention	在调用UCSDKAbsProxy::ReleaseInstance()时候，会跟着一起释放
	 *@par 			无
	**/
	static void ReleaseInstance();

public:
	/**
	 *创建VoIP音视频呼叫
	 * 
	 *该函数用于创建VoIP音视频呼叫
	 *
	 *@param[out] 	strConvID	VoIP呼叫会话ID
	 *@param[in] 	member		呼叫成员
	 *@param[in] 	iType		呼叫类型：参考CALL_TYPE_E
	 *@param[in] 	localWnd	本地视频窗口
	 *@param[in] 	remoteWnd	远程视频窗口
	 *@return 		成功：0		失败：非0,参考返回码
	 *@attention	如果iType是Call_Audio（语音呼叫）时，不使用localWnd和remoteWnd参数
	 *@par 			无
	**/
	virtual int MakeCall(std::string& strConvID, const UCSDKContact& member, int iType,
		const STVideoWindow& localWnd, const STVideoWindow& remoteWnd) = 0;

	/**
	 *呼叫应答
	 * 
	 *该函数用于呼叫应答
	 *
	 *@param[in] 	strConvID	VoIP呼叫会话ID
	 *@param[in] 	iType		呼叫类型：参考CALL_TYPE_E
	 *@param[in] 	localWnd	本地视频窗口
	 *@param[in] 	remoteWnd	远程视频窗口
	 *@return 		成功：0		失败：非0,参考返回码
	 *@attention	如果iType是Call_Audio（语音呼叫）时，不使用localWnd和remoteWnd参数
	 *@par 			无
	**/
	virtual int Accept(const std::string& strConvID, int iType, const STVideoWindow& localWnd, const STVideoWindow& remoteWnd) = 0;

	/**
	 *拒绝接听
	 * 
	 *该函数用于拒绝接听
	 *
	 *@param[in] 	strConvID	VoIP呼叫会话ID
	 *@param[in] 	iType		呼叫类型：参考CALL_TYPE_E
	 *@return 		成功：0		失败：非0,参考返回码
	 *@attention	拒绝视频和语音呼叫是都使用iType=Call_Audio（语音呼叫），Call_Video（视频呼叫）暂时保留
	 *@par 			无
	**/
	virtual int Reject(const std::string& strConvID, int iType) = 0;

	/**
	 *断开通话
	 * 
	 *该函数用于断开通话
	 *
	 *@param[in] 	strConvID	VoIP呼叫会话ID
	 *@param[in] 	iType		呼叫类型：参考CALL_TYPE_E
	 *@return 		成功：0		失败：非0,参考返回码
	 *@attention	如果iType=Call_Video（视频呼叫）仅关闭视频，用于视频通话转语音通话
	 *@par 			无
	**/
	virtual int Hangup(const std::string& strConvID, int iType) = 0;

	/**
	 *通话保持
	 * 
	 *该函数用于通话保持
	 *
	 *@param[in] 	strConvID	VoIP呼叫会话ID
	 *@return 		成功：0		失败：非0,参考返回码
	 *@attention	无
	 *@par 			无
	**/
	virtual int Hold(const std::string& strConvID) = 0;

	/**
	 *恢复通话
	 * 
	 *该函数用于恢复通话
	 *
	 *@param[in] 	strConvID	VoIP呼叫会话ID
	 *@return 		成功：0		失败：非0,参考返回码
	 *@attention	无
	 *@par 			无
	**/
	virtual int Resume(const std::string& strConvID) = 0;

	/**
	 *呼叫前转
	 * 
	 *该函数用于呼叫前转
	 *
	 *@param[in] 	strConvID	VoIP呼叫会话ID
	 *@param[in] 	strAccount	前转用户
	 *@return 		成功：0		失败：非0,参考返回码
	 *@attention	无
	 *@par 			无
	**/
	virtual int Forward(const std::string& strConvID, const std::string& strAccount) = 0;

	/**
	 *开始录音
	 * 
	 *该函数用于开始录音
	 *
	 *@param[in] 	strConvID	VoIP呼叫会话ID
	 *@param[in] 	strFilePath	录音文件保存的路径
	 *@return 		成功：0		失败：非0,参考返回码
	 *@attention	无
	 *@par 			无
	**/
	virtual int StartRecord(const std::string& strConvID, const std::string& strFilePath) = 0;

	/**
	 *停止录音
	 * 
	 *该函数用于停止录音
	 *
	 *@param[in] 	strConvID	VoIP呼叫会话ID
	 *@return 		成功：0		失败：非0,参考返回码
	 *@attention	无
	 *@par 			无
	**/
	virtual int StopRecord(const std::string& strConvID) = 0;

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
	virtual int Mute(const int iType) = 0;

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
	virtual int UnMute(const int iType) = 0;
};

}
}

#endif