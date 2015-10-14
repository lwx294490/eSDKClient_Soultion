#include "stdafx.h"
#include "UCGroup.h"
#include "UCGroupAbsProxy.h"
#include "UCStructCopy.h"
#include "eSDKLog.h"
#include "UCCommon.h"


#pragma comment(linker, "/EXPORT:AddFixedGroup=_AddFixedGroup@4")
#pragma comment(linker, "/EXPORT:GetFixedGroupByID=_GetFixedGroupByID@8")
#pragma comment(linker, "/EXPORT:GetFixedGroupByUri=_GetFixedGroupByUri@8")
#pragma comment(linker, "/EXPORT:RemoveFixedGroup=_RemoveFixedGroup@4")
#pragma comment(linker, "/EXPORT:RefreshFixedGrouplist=_RefreshFixedGrouplist@12")
#pragma comment(linker, "/EXPORT:GetFixedGrouplist=_GetFixedGrouplist@12")
#pragma comment(linker, "/EXPORT:SearchFixedGroup=_SearchFixedGroup@20")
#pragma comment(linker, "/EXPORT:AddCustomGroup=_AddCustomGroup@4")
#pragma comment(linker, "/EXPORT:AddFavoriteGroup=_AddFavoriteGroup@4")
#pragma comment(linker, "/EXPORT:GetCustomGroupById=_GetCustomGroupById@8")
#pragma comment(linker, "/EXPORT:GetCustomGrouplist=_GetCustomGrouplist@12")
#pragma comment(linker, "/EXPORT:RemoveCustomGroup=_RemoveCustomGroup@4")
#pragma comment(linker, "/EXPORT:RemoveFavoriteGroup=_RemoveFavoriteGroup@4")
#pragma comment(linker, "/EXPORT:AddContactToFavoriteGroup=_AddContactToFavoriteGroup@8")
#pragma comment(linker, "/EXPORT:RemoveContactFromFavoriteGroup=_RemoveContactFromFavoriteGroup@8")
#pragma comment(linker, "/EXPORT:RenameToFavoriteGroup=_RenameToFavoriteGroup@8")
#pragma comment(linker, "/EXPORT:GetContactlistFromFavoriteGroup=_GetContactlistFromFavoriteGroup@16")
#pragma comment(linker, "/EXPORT:AddContactToCustomGroup=_AddContactToCustomGroup@8")
#pragma comment(linker, "/EXPORT:RemoveContactFromCustomGroup=_RemoveContactFromCustomGroup@8")
#pragma comment(linker, "/EXPORT:RenameToCustomGroup=_RenameToCustomGroup@8")
#pragma comment(linker, "/EXPORT:GetContactlistFromCustomGroup=_GetContactlistFromCustomGroup@16")
#pragma comment(linker, "/EXPORT:MoveUp=_MoveUp@4")
#pragma comment(linker, "/EXPORT:MoveDown=_MoveDown@4")
#pragma comment(linker, "/EXPORT:AddContactToFixedGroup=_AddContactToFixedGroup@8")
#pragma comment(linker, "/EXPORT:RemoveContactFromFixedGroup=_RemoveContactFromFixedGroup@8")
#pragma comment(linker, "/EXPORT:RenameToFixedGroup=_RenameToFixedGroup@8")
#pragma comment(linker, "/EXPORT:GetContactlistFromFixedGroup=_GetContactlistFromFixedGroup@16")
#pragma comment(linker, "/EXPORT:ChangeGroupInfo=_ChangeGroupInfo@4")
#pragma comment(linker, "/EXPORT:ChangeGroupOwner=_ChangeGroupOwner@8")
#pragma comment(linker, "/EXPORT:RefreshContactList=_RefreshContactList@16")
#pragma comment(linker, "/EXPORT:RefreshGroup=_RefreshGroup@4")
#pragma comment(linker, "/EXPORT:AcceptInvitation=_AcceptInvitation@4")
#pragma comment(linker, "/EXPORT:RejectInvitation=_RejectInvitation@4")
#pragma comment(linker, "/EXPORT:AcceptJoinReq=_AcceptJoinReq@8")
#pragma comment(linker, "/EXPORT:RejectJoinReq=_RejectJoinReq@8")


int UCSDK_CALL AddFixedGroup(UCFixedGroup* group)
{
	DEBUG_LOG() << "--- ENTER";
	CHECK_POINTER(group, UC_InvalidParam);

	UCGroupAbsProxy* pUCGroupAbsProxy = UCGroupAbsProxy::GetInstance();
	CHECK_POINTER(pUCGroupAbsProxy, UC_NullPoint);

	UCSDKFixedGroup fixedgroup;
	UCStructCopy::Copy_UCSDKFixedGroup(fixedgroup, *group);

	int iRet = pUCGroupAbsProxy->AddFixedGroup(fixedgroup);
	CHECK_RETURN(iRet, UC_Succ, "AddFixedGroup");

	UCStructCopy::Copy_UCFixedGroup(*group, fixedgroup);

	DEBUG_LOG() << "--- LEAVE";
	return UC_Succ;
}

