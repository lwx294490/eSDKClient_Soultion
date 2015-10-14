#include "stdafx.h"
#include "UCSDK.h"
#include "UCIMProxy.h"
#include "UCVoIPProxy.h"
#include "UCMeetingProxy.h"
#include "UCPublicProxy.h"
#include "UCGroupProxy.h"
#include "UCContactMgrProxy.h"
#include "eSDKLog.h"
#include "UCCommon.h"

#pragma comment(lib, "eSDKTool.lib")
int g_iLogInstanceIndex = 0;


namespace eSDK {
	namespace UC {


#ifdef ESDKCLIENT_PLATFORM_DEPEND
		IMPLEMENT_RUNTIME(UCSDK, eSDK::UC::UCSDK)
#endif

//////////////////////////////////////////////////////////////////////////
UCSDKAbsProxy::UCSDKAbsProxy()
{

}

UCSDKAbsProxy::~UCSDKAbsProxy()
{

}

UCSDKAbsProxy* UCSDKAbsProxy::GetInstance()
{
#ifdef ESDKCLIENT_PLATFORM_DEPEND
	return dynamic_cast<UCSDKAbsProxy*>(UCSDK::CreateInstance());
#else
	return dynamic_cast<UCSDKAbsProxy*>(UCSDK::Instance());
#endif
}
void UCSDKAbsProxy::ReleaseInstance()
{
#ifdef ESDKCLIENT_PLATFORM_DEPEND
	UCSDK::DestroyInstance();
#else
	UCSDK::Destroy();
#endif
}

//////////////////////////////////////////////////////////////////////////
UCSDK* UCSDK::m_pUCSDKProxy = NULL;

UCSDK::UCSDK()
	: m_strSrvUrl("")
	, m_strLang("")
#ifdef ESDKCLIENT_PLATFORM_DEPEND
	, m_iSignEvent(-1)
	, m_strReason("")
#endif
	, m_pUCClient(NULL)
	, m_pConvMgr(NULL)
	, m_pContactSubManager(NULL)
	, m_pContactMgr(NULL)
{

}

UCSDK::~UCSDK()
{
	m_pUCClient = NULL;
	m_pConvMgr = NULL;
	m_pContactSubManager = NULL;
	m_pContactMgr = NULL;
}

#ifdef ESDKCLIENT_PLATFORM_DEPEND
UCSDK* UCSDK::CreateInstance()
#else
UCSDK* UCSDK::Instance()
#endif
{
	if (NULL == m_pUCSDKProxy)
	{
		m_pUCSDKProxy = new UCSDK;
	}

	return m_pUCSDKProxy;
}

#ifdef ESDKCLIENT_PLATFORM_DEPEND
void UCSDK::DestroyInstance()
#else
void UCSDK::Destroy()
#endif
{
	if (NULL != m_pUCSDKProxy)
	{
		delete m_pUCSDKProxy;
		m_pUCSDKProxy = NULL;
	}

	UCIMProxy::Destroy();
	UCVoIPProxy::Destroy();
	UCMeetingProxy::Destroy();
	UCPublicProxy::Destroy();
	UCGroupProxy::Destroy();
	UCContactMgrProxy::Destroy();
}

int UCSDK::Init()
{
	//初始化日志
	eSDKLog *pLog = eSDKLog::getInstance();
	if (NULL == pLog)
	{
		return UCSDK_Fail;
	}
	int iRetLog = pLog->init("UCSDK", g_iLogInstanceIndex);
	if (ESDKLOG_SUCCESS != iRetLog)
	{
		return UCSDK_Fail;
	}
	DEBUG_LOG() << "--- ENTER";

	//初始化UCClient
	m_pUCClient = UCClient::GetClient();
	if (NULL == m_pUCClient)
	{
		ERROR_LOG() << "Get UCClient failed.";
		DEBUG_LOG() << "--- LEAVE";
		return UCSDK_Fail;
	}

	if (!m_pUCClient->Init())
	{
		ERROR_LOG() << "UCClient init failed.";
		DEBUG_LOG() << "--- LEAVE";
		return UCSDK_Fail;
	}

	m_pConvMgr = m_pUCClient->ConvManager;
	if (NULL == m_pConvMgr)
	{
		ERROR_LOG() << "m_pConvMgr is null.";
		DEBUG_LOG() << "--- LEAVE";
		return UCSDK_Fail;
	}
	m_pContactSubManager = m_pUCClient->ContactSubManager;
	if (NULL == m_pContactSubManager)
	{
		ERROR_LOG() << "m_pSubscribeMgr is null.";
		DEBUG_LOG() << "--- LEAVE";
		return UCSDK_NullPoint;
	}
	m_pContactMgr = m_pUCClient->ContactManager;
	if (NULL == m_pContactMgr)
	{
		ERROR_LOG() << "m_pContactMgr is null.";
		DEBUG_LOG() << "--- LEAVE";
		return UCSDK_NullPoint;
	}

	//初始化各组件
	//初始化UCIMProxy
	UCIMProxy* pUCIMProxy = UCIMProxy::Instance();
	CHECK_POINTER(pUCIMProxy, UCSDK_Fail);
	int iRet = pUCIMProxy->Init();
	CHECK_RETURN(iRet, UCSDK_Succ, "UCIMProxy init");

	//初始化UCVoIPProxy
	UCVoIPProxy* pUCVoIPProxy = UCVoIPProxy::Instance();
	CHECK_POINTER(pUCVoIPProxy, UCSDK_Fail);
	iRet = pUCVoIPProxy->Init();
	CHECK_RETURN(iRet, UCSDK_Succ, "UCVoIPProxy init");

	//初始化UCMeetingProxy
	UCMeetingProxy* pUCMeetingProxy = UCMeetingProxy::Instance();
	CHECK_POINTER(pUCMeetingProxy, UCSDK_Fail);
	iRet = pUCMeetingProxy->Init();
	CHECK_RETURN(iRet, UCSDK_Succ, "UCMeetingProxy init");

	//初始化UCPublicProxy
	UCPublicProxy* pUCPublicProxy = UCPublicProxy::Instance();
	CHECK_POINTER(pUCPublicProxy, UCSDK_Fail);
	iRet = pUCPublicProxy->Init();
	CHECK_RETURN(iRet, UCSDK_Succ, "UCPublicProxy init");

	//初始化UCGroupProxy
	UCGroupProxy* pUCGroupProxy = UCGroupProxy::Instance();
	CHECK_POINTER(pUCGroupProxy, UCSDK_Fail);
	iRet = pUCGroupProxy->Init();
	CHECK_RETURN(iRet, UCSDK_Succ, "UCGroupProxy init");

	//初始化UCContactMgrProxy
	UCContactMgrProxy* pUCContactMgrProxy = UCContactMgrProxy::Instance();
	CHECK_POINTER(pUCContactMgrProxy, UCSDK_Fail);
	iRet = pUCContactMgrProxy->Init();
	CHECK_RETURN(iRet, UCSDK_Succ, "UCContactMgrProxy init");

	//设置信号
	m_UCMessageSignalProcess.SetUCSignalRecvAbsProxy(NULL);

	DEBUG_LOG() << "--- LEAVE";
	return UCSDK_Succ;
}

int UCSDK::UnInit()
{
	DEBUG_LOG() << "--- ENTER";

	//去初始化各组件
	//去初始化UCIMProxy
	UCIMProxy* pUCIMProxy = UCIMProxy::Instance();
	CHECK_POINTER(pUCIMProxy, UCSDK_Fail);
	int iRet = pUCIMProxy->UnInit();
	CHECK_RETURN(iRet, UCSDK_Succ, "UCIMProxy uninit");

	//去初始化UCVoIPProxy
	UCVoIPProxy* pUCVoIPProxy = UCVoIPProxy::Instance();
	CHECK_POINTER(pUCVoIPProxy, UCSDK_Fail);
	iRet = pUCVoIPProxy->UnInit();
	CHECK_RETURN(iRet, UCSDK_Succ, "UCVoIPProxy uninit");

	//去初始化UCMeetingProxy
	UCMeetingProxy* pUCMeetingProxy = UCMeetingProxy::Instance();
	CHECK_POINTER(pUCMeetingProxy, UCSDK_Fail);
	iRet = pUCMeetingProxy->UnInit();
	CHECK_RETURN(iRet, UCSDK_Succ, "UCMeetingProxy uninit");

	//去初始化UCPublicProxy
	UCPublicProxy* pUCPublicProxy = UCPublicProxy::Instance();
	CHECK_POINTER(pUCPublicProxy, UCSDK_Fail);
	iRet = pUCPublicProxy->UnInit();
	CHECK_RETURN(iRet, UCSDK_Succ, "UCPublicProxy uninit");

	//去初始化UCGroupProxy
	UCGroupProxy* pUCGroupProxy = UCGroupProxy::Instance();
	CHECK_POINTER(pUCGroupProxy, UCSDK_Fail);
	iRet = pUCGroupProxy->UnInit();
	CHECK_RETURN(iRet, UCSDK_Succ, "UCGroupProxy uninit");

	//去初始化UCContactMgrProxy
	UCContactMgrProxy* pUCContactMgrProxy = UCContactMgrProxy::Instance();
	CHECK_POINTER(pUCContactMgrProxy, UCSDK_Fail);
	iRet = pUCContactMgrProxy->UnInit();
	CHECK_RETURN(iRet, UCSDK_Succ, "UCContactMgrProxy uninit");

	//uc 去初始化
	if (NULL != m_pConvMgr)
	{
		m_pConvMgr->DisconObserver();
	}
	if (NULL != m_pUCClient)
	{
		if (!m_pUCClient->UnInit())
		{
			ERROR_LOG() << "UCClient uninit failed.";
			//return UCSDK_Fail;
		}
		//UCClient::ReleaseClient();
		m_pUCClient = NULL;
	}
	
	m_pConvMgr = NULL;
	m_pContactSubManager = NULL;
	m_pContactMgr = NULL;
	m_UCMessageSignalProcess.SetUCSignalRecvAbsProxy(NULL);

	DEBUG_LOG() << "--- LEAVE";
	eSDKLog::destroyInstance();
	return UCSDK_Succ;
}

int UCSDK::Login(const std::string& strToken)
{
	DEBUG_LOG() << "--- ENTER";

	if (strToken.empty())
	{
		ERROR_LOG() << "Token is empty.";
		DEBUG_LOG() << "--- LEAVE";
		return UCSDK_InvalidParam;
	}
	INFO_PARAM2(m_strSrvUrl, m_strLang);
	if (m_strSrvUrl.empty() || m_strLang.empty())
	{
		ERROR_LOG() << "Server url or language is null.";
		DEBUG_LOG() << "--- LEAVE";
		return UCSDK_Fail;
	}
	if (NULL == m_pUCClient)
	{
		ERROR_LOG() << "m_pUCClient is null.";
		DEBUG_LOG() << "--- LEAVE";
		return UCSDK_NullPoint;
	}

	//连接信号
	(void)ConnectSignNotify();

	m_pUCClient->SignConfig.internalurl = m_strSrvUrl;	//登录URL，格式为IP:Port
	m_pUCClient->SignConfig.externalsurl = m_strSrvUrl;
	m_pUCClient->SignConfig.lang = m_strLang;			//语言

	//其他参数采用默认				
	m_pUCClient->SignConfig.ver = "v2.1.3.35";			//版本
	m_pUCClient->SignConfig.signinmode = ByTicket;		//登录模式默认为账户+密码
	m_pUCClient->SignConfig.initStatus = Online;	
	m_pUCClient->SignConfig.siteID = Server1;

	if (!m_pUCClient->SignIn())
	{
		ERROR_LOG() << "SignIn failed.";
		DEBUG_LOG() << "--- LEAVE";
		return UCSDK_Fail;
	}

#ifdef ESDKCLIENT_PLATFORM_DEPEND
	m_iSignEvent = -1;
	int iTimeOut = 60;//30 second
	while (-1 == m_iSignEvent)
	{
		Sleep(500);
		if (--iTimeOut <= 0)
		{
			ERROR_LOG() << "Sign time out!!!";
			DEBUG_LOG() << "--- LEAVE";
			return UCSDK_Fail;
		}
	}
	if ((int)UCClient::Client_SignedIn != m_iSignEvent)
	{
		ERROR_LOG() << "SignIn failed!!!";
		DEBUG_LOG() << "--- LEAVE";
		return UCSDK_Fail;
	}
#endif

	DEBUG_LOG() << "--- LEAVE";
	return UCSDK_Succ;
}

int UCSDK::Login(const std::string& strName, const std::string& strPassword)
{
	DEBUG_LOG() << "--- ENTER";

	INFO_PARAM1(strName);
	if (strName.empty() || strPassword.empty())
	{
		ERROR_LOG() << "Name or password is empty.";
		DEBUG_LOG() << "--- LEAVE";
		return UCSDK_InvalidParam;
	}
	INFO_PARAM2(m_strSrvUrl, m_strLang);
	if (m_strSrvUrl.empty() || m_strLang.empty())
	{
		ERROR_LOG() << "Server url or language is null.";
		DEBUG_LOG() << "--- LEAVE";
		return UCSDK_Fail;
	}
	if (NULL == m_pUCClient)
	{
		ERROR_LOG() << "m_pUCClient is null.";
		DEBUG_LOG() << "--- LEAVE";
		return UCSDK_NullPoint;
	}

	//连接信号
	(void)ConnectSignNotify();

	m_pUCClient->SignConfig.account = strName;			//登录账号
	m_pUCClient->SignConfig.pwd = strPassword;			//登录密码	
	m_pUCClient->SignConfig.internalurl = m_strSrvUrl;	//登录URL，格式为IP:Port
	m_pUCClient->SignConfig.externalsurl = m_strSrvUrl;
	m_pUCClient->SignConfig.lang = m_strLang;			//语言

	//其他参数采用默认				
	m_pUCClient->SignConfig.ver = "v2.1.3.35";			//版本
	m_pUCClient->SignConfig.signinmode = AccountAndPwd;	//登录模式默认为账户+密码
	m_pUCClient->SignConfig.initStatus = Online;	
	m_pUCClient->SignConfig.siteID = Server1;

	if (!m_pUCClient->SignIn())
	{
		ERROR_LOG() << "SignIn failed.";
		DEBUG_LOG() << "--- LEAVE";
		return UCSDK_Fail;
	}

#ifdef ESDKCLIENT_PLATFORM_DEPEND
	m_iSignEvent = -1;
	int iTimeOut = 60;//30 second
	while (-1 == m_iSignEvent)
	{
		Sleep(500);
		if (--iTimeOut <= 0)
		{
			ERROR_LOG() << "Sign time out!!!";
			DEBUG_LOG() << "--- LEAVE";
			return UCSDK_Fail;
		}
	}
	if ((int)UCClient::Client_SignedIn != m_iSignEvent)
	{
		ERROR_LOG() << "SignIn failed!!!";
		DEBUG_LOG() << "--- LEAVE";
		return UCSDK_Fail;
	}
#endif

	DEBUG_LOG() << "--- LEAVE";
	return UCSDK_Succ;
}

int UCSDK::Logout()
{
	DEBUG_LOG() << "--- ENTER";

	if (NULL == m_pUCClient)
	{
		ERROR_LOG() << "m_pUCClient is null.";
		DEBUG_LOG() << "--- LEAVE";
		return UCSDK_NullPoint;
	}

	if (!m_pUCClient->SignOut())
	{
		ERROR_LOG() << "SignOut failed.";
		DEBUG_LOG() << "--- LEAVE";
		return UCSDK_Fail;
	}

#ifdef ESDKCLIENT_PLATFORM_DEPEND
	m_iSignEvent = -1;
	m_strReason = "";
	int iTimeOut = 60;//30 second
	while (-1 == m_iSignEvent)
	{
		Sleep(500);
		if (--iTimeOut <= 0)
		{
			ERROR_LOG() << "Sign time out!!!";
			DEBUG_LOG() << "--- LEAVE";
			return UCSDK_Fail;
		}
	}
	if ((int)UCClient::Client_SignedFailed != m_iSignEvent || "signout" != m_strReason)
	{
		ERROR_LOG() << "SignOut failed!!!";
		DEBUG_LOG() << "--- LEAVE";
		return UCSDK_Fail;
	}
#endif

	DEBUG_LOG() << "--- LEAVE";
	return UCSDK_Succ;
}

int UCSDK::Config(const std::string& strSrvUrl)
{
	DEBUG_LOG() << "--- ENTER";
	INFO_PARAM1(strSrvUrl);

	m_strSrvUrl = strSrvUrl;

	DEBUG_LOG() << "--- LEAVE";
	return UCSDK_Succ;
}

int UCSDK::SetLang(const std::string& strLang)
{
	DEBUG_LOG() << "--- ENTER";
	INFO_PARAM1(strLang);

	m_strLang = strLang;

	DEBUG_LOG() << "--- LEAVE";
	return UCSDK_Succ;
}

int UCSDK::SetUCSignalRecvAbsProxy(UCSignalRecvAbsProxy* pUCSignalRecvAbsProxy)
{
	DEBUG_LOG() << "--- ENTER";
	INFO_PARAM1(pUCSignalRecvAbsProxy);

	if (NULL == pUCSignalRecvAbsProxy)
	{
		ERROR_LOG() << "pUCSignalRecvAbsProxy is null.";
		DEBUG_LOG() << "--- LEAVE";
		return UCSDK_InvalidParam;
	}

	m_UCMessageSignalProcess.SetUCSignalRecvAbsProxy(pUCSignalRecvAbsProxy);

	DEBUG_LOG() << "--- LEAVE";
	return UCSDK_Succ;
}

#ifdef ESDKCLIENT_PLATFORM_DEPEND
UCSDKAbsProxy* UCSDK::GetUCSDKAbsProxy()
{
	return UCSDKAbsProxy::GetInstance();
}

UCContactMgrAbsProxy* UCSDK::GetUCContactMgrAbsProxy()
{
	return UCContactMgrAbsProxy::GetInstance();
}

UCGroupAbsProxy* UCSDK::GetUCGroupAbsProxy()
{
	return UCGroupAbsProxy::GetInstance();
}

UCIMAbsProxy* UCSDK::GetUCIMAbsProxy()
{
	return UCIMAbsProxy::GetInstance();
}

UCMeetingAbsProxy* UCSDK::GetUCMeetingAbsProxy()
{
	return UCMeetingAbsProxy::GetInstance();
}

UCPublicAbsProxy* UCSDK::GetUCPublicAbsProxy()
{
	return UCPublicAbsProxy::GetInstance();
}

UCVoIPAbsProxy* UCSDK::GetUCVoIPAbsProxy()
{
	return UCVoIPAbsProxy::GetInstance();
}
#endif


//////////////////////////////////////////////////////////////////////////
int UCSDK::ConnectSignNotify()
{
	DEBUG_LOG() << "--- ENTER";
	if (NULL == m_pUCClient)
	{
		ERROR_LOG() << "m_pUCClient is null.";
		DEBUG_LOG() << "--- LEAVE";
		return UCSDK_NullPoint;
	}
	if (NULL == m_pContactSubManager)
	{
		ERROR_LOG() << "m_pSubscribeMgr is null.";
		DEBUG_LOG() << "--- LEAVE";
		return UCSDK_NullPoint;
	}

	m_pUCClient->SignInNotify_.disconnect_all();
	m_pUCClient->SignInNotify_.connect(&m_UCMessageSignalProcess, &UCMessageSignalProcess::OnSignInNotify);

	//连接状态信号
	m_pContactSubManager->UserAvailabilityChanged_.disconnect_all();
	m_pContactSubManager->UserAvailabilityChanged_.connect(&m_UCMessageSignalProcess, &UCMessageSignalProcess::OnStatusChanged);

	DEBUG_LOG() << "--- LEAVE";
	return UCSDK_Succ;
}

int UCSDK::ConnectAVSess()
{
	DEBUG_LOG() << "--- ENTER";
	if (NULL == m_pConvMgr)
	{
		ERROR_LOG() << "m_pConvMgr is null.";
		DEBUG_LOG() << "--- LEAVE";
		return UCSDK_NullPoint;
	}

	m_pConvMgr->AVSessionRinged.disconnect_all();
	m_pConvMgr->AVSessAdded.disconnect_all();
	m_pConvMgr->AVSessionConnected.disconnect_all();
	m_pConvMgr->AVSessionClosed.disconnect_all();

	m_pConvMgr->AVSessionRinged.connect(&m_UCMessageSignalProcess, &UCMessageSignalProcess::OnAVSessionRinged);
	m_pConvMgr->AVSessAdded.connect(&m_UCMessageSignalProcess, &UCMessageSignalProcess::OnAVSessAdded);
	m_pConvMgr->AVSessionConnected.connect(&m_UCMessageSignalProcess, &UCMessageSignalProcess::OnAVSessionConnected);
	m_pConvMgr->AVSessionClosed.connect(&m_UCMessageSignalProcess, &UCMessageSignalProcess::OnAVSessionClosed);

	DEBUG_LOG() << "--- LEAVE";
	return UCSDK_Succ;
}

int UCSDK::ConnectConference(uc::model::conversation::Conversation* pConversation)
{
	DEBUG_LOG() << "--- ENTER";
	if (NULL == pConversation)
	{
		ERROR_LOG() << "pConversation is null.";
		DEBUG_LOG() << "--- LEAVE";
		return UCSDK_InvalidParam;
	}

	pConversation->ConvMemberStatusChanged.disconnect_all();
	pConversation->ConvMemAllowSpeak.disconnect_all();
	pConversation->ConvMemForbidSpeak.disconnect_all();
	pConversation->ConvCurSpeaker.disconnect_all();
	pConversation->ConvGroupMemberChanged.disconnect_all();

	pConversation->ConvMemberStatusChanged.connect(&m_UCMessageSignalProcess, &UCMessageSignalProcess::OnConvMemberStatusChanged);
	pConversation->ConvMemAllowSpeak.connect(&m_UCMessageSignalProcess, &UCMessageSignalProcess::OnConvMemAllowSpeak);
	pConversation->ConvMemForbidSpeak.connect(&m_UCMessageSignalProcess, &UCMessageSignalProcess::OnConvMemForbidSpeak);
	pConversation->ConvCurSpeaker.connect(&m_UCMessageSignalProcess, &UCMessageSignalProcess::OnConvMemCurSpeaker);
	pConversation->ConvGroupMemberChanged.connect(&m_UCMessageSignalProcess,&UCMessageSignalProcess::OnConvGroupMemberChanged);

	DEBUG_LOG() << "--- LEAVE";
	return UCSDK_Succ;
}

int UCSDK::ConnectInstantMessage()
{
	DEBUG_LOG() << "--- ENTER";
	if (NULL == m_pConvMgr)
	{
		ERROR_LOG() << "m_pConvMgr is null.";
		DEBUG_LOG() << "--- LEAVE";
		return UCSDK_NullPoint;
	}

	m_pConvMgr->InstantMessageReceived.disconnect_all();
	m_pConvMgr->InstantSessRemoved.disconnect_all();
	m_pConvMgr->InstantSessAdded.disconnect_all();
	m_pConvMgr->SystemMsgReceived.disconnect_all();

	m_pConvMgr->InstantMessageReceived.connect(&m_UCMessageSignalProcess, &UCMessageSignalProcess::OnReceivedIMMessage);
	m_pConvMgr->InstantSessRemoved.connect(&m_UCMessageSignalProcess, &UCMessageSignalProcess::OnInstantSessRemoved);
	m_pConvMgr->InstantSessAdded.connect(&m_UCMessageSignalProcess, &UCMessageSignalProcess::OnInstantSessAdded);
	m_pConvMgr->SystemMsgReceived.connect(&m_UCMessageSignalProcess, &UCMessageSignalProcess::OnSystemMsgReceived);


	DEBUG_LOG() << "--- LEAVE";
	return UCSDK_Succ;
}

int UCSDK::ConnectGroup()
{
	DEBUG_LOG() << "--- ENTER";
	if (NULL == m_pContactMgr)
	{
		ERROR_LOG() << "m_pContactMgr is null.";
		DEBUG_LOG() << "--- LEAVE";
		return UCSDK_NullPoint;
	}

	m_pContactMgr->IncreContactsChanged_.disconnect_all();
	m_pContactMgr->FixedGroupInvitation_.disconnect_all();
	m_pContactMgr->FixedGroupInvitationRes_.disconnect_all();
	m_pContactMgr->LeaveFromFixedGroup_.disconnect_all();
	m_pContactMgr->JoinFixedGroupRequset_.disconnect_all();
	m_pContactMgr->JoinFixedGroupRes_.disconnect_all();
	m_pContactMgr->MemberAdded_.disconnect_all();
	m_pContactMgr->MemberRemoved_.disconnect_all();
	m_pContactMgr->MemberFlowChanged_.disconnect_all();
	m_pContactMgr->FixedGroupInfoChanged_.disconnect_all();

	m_pContactMgr->IncreContactsChanged_.connect(&m_UCMessageSignalProcess,&UCMessageSignalProcess::OnIncreContactsChanged);
	m_pContactMgr->FixedGroupInvitation_.connect(&m_UCMessageSignalProcess, &UCMessageSignalProcess::OnGroupInvitation);
	m_pContactMgr->FixedGroupInvitationRes_.connect(&m_UCMessageSignalProcess, &UCMessageSignalProcess::OnGroupInvitationRes);
	m_pContactMgr->LeaveFromFixedGroup_.connect(&m_UCMessageSignalProcess, &UCMessageSignalProcess::OnLeaveFromFixedGroup);
	m_pContactMgr->JoinFixedGroupRequset_.connect(&m_UCMessageSignalProcess, &UCMessageSignalProcess::OnJoinFixedGroupRequest);
	m_pContactMgr->JoinFixedGroupRes_.connect(&m_UCMessageSignalProcess, &UCMessageSignalProcess::OnJoinFixedGroupRes);
	m_pContactMgr->MemberAdded_.connect(&m_UCMessageSignalProcess, &UCMessageSignalProcess::OnMemberAdded);
	m_pContactMgr->MemberRemoved_.connect(&m_UCMessageSignalProcess, &UCMessageSignalProcess::OnMemberRemoved);
	m_pContactMgr->MemberFlowChanged_.connect(&m_UCMessageSignalProcess, &UCMessageSignalProcess::OnMemberFlowChanged);
	m_pContactMgr->FixedGroupInfoChanged_.connect(&m_UCMessageSignalProcess, &UCMessageSignalProcess::OnFixedGroupInfoChanged);

	DEBUG_LOG() << "--- LEAVE";
	return UCSDK_Succ;
}

int UCSDK::ConnectFile() const
{
	DEBUG_LOG() << "--- ENTER";

	DEBUG_LOG() << "--- LEAVE";
	return UCSDK_Succ;
}

void UCSDK::DisConnectAll()
{
	DEBUG_LOG() << "--- ENTER";
	if (NULL != m_pUCClient)
	{
		m_pUCClient->SignInNotify_.disconnect_all();
	}
	
	if (NULL != m_pContactSubManager)
	{
		m_pContactSubManager->UserAvailabilityChanged_.disconnect_all();
	}

	if (NULL != m_pConvMgr)
	{
		m_pConvMgr->AVSessionRinged.disconnect_all();
		m_pConvMgr->AVSessAdded.disconnect_all();
		m_pConvMgr->AVSessionConnected.disconnect_all();
		m_pConvMgr->AVSessionClosed.disconnect_all();
		m_pConvMgr->InstantMessageReceived.disconnect_all();
		m_pConvMgr->InstantSessRemoved.disconnect_all();
		m_pConvMgr->InstantSessAdded.disconnect_all();
		m_pConvMgr->SystemMsgReceived.disconnect_all();
	}
	
	if (NULL != m_pContactMgr)
	{
		m_pContactMgr->IncreContactsChanged_.disconnect_all();
		m_pContactMgr->FixedGroupInvitation_.disconnect_all();
		m_pContactMgr->FixedGroupInvitationRes_.disconnect_all();
		m_pContactMgr->LeaveFromFixedGroup_.disconnect_all();
		m_pContactMgr->JoinFixedGroupRequset_.disconnect_all();
		m_pContactMgr->JoinFixedGroupRes_.disconnect_all();
		m_pContactMgr->MemberAdded_.disconnect_all();
		m_pContactMgr->MemberRemoved_.disconnect_all();
		m_pContactMgr->MemberFlowChanged_.disconnect_all();
		m_pContactMgr->FixedGroupInfoChanged_.disconnect_all();
	}
	DEBUG_LOG() << "--- LEAVE";
}

void UCSDK::InitSubContactlist()
{
	DEBUG_LOG() << "--- ENTER";

	if (NULL != m_pContactSubManager)
	{
		m_pContactSubManager->InitSubContactlist();
	}

	DEBUG_LOG() << "--- LEAVE";
}

void UCSDK::UninitContactSub()
{
	DEBUG_LOG() << "--- ENTER";

	if (NULL != m_pContactMgr)
	{
		m_pContactMgr->Uninit();
	}

	DEBUG_LOG() << "--- LEAVE";
}

}
}
