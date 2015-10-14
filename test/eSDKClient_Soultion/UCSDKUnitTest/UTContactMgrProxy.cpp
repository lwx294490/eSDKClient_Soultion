#include "stdafx.h"
#include "ctk/mt/thread.h"
#include "UTContactMgrProxy.h"

CPPUNIT_TEST_SUITE_NAMED_REGISTRATION(UTContactMgrAbsProxy, "UCSDKUnitTest");

int UTContactMgrAbsProxy::m_iSignFlag = -1;
UTContactMgrAbsProxy::UTContactMgrAbsProxy()
{

}

UTContactMgrAbsProxy::~UTContactMgrAbsProxy()
{

}

void UTContactMgrAbsProxy::setUp()
{
	UCSDKAbsProxy::GetInstance()->Init();
	UCSDKAbsProxy::GetInstance()->Config("10.170.103.52:8081");
	UCSDKAbsProxy::GetInstance()->SetLang("Chinese");
	
	//UCSignalRecvAbsProxy::GetInstance()->OnClientSignInNotify(TurnOnClientSignInNotify);
	
	UTSignIn();
}

void UTContactMgrAbsProxy::tearDown()
{
	UTSignOut();


	
	ctk::sleep(1000);
}

//²âÊÔÓÃÀý
void UTContactMgrAbsProxy::UTContactMgrAbsProxy_GetContactById()
{
	RemoveContact();
	UCSDKContactList memberList;
	int iRet = UCContactMgrAbsProxy::GetInstance()->GetAllContactlist(memberList);
	CPPUNIT_ASSERT_MESSAGE("GetAllContactlist", UCSDK_Succ == iRet);
	CPPUNIT_ASSERT_MESSAGE("GetAllContactlist", 1 == memberList.size());
	
	UCSDKContactList::iterator iter_b = memberList.begin();
	UCSDKContactList::iterator iter_e = memberList.end();
	for (; iter_b != iter_e; iter_b++)
	{
		UCSDKContact member;

		iRet = UCContactMgrAbsProxy::GetInstance()->GetContactById(member,(*iter_b).id_);
		CPPUNIT_ASSERT_MESSAGE("GetContactById", UCSDK_Succ == iRet);
		CPPUNIT_ASSERT_MESSAGE("GetContactById", ((member.id_ == (*iter_b).id_) && (member.uri_ == (*iter_b).uri_) && (member.ucAcc_ == (*iter_b).ucAcc_)));
		
	}	
}

//²âÊÔÓÃÀý
void UTContactMgrAbsProxy::UTContactMgrAbsProxy_GetContactByAccount()
{
	RemoveContact();
	UCSDKContactList memberList;
	int iRet = UCContactMgrAbsProxy::GetInstance()->GetAllContactlist(memberList);
	CPPUNIT_ASSERT_MESSAGE("GetAllContactlist", UCSDK_Succ == iRet);
	CPPUNIT_ASSERT_MESSAGE("GetAllContactlist", 1 == memberList.size());

	UCSDKContactList::iterator iter_b = memberList.begin();
	UCSDKContactList::iterator iter_e = memberList.end();
	for (; iter_b != iter_e; iter_b++)
	{
		UCSDKContact member;

		iRet = UCContactMgrAbsProxy::GetInstance()->GetContactByAccount(member, (*iter_b).ucAcc_);
		CPPUNIT_ASSERT_MESSAGE("GetContactByAccount", UCSDK_Succ == iRet);
		CPPUNIT_ASSERT_MESSAGE("GetContactByAccount", ((member.uri_ == (*iter_b).uri_) && (member.ucAcc_ == (*iter_b).ucAcc_)));

	}	
}

//²âÊÔÓÃÀý
void UTContactMgrAbsProxy::UTContactMgrAbsProxy_GetContactByPhoneNum()
{
	RemoveContact();
	UCSDKContactList memberList;
	int iRet = UCContactMgrAbsProxy::GetInstance()->GetAllContactlist(memberList);
	CPPUNIT_ASSERT_MESSAGE("GetAllContactlist", UCSDK_Succ == iRet);
	CPPUNIT_ASSERT_MESSAGE("GetAllContactlist", 1 == memberList.size());

	UCSDKContactList::iterator iter_b = memberList.begin();
	UCSDKContactList::iterator iter_e = memberList.end();
	for (; iter_b != iter_e; iter_b++)
	{
		UCSDKContact member;

		iRet = UCContactMgrAbsProxy::GetInstance()->GetContactByPhoneNum(member, (*iter_b).homePhone_);
		CPPUNIT_ASSERT_MESSAGE("GetContactByPhoneNum", UCSDK_Succ == iRet);
		CPPUNIT_ASSERT_MESSAGE("GetContactByPhoneNum", ((member.uri_ == (*iter_b).uri_) && (member.ucAcc_ == (*iter_b).ucAcc_)));

	}	
}

