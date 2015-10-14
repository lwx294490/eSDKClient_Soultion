#include "stdafx.h"
#include "ctk/mt/thread.h"
#include "UTGroupAbsProxy.h"

CPPUNIT_TEST_SUITE_NAMED_REGISTRATION(UTGroupAbsProxy, "UCSDKUnitTest");

int UTGroupAbsProxy::m_iSignFlag = -1;
UTGroupAbsProxy::UTGroupAbsProxy()
{

}

UTGroupAbsProxy::~UTGroupAbsProxy()
{

}

void UTGroupAbsProxy::setUp()
{
	UCSDKAbsProxy::GetInstance()->Init();
	UCSDKAbsProxy::GetInstance()->Config("10.170.103.52:8081");
	UCSDKAbsProxy::GetInstance()->SetLang("Chinese");
	
	//UCSignalRecvAbsProxy::GetInstance()->OnClientSignInNotify(TurnOnClientSignInNotify);
	
	UTSignIn();
}

void UTGroupAbsProxy::tearDown()
{
	UTSignOut();


	
	ctk::sleep(1000);
}

//²âÊÔÓÃÀý
void UTGroupAbsProxy::UTGroupAbsProxy_AddFixedGroup()
{
	RemoveContact();	

	UCSDKFixedGroup group;
	group.name_ = "UTFixedgroup1";
	int iRet = UCGroupAbsProxy::GetInstance()->AddFixedGroup(group);
	CPPUNIT_ASSERT_MESSAGE("AddFixedGroup", UCSDK_Succ == iRet);

	UCSDKContactList memberList;
	const int PAGE_SIZE = 2;
	int recamount = 0;
	iRet = UCContactMgrAbsProxy::GetInstance()->SearchContact(memberList,"fjj23", "", true, 0, PAGE_SIZE, 0, recamount);
	CPPUNIT_ASSERT_MESSAGE("SearchContact", UCSDK_Succ == iRet);
	CPPUNIT_ASSERT_MESSAGE("SearchContact", 1 == memberList.size());

	iRet = UCGroupAbsProxy::GetInstance()->AddContact(group, memberList.at(0));
	CPPUNIT_ASSERT_MESSAGE("AddContact", UCSDK_Succ == iRet);
	
	UCSDKContactList allList;
	iRet = UCGroupAbsProxy::GetInstance()->GetContactlist(group, allList);
	CPPUNIT_ASSERT_MESSAGE("GetContactlist", UCSDK_Succ == iRet);
	CPPUNIT_ASSERT_MESSAGE("GetContactlist", 2 == allList.size());

	UCSDKContactList memberList1;
	iRet = UCContactMgrAbsProxy::GetInstance()->SearchContact(memberList1,"fjj33", "", true, 0, PAGE_SIZE, 0, recamount);
	CPPUNIT_ASSERT_MESSAGE("SearchContact", UCSDK_Succ == iRet);
	CPPUNIT_ASSERT_MESSAGE("SearchContact", 1 == memberList1.size());

	iRet = UCGroupAbsProxy::GetInstance()->AddContact(group, memberList1.at(0));
	CPPUNIT_ASSERT_MESSAGE("AddContact", UCSDK_Succ == iRet);
	
	allList.clear();
	iRet = UCGroupAbsProxy::GetInstance()->GetContactlist(group, allList);
	CPPUNIT_ASSERT_MESSAGE("GetContactlist", UCSDK_Succ == iRet);
	CPPUNIT_ASSERT_MESSAGE("GetContactlist", 3 == allList.size());

	iRet = UCGroupAbsProxy::GetInstance()->RemoveFixedGroup(group);
	CPPUNIT_ASSERT_MESSAGE("RemoveFixedGroup", UCSDK_Succ == iRet);

	UCSDKContactList allList1;
	iRet = UCContactMgrAbsProxy::GetInstance()->GetAllContactlist(allList1);
	CPPUNIT_ASSERT_MESSAGE("GetAllContactlist", UCSDK_Succ == iRet);
	CPPUNIT_ASSERT_MESSAGE("GetAllContactlist", 1 == allList1.size());
}

//²âÊÔÓÃÀý
void UTGroupAbsProxy::UTGroupAbsProxy_GetFixedGroupByID()
{
	RemoveContact();	

	UCSDKFixedGroup group;
	group.name_ = "UTFixedgroup1";
	int iRet = UCGroupAbsProxy::GetInstance()->AddFixedGroup(group);
	CPPUNIT_ASSERT_MESSAGE("AddFixedGroup", UCSDK_Succ == iRet);
	
	UCSDKFixedGroup group1;
	iRet = UCGroupAbsProxy::GetInstance()->GetFixedGroupByID(group1, group.id_);
	CPPUNIT_ASSERT_MESSAGE("GetFixedGroupByID", UCSDK_Succ == iRet);
	CPPUNIT_ASSERT_MESSAGE("GetFixedGroupByID", ((group.uri_ == group1.uri_) && (group.creator_ == group1.creator_)));

	iRet = UCGroupAbsProxy::GetInstance()->RemoveFixedGroup(group);
	CPPUNIT_ASSERT_MESSAGE("RemoveFixedGroup", UCSDK_Succ == iRet);	
}

//²âÊÔÓÃÀý
void UTGroupAbsProxy::UTGroupAbsProxy_GetFixedGroupByUri()
{
	RemoveContact();	

	UCSDKFixedGroup group;
	group.name_ = "UTFixedgroup1";
	int iRet = UCGroupAbsProxy::GetInstance()->AddFixedGroup(group);
	CPPUNIT_ASSERT_MESSAGE("AddFixedGroup", UCSDK_Succ == iRet);

	UCSDKFixedGroup group1;
	iRet = UCGroupAbsProxy::GetInstance()->GetFixedGroupByUri(group1, group.uri_);
	CPPUNIT_ASSERT_MESSAGE("GetFixedGroupByUri", UCSDK_Succ == iRet);
	CPPUNIT_ASSERT_MESSAGE("GetFixedGroupByUri", ((group.uri_ == group1.uri_) && (group.creator_ == group1.creator_)));

	iRet = UCGroupAbsProxy::GetInstance()->RemoveFixedGroup(group);
	CPPUNIT_ASSERT_MESSAGE("RemoveFixedGroup", UCSDK_Succ == iRet);
		
}

//²âÊÔÓÃÀý
void UTGroupAbsProxy::UTGroupAbsProxy_RemoveFixedGroup()
{
	RemoveContact();	

	UCSDKFixedGroup group;
	group.name_ = "UTFixedgroup1";
	int iRet = UCGroupAbsProxy::GetInstance()->AddFixedGroup(group);
	CPPUNIT_ASSERT_MESSAGE("AddFixedGroup", UCSDK_Succ == iRet);

	UCSDKFixedGroup group1;
	group1.name_ = "UTFixedgroup2";
	iRet = UCGroupAbsProxy::GetInstance()->AddFixedGroup(group1);
	CPPUNIT_ASSERT_MESSAGE("AddFixedGroup", UCSDK_Succ == iRet);

	UCSDKFixedGroupList groupList;
	iRet = UCGroupAbsProxy::GetInstance()->GetFixedGrouplist(groupList);
	CPPUNIT_ASSERT_MESSAGE("GetFixedGrouplist", UCSDK_Succ == iRet);
	CPPUNIT_ASSERT_MESSAGE("GetFixedGrouplist", 2 == groupList.size());
	
	iRet = UCGroupAbsProxy::GetInstance()->RemoveFixedGroup(group);
	CPPUNIT_ASSERT_MESSAGE("RemoveFixedGroup", UCSDK_Succ == iRet);

	UCSDKFixedGroupList groupList1;
	iRet = UCGroupAbsProxy::GetInstance()->GetFixedGrouplist(groupList1);
	CPPUNIT_ASSERT_MESSAGE("GetFixedGrouplist", UCSDK_Succ == iRet);
	CPPUNIT_ASSERT_MESSAGE("GetFixedGrouplist", 1 == groupList1.size());

	iRet = UCGroupAbsProxy::GetInstance()->RemoveFixedGroup(group1);
	CPPUNIT_ASSERT_MESSAGE("RemoveFixedGroup", UCSDK_Succ == iRet);

}

