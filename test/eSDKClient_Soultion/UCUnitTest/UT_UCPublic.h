#ifndef __UT_UC_PUBLIC_H__
#define __UT_UC_PUBLIC_H__

class UT_UCPublic : public CppUnit::TestFixture
{
public:
	UT_UCPublic();
	virtual ~UT_UCPublic();

public:
	CPPUNIT_TEST_SUITE( UT_UCPublic );
	CPPUNIT_TEST(UT_PublishSelfInformation);
	CPPUNIT_TEST(UT_GetContactStatus);
	CPPUNIT_TEST_SUITE_END();

public:
	// 初始化函数
	virtual void setUp();
	// 清理函数
	virtual void tearDown();

public:
	//测试用例
	void UT_PublishSelfInformation();
	void UT_GetContactStatus();

private:
	void GetMySelfContactInfo(UCContact* contact);
};

#endif