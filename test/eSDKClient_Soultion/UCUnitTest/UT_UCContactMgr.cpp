#include "stdafx.h"
#include "UT_UCContactMgr.h"
#include "UT_UCGroup.h"
#include "UCUnitTest.h"

CPPUNIT_TEST_SUITE_NAMED_REGISTRATION(UT_UCContactMgr, "UCUnitTest");

UT_UCContactMgr::UT_UCContactMgr()
{

}

UT_UCContactMgr::~UT_UCContactMgr()
{

}

void UT_UCContactMgr::setUp()
{
	UCUnitTest* pUCUnitTest = UCUnitTest::Instance();
	bool bRet = pUCUnitTest->Start();
	CPPUNIT_ASSERT_MESSAGE("Start", bRet);
}

void UT_UCContactMgr::tearDown()
{
	UCUnitTest* pUCUnitTest = UCUnitTest::Instance();
	bool bRet = pUCUnitTest->Stop();
	CPPUNIT_ASSERT_MESSAGE("Stop", bRet);
}

void UT_UCContactMgr::UT_GetAllContactlist()
{
	RemoveAllContactExceptSelf();
	UT_UCGroup::RemoveAllCustomGroupExceptDefault();

	//获取联系人列表
	std::vector<UCContact> vecList;
	GetAllContactlist_(vecList);
	CPPUNIT_ASSERT_MESSAGE("GetAllContactlist", 1 == vecList.size());

	UCCustomGroup customgroup;
	memset(&customgroup, 0, sizeof(customgroup));
	memcpy(customgroup.id_, "-1", strlen("-1"));
	UCContact contact;
	memset(&contact, 0, sizeof(contact));
	memcpy(contact.ucAcc_, "bby01", strlen("bby01"));

	UCUnitTest* pUCUnitTest = UCUnitTest::Instance();
	int iRet = pUCUnitTest->m_fpAddContactToCustomGroup(&customgroup, &contact);
	CPPUNIT_ASSERT_MESSAGE("AddContactToCustomGroup", 0 == iRet);

	vecList.clear();
	GetAllContactlist_(vecList);
	CPPUNIT_ASSERT_MESSAGE("GetAllContactlist", 2 == vecList.size());
}

void UT_UCContactMgr::UT_GetContactByAccount()
{
	UCContact contact;
	memset(&contact, 0, sizeof(contact));
	
	UCUnitTest* pUCUnitTest = UCUnitTest::Instance();
	int iRet = pUCUnitTest->m_fpGetContactByAccount("bby01", &contact);
	CPPUNIT_ASSERT_MESSAGE("GetContactByAccount", 0 == iRet);
	CPPUNIT_ASSERT_MESSAGE("GetContactByAccount", 0 == strcmp(contact.ucAcc_, "bby01"));

	memset(&contact, 0, sizeof(contact));
	iRet = pUCUnitTest->m_fpGetContactByAccount("yubinbin", &contact);
	CPPUNIT_ASSERT_MESSAGE("GetContactByAccount", 0 != iRet);
	CPPUNIT_ASSERT_MESSAGE("GetContactByAccount", 0 == strcmp(contact.ucAcc_, ""));

	memset(&contact, 0, sizeof(contact));
	iRet = pUCUnitTest->m_fpGetContactByAccount("ErrorUcAcc", &contact);
	CPPUNIT_ASSERT_MESSAGE("GetContactByAccount", 0 != iRet);
	CPPUNIT_ASSERT_MESSAGE("GetContactByAccount", 0 == strcmp(contact.ucAcc_, ""));
}

