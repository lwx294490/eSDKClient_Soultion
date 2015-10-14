#ifndef __UT_UC_SIGNIN_H__
#define __UT_UC_SIGNIN_H__

class UT_UCSignIn : public CppUnit::TestFixture
{
public:
	UT_UCSignIn();
	virtual ~UT_UCSignIn();

public:
	CPPUNIT_TEST_SUITE( UT_UCSignIn );
	CPPUNIT_TEST(UT_SignInByPasswd);
	CPPUNIT_TEST(UT_SignInByPasswd_Err_Acc);
	CPPUNIT_TEST(UT_SignInByPasswd_Err_Pwd);
	CPPUNIT_TEST(UT_SignOut);
	CPPUNIT_TEST_SUITE_END();

public:
	// ��ʼ������
	virtual void setUp();
	// ������
	virtual void tearDown();

	//��������
public:	
	void UT_SignInByPasswd();
	void UT_SignInByPasswd_Err_Acc();
	void UT_SignInByPasswd_Err_Pwd();
	void UT_SignOut();
};

#endif