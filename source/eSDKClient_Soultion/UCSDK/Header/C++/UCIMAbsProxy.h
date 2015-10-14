#ifndef _UC_IM_ABS_PROXY_H_
#define _UC_IM_ABS_PROXY_H_

#include "DataType.h"


namespace eSDK {
	namespace UC {


/**
 *��ʱ��Ϣ���ļ����������
 * 
 *�������ڴ���ʱ��Ϣ���ͺ��ļ�����
 *
 *@attention	��
 *@par			��
**/
class UCSDK_API UCIMAbsProxy
{
protected:
	UCIMAbsProxy();
	virtual ~UCIMAbsProxy();

public:
	/**
	 *��ȡ��ʱ��Ϣ���ļ���������൥ʵ��
	 * 
	 *�ú������ڻ�ȡ��ʱ��Ϣ���ļ���������൥ʵ��
	 *
	 *@return		�ɹ�����ʱ��Ϣ���ļ���������൥ʵ��ָ�룬 ʧ�ܣ�NULL
	 *@attention	��
	 *@par			��
	**/
	static UCIMAbsProxy* GetInstance();

	/**
	 *�ͷż�ʱ��Ϣ���ļ���������൥ʵ��
	 * 
	 *�ú��������ͷż�ʱ��Ϣ���ļ���������൥ʵ��
	 *
	 *@attention	�ڵ���UCSDKAbsProxy::ReleaseInstance()ʱ�򣬻����һ���ͷ�
	 *@par			��
	**/
	static void ReleaseInstance();

public:
	/**
	 *���ͼ�ʱ��Ϣ
	 * 
	 *�ú������ڷ��ͼ�ʱ��Ϣ
	 *
	 *@param[in]	strIMMsg
	 *@param[in]	accountList
	 *@param[in/out]conversationID
	 *@return		�ɹ���0		ʧ�ܣ���0,�ο�������
	 *@attention	1.��conversationIDΪ��ʱ��Ҫʹ��accountList����conversationID��Ϊ��ʱ��ʹ��accountList
	 *				2.��strIMMsgΪ�գ�conversationIDΪ��ʱ�ᴴ��conversation�����طǿ�conversationID
	 *@par			��
	**/
	virtual int SendIMMessage(const std::string& strIMMsg, const AccountList& accountList, std::string &conversationID) = 0;

	/**
	 *����conversationID�رջỰ��conversation��
	 * 
	 *�ú������ڸ���conversationID�رջỰ��conversation��
	 *
	 *@param[in] 	conversationID
	 *@return 		�ɹ���0		ʧ�ܣ���0,�ο�������
	 *@attention	�ر�conversation�������Ự���IMSession��AVSession��
	 *@par 			��
	**/
	virtual int CloseConversation(const std::string &conversationID) = 0;

	/**
	 *�����ļ�
	 * 
	 *�ú������ڽ����ļ�
	 *
	 *@param[in] 	strFileID
	 *@param[in] 	strFilePath
	 *@return 		�ɹ���0		ʧ�ܣ���0,�ο�������
	 *@attention	��
	 *@par 			��
	**/
	virtual int AcceptFile(const std::string& strFileID, const std::string& strFilePath) = 0;

	/**
	 *ȡ�����ͻ�����ļ�
	 * 
	 *�ú�������ȡ�����ͻ�����ļ�
	 *
	 *@param[in] 	strFileID
	 *@return 		�ɹ���0		ʧ�ܣ���0,�ο�������
	 *@attention	��
	 *@par 			��
	**/
	virtual int CancelFile(const std::string& strFileID) = 0;

	/**
	 *�ܾ������ļ�
	 * 
	 *�ú������ھܾ������ļ�
	 *
	 *@param[in] 	strFileID
	 *@return 		�ɹ���0		ʧ�ܣ���0,�ο�������
	 *@attention	��
	 *@par 			��
	**/
	virtual int RejectFile(const std::string& strFileID) = 0;

	/**
	 *�����ļ�
	 * 
	 *�ú������ڷ����ļ�
	 *
	 *@param[in] 	strAccout
	 *@param[in] 	strFilePath
	 *@param[in] 	strTransType
	 *@param[in] 	bIsOfflineFile
	 *@return 		�ɹ���0		ʧ�ܣ���0,�ο�������
	 *@attention	��
	 *@par 			��
	**/
	virtual std::string TransferFile(const std::string& strAccout,
		const std::string& strFilePath, const std::string& strTransType, bool bIsOfflineFile) = 0;
};

}
}

#endif