void UT_UCContactMgr::UT_GetContactById()
{
	UCUnitTest* pUCUnitTest = UCUnitTest::Instance();

	//获取联系人列表
	std::vector<UCContact> vecList;
	GetAllContactlist_(vecList);
	CPPUNIT_ASSERT_MESSAGE("GetAllContactlist", 2 == vecList.size());

	std::vector<UCContact>::iterator itor = vecList.begin();
	for (; itor != vecList.end(); itor++)
	{
		if (0 == strcmp(itor->ucAcc_, pUCUnitTest->m_strAcc.c_str()))
		{
			continue;
		}

		UCContact contact;
		memset(&contact, 0, sizeof(contact));
		int iRet = pUCUnitTest->m_fpGetContactById(itor->id_, &contact);
		CPPUNIT_ASSERT_MESSAGE("GetContactById", 0 == iRet);
		CPPUNIT_ASSERT_MESSAGE("GetContactById", 0 == strcmp(contact.ucAcc_, itor->ucAcc_));

		memset(&contact, 0, sizeof(contact));
		iRet = pUCUnitTest->m_fpGetContactById("ErrorId", &contact);
		CPPUNIT_ASSERT_MESSAGE("GetContactById", 0 != iRet);
		CPPUNIT_ASSERT_MESSAGE("GetContactById", 0 == strcmp(contact.ucAcc_, ""));

		break;
	}
}

void UT_UCContactMgr::UT_GetContactByPhoneNum()
{
	UCUnitTest* pUCUnitTest = UCUnitTest::Instance();

	//获取联系人列表
	std::vector<UCContact> vecList;
	GetAllContactlist_(vecList);
	CPPUNIT_ASSERT_MESSAGE("GetAllContactlist", 2 == vecList.size());

	std::vector<UCContact>::iterator itor = vecList.begin();
	for (; itor != vecList.end(); itor++)
	{
		if (0 == strcmp(itor->ucAcc_, pUCUnitTest->m_strAcc.c_str()))
		{
			continue;
		}

		UCContact contact;
		memset(&contact, 0, sizeof(contact));
		std::string phoneNum;
		GetPhoneNumByUri(itor->uri_, phoneNum);
		int iRet = pUCUnitTest->m_fpGetContactByPhoneNum(phoneNum.c_str(), &contact);
		CPPUNIT_ASSERT_MESSAGE("GetContactByPhoneNum", 0 == iRet);
		CPPUNIT_ASSERT_MESSAGE("GetContactByPhoneNum", 0 == strcmp(contact.ucAcc_, itor->ucAcc_));

		memset(&contact, 0, sizeof(contact));
		iRet = pUCUnitTest->m_fpGetContactByPhoneNum("ErrorPhoneNum", &contact);
		CPPUNIT_ASSERT_MESSAGE("GetContactByPhoneNum", 0 != iRet);
		CPPUNIT_ASSERT_MESSAGE("GetContactByPhoneNum", 0 == strcmp(contact.ucAcc_, ""));

		break;
	}
}

void UT_UCContactMgr::UT_GetContactByUri()
{
	UCUnitTest* pUCUnitTest = UCUnitTest::Instance();

	//获取联系人列表
	std::vector<UCContact> vecList;
	GetAllContactlist_(vecList);
	CPPUNIT_ASSERT_MESSAGE("GetAllContactlist", 2 == vecList.size());

	std::vector<UCContact>::iterator itor = vecList.begin();
	for (; itor != vecList.end(); itor++)
	{
		if (0 == strcmp(itor->ucAcc_, pUCUnitTest->m_strAcc.c_str()))
		{
			continue;
		}

		UCContact contact;
		memset(&contact, 0, sizeof(contact));
		int iRet = pUCUnitTest->m_fpGetContactByUri(itor->uri_, &contact);
		CPPUNIT_ASSERT_MESSAGE("GetContactByUri", 0 == iRet);
		CPPUNIT_ASSERT_MESSAGE("GetContactByUri", 0 == strcmp(contact.ucAcc_, itor->ucAcc_));

		memset(&contact, 0, sizeof(contact));
		iRet = pUCUnitTest->m_fpGetContactByUri("ErrorUri", &contact);
		CPPUNIT_ASSERT_MESSAGE("GetContactByUri", 0 != iRet);
		CPPUNIT_ASSERT_MESSAGE("GetContactByUri", 0 == strcmp(contact.ucAcc_, ""));

		break;
	}
}

