#ifndef _UC_VOIP_PROXY_H_
#define _UC_VOIP_PROXY_H_

#include "UCVoIPAbsProxy.h"
#include "UCObserver.h"


namespace eSDK {
	namespace UC {


class UCVoIPProxy : public UCVoIPAbsProxy
{
private:
	UCVoIPProxy();
	~UCVoIPProxy();

public:
	static UCVoIPProxy* Instance();
	static void Destroy();

public:
	virtual int MakeCall(std::string& strConvID, const UCSDKContact& member, int iType,
		const STVideoWindow& localWnd, const STVideoWindow& remoteWnd);
	virtual int Accept(const std::string& strConvID, int iType, const STVideoWindow& localWnd, const STVideoWindow& remoteWnd);
	virtual int Reject(const std::string& strConvID, int iType);
	virtual int Hangup(const std::string& strConvID, int iType);	
	virtual int Hold(const std::string& strConvID);
	virtual int Resume(const std::string& strConvID);
	virtual int Forward(const std::string& strConvID, const std::string& strAccount);
	virtual int StartRecord(const std::string& strConvID, const std::string& strFilePath);
	virtual int StopRecord(const std::string& strConvID);
	virtual int Mute(const int iType);
	virtual int UnMute(const int iType);

public:
	int Init();
	int UnInit();
	int DeviceMgrInit();
	int DeviceMgrUnInit();
	uc::model::conversation::ConversationMgr* GetConvMgr();

	//¸¨Öúº¯Êý
private:
	uc::model::conversation::Conversation* GetConversation(const std::string& strConvID);
	uc::model::conversation::AVSession* GetAVSession(const std::string& strConvID);

private:
	uc::model::conversation::ConversationMgr* m_pConvManager;
	uc::model::device::DeviceMgr* m_pDevMgr;
	static UCObserver m_UCSDKObserver;

private:
	static UCVoIPProxy* m_pUCVoIPProxy;
};

}
}

#endif