//²âÊÔÓÃÀý
void UTGroupAbsProxy::UTGroupAbsProxy_RefreshFixedGrouplist()
{
	RemoveContact();	

	UCSDKFixedGroup group;
	group.name_ = "UTFixedgroup1";
	int iRet = UCGroupAbsProxy::GetInstance()->AddFixedGroup(group);
	CPPUNIT_ASSERT_MESSAGE("AddFixedGroup", UCSDK_Succ == iRet);

	UCSDKFixedGroup group1;
	group1.name_ = "UTFixedgroup2";
	iRet = UCGroupAbsProxy::GetInstance()->AddFixedGroup(group1);
	CPPUNIT_ASSERT_MESSAGE("AddFixedGroup", UCSDK_Succ == iRet);

	UCSDKFixedGroupList groupList;
	iRet = UCGroupAbsProxy::GetInstance()->GetFixedGrouplist(groupList);
	CPPUNIT_ASSERT_MESSAGE("GetFixedGrouplist", UCSDK_Succ == iRet);
	CPPUNIT_ASSERT_MESSAGE("GetFixedGrouplist", 2 == groupList.size());
	
	UCSDKFixedGroupList groupList1;
	iRet = UCGroupAbsProxy::GetInstance()->RefreshFixedGrouplist(groupList1);
	CPPUNIT_ASSERT_MESSAGE("RefreshFixedGrouplist", UCSDK_Succ == iRet);
	CPPUNIT_ASSERT_MESSAGE("RefreshFixedGrouplist", (groupList1.at(0).name_ == groupList.at(0).name_) && (groupList1.at(1).name_ == groupList.at(1).name_));
		
	iRet = UCGroupAbsProxy::GetInstance()->RemoveFixedGroup(group);
	CPPUNIT_ASSERT_MESSAGE("RemoveFixedGroup", UCSDK_Succ == iRet);

	iRet = UCGroupAbsProxy::GetInstance()->RemoveFixedGroup(group1);
	CPPUNIT_ASSERT_MESSAGE("RemoveFixedGroup", UCSDK_Succ == iRet);

}

//²âÊÔÓÃÀý
void UTGroupAbsProxy::UTGroupAbsProxy_GetFixedGrouplist()
{
	RemoveContact();	
	
	UCSDKFixedGroupList TmpList;
	int iRet = UCGroupAbsProxy::GetInstance()->GetFixedGrouplist(TmpList);
	CPPUNIT_ASSERT_MESSAGE("GetFixedGrouplist", UCSDK_Succ == iRet);
	CPPUNIT_ASSERT_MESSAGE("GetFixedGrouplist", 0 == TmpList.size());

	UCSDKFixedGroup group;
	group.name_ = "UTFixedgroup1";
	iRet = UCGroupAbsProxy::GetInstance()->AddFixedGroup(group);
	CPPUNIT_ASSERT_MESSAGE("AddFixedGroup", UCSDK_Succ == iRet);

	UCSDKFixedGroup group1;
	group1.name_ = "UTFixedgroup2";
	iRet = UCGroupAbsProxy::GetInstance()->AddFixedGroup(group1);
	CPPUNIT_ASSERT_MESSAGE("AddFixedGroup", UCSDK_Succ == iRet);

	UCSDKFixedGroupList groupList;
	iRet = UCGroupAbsProxy::GetInstance()->GetFixedGrouplist(groupList);
	CPPUNIT_ASSERT_MESSAGE("GetFixedGrouplist", UCSDK_Succ == iRet);
	CPPUNIT_ASSERT_MESSAGE("GetFixedGrouplist", 2 == groupList.size());

	iRet = UCGroupAbsProxy::GetInstance()->RemoveFixedGroup(group);
	CPPUNIT_ASSERT_MESSAGE("RemoveFixedGroup", UCSDK_Succ == iRet);

	UCSDKFixedGroupList groupList1;
	iRet = UCGroupAbsProxy::GetInstance()->GetFixedGrouplist(groupList1);
	CPPUNIT_ASSERT_MESSAGE("GetFixedGrouplist", UCSDK_Succ == iRet);
	CPPUNIT_ASSERT_MESSAGE("GetFixedGrouplist", 1 == groupList1.size());

	iRet = UCGroupAbsProxy::GetInstance()->RemoveFixedGroup(group1);
	CPPUNIT_ASSERT_MESSAGE("RemoveFixedGroup", UCSDK_Succ == iRet);

}

//²âÊÔÓÃÀý
void UTGroupAbsProxy::UTGroupAbsProxy_SearchFixedGroup()
{
	RemoveContact();	

	UCSDKFixedGroup group;
	group.name_ = "UTFixedgroup1";
	int iRet = UCGroupAbsProxy::GetInstance()->AddFixedGroup(group);
	CPPUNIT_ASSERT_MESSAGE("AddFixedGroup", UCSDK_Succ == iRet);

	UCSDKFixedGroup group1;
	group1.name_ = "UTFixedgroup2";
	iRet = UCGroupAbsProxy::GetInstance()->AddFixedGroup(group1);
	CPPUNIT_ASSERT_MESSAGE("AddFixedGroup", UCSDK_Succ == iRet);

	UCSDKFixedGroup group2;
	group2.name_ = "UTFixedgroup3";
	iRet = UCGroupAbsProxy::GetInstance()->AddFixedGroup(group2);
	CPPUNIT_ASSERT_MESSAGE("AddFixedGroup", UCSDK_Succ == iRet);

	UCSDKFixedGroupList groupList;
	const int PAGE_SIZE = 2;
	iRet = UCGroupAbsProxy::GetInstance()->SearchFixedGroup(groupList, "", "UTFixedgroup2", 1, PAGE_SIZE);
	CPPUNIT_ASSERT_MESSAGE("GetFixedGrouplist", UCSDK_Succ == iRet);
	CPPUNIT_ASSERT_MESSAGE("GetFixedGrouplist", (1 == groupList.size()) && (groupList.at(0).name_ == group1.name_));

	iRet = UCGroupAbsProxy::GetInstance()->RemoveFixedGroup(group);
	CPPUNIT_ASSERT_MESSAGE("RemoveFixedGroup", UCSDK_Succ == iRet);	

	iRet = UCGroupAbsProxy::GetInstance()->RemoveFixedGroup(group1);
	CPPUNIT_ASSERT_MESSAGE("RemoveFixedGroup", UCSDK_Succ == iRet);

	iRet = UCGroupAbsProxy::GetInstance()->RemoveFixedGroup(group2);
	CPPUNIT_ASSERT_MESSAGE("RemoveFixedGroup", UCSDK_Succ == iRet);

}