void UT_UCContactMgr::UT_HasContact()
{
	UCUnitTest* pUCUnitTest = UCUnitTest::Instance();

	//获取联系人列表
	std::vector<UCContact> vecList;
	GetAllContactlist_(vecList);
	CPPUNIT_ASSERT_MESSAGE("GetAllContactlist", 2 == vecList.size());

	std::vector<UCContact>::iterator itor = vecList.begin();
	for (; itor != vecList.end(); itor++)
	{
		if (0 == strcmp(itor->ucAcc_, pUCUnitTest->m_strAcc.c_str()))
		{
			continue;
		}

		int iRet = pUCUnitTest->m_fpHasContact(itor->uri_);
		CPPUNIT_ASSERT_MESSAGE("HasContact", 0 == iRet);

		iRet = pUCUnitTest->m_fpHasContact("ErrorUri");
		CPPUNIT_ASSERT_MESSAGE("HasContact", 0 != iRet);

		break;
	}
}

void UT_UCContactMgr::UT_RefreshContactByAccount()
{
	UCContact contact;
	memset(&contact, 0, sizeof(contact));

	UCUnitTest* pUCUnitTest = UCUnitTest::Instance();
	int iRet = pUCUnitTest->m_fpRefreshContactByAccount("bby01", &contact);
	CPPUNIT_ASSERT_MESSAGE("RefreshContactByAccount", 0 == iRet);
	CPPUNIT_ASSERT_MESSAGE("RefreshContactByAccount", 0 == strcmp(contact.ucAcc_, "bby01"));

	memset(&contact, 0, sizeof(contact));
	iRet = pUCUnitTest->m_fpRefreshContactByAccount("yubinbin", &contact);
	CPPUNIT_ASSERT_MESSAGE("RefreshContactByAccount", 0 != iRet);
	CPPUNIT_ASSERT_MESSAGE("RefreshContactByAccount", 0 == strcmp(contact.ucAcc_, ""));

	memset(&contact, 0, sizeof(contact));
	iRet = pUCUnitTest->m_fpRefreshContactByAccount("ErrorUcAcc", &contact);
	CPPUNIT_ASSERT_MESSAGE("RefreshContactByAccount", 0 != iRet);
	CPPUNIT_ASSERT_MESSAGE("RefreshContactByAccount", 0 == strcmp(contact.ucAcc_, ""));
}

void UT_UCContactMgr::UT_RefreshContactById()
{
	UCUnitTest* pUCUnitTest = UCUnitTest::Instance();

	//获取联系人列表
	std::vector<UCContact> vecList;
	GetAllContactlist_(vecList);
	CPPUNIT_ASSERT_MESSAGE("GetAllContactlist", 2 == vecList.size());

	std::vector<UCContact>::iterator itor = vecList.begin();
	for (; itor != vecList.end(); itor++)
	{
		if (0 == strcmp(itor->ucAcc_, pUCUnitTest->m_strAcc.c_str()))
		{
			continue;
		}

		UCContact contact;
		memset(&contact, 0, sizeof(contact));
		int iRet = pUCUnitTest->m_fpRefreshContactById(itor->id_, &contact);
		CPPUNIT_ASSERT_MESSAGE("RefreshContactById", 0 == iRet);
		CPPUNIT_ASSERT_MESSAGE("RefreshContactById", 0 == strcmp(contact.ucAcc_, itor->ucAcc_));

		memset(&contact, 0, sizeof(contact));
		iRet = pUCUnitTest->m_fpRefreshContactById("ErrorId", &contact);
		CPPUNIT_ASSERT_MESSAGE("RefreshContactById", 0 != iRet);
		CPPUNIT_ASSERT_MESSAGE("RefreshContactById", 0 == strcmp(contact.ucAcc_, ""));

		break;
	}
}

