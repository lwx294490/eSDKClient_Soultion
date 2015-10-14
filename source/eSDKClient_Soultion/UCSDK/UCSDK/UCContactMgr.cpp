#include "stdafx.h"
#include "UCContactMgr.h"
#include "UCContactMgrAbsProxy.h"
#include "UCStructCopy.h"
#include "eSDKLog.h"
#include "UCCommon.h"


#pragma comment(linker, "/EXPORT:GetAllContactlist=_GetAllContactlist@12")
#pragma comment(linker, "/EXPORT:GetContactByAccount=_GetContactByAccount@8")
#pragma comment(linker, "/EXPORT:GetContactById=_GetContactById@8")
#pragma comment(linker, "/EXPORT:GetContactByPhoneNum=_GetContactByPhoneNum@8")
#pragma comment(linker, "/EXPORT:GetContactByUri=_GetContactByUri@8")
#pragma comment(linker, "/EXPORT:HasContact=_HasContact@4")
#pragma comment(linker, "/EXPORT:RefreshContactByAccount=_RefreshContactByAccount@8")
#pragma comment(linker, "/EXPORT:RefreshContactById=_RefreshContactById@8")
#pragma comment(linker, "/EXPORT:RefreshContactByUri=_RefreshContactByUri@8")
#pragma comment(linker, "/EXPORT:RemoveContactById=_RemoveContactById@4")
#pragma comment(linker, "/EXPORT:SearchContact=_SearchContact@32")
#pragma comment(linker, "/EXPORT:Modify=_Modify@4")
#pragma comment(linker, "/EXPORT:GetHeadImagePath=_GetHeadImagePath@8")
#pragma comment(linker, "/EXPORT:MoveToGroup=_MoveToGroup@12")
#pragma comment(linker, "/EXPORT:AddToGroup=_AddToGroup@8")
#pragma comment(linker, "/EXPORT:RemoveFromGroup=_RemoveFromGroup@8")
#pragma comment(linker, "/EXPORT:CanStartSession=_CanStartSession@8")
#pragma comment(linker, "/EXPORT:CanMoveToGroup=_CanMoveToGroup@12")
#pragma comment(linker, "/EXPORT:GetCustomGroups=_GetCustomGroups@16")
#pragma comment(linker, "/EXPORT:IsFavourite=_IsFavourite@4")


int UCSDK_CALL GetAllContactlist(int iFrom, int iTo, UCContactList* memberList)
{
	DEBUG_LOG() << "--- ENTER";
	CHECK_POINTER(memberList, UC_InvalidParam);
	if (0 > iFrom || iFrom > iTo)
	{
		INFO_PARAM2(iFrom, iTo);
		ERROR_LOG() << "iFrom or iTo is Invaild praram";
		DEBUG_LOG() << "--- LEAVE";
		return UC_InvalidParam;
	}

	UCContactMgrAbsProxy* pUCContactMgrAbsProxy = UCContactMgrAbsProxy::GetInstance();
	CHECK_POINTER(pUCContactMgrAbsProxy, UC_NullPoint);

	UCSDKContactList contactlist;
	int iRet = pUCContactMgrAbsProxy->GetAllContactlist(contactlist);
	CHECK_RETURN(iRet, UC_Succ, "GetAllContactlist");

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
		UCStructCopy::Copy_UCContact(memberList->contact[i-iFrom], contactlist[(unsigned int)i]);
	}
	memberList->iFrom = iFrom;
	memberList->iTo = iEnd;
	memberList->iTotal = iTotalSize;

	DEBUG_LOG() << "--- LEAVE";
	return UC_Succ;
}

int UCSDK_CALL GetContactByAccount(const char* pAcc, UCContact* member)
{
	DEBUG_LOG() << "--- ENTER";
	CHECK_POINTER(member, UC_InvalidParam);
	CHECK_POINTER(pAcc, UC_InvalidParam);

	UCContactMgrAbsProxy* pUCContactMgrAbsProxy = UCContactMgrAbsProxy::GetInstance();
	CHECK_POINTER(pUCContactMgrAbsProxy, UC_NullPoint);

	UCSDKContact contact;
	int iRet = pUCContactMgrAbsProxy->GetContactByAccount(contact, pAcc);
	CHECK_RETURN(iRet, UC_Succ, "GetContactByAccount");

	UCStructCopy::Copy_UCContact(*member, contact);

	DEBUG_LOG() << "--- LEAVE";
	return UC_Succ;
}

