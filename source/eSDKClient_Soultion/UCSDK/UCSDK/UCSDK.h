#ifndef _UC_SDK_PROXY_H_
#define _UC_SDK_PROXY_H_

#include "UCSDKAbsProxy.h"
#include "UCService.h"
#include "UCMessageSignalProcess.h"

#ifdef ESDKCLIENT_PLATFORM_DEPEND
#include "DynamicClass.h"
#endif


namespace eSDK {
	namespace UC {


#ifdef ESDKCLIENT_PLATFORM_DEPEND
class UCSDK : public UCSDKAbsProxy , public ProductUCSDK
#else
class UCSDK : public UCSDKAbsProxy
#endif
{
private:
	UCSDK();
	~UCSDK();

#ifdef ESDKCLIENT_PLATFORM_DEPEND
	DECLARE_RUNTIME(UCSDK)
#endif

public:
#ifdef ESDKCLIENT_PLATFORM_DEPEND
	static UCSDK* CreateInstance();
	static void DestroyInstance();
#else
	static UCSDK* Instance();
	static void Destroy();
#endif

public:
	virtual int Init();
	virtual int UnInit();
	virtual int Login(const std::string& strToken);
	virtual int Login(const std::string& strName, const std::string& strPassword);
	virtual int Logout();
	virtual int Config(const std::string& strSrvUrl);
	virtual int SetLang(const std::string& strLang);
	virtual int SetUCSignalRecvAbsProxy(UCSignalRecvAbsProxy* pUCSignalRecvAbsProxy);

#ifdef ESDKCLIENT_PLATFORM_DEPEND
public:
	virtual UCSDKAbsProxy* GetUCSDKAbsProxy();
	virtual UCContactMgrAbsProxy* GetUCContactMgrAbsProxy();
	virtual UCGroupAbsProxy* GetUCGroupAbsProxy();
	virtual UCIMAbsProxy* GetUCIMAbsProxy();
	virtual UCMeetingAbsProxy* GetUCMeetingAbsProxy();
	virtual UCPublicAbsProxy* GetUCPublicAbsProxy();
	virtual UCVoIPAbsProxy* GetUCVoIPAbsProxy();
#endif

private:
	std::string m_strSrvUrl;
	std::string m_strLang;

#ifdef ESDKCLIENT_PLATFORM_DEPEND
private:
	int m_iSignEvent;
	std::string m_strReason;
public:
	void SetSignEvent(int iSignEvent, const std::string& reason) { m_iSignEvent = iSignEvent; m_strReason = reason; }
#endif

private:
	static UCSDK* m_pUCSDKProxy;
	uc::model::UCClient* m_pUCClient;
	uc::model::conversation::ConversationMgr* m_pConvMgr;
	uc::model::ContactSubscription*  m_pContactSubManager;
	uc::model::ContactMgr* m_pContactMgr;

public:
	int ConnectSignNotify();
	int ConnectAVSess();
	int ConnectConference(uc::model::conversation::Conversation* pConversation);
	int ConnectInstantMessage();
	int ConnectGroup();	
	int ConnectFile() const;
	void DisConnectAll();

	void InitSubContactlist();
	void UninitContactSub();
private:
	UCMessageSignalProcess m_UCMessageSignalProcess;
};

}
}

#endif