//²âÊÔÓÃÀý
void UTContactMgrAbsProxy::UTContactMgrAbsProxy_GetContactByUri()
{
	RemoveContact();
	UCSDKContactList memberList;
	int iRet = UCContactMgrAbsProxy::GetInstance()->GetAllContactlist(memberList);
	CPPUNIT_ASSERT_MESSAGE("GetAllContactlist", UCSDK_Succ == iRet);
	CPPUNIT_ASSERT_MESSAGE("GetAllContactlist", 1 == memberList.size());

	UCSDKContactList::iterator iter_b = memberList.begin();
	UCSDKContactList::iterator iter_e = memberList.end();
	for (; iter_b != iter_e; iter_b++)
	{
		UCSDKContact member;

		iRet = UCContactMgrAbsProxy::GetInstance()->GetContactByUri(member, (*iter_b).uri_);
		CPPUNIT_ASSERT_MESSAGE("GetContactByUri", UCSDK_Succ == iRet);
		CPPUNIT_ASSERT_MESSAGE("GetContactByUri", ((member.uri_ == (*iter_b).uri_) && (member.ucAcc_ == (*iter_b).ucAcc_)));

	}	
}

//²âÊÔÓÃÀý
void UTContactMgrAbsProxy::UTContactMgrAbsProxy_HasContact()
{
	RemoveContact();
	UCSDKContactList memberList;
	int iRet = UCContactMgrAbsProxy::GetInstance()->GetAllContactlist(memberList);
	CPPUNIT_ASSERT_MESSAGE("GetAllContactlist", UCSDK_Succ == iRet);
	CPPUNIT_ASSERT_MESSAGE("GetAllContactlist", 1 == memberList.size());

	UCSDKContactList::iterator iter_b = memberList.begin();
	UCSDKContactList::iterator iter_e = memberList.end();
	for (; iter_b != iter_e; iter_b++)
	{		
		bool bRet = UCContactMgrAbsProxy::GetInstance()->HasContact((*iter_b).uri_);
		CPPUNIT_ASSERT_MESSAGE("HasContact", true == bRet);		
	}

	memberList.clear();
	const int PAGE_SIZE = 2;
	int recamount = 0;
	iRet = UCContactMgrAbsProxy::GetInstance()->SearchContact(memberList,"fjj20", "", true, 0, PAGE_SIZE, 0, recamount);
	CPPUNIT_ASSERT_MESSAGE("SearchContact", UCSDK_Succ == iRet);
	CPPUNIT_ASSERT_MESSAGE("SearchContact", 1 == memberList.size());
	
	iter_b = memberList.begin();
	iter_e = memberList.end();
	for (; iter_b != iter_e; iter_b++)
	{		
		bool bRet = UCContactMgrAbsProxy::GetInstance()->HasContact((*iter_b).uri_);
		CPPUNIT_ASSERT_MESSAGE("HasContact", false == bRet);		
	}	
}
#if 1
//²âÊÔÓÃÀý
void UTContactMgrAbsProxy::UTContactMgrAbsProxy_RefreshContactByAccount()
{
	RemoveContact();
	UCSDKCustomGroup group;
	group.name_ = "UTgroup1";
	int iRet = UCGroupAbsProxy::GetInstance()->AddCustomGroup(group);
	CPPUNIT_ASSERT_MESSAGE("AddCustomGroup", UCSDK_Succ == iRet);

	UCSDKContactList memberList;
	const int PAGE_SIZE = 2;
	int recamount = 0;
	iRet = UCContactMgrAbsProxy::GetInstance()->SearchContact(memberList,"fjj20", "", true, 0, PAGE_SIZE, 0, recamount);
	CPPUNIT_ASSERT_MESSAGE("SearchContact", UCSDK_Succ == iRet);
	CPPUNIT_ASSERT_MESSAGE("SearchContact", 1 == memberList.size());
	
	iRet = UCGroupAbsProxy::GetInstance()->AddContact(group, memberList.at(0));
	CPPUNIT_ASSERT_MESSAGE("AddContact", UCSDK_Succ == iRet);

	UCSDKContact member;
	iRet = UCContactMgrAbsProxy::GetInstance()->RefreshContactByAccount(memberList.at(0).ucAcc_, member);
	CPPUNIT_ASSERT_MESSAGE("RefreshContactByAccount", UCSDK_Succ == iRet);
	
	UCSDKContactList allList;
	iRet = UCContactMgrAbsProxy::GetInstance()->GetAllContactlist(allList);
	CPPUNIT_ASSERT_MESSAGE("GetAllContactlist", UCSDK_Succ == iRet);
	
	iRet = UCGroupAbsProxy::GetInstance()->RemoveContact(group, memberList.at(0));
	CPPUNIT_ASSERT_MESSAGE("RemoveContact", UCSDK_Succ == iRet);
	
	UCSDKContactList allList1;
	iRet = UCContactMgrAbsProxy::GetInstance()->GetAllContactlist(allList1);
	CPPUNIT_ASSERT_MESSAGE("GetAllContactlist", UCSDK_Succ == iRet);
	CPPUNIT_ASSERT_MESSAGE("GetAllContactlist", allList.size() == (allList1.size() + 1));

	iRet = UCGroupAbsProxy::GetInstance()->RemoveCustomGroup(group);
	CPPUNIT_ASSERT_MESSAGE("RemoveCustomGroup", UCSDK_Succ == iRet);
}

