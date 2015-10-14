#include "stdafx.h"
#include "UCIMProxy.h"
#include "eSDKLog.h"
#include "UCContactMgrProxy.h"


namespace eSDK {
	namespace UC {


UCIMAbsProxy::UCIMAbsProxy()
{

}

UCIMAbsProxy::~UCIMAbsProxy()
{

}

UCIMAbsProxy* UCIMAbsProxy::GetInstance()
{
	return dynamic_cast<UCIMAbsProxy*>(UCIMProxy::Instance());
}

void UCIMAbsProxy::ReleaseInstance()
{
	UCIMProxy::Destroy();
}

//////////////////////////////////////////////////////////////////////////
UCIMProxy* UCIMProxy::m_pUCIMProxy = NULL;

UCIMProxy::UCIMProxy()
	:m_pUCClient(NULL)
{

}

UCIMProxy::~UCIMProxy()
{
	m_pUCClient = NULL;
}

UCIMProxy* UCIMProxy::Instance()
{
	if (NULL == m_pUCIMProxy)
	{
		m_pUCIMProxy = new UCIMProxy;
	}

	return m_pUCIMProxy;
}

void UCIMProxy::Destroy()
{
	if (NULL != m_pUCIMProxy)
	{
		delete m_pUCIMProxy;
		m_pUCIMProxy = NULL;
	}
}

int UCIMProxy::Init()
{
	DEBUG_LOG() << "--- ENTRY";
	m_pUCClient = UCClient::GetClient();
	if (NULL == m_pUCClient)
	{
		ERROR_LOG() << "Get UCClient failed.";
		DEBUG_LOG() << "--- LEAVE";
		return UCSDK_NullPoint;
	}

	DEBUG_LOG() << "--- LEAVE";
	return UCSDK_Succ;
}

int UCIMProxy::UnInit()
{
	DEBUG_LOG() << "--- ENTER";

	m_pUCClient = NULL;

	DEBUG_LOG() << "--- LEAVE";
	return UCSDK_Succ;
}

int UCIMProxy::SendIMMessage(const std::string& strIMMsg, const AccountList& accountList, std::string &conversationID)
{
	DEBUG_LOG() << "--- ENTRY";
	INFO_PARAM2(strIMMsg, conversationID);

	conversation::InstantMsgSession* pInSession = NULL;
	int iRet = GetIMSessionByConversationID(accountList, conversationID, &pInSession);
	if (UCSDK_Succ != iRet)
	{
		ERROR_LOG() << "GetIMSessionByConversationID fail";
		return UCSDK_Fail;
	}

	if (NULL == pInSession)
	{
		ERROR_LOG() << "pInSession is NULL";
		return UCSDK_NullPoint;
	}

	if (strIMMsg.empty())
	{
		DEBUG_LOG() << "Empty message";
		return UCSDK_Succ;
	}

	//·¢ËÍÏûÏ¢
	if (!(pInSession->SendMessage(strIMMsg)))
	{
		ERROR_LOG() << "Send message fail!!!";
		return UCSDK_Fail;
	}
	
	DEBUG_LOG()<< "Send message success";
	DEBUG_LOG() << "--- LEAVE";	
	return UCSDK_Succ;
}

int UCIMProxy::CloseConversation(const std::string &conversationID)
{
	DEBUG_LOG() << "--- ENTRY";
	INFO_PARAM1(conversationID);

	if(conversationID.empty())
	{
		ERROR_LOG() << "conversationID is null";
		return UCSDK_InvalidParam;
	}
	
	if (NULL == m_pUCClient)
	{
		ERROR_LOG() << "No UCClient";
		return UCSDK_Fail;
	}

	conversation::ConversationMgr* pConvMgr = m_pUCClient->ConvManager;
	if (NULL == pConvMgr)
	{
		ERROR_LOG() << "No ConvManager";
		return UCSDK_Fail;
	}

	if (!(pConvMgr->RemoveConversation(conversationID)))
	{
		ERROR_LOG() << "Remove conversation fail!!!";
		return UCSDK_Fail;
	}

	DEBUG_LOG()<< "Remove conversation success";
	DEBUG_LOG() << "--- LEAVE";	
	return UCSDK_Succ;
}

int UCIMProxy::AcceptFile(const std::string& /*strFileID*/, const std::string& /*strFilePath*/)
{
	return 0;
}

int UCIMProxy::CancelFile(const std::string& /*strFileID*/)
{
	return 0;
}

int UCIMProxy::RejectFile(const std::string& /*strFileID*/)
{
	return 0;
}

std::string UCIMProxy::TransferFile(const std::string& /*strAccout*/, 
	const std::string& /*strFilePath*/, const std::string& /*strTransType*/, bool /*bIsOfflineFile*/)
{
	return "";
}

int UCIMProxy::GetIMSessionByConversationID(const AccountList& accountList, std::string &conversationID, conversation::InstantMsgSession** ppIMSession) const
{
	if (NULL == m_pUCClient)
	{
		ERROR_LOG() << "No UCClient";
		*ppIMSession = NULL;
		return UCSDK_Fail;
	}

	conversation::ConversationMgr* pConvMgr = m_pUCClient->ConvManager;
	if (NULL == pConvMgr)
	{
		ERROR_LOG() << "No ConvManager";
		*ppIMSession = NULL;
		return UCSDK_Fail;
	}

	conversation::Conversation* pConversation = NULL;
	conversation::Session* pSession = NULL;	
	if (!conversationID.empty())
	{
		pConversation = pConvMgr->GetConversation(conversationID);
		if (NULL == pConversation)
		{
			ERROR_LOG() << "Get Conversation fail";
			*ppIMSession = NULL;
			return UCSDK_Fail;
		}

		pSession = pConversation->GetSession(InstantMessage);
		if (NULL == pSession)
		{
			pSession = pConversation->AddSession(InstantMessage);
			if (NULL == pSession)
			{
				ERROR_LOG() << "Get session fail";
				*ppIMSession = NULL;
				return UCSDK_Fail;
			}	
		}	
	}
	else
	{		
		pConversation = pConvMgr->AddConversation();
		if (NULL == pConversation)
		{
			ERROR_LOG() << "Add conversation fail";
			*ppIMSession = NULL;
			return UCSDK_Fail;
		}

		pSession = pConversation->AddSession(InstantMessage);
		if (NULL == pSession)
		{
			ERROR_LOG() << "Add IM session fail";
			pConversation->End();
			*ppIMSession = NULL;
			return UCSDK_Fail;
		}

		UCContactMgrProxy* pUCContactMgrProxy = UCContactMgrProxy::Instance();
		if (NULL == pUCContactMgrProxy)
		{
			ERROR_LOG() << "Get UCContactMgrProxy instance failed.";
			pSession->Disconnect();
			pConversation->End();
			*ppIMSession = NULL;
			return UCSDK_Fail;
		}
		AccountList::const_iterator iter = accountList.begin();
		AccountList::const_iterator itEnd = accountList.end();
		for (; iter != itEnd; iter++)
		{
			Contact member;

			if (UCSDK_Succ != pUCContactMgrProxy->GetContactByAccount(member, (*iter)))
			{
				ERROR_LOG() << "GetContactByAccount fail, account = " << (*iter);
				pSession->Disconnect();
				pConversation->End();
				*ppIMSession = NULL;
				return UCSDK_Fail;
			}

			if (!pConversation->AddParticipant(member))
			{
				ERROR_LOG() << "AddParticipant fail, account = " << (*iter);
				pSession->Disconnect();
				pConversation->End();
				*ppIMSession = NULL;
				return UCSDK_Fail;
			}
		}

		conversationID = pConversation->propmap_[conversation::ConvIdentifier];		
	}

	*ppIMSession = dynamic_cast<conversation::InstantMsgSession*>(pSession);

	return UCSDK_Succ;
}

}
}
