#include "stdafx.h"
#include "UCPublicProxy.h"
#include "eSDKLog.h"


namespace eSDK {
	namespace UC {


UCPublicAbsProxy::UCPublicAbsProxy()
{

}

UCPublicAbsProxy::~UCPublicAbsProxy()
{

}

UCPublicAbsProxy* UCPublicAbsProxy::GetInstance()
{
	return dynamic_cast<UCPublicAbsProxy*>(UCPublicProxy::Instance());
}

void UCPublicAbsProxy::ReleaseInstance()
{
	UCPublicProxy::Destroy();
}

//////////////////////////////////////////////////////////////////////////
UCPublicProxy* UCPublicProxy::m_pUCPublicProxy = NULL;

UCPublicProxy::UCPublicProxy()
	: m_pUCClient(NULL)
{

}

UCPublicProxy::~UCPublicProxy()
{
	m_pUCClient = NULL;
}

UCPublicProxy* UCPublicProxy::Instance()
{
	if (NULL == m_pUCPublicProxy)
	{
		m_pUCPublicProxy = new UCPublicProxy;
	}

	return m_pUCPublicProxy;
}

void UCPublicProxy::Destroy()
{
	if (NULL != m_pUCPublicProxy)
	{
		delete m_pUCPublicProxy;
		m_pUCPublicProxy = NULL;
	}
}

int UCPublicProxy::Init()
{
	DEBUG_LOG() << "--- ENTER";

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

int UCPublicProxy::UnInit()
{
	DEBUG_LOG() << "--- ENTER";

	m_pUCClient = NULL;

	DEBUG_LOG() << "--- LEAVE";
	return UCSDK_Succ;
}

int UCPublicProxy::PublishSelfInformation(const PublishInfoMap& publishInfoMap)
{
	DEBUG_LOG() << "--- ENTER";

	if (NULL == m_pUCClient)
	{
		ERROR_LOG() << "m_pUCClient is null.";
		DEBUG_LOG() << "--- LEAVE";
		return UCSDK_NullPoint;
	}

	if (NULL == m_pUCClient->Self)
	{
		ERROR_LOG() << "m_pUCClient->Self is null.";
		DEBUG_LOG() << "--- LEAVE";
		return UCSDK_NullPoint;
	}

	if (publishInfoMap.empty())
	{
		ERROR_LOG() << "Input pubInfoMap is empty.";
		DEBUG_LOG() << "--- LEAVE";
		return UCSDK_InvalidParam;
	}

	std::map<uc::model::UCSelf::PubContactInfoType, std::string> _values;
	PublishInfoMap::const_iterator itor_b = publishInfoMap.begin();
	PublishInfoMap::const_iterator itor_e = publishInfoMap.end();
	for (; itor_b != itor_e; itor_b++)
	{
		uc::model::UCSelf::PubContactInfoType eType = (uc::model::UCSelf::PubContactInfoType)itor_b->first;
		const std::string& info = itor_b->second;
		(void)_values.insert(std::make_pair(eType, info));
	}

	if (!m_pUCClient->Self->PublishSelfInformation(_values))
	{
		ERROR_LOG() << "Publish self infomation failed.";
		DEBUG_LOG() << "--- LEAVE";
		return UCSDK_Fail;
	}

	DEBUG_LOG() << "--- LEAVE";
	return UCSDK_Succ;
}

int UCPublicProxy::GetContactStatus(const std::string& _uri, int& _status)
{
	DEBUG_LOG() << "--- ENTER";
	INFO_PARAM1(_uri);
	
	if (_uri.empty())
	{
		ERROR_LOG() << "_uri is empty.";
		DEBUG_LOG() << "--- LEAVE";
		return UCSDK_InvalidParam;
	}

	if (NULL == m_pUCClient)
	{
		ERROR_LOG() << "m_pUCClient is null.";
		DEBUG_LOG() << "--- LEAVE";
		return UCSDK_NullPoint;
	}

	if (NULL == m_pUCClient->ContactSubManager)
	{
		ERROR_LOG() << "m_pUCClient->ContactSubManager is null.";
		DEBUG_LOG() << "--- LEAVE";
		return UCSDK_NullPoint;
	}

	_status = m_pUCClient->ContactSubManager->GetContactStatus(_uri);
	INFO_PARAM1(_status);

	DEBUG_LOG() << "--- LEAVE";
	return UCSDK_Succ;
}

}
}