#endif
#if 1
//²âÊÔÓÃÀý
void UTContactMgrAbsProxy::UTContactMgrAbsProxy_RefreshContactByUri()
{
	RemoveContact();
	UCSDKCustomGroup group;
	group.name_ = "UTgroup1";
	int iRet = UCGroupAbsProxy::GetInstance()->AddCustomGroup(group);
	CPPUNIT_ASSERT_MESSAGE("AddCustomGroup", UCSDK_Succ == iRet);

	UCSDKContactList memberList;
	const int PAGE_SIZE = 2;
	int recamount = 0;
	iRet = UCContactMgrAbsProxy::GetInstance()->SearchContact(memberList,"fjj23", "", true, 0, PAGE_SIZE, 0, recamount);
	CPPUNIT_ASSERT_MESSAGE("SearchContact", UCSDK_Succ == iRet);
	CPPUNIT_ASSERT_MESSAGE("SearchContact", 1 == memberList.size());

	iRet = UCGroupAbsProxy::GetInstance()->AddContact(group, memberList.at(0));
	CPPUNIT_ASSERT_MESSAGE("AddContact", UCSDK_Succ == iRet);

	UCSDKContact member;
	iRet = UCContactMgrAbsProxy::GetInstance()->RefreshContactByUri(memberList.at(0).uri_, member);
	CPPUNIT_ASSERT_MESSAGE("RefreshContactByAccount", UCSDK_Succ == iRet);

	UCSDKContactList allList;
	iRet = UCContactMgrAbsProxy::GetInstance()->GetAllContactlist(allList);
	CPPUNIT_ASSERT_MESSAGE("GetAllContactlist", UCSDK_Succ == iRet);

	iRet = UCGroupAbsProxy::GetInstance()->RemoveContact(group, memberList.at(0));
	CPPUNIT_ASSERT_MESSAGE("RemoveContact", UCSDK_Succ == iRet);

	UCSDKContactList allList1;
	iRet = UCContactMgrAbsProxy::GetInstance()->GetAllContactlist(allList1);
	CPPUNIT_ASSERT_MESSAGE("GetAllContactlist", UCSDK_Succ == iRet);
	CPPUNIT_ASSERT_MESSAGE("GetAllContactlist", allList.size() == (allList1.size() + 1));

	iRet = UCGroupAbsProxy::GetInstance()->RemoveCustomGroup(group);
	CPPUNIT_ASSERT_MESSAGE("RemoveCustomGroup", UCSDK_Succ == iRet);

}