int UCSDK_CALL GetFixedGroupByID(const char* pGId, UCFixedGroup* group)
{
	DEBUG_LOG() << "--- ENTER";
	CHECK_POINTER(group, UC_InvalidParam);
	CHECK_POINTER(pGId, UC_InvalidParam);

	UCGroupAbsProxy* pUCGroupAbsProxy = UCGroupAbsProxy::GetInstance();
	CHECK_POINTER(pUCGroupAbsProxy, UC_NullPoint);

	UCSDKFixedGroup fixedgroup;
	int iRet = pUCGroupAbsProxy->GetFixedGroupByID(fixedgroup, pGId);
	CHECK_RETURN(iRet, UC_Succ, "GetFixedGroupByID");

	UCStructCopy::Copy_UCFixedGroup(*group, fixedgroup);

	DEBUG_LOG() << "--- LEAVE";
	return UC_Succ;
}

int UCSDK_CALL GetFixedGroupByUri(const char* pGUri, UCFixedGroup* group)
{
	DEBUG_LOG() << "--- ENTER";
	CHECK_POINTER(group, UC_InvalidParam);
	CHECK_POINTER(pGUri, UC_InvalidParam);

	UCGroupAbsProxy* pUCGroupAbsProxy = UCGroupAbsProxy::GetInstance();
	CHECK_POINTER(pUCGroupAbsProxy, UC_NullPoint);

	UCSDKFixedGroup fixedgroup;
	int iRet = pUCGroupAbsProxy->GetFixedGroupByUri(fixedgroup, pGUri);
	CHECK_RETURN(iRet, UC_Succ, "GetFixedGroupByUri");

	UCStructCopy::Copy_UCFixedGroup(*group, fixedgroup);

	DEBUG_LOG() << "--- LEAVE";
	return UC_Succ;
}

int UCSDK_CALL RemoveFixedGroup(const UCFixedGroup* group)
{
	DEBUG_LOG() << "--- ENTER";
	CHECK_POINTER(group, UC_InvalidParam);

	UCGroupAbsProxy* pUCGroupAbsProxy = UCGroupAbsProxy::GetInstance();
	CHECK_POINTER(pUCGroupAbsProxy, UC_NullPoint);

	UCSDKFixedGroup fixedgroup;
	UCStructCopy::Copy_UCSDKFixedGroup(fixedgroup, *group);

	int iRet = pUCGroupAbsProxy->RemoveFixedGroup(fixedgroup);
	CHECK_RETURN(iRet, UC_Succ, "RemoveFixedGroup");

	DEBUG_LOG() << "--- LEAVE";
	return UC_Succ;
}

int UCSDK_CALL RefreshFixedGrouplist(int iFrom, int iTo, UCFixedGroupList* groupList)
{
	DEBUG_LOG() << "--- ENTER";
	CHECK_POINTER(groupList, UC_InvalidParam);
	if (0 > iFrom || iFrom > iTo)
	{
		INFO_PARAM2(iFrom, iTo);
		ERROR_LOG() << "iFrom or iTo is Invaild praram";
		DEBUG_LOG() << "--- LEAVE";
		return UC_InvalidParam;
	}

	UCGroupAbsProxy* pUCGroupAbsProxy = UCGroupAbsProxy::GetInstance();
	CHECK_POINTER(pUCGroupAbsProxy, UC_NullPoint);

	UCSDKFixedGroupList fixedgrouplist;
	int iRet = pUCGroupAbsProxy->RefreshFixedGrouplist(fixedgrouplist);
	CHECK_RETURN(iRet, UC_Succ, "RefreshFixedGrouplist");

	int iTotalSize = (int)fixedgrouplist.size();
	if (iTotalSize > 0 && iFrom > iTotalSize - 1)
	{
		ERROR_LOG() << "iFrom is greater than the total size.";
		DEBUG_LOG() << "--- LEAVE";
		return UC_InvalidParam;
	}
	int iEnd = iTo < (iTotalSize - 1) ? iTo : (iTotalSize - 1);
	for (int i=iFrom; i<=iEnd; i++)
	{
		UCStructCopy::Copy_UCFixedGroup(groupList->group[i-iFrom], fixedgrouplist[(unsigned int)i]);
	}
	groupList->iFrom = iFrom;
	groupList->iTo = iEnd;
	groupList->iTotal = iTotalSize;

	DEBUG_LOG() << "--- LEAVE";
	return UC_Succ;
}

int UCSDK_CALL GetFixedGrouplist(int iFrom, int iTo, UCFixedGroupList* groupList)
{
	DEBUG_LOG() << "--- ENTER";
	CHECK_POINTER(groupList, UC_InvalidParam);
	if (0 > iFrom || iFrom > iTo)
	{
		INFO_PARAM2(iFrom, iTo);
		ERROR_LOG() << "iFrom or iTo is Invaild praram";
		DEBUG_LOG() << "--- LEAVE";
		return UC_InvalidParam;
	}

	UCGroupAbsProxy* pUCGroupAbsProxy = UCGroupAbsProxy::GetInstance();
	CHECK_POINTER(pUCGroupAbsProxy, UC_NullPoint);

	UCSDKFixedGroupList fixedgrouplist;
	int iRet = pUCGroupAbsProxy->GetFixedGrouplist(fixedgrouplist);
	CHECK_RETURN(iRet, UC_Succ, "GetFixedGrouplist");

	int iTotalSize = (int)fixedgrouplist.size();
	if (iTotalSize > 0 && iFrom > iTotalSize - 1)
	{
		ERROR_LOG() << "iFrom is greater than the total size.";
		DEBUG_LOG() << "--- LEAVE";
		return UC_InvalidParam;
	}
	int iEnd = iTo < (iTotalSize - 1) ? iTo : (iTotalSize - 1);
	for (int i=iFrom; i<=iEnd; i++)
	{
		UCStructCopy::Copy_UCFixedGroup(groupList->group[i-iFrom], fixedgrouplist[(unsigned int)i]);
	}
	groupList->iFrom = iFrom;
	groupList->iTo = iEnd;
	groupList->iTotal = iTotalSize;

	DEBUG_LOG() << "--- LEAVE";
	return UC_Succ;
}