void UT_UCContactMgr::UT_RefreshContactByUri()
{
	UCUnitTest* pUCUnitTest = UCUnitTest::Instance();

	//获取联系人列表
	std::vector<UCContact> vecList;
	GetAllContactlist_(vecList);
	CPPUNIT_ASSERT_MESSAGE("GetAllContactlist", 2 == vecList.size());

	std::vector<UCContact>::iterator itor = vecList.begin();
	for (; itor != vecList.end(); itor++)
	{
		if (0 == strcmp(itor->ucAcc_, pUCUnitTest->m_strAcc.c_str()))
		{
			continue;
		}

		UCContact contact;
		memset(&contact, 0, sizeof(contact));
		int iRet = pUCUnitTest->m_fpRefreshContactByUri(itor->uri_, &contact);
		CPPUNIT_ASSERT_MESSAGE("RefreshContactByUri", 0 == iRet);
		CPPUNIT_ASSERT_MESSAGE("RefreshContactByUri", 0 == strcmp(contact.ucAcc_, itor->ucAcc_));

		memset(&contact, 0, sizeof(contact));
		iRet = pUCUnitTest->m_fpRefreshContactByUri("ErrorUri", &contact);
		CPPUNIT_ASSERT_MESSAGE("RefreshContactByUri", 0 != iRet);
		CPPUNIT_ASSERT_MESSAGE("RefreshContactByUri", 0 == strcmp(contact.ucAcc_, ""));

		break;
	}
}

void UT_UCContactMgr::UT_SearchContact()
{
	UCUnitTest* pUCUnitTest = UCUnitTest::Instance();

	const int SIZE = 10;
	int recamount = 0;
	UCContactList contactlist;
	memset(&contactlist, 0, sizeof(contactlist));
	contactlist.contact = (UCContact*)malloc(sizeof(UCContact)*SIZE);
	memset(contactlist.contact, 0, sizeof(UCContact)*SIZE);

	int iRet = pUCUnitTest->m_fpSearchContact("bby", "", 1, 0, SIZE, 0, &recamount, &contactlist);
	CPPUNIT_ASSERT_MESSAGE("SearchContact", 0 == iRet);
	CPPUNIT_ASSERT_MESSAGE("SearchContact", 0 < recamount);
	bool bFound = false;
	for (int i=0; i<=contactlist.iTo-contactlist.iFrom; i++)
	{
		if (0 == strcmp(contactlist.contact[i].ucAcc_, "bby"))
		{
			bFound = true;
			break;
		}
	}
	CPPUNIT_ASSERT_MESSAGE("SearchContact", bFound);

	memset(contactlist.contact, 0, sizeof(UCContact)*SIZE);
	iRet = pUCUnitTest->m_fpSearchContact("ybb", "", 1, 0, SIZE, 0, &recamount, &contactlist);
	CPPUNIT_ASSERT_MESSAGE("SearchContact", 0 == iRet);
	CPPUNIT_ASSERT_MESSAGE("SearchContact", 0 < recamount);
	bFound = false;
	for (int i=0; i<=contactlist.iTo-contactlist.iFrom; i++)
	{
		if (0 == strcmp(contactlist.contact[i].ucAcc_, "ybb"))
		{
			bFound = true;
			break;
		}
	}
	CPPUNIT_ASSERT_MESSAGE("SearchContact", bFound);

	memset(contactlist.contact, 0, sizeof(UCContact)*SIZE);
	iRet = pUCUnitTest->m_fpSearchContact("yub", "", 1, 0, SIZE, 0, &recamount, &contactlist);
	CPPUNIT_ASSERT_MESSAGE("SearchContact", 0 == iRet);
	CPPUNIT_ASSERT_MESSAGE("SearchContact", 0 < recamount);
	bFound = false;
	for (int i=0; i<=contactlist.iTo-contactlist.iFrom; i++)
	{
		if (0 == strcmp(contactlist.contact[i].ucAcc_, "yubinbin"))
		{
			bFound = true;
			break;
		}
	}
	CPPUNIT_ASSERT_MESSAGE("SearchContact", bFound);

	memset(contactlist.contact, 0, sizeof(UCContact)*SIZE);
	iRet = pUCUnitTest->m_fpSearchContact("ErrorUcAccount", "", 1, 0, SIZE, 0, &recamount, &contactlist);
	CPPUNIT_ASSERT_MESSAGE("SearchContact", 0 == iRet);
	CPPUNIT_ASSERT_MESSAGE("SearchContact", 0 == recamount);

	free(contactlist.contact);
}