//²âÊÔÓÃÀý
void UTContactMgrAbsProxy::UTContactMgrAbsProxy_RefreshContactById()
{
	RemoveContact();
	UCSDKCustomGroup group;
	group.name_ = "UTgroup1";
	int iRet = UCGroupAbsProxy::GetInstance()->AddCustomGroup(group);
	CPPUNIT_ASSERT_MESSAGE("AddCustomGroup", UCSDK_Succ == iRet);

	UCSDKContactList memberList;
	const int PAGE_SIZE = 2;
	int recamount = 0;
	iRet = UCContactMgrAbsProxy::GetInstance()->SearchContact(memberList,"fjj23", "", true, 0, PAGE_SIZE, 0, recamount);
	CPPUNIT_ASSERT_MESSAGE("SearchContact", UCSDK_Succ == iRet);
	CPPUNIT_ASSERT_MESSAGE("SearchContact", 1 == memberList.size());

	iRet = UCGroupAbsProxy::GetInstance()->AddContact(group, memberList.at(0));
	CPPUNIT_ASSERT_MESSAGE("AddContact", UCSDK_Succ == iRet);

	UCSDKContactList allList;
	iRet = UCContactMgrAbsProxy::GetInstance()->GetAllContactlist(allList);
	CPPUNIT_ASSERT_MESSAGE("GetAllContactlist", UCSDK_Succ == iRet);
	
	UCSDKContactList::iterator iter_b = allList.begin();
	UCSDKContactList::iterator iter_e = allList.end();
	for(; iter_b != iter_e; iter_b++)
	{
		UCSDKContact member;
		iRet = UCContactMgrAbsProxy::GetInstance()->RefreshContactById((*iter_b).id_, member);
		CPPUNIT_ASSERT_MESSAGE("RefreshContactByAccount", UCSDK_Succ == iRet);
	}	
	
	iRet = UCGroupAbsProxy::GetInstance()->RemoveContact(group, memberList.at(0));
	CPPUNIT_ASSERT_MESSAGE("RemoveContact", UCSDK_Succ == iRet);

	UCSDKContactList allList1;
	iRet = UCContactMgrAbsProxy::GetInstance()->GetAllContactlist(allList1);
	CPPUNIT_ASSERT_MESSAGE("GetAllContactlist", UCSDK_Succ == iRet);
	CPPUNIT_ASSERT_MESSAGE("GetAllContactlist", allList.size() == (allList1.size() + 1));

	iRet = UCGroupAbsProxy::GetInstance()->RemoveCustomGroup(group);
	CPPUNIT_ASSERT_MESSAGE("RemoveCustomGroup", UCSDK_Succ == iRet);

}

//²âÊÔÓÃÀý
void UTContactMgrAbsProxy::UTContactMgrAbsProxy_RemoveContactById()
{	
	RemoveContact();
	
	UCSDKCustomGroup group;
	group.name_ = "UTgroup1";
	int iRet = UCGroupAbsProxy::GetInstance()->AddCustomGroup(group);
	CPPUNIT_ASSERT_MESSAGE("AddCustomGroup", UCSDK_Succ == iRet);

	UCSDKContactList memberList;
	const int PAGE_SIZE = 2;
	int recamount = 0;
	iRet = UCContactMgrAbsProxy::GetInstance()->SearchContact(memberList,"fjj23", "", true, 0, PAGE_SIZE, 0, recamount);
	CPPUNIT_ASSERT_MESSAGE("SearchContact", UCSDK_Succ == iRet);
	CPPUNIT_ASSERT_MESSAGE("SearchContact", 1 == memberList.size());

	iRet = UCGroupAbsProxy::GetInstance()->AddContact(group, memberList.at(0));
	CPPUNIT_ASSERT_MESSAGE("AddContact", UCSDK_Succ == iRet);

	UCSDKContactList allList;
	iRet = UCContactMgrAbsProxy::GetInstance()->GetAllContactlist(allList);
	CPPUNIT_ASSERT_MESSAGE("GetAllContactlist", UCSDK_Succ == iRet);

	RemoveContact();

	UCSDKContactList allList1;
	iRet = UCContactMgrAbsProxy::GetInstance()->GetAllContactlist(allList1);
	CPPUNIT_ASSERT_MESSAGE("GetAllContactlist", UCSDK_Succ == iRet);
	CPPUNIT_ASSERT_MESSAGE("GetAllContactlist", allList.size() == (allList1.size() + 1));

	iRet = UCGroupAbsProxy::GetInstance()->RemoveCustomGroup(group);
	CPPUNIT_ASSERT_MESSAGE("RemoveCustomGroup", UCSDK_Succ == iRet);

}