int UCSDK_CALL SearchFixedGroup(const char* groupNo, const char* groupName, int offset, int count,
								UCFixedGroupList* groupList)
{
	DEBUG_LOG() << "--- ENTER";
	CHECK_POINTER(groupList, UC_InvalidParam);
	CHECK_POINTER(groupNo, UC_InvalidParam);
	CHECK_POINTER(groupName, UC_InvalidParam);

	UCGroupAbsProxy* pUCGroupAbsProxy = UCGroupAbsProxy::GetInstance();
	CHECK_POINTER(pUCGroupAbsProxy, UC_NullPoint);

	UCSDKFixedGroupList fixedgrouplist;
	int iRet = pUCGroupAbsProxy->SearchFixedGroup(fixedgrouplist, groupNo, groupName, offset, count);
	CHECK_RETURN(iRet, UC_Succ, "SearchFixedGroup");

	int iFoundCount = (int)fixedgrouplist.size();
	if (iFoundCount > count)
	{
		WARN_LOG() << "fixedgrouplist's size is large than count.";
		iFoundCount = count;
	}

	for (int i=0; i<iFoundCount; i++)
	{
		UCStructCopy::Copy_UCFixedGroup(groupList->group[i], fixedgrouplist[(unsigned int)i]);
	}
	groupList->iFrom = 0;
	groupList->iTo = iFoundCount-1;
	groupList->iTotal = iFoundCount;

	DEBUG_LOG() << "--- LEAVE";
	return UC_Succ;
}

int UCSDK_CALL AddCustomGroup(UCCustomGroup* group)
{
	DEBUG_LOG() << "--- ENTER";
	CHECK_POINTER(group, UC_InvalidParam);

	UCGroupAbsProxy* pUCGroupAbsProxy = UCGroupAbsProxy::GetInstance();
	CHECK_POINTER(pUCGroupAbsProxy, UC_NullPoint);

	UCSDKCustomGroup customgroup;
	UCStructCopy::Copy_UCSDKCustomGroup(customgroup, *group);

	int iRet = pUCGroupAbsProxy->AddCustomGroup(customgroup);
	CHECK_RETURN(iRet, UC_Succ, "AddCustomGroup");

	UCStructCopy::Copy_UCCustomGroup(*group, customgroup);

	DEBUG_LOG() << "--- LEAVE";
	return UC_Succ;
}

int UCSDK_CALL AddFavoriteGroup(UCFavoriteGroup* group)
{
	DEBUG_LOG() << "--- ENTER";
	CHECK_POINTER(group, UC_InvalidParam);

	UCGroupAbsProxy* pUCGroupAbsProxy = UCGroupAbsProxy::GetInstance();
	CHECK_POINTER(pUCGroupAbsProxy, UC_NullPoint);

	UCSDKFavoriteGroup favoritegroup;
	UCStructCopy::Copy_UCSDKFavoriteGroup(favoritegroup, *group);

	int iRet = pUCGroupAbsProxy->AddFavoriteGroup(favoritegroup);
	CHECK_RETURN(iRet, UC_Succ, "AddFavoriteGroup");

	UCStructCopy::Copy_UCFavoriteGroup(*group, favoritegroup);

	DEBUG_LOG() << "--- LEAVE";
	return UC_Succ;
}

int UCSDK_CALL GetCustomGroupById(const char* pGId, UCCustomGroup* group)
{
	DEBUG_LOG() << "--- ENTER";
	CHECK_POINTER(group, UC_InvalidParam);
	CHECK_POINTER(pGId, UC_InvalidParam);

	UCGroupAbsProxy* pUCGroupAbsProxy = UCGroupAbsProxy::GetInstance();
	CHECK_POINTER(pUCGroupAbsProxy, UC_NullPoint);
	
	UCSDKCustomGroup customgroup;
	int iRet = pUCGroupAbsProxy->GetCustomGroupById(customgroup, pGId);
	CHECK_RETURN(iRet, UC_Succ, "GetCustomGroupById");

	UCStructCopy::Copy_UCCustomGroup(*group, customgroup);

	DEBUG_LOG() << "--- LEAVE";
	return UC_Succ;
}

