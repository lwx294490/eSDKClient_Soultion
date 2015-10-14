#include "stdafx.h"
#include "UCGroupProxy.h"
#include "UCContactMgrProxy.h"
#include "eSDKLog.h"


namespace eSDK {
	namespace UC {


UCGroupAbsProxy::UCGroupAbsProxy()
{

}

UCGroupAbsProxy::~UCGroupAbsProxy()
{

}

UCGroupAbsProxy* UCGroupAbsProxy::GetInstance()
{
	return dynamic_cast<UCGroupAbsProxy*>(UCGroupProxy::Instance());
}

void UCGroupAbsProxy::ReleaseInstance()
{
	UCGroupProxy::Destroy();
}
//////////////////////////////////////////////////////////////////////////
UCGroupProxy* UCGroupProxy::m_pUCGroupProxy = NULL;

UCGroupProxy::UCGroupProxy()
	: m_pUCClient(NULL)
	, m_pContactMgr(NULL)
{

}

UCGroupProxy::~UCGroupProxy()
{
	m_pUCClient = NULL;
	m_pContactMgr = NULL;
}

UCGroupProxy* UCGroupProxy::Instance()
{
	if (NULL == m_pUCGroupProxy)
	{
		m_pUCGroupProxy = new UCGroupProxy;
	}

	return m_pUCGroupProxy;
}

void UCGroupProxy::Destroy()
{
	if (NULL != m_pUCGroupProxy)
	{
		delete m_pUCGroupProxy;
		m_pUCGroupProxy = NULL;
	}
}

int UCGroupProxy::Init()
{
	DEBUG_LOG() << "--- ENTER";

	m_pUCClient = UCClient::GetClient();
	if (NULL == m_pUCClient)
	{
		ERROR_LOG() << "Get UCClient failed.";
		DEBUG_LOG() << "--- LEAVE";
		return UCSDK_NullPoint;
	}

	m_pContactMgr = m_pUCClient->ContactManager;
	if (NULL == m_pContactMgr)
	{
		ERROR_LOG() << "Get ContactMgr failed.";
		DEBUG_LOG() << "--- LEAVE";
		return UCSDK_NullPoint;
	}

	DEBUG_LOG() << "--- LEAVE";
	return UCSDK_Succ;
}

int UCGroupProxy::UnInit()
{
	DEBUG_LOG() << "--- ENTER";

	m_pUCClient = NULL;
	m_pContactMgr = NULL;

	DEBUG_LOG() << "--- LEAVE";
	return UCSDK_Succ;
}

int UCGroupProxy::AddFixedGroup(UCSDKFixedGroup& group)
{
	DEBUG_LOG() << "--- ENTER";
	INFO_PARAM1(group.name_);

	if (NULL == m_pContactMgr)
	{
		ERROR_LOG() << "m_pContactMgr is null.";
		DEBUG_LOG() << "--- LEAVE";
		return UCSDK_NullPoint;
	}

	uc::model::FixedGroup fixedGroup;
	CopyUCSDKFixedGroupToFixedGroup(group, fixedGroup);

	if (UCSDK_Succ != m_pContactMgr->AddFixedGroup(fixedGroup))
	{
		ERROR_LOG() << "Add fixed group failed.";
		DEBUG_LOG() << "--- LEAVE";
		return UCSDK_Fail;
	}

	CopyFixedGroupToUCSDKFixedGroup(fixedGroup, group);

	DEBUG_LOG() << "--- LEAVE";
	return UCSDK_Succ;
}

int UCGroupProxy::GetFixedGroupByID(UCSDKFixedGroup& group, const std::string& strGroupID)
{
	DEBUG_LOG() << "--- ENTER";
	INFO_PARAM1(strGroupID);

	if (strGroupID.empty())
	{
		ERROR_LOG() << "Group Id is empty.";
		DEBUG_LOG() << "--- LEAVE";
		return UCSDK_InvalidParam;
	}

	if (NULL == m_pContactMgr)
	{
		ERROR_LOG() << "m_pContactMgr is null.";
		DEBUG_LOG() << "--- LEAVE";
		return UCSDK_NullPoint;
	}

	uc::model::FixedGroup fixedGroup;
	if (!m_pContactMgr->GetFixedGroupByID(strGroupID, fixedGroup))
	{
		ERROR_LOG() << "Get fixed group by Id failed.";
		DEBUG_LOG() << "--- LEAVE";
		return UCSDK_Fail;
	}

	CopyFixedGroupToUCSDKFixedGroup(fixedGroup, group);

	DEBUG_LOG() << "--- LEAVE";
	return UCSDK_Succ;
}

int UCGroupProxy::GetFixedGroupByUri(UCSDKFixedGroup& group, const std::string& strGroupUri)
{
	DEBUG_LOG() << "--- ENTER";
	INFO_PARAM1(strGroupUri);

	if (strGroupUri.empty())
	{
		ERROR_LOG() << "Group uri is empty.";
		DEBUG_LOG() << "--- LEAVE";
		return UCSDK_InvalidParam;
	}

	if (NULL == m_pContactMgr)
	{
		ERROR_LOG() << "m_pContactMgr is null.";
		DEBUG_LOG() << "--- LEAVE";
		return UCSDK_NullPoint;
	}

	uc::model::FixedGroup fixedGroup;
	if (!m_pContactMgr->GetFixedGroupByUri(strGroupUri, fixedGroup))
	{
		ERROR_LOG() << "Get fixed group by uri failed.";
		DEBUG_LOG() << "--- LEAVE";
		return UCSDK_Fail;
	}

	CopyFixedGroupToUCSDKFixedGroup(fixedGroup, group);

	DEBUG_LOG() << "--- LEAVE";
	return UCSDK_Succ;
}

int UCGroupProxy::RemoveFixedGroup(const UCSDKFixedGroup& group)
{
	DEBUG_LOG() << "--- ENTER";
	INFO_PARAM2(group.name_, group.id_);

	if (NULL == m_pContactMgr)
	{
		ERROR_LOG() << "m_pContactMgr is null.";
		DEBUG_LOG() << "--- LEAVE";
		return UCSDK_NullPoint;
	}

	uc::model::FixedGroup fixedGroup;
	int iRet = GetFixedGroup(group, fixedGroup);
	if (UCSDK_Succ != iRet)
	{
		ERROR_LOG() << "GetFixedGroup failed.";
		DEBUG_LOG() << "--- LEAVE";
		return iRet;
	}

	if (!m_pContactMgr->RemoveFixedGroup(fixedGroup))
	{
		ERROR_LOG() << "Remove fixed group failed.";
		DEBUG_LOG() << "--- LEAVE";
		return UCSDK_Fail;
	}

	DEBUG_LOG() << "--- LEAVE";
	return UCSDK_Succ;
}

int UCGroupProxy::RefreshFixedGrouplist(UCSDKFixedGroupList& groupList)
{
	DEBUG_LOG() << "--- ENTER";

	if (NULL == m_pContactMgr)
	{
		ERROR_LOG() << "m_pContactMgr is null.";
		DEBUG_LOG() << "--- LEAVE";
		return UCSDK_NullPoint;
	}

	std::vector<uc::model::FixedGroup> _grouplist;
	if (!m_pContactMgr->RefreshFixedGrouplist(_grouplist))
	{
		ERROR_LOG() << "Refresh fixed group failed.";
		DEBUG_LOG() << "--- LEAVE";
		return UCSDK_Fail;
	}

	std::vector<uc::model::FixedGroup>::iterator itor_b = _grouplist.begin();
	std::vector<uc::model::FixedGroup>::iterator itor_e = _grouplist.end();
	for (; itor_b != itor_e; itor_b++)
	{
		//这里必须刷新固定群组，不然GetFixedGroupByID不能正常实现
		if (!itor_b->Refresh())
		{
			WARN_LOG() << "FixedGroup " << itor_b->name_ << " Refresh failed.";
		}

		UCSDKFixedGroup group;
		CopyFixedGroupToUCSDKFixedGroup(*itor_b, group);
		groupList.push_back(group);
	}

	DEBUG_LOG() << "--- LEAVE";
	return UCSDK_Succ;
}

int UCGroupProxy::GetFixedGrouplist(UCSDKFixedGroupList& groupList)
{
	DEBUG_LOG() << "--- ENTER";

	if (NULL == m_pContactMgr)
	{
		ERROR_LOG() << "m_pContactMgr is null.";
		DEBUG_LOG() << "--- LEAVE";
		return UCSDK_NullPoint;
	}

	std::vector<uc::model::FixedGroup> _grouplist;
	if (!m_pContactMgr->GetFixedGrouplist(_grouplist))
	{
		ERROR_LOG() << "Get fixed group failed.";
		DEBUG_LOG() << "--- LEAVE";
		return UCSDK_Fail;
	}

	std::vector<uc::model::FixedGroup>::iterator itor_b = _grouplist.begin();
	std::vector<uc::model::FixedGroup>::iterator itor_e = _grouplist.end();
	for (; itor_b != itor_e; itor_b++)
	{
		UCSDKFixedGroup group;
		CopyFixedGroupToUCSDKFixedGroup(*itor_b, group);
		groupList.push_back(group);
	}

	DEBUG_LOG() << "--- LEAVE";
	return UCSDK_Succ;
}

int UCGroupProxy::SearchFixedGroup(UCSDKFixedGroupList& groupList, 
	const std::string& groupNo, const std::string& groupName, int offset, int count)
{
	DEBUG_LOG() << "--- ENTER";
	INFO_PARAM4(groupNo, groupName, offset, count);

	if (NULL == m_pContactMgr)
	{
		ERROR_LOG() << "m_pContactMgr is null.";
		DEBUG_LOG() << "--- LEAVE";
		return UCSDK_NullPoint;
	}

	std::vector<uc::model::FixedGroup> _grouplist;
	if (!m_pContactMgr->SearchFixedGroup(groupNo, groupName, offset, count, _grouplist))
	{
		ERROR_LOG() << "Search fixed group failed.";
		DEBUG_LOG() << "--- LEAVE";
		return UCSDK_Fail;
	}

	std::vector<uc::model::FixedGroup>::iterator itor_b = _grouplist.begin();
	std::vector<uc::model::FixedGroup>::iterator itor_e = _grouplist.end();
	for (; itor_b != itor_e; itor_b++)
	{
		UCSDKFixedGroup group;
		CopyFixedGroupToUCSDKFixedGroup(*itor_b, group);
		groupList.push_back(group);
	}

	DEBUG_LOG() << "--- LEAVE";
	return UCSDK_Succ;
}

int UCGroupProxy::AddCustomGroup(UCSDKCustomGroup& group)
{
	DEBUG_LOG() << "--- ENTER";
	INFO_PARAM1(group.name_);

	if (NULL == m_pContactMgr)
	{
		ERROR_LOG() << "m_pContactMgr is null.";
		DEBUG_LOG() << "--- LEAVE";
		return UCSDK_NullPoint;
	}

	uc::model::CustomGroup customGroup;
	CopyUCSDKCustomGroupToCustomGroup(group, customGroup);

	if (!m_pContactMgr->AddCustomGroup(customGroup))
	{
		ERROR_LOG() << "Add custom group failed.";
		DEBUG_LOG() << "--- LEAVE";
		return UCSDK_Fail;
	}

	CopyCustomGroupToUCSDKCustomGroup(customGroup, group);

	DEBUG_LOG() << "--- LEAVE";
	return UCSDK_Succ;
}

int UCGroupProxy::AddFavoriteGroup(UCSDKFavoriteGroup& group)
{
	DEBUG_LOG() << "--- ENTER";
	INFO_PARAM1(group.name_);

	if (NULL == m_pContactMgr)
	{
		ERROR_LOG() << "m_pContactMgr is null.";
		DEBUG_LOG() << "--- LEAVE";
		return UCSDK_NullPoint;
	}

	uc::model::FavoriteGroup favoriteGroup;
	CopyUCSDKFavoriteGroupToFavoriteGroup(group, favoriteGroup);

	if (!m_pContactMgr->AddFavoriteGroup(favoriteGroup))
	{
		ERROR_LOG() << "Add favorite group failed.";
		DEBUG_LOG() << "--- LEAVE";
		return UCSDK_Fail;
	}

	CopyFavoriteGroupToUCSDKFavoriteGroup(favoriteGroup, group);

	DEBUG_LOG() << "--- LEAVE";
	return UCSDK_Succ;
}

int UCGroupProxy::GetCustomGroupById(UCSDKCustomGroup& group, const std::string& strGroupID)
{
	DEBUG_LOG() << "--- ENTER";
	INFO_PARAM1(strGroupID);

	if (strGroupID.empty())
	{
		ERROR_LOG() << "Group Id is empty.";
		DEBUG_LOG() << "--- LEAVE";
		return UCSDK_InvalidParam;
	}

	if (NULL == m_pContactMgr)
	{
		ERROR_LOG() << "m_pContactMgr is null.";
		DEBUG_LOG() << "--- LEAVE";
		return UCSDK_NullPoint;
	}

	uc::model::CustomGroup customGroup;
	if (!m_pContactMgr->GetCustomGroupById(strGroupID, customGroup))
	{
		ERROR_LOG() << "Get custom group by Id failed.";
		DEBUG_LOG() << "--- LEAVE";
		return UCSDK_Fail;
	}

	CopyCustomGroupToUCSDKCustomGroup(customGroup, group);

	DEBUG_LOG() << "--- LEAVE";
	return UCSDK_Succ;
}

int UCGroupProxy::GetCustomGrouplist(UCSDKCustomGroupList& groupList)
{
	DEBUG_LOG() << "--- ENTER";

	if (NULL == m_pContactMgr)
	{
		ERROR_LOG() << "m_pContactMgr is null.";
		DEBUG_LOG() << "--- LEAVE";
		return UCSDK_NullPoint;
	}

	std::vector<uc::model::CustomGroup> _grouplist;
	if (!m_pContactMgr->GetCustomGrouplist(_grouplist))
	{
		ERROR_LOG() << "Get custom group list failed.";
		DEBUG_LOG() << "--- LEAVE";
		return UCSDK_Fail;
	}

	std::vector<uc::model::CustomGroup>::iterator itor_b = _grouplist.begin();
	std::vector<uc::model::CustomGroup>::iterator itor_e = _grouplist.end();
	for (; itor_b != itor_e; itor_b++)
	{
		UCSDKCustomGroup group;
		CopyCustomGroupToUCSDKCustomGroup(*itor_b, group);
		groupList.push_back(group);
	}

	DEBUG_LOG() << "--- LEAVE";
	return UCSDK_Succ;
}

int UCGroupProxy::RemoveCustomGroup(const UCSDKCustomGroup& group)
{
	DEBUG_LOG() << "--- ENTER";
	INFO_PARAM2(group.name_,group.id_);

	if (NULL == m_pContactMgr)
	{
		ERROR_LOG() << "m_pContactMgr is null.";
		DEBUG_LOG() << "--- LEAVE";
		return UCSDK_NullPoint;
	}

	uc::model::CustomGroup customGroup;
	CopyUCSDKCustomGroupToCustomGroup(group, customGroup);
	if (!m_pContactMgr->RemoveCustomGroup(customGroup))
	{
		ERROR_LOG() << "Remove custom group failed.";
		DEBUG_LOG() << "--- LEAVE";
		return UCSDK_Fail;
	}

	DEBUG_LOG() << "--- LEAVE";
	return UCSDK_Succ;
}

int UCGroupProxy::RemoveFavoriteGroup(const UCSDKFavoriteGroup& group)
{
	DEBUG_LOG() << "--- ENTER";
	INFO_PARAM2(group.name_,group.id_);

	if (NULL == m_pContactMgr)
	{
		ERROR_LOG() << "m_pContactMgr is null.";
		DEBUG_LOG() << "--- LEAVE";
		return UCSDK_NullPoint;
	}

	uc::model::FavoriteGroup favoriteGroup;
	CopyUCSDKFavoriteGroupToFavoriteGroup(group, favoriteGroup);
	if (!m_pContactMgr->RemoveFavoriteGroup(favoriteGroup))
	{
		ERROR_LOG() << "Remove favorite group failed.";
		DEBUG_LOG() << "--- LEAVE";
		return UCSDK_Fail;
	}

	DEBUG_LOG() << "--- LEAVE";
	return UCSDK_Succ;
}

//FavoriteGroup
int UCGroupProxy::AddContact(const UCSDKFavoriteGroup& /*group*/, UCSDKContact& /*_contact*/)
{
	return UCSDK_Fail;
}

int UCGroupProxy::RemoveContact(const UCSDKFavoriteGroup& /*group*/, const UCSDKContact& /*_contact*/) const
{
	return UCSDK_Fail;
}

int UCGroupProxy::Rename(const UCSDKFavoriteGroup& /*group*/, const std::string& /*_name*/)
{
	return UCSDK_Fail;
}

int UCGroupProxy::GetContactlist(const UCSDKFavoriteGroup& /*group*/, UCSDKContactList& /*_contactlist*/)
{
	return UCSDK_Fail;
}

//CustomGroup
int UCGroupProxy::AddContact(const UCSDKCustomGroup& group, UCSDKContact& _contact)
{
	DEBUG_LOG() << "--- ENTER";
	INFO_PARAM3(group.id_, _contact.uri_, _contact.ucAcc_);

	if (NULL == m_pContactMgr)
	{
		ERROR_LOG() << "m_pContactMgr is null.";
		DEBUG_LOG() << "--- LEAVE";
		return UCSDK_NullPoint;
	}

	Contact contact;
	UCContactMgrProxy* pUCContactMgrProxy = UCContactMgrProxy::Instance();
	if (NULL == pUCContactMgrProxy)
	{
		ERROR_LOG() << "Get UCContactMgrProxy instance failed.";
		DEBUG_LOG() << "--- LEAVE";
		return UCSDK_NullPoint;
	}
	if (!pUCContactMgrProxy->GetContactByUCSDKContact(_contact, contact))
	{
		ERROR_LOG() << "Get contact by uccontact failed.";
		DEBUG_LOG() << "--- LEAVE";
		return UCSDK_Fail;
	}

	CustomGroup customGroup;
	if (!m_pContactMgr->GetCustomGroupById(group.id_, customGroup))
	{
		ERROR_LOG() << "Get custom group by id failed.";
		DEBUG_LOG() << "--- LEAVE";
		return UCSDK_Fail;
	}

	if (!customGroup.AddContact(contact))
	{
		ERROR_LOG() << "Add contact failed.";
		DEBUG_LOG() << "--- LEAVE";
		return UCSDK_Fail;
	}

	UCContactMgrProxy::CopyContactToUCSDKContact(contact, _contact);

	DEBUG_LOG() << "--- LEAVE";
	return UCSDK_Succ;
}

int UCGroupProxy::RemoveContact(const UCSDKCustomGroup& group, const UCSDKContact& _contact) const
{
	DEBUG_LOG() << "--- ENTER";
	INFO_PARAM3(group.id_, _contact.uri_, _contact.ucAcc_);

	if (NULL == m_pContactMgr)
	{
		ERROR_LOG() << "m_pContactMgr is null.";
		DEBUG_LOG() << "--- LEAVE";
		return UCSDK_NullPoint;
	}

	Contact contact;
	UCContactMgrProxy* pUCContactMgrProxy = UCContactMgrProxy::Instance();
	if (NULL == pUCContactMgrProxy)
	{
		ERROR_LOG() << "Get UCContactMgrProxy instance failed.";
		DEBUG_LOG() << "--- LEAVE";
		return UCSDK_NullPoint;
	}
	if (!pUCContactMgrProxy->GetContactByUCSDKContact(_contact, contact))
	{
		ERROR_LOG() << "Get contact by uccontact failed.";
		DEBUG_LOG() << "--- LEAVE";
		return UCSDK_Fail;
	}

	CustomGroup customGroup;
	if (!m_pContactMgr->GetCustomGroupById(group.id_, customGroup))
	{
		ERROR_LOG() << "Get custom group by id failed.";
		DEBUG_LOG() << "--- LEAVE";
		return UCSDK_Fail;
	}
	
	if (!contact.RemoveFromGroup(customGroup))
	{
		ERROR_LOG() << "Remove contact from group failed.";
		DEBUG_LOG() << "--- LEAVE";
		return UCSDK_Fail;
	}
	
	if (!m_pContactMgr->RemoveContactById(contact.id_))
	{
		ERROR_LOG() << "Remove contact failed.";
		DEBUG_LOG() << "--- LEAVE";
		return UCSDK_Fail;
	}
	DEBUG_LOG() << "--- LEAVE";
	return UCSDK_Succ;
}

int UCGroupProxy::Rename(const UCSDKCustomGroup& group, const std::string& _name)
{
	DEBUG_LOG() << "--- ENTER";
	INFO_PARAM2(group.id_, _name);

	if (NULL == m_pContactMgr)
	{
		ERROR_LOG() << "m_pContactMgr is null.";
		DEBUG_LOG() << "--- LEAVE";
		return UCSDK_NullPoint;
	}

	CustomGroup customGroup;
	if (!m_pContactMgr->GetCustomGroupById(group.id_, customGroup))
	{
		ERROR_LOG() << "Get custom group by id failed.";
		DEBUG_LOG() << "--- LEAVE";
		return UCSDK_Fail;
	}

	//这里不对返回值进行判断，因为经过测试，发现group名字修改成功，但是该接口仍然返回false
	customGroup.Rename(_name);

	DEBUG_LOG() << "--- LEAVE";
	return UCSDK_Succ;
}

int UCGroupProxy::GetContactlist(const UCSDKCustomGroup& group, UCSDKContactList& _contactlist)
{
	DEBUG_LOG() << "--- ENTER";
	INFO_PARAM2(group.name_,group.id_);

	if (NULL == m_pContactMgr)
	{
		ERROR_LOG() << "m_pContactMgr is null.";
		DEBUG_LOG() << "--- LEAVE";
		return UCSDK_NullPoint;
	}

	CustomGroup customGroup;
	if (!m_pContactMgr->GetCustomGroupById(group.id_, customGroup))
	{
		ERROR_LOG() << "Get custom group by id failed.";
		DEBUG_LOG() << "--- LEAVE";
		return UCSDK_Fail;
	}

	std::vector<Contact> contactlist;
	if (!customGroup.GetContactlist(contactlist))
	{
		ERROR_LOG() << "Get contact list failed.";
		DEBUG_LOG() << "--- LEAVE";
		return UCSDK_Fail;
	}

	std::vector<Contact>::iterator itor_b = contactlist.begin();
	std::vector<Contact>::iterator itor_e = contactlist.end();
	for (; itor_b != itor_e; itor_b++)
	{
		UCSDKContact member;
		UCContactMgrProxy::CopyContactToUCSDKContact(*itor_b, member);
		_contactlist.push_back(member);
	}

	DEBUG_LOG() << "--- LEAVE";
	return UCSDK_Succ;
}

int UCGroupProxy::MoveUp(const UCSDKCustomGroup& /*group*/)
{
	//DEBUG_LOG() << "--- ENTER";
	//INFO_PARAM1(group.id_);

	//if (NULL == m_pContactMgr)
	//{
	//	ERROR_LOG() << "m_pContactMgr is null.";
	//	DEBUG_LOG() << "--- LEAVE";
	//	return UCSDK_NullPoint;
	//}

	//CustomGroup customGroup;
	//if (!m_pContactMgr->GetCustomGroupById(group.id_, customGroup))
	//{
	//	ERROR_LOG() << "Get custom group by id failed.";
	//	DEBUG_LOG() << "--- LEAVE";
	//	return UCSDK_Fail;
	//}

	//if (!customGroup.MoveUp())
	//{
	//	ERROR_LOG() << "Move up failed.";
	//	DEBUG_LOG() << "--- LEAVE";
	//	return UCSDK_Fail;
	//}

	//DEBUG_LOG() << "--- LEAVE";
	return UCSDK_Succ;
}

int UCGroupProxy::MoveDown(const UCSDKCustomGroup& /*group*/)
{
	//DEBUG_LOG() << "--- ENTER";
	//INFO_PARAM1(group.id_);

	//if (NULL == m_pContactMgr)
	//{
	//	ERROR_LOG() << "m_pContactMgr is null.";
	//	DEBUG_LOG() << "--- LEAVE";
	//	return UCSDK_NullPoint;
	//}

	//CustomGroup customGroup;
	//if (!m_pContactMgr->GetCustomGroupById(group.id_, customGroup))
	//{
	//	ERROR_LOG() << "Get custom group by id failed.";
	//	DEBUG_LOG() << "--- LEAVE";
	//	return UCSDK_Fail;
	//}

	//if (!customGroup.MoveDown())
	//{
	//	ERROR_LOG() << "Move down failed.";
	//	DEBUG_LOG() << "--- LEAVE";
	//	return UCSDK_Fail;
	//}

	//DEBUG_LOG() << "--- LEAVE";
	return UCSDK_Succ;
}

//FixedGroup
int UCGroupProxy::AddContact(const UCSDKFixedGroup& group, UCSDKContact& _contact)
{
	DEBUG_LOG() << "--- ENTER";
	INFO_PARAM3(group.id_, _contact.uri_, _contact.ucAcc_);

	if (NULL == m_pContactMgr)
	{
		ERROR_LOG() << "m_pContactMgr is null.";
		DEBUG_LOG() << "--- LEAVE";
		return UCSDK_NullPoint;
	}

	Contact contact;
	UCContactMgrProxy* pUCContactMgrProxy = UCContactMgrProxy::Instance();
	if (NULL == pUCContactMgrProxy)
	{
		ERROR_LOG() << "Get UCContactMgrProxy instance failed.";
		DEBUG_LOG() << "--- LEAVE";
		return UCSDK_NullPoint;
	}
	if (!pUCContactMgrProxy->GetContactByUCSDKContact(_contact, contact))
	{
		ERROR_LOG() << "Get contact by uccontact failed.";
		DEBUG_LOG() << "--- LEAVE";
		return UCSDK_Fail;
	}

	//在本地查找固定群组（用于群主主动加人）
	uc::model::FixedGroup fixedGroup;
	int iRet = GetFixedGroup(group, fixedGroup);
	if (UCSDK_Succ != iRet)
	{
		INFO_LOG() << "GetFixedGroup failed.";
		//在通讯录查找固定群组（用于申请加入群组）
		iRet = SearchFixedGroup(group, fixedGroup);
		if (UCSDK_Succ != iRet)
		{
			ERROR_LOG() << "SearchFixedGroup failed.";
			DEBUG_LOG() << "--- LEAVE";
			return iRet;
		}
		INFO_LOG() << "SearchFixedGroup success.";
	}

	if (UCSDK_Succ != fixedGroup.AddContact(contact))
	{
		ERROR_LOG() << "Add contact failed.";
		DEBUG_LOG() << "--- LEAVE";
		return UCSDK_Fail;
	}

	UCContactMgrProxy::CopyContactToUCSDKContact(contact, _contact);

	DEBUG_LOG() << "--- LEAVE";
	return UCSDK_Succ;
}

int UCGroupProxy::RemoveContact(const UCSDKFixedGroup& group, const UCSDKContact& _contact) const
{
	DEBUG_LOG() << "--- ENTER";
	INFO_PARAM3(group.id_, _contact.uri_, _contact.ucAcc_);

	if (NULL == m_pContactMgr)
	{
		ERROR_LOG() << "m_pContactMgr is null.";
		DEBUG_LOG() << "--- LEAVE";
		return UCSDK_NullPoint;
	}

	Contact contact;
	UCContactMgrProxy* pUCContactMgrProxy = UCContactMgrProxy::Instance();
	if (NULL == pUCContactMgrProxy)
	{
		ERROR_LOG() << "Get UCContactMgrProxy instance failed.";
		DEBUG_LOG() << "--- LEAVE";
		return UCSDK_NullPoint;
	}
	if (!pUCContactMgrProxy->GetContactByUCSDKContact(_contact, contact))
	{
		ERROR_LOG() << "Get contact by uccontact failed.";
		DEBUG_LOG() << "--- LEAVE";
		return UCSDK_Fail;
	}

	uc::model::FixedGroup fixedGroup;
	int iRet = GetFixedGroup(group, fixedGroup);
	if (UCSDK_Succ != iRet)
	{
		ERROR_LOG() << "GetFixedGroup failed.";
		DEBUG_LOG() << "--- LEAVE";
		return iRet;
	}

	if (!contact.RemoveFromGroup(fixedGroup))
	{
		ERROR_LOG() << "Remove contact from group failed.";
		DEBUG_LOG() << "--- LEAVE";
		return UCSDK_Fail;
	}
	
	DEBUG_LOG() << "--- LEAVE";
	return UCSDK_Succ;
}

int UCGroupProxy::Rename(const UCSDKFixedGroup& group, const std::string& _name)
{
	DEBUG_LOG() << "--- ENTER";
	INFO_PARAM2(group.id_, _name);

	if (NULL == m_pContactMgr)
	{
		ERROR_LOG() << "m_pContactMgr is null.";
		DEBUG_LOG() << "--- LEAVE";
		return UCSDK_NullPoint;
	}

	uc::model::FixedGroup fixedGroup;
	int iRet = GetFixedGroup(group, fixedGroup);
	if (UCSDK_Succ != iRet)
	{
		ERROR_LOG() << "GetFixedGroup failed.";
		DEBUG_LOG() << "--- LEAVE";
		return iRet;
	}

	if (!fixedGroup.Rename(_name))
	{
		ERROR_LOG() << "Rename failed.";
		DEBUG_LOG() << "--- LEAVE";
		return UCSDK_Fail;
	}

	DEBUG_LOG() << "--- LEAVE";
	return UCSDK_Succ;
}

int UCGroupProxy::GetContactlist(const UCSDKFixedGroup& group, UCSDKContactList& _contactlist)
{
	DEBUG_LOG() << "--- ENTER";
	INFO_PARAM2(group.name_,group.id_);

	if (NULL == m_pContactMgr)
	{
		ERROR_LOG() << "m_pContactMgr is null.";
		DEBUG_LOG() << "--- LEAVE";
		return UCSDK_NullPoint;
	}

	uc::model::FixedGroup fixedGroup;
	int iRet = GetFixedGroup(group, fixedGroup);
	if (UCSDK_Succ != iRet)
	{
		ERROR_LOG() << "GetFixedGroup failed.";
		DEBUG_LOG() << "--- LEAVE";
		return iRet;
	}

	std::vector<Contact> contactlist;
	if (!fixedGroup.GetContactlist(contactlist))
	{
		ERROR_LOG() << "Get contact list failed.";
		DEBUG_LOG() << "--- LEAVE";
		return UCSDK_Fail;
	}

	std::vector<Contact>::iterator itor_b = contactlist.begin();
	std::vector<Contact>::iterator itor_e = contactlist.end();
	for (; itor_b != itor_e; itor_b++)
	{
		UCSDKContact member;
		UCContactMgrProxy::CopyContactToUCSDKContact(*itor_b, member);
		_contactlist.push_back(member);
	}

	DEBUG_LOG() << "--- LEAVE";
	return UCSDK_Succ;
}

int UCGroupProxy::ChangeGroupInfo(const UCSDKFixedGroup& group)
{
	DEBUG_LOG() << "--- ENTER";
	INFO_PARAM2(group.name_,group.id_);

	if (NULL == m_pContactMgr)
	{
		ERROR_LOG() << "m_pContactMgr is null.";
		DEBUG_LOG() << "--- LEAVE";
		return UCSDK_NullPoint;
	}

	FixedGroup fixedGroup;
	int iRet = GetFixedGroup(group, fixedGroup);
	if (UCSDK_Succ != iRet)
	{
		ERROR_LOG() << "GetFixedGroup failed.";
		DEBUG_LOG() << "--- LEAVE";
		return iRet;
	}

	//确保查找到的uri_和id_与入参一致
	if (group.uri_ != fixedGroup.uri_ || group.id_ != fixedGroup.id_)
	{
		ERROR_LOG() << "FixedGroup's id or uri is not equal to the UCSDKFixedGroup.";
		DEBUG_LOG() << "--- LEAVE";
		return UCSDK_NotFound;
	}
	//修改要改变的值！
	CopyUCSDKFixedGroupToFixedGroup(group, fixedGroup);

	if (!fixedGroup.ChangeGroupInfo())
	{
		ERROR_LOG() << "Change group info failed.";
		DEBUG_LOG() << "--- LEAVE";
		return UCSDK_Fail;
	}

	DEBUG_LOG() << "--- LEAVE";
	return UCSDK_Succ;
}

int UCGroupProxy::ChangeGroupOwner(const UCSDKFixedGroup& group, const UCSDKContact& _owner)
{
	DEBUG_LOG() << "--- ENTER";
	INFO_PARAM3(group.id_, _owner.uri_, _owner.ucAcc_);

	if (NULL == m_pContactMgr)
	{
		ERROR_LOG() << "m_pContactMgr is null.";
		DEBUG_LOG() << "--- LEAVE";
		return UCSDK_NullPoint;
	}

	Contact contact;
	UCContactMgrProxy* pUCContactMgrProxy = UCContactMgrProxy::Instance();
	if (NULL == pUCContactMgrProxy)
	{
		ERROR_LOG() << "Get UCContactMgrProxy instance failed.";
		DEBUG_LOG() << "--- LEAVE";
		return UCSDK_NullPoint;
	}
	if (!pUCContactMgrProxy->GetContactByUCSDKContact(_owner, contact))
	{
		ERROR_LOG() << "Get contact by uccontact failed.";
		DEBUG_LOG() << "--- LEAVE";
		return UCSDK_Fail;
	}

	uc::model::FixedGroup fixedGroup;
	int iRet = GetFixedGroup(group, fixedGroup);
	if (UCSDK_Succ != iRet)
	{
		ERROR_LOG() << "GetFixedGroup failed.";
		DEBUG_LOG() << "--- LEAVE";
		return iRet;
	}

	if (UCSDK_Succ != fixedGroup.ChangeGroupOwner(contact))
	{
		ERROR_LOG() << "Change group owner failed.";
		DEBUG_LOG() << "--- LEAVE";
		return UCSDK_Fail;
	}

	DEBUG_LOG() << "--- LEAVE";
	return UCSDK_Succ;
}

int UCGroupProxy::Refresh(const UCSDKFixedGroup& group, UCSDKContactList& _contactlist)
{
	DEBUG_LOG() << "--- ENTER";
	INFO_PARAM1(group.id_);

	if (NULL == m_pContactMgr)
	{
		ERROR_LOG() << "m_pContactMgr is null.";
		DEBUG_LOG() << "--- LEAVE";
		return UCSDK_NullPoint;
	}

	uc::model::FixedGroup fixedGroup;
	int iRet = GetFixedGroup(group, fixedGroup);
	if (UCSDK_Succ != iRet)
	{
		INFO_LOG() << "GetFixedGroup failed.";
		iRet = SearchFixedGroup(group, fixedGroup);
		if (UCSDK_Succ != iRet)
		{
			ERROR_LOG() << "GetFixedGroup failed.";
			DEBUG_LOG() << "--- LEAVE";
			return iRet;
		}
	}

	std::vector<Contact> contactlist;
	if (!fixedGroup.Refresh(contactlist))
	{
		ERROR_LOG() << "Refresh failed.";
		DEBUG_LOG() << "--- LEAVE";
		return UCSDK_Fail;
	}

	std::vector<Contact>::iterator itor_b = contactlist.begin();
	std::vector<Contact>::iterator itor_e = contactlist.end();
	for (; itor_b != itor_e; itor_b++)
	{
		UCSDKContact member;
		UCContactMgrProxy::CopyContactToUCSDKContact(*itor_b, member);
		_contactlist.push_back(member);
	}

	DEBUG_LOG() << "--- LEAVE";
	return UCSDK_Succ;
}

int UCGroupProxy::Refresh(const UCSDKFixedGroup& group, bool sync_)
{
	DEBUG_LOG() << "--- ENTER";
	INFO_PARAM2(group.id_, sync_);

	if (NULL == m_pContactMgr)
	{
		ERROR_LOG() << "m_pContactMgr is null.";
		DEBUG_LOG() << "--- LEAVE";
		return UCSDK_NullPoint;
	}

	uc::model::FixedGroup fixedGroup;
	int iRet = GetFixedGroup(group, fixedGroup);
	if (UCSDK_Succ != iRet)
	{
		INFO_LOG() << "GetFixedGroup failed.";
		iRet = SearchFixedGroup(group, fixedGroup);
		if (UCSDK_Succ != iRet)
		{
			ERROR_LOG() << "GetFixedGroup failed.";
			DEBUG_LOG() << "--- LEAVE";
			return iRet;
		}
	}

	if (!fixedGroup.Refresh(sync_))
	{
		ERROR_LOG() << "Refresh failed.";
		DEBUG_LOG() << "--- LEAVE";
		return UCSDK_Fail;
	}

	DEBUG_LOG() << "--- LEAVE";
	return UCSDK_Succ;
}

int UCGroupProxy::AcceptInvitation(const UCSDKFixedGroup& group) const
{
	DEBUG_LOG() << "--- ENTER";
	INFO_PARAM1(group.id_);

	//查找固定群组
	uc::model::FixedGroup fixedGroup;
	int iRet = SearchFixedGroup(group, fixedGroup);
	if (UCSDK_Succ != iRet)
	{
		ERROR_LOG() << "SearchFixedGroup failed.";
		DEBUG_LOG() << "--- LEAVE";
		return iRet;
	}

	if (!fixedGroup.AcceptInvitation())
	{
		ERROR_LOG() << ".Accept invitation failed.";
		DEBUG_LOG() << "--- LEAVE";
		return UCSDK_Fail;
	}

	DEBUG_LOG() << "--- LEAVE";
	return UCSDK_Succ;
}

int UCGroupProxy::RejectInvitation(const UCSDKFixedGroup& group) const
{
	DEBUG_LOG() << "--- ENTER";
	INFO_PARAM1(group.id_);

	//查找固定群组
	uc::model::FixedGroup fixedGroup;
	int iRet = SearchFixedGroup(group, fixedGroup);
	if (UCSDK_Succ != iRet)
	{
		ERROR_LOG() << "SearchFixedGroup failed.";
		DEBUG_LOG() << "--- LEAVE";
		return iRet;
	}

	if (!fixedGroup.RejectInvitation())
	{
		ERROR_LOG() << "Reject invitation failed.";
		DEBUG_LOG() << "--- LEAVE";
		return UCSDK_Fail;
	}

	DEBUG_LOG() << "--- LEAVE";
	return UCSDK_Succ;
}

int UCGroupProxy::AcceptJoinReq(const UCSDKFixedGroup& group, const UCSDKContact& _contact) const
{
	DEBUG_LOG() << "--- ENTER";
	INFO_PARAM5(_contact.uri_,_contact.ucAcc_,group.name_,group.id_,group.uri_);

	if (NULL == m_pContactMgr)
	{
		ERROR_LOG() << "m_pContactMgr is null.";
		DEBUG_LOG() << "--- LEAVE";
		return UCSDK_NullPoint;
	}

	//查找联系人
	uc::model::Contact contact;
	UCContactMgrProxy* pUCContactMgrProxy = UCContactMgrProxy::Instance();
	if (NULL == pUCContactMgrProxy)
	{
		ERROR_LOG() << "Get UCContactMgrProxy instance failed.";
		DEBUG_LOG() << "--- LEAVE";
		return UCSDK_NullPoint;
	}
	if (!pUCContactMgrProxy->GetContactByUCSDKContact(_contact, contact))
	{
		ERROR_LOG() << "Get contact by uccontact failed.";
		DEBUG_LOG() << "--- LEAVE";
		return UCSDK_Fail;
	}

	//查找固定群组
	uc::model::FixedGroup fixedGroup;
	int iRet = GetFixedGroup(group, fixedGroup);
	if (UCSDK_Succ != iRet)
	{
		ERROR_LOG() << "GetFixedGroup failed.";
		DEBUG_LOG() << "--- LEAVE";
		return iRet;
	}

	//接受请求
	if (!fixedGroup.AcceptJoinReq(contact))
	{
		ERROR_LOG() << "AcceptJoinReq failed.";
		DEBUG_LOG() << "--- LEAVE";
		return UCSDK_Fail;
	}

	DEBUG_LOG() << "--- LEAVE";
	return UCSDK_Succ;
}

int UCGroupProxy::RejectJoinReq(const UCSDKFixedGroup& group, const UCSDKContact& _contact) const
{
	DEBUG_LOG() << "--- ENTER";
	INFO_PARAM5(_contact.uri_,_contact.ucAcc_,group.name_,group.id_,group.uri_);

	if (NULL == m_pContactMgr)
	{
		ERROR_LOG() << "m_pContactMgr is null.";
		DEBUG_LOG() << "--- LEAVE";
		return UCSDK_NullPoint;
	}

	//查找联系人
	uc::model::Contact contact;
	UCContactMgrProxy* pUCContactMgrProxy = UCContactMgrProxy::Instance();
	if (NULL == pUCContactMgrProxy)
	{
		ERROR_LOG() << "Get UCContactMgrProxy instance failed.";
		DEBUG_LOG() << "--- LEAVE";
		return UCSDK_NullPoint;
	}
	if (!pUCContactMgrProxy->GetContactByUCSDKContact(_contact, contact))
	{
		ERROR_LOG() << "Get contact by uccontact failed.";
		DEBUG_LOG() << "--- LEAVE";
		return UCSDK_Fail;
	}

	//查找固定群组
	uc::model::FixedGroup fixedGroup;
	int iRet = GetFixedGroup(group, fixedGroup);
	if (UCSDK_Succ != iRet)
	{
		ERROR_LOG() << "GetFixedGroup failed.";
		DEBUG_LOG() << "--- LEAVE";
		return iRet;
	}

	//拒绝请求
	if (!fixedGroup.RejectJoinReq(contact))
	{
		ERROR_LOG() << "RejectJoinReq failed.";
		DEBUG_LOG() << "--- LEAVE";
		return UCSDK_Fail;
	}

	DEBUG_LOG() << "--- LEAVE";
	return UCSDK_Succ;
}

int UCGroupProxy::GetFixedGroup(const UCSDKFixedGroup& group, uc::model::FixedGroup& fixedGroup) const
{
	DEBUG_LOG() << "--- ENTER";
	INFO_PARAM2(group.uri_, group.id_);

	if (NULL == m_pContactMgr)
	{
		ERROR_LOG() << "m_pContactMgr is null.";
		DEBUG_LOG() << "--- LEAVE";
		return UCSDK_NullPoint;
	}

	if (!group.id_.empty())
	{
		if (!m_pContactMgr->GetFixedGroupByID(group.id_, fixedGroup))
		{
			ERROR_LOG() << "GetFixedGroupByID failed.";
			DEBUG_LOG() << "--- LEAVE";
			return UCSDK_Fail;
		}
	}
	else if (!group.uri_.empty())
	{
		if (!m_pContactMgr->GetFixedGroupByUri(group.uri_, fixedGroup))
		{
			ERROR_LOG() << "GetFixedGroupByUri failed.";
			DEBUG_LOG() << "--- LEAVE";
			return UCSDK_Fail;
		}
	}
	else
	{
		ERROR_LOG() << "group's id and uri are empty.";
		DEBUG_LOG() << "--- LEAVE";
		return UCSDK_InvalidParam;
	}

	DEBUG_LOG() << "--- LEAVE";
	return UCSDK_Succ;
}

int UCGroupProxy::SearchFixedGroup(const UCSDKFixedGroup& group, uc::model::FixedGroup& fixedGroup) const
{
	DEBUG_LOG() << "--- ENTER";
	INFO_PARAM2(group.name_, group.groupno_);

	if (NULL == m_pContactMgr)
	{
		ERROR_LOG() << "m_pContactMgr is null.";
		DEBUG_LOG() << "--- LEAVE";
		return UCSDK_NullPoint;
	}

	const int SIZE = 5;
	std::vector<FixedGroup> fixedgrouplist;
	if (!m_pContactMgr->SearchFixedGroup(group.groupno_, group.name_, 1, SIZE, fixedgrouplist))
	{
		ERROR_LOG() << "SearchFixedGroup failed.";
		DEBUG_LOG() << "--- LEAVE";
		return UCSDK_Fail;
	}

	if (fixedgrouplist.empty())
	{
		ERROR_LOG() << "Fixedgrouplist is empty.";
		DEBUG_LOG() << "--- LEAVE";
		return UCSDK_Fail;
	}

	for (size_t i=0; i<fixedgrouplist.size(); i++)
	{
		//ISV 只需传入groupno_和name_之一
		if ((fixedgrouplist[i].groupno_ == group.groupno_)
			|| (fixedgrouplist[i].name_ == group.name_))
		{
			fixedGroup.name_			= fixedgrouplist[i].name_;
			fixedGroup.id_				= fixedgrouplist[i].id_;
			fixedGroup.type_			= fixedgrouplist[i].type_;
			fixedGroup.readonly_		= fixedgrouplist[i].readonly_;
			fixedGroup.creator_			= fixedgrouplist[i].creator_;
			fixedGroup.uri_				= fixedgrouplist[i].uri_;
			fixedGroup.groupno_			= fixedgrouplist[i].groupno_;
			fixedGroup.desc_			= fixedgrouplist[i].desc_;
			fixedGroup.bulletin_		= fixedgrouplist[i].bulletin_;
			fixedGroup.owneruri_		= fixedgrouplist[i].owneruri_;
			fixedGroup.capacity_		= fixedgrouplist[i].capacity_;
			fixedGroup.needpermit_		= fixedgrouplist[i].needpermit_;

			DEBUG_LOG() << "--- LEAVE";
			return UCSDK_Succ;
		}
	}

	ERROR_LOG() << "Not found the fixed group for the search group list.";
	DEBUG_LOG() << "--- LEAVE";
	return UCSDK_Fail;
}

void UCGroupProxy::CopyUCSDKFixedGroupToFixedGroup(const UCSDKFixedGroup& group, uc::model::FixedGroup& fixedGroup)
{
	fixedGroup.name_			= group.name_;
	fixedGroup.id_				= group.id_;
	fixedGroup.type_			= group.type_;
	fixedGroup.readonly_		= group.readonly_;
	fixedGroup.creator_			= group.creator_;
	fixedGroup.uri_				= group.uri_;
	fixedGroup.groupno_			= group.groupno_;
	fixedGroup.desc_			= group.desc_;
	fixedGroup.bulletin_		= group.bulletin_;
	fixedGroup.owneruri_		= group.owneruri_;
	fixedGroup.capacity_		= group.capacity_;
	fixedGroup.needpermit_		= group.needpermit_;
}

void UCGroupProxy::CopyFixedGroupToUCSDKFixedGroup(const uc::model::FixedGroup& fixedGroup, UCSDKFixedGroup& group)
{
	group.name_					= fixedGroup.name_;
	group.id_					= fixedGroup.id_;
	group.type_					= fixedGroup.type_;
	group.readonly_				= fixedGroup.readonly_;
	group.creator_				= fixedGroup.creator_;
	group.uri_					= fixedGroup.uri_;
	group.groupno_				= fixedGroup.groupno_;
	group.desc_					= fixedGroup.desc_;
	group.bulletin_				= fixedGroup.bulletin_;
	group.owneruri_				= fixedGroup.owneruri_;
	group.capacity_				= fixedGroup.capacity_;
	group.needpermit_			= fixedGroup.needpermit_;
}

void UCGroupProxy::CopyUCSDKCustomGroupToCustomGroup(const UCSDKCustomGroup& group, uc::model::CustomGroup& customGroup)
{
	customGroup.name_			= group.name_;
	customGroup.id_				= group.id_;
	customGroup.type_			= group.type_;
	customGroup.readonly_		= group.readonly_;
	customGroup.indexno_		= group.indexno_;
}

void UCGroupProxy::CopyCustomGroupToUCSDKCustomGroup(const uc::model::CustomGroup& customGroup, UCSDKCustomGroup& group)
{
	group.name_					= customGroup.name_;
	group.id_					= customGroup.id_;
	group.type_					= customGroup.type_;
	group.readonly_				= customGroup.readonly_;
	group.indexno_				= customGroup.indexno_;
}

void UCGroupProxy::CopyUCSDKFavoriteGroupToFavoriteGroup(const UCSDKFavoriteGroup& group, uc::model::FavoriteGroup& favoriteGroup)
{
	favoriteGroup.name_			= group.name_;
	favoriteGroup.id_			= group.id_;
	favoriteGroup.type_			= group.type_;
	favoriteGroup.readonly_		= group.readonly_;
}

void UCGroupProxy::CopyFavoriteGroupToUCSDKFavoriteGroup(const uc::model::FavoriteGroup& favoriteGroup, UCSDKFavoriteGroup& group)
{
	group.name_					= favoriteGroup.name_;
	group.id_					= favoriteGroup.id_;
	group.type_					= favoriteGroup.type_;
	group.readonly_				= favoriteGroup.readonly_;
}

}
}
