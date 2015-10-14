#include "stdafx.h"
#include "UT_UCPublic.h"
#include "UT_UCGroup.h"
#include "UCUnitTest.h"
#include <sstream>

CPPUNIT_TEST_SUITE_NAMED_REGISTRATION(UT_UCPublic, "UCUnitTest");

UT_UCPublic::UT_UCPublic()
{

}

UT_UCPublic::~UT_UCPublic()
{

}

void UT_UCPublic::setUp()
{
	UCUnitTest* pUCUnitTest = UCUnitTest::Instance();
	bool bRet = pUCUnitTest->Start();
	CPPUNIT_ASSERT_MESSAGE("Start", bRet);
}

void UT_UCPublic::tearDown()
{
	UCUnitTest* pUCUnitTest = UCUnitTest::Instance();
	bool bRet = pUCUnitTest->Stop();
	CPPUNIT_ASSERT_MESSAGE("Stop", bRet);
}

void UT_UCPublic::UT_PublishSelfInformation()
{
	UCUnitTest* pUCUnitTest = UCUnitTest::Instance();

	//获取自己的信息
	UCContact myself;
	memset(&myself, 0, sizeof(myself));
	GetMySelfContactInfo(&myself);
	CPPUNIT_ASSERT_MESSAGE("PublishSelfInformation", 0 != strcmp(myself.uri_, ""));

	std::ostringstream os;

	//发布状态 1
	os << UC_Busy;
	UCPublishInfoMap pubInfo;
	memset(&pubInfo, 0, sizeof(pubInfo));
	memcpy(pubInfo.publish[UC_Availability], os.str().c_str(), os.str().size());
	int iRet = pUCUnitTest->m_fpPublishSelfInformation(&pubInfo);
	CPPUNIT_ASSERT_MESSAGE("PublishSelfInformation", 0 == iRet);
	//校验状态
	int state = -1;
	iRet = pUCUnitTest->m_fpGetContactStatus(myself.uri_, &state);
	CPPUNIT_ASSERT_MESSAGE("GetContactStatus", 0 == iRet);
	CPPUNIT_ASSERT_MESSAGE("GetContactStatus", UC_Busy == state);

	//发布状态 2
	os.str("");
	memset(&pubInfo, 0, sizeof(pubInfo));
	os << UC_Offline;
	memcpy(pubInfo.publish[UC_Availability], os.str().c_str(), os.str().size());
	iRet = pUCUnitTest->m_fpPublishSelfInformation(&pubInfo);
	CPPUNIT_ASSERT_MESSAGE("PublishSelfInformation", 0 == iRet);
	//校验状态
	//state = -1;
	//iRet = pUCUnitTest->m_fpGetContactStatus(myself.uri_, &state);
	//CPPUNIT_ASSERT_MESSAGE("GetContactStatus", 0 == iRet);
	//CPPUNIT_ASSERT_MESSAGE("GetContactStatus", UC_Offline == state);

	//发布状态 3
	os.str("");
	memset(&pubInfo, 0, sizeof(pubInfo));
	os << UC_Online;
	memcpy(pubInfo.publish[UC_Availability], os.str().c_str(), os.str().size());
	iRet = pUCUnitTest->m_fpPublishSelfInformation(&pubInfo);
	CPPUNIT_ASSERT_MESSAGE("PublishSelfInformation", 0 == iRet);
	//校验状态
	state = -1;
	iRet = pUCUnitTest->m_fpGetContactStatus(myself.uri_, &state);
	CPPUNIT_ASSERT_MESSAGE("GetContactStatus", 0 == iRet);
	CPPUNIT_ASSERT_MESSAGE("GetContactStatus", UC_Online == state);


	//发布签名 1
	os.str("");
	memset(&pubInfo, 0, sizeof(pubInfo));
	os << "Hello World";
	memcpy(pubInfo.publish[UC_Signature], os.str().c_str(), os.str().size());
	iRet = pUCUnitTest->m_fpPublishSelfInformation(&pubInfo);
	CPPUNIT_ASSERT_MESSAGE("PublishSelfInformation", 0 == iRet);
	//校验签名
	memset(&myself, 0, sizeof(myself));
	GetMySelfContactInfo(&myself);
	CPPUNIT_ASSERT_MESSAGE("PublishSelfInformation", 0 == strcmp(myself.signature_, "Hello World"));
}