int UCSDK_CALL GetCustomGrouplist(int iFrom, int iTo, UCCustomGroupList* groupList)
{
	DEBUG_LOG() << "--- ENTER";
	CHECK_POINTER(groupList, UC_InvalidParam);
	if (0 > iFrom || iFrom > iTo)
	{
		INFO_PARAM2(iFrom, iTo);
		ERROR_LOG() << "iFrom or iTo is Invaild praram";
		DEBUG_LOG() << "--- LEAVE";
		return UC_InvalidParam;
	}

	UCGroupAbsProxy* pUCGroupAbsProxy = UCGroupAbsProxy::GetInstance();
	CHECK_POINTER(pUCGroupAbsProxy, UC_NullPoint);

	UCSDKCustomGroupList customgrouplist;
	int iRet = pUCGroupAbsProxy->GetCustomGrouplist(customgrouplist);
	CHECK_RETURN(iRet, UC_Succ, "GetCustomGrouplist");

	int iTotalSize = (int)customgrouplist.size();
	if (iTotalSize > 0 && iFrom > iTotalSize - 1)
	{
		ERROR_LOG() << "iFrom is greater than the total size.";
		DEBUG_LOG() << "--- LEAVE";
		return UC_InvalidParam;
	}
	int iEnd = iTo < (iTotalSize - 1) ? iTo : (iTotalSize - 1);
	for (int i=iFrom; i<=iEnd; i++)
	{
		UCStructCopy::Copy_UCCustomGroup(groupList->group[i-iFrom], customgrouplist[(unsigned int)i]);
	}
	groupList->iFrom = iFrom;
	groupList->iTo = iEnd;
	groupList->iTotal = iTotalSize;

	DEBUG_LOG() << "--- LEAVE";
	return UC_Succ;
}

int UCSDK_CALL RemoveCustomGroup(const UCCustomGroup* group)
{
	DEBUG_LOG() << "--- ENTER";
	CHECK_POINTER(group, UC_InvalidParam);

	UCGroupAbsProxy* pUCGroupAbsProxy = UCGroupAbsProxy::GetInstance();
	CHECK_POINTER(pUCGroupAbsProxy, UC_NullPoint);

	UCSDKCustomGroup customgroup;
	UCStructCopy::Copy_UCSDKCustomGroup(customgroup, *group);

	int iRet = pUCGroupAbsProxy->RemoveCustomGroup(customgroup);
	CHECK_RETURN(iRet, UC_Succ, "RemoveCustomGroup");

	DEBUG_LOG() << "--- LEAVE";
	return UC_Succ;
}

int UCSDK_CALL RemoveFavoriteGroup(const UCFavoriteGroup* group)
{
	DEBUG_LOG() << "--- ENTER";
	CHECK_POINTER(group, UC_InvalidParam);

	UCGroupAbsProxy* pUCGroupAbsProxy = UCGroupAbsProxy::GetInstance();
	CHECK_POINTER(pUCGroupAbsProxy, UC_NullPoint);

	UCSDKFavoriteGroup favoritegroup;
	UCStructCopy::Copy_UCSDKFavoriteGroup(favoritegroup, *group);

	int iRet = pUCGroupAbsProxy->RemoveFavoriteGroup(favoritegroup);
	CHECK_RETURN(iRet, UC_Succ, "RemoveFavoriteGroup");

	DEBUG_LOG() << "--- LEAVE";
	return UC_Succ;
}

int UCSDK_CALL AddContactToFavoriteGroup(const UCFavoriteGroup* group, UCContact* _contact)
{
	DEBUG_LOG() << "--- ENTER";
	CHECK_POINTER(group, UC_InvalidParam);
	CHECK_POINTER(_contact, UC_InvalidParam);

	UCGroupAbsProxy* pUCGroupAbsProxy = UCGroupAbsProxy::GetInstance();
	CHECK_POINTER(pUCGroupAbsProxy, UC_NullPoint);

	UCSDKFavoriteGroup favoritegroup;
	UCSDKContact contact;
	UCStructCopy::Copy_UCSDKFavoriteGroup(favoritegroup, *group);
	UCStructCopy::Copy_UCSDKContact(contact, *_contact);

	int iRet = pUCGroupAbsProxy->AddContact(favoritegroup, contact);
	CHECK_RETURN(iRet, UC_Succ, "AddContact");

	UCStructCopy::Copy_UCContact(*_contact, contact);

	DEBUG_LOG() << "--- LEAVE";
	return UC_Succ;
}

int UCSDK_CALL RemoveContactFromFavoriteGroup(const UCFavoriteGroup* group, const UCContact* _contact)
{
	DEBUG_LOG() << "--- ENTER";
	CHECK_POINTER(group, UC_InvalidParam);
	CHECK_POINTER(_contact, UC_InvalidParam);

	UCGroupAbsProxy* pUCGroupAbsProxy = UCGroupAbsProxy::GetInstance();
	CHECK_POINTER(pUCGroupAbsProxy, UC_NullPoint);

	UCSDKFavoriteGroup favoritegroup;
	UCSDKContact contact;
	UCStructCopy::Copy_UCSDKFavoriteGroup(favoritegroup, *group);
	UCStructCopy::Copy_UCSDKContact(contact, *_contact);

	int iRet = pUCGroupAbsProxy->RemoveContact(favoritegroup, contact);
	CHECK_RETURN(iRet, UC_Succ, "RemoveContact");

	DEBUG_LOG() << "--- LEAVE";
	return UC_Succ;
}

int UCSDK_CALL RenameToFavoriteGroup(const UCFavoriteGroup* group, const char* _name)
{
	DEBUG_LOG() << "--- ENTER";
	CHECK_POINTER(group, UC_InvalidParam);
	CHECK_POINTER(_name, UC_InvalidParam);

	UCGroupAbsProxy* pUCGroupAbsProxy = UCGroupAbsProxy::GetInstance();
	CHECK_POINTER(pUCGroupAbsProxy, UC_NullPoint);

	UCSDKFavoriteGroup favoritegroup;
	UCStructCopy::Copy_UCSDKFavoriteGroup(favoritegroup, *group);

	int iRet = pUCGroupAbsProxy->Rename(favoritegroup, _name);
	CHECK_RETURN(iRet, UC_Succ, "Rename");

	DEBUG_LOG() << "--- LEAVE";
	return UC_Succ;
}