int UCSDK_CALL GetContactById(const char* pId, UCContact* member)
{
	DEBUG_LOG() << "--- ENTER";
	CHECK_POINTER(member, UC_InvalidParam);
	CHECK_POINTER(pId, UC_InvalidParam);

	UCContactMgrAbsProxy* pUCContactMgrAbsProxy = UCContactMgrAbsProxy::GetInstance();
	CHECK_POINTER(pUCContactMgrAbsProxy, UC_NullPoint);

	UCSDKContact contact;
	int iRet = pUCContactMgrAbsProxy->GetContactById(contact, pId);
	CHECK_RETURN(iRet, UC_Succ, "GetContactById");

	UCStructCopy::Copy_UCContact(*member, contact);

	DEBUG_LOG() << "--- LEAVE";
	return UC_Succ;
}

int UCSDK_CALL GetContactByPhoneNum(const char* pPhoneNum, UCContact* member)
{
	DEBUG_LOG() << "--- ENTER";
	CHECK_POINTER(member, UC_InvalidParam);
	CHECK_POINTER(pPhoneNum, UC_InvalidParam);

	UCContactMgrAbsProxy* pUCContactMgrAbsProxy = UCContactMgrAbsProxy::GetInstance();
	CHECK_POINTER(pUCContactMgrAbsProxy, UC_NullPoint);

	UCSDKContact contact;
	int iRet = pUCContactMgrAbsProxy->GetContactByPhoneNum(contact, pPhoneNum);
	CHECK_RETURN(iRet, UC_Succ, "GetContactByPhoneNum");

	UCStructCopy::Copy_UCContact(*member, contact);

	DEBUG_LOG() << "--- LEAVE";
	return UC_Succ;
}

int UCSDK_CALL GetContactByUri(const char* pUri, UCContact* member)
{
	DEBUG_LOG() << "--- ENTER";
	CHECK_POINTER(member, UC_InvalidParam);
	CHECK_POINTER(pUri, UC_InvalidParam);

	UCContactMgrAbsProxy* pUCContactMgrAbsProxy = UCContactMgrAbsProxy::GetInstance();
	CHECK_POINTER(pUCContactMgrAbsProxy, UC_NullPoint);

	UCSDKContact contact;
	int iRet = pUCContactMgrAbsProxy->GetContactByUri(contact, pUri);
	CHECK_RETURN(iRet, UC_Succ, "GetContactByUri");

	UCStructCopy::Copy_UCContact(*member, contact);

	DEBUG_LOG() << "--- LEAVE";
	return UC_Succ;
}

int UCSDK_CALL HasContact(const char* pUri)
{
	DEBUG_LOG() << "--- ENTER";
	CHECK_POINTER(pUri, false);

	UCContactMgrAbsProxy* pUCContactMgrAbsProxy = UCContactMgrAbsProxy::GetInstance();
	CHECK_POINTER(pUCContactMgrAbsProxy, false);

	bool bRet = pUCContactMgrAbsProxy->HasContact(pUri);
	INFO_PARAM1(bRet);

	int iRet = UC_Fail;
	if (bRet)
	{
		iRet = UC_Succ;
	}

	DEBUG_LOG() << "--- LEAVE";
	return iRet;
}

int UCSDK_CALL RefreshContactByAccount(const char* pAcc, UCContact* member)
{
	DEBUG_LOG() << "--- ENTER";
	CHECK_POINTER(pAcc, UC_InvalidParam);
	CHECK_POINTER(member, UC_InvalidParam);

	UCContactMgrAbsProxy* pUCContactMgrAbsProxy = UCContactMgrAbsProxy::GetInstance();
	CHECK_POINTER(pUCContactMgrAbsProxy, UC_NullPoint);

	UCSDKContact contact;
	int iRet = pUCContactMgrAbsProxy->RefreshContactByAccount(pAcc, contact);
	CHECK_RETURN(iRet, UC_Succ, "RefreshContactByAccount");

	UCStructCopy::Copy_UCContact(*member, contact);

	DEBUG_LOG() << "--- LEAVE";
	return UC_Succ;
}

int UCSDK_CALL RefreshContactById(const char* pId, UCContact* member)
{
	DEBUG_LOG() << "--- ENTER";
	CHECK_POINTER(pId, UC_InvalidParam);
	CHECK_POINTER(member, UC_InvalidParam);

	UCContactMgrAbsProxy* pUCContactMgrAbsProxy = UCContactMgrAbsProxy::GetInstance();
	CHECK_POINTER(pUCContactMgrAbsProxy, UC_NullPoint);

	UCSDKContact contact;
	int iRet = pUCContactMgrAbsProxy->RefreshContactById(pId, contact);
	CHECK_RETURN(iRet, UC_Succ, "RefreshContactById");

	UCStructCopy::Copy_UCContact(*member, contact);

	DEBUG_LOG() << "--- LEAVE";
	return UC_Succ;
}

