#ifndef __UT_UC_CONTACT_MGR_H__
#define __UT_UC_CONTACT_MGR_H__

class UT_UCContactMgr : public CppUnit::TestFixture
{
public:
	UT_UCContactMgr();
	virtual ~UT_UCContactMgr();

public:
	CPPUNIT_TEST_SUITE( UT_UCContactMgr );
	CPPUNIT_TEST(UT_GetAllContactlist);
	CPPUNIT_TEST(UT_GetContactByAccount);
	CPPUNIT_TEST(UT_GetContactById);
	CPPUNIT_TEST(UT_GetContactByPhoneNum);
	CPPUNIT_TEST(UT_GetContactByUri);
	CPPUNIT_TEST(UT_HasContact);
	CPPUNIT_TEST(UT_RefreshContactByAccount);
	CPPUNIT_TEST(UT_RefreshContactById);
	CPPUNIT_TEST(UT_RefreshContactByUri);
	CPPUNIT_TEST(UT_SearchContact);
	CPPUNIT_TEST(UT_Modify);
	CPPUNIT_TEST(UT_GetHeadImagePath);
	CPPUNIT_TEST(UT_AddToGroup);
	CPPUNIT_TEST(UT_RemoveFromGroup);
	CPPUNIT_TEST(UT_GetCustomGroups);
	CPPUNIT_TEST(UT_RemoveContactById);
	CPPUNIT_TEST_SUITE_END();

public:
	// 初始化函数
	virtual void setUp();
	// 清理函数
	virtual void tearDown();

	//测试用例
public:
	void UT_GetAllContactlist();
	void UT_GetContactByAccount();
	void UT_GetContactById();
	void UT_GetContactByPhoneNum();
	void UT_GetContactByUri();
	void UT_HasContact();
	void UT_RefreshContactByAccount();
	void UT_RefreshContactById();
	void UT_RefreshContactByUri();
	void UT_SearchContact();
	void UT_Modify();
	void UT_GetHeadImagePath();
	void UT_AddToGroup();
	void UT_RemoveFromGroup();
	void UT_GetCustomGroups();
	void UT_RemoveContactById();

	//辅助函数
public:
	static void GetAllContactlist_(std::vector<UCContact>& vecList);
	static void RemoveAllContactExceptSelf();
	static void GetCustomGroups_(const UCContact* contact, std::vector<UCCustomGroup>& vecList);

	void GetPhoneNumByUri(const std::string& uri, std::string& phoneNum);
};

#endif