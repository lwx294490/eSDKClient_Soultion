#ifndef __UT_UC_GROUP_H__
#define __UT_UC_GROUP_H__

class UT_UCGroup : public CppUnit::TestFixture
{
public:
	UT_UCGroup();
	virtual ~UT_UCGroup();

public:
	CPPUNIT_TEST_SUITE( UT_UCGroup );
	CPPUNIT_TEST(UT_GetCustomGrouplist);
	CPPUNIT_TEST(UT_GetContactlistFromCustomGroup);
	CPPUNIT_TEST(UT_RefreshFixedGrouplist);
	CPPUNIT_TEST(UT_RefreshContactList);
	CPPUNIT_TEST(UT_GetFixedGrouplist);
	CPPUNIT_TEST(UT_GetFixedGroupByID);
	CPPUNIT_TEST(UT_GetFixedGroupByUri);
	CPPUNIT_TEST(UT_GetCustomGroupById);
	CPPUNIT_TEST(UT_SearchFixedGroup);
	CPPUNIT_TEST(UT_RenameToCustomGroup);
	CPPUNIT_TEST(UT_RenameToFixedGroup);
	CPPUNIT_TEST(UT_ChangeGroupInfo);
	//CPPUNIT_TEST(UT_ChangeGroupOwner);	//注释部分需要打桩测试……
	CPPUNIT_TEST(UT_RefreshGroup);
	//CPPUNIT_TEST(UT_AcceptInvitation);
	//CPPUNIT_TEST(UT_RejectInvitation);
	//CPPUNIT_TEST(UT_AcceptJoinReq);
	//CPPUNIT_TEST(UT_RejectJoinReq);
	CPPUNIT_TEST_SUITE_END();

public:
	// 初始化函数
	virtual void setUp();
	// 清理函数
	virtual void tearDown();

public:
	//测试用例
	void UT_GetCustomGrouplist();
	void UT_GetContactlistFromCustomGroup();
	void UT_RefreshFixedGrouplist();
	void UT_RefreshContactList();
	void UT_GetFixedGrouplist();
	void UT_GetFixedGroupByID();
	void UT_GetFixedGroupByUri();
	void UT_GetCustomGroupById();
	void UT_SearchFixedGroup();
	void UT_RenameToCustomGroup();
	void UT_RenameToFixedGroup();
	void UT_ChangeGroupInfo();
	void UT_ChangeGroupOwner();
	void UT_RefreshGroup();
	void UT_AcceptInvitation();
	void UT_RejectInvitation();
	void UT_AcceptJoinReq();
	void UT_RejectJoinReq();

	//辅助函数
public:
	static void GetCustomGrouplist_(std::vector<UCCustomGroup>& vecList);
	static void GetContactlistFromCustomGroup_(const UCCustomGroup* group, std::vector<UCContact>& vecList);
	static void RefreshFixedGrouplist_(std::vector<UCFixedGroup>& vecList);
	static void RefreshContactList_(const UCFixedGroup* group, std::vector<UCContact>& vecList);
	static void GetFixedGrouplist_(std::vector<UCFixedGroup>& vecList);
	static void RemoveAllCustomGroupExceptDefault();
	static void RemoveAllFixedGroup();
};

#endif