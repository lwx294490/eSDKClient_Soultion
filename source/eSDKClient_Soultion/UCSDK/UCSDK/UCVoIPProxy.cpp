#include "stdafx.h"
#include "UCVoIPProxy.h"
#include "UCContactMgrProxy.h"
#include "eSDKLog.h"


namespace eSDK {
	namespace UC {


UCVoIPAbsProxy::UCVoIPAbsProxy()
{

}

UCVoIPAbsProxy::~UCVoIPAbsProxy()
{

}

UCVoIPAbsProxy* UCVoIPAbsProxy::GetInstance()
{
	return dynamic_cast<UCVoIPAbsProxy*>(UCVoIPProxy::Instance());
}

void UCVoIPAbsProxy::ReleaseInstance()
{
	UCVoIPProxy::Destroy();
}

//////////////////////////////////////////////////////////////////////////
UCVoIPProxy* UCVoIPProxy::m_pUCVoIPProxy = NULL;
UCObserver UCVoIPProxy::m_UCSDKObserver;

UCVoIPProxy::UCVoIPProxy()
	: m_pConvManager(NULL)
	, m_pDevMgr(NULL)
{

}

UCVoIPProxy::~UCVoIPProxy()
{
	m_pConvManager = NULL;
	m_pDevMgr = NULL;
}

UCVoIPProxy* UCVoIPProxy::Instance()
{
	if (NULL == m_pUCVoIPProxy)
	{
		m_pUCVoIPProxy = new UCVoIPProxy;
	}

	return m_pUCVoIPProxy;
}

void UCVoIPProxy::Destroy()
{
	if (NULL != m_pUCVoIPProxy)
	{
		delete m_pUCVoIPProxy;
		m_pUCVoIPProxy = NULL;
	}
}

int UCVoIPProxy::Init()
{
	DEBUG_LOG() << "--- ENTER";

	uc::model::UCClient* pUCClient = UCClient::GetClient();
	if(NULL == pUCClient)
	{
		ERROR_LOG() << "Get UCClient failed.";
		DEBUG_LOG() << "--- LEAVE";
		return UCSDK_NullPoint;
	}

	m_pConvManager = pUCClient->ConvManager;
	if (NULL == m_pConvManager)
	{
		ERROR_LOG() << "ConvManager is null.";
		DEBUG_LOG() << "--- LEAVE";
		return UCSDK_NullPoint;
	}

	m_pConvManager->observer = &m_UCSDKObserver;

	m_pDevMgr = pUCClient->DeviceManager;
	if (NULL == m_pDevMgr)
	{
		ERROR_LOG() << "DeviceManager is null.";
		DEBUG_LOG() << "--- LEAVE";
		return UCSDK_NullPoint;
	}

	DEBUG_LOG() << "--- LEAVE";
	return UCSDK_Succ;
}

int UCVoIPProxy::UnInit()
{
	DEBUG_LOG() << "--- ENTER";

	m_pConvManager = NULL;
	m_pDevMgr = NULL;

	DEBUG_LOG() << "--- LEAVE";
	return UCSDK_Succ;
}

int UCVoIPProxy::DeviceMgrInit()
{
	DEBUG_LOG() << "--- ENTER";

	if (NULL == m_pDevMgr)
	{
		ERROR_LOG() << "DeviceManager is null.";
		DEBUG_LOG() << "--- LEAVE";
		return UCSDK_NullPoint;
	}
	
	if (!m_pDevMgr->Init())
	{
		ERROR_LOG() << "Device mgr init failed.";
		DEBUG_LOG() << "--- LEAVE";
		return UCSDK_Fail;
	}

	DEBUG_LOG() << "--- LEAVE";
	return UCSDK_Succ;
}

int UCVoIPProxy::DeviceMgrUnInit()
{
	DEBUG_LOG() << "--- ENTER";

	if (NULL == m_pDevMgr)
	{
		ERROR_LOG() << "DeviceManager is null.";
		DEBUG_LOG() << "--- LEAVE";
		return UCSDK_NullPoint;
	}

	if (!m_pDevMgr->Uninit())
	{
		ERROR_LOG() << "Device mgr uninit failed.";
		DEBUG_LOG() << "--- LEAVE";
		return UCSDK_Fail;
	}

	DEBUG_LOG() << "--- LEAVE";
	return UCSDK_Succ;
}

ConversationMgr* UCVoIPProxy::GetConvMgr()
{
	return m_pConvManager;
}

int UCVoIPProxy::MakeCall(std::string& strConvID, const UCSDKContact& member, int iType,
	const STVideoWindow& localWnd, const STVideoWindow& remoteWnd)
{
	DEBUG_LOG() << "--- ENTER";
	INFO_PARAM2(strConvID, iType);

	//У�����
	if(NULL == m_pConvManager)
	{
		ERROR_LOG() << "ConvManager is null.";
		DEBUG_LOG() << "--- LEAVE";
		return UCSDK_NullPoint;
	}

	//����AVSession
	if (m_pConvManager->HasConnectingAVSession())
	{
		ERROR_LOG() << "Connecting av session is exist.";
		DEBUG_LOG() << "--- LEAVE";
		return UCSDK_ExistAVSess;
	}

	//��ȡ�Ự
	conversation::Conversation* pConversation = NULL;
	if(!strConvID.empty())
	{
		pConversation = m_pConvManager->GetConversation(strConvID);
	}

	if(NULL == pConversation)
	{
		pConversation = m_pConvManager->AddConversation();
		if (NULL == pConversation)
		{
			ERROR_LOG() << "Add conversation failed.";
			DEBUG_LOG() << "--- LEAVE";
			return UCSDK_Fail;
		}

		strConvID = pConversation->propmap_[conversation::ConvIdentifier];
	}

	//��Ӻ��г�Ա
	Contact contact;
	UCContactMgrProxy* pUCContactMgrProxy = UCContactMgrProxy::Instance();
	if (NULL == pUCContactMgrProxy)
	{
		ERROR_LOG() << "UCContactMgrProxy's instance is null.";
		DEBUG_LOG() << "--- LEAVE";
		return UCSDK_Fail;
	}
	if (!pUCContactMgrProxy->GetContactByUCSDKContact(member, contact))
	{
		ERROR_LOG() << "GetContactByUCContact failed.";
		DEBUG_LOG() << "--- LEAVE";
		return UCSDK_InvalidParam;
	}
	if (!pConversation->AddParticipant(contact))
	{
		ERROR_LOG() << "AddParticipant failed.";
		DEBUG_LOG() << "--- LEAVE";
		return UCSDK_Fail;
	}

	//��ȡAV Session
	conversation::AVSession* pAVSession = NULL;
	if(pConversation->HasSession(AudioVideo))
	{
		pAVSession = dynamic_cast<conversation::AVSession*>(pConversation->GetSession(AudioVideo));
		if (NULL == pAVSession)
		{
			ERROR_LOG() << "Get av session failed.";
			DEBUG_LOG() << "--- LEAVE";
			return UCSDK_Fail;
		}

		//������Ƶ����
		if (Call_Video == iType)
		{
			pAVSession->videochannel_.remotewnd_.wnd_ = (HWND)remoteWnd.hWnd;
			pAVSession->videochannel_.remotewnd_.top_ = remoteWnd.top;
			pAVSession->videochannel_.remotewnd_.left_ = remoteWnd.left;
			pAVSession->videochannel_.remotewnd_.height_ = remoteWnd.height;
			pAVSession->videochannel_.remotewnd_.width_ = remoteWnd.width;
			pAVSession->videochannel_.localwnd_.wnd_ = (HWND)localWnd.hWnd;
			pAVSession->videochannel_.localwnd_.top_ = localWnd.top;
			pAVSession->videochannel_.localwnd_.left_ = localWnd.left;
			pAVSession->videochannel_.localwnd_.height_ = localWnd.height;
			pAVSession->videochannel_.localwnd_.width_ = localWnd.width;

			if(!pAVSession->videochannel_.Start())
			{
				ERROR_LOG() << "Open video from audio failed.";
				DEBUG_LOG() << "--- LEAVE";
				return UCSDK_Fail;
			}

			DEBUG_LOG() << "Open video from audio success.";
			DEBUG_LOG() << "--- LEAVE";
			return UCSDK_Succ;
		}
	}
	else
	{
		pAVSession = dynamic_cast<conversation::AVSession*>(pConversation->AddSession(AudioVideo));
		if (NULL == pAVSession)
		{
			ERROR_LOG() << "Add av session failed.";
			DEBUG_LOG() << "--- LEAVE";
			return UCSDK_Fail;
		}

		//������Ƶ����
		if (Call_Video == iType)
		{
			pAVSession->videochannel_.remotewnd_.wnd_ = (HWND)remoteWnd.hWnd;
			pAVSession->videochannel_.remotewnd_.top_ = remoteWnd.top;
			pAVSession->videochannel_.remotewnd_.left_ = remoteWnd.left;
			pAVSession->videochannel_.remotewnd_.height_ = remoteWnd.height;
			pAVSession->videochannel_.remotewnd_.width_ = remoteWnd.width;
			pAVSession->videochannel_.localwnd_.wnd_ = (HWND)localWnd.hWnd;
			pAVSession->videochannel_.localwnd_.top_ = localWnd.top;
			pAVSession->videochannel_.localwnd_.left_ = localWnd.left;
			pAVSession->videochannel_.localwnd_.height_ = localWnd.height;
			pAVSession->videochannel_.localwnd_.width_ = localWnd.width;
		}
	}

	//�������
	if (!pAVSession->Connect())
	{
		pAVSession->Disconnect();
		pConversation->RemoveSession(AudioVideo);
		ERROR_LOG() << "Connect av session failed.";
		DEBUG_LOG() << "--- LEAVE";
		return UCSDK_Fail;
	}

	DEBUG_LOG() << "--- LEAVE";
	return UCSDK_Succ;
}

int UCVoIPProxy::Accept(const std::string& strConvID, int iType, const STVideoWindow& localWnd, const STVideoWindow& remoteWnd)
{
	DEBUG_LOG() << "--- ENTER";
	INFO_PARAM1(strConvID);

	//��ȡ�Ự
	uc::model::conversation::Conversation* pConversation = GetConversation(strConvID);
	if (NULL == pConversation)
	{
		ERROR_LOG() << "Get conversation failed.";
		DEBUG_LOG() << "--- LEAVE";
		return UCSDK_Fail;
	}

	//��ȡAV Session
	conversation::AVSession* pAVSession = dynamic_cast<conversation::AVSession*>(pConversation->GetSession(AudioVideo));
	if (NULL == pAVSession)
	{
		ERROR_LOG() << "Get av session failed.";
		DEBUG_LOG() << "--- LEAVE";
		return UCSDK_Fail;
	}

	//������Ƶ����
	if (Call_Video == iType)
	{
		pAVSession->videochannel_.remotewnd_.wnd_ = (HWND)remoteWnd.hWnd;
		pAVSession->videochannel_.remotewnd_.top_ = remoteWnd.top;
		pAVSession->videochannel_.remotewnd_.left_ = remoteWnd.left;
		pAVSession->videochannel_.remotewnd_.height_ = remoteWnd.height;
		pAVSession->videochannel_.remotewnd_.width_ = remoteWnd.width;
		pAVSession->videochannel_.localwnd_.wnd_ = (HWND)localWnd.hWnd;
		pAVSession->videochannel_.localwnd_.top_ = localWnd.top;
		pAVSession->videochannel_.localwnd_.left_ = localWnd.left;
		pAVSession->videochannel_.localwnd_.height_ = localWnd.height;
		pAVSession->videochannel_.localwnd_.width_ = localWnd.width;

		if(conversation::SessionConnected == pAVSession->state_)
		{
			if (!pAVSession->videochannel_.Start())
			{
				ERROR_LOG() << "accept video from audio failed.";
				DEBUG_LOG() << "--- LEAVE";
				return UCSDK_Fail;
			}

			DEBUG_LOG() << "accept video from audio success.";
			DEBUG_LOG() << "--- LEAVE";
			return UCSDK_Succ;
		}
	}
	
	//��������
	if (!pAVSession->Accept())
	{
		pAVSession->Disconnect();
		pConversation->RemoveSession(AudioVideo);
		ERROR_LOG() << "Accept av session failed";
		DEBUG_LOG() << "--- LEAVE";
		return UCSDK_Fail;
	}

	DEBUG_LOG() << "--- LEAVE";
	return UCSDK_Succ;
}

int UCVoIPProxy::Reject(const std::string& strConvID, int iType)
{
	DEBUG_LOG() << "--- ENTER";
	INFO_PARAM2(strConvID, iType);

	//��ȡ�Ự
	uc::model::conversation::Conversation* pConversation = GetConversation(strConvID);
	if (NULL == pConversation)
	{
		ERROR_LOG() << "Get conversation failed.";
		DEBUG_LOG() << "--- LEAVE";
		return UCSDK_Fail;
	}

	//��ȡAV Session
	conversation::AVSession* pAVSession = dynamic_cast<conversation::AVSession*>(pConversation->GetSession(AudioVideo));
	if (NULL == pAVSession)
	{
		ERROR_LOG() << "Get av session failed.";
		DEBUG_LOG() << "--- LEAVE";
		return UCSDK_Fail;
	}

	//�ܾ���Ƶ
	if (Call_Video == iType)
	{
		if(!pAVSession->videochannel_.Stop())
		{
			WARN_LOG() << "Reject video failed";
		}
	}

	//�ܾ�
	pAVSession->Reject();
	pConversation->RemoveSession(AudioVideo);

	DEBUG_LOG() << "--- LEAVE";
	return UCSDK_Succ;
}

int UCVoIPProxy::Hangup(const std::string& strConvID, int iType)
{
	DEBUG_LOG() << "--- ENTER";
	INFO_PARAM2(strConvID, iType);

	//��ȡ�Ự
	uc::model::conversation::Conversation* pConversation = GetConversation(strConvID);
	if (NULL == pConversation)
	{
		ERROR_LOG() << "Get conversation failed.";
		DEBUG_LOG() << "--- LEAVE";
		return UCSDK_Fail;
	}

	//��ȡAV Session
	conversation::AVSession* pAVSession = dynamic_cast<conversation::AVSession*>(pConversation->GetSession(AudioVideo));
	if (NULL == pAVSession)
	{
		ERROR_LOG() << "Get av session failed.";
		DEBUG_LOG() << "--- LEAVE";
		return UCSDK_Fail;
	}

	//ֻ�Ҷ���Ƶ
	if (Call_Video == iType)
	{
		if (!pAVSession->videochannel_.Stop())
		{
			ERROR_LOG() << "Only hangup video failed.";
			DEBUG_LOG() << "--- LEAVE";
			return UCSDK_Fail;
		}

		DEBUG_LOG() << "Only hangup video success.";
		DEBUG_LOG() << "--- LEAVE";
		return UCSDK_Succ;
	}

	//�Ҷ�
	pAVSession->Disconnect();
	pConversation->RemoveSession(AudioVideo);

	DEBUG_LOG() << "--- LEAVE";
	return UCSDK_Succ;
}

int UCVoIPProxy::Hold(const std::string& strConvID)
{
	DEBUG_LOG() << "--- ENTER";
	INFO_PARAM1(strConvID);

	//��ȡAV Session
	conversation::AVSession* pAVSession = GetAVSession(strConvID);
	if (NULL == pAVSession)
	{
		ERROR_LOG() << "pAVSession is null.";
		DEBUG_LOG() << "--- LEAVE";
		return UCSDK_Fail;
	}

	//���֣�������ʱ��᷵��ʧ�ܣ���ʵ�ʲ����ɹ����ʲ�ȡ�䷵���ж�
	(void)pAVSession->Hold();

	DEBUG_LOG() << "--- LEAVE";
	return UCSDK_Succ;
}

int UCVoIPProxy::Resume(const std::string& strConvID)
{
	DEBUG_LOG() << "--- ENTER";
	INFO_PARAM1(strConvID);

	//��ȡAV Session
	conversation::AVSession* pAVSession = GetAVSession(strConvID);
	if (NULL == pAVSession)
	{
		ERROR_LOG() << "pAVSession is null.";
		DEBUG_LOG() << "--- LEAVE";
		return UCSDK_Fail;
	}

	//�ָ���������ʱ��᷵��ʧ�ܣ���ʵ�ʲ����ɹ����ʲ�ȡ�䷵���ж�
	(void)pAVSession->Resume();

	DEBUG_LOG() << "--- LEAVE";
	return UCSDK_Succ;
}

int UCVoIPProxy::Forward(const std::string& strConvID, const std::string& strAccount)
{
	DEBUG_LOG() << "--- ENTER";
	INFO_PARAM2(strConvID, strAccount);
	
	if (strAccount.empty())
	{
		ERROR_LOG() << "Input account is empty.";
		DEBUG_LOG() << "--- LEAVE";
		return UCSDK_InvalidParam;
	}

	//��ȡAV Session
	conversation::AVSession* pAVSession = GetAVSession(strConvID);
	if (NULL == pAVSession)
	{
		ERROR_LOG() << "pAVSession is null.";
		DEBUG_LOG() << "--- LEAVE";
		return UCSDK_Fail;
	}

	//��ȡ��ϵ��
	Contact contact;
	contact.ucAcc_ = strAccount;
	UCContactMgrProxy* pUCContactMgrProxy = UCContactMgrProxy::Instance();
	if (NULL == pUCContactMgrProxy)
	{
		ERROR_LOG() << "UCContactMgrProxy's instance is null.";
		DEBUG_LOG() << "--- LEAVE";
		return UCSDK_Fail;
	}
	if (UCSDK_Succ != pUCContactMgrProxy->GetContactByAccount(contact, contact.ucAcc_))
	{
		ERROR_LOG() << "GetContactByAccount failed.";
		DEBUG_LOG() << "--- LEAVE";
		return UCSDK_InvalidParam;
	}

	if (!pAVSession->Forward(contact))
	{
		ERROR_LOG() << "Forward failed.";
		DEBUG_LOG() << "--- LEAVE";
		return UCSDK_Fail;
	}

	DEBUG_LOG() << "--- LEAVE";
	return UCSDK_Succ;
}

int UCVoIPProxy::StartRecord(const std::string& strConvID, const std::string& strFilePath)
{
	DEBUG_LOG() << "--- ENTER";
	INFO_PARAM2(strConvID, strFilePath);

	//��ȡAV Session
	conversation::AVSession* pAVSession = GetAVSession(strConvID);
	if (NULL == pAVSession)
	{
		ERROR_LOG() << "pAVSession is null.";
		DEBUG_LOG() << "--- LEAVE";
		return UCSDK_Fail;
	}

	//��ʼ¼��
	if (!pAVSession->StartRecord(strFilePath))
	{
		ERROR_LOG() << "Start record failed.";
		return UCSDK_Fail;
	}

	DEBUG_LOG() << "--- LEAVE";
	return UCSDK_Succ;
}

int UCVoIPProxy::StopRecord(const std::string& strConvID)
{
	DEBUG_LOG() << "--- ENTER";
	INFO_PARAM1(strConvID);

	//��ȡAV Session
	conversation::AVSession* pAVSession = GetAVSession(strConvID);
	if (NULL == pAVSession)
	{
		ERROR_LOG() << "pAVSession is null.";
		DEBUG_LOG() << "--- LEAVE";
		return UCSDK_Fail;
	}

	//��ʼ¼��
	if (!pAVSession->StopRecord())
	{
		ERROR_LOG() << "Stop record failed.";
		return UCSDK_Fail;
	}

	DEBUG_LOG() << "--- LEAVE";
	return UCSDK_Succ;
}

int UCVoIPProxy::Mute(const int iType)
{
	DEBUG_LOG() << "--- ENTER";
	INFO_PARAM1(iType);

	//У�����
	if (NULL == m_pDevMgr)
	{
		ERROR_LOG() << "DeviceMgr is null.";
		DEBUG_LOG() << "--- LEAVE";
		return UCSDK_NullPoint;
	}

	//��˷羲��
	if (Dev_Mic == iType)
	{
		if (NULL == m_pDevMgr->activemicdev)
		{
			ERROR_LOG() << "Activemicdev is null.";
			DEBUG_LOG() << "--- LEAVE";
			return UCSDK_NullPoint;
		}

		if (!m_pDevMgr->activemicdev->Mute())
		{
			ERROR_LOG() << "Mute the mic device failed.";
			DEBUG_LOG() << "--- LEAVE";
			return UCSDK_Fail;
		}
	}
	//����������
	else if (Dev_Speaker == iType)
	{
		if (NULL == m_pDevMgr->activespkerdev)
		{
			ERROR_LOG() << "Activespkerdev is null.";
			DEBUG_LOG() << "--- LEAVE";
			return UCSDK_NullPoint;
		}

		if (!m_pDevMgr->activespkerdev->Mute())
		{
			ERROR_LOG() << "Mute the speaker device failed.";
			DEBUG_LOG() << "--- LEAVE";
			return UCSDK_Fail;
		}
	}
	//�����豸����
	else
	{
		ERROR_LOG() << "Invalid device type.";
		DEBUG_LOG() << "--- LEAVE";
		return UCSDK_InvalidParam;
	}

	DEBUG_LOG() << "--- LEAVE";
	return UCSDK_Succ;
}

int UCVoIPProxy::UnMute(const int iType)
{
	DEBUG_LOG() << "--- ENTER";
	INFO_PARAM1(iType);

	//У�����
	if (NULL == m_pDevMgr)
	{
		ERROR_LOG() << "DeviceMgr is null.";
		DEBUG_LOG() << "--- LEAVE";
		return UCSDK_NullPoint;
	}

	//��˷�ȡ������
	if (Dev_Mic == iType)
	{
		if (NULL == m_pDevMgr->activemicdev)
		{
			ERROR_LOG() << "Activemicdev is null.";
			DEBUG_LOG() << "--- LEAVE";
			return UCSDK_NullPoint;
		}

		if (!m_pDevMgr->activemicdev->UnMute())
		{
			ERROR_LOG() << "UnMute the mic device failed.";
			DEBUG_LOG() << "--- LEAVE";
			return UCSDK_Fail;
		}
	}
	//������ȡ������
	else if (Dev_Speaker == iType)
	{
		if (NULL == m_pDevMgr->activespkerdev)
		{
			ERROR_LOG() << "Activespkerdev is null.";
			DEBUG_LOG() << "--- LEAVE";
			return UCSDK_NullPoint;
		}

		if (!m_pDevMgr->activespkerdev->UnMute())
		{
			ERROR_LOG() << "UnMute the speaker device failed.";
			DEBUG_LOG() << "--- LEAVE";
			return UCSDK_Fail;
		}
	}
	//�����豸����
	else
	{
		ERROR_LOG() << "Invalid device type.";
		DEBUG_LOG() << "--- LEAVE";
		return UCSDK_InvalidParam;
	}

	DEBUG_LOG() << "--- LEAVE";
	return UCSDK_Succ;
}

uc::model::conversation::Conversation* UCVoIPProxy::GetConversation(const std::string& strConvID)
{
	DEBUG_LOG() << "--- ENTER";
	INFO_PARAM1(strConvID);

	uc::model::conversation::Conversation* pConversation = NULL;

	//У�����
	if (strConvID.empty())
	{
		ERROR_LOG() << "strConvID is empty.";
		DEBUG_LOG() << "--- LEAVE";
		return pConversation;
	}
	if(NULL == m_pConvManager)
	{
		ERROR_LOG() << "ConvManager is null.";
		DEBUG_LOG() << "--- LEAVE";
		return pConversation;
	}

	//��ȡ�Ự
	pConversation = m_pConvManager->GetConversation(strConvID);
	if (NULL == pConversation)
	{
		ERROR_LOG() << "Get conversation failed.";
	}

	DEBUG_LOG() << "--- LEAVE";
	return pConversation;
}

uc::model::conversation::AVSession* UCVoIPProxy::GetAVSession(const std::string& strConvID)
{
	DEBUG_LOG() << "--- ENTER";
	INFO_PARAM1(strConvID);

	uc::model::conversation::AVSession* pAVSession = NULL;
	//��ȡ�Ự
	uc::model::conversation::Conversation* pConversation = GetConversation(strConvID);
	if (NULL == pConversation)
	{
		ERROR_LOG() << "Get conversation failed.";
		DEBUG_LOG() << "--- LEAVE";
		return pAVSession;
	}

	//��ȡAV Session
	pAVSession = dynamic_cast<conversation::AVSession*>(pConversation->GetSession(AudioVideo));
	if (NULL == pAVSession)
	{
		ERROR_LOG() << "Get av session failed.";
	}

	DEBUG_LOG() << "--- LEAVE";
	return pAVSession;
}

}
}
