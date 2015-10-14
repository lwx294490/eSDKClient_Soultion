#include "stdafx.h"
#include "UCMeetingProxy.h"
#include "UCContactMgrProxy.h"
#include "UCSDK.h"
#include "eSDKLog.h"


namespace eSDK {
	namespace UC {


UCMeetingAbsProxy::UCMeetingAbsProxy()
{

}

UCMeetingAbsProxy::~UCMeetingAbsProxy()
{

}

UCMeetingAbsProxy* UCMeetingAbsProxy::GetInstance()
{
	return dynamic_cast<UCMeetingAbsProxy*>(UCMeetingProxy::Instance());
}

void UCMeetingAbsProxy::ReleaseInstance()
{
	UCMeetingProxy::Destroy();
}

//////////////////////////////////////////////////////////////////////////
UCMeetingProxy* UCMeetingProxy::m_pUCMeetingProxy = NULL;

UCMeetingProxy::UCMeetingProxy()
	: m_pUCClient(NULL)
	, m_pConvManager(NULL)
{

}

UCMeetingProxy::~UCMeetingProxy()
{
	m_pUCClient = NULL;
	m_pConvManager = NULL;
}

UCMeetingProxy* UCMeetingProxy::Instance()
{
	if (NULL == m_pUCMeetingProxy)
	{
		m_pUCMeetingProxy = new UCMeetingProxy;
	}
	
	return m_pUCMeetingProxy;
}

void UCMeetingProxy::Destroy()
{
	if (NULL != m_pUCMeetingProxy)
	{
		delete m_pUCMeetingProxy;
		m_pUCMeetingProxy = NULL;
	}
}

int UCMeetingProxy::Init()
{
	DEBUG_LOG() << "--- ENTER";

	m_pUCClient = UCClient::GetClient();
	if(NULL == m_pUCClient)
	{
		ERROR_LOG() << "Get UCClient failed.";
		DEBUG_LOG() << "--- LEAVE";
		return UCSDK_NullPoint;
	}

	m_pConvManager = m_pUCClient->ConvManager;
	if (NULL == m_pConvManager)
	{
		ERROR_LOG() << "ConvManager is null.";
		DEBUG_LOG() << "--- LEAVE";
		return UCSDK_NullPoint;
	}

	DEBUG_LOG() << "--- LEAVE";
	return UCSDK_Succ;
}

int UCMeetingProxy::UnInit()
{
	DEBUG_LOG() << "--- ENTER";

	m_pUCClient = NULL;
	m_pConvManager = NULL;

	DEBUG_LOG() << "--- LEAVE";
	return UCSDK_Succ;
}

int UCMeetingProxy::MakeMeetingGroup(const UCSDKContactList& memberlist, std::string& convId)
{
	DEBUG_LOG() << "--- ENTER";

	//校验参数
	if (!convId.empty())
	{
		ERROR_LOG() << "Meeting is exist.";
		DEBUG_LOG() << "--- LEAVE";
		return UCSDK_InvalidParam;
	}
	if (memberlist.empty())
	{
		ERROR_LOG() << "member list is empty.";
		DEBUG_LOG() << "--- LEAVE";
		return UCSDK_InvalidParam;
	}
	if (NULL == m_pConvManager)
	{
		ERROR_LOG() << "m_pConvManager is null.";
		DEBUG_LOG() << "--- LEAVE";
		return UCSDK_NullPoint;
	}

	//增加conversation
	uc::model::conversation::Conversation* pConversation = m_pConvManager->AddConversation();
	if (NULL == pConversation)
	{
		ERROR_LOG() << "Add conversation failed.";
		DEBUG_LOG() << "--- LEAVE";
		return UCSDK_Fail;
	}

	convId = pConversation->propmap_[uc::model::conversation::ConvIdentifier];

	//增加conversation的参数，这里指定参数ConvSubject为“TempGroup”
	pConversation->propmap_[uc::model::conversation::ConvSubject] = "TempGroup";

	//遍历增加成员
	UCContactMgrProxy* pUCContactMgrProxy = UCContactMgrProxy::Instance();
	if (NULL == pUCContactMgrProxy)
	{
		m_pConvManager->RemoveConversation(convId);
		convId.clear();
		ERROR_LOG() << "Get UCContactMgrProxy instance failed.";
		DEBUG_LOG() << "--- LEAVE";		
		return UCSDK_NullPoint;
	}
	UCSDKContactList::const_iterator itor_begin = memberlist.begin();
	UCSDKContactList::const_iterator itor_end = memberlist.end();
	for (; itor_begin != itor_end; itor_begin++)
	{
		Contact contact;
		if (!pUCContactMgrProxy->GetContactByUCSDKContact(*itor_begin, contact))
		{
			m_pConvManager->RemoveConversation(convId);
			convId.clear();
			ERROR_LOG() << "Get contact by uccontact failed.";
			DEBUG_LOG() << "--- LEAVE";
			return UCSDK_Fail;
		}

		if (!pConversation->AddParticipant(contact))
		{
			m_pConvManager->RemoveConversation(convId);
			convId.clear();
			ERROR_LOG() << "AddParticipant failed.";
			DEBUG_LOG() << "--- LEAVE";
			return UCSDK_Fail;
		}
	}

	conversation::InstantMsgSession* pIMSess = dynamic_cast<conversation::InstantMsgSession*>(pConversation->AddSession(InstantMessage));
	if (NULL == pIMSess)
	{
		m_pConvManager->RemoveConversation(convId);
		convId.clear();
		ERROR_LOG() << "Add im session failed.";
		DEBUG_LOG() << "--- LEAVE";
		return UCSDK_Fail;
	}

	if (!pIMSess->Connect())
	{
		pConversation->RemoveSession(InstantMessage);
		m_pConvManager->RemoveConversation(convId);
		convId.clear();
		ERROR_LOG() << "IM connect failed.";
		DEBUG_LOG() << "--- LEAVE";
		return UCSDK_Fail;
	}

	//关联信号
#ifdef ESDKCLIENT_PLATFORM_DEPEND
	UCSDK* pUCSDK = UCSDK::CreateInstance();
#else
	UCSDK* pUCSDK = UCSDK::Instance();
#endif
	if (NULL == pUCSDK)
	{
		pConversation->RemoveSession(InstantMessage);
		m_pConvManager->RemoveConversation(convId);
		convId.clear();
		ERROR_LOG() << "Get UCSDK's instance failed.";
		DEBUG_LOG() << "--- LEAVE";
		return UCSDK_Fail;
	}
	(void)pUCSDK->ConnectConference(pConversation);

	DEBUG_LOG() << "--- LEAVE";
	return UCSDK_Succ;
}

int UCMeetingProxy::StartMeeting(const std::string& convId)
{
	DEBUG_LOG() << "--- ENTER";
	INFO_PARAM1(convId);

	//校验参数
	if (convId.empty())
	{
		ERROR_LOG() << "Meeting is not exist.";
		DEBUG_LOG() << "--- LEAVE";
		return UCSDK_InvalidParam;
	}
	if (NULL == m_pConvManager)
	{
		ERROR_LOG() << "m_pConvManager is null.";
		DEBUG_LOG() << "--- LEAVE";
		return UCSDK_NullPoint;
	}

	uc::model::conversation::Conversation* pConversation = m_pConvManager->GetConversation(convId);
	if (NULL == pConversation)
	{
		ERROR_LOG() << "Get conversation by convId failed.";
		DEBUG_LOG() << "--- LEAVE";
		return UCSDK_Fail;
	}

	if (pConversation->HasSession(AudioVideo))
	{
		ERROR_LOG() << "Meeting is started.";
		DEBUG_LOG() << "--- LEAVE";
		return UCSDK_Fail;
	}

	conversation::AVSession* pAVSess = dynamic_cast<conversation::AVSession*>(pConversation->AddSession(AudioVideo));
	if (NULL == pAVSess)
	{
		ERROR_LOG() << "Add av session failed.";
		DEBUG_LOG() << "--- LEAVE";
		return UCSDK_Fail;
	}

	if (!pAVSess->Connect())
	{
		pConversation->RemoveSession(AudioVideo);
		ERROR_LOG() << "AV session connect failed.";
		DEBUG_LOG() << "--- LEAVE";
		return UCSDK_Fail;
	}

	DEBUG_LOG() << "--- LEAVE";
	return UCSDK_Succ;
}

int UCMeetingProxy::AcceptMeeting(const std::string& convId)
{
	DEBUG_LOG() << "--- ENTER";
	INFO_PARAM1(convId);

	//校验参数
	if (convId.empty())
	{
		ERROR_LOG() << "Meeting is not exist.";
		DEBUG_LOG() << "--- LEAVE";
		return UCSDK_InvalidParam;
	}
	if (NULL == m_pConvManager)
	{
		ERROR_LOG() << "m_pConvManager is null.";
		DEBUG_LOG() << "--- LEAVE";
		return UCSDK_NullPoint;
	}

	uc::model::conversation::Conversation* pConversation = m_pConvManager->GetConversation(convId);
	if (NULL == pConversation)
	{
		ERROR_LOG() << "Get conversation by convId failed.";
		DEBUG_LOG() << "--- LEAVE";
		return UCSDK_Fail;
	}

	//获取AVsession
	uc::model::conversation::AVSession* pAVSession = GetAVSession(pConversation);
	if (NULL == pAVSession)
	{
		ERROR_LOG() << "Get av session failed.";
		DEBUG_LOG() << "--- LEAVE";
		return UCSDK_Fail;
	}

	if (!pAVSession->Accept())
	{
		ERROR_LOG() << "Accept av session failed.";
		DEBUG_LOG() << "--- LEAVE";
		return UCSDK_Fail;
	}

	//关联信号
#ifdef ESDKCLIENT_PLATFORM_DEPEND
	UCSDK* pUCSDK = UCSDK::CreateInstance();
#else
	UCSDK* pUCSDK = UCSDK::Instance();
#endif
	if (NULL == pUCSDK)
	{
		ERROR_LOG() << "Get UCSDK's instance failed.";
		DEBUG_LOG() << "--- LEAVE";
		return UCSDK_Fail;
	}
	(void)pUCSDK->ConnectConference(pConversation);

	DEBUG_LOG() << "--- LEAVE";
	return UCSDK_Succ;
}

int UCMeetingProxy::AddParticipant(const UCSDKContact& member, const std::string& convId)
{
	DEBUG_LOG() << "--- ENTER";
	INFO_PARAM2(member.uri_,convId);

	//校验参数
	if (convId.empty())
	{
		ERROR_LOG() << "Not have conference. can't add participant.";
		DEBUG_LOG() << "--- LEAVE";
		return UCSDK_InvalidParam;
	}

	if (NULL == m_pConvManager)
	{
		ERROR_LOG() << "m_pConvManager is null.";
		DEBUG_LOG() << "--- LEAVE";
		return UCSDK_NullPoint;
	}

	uc::model::conversation::Conversation* pConversation =  m_pConvManager->GetConversation(convId);
	if (NULL == pConversation)
	{
		ERROR_LOG() << "Get conversation by convId failed.";
		DEBUG_LOG() << "--- LEAVE";
		return UCSDK_Fail;
	}

	InstantMsgSession* pIMSess = dynamic_cast<conversation::InstantMsgSession*>(pConversation->GetSession(InstantMessage));
	if(NULL == pIMSess)
	{
		pIMSess = dynamic_cast<conversation::InstantMsgSession*>(pConversation->AddSession(InstantMessage));
	}
	if(NULL == pIMSess)
	{
		ERROR_LOG() << "pIMSess is null.";
		DEBUG_LOG() << "--- LEAVE";
		return UCSDK_Fail;
	}

	if(SessionDisconnected == pIMSess->state_)
	{
		pConversation->propmap_[conversation::ConvSubject] = "TempGroup";
		if(!pIMSess->Connect())
		{
			WARN_LOG() << "IMSession connect failed.";
		}
	}

	//查找联系人
	Contact contact;
	int iRet = FindContact(contact, member);
	if (UCSDK_Succ != iRet)
	{
		ERROR_LOG() << "Find contact failed.";
		DEBUG_LOG() << "--- LEAVE";
		return iRet;
	}
	if (!pConversation->AddParticipant(contact))
	{
		ERROR_LOG() << "AddParticipant failed.";
		DEBUG_LOG() << "--- LEAVE";
		return UCSDK_Fail;
	}

	//关联信号
#ifdef ESDKCLIENT_PLATFORM_DEPEND
	UCSDK* pUCSDK = UCSDK::CreateInstance();
#else
	UCSDK* pUCSDK = UCSDK::Instance();
#endif
	if (NULL == pUCSDK)
	{
		ERROR_LOG() << "Get UCSDK's instance failed.";
		DEBUG_LOG() << "--- LEAVE";
		return UCSDK_Fail;
	}
	(void)pUCSDK->ConnectConference(pConversation);

	DEBUG_LOG() << "--- LEAVE";
	return UCSDK_Succ;
}

int UCMeetingProxy::ConnectParticipant(const UCSDKContact& member, const std::string& convId)
{
	DEBUG_LOG() << "--- ENTER";
	INFO_PARAM2(member.uri_, convId);

	//获取AVsession
	uc::model::conversation::AVSession* pAVSession = GetAVSession(convId);
	if (NULL == pAVSession)
	{
		ERROR_LOG() << "Get av session failed.";
		DEBUG_LOG() << "--- LEAVE";
		return UCSDK_Fail;
	}

	//查找联系人
	Contact contact;
	int iRet = FindContact(contact, member);
	if (UCSDK_Succ != iRet)
	{
		ERROR_LOG() << "Find contact failed.";
		DEBUG_LOG() << "--- LEAVE";
		return iRet;
	}

	uc::model::conversation::Participant part_;
	CopyContactToContact(contact, part_.contact_);

	//重新邀请与会人
	if (!pAVSession->ConnectParticipant(part_))
	{
		ERROR_LOG() << "Connect participant failed.";
		DEBUG_LOG() << "--- LEAVE";
		return UCSDK_Fail;
	}

	DEBUG_LOG() << "--- LEAVE";
	return UCSDK_Succ;
}

int UCMeetingProxy::RemoveParticipant(const UCSDKContact& member, const std::string& convId)
{
	DEBUG_LOG() << "--- ENTER";
	INFO_PARAM2(member.uri_, convId);

	//获取conversation
	uc::model::conversation::Conversation* pConversation = GetConversation(convId);
	if (NULL == pConversation)
	{
		ERROR_LOG() << "Get conversation failed.";
		DEBUG_LOG() << "--- LEAVE";
		return UCSDK_Fail;
	}

	//查找联系人
	Contact contact;
	int iRet = FindContact(contact, member);
	if (UCSDK_Succ != iRet)
	{
		ERROR_LOG() << "Find contact failed.";
		DEBUG_LOG() << "--- LEAVE";
		return iRet;
	}

	//删除与会人
	if (!pConversation->RemoveParticipant(contact))
	{
		ERROR_LOG() << "Remove participant failed.";
		DEBUG_LOG() << "--- LEAVE";
		return UCSDK_Fail;
	}

	DEBUG_LOG() << "--- LEAVE";
	return UCSDK_Succ;
}

int UCMeetingProxy::KickParticipant(const UCSDKContact& member, const std::string& convId)
{
	DEBUG_LOG() << "--- ENTER";
	INFO_PARAM2(member.uri_, convId);

	//获取AVsession
	uc::model::conversation::AVSession* pAVSession = GetAVSession(convId);
	if (NULL == pAVSession)
	{
		ERROR_LOG() << "Get av session failed.";
		DEBUG_LOG() << "--- LEAVE";
		return UCSDK_Fail;
	}

	//查找联系人
	Contact contact;
	int iRet = FindContact(contact, member);
	if (UCSDK_Succ != iRet)
	{
		ERROR_LOG() << "Find contact failed.";
		DEBUG_LOG() << "--- LEAVE";
		return iRet;
	}

	uc::model::conversation::Participant part_;
	CopyContactToContact(contact, part_.contact_);

	//重新邀请与会人
	if (!pAVSession->KickParticipant(part_))
	{
		ERROR_LOG() << "Kick participant failed.";
		DEBUG_LOG() << "--- LEAVE";
		return UCSDK_Fail;
	}

	DEBUG_LOG() << "--- LEAVE";
	return UCSDK_Succ;
}

int UCMeetingProxy::GetBookConfList(UCSDKBookConfList& bookConfList)
{
	DEBUG_LOG() << "--- ENTER";

	if (NULL == m_pConvManager)
	{
		ERROR_LOG() << "m_pConvManager is null.";
		DEBUG_LOG() << "--- LEAVE";
		return UCSDK_NullPoint;
	}
	if (NULL == m_pUCClient)
	{
		ERROR_LOG() << "m_pUCClient is null.";
		DEBUG_LOG() << "--- LEAVE";
		return UCSDK_NullPoint;
	}

	if (NULL == m_pUCClient->Self)
	{
		ERROR_LOG() << "UCSelf is null.";
		DEBUG_LOG() << "--- LEAVE";
		return UCSDK_NullPoint;
	}

	//设置出参
	bookConfList.clear();
	std::vector<uc::model::UCBookConfInfo> conflist_;
	m_pUCClient->Self->GetBookConfList(conflist_);

	std::vector<uc::model::UCBookConfInfo>::iterator itor_begin = conflist_.begin();
	std::vector<uc::model::UCBookConfInfo>::iterator itor_end = conflist_.end();
	for (; itor_begin != itor_end; itor_begin++)
	{
		UCSDKBookConfInfo bookConfInfo;
		bookConfInfo.topic			= itor_begin->topic;
		bookConfInfo.meetingtime	= itor_begin->meetingtime;
		bookConfInfo.convener		= itor_begin->convener;
		bookConfInfo.convenername	= itor_begin->convenername;
		bookConfInfo.attendeelist	= itor_begin->attendeelist;	//vector 自己实现
		bookConfInfo.accessnum		= itor_begin->accessnum;
		bookConfInfo.securitycode	= itor_begin->securitycode;
		bookConfInfo.iscycle		= itor_begin->iscycle;
		bookConfInfo.startdate		= itor_begin->startdate;
		bookConfInfo.validityperiod	= itor_begin->validityperiod;
		bookConfInfo.content		= itor_begin->content;
		bookConfInfo.chairmanpwd	= itor_begin->chairmanpwd;
		bookConfInfo.partmanpwd		= itor_begin->partmanpwd;
		bookConfInfo.recordcode		= itor_begin->recordcode;
		bookConfInfo.funcbits		= itor_begin->funcbits;
		bookConfInfo.mediaBits		= itor_begin->mediaBits;
		bookConfInfo.confType		= itor_begin->confType;
		bookConfInfo.confid			= itor_begin->confid;
		bookConfInfo.confStyle		= itor_begin->confStyle;

		bookConfList.push_back(bookConfInfo);
	}

	DEBUG_LOG() << "--- LEAVE";
	return UCSDK_Succ;
}

int UCMeetingProxy::JoinMeeting(std::string& convId, const UCSDKBookConfInfo& meetingInfo)
{
	DEBUG_LOG() << "--- ENTER";
	INFO_PARAM2(convId, meetingInfo.confid);

	if (NULL == m_pConvManager)
	{
		ERROR_LOG() << "m_pConvManager is null.";
		DEBUG_LOG() << "--- LEAVE";
		return UCSDK_NullPoint;
	}
	if (NULL == m_pUCClient)
	{
		ERROR_LOG() << "m_pUCClient is null.";
		DEBUG_LOG() << "--- LEAVE";
		return UCSDK_NullPoint;
	}

	uc::model::conversation::Conversation* pConversation = NULL;
	if (!convId.empty())
	{
		pConversation = m_pConvManager->GetConversation(convId);
	}

	if (NULL == pConversation)
	{
		pConversation = m_pConvManager->AddConversation();
		if (NULL == pConversation)
		{
			ERROR_LOG() << "Add conversation failed.";
			DEBUG_LOG() << "--- LEAVE";
			return UCSDK_Fail;
		}
		std::string CallNum("conf");
		CallNum.append(meetingInfo.accessnum);
		CallNum.append("*");
		CallNum.append(meetingInfo.securitycode);

		Contact contact;
		contact.mobile_ = CallNum;
		contact.name_ = meetingInfo.topic;
		
		//增加预定义会议组装成的成员对象
		if (!pConversation->AddParticipant(contact))
		{			
			pConversation->RemoveSession(uc::model::AudioVideo);
			ERROR_LOG() << "Add conference participant failed.";
			DEBUG_LOG() << "--- LEAVE";
			return UCSDK_Fail;
		}
		//增加自己
		if (NULL == m_pUCClient->Self)
		{
			pConversation->RemoveSession(uc::model::AudioVideo);
			ERROR_LOG() << "UCSelf is null.";
			DEBUG_LOG() << "--- LEAVE";
			return UCSDK_Fail;
		}
		if (!pConversation->AddParticipant(m_pUCClient->Self->selfInfo))
		{
			pConversation->RemoveSession(uc::model::AudioVideo);
			ERROR_LOG() << "Add myself failed.";
			DEBUG_LOG() << "--- LEAVE";
			return UCSDK_Fail;
		}
		//保存会话ID
		convId = pConversation->propmap_[ConvIdentifier];
		if (convId.empty())
		{
			pConversation->RemoveSession(uc::model::AudioVideo);
			pConversation->End();
			ERROR_LOG() << "Conversation is empty.";
			DEBUG_LOG() << "--- LEAVE";
			return UCSDK_Fail;
		}
	}

	//获取AVsession
	uc::model::conversation::AVSession* pAVSession = dynamic_cast<uc::model::conversation::AVSession*>(pConversation->AddSession(uc::model::AudioVideo));
	if (NULL == pAVSession)
	{
		ERROR_LOG() << "Add av session failed.";
		DEBUG_LOG() << "--- LEAVE";
		m_pConvManager->RemoveConversation(convId);
		convId.clear();
		return UCSDK_Fail;
	}

	if (!pAVSession->Connect())
	{
		pAVSession->Disconnect();
		pConversation->RemoveSession(uc::model::AudioVideo);
		m_pConvManager->RemoveConversation(convId);
		convId.clear();
		ERROR_LOG() << "Connect failed.";
		DEBUG_LOG() << "--- LEAVE";
		return UCSDK_Fail;
	}

	//关联信号
#ifdef ESDKCLIENT_PLATFORM_DEPEND
	UCSDK* pUCSDK = UCSDK::CreateInstance();
#else
	UCSDK* pUCSDK = UCSDK::Instance();
#endif
	if (NULL == pUCSDK)
	{
		ERROR_LOG() << "Get UCSDK's instance failed.";
		DEBUG_LOG() << "--- LEAVE";
		return UCSDK_Fail;
	}
	(void)pUCSDK->ConnectConference(pConversation);

	DEBUG_LOG() << "--- LEAVE";
	return UCSDK_Succ;
}


int UCMeetingProxy::LeaveMeeting(const std::string& convId)
{
	DEBUG_LOG() << "--- ENTER";
	INFO_PARAM1(convId);

	if (convId.empty())
	{
		ERROR_LOG() << "convId is empty.";
		DEBUG_LOG() << "--- LEAVE";
		return UCSDK_InvalidParam;
	}

	//获取conversation
	uc::model::conversation::Conversation* pConversation = GetConversation(convId);
	if (NULL == pConversation)
	{
		ERROR_LOG() << "Get conversation failed.";
		DEBUG_LOG() << "--- LEAVE";
		return UCSDK_Fail;
	}

	//获取AVsession
	uc::model::conversation::AVSession* pAVSession = GetAVSession(pConversation);
	if (NULL == pAVSession)
	{
		ERROR_LOG() << "Get av session failed.";
		DEBUG_LOG() << "--- LEAVE";
		return UCSDK_Fail;
	}

	pAVSession->Disconnect();
	pConversation->RemoveSession(uc::model::InstantMessage);
	pConversation->RemoveSession(uc::model::AudioVideo);
	if (NULL != m_pConvManager)
	{
		m_pConvManager->RemoveConversation(convId);
	}

	DEBUG_LOG() << "--- LEAVE";
	return UCSDK_Succ;
}

int UCMeetingProxy::Mute(const UCSDKContact& member, const std::string& convId)
{
	DEBUG_LOG() << "--- ENTER";
	INFO_PARAM2(member.uri_, convId);

	//获取AVsession
	uc::model::conversation::AVSession* pAVSession = GetAVSession(convId);
	if (NULL == pAVSession)
	{
		ERROR_LOG() << "Get av session failed.";
		DEBUG_LOG() << "--- LEAVE";
		return UCSDK_Fail;
	}

	//查找联系人
	Contact contact;
	int iRet = FindContact(contact, member);
	if (UCSDK_Succ != iRet)
	{
		ERROR_LOG() << "Find contact failed.";
		DEBUG_LOG() << "--- LEAVE";
		return iRet;
	}

	uc::model::conversation::Participant part_;
	CopyContactToContact(contact, part_.contact_);

	std::vector<uc::model::conversation::Participant> partlist_;
	partlist_.push_back(part_);

	//静音
	if (!pAVSession->Mute(partlist_))
	{
		ERROR_LOG() << "Mute failed.";
		DEBUG_LOG() << "--- LEAVE";
		return UCSDK_Fail;
	}

	DEBUG_LOG() << "--- LEAVE";
	return UCSDK_Succ;
}

int UCMeetingProxy::UnMute(const UCSDKContact& member, const std::string& convId)
{
	DEBUG_LOG() << "--- ENTER";
	INFO_PARAM2(member.uri_, convId);

	//获取AVsession
	uc::model::conversation::AVSession* pAVSession = GetAVSession(convId);
	if (NULL == pAVSession)
	{
		ERROR_LOG() << "Get av session failed.";
		DEBUG_LOG() << "--- LEAVE";
		return UCSDK_Fail;
	}

	//查找联系人
	Contact contact;
	int iRet = FindContact(contact, member);
	if (UCSDK_Succ != iRet)
	{
		ERROR_LOG() << "Find contact failed.";
		DEBUG_LOG() << "--- LEAVE";
		return iRet;
	}

	uc::model::conversation::Participant part_;
	CopyContactToContact(contact, part_.contact_);

	std::vector<uc::model::conversation::Participant> partlist_;
	partlist_.push_back(part_);

	//静音
	if (!pAVSession->UnMute(partlist_))
	{
		ERROR_LOG() << "UnMute failed.";
		DEBUG_LOG() << "--- LEAVE";
		return UCSDK_Fail;
	}

	DEBUG_LOG() << "--- LEAVE";
	return UCSDK_Succ;
}

//////////////////////////////////////////////////////////////////////////
//辅助函数
uc::model::conversation::Conversation* UCMeetingProxy::GetConversation(const std::string& convId)
{
	DEBUG_LOG() << "--- ENTER";

	uc::model::conversation::Conversation* pConversation = NULL;

	//校验参数
	if (convId.empty())
	{
		ERROR_LOG() << "ConversationID is empty.";
		DEBUG_LOG() << "--- LEAVE";
		return pConversation;
	}
	if (NULL == m_pConvManager)
	{
		ERROR_LOG() << "m_pConvManager is null.";
		DEBUG_LOG() << "--- LEAVE";
		return pConversation;
	}

	//获取conversation
	pConversation = m_pConvManager->GetConversation(convId);
	if (NULL == pConversation)
	{
		ERROR_LOG() << "Get conversation failed.";
	}

	DEBUG_LOG() << "--- LEAVE";
	return pConversation;
}

uc::model::conversation::AVSession* UCMeetingProxy::GetAVSession(const std::string& convId)
{
	DEBUG_LOG() << "--- ENTER";

	uc::model::conversation::AVSession* pAVSession = NULL;

	uc::model::conversation::Conversation* pConversation = GetConversation(convId);
	if (NULL == pConversation)
	{
		ERROR_LOG() << "Get conversation failed.";
		DEBUG_LOG() << "--- LEAVE";
		return pAVSession;
	}

	pAVSession = dynamic_cast<uc::model::conversation::AVSession*>(pConversation->GetSession(uc::model::AudioVideo));
	if (NULL == pAVSession)
	{
		ERROR_LOG() << "Get av session failed.";
	}

	DEBUG_LOG() << "--- LEAVE";
	return pAVSession;
}

uc::model::conversation::AVSession* UCMeetingProxy::GetAVSession(conversation::Conversation* pConversation) const
{
	DEBUG_LOG() << "--- ENTER";
	INFO_PARAM1(pConversation);

	uc::model::conversation::AVSession* pAVSession = NULL;

	if (NULL == pConversation)
	{
		ERROR_LOG() << "pConversation is null.";
		DEBUG_LOG() << "--- LEAVE";
		return pAVSession;
	}

	pAVSession = dynamic_cast<uc::model::conversation::AVSession*>(pConversation->GetSession(uc::model::AudioVideo));
	if (NULL == pAVSession)
	{
		ERROR_LOG() << "Get av session failed.";
	}

	DEBUG_LOG() << "--- LEAVE";
	return pAVSession;
}

int UCMeetingProxy::FindContact(Contact& contact, const UCSDKContact& member) const
{
	DEBUG_LOG() << "--- ENTER";

	UCContactMgrProxy* pUCContactMgrProxy = UCContactMgrProxy::Instance();
	if (NULL == pUCContactMgrProxy)
	{
		ERROR_LOG() << "Get UCContactMgrProxy instance failed.";
		DEBUG_LOG() << "--- LEAVE";
		return UCSDK_NullPoint;
	}

	if (!pUCContactMgrProxy->GetContactByUCSDKContact(member, contact))
	{
		ERROR_LOG() << "Get contact by uccontact failed.";
		DEBUG_LOG() << "--- LEAVE";
		return UCSDK_Fail;
	}

	DEBUG_LOG() << "--- LEAVE";
	return UCSDK_Succ;
}

void UCMeetingProxy::CopyContactToContact(const Contact& first, Contact& second) const
{
	second.id_				= first.id_;
	second.uri_				= first.uri_;
	second.ucAcc_			= first.ucAcc_;
	second.staffNo_			= first.staffNo_;
	second.name_			= first.name_;
	second.nickName_		= first.nickName_;
	second.qpinyin_			= first.qpinyin_;
	second.spinyin_			= first.spinyin_;
	second.homePhone_		= first.homePhone_;
	second.officePhone_		= first.officePhone_;
	second.mobile_			= first.mobile_;
	second.otherPhone_		= first.otherPhone_;
	second.address_			= first.address_;
	second.email_			= first.email_;
	second.fax_				= first.fax_;
	second.corpName_		= first.corpName_;
	second.deptName_		= first.deptName_;
	second.webSite_			= first.webSite_;
	second.desc_			= first.desc_;
	second.zip_				= first.zip_;
	second.signature_		= first.signature_;
	second.imageID_			= first.imageID_;
	second.position_		= first.position_;
	second.location_		= first.location_;
	second.tzone_			= first.tzone_;
	second.avtool_			= first.avtool_;
	second.device_			= first.device_;
	second.terminalType_	= first.terminalType_;
}

}
}
