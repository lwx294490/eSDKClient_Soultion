#ifndef _UC_IM_HEADER_
#define _UC_IM_HEADER_

#include "DataDef.h"


#ifdef __cplusplus
extern "C"
{
#endif

	/**
	 *发送即时消息
	 * 
	 *该函数用于发送即时消息
	 *
	 *@param[in]	pMsg
	 *@param[in]	accountList
	 *@param[in/out]convId
	 *@return		成功：0		失败：非0,参考返回码
	 *@attention	1.当convId为空时需要使用accountList，当convId不为空时不使用accountList
	 *				2.当pMsg为空，convId为空时会创建conversation，返回非空convId
	 *				3.accountList内存大小与accountList->iFrom和accountList->iTo保持一致
	 *@par			无
	**/
	UCSDK_API int UCSDK_CALL SendIMMessage(const char* pMsg, const UCAccountList* accountList, char convId[CONVID_LENGTH]);

	/**
	 *根据conversationID关闭会话（conversation）
	 * 
	 *该函数用于根据conversationID关闭会话（conversation）
	 *
	 *@param[in] 	convId
	 *@return 		成功：0		失败：非0,参考返回码
	 *@attention	关闭conversation，包括会话里的IMSession和AVSession等
	 *@par 			无
	**/
	UCSDK_API int UCSDK_CALL CloseConversation(const char* convId);

	/**
	 *接收文件
	 * 
	 *该函数用于接收文件
	 *
	 *@param[in] 	fileId
	 *@param[in] 	filePath
	 *@return 		成功：0		失败：非0,参考返回码
	 *@attention	无
	 *@par 			无
	**/
	UCSDK_API int UCSDK_CALL AcceptFile(const char* fileId, const char* filePath);

	/**
	 *取消发送或接收文件
	 * 
	 *该函数用于取消发送或接收文件
	 *
	 *@param[in] 	fileId
	 *@return 		成功：0		失败：非0,参考返回码
	 *@attention	无
	 *@par 			无
	**/
	UCSDK_API int UCSDK_CALL CancelFile(const char* fileId);

	/**
	 *拒绝接收文件
	 * 
	 *该函数用于拒绝接收文件
	 *
	 *@param[in] 	fileId
	 *@return 		成功：0		失败：非0,参考返回码
	 *@attention	无
	 *@par 			无
	**/
	UCSDK_API int UCSDK_CALL RejectFile(const char* fileId);

	/**
	 *发送文件
	 * 
	 *该函数用于发送文件
	 *
	 *@param[in] 	pAcc
	 *@param[in] 	filePath
	 *@param[in] 	transType
	 *@param[in] 	bIsOfflineFile	//1:是 0:不是
	 *@param[out] 	fileId
	 *@return 		成功：0		失败：非0,参考返回码
	 *@attention	无
	 *@par 			无
	**/
	UCSDK_API int UCSDK_CALL TransferFile(const char* pAcc,const char* filePath,
							const char* transType, int bIsOfflineFile, char fileId[FILEID_LENGTH]);


#ifdef __cplusplus
}
#endif 


#endif