//²âÊÔÓÃÀý
void UTGroupAbsProxy::UTGroupAbsProxy_AddCustomGroup()
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
void UTGroupAbsProxy::UTGroupAbsProxy_AddFavoriteGroup()
{	
	RemoveContact();

	// 	UCSDKCustomGroup group;
	// 	group.name_ = "UTgroup1";
	// 	int iRet = UCGroupAbsProxy::GetInstance()->AddCustomGroup(group);
	// 	CPPUNIT_ASSERT_MESSAGE("AddCustomGroup", UCSDK_Succ == iRet);
	// 
	// 	UCSDKFixedGroup group;
	// 	group.name_ = "UTFixedgroup1";
	// 	int iRet = UCGroupAbsProxy::GetInstance()->AddFixedGroup(group);
	// 	CPPUNIT_ASSERT_MESSAGE("AddFixedGroup", UCSDK_Succ == iRet);
	// 	
	// 	UCSDKFavoriteGroup group1;
	// 	group1.id_ = group.id_;
	// 	iRet = UCGroupAbsProxy::GetInstance()->AddFavoriteGroup(group1);
	// 	CPPUNIT_ASSERT_MESSAGE("AddFavoriteGroup", UCSDK_Succ == iRet);
	// 
	// 	iRet = UCGroupAbsProxy::GetInstance()->RemoveFavoriteGroup(group1);
	// 	CPPUNIT_ASSERT_MESSAGE("RemoveFavoriteGroup", UCSDK_Succ == iRet);
	// 	
	// 	iRet = UCGroupAbsProxy::GetInstance()->RemoveCustomGroup(group);
	// 	CPPUNIT_ASSERT_MESSAGE("RemoveCustomGroup", UCSDK_Succ == iRet);
	// 
	// 	iRet = UCGroupAbsProxy::GetInstance()->RemoveFixedGroup(group);
	// 	CPPUNIT_ASSERT_MESSAGE("RemoveFixedGroup", UCSDK_Succ == iRet);
}

//²âÊÔÓÃÀý
void UTGroupAbsProxy::UTGroupAbsProxy_GetCustomGroupById()
{
	RemoveContact();	

	UCSDKCustomGroup group;
	group.name_ = "UTgroup1";
	int iRet = UCGroupAbsProxy::GetInstance()->AddCustomGroup(group);
	CPPUNIT_ASSERT_MESSAGE("AddCustomGroup", UCSDK_Succ == iRet);

	UCSDKCustomGroup group1;
	group1.name_ = "UTgroup2";
	iRet = UCGroupAbsProxy::GetInstance()->AddCustomGroup(group1);
	CPPUNIT_ASSERT_MESSAGE("AddCustomGroup", UCSDK_Succ == iRet);

	UCSDKCustomGroup group2;
	group2.name_ = "UTgroup3";
	iRet = UCGroupAbsProxy::GetInstance()->AddCustomGroup(group2);
	CPPUNIT_ASSERT_MESSAGE("AddCustomGroup", UCSDK_Succ == iRet);

	UCSDKCustomGroup group3;
	group3.name_ = "UTgroup4";
	iRet = UCGroupAbsProxy::GetInstance()->AddCustomGroup(group3);
	CPPUNIT_ASSERT_MESSAGE("AddCustomGroup", UCSDK_Succ == iRet);
	
	UCSDKCustomGroup groupFind;
	iRet = UCGroupAbsProxy::GetInstance()->GetCustomGroupById(groupFind, group.id_);
	CPPUNIT_ASSERT_MESSAGE("GetCustomGroupById", UCSDK_Succ == iRet);
	CPPUNIT_ASSERT_MESSAGE("GetCustomGroupById", groupFind.name_ == group.name_);

	UCSDKCustomGroup groupFind1;
	iRet = UCGroupAbsProxy::GetInstance()->GetCustomGroupById(groupFind1, group1.id_);
	CPPUNIT_ASSERT_MESSAGE("GetCustomGroupById", UCSDK_Succ == iRet);
	CPPUNIT_ASSERT_MESSAGE("GetCustomGroupById", groupFind1.name_ == group1.name_);

	UCSDKCustomGroup groupFind3;
	iRet = UCGroupAbsProxy::GetInstance()->GetCustomGroupById(groupFind3, group3.id_);
	CPPUNIT_ASSERT_MESSAGE("GetCustomGroupById", UCSDK_Succ == iRet);
	CPPUNIT_ASSERT_MESSAGE("GetCustomGroupById", groupFind3.name_ == group3.name_);

	
	iRet = UCGroupAbsProxy::GetInstance()->RemoveCustomGroup(group);
	CPPUNIT_ASSERT_MESSAGE("RemoveFixedGroup", UCSDK_Succ == iRet);	

	iRet = UCGroupAbsProxy::GetInstance()->RemoveCustomGroup(group1);
	CPPUNIT_ASSERT_MESSAGE("RemoveFixedGroup", UCSDK_Succ == iRet);	

	iRet = UCGroupAbsProxy::GetInstance()->RemoveCustomGroup(group2);
	CPPUNIT_ASSERT_MESSAGE("RemoveFixedGroup", UCSDK_Succ == iRet);	

	iRet = UCGroupAbsProxy::GetInstance()->RemoveCustomGroup(group3);
	CPPUNIT_ASSERT_MESSAGE("RemoveFixedGroup", UCSDK_Succ == iRet);		
}

//²âÊÔÓÃÀý
void UTGroupAbsProxy::UTGroupAbsProxy_GetCustomGrouplist()
{
	RemoveContact();	

	UCSDKCustomGroupList groupList;
	int iRet = UCGroupAbsProxy::GetInstance()->GetCustomGrouplist(groupList);
	CPPUNIT_ASSERT_MESSAGE("GetCustomGrouplist", UCSDK_Succ == iRet);

	UCSDKCustomGroup group;
	group.name_ = "UTgroup1";
	iRet = UCGroupAbsProxy::GetInstance()->AddCustomGroup(group);
	CPPUNIT_ASSERT_MESSAGE("AddCustomGroup", UCSDK_Succ == iRet);

	UCSDKCustomGroup group1;
	group1.name_ = "UTgroup2";
	iRet = UCGroupAbsProxy::GetInstance()->AddCustomGroup(group1);
	CPPUNIT_ASSERT_MESSAGE("AddCustomGroup", UCSDK_Succ == iRet);

	UCSDKCustomGroup group2;
	group2.name_ = "UTgroup3";
	iRet = UCGroupAbsProxy::GetInstance()->AddCustomGroup(group2);
	CPPUNIT_ASSERT_MESSAGE("AddCustomGroup", UCSDK_Succ == iRet);

	UCSDKCustomGroup group3;
	group3.name_ = "UTgroup4";
	iRet = UCGroupAbsProxy::GetInstance()->AddCustomGroup(group3);
	CPPUNIT_ASSERT_MESSAGE("AddCustomGroup", UCSDK_Succ == iRet);

	UCSDKCustomGroupList groupList1;
	iRet = UCGroupAbsProxy::GetInstance()->GetCustomGrouplist(groupList1);
	CPPUNIT_ASSERT_MESSAGE("GetCustomGrouplist", UCSDK_Succ == iRet);
	CPPUNIT_ASSERT_MESSAGE("GetCustomGrouplist", (groupList.size() + 4) == groupList1.size());	

	iRet = UCGroupAbsProxy::GetInstance()->RemoveCustomGroup(group);
	CPPUNIT_ASSERT_MESSAGE("RemoveFixedGroup", UCSDK_Succ == iRet);	

	iRet = UCGroupAbsProxy::GetInstance()->RemoveCustomGroup(group1);
	CPPUNIT_ASSERT_MESSAGE("RemoveFixedGroup", UCSDK_Succ == iRet);	

	iRet = UCGroupAbsProxy::GetInstance()->RemoveCustomGroup(group2);
	CPPUNIT_ASSERT_MESSAGE("RemoveFixedGroup", UCSDK_Succ == iRet);	

	iRet = UCGroupAbsProxy::GetInstance()->RemoveCustomGroup(group3);
	CPPUNIT_ASSERT_MESSAGE("RemoveFixedGroup", UCSDK_Succ == iRet);		
}

