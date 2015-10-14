#ifndef _UC_IM_ABS_PROXY_H_
#define _UC_IM_ABS_PROXY_H_

#include "DataType.h"


namespace eSDK {
	namespace UC {


/**
 *即时消息和文件传输管理类
 * 
 *该类用于处理即时消息发送和文件传输
 *
 *@attention	无
 *@par			无
**/
class UCSDK_API UCIMAbsProxy
{
protected:
	UCIMAbsProxy();
	virtual ~UCIMAbsProxy();

public:
	/**
	 *获取即时消息和文件传输管理类单实例
	 * 
	 *该函数用于获取即时消息和文件传输管理类单实例
	 *
	 *@return		成功：即时消息和文件传输管理类单实例指针， 失败：NULL
	 *@attention	无
	 *@par			无
	**/
	static UCIMAbsProxy* GetInstance();

	/**
	 *释放即时消息和文件传输管理类单实例
	 * 
	 *该函数用于释放即时消息和文件传输管理类单实例
	 *
	 *@attention	在调用UCSDKAbsProxy::ReleaseInstance()时候，会跟着一起释放
	 *@par			无
	**/
	static void ReleaseInstance();

public:
	/**
	 *发送即时消息
	 * 
	 *该函数用于发送即时消息
	 *
	 *@param[in]	strIMMsg
	 *@param[in]	accountList
	 *@param[in/out]conversationID
	 *@return		成功：0		失败：非0,参考返回码
	 *@attention	1.当conversationID为空时需要使用accountList，当conversationID不为空时不使用accountList
	 *				2.当strIMMsg为空，conversationID为空时会创建conversation，返回非空conversationID
	 *@par			无
	**/
	virtual int SendIMMessage(const std::string& strIMMsg, const AccountList& accountList, std::string &conversationID) = 0;

	/**
	 *根据conversationID关闭会话（conversation）
	 * 
	 *该函数用于根据conversationID关闭会话（conversation）
	 *
	 *@param[in] 	conversationID
	 *@return 		成功：0		失败：非0,参考返回码
	 *@attention	关闭conversation，包括会话里的IMSession和AVSession等
	 *@par 			无
	**/
	virtual int CloseConversation(const std::string &conversationID) = 0;

	/**
	 *接收文件
	 * 
	 *该函数用于接收文件
	 *
	 *@param[in] 	strFileID
	 *@param[in] 	strFilePath
	 *@return 		成功：0		失败：非0,参考返回码
	 *@attention	无
	 *@par 			无
	**/
	virtual int AcceptFile(const std::string& strFileID, const std::string& strFilePath) = 0;

	/**
	 *取消发送或接收文件
	 * 
	 *该函数用于取消发送或接收文件
	 *
	 *@param[in] 	strFileID
	 *@return 		成功：0		失败：非0,参考返回码
	 *@attention	无
	 *@par 			无
	**/
	virtual int CancelFile(const std::string& strFileID) = 0;

	/**
	 *拒绝接收文件
	 * 
	 *该函数用于拒绝接收文件
	 *
	 *@param[in] 	strFileID
	 *@return 		成功：0		失败：非0,参考返回码
	 *@attention	无
	 *@par 			无
	**/
	virtual int RejectFile(const std::string& strFileID) = 0;

	/**
	 *发送文件
	 * 
	 *该函数用于发送文件
	 *
	 *@param[in] 	strAccout
	 *@param[in] 	strFilePath
	 *@param[in] 	strTransType
	 *@param[in] 	bIsOfflineFile
	 *@return 		成功：0		失败：非0,参考返回码
	 *@attention	无
	 *@par 			无
	**/
	virtual std::string TransferFile(const std::string& strAccout,
		const std::string& strFilePath, const std::string& strTransType, bool bIsOfflineFile) = 0;
};

}
}

#endif