int UCSDK_CALL RefreshContactByUri(const char* pUri, UCContact* member)
{
	DEBUG_LOG() << "--- ENTER";
	CHECK_POINTER(pUri, UC_InvalidParam);
	CHECK_POINTER(member, UC_InvalidParam);

	UCContactMgrAbsProxy* pUCContactMgrAbsProxy = UCContactMgrAbsProxy::GetInstance();
	CHECK_POINTER(pUCContactMgrAbsProxy, UC_NullPoint);

	UCSDKContact contact;
	int iRet = pUCContactMgrAbsProxy->RefreshContactByUri(pUri, contact);
	CHECK_RETURN(iRet, UC_Succ, "RefreshContactByUri");

	UCStructCopy::Copy_UCContact(*member, contact);

	DEBUG_LOG() << "--- LEAVE";
	return UC_Succ;
}

int UCSDK_CALL RemoveContactById(const char* pId)
{
	DEBUG_LOG() << "--- ENTER";
	CHECK_POINTER(pId, UC_InvalidParam);

	UCContactMgrAbsProxy* pUCContactMgrAbsProxy = UCContactMgrAbsProxy::GetInstance();
	CHECK_POINTER(pUCContactMgrAbsProxy, UC_NullPoint);

	int iRet = pUCContactMgrAbsProxy->RemoveContactById(pId);
	CHECK_RETURN(iRet, UC_Succ, "RemoveContactById");

	DEBUG_LOG() << "--- LEAVE";
	return UC_Succ;
}

int UCSDK_CALL SearchContact(const char* condition, const char* deptid,
							 int querysubdept, int offset, int count, int ordertype, 
							 int* recamount, UCContactList* memberList)
{
	DEBUG_LOG() << "--- ENTER";
	CHECK_POINTER(memberList, UC_InvalidParam);
	CHECK_POINTER(condition, UC_InvalidParam);
	CHECK_POINTER(deptid, UC_InvalidParam);
	CHECK_POINTER(recamount, UC_InvalidParam);

	UCContactMgrAbsProxy* pUCContactMgrAbsProxy = UCContactMgrAbsProxy::GetInstance();
	CHECK_POINTER(pUCContactMgrAbsProxy, UC_NullPoint);

	bool querysub = true;
	if (0 == querysubdept)
	{
		querysub = false;
	}
	UCSDKContactList contactlist;
	int iRet = pUCContactMgrAbsProxy->SearchContact(contactlist, condition, deptid, querysub, offset, count, ordertype, *recamount);
	CHECK_RETURN(iRet, UC_Succ, "SearchContact");

	int iFoundCount = (int)contactlist.size();
	int iEnd = iFoundCount;
	if (iFoundCount > count)
	{
		WARN_LOG() << "contactlist's size is large than count.";
		iEnd = count;
	}
	for (int i=0; i<iEnd; i++)
	{
		UCStructCopy::Copy_UCContact(memberList->contact[i], contactlist[(unsigned int)i]);
	}
	memberList->iFrom = 0;
	memberList->iTo = iEnd-1;
	memberList->iTotal = iFoundCount;

	DEBUG_LOG() << "--- LEAVE";
	return UC_Succ;
}

int UCSDK_CALL Modify(const UCContact* member)
{
	DEBUG_LOG() << "--- ENTER";
	CHECK_POINTER(member, false);

	UCContactMgrAbsProxy* pUCContactMgrAbsProxy = UCContactMgrAbsProxy::GetInstance();
	CHECK_POINTER(pUCContactMgrAbsProxy, false);

	UCSDKContact contact;
	UCStructCopy::Copy_UCSDKContact(contact, *member);

	bool bRet = pUCContactMgrAbsProxy->Modify(contact);
	INFO_PARAM1(bRet);

	int iRet = UC_Fail;
	if (bRet)
	{
		iRet = UC_Succ;
	}

	DEBUG_LOG() << "--- LEAVE";
	return iRet;
}