//²âÊÔÓÃÀý
void UTGroupAbsProxy::UTGroupAbsProxy_RemoveCustomGroup()
{
	RemoveContact();	

	UCSDKCustomGroupList groupList;
	int iRet = UCGroupAbsProxy::GetInstance()->GetCustomGrouplist(groupList);
	CPPUNIT_ASSERT_MESSAGE("GetCustomGrouplist", UCSDK_Succ == iRet);

	UCSDKCustomGroup group;
	group.name_ = "UTgroup1";
	iRet = UCGroupAbsProxy::GetInstance()->AddCustomGroup(group);
	CPPUNIT_ASSERT_MESSAGE("AddCustomGroup", UCSDK_Succ == iRet);

	UCSDKCustomGroup group1;
	group1.name_ = "UTgroup2";
	iRet = UCGroupAbsProxy::GetInstance()->AddCustomGroup(group1);
	CPPUNIT_ASSERT_MESSAGE("AddCustomGroup", UCSDK_Succ == iRet);

	UCSDKCustomGroup group2;
	group2.name_ = "UTgroup3";
	iRet = UCGroupAbsProxy::GetInstance()->AddCustomGroup(group2);
	CPPUNIT_ASSERT_MESSAGE("AddCustomGroup", UCSDK_Succ == iRet);

	UCSDKCustomGroup group3;
	group3.name_ = "UTgroup4";
	iRet = UCGroupAbsProxy::GetInstance()->AddCustomGroup(group3);
	CPPUNIT_ASSERT_MESSAGE("AddCustomGroup", UCSDK_Succ == iRet);

	UCSDKCustomGroupList groupList1;
	iRet = UCGroupAbsProxy::GetInstance()->GetCustomGrouplist(groupList1);
	CPPUNIT_ASSERT_MESSAGE("GetCustomGrouplist", UCSDK_Succ == iRet);
	CPPUNIT_ASSERT_MESSAGE("GetCustomGrouplist", (groupList.size() + 4) == groupList1.size());	

	iRet = UCGroupAbsProxy::GetInstance()->RemoveCustomGroup(group);
	CPPUNIT_ASSERT_MESSAGE("RemoveFixedGroup", UCSDK_Succ == iRet);	

	UCSDKCustomGroupList groupList2;
	iRet = UCGroupAbsProxy::GetInstance()->GetCustomGrouplist(groupList2);
	CPPUNIT_ASSERT_MESSAGE("GetCustomGrouplist", UCSDK_Succ == iRet);
	CPPUNIT_ASSERT_MESSAGE("GetCustomGrouplist", groupList1.size() == (groupList2.size() + 1));

	iRet = UCGroupAbsProxy::GetInstance()->RemoveCustomGroup(group1);
	CPPUNIT_ASSERT_MESSAGE("RemoveFixedGroup", UCSDK_Succ == iRet);	

	UCSDKCustomGroupList groupList3;
	iRet = UCGroupAbsProxy::GetInstance()->GetCustomGrouplist(groupList3);
	CPPUNIT_ASSERT_MESSAGE("GetCustomGrouplist", UCSDK_Succ == iRet);
	CPPUNIT_ASSERT_MESSAGE("GetCustomGrouplist", groupList1.size() == (groupList3.size() + 2));

	iRet = UCGroupAbsProxy::GetInstance()->RemoveCustomGroup(group2);
	CPPUNIT_ASSERT_MESSAGE("RemoveFixedGroup", UCSDK_Succ == iRet);	

	UCSDKCustomGroupList groupList4;
	iRet = UCGroupAbsProxy::GetInstance()->GetCustomGrouplist(groupList4);
	CPPUNIT_ASSERT_MESSAGE("GetCustomGrouplist", UCSDK_Succ == iRet);
	CPPUNIT_ASSERT_MESSAGE("GetCustomGrouplist", groupList1.size() == (groupList4.size() + 3));

	iRet = UCGroupAbsProxy::GetInstance()->RemoveCustomGroup(group3);
	CPPUNIT_ASSERT_MESSAGE("RemoveFixedGroup", UCSDK_Succ == iRet);	

	UCSDKCustomGroupList groupList5;
	iRet = UCGroupAbsProxy::GetInstance()->GetCustomGrouplist(groupList5);
	CPPUNIT_ASSERT_MESSAGE("GetCustomGrouplist", UCSDK_Succ == iRet);
	CPPUNIT_ASSERT_MESSAGE("GetCustomGrouplist", groupList.size() == groupList5.size());
}

//²âÊÔÓÃÀý
void UTGroupAbsProxy::UTGroupAbsProxy_AddContact()
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

	UCSDKContactList memberList2;
	iRet = UCContactMgrAbsProxy::GetInstance()->SearchContact(memberList2,"fjj35", "", true, 0, PAGE_SIZE, 0, recamount);
	CPPUNIT_ASSERT_MESSAGE("SearchContact", UCSDK_Succ == iRet);
	CPPUNIT_ASSERT_MESSAGE("SearchContact", 1 == memberList2.size());

	UCSDKCustomGroup group;
	group.name_ = "UTgroup1";
	iRet = UCGroupAbsProxy::GetInstance()->AddCustomGroup(group);
	CPPUNIT_ASSERT_MESSAGE("AddCustomGroup", UCSDK_Succ == iRet);

	iRet = UCGroupAbsProxy::GetInstance()->AddContact(group, memberList.at(0));
	CPPUNIT_ASSERT_MESSAGE("AddContact", UCSDK_Succ == iRet);

	UCSDKContactList allList1;
	iRet = UCGroupAbsProxy::GetInstance()->GetContactlist(group, allList1);
	CPPUNIT_ASSERT_MESSAGE("GetContactlist", UCSDK_Succ == iRet);
	CPPUNIT_ASSERT_MESSAGE("GetContactlist", 1 == allList1.size());

	iRet = UCGroupAbsProxy::GetInstance()->AddContact(group, memberList1.at(0));
	CPPUNIT_ASSERT_MESSAGE("AddContact", UCSDK_Succ == iRet);

	UCSDKContactList allList2;
	iRet = UCGroupAbsProxy::GetInstance()->GetContactlist(group, allList2);
	CPPUNIT_ASSERT_MESSAGE("GetContactlist", UCSDK_Succ == iRet);
	CPPUNIT_ASSERT_MESSAGE("GetContactlist", (allList1.size() + 1) == allList2.size());

	iRet = UCGroupAbsProxy::GetInstance()->AddContact(group, memberList2.at(0));
	CPPUNIT_ASSERT_MESSAGE("AddContact", UCSDK_Succ == iRet);

	UCSDKContactList allList3;
	iRet = UCGroupAbsProxy::GetInstance()->GetContactlist(group, allList3);
	CPPUNIT_ASSERT_MESSAGE("GetContactlist", UCSDK_Succ == iRet);
	CPPUNIT_ASSERT_MESSAGE("GetContactlist", (allList1.size() + 2) == allList3.size());

	iRet = UCGroupAbsProxy::GetInstance()->RemoveContact(group, memberList.at(0));
	CPPUNIT_ASSERT_MESSAGE("RemoveContact", UCSDK_Succ == iRet);

	iRet = UCGroupAbsProxy::GetInstance()->RemoveContact(group, memberList1.at(0));
	CPPUNIT_ASSERT_MESSAGE("RemoveContact", UCSDK_Succ == iRet);

	iRet = UCGroupAbsProxy::GetInstance()->RemoveContact(group, memberList2.at(0));
	CPPUNIT_ASSERT_MESSAGE("RemoveContact", UCSDK_Succ == iRet);
	
	iRet = UCGroupAbsProxy::GetInstance()->RemoveCustomGroup(group);
	CPPUNIT_ASSERT_MESSAGE("RemoveCustomGroup", UCSDK_Succ == iRet);	
}