//²âÊÔÓÃÀý
void UTContactMgrAbsProxy::UTContactMgrAbsProxy_SearchContact()
{	
	RemoveContact();
	
	UCSDKContactList memberList;
	const int PAGE_SIZE = 2;
	int recamount = 0;
	int iRet = UCContactMgrAbsProxy::GetInstance()->SearchContact(memberList,"fjj23", "", true, 0, PAGE_SIZE, 0, recamount);
	CPPUNIT_ASSERT_MESSAGE("SearchContact", UCSDK_Succ == iRet);
	CPPUNIT_ASSERT_MESSAGE("SearchContact", 1 == memberList.size());

	memberList.clear();
	iRet = UCContactMgrAbsProxy::GetInstance()->SearchContact(memberList,"fjj233", "", true, 0, PAGE_SIZE, 0, recamount);
	CPPUNIT_ASSERT_MESSAGE("SearchContact", UCSDK_Succ == iRet);
	CPPUNIT_ASSERT_MESSAGE("SearchContact", 0 == memberList.size());
	
	const int PAGE_SIZE_TOTAL = 70;
	memberList.clear();
	iRet = UCContactMgrAbsProxy::GetInstance()->SearchContact(memberList,"fjj", "", true, 0, PAGE_SIZE_TOTAL, 0, recamount);
	CPPUNIT_ASSERT_MESSAGE("SearchContact", UCSDK_Succ == iRet);
	CPPUNIT_ASSERT_MESSAGE("SearchContact", 65 == memberList.size());

	const int PAGE_SIZE_SEG = 10;
	memberList.clear();
	iRet = UCContactMgrAbsProxy::GetInstance()->SearchContact(memberList,"fjj", "", true, 0, PAGE_SIZE_SEG, 0, recamount);
	CPPUNIT_ASSERT_MESSAGE("SearchContact", UCSDK_Succ == iRet);
	CPPUNIT_ASSERT_MESSAGE("SearchContact", 10 == memberList.size());
}

//²âÊÔÓÃÀý
void UTContactMgrAbsProxy::UTContactMgrAbsProxy_Modify()
{	
	RemoveContact();

	UCSDKContactList memberList;
	const int PAGE_SIZE = 2;
	int recamount = 0;
	int iRet = UCContactMgrAbsProxy::GetInstance()->SearchContact(memberList,"fjj23", "", true, 0, PAGE_SIZE, 0, recamount);
	CPPUNIT_ASSERT_MESSAGE("SearchContact", UCSDK_Succ == iRet);
	CPPUNIT_ASSERT_MESSAGE("SearchContact", 1 == memberList.size());

	bool bRet = UCContactMgrAbsProxy::GetInstance()->Modify(memberList.at(0));
	CPPUNIT_ASSERT_MESSAGE("SearchContact", false == bRet);
}

//²âÊÔÓÃÀý
void UTContactMgrAbsProxy::UTContactMgrAbsProxy_GetHeadImagePath()
{	
	RemoveContact();

	UCSDKContactList memberList;
	const int PAGE_SIZE = 2;
	int recamount = 0;
	int iRet = UCContactMgrAbsProxy::GetInstance()->SearchContact(memberList,"fjj53", "", true, 0, PAGE_SIZE, 0, recamount);
	CPPUNIT_ASSERT_MESSAGE("SearchContact", UCSDK_Succ == iRet);
	CPPUNIT_ASSERT_MESSAGE("SearchContact", 1 == memberList.size());

	UCSDKCustomGroup group;
	group.name_ = "UTgroup1";
	iRet = UCGroupAbsProxy::GetInstance()->AddCustomGroup(group);
	CPPUNIT_ASSERT_MESSAGE("AddCustomGroup", UCSDK_Succ == iRet);

	iRet = UCGroupAbsProxy::GetInstance()->AddContact(group, memberList.at(0));
	CPPUNIT_ASSERT_MESSAGE("AddContact", UCSDK_Succ == iRet);

	std::string path = UCContactMgrAbsProxy::GetInstance()->GetHeadImagePath(memberList.at(0), false);
	CPPUNIT_ASSERT_MESSAGE("GetHeadImagePath", "" != path);

	path = UCContactMgrAbsProxy::GetInstance()->GetHeadImagePath(memberList.at(0), true);
	CPPUNIT_ASSERT_MESSAGE("GetHeadImagePath", "" != path);

	RemoveContact();

	iRet = UCGroupAbsProxy::GetInstance()->RemoveCustomGroup(group);
	CPPUNIT_ASSERT_MESSAGE("RemoveCustomGroup", UCSDK_Succ == iRet);
}