int UCSDK_CALL GetHeadImagePath(const UCContact* member, char path[IMAGE_LENGTH])
{
	DEBUG_LOG() << "--- ENTER";
	CHECK_POINTER(path, UC_InvalidParam);
	CHECK_POINTER(member, UC_InvalidParam);

	UCContactMgrAbsProxy* pUCContactMgrAbsProxy = UCContactMgrAbsProxy::GetInstance();
	CHECK_POINTER(pUCContactMgrAbsProxy, UC_NullPoint);

	UCSDKContact contact;
	UCStructCopy::Copy_UCSDKContact(contact, *member);

	std::string sPath = pUCContactMgrAbsProxy->GetHeadImagePath(contact);
	if (sPath.empty())
	{
		ERROR_LOG() << "ImagePath is empty.";
		DEBUG_LOG() << "--- LEAVE";
		return UC_Fail;
	}

	UCStructCopy::UCMemCopy(path, sPath, IMAGE_LENGTH);

	DEBUG_LOG() << "--- LEAVE";
	return UC_Succ;
}

int UCSDK_CALL MoveToGroup(const UCContact* member, const UCGroup* _src, const UCGroup* _target)
{
	DEBUG_LOG() << "--- ENTER";
	CHECK_POINTER(member, UC_InvalidParam);
	CHECK_POINTER(_src, UC_InvalidParam);
	CHECK_POINTER(_target, UC_InvalidParam);

	UCContactMgrAbsProxy* pUCContactMgrAbsProxy = UCContactMgrAbsProxy::GetInstance();
	CHECK_POINTER(pUCContactMgrAbsProxy, UC_NullPoint);

	UCSDKContact contact;
	UCSDKGroup srcgroup;
	UCSDKGroup targetgroup;
	UCStructCopy::Copy_UCSDKContact(contact, *member);
	UCStructCopy::Copy_UCSDKGroup(srcgroup, *_src);
	UCStructCopy::Copy_UCSDKGroup(targetgroup, *_target);

	bool bRet = pUCContactMgrAbsProxy->MoveToGroup(contact, srcgroup, targetgroup);
	if (!bRet)
	{
		ERROR_LOG() << "MoveToGroup failed.";
		DEBUG_LOG() << "--- LEAVE";
		return UC_Fail;
	}

	DEBUG_LOG() << "--- LEAVE";
	return UC_Succ;
}

int UCSDK_CALL AddToGroup(const UCContact* member, const UCGroup* _target)
{
	DEBUG_LOG() << "--- ENTER";
	CHECK_POINTER(member, UC_InvalidParam);
	CHECK_POINTER(_target, UC_InvalidParam);

	UCContactMgrAbsProxy* pUCContactMgrAbsProxy = UCContactMgrAbsProxy::GetInstance();
	CHECK_POINTER(pUCContactMgrAbsProxy, UC_NullPoint);

	UCSDKContact contact;
	UCSDKGroup targetgroup;
	UCStructCopy::Copy_UCSDKContact(contact, *member);
	UCStructCopy::Copy_UCSDKGroup(targetgroup, *_target);

	bool bRet = pUCContactMgrAbsProxy->AddToGroup(contact, targetgroup);
	if (!bRet)
	{
		ERROR_LOG() << "AddToGroup failed.";
		DEBUG_LOG() << "--- LEAVE";
		return UC_Fail;
	}

	DEBUG_LOG() << "--- LEAVE";
	return UC_Succ;
}

int UCSDK_CALL RemoveFromGroup(const UCContact* member, const UCGroup* _target)
{
	DEBUG_LOG() << "--- ENTER";
	CHECK_POINTER(member, UC_InvalidParam);
	CHECK_POINTER(_target, UC_InvalidParam);

	UCContactMgrAbsProxy* pUCContactMgrAbsProxy = UCContactMgrAbsProxy::GetInstance();
	CHECK_POINTER(pUCContactMgrAbsProxy, UC_NullPoint);

	UCSDKContact contact;
	UCSDKGroup targetgroup;
	UCStructCopy::Copy_UCSDKContact(contact, *member);
	UCStructCopy::Copy_UCSDKGroup(targetgroup, *_target);

	bool bRet = pUCContactMgrAbsProxy->RemoveFromGroup(contact, targetgroup);
	if (!bRet)
	{
		ERROR_LOG() << "RemoveFromGroup failed.";
		DEBUG_LOG() << "--- LEAVE";
		return UC_Fail;
	}

	DEBUG_LOG() << "--- LEAVE";
	return UC_Succ;
}