//²âÊÔÓÃÀý
void UTGroupAbsProxy::UTGroupAbsProxy_RemoveContact()
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

	UCSDKContactList memberList2;
	iRet = UCContactMgrAbsProxy::GetInstance()->SearchContact(memberList2,"fjj35", "", true, 0, PAGE_SIZE, 0, recamount);
	CPPUNIT_ASSERT_MESSAGE("SearchContact", UCSDK_Succ == iRet);
	CPPUNIT_ASSERT_MESSAGE("SearchContact", 1 == memberList2.size());

	UCSDKCustomGroup group;
	group.name_ = "UTgroup1";
	iRet = UCGroupAbsProxy::GetInstance()->AddCustomGroup(group);
	CPPUNIT_ASSERT_MESSAGE("AddCustomGroup", UCSDK_Succ == iRet);

	iRet = UCGroupAbsProxy::GetInstance()->AddContact(group, memberList.at(0));
	CPPUNIT_ASSERT_MESSAGE("AddContact", UCSDK_Succ == iRet);

	UCSDKContactList allList1;
	iRet = UCGroupAbsProxy::GetInstance()->GetContactlist(group, allList1);
	CPPUNIT_ASSERT_MESSAGE("GetContactlist", UCSDK_Succ == iRet);
	CPPUNIT_ASSERT_MESSAGE("GetContactlist", 1 == allList1.size());

	iRet = UCGroupAbsProxy::GetInstance()->AddContact(group, memberList1.at(0));
	CPPUNIT_ASSERT_MESSAGE("AddContact", UCSDK_Succ == iRet);

	UCSDKContactList allList2;
	iRet = UCGroupAbsProxy::GetInstance()->GetContactlist(group, allList2);
	CPPUNIT_ASSERT_MESSAGE("GetContactlist", UCSDK_Succ == iRet);
	CPPUNIT_ASSERT_MESSAGE("GetContactlist", (allList1.size() + 1) == allList2.size());

	iRet = UCGroupAbsProxy::GetInstance()->AddContact(group, memberList2.at(0));
	CPPUNIT_ASSERT_MESSAGE("AddContact", UCSDK_Succ == iRet);

	UCSDKContactList allList3;
	iRet = UCGroupAbsProxy::GetInstance()->GetContactlist(group, allList3);
	CPPUNIT_ASSERT_MESSAGE("GetContactlist", UCSDK_Succ == iRet);
	CPPUNIT_ASSERT_MESSAGE("GetContactlist", (allList1.size() + 2) == allList3.size());

	iRet = UCGroupAbsProxy::GetInstance()->RemoveContact(group, memberList.at(0));
	CPPUNIT_ASSERT_MESSAGE("RemoveContact", UCSDK_Succ == iRet);

	UCSDKContactList allList4;
	iRet = UCGroupAbsProxy::GetInstance()->GetContactlist(group, allList4);
	CPPUNIT_ASSERT_MESSAGE("GetContactlist", UCSDK_Succ == iRet);
	CPPUNIT_ASSERT_MESSAGE("GetContactlist", (allList4.size() + 1) == allList3.size());

	iRet = UCGroupAbsProxy::GetInstance()->RemoveContact(group, memberList1.at(0));
	CPPUNIT_ASSERT_MESSAGE("RemoveContact", UCSDK_Succ == iRet);

	UCSDKContactList allList5;
	iRet = UCGroupAbsProxy::GetInstance()->GetContactlist(group, allList5);
	CPPUNIT_ASSERT_MESSAGE("GetContactlist", UCSDK_Succ == iRet);
	CPPUNIT_ASSERT_MESSAGE("GetContactlist", (allList5.size() + 2) == allList3.size());

	iRet = UCGroupAbsProxy::GetInstance()->RemoveContact(group, memberList2.at(0));
	CPPUNIT_ASSERT_MESSAGE("RemoveContact", UCSDK_Succ == iRet);

	iRet = UCGroupAbsProxy::GetInstance()->RemoveCustomGroup(group);
	CPPUNIT_ASSERT_MESSAGE("RemoveCustomGroup", UCSDK_Succ == iRet);	
}

//²âÊÔÓÃÀý
void UTGroupAbsProxy::UTGroupAbsProxy_Rename()
{	
	RemoveContact();
	
	UCSDKCustomGroup group;
	group.name_ = "UTgroup1";
	int iRet = UCGroupAbsProxy::GetInstance()->AddCustomGroup(group);
	CPPUNIT_ASSERT_MESSAGE("AddCustomGroup", UCSDK_Succ == iRet);
	
	std::string groupname = "eSDKClientGroup"; 
	iRet = UCGroupAbsProxy::GetInstance()->Rename(group, groupname);
	CPPUNIT_ASSERT_MESSAGE("Rename", UCSDK_Succ == iRet);
	
	UCSDKCustomGroup groupFind;
	iRet = UCGroupAbsProxy::GetInstance()->GetCustomGroupById(groupFind, group.id_);
	CPPUNIT_ASSERT_MESSAGE("GetCustomGroupById", UCSDK_Succ == iRet);
	CPPUNIT_ASSERT_MESSAGE("GetCustomGroupById", "eSDKClientGroup" == groupFind.name_);

	iRet = UCGroupAbsProxy::GetInstance()->RemoveCustomGroup(groupFind);
	CPPUNIT_ASSERT_MESSAGE("RemoveCustomGroup", UCSDK_Succ == iRet);	
}

void UTGroupAbsProxy::UTGroupAbsProxy_GetContactlist()
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

	UCSDKContactList memberList2;
	iRet = UCContactMgrAbsProxy::GetInstance()->SearchContact(memberList2,"fjj35", "", true, 0, PAGE_SIZE, 0, recamount);
	CPPUNIT_ASSERT_MESSAGE("SearchContact", UCSDK_Succ == iRet);
	CPPUNIT_ASSERT_MESSAGE("SearchContact", 1 == memberList2.size());

	UCSDKCustomGroup group;
	group.name_ = "UTgroup1";
	iRet = UCGroupAbsProxy::GetInstance()->AddCustomGroup(group);
	CPPUNIT_ASSERT_MESSAGE("AddCustomGroup", UCSDK_Succ == iRet);

	iRet = UCGroupAbsProxy::GetInstance()->AddContact(group, memberList.at(0));
	CPPUNIT_ASSERT_MESSAGE("AddContact", UCSDK_Succ == iRet);

	UCSDKContactList allList1;
	iRet = UCGroupAbsProxy::GetInstance()->GetContactlist(group, allList1);
	CPPUNIT_ASSERT_MESSAGE("GetContactlist", UCSDK_Succ == iRet);
	CPPUNIT_ASSERT_MESSAGE("GetContactlist", 1 == allList1.size());

	iRet = UCGroupAbsProxy::GetInstance()->AddContact(group, memberList1.at(0));
	CPPUNIT_ASSERT_MESSAGE("AddContact", UCSDK_Succ == iRet);

	UCSDKContactList allList2;
	iRet = UCGroupAbsProxy::GetInstance()->GetContactlist(group, allList2);
	CPPUNIT_ASSERT_MESSAGE("GetContactlist", UCSDK_Succ == iRet);
	CPPUNIT_ASSERT_MESSAGE("GetContactlist", (allList1.size() + 1) == allList2.size());

	iRet = UCGroupAbsProxy::GetInstance()->AddContact(group, memberList2.at(0));
	CPPUNIT_ASSERT_MESSAGE("AddContact", UCSDK_Succ == iRet);

	UCSDKContactList allList3;
	iRet = UCGroupAbsProxy::GetInstance()->GetContactlist(group, allList3);
	CPPUNIT_ASSERT_MESSAGE("GetContactlist", UCSDK_Succ == iRet);
	CPPUNIT_ASSERT_MESSAGE("GetContactlist", (allList1.size() + 2) == allList3.size());

	iRet = UCGroupAbsProxy::GetInstance()->RemoveContact(group, memberList.at(0));
	CPPUNIT_ASSERT_MESSAGE("RemoveContact", UCSDK_Succ == iRet);

	iRet = UCGroupAbsProxy::GetInstance()->RemoveContact(group, memberList1.at(0));
	CPPUNIT_ASSERT_MESSAGE("RemoveContact", UCSDK_Succ == iRet);

	iRet = UCGroupAbsProxy::GetInstance()->RemoveContact(group, memberList2.at(0));
	CPPUNIT_ASSERT_MESSAGE("RemoveContact", UCSDK_Succ == iRet);

	iRet = UCGroupAbsProxy::GetInstance()->RemoveCustomGroup(group);
	CPPUNIT_ASSERT_MESSAGE("RemoveCustomGroup", UCSDK_Succ == iRet);	
}