//²âÊÔÓÃÀý
void UTContactMgrAbsProxy::UTContactMgrAbsProxy_MoveToGroup()
{	
	RemoveContact();	
}

//²âÊÔÓÃÀý
void UTContactMgrAbsProxy::UTContactMgrAbsProxy_AddToGroup()
{	
	RemoveContact();

	UCSDKContactList memberList;
	const int PAGE_SIZE = 2;
	int recamount = 0;
	int iRet = UCContactMgrAbsProxy::GetInstance()->SearchContact(memberList,"fjj33", "", true, 0, PAGE_SIZE, 0, recamount);
	CPPUNIT_ASSERT_MESSAGE("SearchContact", UCSDK_Succ == iRet);
	CPPUNIT_ASSERT_MESSAGE("SearchContact", 1 == memberList.size());

	UCSDKCustomGroup group;
	group.name_ = "UTgroup1";
	iRet = UCGroupAbsProxy::GetInstance()->AddCustomGroup(group);
	CPPUNIT_ASSERT_MESSAGE("AddCustomGroup", UCSDK_Succ == iRet);

	iRet = UCGroupAbsProxy::GetInstance()->AddContact(group, memberList.at(0));
	CPPUNIT_ASSERT_MESSAGE("AddContact", UCSDK_Succ == iRet);

	UCSDKCustomGroup group2;
	group2.name_ = "UTgroup2";
	iRet = UCGroupAbsProxy::GetInstance()->AddCustomGroup(group2);
	CPPUNIT_ASSERT_MESSAGE("AddCustomGroup", UCSDK_Succ == iRet);

	bool bRet = UCContactMgrAbsProxy::GetInstance()->RemoveFromGroup(memberList.at(0), group);
	CPPUNIT_ASSERT_MESSAGE("RemoveFromGroup", true == bRet);
	
	UCSDKContactList memberList1;
	iRet = UCContactMgrAbsProxy::GetInstance()->SearchContact(memberList1,"fjj34", "", true, 0, PAGE_SIZE, 0, recamount);
	CPPUNIT_ASSERT_MESSAGE("SearchContact", UCSDK_Succ == iRet);
	CPPUNIT_ASSERT_MESSAGE("SearchContact", 1 == memberList1.size());

	iRet = UCGroupAbsProxy::GetInstance()->AddContact(group2, memberList1.at(0));
	CPPUNIT_ASSERT_MESSAGE("AddContact", UCSDK_Succ == iRet);

	UCSDKContactList allList;
	iRet = UCGroupAbsProxy::GetInstance()->GetContactlist(group2, allList);
	CPPUNIT_ASSERT_MESSAGE("GetAllContactlist", UCSDK_Succ == iRet);
	CPPUNIT_ASSERT_MESSAGE("GetAllContactlist", 1 == allList.size());
	
	bRet = UCContactMgrAbsProxy::GetInstance()->AddToGroup(memberList.at(0), group2);
	CPPUNIT_ASSERT_MESSAGE("AddToGroup", true == bRet);

	UCSDKContactList allList1;
	iRet = UCGroupAbsProxy::GetInstance()->GetContactlist(group2, allList1);
	CPPUNIT_ASSERT_MESSAGE("GetAllContactlist", UCSDK_Succ == iRet);
	CPPUNIT_ASSERT_MESSAGE("GetAllContactlist", allList1.size() == (allList.size() + 1));

	iRet = UCGroupAbsProxy::GetInstance()->RemoveContact(group2, memberList.at(0));
	CPPUNIT_ASSERT_MESSAGE("RemoveContact", UCSDK_Succ == iRet);

	iRet = UCGroupAbsProxy::GetInstance()->RemoveContact(group2, memberList1.at(0));
	CPPUNIT_ASSERT_MESSAGE("RemoveContact", UCSDK_Succ == iRet);

	iRet = UCGroupAbsProxy::GetInstance()->RemoveCustomGroup(group);
	CPPUNIT_ASSERT_MESSAGE("RemoveCustomGroup", UCSDK_Succ == iRet);

	iRet = UCGroupAbsProxy::GetInstance()->RemoveCustomGroup(group2);
	CPPUNIT_ASSERT_MESSAGE("RemoveCustomGroup", UCSDK_Succ == iRet);
}