int UCSDK_CALL GetContactlistFromFavoriteGroup(const UCFavoriteGroup* group, int iFrom, int iTo, UCContactList* _contactlist)
{
	DEBUG_LOG() << "--- ENTER";
	CHECK_POINTER(group, UC_InvalidParam);
	CHECK_POINTER(_contactlist, UC_InvalidParam);
	if (0 > iFrom || iFrom > iTo)
	{
		INFO_PARAM2(iFrom, iTo);
		ERROR_LOG() << "iFrom or iTo is Invaild praram";
		DEBUG_LOG() << "--- LEAVE";
		return UC_InvalidParam;
	}

	UCGroupAbsProxy* pUCGroupAbsProxy = UCGroupAbsProxy::GetInstance();
	CHECK_POINTER(pUCGroupAbsProxy, UC_NullPoint);

	UCSDKFavoriteGroup favoritegroup;
	UCStructCopy::Copy_UCSDKFavoriteGroup(favoritegroup, *group);
	UCSDKContactList contactlist;

	int iRet = pUCGroupAbsProxy->GetContactlist(favoritegroup, contactlist);
	CHECK_RETURN(iRet, UC_Succ, "GetContactlist");

	int iTotalSize = (int)contactlist.size();
	if (iTotalSize > 0 && iFrom > iTotalSize - 1)
	{
		ERROR_LOG() << "iFrom is greater than the total size.";
		DEBUG_LOG() << "--- LEAVE";
		return UC_InvalidParam;
	}
	int iEnd = iTo < (iTotalSize - 1) ? iTo : (iTotalSize - 1);
	for (int i=iFrom; i<=iEnd; i++)
	{
		UCStructCopy::Copy_UCContact(_contactlist->contact[i-iFrom], contactlist[(unsigned int)i]);
	}
	_contactlist->iFrom = iFrom;
	_contactlist->iTo = iEnd;
	_contactlist->iTotal = iTotalSize;

	DEBUG_LOG() << "--- LEAVE";
	return UC_Succ;
}

int UCSDK_CALL AddContactToCustomGroup(const UCCustomGroup* group, UCContact* _contact)
{
	DEBUG_LOG() << "--- ENTER";
	CHECK_POINTER(group, UC_InvalidParam);
	CHECK_POINTER(_contact, UC_InvalidParam);

	UCGroupAbsProxy* pUCGroupAbsProxy = UCGroupAbsProxy::GetInstance();
	CHECK_POINTER(pUCGroupAbsProxy, UC_NullPoint);

	UCSDKCustomGroup customgroup;
	UCSDKContact contact;
	UCStructCopy::Copy_UCSDKCustomGroup(customgroup, *group);
	UCStructCopy::Copy_UCSDKContact(contact, *_contact);

	int iRet = pUCGroupAbsProxy->AddContact(customgroup, contact);
	CHECK_RETURN(iRet, UC_Succ, "AddContact");

	UCStructCopy::Copy_UCContact(*_contact, contact);

	DEBUG_LOG() << "--- LEAVE";
	return UC_Succ;
}

int UCSDK_CALL RemoveContactFromCustomGroup(const UCCustomGroup* group, const UCContact* _contact)
{
	DEBUG_LOG() << "--- ENTER";
	CHECK_POINTER(group, UC_InvalidParam);
	CHECK_POINTER(_contact, UC_InvalidParam);

	UCGroupAbsProxy* pUCGroupAbsProxy = UCGroupAbsProxy::GetInstance();
	CHECK_POINTER(pUCGroupAbsProxy, UC_NullPoint);

	UCSDKCustomGroup customgroup;
	UCSDKContact contact;
	UCStructCopy::Copy_UCSDKCustomGroup(customgroup, *group);
	UCStructCopy::Copy_UCSDKContact(contact, *_contact);

	int iRet = pUCGroupAbsProxy->RemoveContact(customgroup, contact);
	CHECK_RETURN(iRet, UC_Succ, "RemoveContact");

	DEBUG_LOG() << "--- LEAVE";
	return UC_Succ;
}

int UCSDK_CALL RenameToCustomGroup(const UCCustomGroup* group, const char* _name)
{
	DEBUG_LOG() << "--- ENTER";
	CHECK_POINTER(group, UC_InvalidParam);
	CHECK_POINTER(_name, UC_InvalidParam);

	UCGroupAbsProxy* pUCGroupAbsProxy = UCGroupAbsProxy::GetInstance();
	CHECK_POINTER(pUCGroupAbsProxy, UC_NullPoint);

	UCSDKCustomGroup customgroup;
	UCStructCopy::Copy_UCSDKCustomGroup(customgroup, *group);

	int iRet = pUCGroupAbsProxy->Rename(customgroup, _name);
	CHECK_RETURN(iRet, UC_Succ, "Rename");

	DEBUG_LOG() << "--- LEAVE";
	return UC_Succ;
}