//²âÊÔÓÃÀý
void UTGroupAbsProxy::UTGroupAbsProxy_FixedGroup_AddContact()
{
	RemoveContact();	

	UCSDKFixedGroup group;
	group.name_ = "UTFixedgroup1";
	int iRet = UCGroupAbsProxy::GetInstance()->AddFixedGroup(group);
	CPPUNIT_ASSERT_MESSAGE("AddFixedGroup", UCSDK_Succ == iRet);

	UCSDKContactList memberList;
	const int PAGE_SIZE = 2;
	int recamount = 0;
	iRet = UCContactMgrAbsProxy::GetInstance()->SearchContact(memberList,"fjj23", "", true, 0, PAGE_SIZE, 0, recamount);
	CPPUNIT_ASSERT_MESSAGE("SearchContact", UCSDK_Succ == iRet);
	CPPUNIT_ASSERT_MESSAGE("SearchContact", 1 == memberList.size());

	iRet = UCGroupAbsProxy::GetInstance()->AddContact(group, memberList.at(0));
	CPPUNIT_ASSERT_MESSAGE("AddContact", UCSDK_Succ == iRet);

	UCSDKContactList allList;
	iRet = UCGroupAbsProxy::GetInstance()->GetContactlist(group, allList);
	CPPUNIT_ASSERT_MESSAGE("GetContactlist", UCSDK_Succ == iRet);

	UCSDKContactList memberList1;
	iRet = UCContactMgrAbsProxy::GetInstance()->SearchContact(memberList1,"fjj33", "", true, 0, PAGE_SIZE, 0, recamount);
	CPPUNIT_ASSERT_MESSAGE("SearchContact", UCSDK_Succ == iRet);
	CPPUNIT_ASSERT_MESSAGE("SearchContact", 1 == memberList1.size());

	iRet = UCGroupAbsProxy::GetInstance()->AddContact(group, memberList1.at(0));
	CPPUNIT_ASSERT_MESSAGE("AddContact", UCSDK_Succ == iRet);

	UCSDKContactList allList1;
	iRet = UCGroupAbsProxy::GetInstance()->GetContactlist(group, allList1);
	CPPUNIT_ASSERT_MESSAGE("GetContactlist", UCSDK_Succ == iRet);
	CPPUNIT_ASSERT_MESSAGE("GetContactlist", (allList.size() + 1) == allList1.size());

	iRet = UCGroupAbsProxy::GetInstance()->RemoveFixedGroup(group);
	CPPUNIT_ASSERT_MESSAGE("RemoveFixedGroup", UCSDK_Succ == iRet);

	UCSDKContactList allList2;
	iRet = UCContactMgrAbsProxy::GetInstance()->GetAllContactlist(allList2);
	CPPUNIT_ASSERT_MESSAGE("GetAllContactlist", UCSDK_Succ == iRet);
	CPPUNIT_ASSERT_MESSAGE("GetAllContactlist", 1 == allList2.size());
}

//²âÊÔÓÃÀý
void UTGroupAbsProxy::UTGroupAbsProxy_FixedGroup_RemoveContact()
{
	RemoveContact();	

	UCSDKFixedGroup group;
	group.name_ = "UTFixedgroup1";
	int iRet = UCGroupAbsProxy::GetInstance()->AddFixedGroup(group);
	CPPUNIT_ASSERT_MESSAGE("AddFixedGroup", UCSDK_Succ == iRet);

	UCSDKContactList memberList;
	const int PAGE_SIZE = 2;
	int recamount = 0;
	iRet = UCContactMgrAbsProxy::GetInstance()->SearchContact(memberList,"fjj23", "", true, 0, PAGE_SIZE, 0, recamount);
	CPPUNIT_ASSERT_MESSAGE("SearchContact", UCSDK_Succ == iRet);
	CPPUNIT_ASSERT_MESSAGE("SearchContact", 1 == memberList.size());

	iRet = UCGroupAbsProxy::GetInstance()->AddContact(group, memberList.at(0));
	CPPUNIT_ASSERT_MESSAGE("AddContact", UCSDK_Succ == iRet);

	UCSDKContactList allList;
	iRet = UCGroupAbsProxy::GetInstance()->GetContactlist(group, allList);
	CPPUNIT_ASSERT_MESSAGE("GetContactlist", UCSDK_Succ == iRet);

	UCSDKContactList memberList1;
	iRet = UCContactMgrAbsProxy::GetInstance()->SearchContact(memberList1,"fjj33", "", true, 0, PAGE_SIZE, 0, recamount);
	CPPUNIT_ASSERT_MESSAGE("SearchContact", UCSDK_Succ == iRet);
	CPPUNIT_ASSERT_MESSAGE("SearchContact", 1 == memberList1.size());

	iRet = UCGroupAbsProxy::GetInstance()->AddContact(group, memberList1.at(0));
	CPPUNIT_ASSERT_MESSAGE("AddContact", UCSDK_Succ == iRet);

	UCSDKContactList allList1;
	iRet = UCGroupAbsProxy::GetInstance()->GetContactlist(group, allList1);
	CPPUNIT_ASSERT_MESSAGE("GetContactlist", UCSDK_Succ == iRet);
	CPPUNIT_ASSERT_MESSAGE("GetContactlist", (allList.size() + 1) == allList1.size());

	UCSDKContactList memberList2;
	iRet = UCContactMgrAbsProxy::GetInstance()->SearchContact(memberList2,"fjj34", "", true, 0, PAGE_SIZE, 0, recamount);
	CPPUNIT_ASSERT_MESSAGE("SearchContact", UCSDK_Succ == iRet);
	CPPUNIT_ASSERT_MESSAGE("SearchContact", 1 == memberList2.size());

	iRet = UCGroupAbsProxy::GetInstance()->AddContact(group, memberList2.at(0));
	CPPUNIT_ASSERT_MESSAGE("AddContact", UCSDK_Succ == iRet);

	UCSDKContactList allList2;
	iRet = UCGroupAbsProxy::GetInstance()->GetContactlist(group, allList2);
	CPPUNIT_ASSERT_MESSAGE("GetContactlist", UCSDK_Succ == iRet);
	CPPUNIT_ASSERT_MESSAGE("GetContactlist", (allList.size() + 2) == allList2.size());

	
	iRet = UCGroupAbsProxy::GetInstance()->RemoveContact(group, memberList.at(0));
	CPPUNIT_ASSERT_MESSAGE("RemoveContact", UCSDK_Succ == iRet);

	UCSDKContactList allList3;
	iRet = UCGroupAbsProxy::GetInstance()->GetContactlist(group, allList3);
	CPPUNIT_ASSERT_MESSAGE("GetContactlist", UCSDK_Succ == iRet);
	CPPUNIT_ASSERT_MESSAGE("GetContactlist", (allList3.size() + 1) == allList2.size());

	iRet = UCGroupAbsProxy::GetInstance()->RemoveContact(group, memberList1.at(0));
	CPPUNIT_ASSERT_MESSAGE("RemoveContact", UCSDK_Succ == iRet);

	UCSDKContactList allList4;
	iRet = UCGroupAbsProxy::GetInstance()->GetContactlist(group, allList4);
	CPPUNIT_ASSERT_MESSAGE("GetContactlist", UCSDK_Succ == iRet);
	CPPUNIT_ASSERT_MESSAGE("GetContactlist", (allList4.size() + 2) == allList2.size());

	iRet = UCGroupAbsProxy::GetInstance()->RemoveFixedGroup(group);
	CPPUNIT_ASSERT_MESSAGE("RemoveFixedGroup", UCSDK_Succ == iRet);

	UCSDKContactList allList5;
	iRet = UCContactMgrAbsProxy::GetInstance()->GetAllContactlist(allList5);
	CPPUNIT_ASSERT_MESSAGE("GetAllContactlist", UCSDK_Succ == iRet);
	CPPUNIT_ASSERT_MESSAGE("GetAllContactlist", 1 == allList5.size());
}