//²âÊÔÓÃÀý
void UTContactMgrAbsProxy::UTContactMgrAbsProxy_RemoveFromGroup()
{	
	RemoveContact();

	UCSDKContactList memberList;
	const int PAGE_SIZE = 2;
	int recamount = 0;
	int iRet = UCContactMgrAbsProxy::GetInstance()->SearchContact(memberList,"fjj33", "", true, 0, PAGE_SIZE, 0, recamount);
	CPPUNIT_ASSERT_MESSAGE("SearchContact", UCSDK_Succ == iRet);
	CPPUNIT_ASSERT_MESSAGE("SearchContact", 1 == memberList.size());

	UCSDKContactList memberList1;
	iRet = UCContactMgrAbsProxy::GetInstance()->SearchContact(memberList1,"fjj34", "", true, 0, PAGE_SIZE, 0, recamount);
	CPPUNIT_ASSERT_MESSAGE("SearchContact", UCSDK_Succ == iRet);
	CPPUNIT_ASSERT_MESSAGE("SearchContact", 1 == memberList1.size());

	UCSDKCustomGroup group;
	group.name_ = "UTgroup1";
	iRet = UCGroupAbsProxy::GetInstance()->AddCustomGroup(group);
	CPPUNIT_ASSERT_MESSAGE("AddCustomGroup", UCSDK_Succ == iRet);

	iRet = UCGroupAbsProxy::GetInstance()->AddContact(group, memberList.at(0));
	CPPUNIT_ASSERT_MESSAGE("AddContact", UCSDK_Succ == iRet);

	iRet = UCGroupAbsProxy::GetInstance()->AddContact(group, memberList1.at(0));
	CPPUNIT_ASSERT_MESSAGE("AddContact", UCSDK_Succ == iRet);
	
	UCSDKContactList allList;
	iRet = UCGroupAbsProxy::GetInstance()->GetContactlist(group, allList);
	CPPUNIT_ASSERT_MESSAGE("GetAllContactlist", UCSDK_Succ == iRet);
	CPPUNIT_ASSERT_MESSAGE("GetAllContactlist", 2 == allList.size());
	
	bool bRet = UCContactMgrAbsProxy::GetInstance()->RemoveFromGroup(memberList.at(0), group);
	CPPUNIT_ASSERT_MESSAGE("RemoveFromGroup", true == bRet);

	UCSDKContactList allList1;
	iRet = UCGroupAbsProxy::GetInstance()->GetContactlist(group, allList1);
	CPPUNIT_ASSERT_MESSAGE("GetAllContactlist", UCSDK_Succ == iRet);
	CPPUNIT_ASSERT_MESSAGE("GetAllContactlist", allList.size() == (allList1.size() + 1));

	RemoveContact();

	iRet = UCGroupAbsProxy::GetInstance()->RemoveCustomGroup(group);
	CPPUNIT_ASSERT_MESSAGE("RemoveCustomGroup", UCSDK_Succ == iRet);
}

//²âÊÔÓÃÀý
void UTContactMgrAbsProxy::UTContactMgrAbsProxy_CanStartSession()
{	
	RemoveContact();
	
}

//²âÊÔÓÃÀý
void UTContactMgrAbsProxy::UTContactMgrAbsProxy_CanMoveToGroup()
{	
	RemoveContact();

}

//²âÊÔÓÃÀý
void UTContactMgrAbsProxy::UTContactMgrAbsProxy_GetCustomGroups()
{	
	RemoveContact();

	UCSDKContactList memberList;
	const int PAGE_SIZE = 2;
	int recamount = 0;
	int iRet = UCContactMgrAbsProxy::GetInstance()->SearchContact(memberList,"fjj33", "", true, 0, PAGE_SIZE, 0, recamount);
	CPPUNIT_ASSERT_MESSAGE("SearchContact", UCSDK_Succ == iRet);
	CPPUNIT_ASSERT_MESSAGE("SearchContact", 1 == memberList.size());

	UCSDKCustomGroup group;
	group.name_ = "UTgroup1";
	iRet = UCGroupAbsProxy::GetInstance()->AddCustomGroup(group);
	CPPUNIT_ASSERT_MESSAGE("AddCustomGroup", UCSDK_Succ == iRet);

	iRet = UCGroupAbsProxy::GetInstance()->AddContact(group, memberList.at(0));
	CPPUNIT_ASSERT_MESSAGE("AddContact", UCSDK_Succ == iRet);
	
	UCSDKCustomGroupList groupList;
	iRet = UCContactMgrAbsProxy::GetInstance()->GetCustomGroups(memberList.at(0), groupList);
	CPPUNIT_ASSERT_MESSAGE("AddContact", UCSDK_Succ == iRet);
	CPPUNIT_ASSERT_MESSAGE("AddContact", ((1 == groupList.size()) && (groupList.at(0).id_ == group.id_) && (groupList.at(0).name_ == group.name_)));

	
	iRet = UCGroupAbsProxy::GetInstance()->RemoveContact(group, memberList.at(0));
	CPPUNIT_ASSERT_MESSAGE("RemoveContact", UCSDK_Succ == iRet);
	iRet = UCGroupAbsProxy::GetInstance()->RemoveCustomGroup(group);
	CPPUNIT_ASSERT_MESSAGE("RemoveCustomGroup", UCSDK_Succ == iRet);	
}

