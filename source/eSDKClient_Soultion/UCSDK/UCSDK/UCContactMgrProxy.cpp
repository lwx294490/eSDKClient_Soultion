#include "stdafx.h"
#include "UCContactMgrProxy.h"
#include "eSDKLog.h"
#include "UCGroupProxy.h"


namespace eSDK {
	namespace UC {


UCContactMgrAbsProxy::UCContactMgrAbsProxy()
{

}

UCContactMgrAbsProxy::~UCContactMgrAbsProxy()
{

}

UCContactMgrAbsProxy* UCContactMgrAbsProxy::GetInstance()
{
	return dynamic_cast<UCContactMgrAbsProxy*>(UCContactMgrProxy::Instance());
}

void UCContactMgrAbsProxy::ReleaseInstance()
{
	UCContactMgrProxy::Destroy();
}

//////////////////////////////////////////////////////////////////////////
UCContactMgrProxy* UCContactMgrProxy::m_pUCContactMgrProxy = NULL;

UCContactMgrProxy::UCContactMgrProxy()
	: m_pContactMgr(NULL)
	, m_pEntContactMgr(NULL)
{

}

UCContactMgrProxy::~UCContactMgrProxy()
{
	m_pContactMgr = NULL;
	m_pEntContactMgr = NULL;
}

UCContactMgrProxy* UCContactMgrProxy::Instance()
{
	if (NULL == m_pUCContactMgrProxy)
	{
		m_pUCContactMgrProxy = new UCContactMgrProxy;
	}

	return m_pUCContactMgrProxy;
}

void UCContactMgrProxy::Destroy()
{
	if (NULL != m_pUCContactMgrProxy)
	{
		delete m_pUCContactMgrProxy;
		m_pUCContactMgrProxy = NULL;
	}
}

int UCContactMgrProxy::Init()
{
	DEBUG_LOG() << "--- ENTER";

	uc::model::UCClient* pUCClient = UCClient::GetClient();
	if (NULL == pUCClient)
	{
		ERROR_LOG() << "Get UCClient failed.";
		DEBUG_LOG() << "--- LEAVE";
		return UCSDK_NullPoint;
	}

	m_pContactMgr = pUCClient->ContactManager;
	if (NULL == m_pContactMgr)
	{
		ERROR_LOG() << "Get ContactMgr failed.";
		DEBUG_LOG() << "--- LEAVE";
		return UCSDK_NullPoint;
	}

	m_pEntContactMgr = &pUCClient->EntAddrbookManager_;

	DEBUG_LOG() << "--- LEAVE";
	return UCSDK_Succ;
}

int UCContactMgrProxy::UnInit()
{
	DEBUG_LOG() << "--- ENTER";

	m_pContactMgr = NULL;
	m_pEntContactMgr = NULL;

	DEBUG_LOG() << "--- LEAVE";
	return UCSDK_Succ;
}

int UCContactMgrProxy::GetAllContactlist(UCSDKContactList& memberList)
{
	DEBUG_LOG() << "--- ENTER";

	if(NULL == m_pContactMgr)
	{
		ERROR_LOG() << "m_pContactMgr is NULL.";
		DEBUG_LOG() << "--- LEAVE";
		return UCSDK_NullPoint;
	}

	std::vector<Contact> contactList;
	if (!m_pContactMgr->GetAllContactlist(contactList))
	{
		ERROR_LOG() << "Get all contact list failed.";
		DEBUG_LOG() << "--- LEAVE";
		return UCSDK_Fail;
	}

	std::vector<Contact>::iterator itor_b = contactList.begin();
	std::vector<Contact>::iterator itor_e = contactList.end();
	for (; itor_b != itor_e; itor_b++)
	{
		UCSDKContact member;
		CopyContactToUCSDKContact(*itor_b, member);
		memberList.push_back(member);
	}

	DEBUG_LOG() << "--- LEAVE";
	return UCSDK_Succ;
}

int UCContactMgrProxy::GetContactByAccount(UCSDKContact& member, const std::string& strAccount)
{
	DEBUG_LOG() << "--- ENTER";
	INFO_PARAM1(strAccount);

	if(NULL == m_pContactMgr)
	{
		ERROR_LOG() << "m_pContactMgr is NULL.";
		DEBUG_LOG() << "--- LEAVE";
		return UCSDK_NullPoint;
	}

	if (strAccount.empty())
	{
		ERROR_LOG() << "Account is empty.";
		DEBUG_LOG() << "--- LEAVE";
		return UCSDK_InvalidParam;
	}

	Contact contact;
	if (!m_pContactMgr->GetContactByAccount(strAccount, contact))
	{
		ERROR_LOG() << "Get contact by account failed.";
		DEBUG_LOG() << "--- LEAVE";
		return UCSDK_Fail;
	}

	CopyContactToUCSDKContact(contact, member);

	DEBUG_LOG() << "--- LEAVE";
	return UCSDK_Succ;
}

int UCContactMgrProxy::GetContactById(UCSDKContact& member, const std::string& strID)
{
	DEBUG_LOG() << "--- ENTER";
	INFO_PARAM1(strID);

	if(NULL == m_pContactMgr)
	{
		ERROR_LOG() << "m_pContactMgr is NULL.";
		DEBUG_LOG() << "--- LEAVE";
		return UCSDK_NullPoint;
	}

	if (strID.empty())
	{
		ERROR_LOG() << "Id is empty.";
		DEBUG_LOG() << "--- LEAVE";
		return UCSDK_InvalidParam;
	}

	Contact contact;
	if (!m_pContactMgr->GetContactById(strID, contact))
	{
		ERROR_LOG() << "Get contact by Id failed.";
		DEBUG_LOG() << "--- LEAVE";
		return UCSDK_Fail;
	}

	CopyContactToUCSDKContact(contact, member);

	DEBUG_LOG() << "--- LEAVE";
	return UCSDK_Succ;
}

int UCContactMgrProxy::GetContactByPhoneNum(UCSDKContact& member, const std::string& strPhoneNum)
{
	DEBUG_LOG() << "--- ENTER";
	INFO_PARAM1(strPhoneNum);

	if(NULL == m_pContactMgr)
	{
		ERROR_LOG() << "m_pContactMgr is NULL.";
		DEBUG_LOG() << "--- LEAVE";
		return UCSDK_NullPoint;
	}

	if (strPhoneNum.empty())
	{
		ERROR_LOG() << "Phonenum is empty.";
		DEBUG_LOG() << "--- LEAVE";
		return UCSDK_InvalidParam;
	}

	Contact contact;
	if (!m_pContactMgr->GetContactByPhoneNum(strPhoneNum, contact))
	{
		ERROR_LOG() << "Get contact by phonenum failed.";
		DEBUG_LOG() << "--- LEAVE";
		return UCSDK_Fail;
	}

	CopyContactToUCSDKContact(contact, member);

	DEBUG_LOG() << "--- LEAVE";
	return UCSDK_Succ;
}

int UCContactMgrProxy::GetContactByUri(UCSDKContact& member, const std::string& strUri)
{
	DEBUG_LOG() << "--- ENTER";
	INFO_PARAM1(strUri);

	if(NULL == m_pContactMgr)
	{
		ERROR_LOG() << "m_pContactMgr is NULL.";
		DEBUG_LOG() << "--- LEAVE";
		return UCSDK_NullPoint;
	}

	if (strUri.empty())
	{
		ERROR_LOG() << "uri is empty.";
		DEBUG_LOG() << "--- LEAVE";
		return UCSDK_InvalidParam;
	}

	Contact contact;
	if (!m_pContactMgr->GetContactByUri(strUri, contact))
	{
		ERROR_LOG() << "Get contact by uri failed.";
		DEBUG_LOG() << "--- LEAVE";
		return UCSDK_Fail;
	}

	CopyContactToUCSDKContact(contact, member);

	DEBUG_LOG() << "--- LEAVE";
	return UCSDK_Succ;
}

bool UCContactMgrProxy::HasContact(const std::string& strUri)
{
	DEBUG_LOG() << "--- ENTER";

	if(NULL == m_pContactMgr)
	{
		ERROR_LOG() << "m_pContactMgr is NULL.";
		DEBUG_LOG() << "--- LEAVE";
		return false;
	}

	bool bRet = m_pContactMgr->HasContact(strUri);
	INFO_LOG() << "HasContact return : " << bRet;

	DEBUG_LOG() << "--- LEAVE";
	return bRet;
}

int UCContactMgrProxy::RefreshContactByAccount(const std::string& strAccount, UCSDKContact& member)
{
	DEBUG_LOG() << "--- ENTER";

	if(NULL == m_pContactMgr)
	{
		ERROR_LOG() << "m_pContactMgr is NULL.";
		DEBUG_LOG() << "--- LEAVE";
		return UCSDK_NullPoint;
	}

	if (strAccount.empty())
	{
		ERROR_LOG() << "Account is empty";
		DEBUG_LOG() << "--- LEAVE";
		return UCSDK_InvalidParam;
	}

	Contact contact;
	if (!m_pContactMgr->RefreshContactByAccount(strAccount, contact))
	{
		ERROR_LOG() << "Refresh contact by account failed.";
		DEBUG_LOG() << "--- LEAVE";
		return UCSDK_Fail;
	}

	CopyContactToUCSDKContact(contact, member);

	DEBUG_LOG() << "--- LEAVE";
	return UCSDK_Succ;
}

int UCContactMgrProxy::RefreshContactById(const std::string& strID, UCSDKContact& member)
{
	DEBUG_LOG() << "--- ENTER";

	if(NULL == m_pContactMgr)
	{
		ERROR_LOG() << "m_pContactMgr is NULL.";
		DEBUG_LOG() << "--- LEAVE";
		return UCSDK_NullPoint;
	}

	if (strID.empty())
	{
		ERROR_LOG() << "Id is empty";
		DEBUG_LOG() << "--- LEAVE";
		return UCSDK_InvalidParam;
	}

	Contact contact;
	if (!m_pContactMgr->RefreshContactById(strID, contact))
	{
		ERROR_LOG() << "Refresh contact by Id failed.";
		DEBUG_LOG() << "--- LEAVE";
		return UCSDK_Fail;
	}

	CopyContactToUCSDKContact(contact, member);

	DEBUG_LOG() << "--- LEAVE";
	return UCSDK_Succ;
}

int UCContactMgrProxy::RefreshContactByUri(const std::string& strUri, UCSDKContact& member)
{
	DEBUG_LOG() << "--- ENTER";

	if(NULL == m_pContactMgr)
	{
		ERROR_LOG() << "m_pContactMgr is NULL.";
		DEBUG_LOG() << "--- LEAVE";
		return UCSDK_NullPoint;
	}

	if (strUri.empty())
	{
		ERROR_LOG() << "Uri is empty";
		DEBUG_LOG() << "--- LEAVE";
		return UCSDK_InvalidParam;
	}

	Contact contact;
	if (!m_pContactMgr->RefreshContactByUri(strUri, contact))
	{
		ERROR_LOG() << "Refresh contact by uri failed.";
		DEBUG_LOG() << "--- LEAVE";
		return UCSDK_Fail;
	}

	CopyContactToUCSDKContact(contact, member);

	DEBUG_LOG() << "--- LEAVE";
	return UCSDK_Succ;
}

int UCContactMgrProxy::RemoveContactById(const std::string& strID)
{
	DEBUG_LOG() << "--- ENTER";

	if(NULL == m_pContactMgr)
	{
		ERROR_LOG() << "m_pContactMgr is NULL.";
		DEBUG_LOG() << "--- LEAVE";
		return UCSDK_NullPoint;
	}

	if (strID.empty())
	{
		ERROR_LOG() << "Id is empty";
		DEBUG_LOG() << "--- LEAVE";
		return UCSDK_InvalidParam;
	}

	if (!m_pContactMgr->RemoveContactById(strID))
	{
		ERROR_LOG() << "Remove contact by Id failed.";
		DEBUG_LOG() << "--- LEAVE";
		return UCSDK_Fail;
	}

	DEBUG_LOG() << "--- LEAVE";
	return UCSDK_Succ;
}

int UCContactMgrProxy::SearchContact(UCSDKContactList& memberList, 
	const std::string& condition, const std::string& deptid,
	bool querysubdept, int offset, int count, int ordertype, int& recamount)
{
	DEBUG_LOG() << "--- ENTER";

	if ((0 > offset) || (0 >= count))
	{
		ERROR_LOG() << "offset or count less than 0.";
		DEBUG_LOG() << "--- LEAVE";
		return UCSDK_InvalidParam;
	}

	if(NULL == m_pEntContactMgr)
	{
		ERROR_LOG() << "m_pEntContactMgr is NULL.";
		DEBUG_LOG() << "--- LEAVE";
		return UCSDK_NullPoint;
	}

	Dept::_ContactStatuses _contactlist;
	if (!m_pEntContactMgr->SearchContact(condition, deptid, querysubdept, offset, count, ordertype, recamount, _contactlist))
	{
		ERROR_LOG() << "Search contact in ent failed.";
		DEBUG_LOG() << "--- LEAVE";
		return UCSDK_Fail;
	}

	Dept::_ContactStatuses::iterator itor_b = _contactlist.begin();
	Dept::_ContactStatuses::iterator itor_e = _contactlist.end();
	for (; itor_b != itor_e; itor_b++)
	{
		const ContactStatus& contacts = *itor_b;
		const Contact& contact = contacts.first;

		UCSDKContact member;
		CopyContactToUCSDKContact(contact, member);
		memberList.push_back(member);
	}

	DEBUG_LOG() << "--- LEAVE";
	return UCSDK_Succ;
}

bool UCContactMgrProxy::Modify(const UCSDKContact& member)
{
	DEBUG_LOG() << "--- ENTER";
	INFO_PARAM2(member.uri_, member.ucAcc_);

	Contact contact;
	if (!GetContactByUCSDKContact(member, contact))
	{
		ERROR_LOG() << "Get contact by ucsdkcontact failed.";
		DEBUG_LOG() << "--- LEAVE";
		return false;
	}

	bool bRet = contact.Modify();
	DEBUG_LOG() << "--- LEAVE";
	return bRet;
}

std::string UCContactMgrProxy::GetHeadImagePath(const UCSDKContact& member, bool grey)
{
	DEBUG_LOG() << "--- ENTER";
	INFO_PARAM2(member.uri_, member.ucAcc_);

	Contact contact;
	if (!GetContactByUCSDKContact(member, contact))
	{
		ERROR_LOG() << "Get contact by ucsdkcontact failed.";
		DEBUG_LOG() << "--- LEAVE";
		return "";
	}

	std::string strImagePath = contact.GetHeadImagePath(grey);
	INFO_PARAM1(strImagePath);

	DEBUG_LOG() << "--- LEAVE";
	return strImagePath;
}

bool UCContactMgrProxy::MoveToGroup(const UCSDKContact& /*member*/, const UCSDKGroup& /*_src*/, const UCSDKGroup& /*_target*/)
{
	DEBUG_LOG() << "--- ENTER";

	DEBUG_LOG() << "--- LEAVE";
	return true;
}

bool UCContactMgrProxy::AddToGroup(const UCSDKContact& member, const UCSDKGroup& _target)
{
	DEBUG_LOG() << "--- ENTER";
	INFO_PARAM3(member.ucAcc_, member.uri_, _target.id_);

	//获取 Contact
	Contact contact;
	if (!GetContactByUCSDKContact(member, contact))
	{
		ERROR_LOG() << "Get contact by ucsdkcontact failed.";
		DEBUG_LOG() << "--- LEAVE";
		return false;
	}

	uc::model::Group* targetGroup = NULL;

	//获取 Group target
	if (!GetGroupByUCGroup(_target, targetGroup))
	{
		ERROR_LOG() << "Get group by ucsdkgroup failed.";
		DEBUG_LOG() << "--- LEAVE";
		return false;
	}

	bool bRet = contact.AddToGroup(*targetGroup);
	
	delete targetGroup;

	DEBUG_LOG() << "--- LEAVE";

	return bRet;
}

bool UCContactMgrProxy::RemoveFromGroup(const UCSDKContact& member, const UCSDKGroup& _target)
{
	DEBUG_LOG() << "--- ENTER";
	INFO_PARAM3(member.ucAcc_, member.uri_, _target.id_);

	//获取 Contact
	Contact contact;
	if (!GetContactByUCSDKContact(member, contact))
	{
		ERROR_LOG() << "Get contact by ucsdkcontact failed.";
		DEBUG_LOG() << "--- LEAVE";
		return false;
	}

	uc::model::Group* targetGroup = NULL;

	//获取 Group target
	if (!GetGroupByUCGroup(_target, targetGroup))
	{
		ERROR_LOG() << "Get group by ucsdkgroup failed.";
		DEBUG_LOG() << "--- LEAVE";
		return false;
	}

	bool bRet = contact.RemoveFromGroup(*targetGroup);

	delete targetGroup;

	DEBUG_LOG() << "--- LEAVE";

	return bRet;
}

bool UCContactMgrProxy::CanStartSession(const UCSDKContact& member, SESSION_TYPE_E /*_type*/)
{
	DEBUG_LOG() << "--- ENTER";
	//获取 Contact
	Contact contact;
	if (!GetContactByUCSDKContact(member, contact))
	{
		ERROR_LOG() << "Get contact by ucsdkcontact failed.";
		DEBUG_LOG() << "--- LEAVE";
		return false;
	}
	
	//bool bRet = contact.CanStartSession((uc::model::SessionType)_type);
	DEBUG_LOG() << "--- LEAVE";

	return true;
}

bool UCContactMgrProxy::CanMoveToGroup(const UCSDKContact& member, const UCSDKGroup& _src, const UCSDKGroup& _target)
{
	DEBUG_LOG() << "--- ENTER";
	//获取 Contact
	Contact contact;
	if (!GetContactByUCSDKContact(member, contact))
	{
		ERROR_LOG() << "Get contact by ucsdkcontact failed.";
		DEBUG_LOG() << "--- LEAVE";
		return false;
	}
	
	uc::model::Group* srcGroup = NULL;
	uc::model::Group* targetGroup = NULL;

	//获取 Group src
	if (!GetGroupByUCGroup(_src, srcGroup))
	{
		ERROR_LOG() << "Get group by ucsdkgroup failed.";
		DEBUG_LOG() << "--- LEAVE";
		return false;
	}

	//获取 Group target
	if (!GetGroupByUCGroup(_target, targetGroup))
	{
		ERROR_LOG() << "Get group by ucsdkgroup failed.";
		delete srcGroup;
		DEBUG_LOG() << "--- LEAVE";
		return false;
	}

	//bool bRet = contact.CanMoveToGroup(*srcGroup, *targetGroup);
	
	delete srcGroup;
	delete targetGroup;

	DEBUG_LOG() << "--- LEAVE";

	return true;
}

int UCContactMgrProxy::GetCustomGroups(const UCSDKContact& member, UCSDKCustomGroupList& _groups)
{
	DEBUG_LOG() << "--- ENTER";
	//获取 Contact
	Contact contact;
	if (!GetContactByUCSDKContact(member, contact))
	{
		ERROR_LOG() << "Get contact by ucsdkcontact failed.";
		DEBUG_LOG() << "--- LEAVE";
		return UCSDK_Fail;
	}

	std::vector<uc::model::CustomGroup> _ucgroups;
	if (!contact.GetCustomGroups(_ucgroups))
	{
		ERROR_LOG() << "Get custom groups failed";
		DEBUG_LOG() << "--- LEAVE";
		return UCSDK_Fail;
	}
	
	std::vector<uc::model::CustomGroup>::iterator itor_b = _ucgroups.begin();
	std::vector<uc::model::CustomGroup>::iterator itor_e = _ucgroups.end();
	for(; itor_b != itor_e; itor_b++)
	{
		UCSDKCustomGroup group;
		UCGroupProxy::CopyCustomGroupToUCSDKCustomGroup((*itor_b), group);
		_groups.push_back(group);
	}
	
	DEBUG_LOG() << "--- LEAVE";
	return UCSDK_Succ;
}

bool UCContactMgrProxy::IsFavourite(const UCSDKContact& member)
{
	DEBUG_LOG() << "--- ENTER";
	//获取 Contact
	Contact contact;
	if (!GetContactByUCSDKContact(member, contact))
	{
		ERROR_LOG() << "Get contact by ucsdkcontact failed.";
		DEBUG_LOG() << "--- LEAVE";
		return false;
	}
	
	bool bRet = contact.IsFavourite();
	DEBUG_LOG() << "--- LEAVE";
	return bRet;
}

int UCContactMgrProxy::GetContactByUri(Contact& contact, const std::string& uri)
{
	DEBUG_LOG() << "--- ENTER";
	INFO_PARAM1(uri);

	if(NULL == m_pContactMgr)
	{
		ERROR_LOG() << "m_pContactMgr is NULL.";
		DEBUG_LOG() << "--- LEAVE";
		return UCSDK_NullPoint;
	}

	if (uri.empty())
	{
		ERROR_LOG() << "uri is empty.";
		DEBUG_LOG() << "--- LEAVE";
		return UCSDK_InvalidParam;
	}

	//先查本地
	bool bRet = m_pContactMgr->GetContactByUri(uri, contact);
	if(bRet)
	{	
		DEBUG_LOG() << "--- LEAVE";
		return UCSDK_Succ;
	}

	bRet = m_pContactMgr->RefreshContactByUri(uri, contact);
	if(!bRet)
	{
		INFO_LOG() << uri << "is not associated with UC account";
		DEBUG_LOG() << "--- LEAVE";
		return UCSDK_NotFound;
	}

	DEBUG_LOG() << "--- LEAVE";
	return UCSDK_Succ;
}

int UCContactMgrProxy::GetContactByAccount(Contact& contact, const std::string& account)
{
	DEBUG_LOG() << "--- ENTER";
	INFO_PARAM1(account);

	if(NULL == m_pContactMgr)
	{
		ERROR_LOG() << "m_pContactMgr is NULL.";
		DEBUG_LOG() << "--- LEAVE";
		return UCSDK_NullPoint;
	}

	if(NULL == m_pEntContactMgr)
	{
		ERROR_LOG() << "m_pEntContactMgr is NULL.";
		DEBUG_LOG() << "--- LEAVE";
		return UCSDK_NullPoint;
	}

	//先查本地，找不到再进行企业通讯录查询
	if(m_pContactMgr->GetContactByAccount(account, contact))
	{
		DEBUG_LOG() << "--- LEAVE";
		return UCSDK_Succ;
	}

	//上企业通讯录查询
	const int PAGE_SIZE = 20;			//每次查找返回的最大个数
	Dept::_ContactStatuses staffList;	//返回的结果
	int recamount = 0;					//返回的个数
	(void)m_pEntContactMgr->SearchContact(account, "", true, 0, PAGE_SIZE, 0, recamount, staffList);

	if(0 == staffList.size())
	{
		ERROR_LOG() << "Not Find UC Account";
		DEBUG_LOG() << "--- LEAVE";
		return UCSDK_NotFound;
	}

	Dept::_ContactStatuses::iterator iter_b = staffList.begin();
	Dept::_ContactStatuses::iterator iter_e = staffList.end();
	for (; iter_b != iter_e; iter_b++)
	{
		if ((iter_b->first).ucAcc_ == account)
		{
			break;
		}
	}
	
	if (iter_b == iter_e)
	{
		iter_b = staffList.begin();
	}

	//上面只查询一个结果，所以取第一个
	contact.id_				= (iter_b->first).id_;
	contact.uri_			= (iter_b->first).uri_;
	contact.ucAcc_			= (iter_b->first).ucAcc_;
	contact.staffNo_		= (iter_b->first).staffNo_;
	contact.name_			= (iter_b->first).name_;
	contact.nickName_		= (iter_b->first).nickName_;
	contact.qpinyin_		= (iter_b->first).qpinyin_;
	contact.spinyin_		= (iter_b->first).spinyin_;
	contact.homePhone_		= (iter_b->first).homePhone_;
	contact.officePhone_	= (iter_b->first).officePhone_;
	contact.mobile_			= (iter_b->first).mobile_;
	contact.otherPhone_		= (iter_b->first).otherPhone_;
	contact.address_		= (iter_b->first).address_;
	contact.email_			= (iter_b->first).email_;
	contact.fax_			= (iter_b->first).fax_;
	contact.corpName_		= (iter_b->first).corpName_;
	contact.deptName_		= (iter_b->first).deptName_;
	contact.webSite_		= (iter_b->first).webSite_;
	contact.desc_			= (iter_b->first).desc_;
	contact.zip_			= (iter_b->first).zip_;
	contact.signature_		= (iter_b->first).signature_;
	contact.imageID_		= (iter_b->first).imageID_;
	contact.position_		= (iter_b->first).position_;
	contact.location_		= (iter_b->first).location_;
	contact.tzone_			= (iter_b->first).tzone_;
	contact.avtool_			= (iter_b->first).avtool_;
	contact.device_			= (iter_b->first).device_;
	contact.terminalType_	= (iter_b->first).terminalType_;

	DEBUG_LOG() << "--- LEAVE";
	return UCSDK_Succ;
}

void UCContactMgrProxy::CopyUCSDKContactToContact(const UCSDKContact& member, Contact& contact)
{
	contact.id_				= member.id_;
	contact.uri_			= member.uri_;
	contact.ucAcc_			= member.ucAcc_;
	contact.staffNo_		= member.staffNo_;
	contact.name_			= member.name_;
	contact.nickName_		= member.nickName_;
	contact.qpinyin_		= member.qpinyin_;
	contact.spinyin_		= member.spinyin_;
	contact.homePhone_		= member.homePhone_;
	contact.officePhone_	= member.officePhone_;
	contact.mobile_			= member.mobile_;
	contact.otherPhone_		= member.otherPhone_;
	contact.address_		= member.address_;
	contact.email_			= member.email_;
	contact.fax_			= member.fax_;
	contact.corpName_		= member.corpName_;
	contact.deptName_		= member.deptName_;
	contact.webSite_		= member.webSite_;
	contact.desc_			= member.desc_;
	contact.zip_			= member.zip_;
	contact.signature_		= member.signature_;
	contact.imageID_		= member.imageID_;
	contact.position_		= member.position_;
	contact.location_		= member.location_;
	contact.tzone_			= member.tzone_;
	contact.avtool_			= member.avtool_;
	contact.device_			= member.device_;
	contact.terminalType_	= member.terminalType_;
}

void UCContactMgrProxy::CopyContactToUCSDKContact(const Contact& contact, UCSDKContact& member)
{
	member.id_				= contact.id_;
	member.uri_				= contact.uri_;
	member.ucAcc_			= contact.ucAcc_;
	member.staffNo_			= contact.staffNo_;
	member.name_			= contact.name_;
	member.nickName_		= contact.nickName_;
	member.qpinyin_			= contact.qpinyin_;
	member.spinyin_			= contact.spinyin_;
	member.homePhone_		= contact.homePhone_;
	member.officePhone_		= contact.officePhone_;
	member.mobile_			= contact.mobile_;
	member.otherPhone_		= contact.otherPhone_;
	member.address_			= contact.address_;
	member.email_			= contact.email_;
	member.fax_				= contact.fax_;
	member.corpName_		= contact.corpName_;
	member.deptName_		= contact.deptName_;
	member.webSite_			= contact.webSite_;
	member.desc_			= contact.desc_;
	member.zip_				= contact.zip_;
	member.signature_		= contact.signature_;
	member.imageID_			= contact.imageID_;
	member.position_		= contact.position_;
	member.location_		= contact.location_;
	member.tzone_			= contact.tzone_;
	member.avtool_			= contact.avtool_;
	member.device_			= contact.device_;
	member.terminalType_	= contact.terminalType_;
}

bool UCContactMgrProxy::GetContactByUCSDKContact(const UCSDKContact& member, Contact& contact)
{
	DEBUG_LOG() << "--- ENTER";

	if (!member.uri_.empty())
	{
		if (UCSDK_Succ != GetContactByUri(contact, member.uri_))
		{
			ERROR_LOG() << "Get contact by uri failed.";
			DEBUG_LOG() << "--- LEAVE";
			return false;
		}
	}
	else if (!member.ucAcc_.empty())
	{
		if (UCSDK_Succ != GetContactByAccount(contact, member.ucAcc_))
		{
			ERROR_LOG() << "Get contact by account failed.";
			DEBUG_LOG() << "--- LEAVE";
			return false;
		}
	}
	else
	{
		ERROR_LOG() << "Invalid input param";
		DEBUG_LOG() << "--- LEAVE";
		return false;
	}

	DEBUG_LOG() << "--- LEAVE";
	return true;
}

bool UCContactMgrProxy::GetGroupByUCGroup(const UCSDKGroup& ucsdkgroup, Group*& group)
{
	DEBUG_LOG() << "--- ENTER";

	if (NULL == m_pContactMgr)
	{
		ERROR_LOG() << "m_pContactMgr is null.";
		DEBUG_LOG() << "--- LEAVE";
		group = NULL;
		return false;
	}
	if (!ucsdkgroup.id_.empty())
	{
		group = new CustomGroup;
		CustomGroup* pCustomGroup = dynamic_cast<CustomGroup*>(group);
		if (NULL == pCustomGroup)
		{
			ERROR_LOG() << "pCustomGroup is null.";
			DEBUG_LOG() << "--- LEAVE";
			delete group;
			group = NULL;
			return false;
		}
		if (!m_pContactMgr->GetCustomGroupById(ucsdkgroup.id_, *pCustomGroup))
		{
			delete group;

			group = new FixedGroup;
			FixedGroup* pFixedGroup = dynamic_cast<FixedGroup*>(group);
			if (NULL == pFixedGroup)
			{
				ERROR_LOG() << "pFixedGroup is null.";
				DEBUG_LOG() << "--- LEAVE";
				delete group;
				group = NULL;
				return false;
			}
			if (!m_pContactMgr->GetFixedGroupByID(ucsdkgroup.id_, *pFixedGroup))
			{
				ERROR_LOG() << "Get group by ucsdkgroup failed.";
				DEBUG_LOG() << "--- LEAVE";

				delete group;
				group = NULL;
				return false;
			}

			DEBUG_LOG() << "--- LEAVE";
			return true;
		}

		DEBUG_LOG() << "--- LEAVE";
		return true;
	}

	DEBUG_LOG() << "--- LEAVE";
	return false;
}

}
}
