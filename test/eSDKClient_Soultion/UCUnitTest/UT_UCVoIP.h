#ifndef __UT_UC_VOIP_H__
#define __UT_UC_VOIP_H__

class UT_UCVoIP : public CppUnit::TestFixture
{
public:
	UT_UCVoIP();
	virtual ~UT_UCVoIP();

public:
	CPPUNIT_TEST_SUITE( UT_UCVoIP );
	CPPUNIT_TEST(UT_MakeCall);
	//CPPUNIT_TEST(UT_Accept);
	//CPPUNIT_TEST(UT_Reject);
	//CPPUNIT_TEST(UT_Hangup);
	//CPPUNIT_TEST(UT_Hold);
	//CPPUNIT_TEST(UT_Resume);
	//CPPUNIT_TEST(UT_Forward);
	//CPPUNIT_TEST(UT_StartRecord);
	//CPPUNIT_TEST(UT_StopRecord);
	//CPPUNIT_TEST(UT_MuteVoIP);
	//CPPUNIT_TEST(UT_UnMuteVoIP);
	CPPUNIT_TEST_SUITE_END();

public:
	// 初始化函数
	virtual void setUp();
	// 清理函数
	virtual void tearDown();

public:
	//测试用例
	void UT_MakeCall();
	void UT_Accept();
	void UT_Reject();
	void UT_Hangup();
	void UT_Hold();
	void UT_Resume();
	void UT_Forward();
	void UT_StartRecord();
	void UT_StopRecord();
	void UT_MuteVoIP();
	void UT_UnMuteVoIP();
};

#endif