int UCSDK_CALL GetContactlistFromCustomGroup(const UCCustomGroup* group, int iFrom, int iTo, UCContactList* _contactlist)
{
	DEBUG_LOG() << "--- ENTER";
	CHECK_POINTER(group, UC_InvalidParam);
	CHECK_POINTER(_contactlist, UC_InvalidParam);
	if (0 > iFrom || iFrom > iTo)
	{
		INFO_PARAM2(iFrom, iTo);
		ERROR_LOG() << "iFrom or iTo is Invaild praram";
		DEBUG_LOG() << "--- LEAVE";
		return UC_InvalidParam;
	}

	UCGroupAbsProxy* pUCGroupAbsProxy = UCGroupAbsProxy::GetInstance();
	CHECK_POINTER(pUCGroupAbsProxy, UC_NullPoint);

	UCSDKCustomGroup customgroup;
	UCStructCopy::Copy_UCSDKCustomGroup(customgroup, *group);
	UCSDKContactList contactlist;

	int iRet = pUCGroupAbsProxy->GetContactlist(customgroup, contactlist);
	CHECK_RETURN(iRet, UC_Succ, "GetContactlist");

	int iTotalSize = (int)contactlist.size();
	if (iTotalSize > 0 && iFrom > iTotalSize - 1)
	{
		ERROR_LOG() << "iFrom is greater than the total size.";
		DEBUG_LOG() << "--- LEAVE";
		return UC_InvalidParam;
	}
	int iEnd = iTo < (iTotalSize - 1) ? iTo : (iTotalSize - 1);
	for (int i=iFrom; i<=iEnd; i++)
	{
		UCStructCopy::Copy_UCContact(_contactlist->contact[i-iFrom], contactlist[(unsigned int)i]);
	}
	_contactlist->iFrom = iFrom;
	_contactlist->iTo = iEnd;
	_contactlist->iTotal = iTotalSize;

	DEBUG_LOG() << "--- LEAVE";
	return UC_Succ;
}

int UCSDK_CALL MoveUp(const UCCustomGroup* group)
{
	DEBUG_LOG() << "--- ENTER";
	CHECK_POINTER(group, UC_InvalidParam);

	UCGroupAbsProxy* pUCGroupAbsProxy = UCGroupAbsProxy::GetInstance();
	CHECK_POINTER(pUCGroupAbsProxy, UC_NullPoint);

	UCSDKCustomGroup customgroup;
	UCStructCopy::Copy_UCSDKCustomGroup(customgroup, *group);

	int iRet = pUCGroupAbsProxy->MoveUp(customgroup);
	CHECK_RETURN(iRet, UC_Succ, "MoveUp");

	DEBUG_LOG() << "--- LEAVE";
	return UC_Succ;
}

int UCSDK_CALL MoveDown(const UCCustomGroup* group)
{
	DEBUG_LOG() << "--- ENTER";
	CHECK_POINTER(group, UC_InvalidParam);

	UCGroupAbsProxy* pUCGroupAbsProxy = UCGroupAbsProxy::GetInstance();
	CHECK_POINTER(pUCGroupAbsProxy, UC_NullPoint);

	UCSDKCustomGroup customgroup;
	UCStructCopy::Copy_UCSDKCustomGroup(customgroup, *group);

	int iRet = pUCGroupAbsProxy->MoveDown(customgroup);
	CHECK_RETURN(iRet, UC_Succ, "MoveDown");

	DEBUG_LOG() << "--- LEAVE";
	return UC_Succ;
}

int UCSDK_CALL AddContactToFixedGroup(const UCFixedGroup* group, UCContact* _contact)
{
	DEBUG_LOG() << "--- ENTER";
	CHECK_POINTER(group, UC_InvalidParam);
	CHECK_POINTER(_contact, UC_InvalidParam);

	UCGroupAbsProxy* pUCGroupAbsProxy = UCGroupAbsProxy::GetInstance();
	CHECK_POINTER(pUCGroupAbsProxy, UC_NullPoint);

	UCSDKFixedGroup fixedgroup;
	UCSDKContact contact;
	UCStructCopy::Copy_UCSDKFixedGroup(fixedgroup, *group);
	UCStructCopy::Copy_UCSDKContact(contact, *_contact);

	int iRet = pUCGroupAbsProxy->AddContact(fixedgroup, contact);
	CHECK_RETURN(iRet, UC_Succ, "AddContact");

	UCStructCopy::Copy_UCContact(*_contact, contact);

	DEBUG_LOG() << "--- LEAVE";
	return UC_Succ;
}

int UCSDK_CALL RemoveContactFromFixedGroup(const UCFixedGroup* group, const UCContact* _contact)
{
	DEBUG_LOG() << "--- ENTER";
	CHECK_POINTER(group, UC_InvalidParam);
	CHECK_POINTER(_contact, UC_InvalidParam);

	UCGroupAbsProxy* pUCGroupAbsProxy = UCGroupAbsProxy::GetInstance();
	CHECK_POINTER(pUCGroupAbsProxy, UC_NullPoint);

	UCSDKFixedGroup fixedgroup;
	UCSDKContact contact;
	UCStructCopy::Copy_UCSDKFixedGroup(fixedgroup, *group);
	UCStructCopy::Copy_UCSDKContact(contact, *_contact);

	int iRet = pUCGroupAbsProxy->RemoveContact(fixedgroup, contact);
	CHECK_RETURN(iRet, UC_Succ, "RemoveContact");

	DEBUG_LOG() << "--- LEAVE";
	return UC_Succ;
}

