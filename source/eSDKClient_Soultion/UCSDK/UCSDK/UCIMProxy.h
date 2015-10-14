#ifndef _UC_IM_PROXY_H_
#define _UC_IM_PROXY_H_

#include "UCIMAbsProxy.h"


namespace eSDK {
	namespace UC {


class UCIMProxy : public UCIMAbsProxy
{
private:
	UCIMProxy();
	~UCIMProxy();

public:
	static UCIMProxy* Instance();
	static void Destroy();

public:
	virtual int SendIMMessage(const std::string& strIMMsg, const AccountList& accountList, std::string &conversationID);
	virtual int CloseConversation(const std::string &conversationID);
	virtual int AcceptFile(const std::string& strFileID, const std::string& strFilePath);
	virtual int CancelFile(const std::string& strFileID);
	virtual int RejectFile(const std::string& strFileID);
	virtual std::string TransferFile(const std::string& strAccout,
		const std::string& strFilePath, const std::string& strTransType, bool bIsOfflineFile);

public:
	int Init();
	int UnInit();

private:
	int GetIMSessionByConversationID(const AccountList& accountList, std::string &conversationID, conversation::InstantMsgSession** ppIMSession) const;

private:
	UCClient* m_pUCClient;

private:
	static UCIMProxy* m_pUCIMProxy;
};

}
}

#endif