void UT_UCContactMgr::UT_Modify()
{
	UCUnitTest* pUCUnitTest = UCUnitTest::Instance();

	//获取联系人列表
	std::vector<UCContact> vecList;
	GetAllContactlist_(vecList);
	CPPUNIT_ASSERT_MESSAGE("GetAllContactlist", 2 == vecList.size());

	std::vector<UCContact>::iterator itor = vecList.begin();
	for (; itor != vecList.end(); itor++)
	{
		if (0 == strcmp(itor->ucAcc_, pUCUnitTest->m_strAcc.c_str()))
		{
			continue;
		}

		UCContact& contact = *itor;
		int iRet = pUCUnitTest->m_fpModify(&contact);
		CPPUNIT_ASSERT_MESSAGE("Modify", 0 == iRet);

		UCContact member;
		memset(&member, 0, sizeof(member));
		memcpy(member.ucAcc_, "yubinbin", strlen("yubinbin"));
		iRet = pUCUnitTest->m_fpModify(&member);
		CPPUNIT_ASSERT_MESSAGE("Modify", 0 != iRet);

		memset(&member, 0, sizeof(member));
		memcpy(member.ucAcc_, "ErrorUcAccount", strlen("ErrorUcAccount"));
		iRet = pUCUnitTest->m_fpModify(&member);
		CPPUNIT_ASSERT_MESSAGE("Modify", 0 != iRet);

		break;
	}
}

void UT_UCContactMgr::UT_GetHeadImagePath()
{
	UCUnitTest* pUCUnitTest = UCUnitTest::Instance();

	//获取联系人列表
	std::vector<UCContact> vecList;
	GetAllContactlist_(vecList);
	CPPUNIT_ASSERT_MESSAGE("GetAllContactlist", 2 == vecList.size());

	std::vector<UCContact>::iterator itor = vecList.begin();
	for (; itor != vecList.end(); itor++)
	{
		if (0 == strcmp(itor->ucAcc_, pUCUnitTest->m_strAcc.c_str()))
		{
			continue;
		}

		char path[IMAGE_LENGTH] = {0};
		UCContact& contact = *itor;
		int iRet = pUCUnitTest->m_fpGetHeadImagePath(&contact, path);
		CPPUNIT_ASSERT_MESSAGE("GetHeadImagePath", 0 == iRet);
		CPPUNIT_ASSERT_MESSAGE("GetHeadImagePath", 0 != strcmp(path, ""));

		//可以查询非好友！！
		memset(path, 0, IMAGE_LENGTH);
		UCContact member;		
		memset(&member, 0, sizeof(member));
		memcpy(member.ucAcc_, "fjj47", strlen("fjj47"));
		iRet = pUCUnitTest->m_fpGetHeadImagePath(&member, path);
		CPPUNIT_ASSERT_MESSAGE("GetHeadImagePath", 0 == iRet);
		CPPUNIT_ASSERT_MESSAGE("GetHeadImagePath", 0 != strcmp(path, ""));

		memset(path, 0, IMAGE_LENGTH);
		memset(&member, 0, sizeof(member));
		memcpy(member.ucAcc_, "ErrorUcAccount", strlen("ErrorUcAccount"));
		iRet = pUCUnitTest->m_fpGetHeadImagePath(&member, path);
		CPPUNIT_ASSERT_MESSAGE("GetHeadImagePath", 0 != iRet);
		CPPUNIT_ASSERT_MESSAGE("GetHeadImagePath", 0 == strcmp(path, ""));

		break;
	}
}