int UCSDK_CALL RenameToFixedGroup(const UCFixedGroup* group, const char* _name)
{
	DEBUG_LOG() << "--- ENTER";
	CHECK_POINTER(group, UC_InvalidParam);
	CHECK_POINTER(_name, UC_InvalidParam);

	UCGroupAbsProxy* pUCGroupAbsProxy = UCGroupAbsProxy::GetInstance();
	CHECK_POINTER(pUCGroupAbsProxy, UC_NullPoint);

	UCSDKFixedGroup fixedgroup;
	UCStructCopy::Copy_UCSDKFixedGroup(fixedgroup, *group);

	int iRet = pUCGroupAbsProxy->Rename(fixedgroup, _name);
	CHECK_RETURN(iRet, UC_Succ, "Rename");

	DEBUG_LOG() << "--- LEAVE";
	return UC_Succ;
}

int UCSDK_CALL GetContactlistFromFixedGroup(const UCFixedGroup* group, int iFrom, int iTo, UCContactList* _contactlist)
{
	DEBUG_LOG() << "--- ENTER";
	CHECK_POINTER(group, UC_InvalidParam);
	CHECK_POINTER(_contactlist, UC_InvalidParam);
	if (0 > iFrom || iFrom > iTo)
	{
		INFO_PARAM2(iFrom, iTo);
		ERROR_LOG() << "iFrom or iTo is Invaild praram";
		DEBUG_LOG() << "--- LEAVE";
		return UC_InvalidParam;
	}

	UCGroupAbsProxy* pUCGroupAbsProxy = UCGroupAbsProxy::GetInstance();
	CHECK_POINTER(pUCGroupAbsProxy, UC_NullPoint);

	UCSDKFixedGroup fixedgroup;
	UCStructCopy::Copy_UCSDKFixedGroup(fixedgroup, *group);
	UCSDKContactList contactlist;

	int iRet = pUCGroupAbsProxy->GetContactlist(fixedgroup, contactlist);
	CHECK_RETURN(iRet, UC_Succ, "GetContactlist");

	int iTotalSize = (int)contactlist.size();
	if (iTotalSize > 0 && iFrom > iTotalSize - 1)
	{
		ERROR_LOG() << "iFrom is greater than the total size.";
		DEBUG_LOG() << "--- LEAVE";
		return UC_InvalidParam;
	}
	int iEnd = iTo < (iTotalSize - 1) ? iTo : (iTotalSize - 1);
	for (int i=iFrom; i<=iEnd; i++)
	{
		UCStructCopy::Copy_UCContact(_contactlist->contact[i-iFrom], contactlist[(unsigned int)i]);
	}
	_contactlist->iFrom = iFrom;
	_contactlist->iTo = iEnd;
	_contactlist->iTotal = iTotalSize;

	DEBUG_LOG() << "--- LEAVE";
	return UC_Succ;
}

int UCSDK_CALL ChangeGroupInfo(const UCFixedGroup* group)
{
	DEBUG_LOG() << "--- ENTER";
	CHECK_POINTER(group, UC_InvalidParam);

	UCGroupAbsProxy* pUCGroupAbsProxy = UCGroupAbsProxy::GetInstance();
	CHECK_POINTER(pUCGroupAbsProxy, UC_NullPoint);

	UCSDKFixedGroup fixedgroup;
	UCStructCopy::Copy_UCSDKFixedGroup(fixedgroup, *group);

	int iRet = pUCGroupAbsProxy->ChangeGroupInfo(fixedgroup);
	CHECK_RETURN(iRet, UC_Succ, "ChangeGroupInfo");

	DEBUG_LOG() << "--- LEAVE";
	return UC_Succ;
}

int UCSDK_CALL ChangeGroupOwner(const UCFixedGroup* group, const UCContact* _owner)
{
	DEBUG_LOG() << "--- ENTER";
	CHECK_POINTER(group, UC_InvalidParam);
	CHECK_POINTER(_owner, UC_InvalidParam);

	UCGroupAbsProxy* pUCGroupAbsProxy = UCGroupAbsProxy::GetInstance();
	CHECK_POINTER(pUCGroupAbsProxy, UC_NullPoint);

	UCSDKFixedGroup fixedgroup;
	UCSDKContact contact;
	UCStructCopy::Copy_UCSDKFixedGroup(fixedgroup, *group);
	UCStructCopy::Copy_UCSDKContact(contact, *_owner);

	int iRet = pUCGroupAbsProxy->ChangeGroupOwner(fixedgroup, contact);
	CHECK_RETURN(iRet, UC_Succ, "ChangeGroupInfo");

	DEBUG_LOG() << "--- LEAVE";
	return UC_Succ;
}