//²âÊÔÓÃÀý
void UTContactMgrAbsProxy::UTContactMgrAbsProxy_IsFavourite()
{	
	RemoveContact();

	UCSDKContactList memberList;
	const int PAGE_SIZE = 2;
	int recamount = 0;
	int iRet = UCContactMgrAbsProxy::GetInstance()->SearchContact(memberList,"fjj33", "", true, 0, PAGE_SIZE, 0, recamount);
	CPPUNIT_ASSERT_MESSAGE("SearchContact", UCSDK_Succ == iRet);
	CPPUNIT_ASSERT_MESSAGE("SearchContact", 1 == memberList.size());
	
	UCSDKCustomGroup group;
	group.name_ = "UTgroup1";
	iRet = UCGroupAbsProxy::GetInstance()->AddCustomGroup(group);
	CPPUNIT_ASSERT_MESSAGE("AddCustomGroup", UCSDK_Succ == iRet);

	iRet = UCGroupAbsProxy::GetInstance()->AddContact(group, memberList.at(0));
	CPPUNIT_ASSERT_MESSAGE("AddContact", UCSDK_Succ == iRet);

	bool bRet = UCContactMgrAbsProxy::GetInstance()->IsFavourite(memberList.at(0));
	CPPUNIT_ASSERT_MESSAGE("AddContact", false == bRet);

	iRet = UCGroupAbsProxy::GetInstance()->RemoveContact(group, memberList.at(0));
	CPPUNIT_ASSERT_MESSAGE("RemoveContact", UCSDK_Succ == iRet);
	iRet = UCGroupAbsProxy::GetInstance()->RemoveCustomGroup(group);
	CPPUNIT_ASSERT_MESSAGE("RemoveCustomGroup", UCSDK_Succ == iRet);		
}

#endif
//¸¨Öúº¯Êý
void UTContactMgrAbsProxy::UTSignIn()
{
	int iRet = UCSDKAbsProxy::GetInstance()->Login("fjj56", "UcAAaa_11");	
	CPPUNIT_ASSERT_MESSAGE("SignIn", UCSDK_Succ == iRet);
}
void UTContactMgrAbsProxy::UTSignOut()
{
	ctk::sleep(100);
	int iRet = UCSDKAbsProxy::GetInstance()->Logout();
	CPPUNIT_ASSERT_MESSAGE("SignOut", UCSDK_Succ == iRet);
}

//call back
void CALLBACK UTContactMgrAbsProxy::TurnOnClientSignInNotify(int state,const std::string &reason)
{
	if (0 == m_iSignFlag)			//signout
	{
		CPPUNIT_ASSERT_MESSAGE("SignOut", 1 == state);
		CPPUNIT_ASSERT_MESSAGE("SignOut", 0 == strcmp("signout", reason.c_str()));
	}
	else if (1 == m_iSignFlag)		//success
	{
		CPPUNIT_ASSERT_MESSAGE("SignIn", 3 == state);
	}

	m_iSignFlag = -1;
}

void UTContactMgrAbsProxy::RemoveContact()
{
	UCSDKContactList allList;
	int iRet = UCContactMgrAbsProxy::GetInstance()->GetAllContactlist(allList);
	
	UCSDKContactList::iterator iter_b = allList.begin();
	UCSDKContactList::iterator iter_e = allList.end();
	for(; iter_b != iter_e; iter_b++)
	{
		if((*iter_b).ucAcc_ != "fjj56")
		{
			iRet = UCContactMgrAbsProxy::GetInstance()->RemoveContactById((*iter_b).id_);
		}
	}	
}