void UT_UCContactMgr::UT_AddToGroup()
{
	UCUnitTest* pUCUnitTest = UCUnitTest::Instance();

	//增加新分组
	UCCustomGroup customgroup;
	memset(&customgroup, 0, sizeof(customgroup));
	memcpy(customgroup.name_, "MyTestCustomGroup", strlen("MyTestCustomGroup"));
	int iRet = pUCUnitTest->m_fpAddCustomGroup(&customgroup);
	CPPUNIT_ASSERT_MESSAGE("AddCustomGroup", 0 == iRet);

	//获取联系人列表
	std::vector<UCContact> vecList;
	GetAllContactlist_(vecList);
	CPPUNIT_ASSERT_MESSAGE("GetAllContactlist", 2 == vecList.size());

	std::vector<UCContact>::iterator itor = vecList.begin();
	for (; itor != vecList.end(); itor++)
	{
		if (0 == strcmp(itor->ucAcc_, pUCUnitTest->m_strAcc.c_str()))
		{
			continue;
		}

		//移动联系人到新建分组
		UCContact& contact = *itor;
		UCGroup oldgroup;
		memset(&oldgroup, 0, sizeof(oldgroup));
		memcpy(oldgroup.id_, "-1", strlen("-1"));
		iRet = pUCUnitTest->m_fpRemoveFromGroup(&contact, &oldgroup);
		CPPUNIT_ASSERT_MESSAGE("RemoveFromGroup", 0 == iRet);
		
		UCGroup newgroup;
		memset(&newgroup, 0, sizeof(newgroup));
		memcpy(newgroup.id_, customgroup.id_, strlen(customgroup.id_));
		iRet = pUCUnitTest->m_fpAddToGroup(&contact, &newgroup);
		CPPUNIT_ASSERT_MESSAGE("RemoveFromGroup", 0 == iRet);

		//校验移动后结果
		std::vector<UCContact> contactlist;
		UT_UCGroup::GetContactlistFromCustomGroup_(&customgroup, contactlist);
		CPPUNIT_ASSERT_MESSAGE("GetContactlistFromCustomGroup", 1 == contactlist.size());
		CPPUNIT_ASSERT_MESSAGE("GetContactlistFromCustomGroup", 0 == strcmp(itor->ucAcc_, contactlist[0].ucAcc_));

		UCCustomGroup oldcustom;
		memset(&oldcustom, 0, sizeof(oldcustom));
		memcpy(oldcustom.id_, "-1", strlen("-1"));
		contactlist.clear();
		UT_UCGroup::GetContactlistFromCustomGroup_(&oldcustom, contactlist);
		CPPUNIT_ASSERT_MESSAGE("GetContactlistFromCustomGroup", 1 == contactlist.size());
		CPPUNIT_ASSERT_MESSAGE("GetContactlistFromCustomGroup", 0 == strcmp(pUCUnitTest->m_strAcc.c_str(), contactlist[0].ucAcc_));

		break;
	}
}