int UCSDK_CALL CanStartSession(const UCContact* member, int _type)
{
	DEBUG_LOG() << "--- ENTER";
	CHECK_POINTER(member, false);

	UCContactMgrAbsProxy* pUCContactMgrAbsProxy = UCContactMgrAbsProxy::GetInstance();
	CHECK_POINTER(pUCContactMgrAbsProxy, false);

	UCSDKContact contact;
	UCStructCopy::Copy_UCSDKContact(contact, *member);

	bool bRet = pUCContactMgrAbsProxy->CanStartSession(contact, (SESSION_TYPE_E)_type);
	INFO_PARAM1(bRet);

	int iRet = UC_Fail;
	if (bRet)
	{
		iRet = UC_Succ;
	}

	DEBUG_LOG() << "--- LEAVE";
	return iRet;
}

int UCSDK_CALL CanMoveToGroup(const UCContact* member, const UCGroup* _src, const UCGroup* _target)
{
	DEBUG_LOG() << "--- ENTER";
	CHECK_POINTER(member, false);
	CHECK_POINTER(_src, false);
	CHECK_POINTER(_target, false);

	UCContactMgrAbsProxy* pUCContactMgrAbsProxy = UCContactMgrAbsProxy::GetInstance();
	CHECK_POINTER(pUCContactMgrAbsProxy, false);
	
	UCSDKContact contact;
	UCSDKGroup srcgroup;
	UCSDKGroup targetgroup;
	UCStructCopy::Copy_UCSDKContact(contact, *member);
	UCStructCopy::Copy_UCSDKGroup(srcgroup, *_src);
	UCStructCopy::Copy_UCSDKGroup(targetgroup, *_target);

	bool bRet = pUCContactMgrAbsProxy->CanMoveToGroup(contact, srcgroup, targetgroup);
	INFO_PARAM1(bRet);

	int iRet = UC_Fail;
	if (bRet)
	{
		iRet = UC_Succ;
	}

	DEBUG_LOG() << "--- LEAVE";
	return iRet;
}

int UCSDK_CALL GetCustomGroups(const UCContact* member, int iFrom, int iTo, UCCustomGroupList* _groups)
{
	DEBUG_LOG() << "--- ENTER";
	CHECK_POINTER(member, UC_InvalidParam);
	CHECK_POINTER(_groups, UC_InvalidParam);
	if (0 > iFrom || iFrom > iTo)
	{
		INFO_PARAM2(iFrom, iTo);
		ERROR_LOG() << "iFrom or iTo is Invaild praram";
		DEBUG_LOG() << "--- LEAVE";
		return UC_InvalidParam;
	}

	UCContactMgrAbsProxy* pUCContactMgrAbsProxy = UCContactMgrAbsProxy::GetInstance();
	CHECK_POINTER(pUCContactMgrAbsProxy, UC_NullPoint);

	UCSDKContact contact;
	UCSDKCustomGroupList customlist;
	UCStructCopy::Copy_UCSDKContact(contact, *member);

	int iRet = pUCContactMgrAbsProxy->GetCustomGroups(contact, customlist);
	CHECK_RETURN(iRet, UC_Succ, "GetCustomGroups");

	int iTotalSize = (int)customlist.size();
	if (iTotalSize > 0 && iFrom > iTotalSize - 1)
	{
		ERROR_LOG() << "iFrom is greater than the total size.";
		DEBUG_LOG() << "--- LEAVE";
		return UC_InvalidParam;
	}
	int iEnd = iTo < (iTotalSize - 1) ? iTo : (iTotalSize - 1);
	for (int i=iFrom; i<=iEnd; i++)
	{
		UCStructCopy::Copy_UCCustomGroup(_groups->group[i-iFrom], customlist[(unsigned int)i]);
	}
	_groups->iFrom = iFrom;
	_groups->iTo = iEnd;
	_groups->iTotal = iTotalSize;

	DEBUG_LOG() << "--- LEAVE";
	return UC_Succ;
}

int UCSDK_CALL IsFavourite(const UCContact* member)
{
	DEBUG_LOG() << "--- ENTER";
	CHECK_POINTER(member, false);

	UCContactMgrAbsProxy* pUCContactMgrAbsProxy = UCContactMgrAbsProxy::GetInstance();
	CHECK_POINTER(pUCContactMgrAbsProxy, false);

	UCSDKContact contact;
	UCStructCopy::Copy_UCSDKContact(contact, *member);

	bool bRet = pUCContactMgrAbsProxy->IsFavourite(contact);
	INFO_PARAM1(bRet);

	int iRet = UC_Fail;
	if (bRet)
	{
		iRet = UC_Succ;
	}

	DEBUG_LOG() << "--- LEAVE";
	return iRet;
}