//²âÊÔÓÃÀý
void UTGroupAbsProxy::UTGroupAbsProxy_FixedGroup_Rename()
{	
	RemoveContact();

	UCSDKFixedGroup group;
	group.name_ = "UTFixedgroup1";
	int iRet = UCGroupAbsProxy::GetInstance()->AddFixedGroup(group);
	CPPUNIT_ASSERT_MESSAGE("AddFixedGroup", UCSDK_Succ == iRet);

	std::string groupname = "Fixed_eSDKClientGroup"; 
	iRet = UCGroupAbsProxy::GetInstance()->Rename(group, groupname);
	CPPUNIT_ASSERT_MESSAGE("Rename", UCSDK_Succ == iRet);

	UCSDKFixedGroup groupFind;
	iRet = UCGroupAbsProxy::GetInstance()->GetFixedGroupByID(groupFind, group.id_);
	CPPUNIT_ASSERT_MESSAGE("GetFixedGroupByID", UCSDK_Succ == iRet);
	CPPUNIT_ASSERT_MESSAGE("GetFixedGroupByID", "Fixed_eSDKClientGroup" == groupFind.name_);

	iRet = UCGroupAbsProxy::GetInstance()->RemoveFixedGroup(groupFind);
	CPPUNIT_ASSERT_MESSAGE("RemoveFixedGroup", UCSDK_Succ == iRet);	
}

//²âÊÔÓÃÀý
void UTGroupAbsProxy::UTGroupAbsProxy_FixedGroup_GetContactlist()
{
	RemoveContact();	

	UCSDKFixedGroup group;
	group.name_ = "UTFixedgroup1";
	int iRet = UCGroupAbsProxy::GetInstance()->AddFixedGroup(group);
	CPPUNIT_ASSERT_MESSAGE("AddFixedGroup", UCSDK_Succ == iRet);

	UCSDKContactList memberList;
	const int PAGE_SIZE = 2;
	int recamount = 0;
	iRet = UCContactMgrAbsProxy::GetInstance()->SearchContact(memberList,"fjj23", "", true, 0, PAGE_SIZE, 0, recamount);
	CPPUNIT_ASSERT_MESSAGE("SearchContact", UCSDK_Succ == iRet);
	CPPUNIT_ASSERT_MESSAGE("SearchContact", 1 == memberList.size());

	iRet = UCGroupAbsProxy::GetInstance()->AddContact(group, memberList.at(0));
	CPPUNIT_ASSERT_MESSAGE("AddContact", UCSDK_Succ == iRet);

	UCSDKContactList allList;
	iRet = UCGroupAbsProxy::GetInstance()->GetContactlist(group, allList);
	CPPUNIT_ASSERT_MESSAGE("GetContactlist", UCSDK_Succ == iRet);

	UCSDKContactList memberList1;
	iRet = UCContactMgrAbsProxy::GetInstance()->SearchContact(memberList1,"fjj33", "", true, 0, PAGE_SIZE, 0, recamount);
	CPPUNIT_ASSERT_MESSAGE("SearchContact", UCSDK_Succ == iRet);
	CPPUNIT_ASSERT_MESSAGE("SearchContact", 1 == memberList1.size());

	iRet = UCGroupAbsProxy::GetInstance()->AddContact(group, memberList1.at(0));
	CPPUNIT_ASSERT_MESSAGE("AddContact", UCSDK_Succ == iRet);

	UCSDKContactList allList1;
	iRet = UCGroupAbsProxy::GetInstance()->GetContactlist(group, allList1);
	CPPUNIT_ASSERT_MESSAGE("GetContactlist", UCSDK_Succ == iRet);
	CPPUNIT_ASSERT_MESSAGE("GetContactlist", (allList.size() + 1) == allList1.size());

	iRet = UCGroupAbsProxy::GetInstance()->RemoveFixedGroup(group);
	CPPUNIT_ASSERT_MESSAGE("RemoveFixedGroup", UCSDK_Succ == iRet);

	UCSDKContactList allList2;
	iRet = UCContactMgrAbsProxy::GetInstance()->GetAllContactlist(allList2);
	CPPUNIT_ASSERT_MESSAGE("GetAllContactlist", UCSDK_Succ == iRet);
	CPPUNIT_ASSERT_MESSAGE("GetAllContactlist", 1 == allList2.size());
}

//²âÊÔÓÃÀý
void UTGroupAbsProxy::UTGroupAbsProxy_FixedGroup_ChangeGroupInfo()
{	
	RemoveContact();

	UCSDKFixedGroup group;
	group.name_ = "UTFixedgroup1";
	int iRet = UCGroupAbsProxy::GetInstance()->AddFixedGroup(group);
	CPPUNIT_ASSERT_MESSAGE("AddFixedGroup", UCSDK_Succ == iRet);

	group.name_ = "Fixed_eSDKClientGroup";
	iRet = UCGroupAbsProxy::GetInstance()->ChangeGroupInfo(group);
	CPPUNIT_ASSERT_MESSAGE("Rename", UCSDK_Succ == iRet);

	
	UCSDKFixedGroup groupFind;
	iRet = UCGroupAbsProxy::GetInstance()->GetFixedGroupByID(groupFind, group.id_);
	CPPUNIT_ASSERT_MESSAGE("GetFixedGroupByID", UCSDK_Succ == iRet);
	CPPUNIT_ASSERT_MESSAGE("GetFixedGroupByID", "Fixed_eSDKClientGroup" == groupFind.name_);

	groupFind.capacity_ = 640;
	iRet = UCGroupAbsProxy::GetInstance()->ChangeGroupInfo(groupFind);
	CPPUNIT_ASSERT_MESSAGE("Rename", UCSDK_Succ == iRet);

	UCSDKFixedGroup groupFind1;
	iRet = UCGroupAbsProxy::GetInstance()->GetFixedGroupByID(groupFind1, groupFind.id_);
	CPPUNIT_ASSERT_MESSAGE("GetFixedGroupByID", UCSDK_Succ == iRet);
	CPPUNIT_ASSERT_MESSAGE("GetFixedGroupByID", 640 == groupFind1.capacity_);

	iRet = UCGroupAbsProxy::GetInstance()->RemoveFixedGroup(groupFind);
	CPPUNIT_ASSERT_MESSAGE("RemoveFixedGroup", UCSDK_Succ == iRet);	
}