void UT_UCContactMgr::UT_RemoveFromGroup()
{
	UCUnitTest* pUCUnitTest = UCUnitTest::Instance();

	std::vector<UCCustomGroup> customlist;
	UT_UCGroup::GetCustomGrouplist_(customlist);
	CPPUNIT_ASSERT_MESSAGE("GetCustomGrouplist", 2 == customlist.size());

	std::vector<UCCustomGroup>::iterator itor = customlist.begin();
	for (; itor != customlist.end(); itor++)
	{
		if (0 == strcmp(itor->id_, "-1"))
		{
			continue;
		}

		UCCustomGroup& customgroup = *itor;

		std::vector<UCContact> contactlist;
		UT_UCGroup::GetContactlistFromCustomGroup_(&customgroup, contactlist);
		CPPUNIT_ASSERT_MESSAGE("GetContactlistFromCustomGroup", 1 == contactlist.size());

		//移动联系人到默认分组
		UCGroup oldgroup;
		memset(&oldgroup, 0, sizeof(oldgroup));
		memcpy(oldgroup.id_, customgroup.id_, strlen(customgroup.id_));
		UCContact contact = contactlist[0];
		int iRet = pUCUnitTest->m_fpRemoveFromGroup(&contact, &oldgroup);
		CPPUNIT_ASSERT_MESSAGE("RemoveFromGroup", 0 == iRet);

		UCGroup newgroup;
		memset(&newgroup, 0, sizeof(newgroup));
		memcpy(newgroup.id_, "-1", strlen("-1"));
		iRet = pUCUnitTest->m_fpAddToGroup(&contact, &newgroup);
		CPPUNIT_ASSERT_MESSAGE("RemoveFromGroup", 0 == iRet);

		//校验移动后结果
		contactlist.clear();
		UT_UCGroup::GetContactlistFromCustomGroup_(&customgroup, contactlist);
		CPPUNIT_ASSERT_MESSAGE("GetContactlistFromCustomGroup", 0 == contactlist.size());

		UCCustomGroup newcustom;
		memset(&newcustom, 0, sizeof(newcustom));
		memcpy(newcustom.id_, "-1", strlen("-1"));
		contactlist.clear();
		UT_UCGroup::GetContactlistFromCustomGroup_(&newcustom, contactlist);
		CPPUNIT_ASSERT_MESSAGE("GetContactlistFromCustomGroup", 2 == contactlist.size());
		CPPUNIT_ASSERT_MESSAGE("GetContactlistFromCustomGroup", 0 == strcmp(contact.ucAcc_, contactlist[0].ucAcc_)
																|| 0 == strcmp(contact.ucAcc_, contactlist[1].ucAcc_));

		break;
	}

	//删除新建分组
	if (itor != customlist.end())
	{
		UCCustomGroup& customgroup = *itor;
		int iRet = pUCUnitTest->m_fpRemoveCustomGroup(&customgroup);
		CPPUNIT_ASSERT_MESSAGE("RemoveCustomGroup", 0 == iRet);

		customlist.clear();
		UT_UCGroup::GetCustomGrouplist_(customlist);
		CPPUNIT_ASSERT_MESSAGE("GetCustomGrouplist", 1 == customlist.size());
		CPPUNIT_ASSERT_MESSAGE("GetCustomGrouplist", 0 == strcmp(customlist[0].id_, "-1"));
	}
}

void UT_UCContactMgr::UT_GetCustomGroups()
{
	UCUnitTest* pUCUnitTest = UCUnitTest::Instance();

	//获取联系人列表
	std::string uri;
	std::vector<UCContact> vecList;
	GetAllContactlist_(vecList);
	CPPUNIT_ASSERT_MESSAGE("GetAllContactlist", 2 == vecList.size());

	std::vector<UCContact>::iterator itor = vecList.begin();
	for (; itor != vecList.end(); itor++)
	{
		if (0 == strcmp(itor->ucAcc_, pUCUnitTest->m_strAcc.c_str()))
		{
			continue;
		}

		break;
	}

	//
	if (itor != vecList.end())
	{
		UCContact& contact = *itor;

		//移动联系人
		UT_AddToGroup();
	
		std::vector<UCCustomGroup> customlist;
		GetCustomGroups_(&contact, customlist);
		CPPUNIT_ASSERT_MESSAGE("GetCustomGroups", 1 == customlist.size());
		CPPUNIT_ASSERT_MESSAGE("GetCustomGroups", 0 == strcmp(customlist[0].name_, "MyTestCustomGroup"));

		//移动联系人
		UT_RemoveFromGroup();
		customlist.clear();
		GetCustomGroups_(&contact, customlist);
		CPPUNIT_ASSERT_MESSAGE("GetCustomGroups", 1 == customlist.size());
		CPPUNIT_ASSERT_MESSAGE("GetCustomGroups", 0 == strcmp(customlist[0].id_, "-1"));
	}
	else
	{
		CPPUNIT_ASSERT_MESSAGE("GetAllContactlist", FALSE);
	}
}

