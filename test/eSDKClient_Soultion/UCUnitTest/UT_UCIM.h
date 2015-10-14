#ifndef __UT_UC_IM_H__
#define __UT_UC_IM_H__

class UT_UCIM : public CppUnit::TestFixture
{
public:
	UT_UCIM();
	virtual ~UT_UCIM();

public:
	CPPUNIT_TEST_SUITE( UT_UCIM );
	CPPUNIT_TEST(UT_SendIMMessage);
	//CPPUNIT_TEST(UT_CloseConversation);
	CPPUNIT_TEST_SUITE_END();

public:
	// ��ʼ������
	virtual void setUp();
	// ������
	virtual void tearDown();

public:
	//��������
	void UT_SendIMMessage();
	void UT_CloseConversation();
};

#endif