#ifndef __UT_UC_MEETING_H__
#define __UT_UC_MEETING_H__

class UT_UCMeeting : public CppUnit::TestFixture
{
public:
	UT_UCMeeting();
	virtual ~UT_UCMeeting();

public:
	CPPUNIT_TEST_SUITE( UT_UCMeeting );
	CPPUNIT_TEST(UT_MakeMeetingGroup);
	CPPUNIT_TEST(UT_StartMeeting);
	//CPPUNIT_TEST(UT_AcceptMeeting);
	CPPUNIT_TEST(UT_AddParticipant);
	CPPUNIT_TEST(UT_ConnectParticipant);
	CPPUNIT_TEST(UT_RemoveParticipant);
	CPPUNIT_TEST(UT_KickParticipant);
	CPPUNIT_TEST(UT_MuteMeeting);
	CPPUNIT_TEST(UT_UnMuteMeeting);
	CPPUNIT_TEST(UT_GetBookConfList);
	CPPUNIT_TEST(UT_JoinMeeting);
	CPPUNIT_TEST(UT_LeaveMeeting);
	CPPUNIT_TEST_SUITE_END();

public:
	// 初始化函数
	virtual void setUp();
	// 清理函数
	virtual void tearDown();

public:
	//测试用例
	void UT_MakeMeetingGroup();
	void UT_StartMeeting();
	void UT_AcceptMeeting();
	void UT_AddParticipant();
	void UT_ConnectParticipant();
	void UT_RemoveParticipant();
	void UT_KickParticipant();
	void UT_MuteMeeting();
	void UT_UnMuteMeeting();
	void UT_GetBookConfList();
	void UT_JoinMeeting();
	void UT_LeaveMeeting();

	//辅助变量
private:
	void MakeMeetingGroup_(char convId[CONVID_LENGTH]);
	void StartMeeting_(const char* convId);
	void GetBookConfList_(std::vector<UCBookConf>& vecList);
	void CloseMeeting_(const char* convId, bool bHasAV = true);
};

#endif