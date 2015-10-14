#include "stdafx.h"
#include "UT_UCVoIP.h"
#include "UCUnitTest.h"

CPPUNIT_TEST_SUITE_NAMED_REGISTRATION(UT_UCVoIP, "UCUnitTest");

UT_UCVoIP::UT_UCVoIP()
{

}

UT_UCVoIP::~UT_UCVoIP()
{

}

void UT_UCVoIP::setUp()
{
	UCUnitTest* pUCUnitTest = UCUnitTest::Instance();
	bool bRet = pUCUnitTest->Start();
	CPPUNIT_ASSERT_MESSAGE("Start", bRet);
}

void UT_UCVoIP::tearDown()
{
	UCUnitTest* pUCUnitTest = UCUnitTest::Instance();
	bool bRet = pUCUnitTest->Stop();
	CPPUNIT_ASSERT_MESSAGE("Stop", bRet);
}

void UT_UCVoIP::UT_MakeCall()
{
	UCUnitTest* pUCUnitTest = UCUnitTest::Instance();

	// ”∆µ∫ÙΩ–
	{
		char convId[CONVID_LENGTH] = {0};
		UCContact contact;
		UCVideoWindow local;
		UCVideoWindow remote;		
		memset(&contact, 0, sizeof(contact));
		memset(&contact, 0, sizeof(contact));
		memset(&contact, 0, sizeof(contact));
		memcpy(contact.ucAcc_, "ybb", strlen("ybb"));
		local.hWnd = 1000;
		local.height = 200;
		local.width = 300;
		local.left = 0;
		local.top = 0;
		remote.hWnd = 1001;
		remote.height = 400;
		remote.width = 600;
		remote.left = 300;
		remote.top = 200;

		int iRet = pUCUnitTest->m_fpMakeCall(&contact, UC_Video, &local, &remote, convId);
		CPPUNIT_ASSERT_MESSAGE("MakeCall", 0 == iRet);
		CPPUNIT_ASSERT_MESSAGE("MakeCall", 0 != strcmp(convId, ""));
		
		if (0 != convId[0])
		{
			//π“∂œ
			iRet = pUCUnitTest->m_fpHangup(convId, UC_Audio);
			CPPUNIT_ASSERT_MESSAGE("Hangup", 0 == iRet);

			//πÿ±’
			iRet = pUCUnitTest->m_fpCloseConversation(convId);
			CPPUNIT_ASSERT_MESSAGE("CloseConversation", 0 == iRet);
			memset(&convId, 0, CONVID_LENGTH);			
		}
	}

	//”Ô“Ù∫ÙΩ–
	{
		char convId[CONVID_LENGTH] = {0};
		UCContact contact;
		UCVideoWindow local;
		UCVideoWindow remote;		
		memset(&contact, 0, sizeof(contact));
		memset(&contact, 0, sizeof(contact));
		memset(&contact, 0, sizeof(contact));
		memcpy(contact.ucAcc_, "ybb", strlen("ybb"));

		int iRet = pUCUnitTest->m_fpMakeCall(&contact, UC_Audio, &local, &remote, convId);
		CPPUNIT_ASSERT_MESSAGE("MakeCall", 0 == iRet);
		CPPUNIT_ASSERT_MESSAGE("MakeCall", 0 != strcmp(convId, ""));

		if (0 != convId[0])
		{
			//π“∂œ
			iRet = pUCUnitTest->m_fpHangup(convId, UC_Audio);
			CPPUNIT_ASSERT_MESSAGE("Hangup", 0 == iRet);

			//πÿ±’
			iRet = pUCUnitTest->m_fpCloseConversation(convId);
			CPPUNIT_ASSERT_MESSAGE("CloseConversation", 0 == iRet);
			memset(&convId, 0, CONVID_LENGTH);				
		}
	}	
}

void UT_UCVoIP::UT_Accept()
{

}

void UT_UCVoIP::UT_Reject()
{

}

void UT_UCVoIP::UT_Hangup()
{
	//Õ¨…œ
	//UT_MakeCall();
}

void UT_UCVoIP::UT_Hold()
{

}

void UT_UCVoIP::UT_Resume()
{

}

void UT_UCVoIP::UT_Forward()
{

}

void UT_UCVoIP::UT_StartRecord()
{

}

void UT_UCVoIP::UT_StopRecord()
{

}

void UT_UCVoIP::UT_MuteVoIP()
{

}

void UT_UCVoIP::UT_UnMuteVoIP()
{

}