int UCSDK_CALL RefreshContactList(const UCFixedGroup* group, int iFrom, int iTo, UCContactList* _contactlist)
{
	DEBUG_LOG() << "--- ENTER";
	CHECK_POINTER(group, UC_InvalidParam);
	CHECK_POINTER(_contactlist, UC_InvalidParam);
	if (0 > iFrom || iFrom > iTo)
	{
		INFO_PARAM2(iFrom, iTo);
		ERROR_LOG() << "iFrom or iTo is Invaild praram";
		DEBUG_LOG() << "--- LEAVE";
		return UC_InvalidParam;
	}

	UCGroupAbsProxy* pUCGroupAbsProxy = UCGroupAbsProxy::GetInstance();
	CHECK_POINTER(pUCGroupAbsProxy, UC_NullPoint);

	UCSDKFixedGroup fixedgroup;
	UCSDKContactList contactlist;
	UCStructCopy::Copy_UCSDKFixedGroup(fixedgroup, *group);

	int iRet = pUCGroupAbsProxy->Refresh(fixedgroup, contactlist);
	CHECK_RETURN(iRet, UC_Succ, "Refresh");

	int iTotalSize = (int)contactlist.size();
	if (iTotalSize > 0 && iFrom > iTotalSize - 1)
	{
		ERROR_LOG() << "iFrom is greater than the total size.";
		DEBUG_LOG() << "--- LEAVE";
		return UC_InvalidParam;
	}
	int iEnd = iTo < (iTotalSize - 1) ? iTo : (iTotalSize - 1);
	for (int i=iFrom; i<=iEnd; i++)
	{
		UCStructCopy::Copy_UCContact(_contactlist->contact[i-iFrom], contactlist[(unsigned int)i]);
	}
	_contactlist->iFrom = iFrom;
	_contactlist->iTo = iEnd;
	_contactlist->iTotal = iTotalSize;

	DEBUG_LOG() << "--- LEAVE";
	return UC_Succ;
}

int UCSDK_CALL RefreshGroup(const UCFixedGroup* group)
{
	DEBUG_LOG() << "--- ENTER";
	CHECK_POINTER(group, UC_InvalidParam);

	UCGroupAbsProxy* pUCGroupAbsProxy = UCGroupAbsProxy::GetInstance();
	CHECK_POINTER(pUCGroupAbsProxy, UC_NullPoint);

	UCSDKFixedGroup fixedgroup;
	UCStructCopy::Copy_UCSDKFixedGroup(fixedgroup, *group);

	int iRet = pUCGroupAbsProxy->Refresh(fixedgroup);
	CHECK_RETURN(iRet, UC_Succ, "Refresh");

	DEBUG_LOG() << "--- LEAVE";
	return UC_Succ;
}

int UCSDK_CALL AcceptInvitation(const UCFixedGroup* group)
{
	DEBUG_LOG() << "--- ENTER";
	CHECK_POINTER(group, UC_InvalidParam);

	UCGroupAbsProxy* pUCGroupAbsProxy = UCGroupAbsProxy::GetInstance();
	CHECK_POINTER(pUCGroupAbsProxy, UC_NullPoint);

	UCSDKFixedGroup fixedgroup;
	UCStructCopy::Copy_UCSDKFixedGroup(fixedgroup, *group);

	int iRet = pUCGroupAbsProxy->AcceptInvitation(fixedgroup);
	CHECK_RETURN(iRet, UC_Succ, "AcceptInvitation");

	DEBUG_LOG() << "--- LEAVE";
	return UC_Succ;
}

int UCSDK_CALL RejectInvitation(const UCFixedGroup* group)
{
	DEBUG_LOG() << "--- ENTER";
	CHECK_POINTER(group, UC_InvalidParam);

	UCGroupAbsProxy* pUCGroupAbsProxy = UCGroupAbsProxy::GetInstance();
	CHECK_POINTER(pUCGroupAbsProxy, UC_NullPoint);

	UCSDKFixedGroup fixedgroup;
	UCStructCopy::Copy_UCSDKFixedGroup(fixedgroup, *group);

	int iRet = pUCGroupAbsProxy->RejectInvitation(fixedgroup);
	CHECK_RETURN(iRet, UC_Succ, "RejectInvitation");

	DEBUG_LOG() << "--- LEAVE";
	return UC_Succ;
}

int UCSDK_CALL AcceptJoinReq(const UCFixedGroup* group, const UCContact* _contact)
{
	DEBUG_LOG() << "--- ENTER";
	CHECK_POINTER(group, UC_InvalidParam);
	CHECK_POINTER(_contact, UC_InvalidParam);

	UCGroupAbsProxy* pUCGroupAbsProxy = UCGroupAbsProxy::GetInstance();
	CHECK_POINTER(pUCGroupAbsProxy, UC_NullPoint);

	UCSDKFixedGroup fixedgroup;
	UCSDKContact contact;
	UCStructCopy::Copy_UCSDKFixedGroup(fixedgroup, *group);
	UCStructCopy::Copy_UCSDKContact(contact, *_contact);

	int iRet = pUCGroupAbsProxy->AcceptJoinReq(fixedgroup, contact);
	CHECK_RETURN(iRet, UC_Succ, "AcceptJoinReq");

	DEBUG_LOG() << "--- LEAVE";
	return UC_Succ;
}

int UCSDK_CALL RejectJoinReq(const UCFixedGroup* group, const UCContact* _contact)
{
	DEBUG_LOG() << "--- ENTER";
	CHECK_POINTER(group, UC_InvalidParam);
	CHECK_POINTER(_contact, UC_InvalidParam);

	UCGroupAbsProxy* pUCGroupAbsProxy = UCGroupAbsProxy::GetInstance();
	CHECK_POINTER(pUCGroupAbsProxy, UC_NullPoint);

	UCSDKFixedGroup fixedgroup;
	UCSDKContact contact;
	UCStructCopy::Copy_UCSDKFixedGroup(fixedgroup, *group);
	UCStructCopy::Copy_UCSDKContact(contact, *_contact);

	int iRet = pUCGroupAbsProxy->RejectJoinReq(fixedgroup, contact);
	CHECK_RETURN(iRet, UC_Succ, "RejectJoinReq");

	DEBUG_LOG() << "--- LEAVE";
	return UC_Succ;
}