//²âÊÔÓÃÀý
void UTGroupAbsProxy::UTGroupAbsProxy_FixedGroup_ChangeGroupOwner()
{	
	RemoveContact();

// 	UCSDKContactList memberList;
// 	const int PAGE_SIZE = 2;
// 	int recamount = 0;
// 	int iRet = UCContactMgrAbsProxy::GetInstance()->SearchContact(memberList,"fjj23", "", true, 0, PAGE_SIZE, 0, recamount);
// 	CPPUNIT_ASSERT_MESSAGE("SearchContact", UCSDK_Succ == iRet);
// 	CPPUNIT_ASSERT_MESSAGE("SearchContact", 1 == memberList.size());
// 
// 	UCSDKFixedGroupList groupList;
// 	iRet = UCGroupAbsProxy::GetInstance()->RefreshFixedGrouplist(groupList);
// 	CPPUNIT_ASSERT_MESSAGE("AddFixedGroup", UCSDK_Succ == iRet);
// 	
// 	iRet = UCGroupAbsProxy::GetInstance()->ChangeGroupOwner(groupList.at(0), memberList.at(0));
// 	CPPUNIT_ASSERT_MESSAGE("Rename", UCSDK_Succ == iRet);
// 
// 	UCSDKFixedGroup groupFind;
// 	iRet = UCGroupAbsProxy::GetInstance()->GetFixedGroupByID(groupFind, groupList.at(0).id_);
// 	CPPUNIT_ASSERT_MESSAGE("GetFixedGroupByID", UCSDK_Succ == iRet);
// 	CPPUNIT_ASSERT_MESSAGE("GetFixedGroupByID", memberList.at(0).uri_ == groupFind.owneruri_);
			
}

//²âÊÔÓÃÀý
void UTGroupAbsProxy::UTGroupAbsProxy_FixedGroup_Refresh()
{	
	RemoveContact();

	UCSDKFixedGroup group;
	group.name_ = "UTFixedgroup1";
	int iRet = UCGroupAbsProxy::GetInstance()->AddFixedGroup(group);
	CPPUNIT_ASSERT_MESSAGE("AddFixedGroup", UCSDK_Succ == iRet);
	
	UCSDKContactList memberList;
	const int PAGE_SIZE = 2;
	int recamount = 0;
	iRet = UCContactMgrAbsProxy::GetInstance()->SearchContact(memberList,"fjj23", "", true, 0, PAGE_SIZE, 0, recamount);
	CPPUNIT_ASSERT_MESSAGE("SearchContact", UCSDK_Succ == iRet);
	CPPUNIT_ASSERT_MESSAGE("SearchContact", 1 == memberList.size());

	iRet = UCGroupAbsProxy::GetInstance()->AddContact(group, memberList.at(0));
	CPPUNIT_ASSERT_MESSAGE("AddContact", UCSDK_Succ == iRet);

	UCSDKContactList memberList1;
	iRet = UCContactMgrAbsProxy::GetInstance()->SearchContact(memberList1,"fjj33", "", true, 0, PAGE_SIZE, 0, recamount);
	CPPUNIT_ASSERT_MESSAGE("SearchContact", UCSDK_Succ == iRet);
	CPPUNIT_ASSERT_MESSAGE("SearchContact", 1 == memberList1.size());

	iRet = UCGroupAbsProxy::GetInstance()->AddContact(group, memberList1.at(0));
	CPPUNIT_ASSERT_MESSAGE("AddContact", UCSDK_Succ == iRet);
	
	UCSDKContactList allList;
	iRet = UCGroupAbsProxy::GetInstance()->GetContactlist(group, allList);
	CPPUNIT_ASSERT_MESSAGE("GetContactlist", UCSDK_Succ == iRet);

	UCSDKContactList allList1;
	iRet = UCGroupAbsProxy::GetInstance()->Refresh(group, allList1);
	CPPUNIT_ASSERT_MESSAGE("Refresh", UCSDK_Succ == iRet);
	CPPUNIT_ASSERT_MESSAGE("Refresh", allList.size() == allList1.size());

	iRet = UCGroupAbsProxy::GetInstance()->RemoveFixedGroup(group);
	CPPUNIT_ASSERT_MESSAGE("RemoveFixedGroup", UCSDK_Succ == iRet);	
}

//²âÊÔÓÃÀý
void UTGroupAbsProxy::UTGroupAbsProxy_FixedGroup_Refresh_SYNC()
{	
	RemoveContact();

	UCSDKFixedGroup group;
	group.name_ = "UTFixedgroup1";
	int iRet = UCGroupAbsProxy::GetInstance()->AddFixedGroup(group);
	CPPUNIT_ASSERT_MESSAGE("AddFixedGroup", UCSDK_Succ == iRet);

	UCSDKContactList memberList;
	const int PAGE_SIZE = 2;
	int recamount = 0;
	iRet = UCContactMgrAbsProxy::GetInstance()->SearchContact(memberList,"fjj23", "", true, 0, PAGE_SIZE, 0, recamount);
	CPPUNIT_ASSERT_MESSAGE("SearchContact", UCSDK_Succ == iRet);
	CPPUNIT_ASSERT_MESSAGE("SearchContact", 1 == memberList.size());

	iRet = UCGroupAbsProxy::GetInstance()->AddContact(group, memberList.at(0));
	CPPUNIT_ASSERT_MESSAGE("AddContact", UCSDK_Succ == iRet);

	UCSDKContactList memberList1;
	iRet = UCContactMgrAbsProxy::GetInstance()->SearchContact(memberList1,"fjj33", "", true, 0, PAGE_SIZE, 0, recamount);
	CPPUNIT_ASSERT_MESSAGE("SearchContact", UCSDK_Succ == iRet);
	CPPUNIT_ASSERT_MESSAGE("SearchContact", 1 == memberList1.size());

	iRet = UCGroupAbsProxy::GetInstance()->AddContact(group, memberList1.at(0));
	CPPUNIT_ASSERT_MESSAGE("AddContact", UCSDK_Succ == iRet);

	UCSDKContactList allList;
	iRet = UCGroupAbsProxy::GetInstance()->GetContactlist(group, allList);
	CPPUNIT_ASSERT_MESSAGE("GetContactlist", UCSDK_Succ == iRet);

	iRet = UCGroupAbsProxy::GetInstance()->Refresh(group, true);
	CPPUNIT_ASSERT_MESSAGE("Refresh", UCSDK_Succ == iRet);
	
	UCSDKContactList allList1;
	iRet = UCGroupAbsProxy::GetInstance()->GetContactlist(group, allList1);
	CPPUNIT_ASSERT_MESSAGE("GetContactlist", UCSDK_Succ == iRet);	
	CPPUNIT_ASSERT_MESSAGE("Refresh", allList.size() == allList1.size());

	iRet = UCGroupAbsProxy::GetInstance()->RemoveFixedGroup(group);
	CPPUNIT_ASSERT_MESSAGE("RemoveFixedGroup", UCSDK_Succ == iRet);	
}

//¸¨Öúº¯Êý
void UTGroupAbsProxy::UTSignIn()
{
	int iRet = UCSDKAbsProxy::GetInstance()->Login("fjj56", "UcAAaa_11");	
	CPPUNIT_ASSERT_MESSAGE("SignIn", UCSDK_Succ == iRet);
}
void UTGroupAbsProxy::UTSignOut()
{
	ctk::sleep(100);
	int iRet = UCSDKAbsProxy::GetInstance()->Logout();
	CPPUNIT_ASSERT_MESSAGE("SignOut", UCSDK_Succ == iRet);
}

//call back
void CALLBACK UTGroupAbsProxy::TurnOnClientSignInNotify(int state,const std::string &reason)
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

void UTGroupAbsProxy::RemoveContact()
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