void UT_UCPublic::UT_GetContactStatus()
{
	UCUnitTest* pUCUnitTest = UCUnitTest::Instance();

	//默认分组增加联系人
	UCCustomGroup customgroup;
	memset(&customgroup, 0, sizeof(customgroup));
	memcpy(customgroup.id_, "-1", strlen("-1"));
	UCContact contact;
	memset(&contact, 0, sizeof(contact));
	memcpy(contact.ucAcc_, "bby01", strlen("bby01"));
	int iRet = pUCUnitTest->m_fpAddContactToCustomGroup(&customgroup, &contact);
	CPPUNIT_ASSERT_MESSAGE("AddContactToCustomGroup", 0 == iRet);

	//获取状态
	std::vector<UCCustomGroup> customlist;
	UT_UCGroup::GetCustomGrouplist_(customlist);
	std::vector<UCCustomGroup>::iterator itor = customlist.begin();
	for (; itor != customlist.end(); itor++)
	{
		UCCustomGroup& tmpgroup = *itor;
		std::vector<UCContact> contactlist;
		UT_UCGroup::GetContactlistFromCustomGroup_(&tmpgroup, contactlist);		
		std::vector<UCContact>::iterator it = contactlist.begin();
		for (; it != contactlist.end(); it++)
		{
			UCContact& tmpcontact = *it;			
			if (0 == strcmp(pUCUnitTest->m_strAcc.c_str(), tmpcontact.ucAcc_))
			{
				int state = -1;
				iRet = pUCUnitTest->m_fpGetContactStatus(tmpcontact.uri_, &state);
				CPPUNIT_ASSERT_MESSAGE("GetContactStatus", 0 == iRet);
				CPPUNIT_ASSERT_MESSAGE("GetContactStatus", UC_Online == state);
			}
			else
			{
				int state = -1;
				iRet = pUCUnitTest->m_fpGetContactStatus(tmpcontact.uri_, &state);
				CPPUNIT_ASSERT_MESSAGE("GetContactStatus", 0 == iRet);
				CPPUNIT_ASSERT_MESSAGE("GetContactStatus", UC_Offline <= state && UC_NoDisturb >= state);
			}
		}
	}

	//删除联系人
	iRet = pUCUnitTest->m_fpRemoveContactFromCustomGroup(&customgroup, &contact);
	CPPUNIT_ASSERT_MESSAGE("AddContactToCustomGroup", 0 == iRet);

	//获取状态
	int state = -1;
	iRet = pUCUnitTest->m_fpGetContactStatus("ErrorContactUri", &state);
	CPPUNIT_ASSERT_MESSAGE("GetContactStatus", 0 == iRet);
	CPPUNIT_ASSERT_MESSAGE("GetContactStatus", UC_InvalidStatus == state);
}

void UT_UCPublic::GetMySelfContactInfo(UCContact* contact)
{
	UCUnitTest* pUCUnitTest = UCUnitTest::Instance();
	memset(contact, 0, sizeof(UCContact));

	//获取状态
	std::vector<UCCustomGroup> customlist;
	UT_UCGroup::GetCustomGrouplist_(customlist);
	std::vector<UCCustomGroup>::iterator itor = customlist.begin();
	for (; itor != customlist.end(); itor++)
	{
		UCCustomGroup& tmpgroup = *itor;
		std::vector<UCContact> contactlist;
		UT_UCGroup::GetContactlistFromCustomGroup_(&tmpgroup, contactlist);		
		std::vector<UCContact>::iterator it = contactlist.begin();
		for (; it != contactlist.end(); it++)
		{
			UCContact& tmpcontact = *it;			
			if (0 == strcmp(pUCUnitTest->m_strAcc.c_str(), tmpcontact.ucAcc_))
			{
				//复杂结构体直接复制内存
				*contact = tmpcontact;
				return;
			}
		}
	}
}