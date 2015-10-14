#include "stdafx.h"
#include "UT_UCSignIn.h"
#include "UCUnitTest.h"

CPPUNIT_TEST_SUITE_NAMED_REGISTRATION(UT_UCSignIn, "UCUnitTest");

UT_UCSignIn::UT_UCSignIn()
{

}

UT_UCSignIn::~UT_UCSignIn()
{

}

void UT_UCSignIn::setUp()
{
	UCUnitTest* pUCUnitTest = UCUnitTest::Instance();
	bool bRet = pUCUnitTest->Start(false);
	CPPUNIT_ASSERT_MESSAGE("Start", bRet);
}

void UT_UCSignIn::tearDown()
{
	UCUnitTest* pUCUnitTest = UCUnitTest::Instance();
	bool bRet = pUCUnitTest->Stop(false);
	CPPUNIT_ASSERT_MESSAGE("Stop", bRet);
}

void UT_UCSignIn::UT_SignInByPasswd()
{
	UCUnitTest* pUCUnitTest = UCUnitTest::Instance();
	int iRet = pUCUnitTest->m_fpeSDKClientPlatform_LoginByPassword("yubinbin","UcAAaa_11",1);
	CPPUNIT_ASSERT_MESSAGE("LoginByPassword", UC_Succ == iRet);

	Sleep(5000);

	bool bRet = pUCUnitTest->Logout();
	CPPUNIT_ASSERT_MESSAGE("LoginByPassword_logout", bRet);
}

void UT_UCSignIn::UT_SignInByPasswd_Err_Acc()
{
	UCUnitTest* pUCUnitTest = UCUnitTest::Instance();
	int iRet = pUCUnitTest->m_fpeSDKClientPlatform_LoginByPassword("ErrorAccount","UcAAaa_11",1);
	CPPUNIT_ASSERT_MESSAGE("SignInByPasswd_Err_Acc", UC_Fail == iRet);
}

void UT_UCSignIn::UT_SignInByPasswd_Err_Pwd()
{
	UCUnitTest* pUCUnitTest = UCUnitTest::Instance();
	int iRet = pUCUnitTest->m_fpeSDKClientPlatform_LoginByPassword("yubinbin","ErrorPasswd",1);
	CPPUNIT_ASSERT_MESSAGE("SignInByPasswd_Err_Pwd", UC_Fail == iRet);
}

void UT_UCSignIn::UT_SignOut()
{
	UCUnitTest* pUCUnitTest = UCUnitTest::Instance();
	bool bRet = pUCUnitTest->Login();
	CPPUNIT_ASSERT_MESSAGE("SignOut_login", bRet);

	Sleep(5000);

	int iRet = pUCUnitTest->m_fpeSDKClientPlatform_Logout();
	CPPUNIT_ASSERT_MESSAGE("SignOut", UC_Succ == iRet);
}