void UT_UCContactMgr::UT_RemoveContactById()
{
	UCUnitTest* pUCUnitTest = UCUnitTest::Instance();

	//获取联系人列表
	std::vector<UCContact> vecList;
	GetAllContactlist_(vecList);
	CPPUNIT_ASSERT_MESSAGE("GetAllContactlist", 2 == vecList.size());

	std::vector<UCContact>::iterator itor = vecList.begin();
	for (; itor != vecList.end(); itor++)
	{
		if (0 == strcmp(itor->ucAcc_, pUCUnitTest->m_strAcc.c_str()))
		{
			continue;
		}

		int iRet = pUCUnitTest->m_fpRemoveContactById(itor->id_);
		CPPUNIT_ASSERT_MESSAGE("RemoveContactById", 0 == iRet);

		vecList.clear();
		GetAllContactlist_(vecList);
		CPPUNIT_ASSERT_MESSAGE("GetAllContactlist", 1 == vecList.size());

		break;
	}
}

void UT_UCContactMgr::RemoveAllContactExceptSelf()
{
	UCUnitTest* pUCUnitTest = UCUnitTest::Instance();

	//获取联系人列表
	std::vector<UCContact> vecList;
	GetAllContactlist_(vecList);

	//删除联系人
	std::vector<UCContact>::iterator itor = vecList.begin();
	for (; itor != vecList.end(); itor++)
	{
		if (0 == strcmp(itor->ucAcc_, pUCUnitTest->m_strAcc.c_str()))
		{
			continue;
		}
		int iRet = pUCUnitTest->m_fpRemoveContactById(itor->id_);
		CPPUNIT_ASSERT_MESSAGE("RemoveContactById", 0 == iRet);
	}
}

void UT_UCContactMgr::GetAllContactlist_(std::vector<UCContact>& vecList)
{
	vecList.clear();
	UCUnitTest* pUCUnitTest = UCUnitTest::Instance();

	const int SIZE = 10;
	int iFrom = 0;
	int iTo = SIZE - 1;
	UCContactList contactlist;
	memset(&contactlist, 0, sizeof(contactlist));
	contactlist.contact = (UCContact*)malloc(sizeof(UCContact)*SIZE);

	do
	{
		memset(contactlist.contact, 0, sizeof(UCContact)*SIZE);
		int iRet = pUCUnitTest->m_fpGetAllContactlist(iFrom, iTo, &contactlist);
		CPPUNIT_ASSERT_MESSAGE("GetAllContactlist", 0 == iRet);

		for (int i=0; i<=contactlist.iTo - contactlist.iFrom; i++)
		{
			//UCContact为简单类型直接复制内存就可以了
			vecList.push_back(contactlist.contact[i]);
		}
		iFrom += SIZE;
		iTo += SIZE;

	} while(contactlist.iTo + 1 < contactlist.iTotal);
	free(contactlist.contact);
	memset(&contactlist, 0, sizeof(contactlist));
}

void UT_UCContactMgr::GetCustomGroups_(const UCContact* contact, std::vector<UCCustomGroup>& vecList)
{
	vecList.clear();
	UCUnitTest* pUCUnitTest = UCUnitTest::Instance();

	const int SIZE = 10;
	int iFrom = 0;
	int iTo = SIZE - 1;
	UCCustomGroupList customlist;
	memset(&customlist, 0, sizeof(customlist));
	customlist.group = (UCCustomGroup*)malloc(sizeof(UCCustomGroup)*SIZE);

	do
	{
		memset(customlist.group, 0, sizeof(UCCustomGroup)*SIZE);
		int iRet = pUCUnitTest->m_fpGetCustomGroups(contact, iFrom, iTo, &customlist);
		CPPUNIT_ASSERT_MESSAGE("GetCustomGroups", 0 == iRet);

		for (int i=0; i<=customlist.iTo - customlist.iFrom; i++)
		{
			//UCContact为简单类型直接复制内存就可以了
			vecList.push_back(customlist.group[i]);
		}
		iFrom += SIZE;
		iTo += SIZE;

	} while(customlist.iTo + 1 < customlist.iTotal);
	free(customlist.group);
	memset(&customlist, 0, sizeof(customlist));
}

void UT_UCContactMgr::GetPhoneNumByUri(const std::string& uri, std::string& phoneNum)
{
	//uri like this: "sip:244197@esdk244.esdk244.com"

	phoneNum = uri.substr(uri.find(":")+1, std::string::npos);
	phoneNum = phoneNum.substr(0, phoneNum.find("@"));
}