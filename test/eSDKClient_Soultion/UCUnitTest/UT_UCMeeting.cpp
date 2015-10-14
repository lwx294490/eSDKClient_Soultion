#include "stdafx.h"
#include "UT_UCMeeting.h"
#include "UCUnitTest.h"

CPPUNIT_TEST_SUITE_NAMED_REGISTRATION(UT_UCMeeting, "UCUnitTest");

UT_UCMeeting::UT_UCMeeting()
{

}

UT_UCMeeting::~UT_UCMeeting()
{

}

void UT_UCMeeting::setUp()
{
	UCUnitTest* pUCUnitTest = UCUnitTest::Instance();
	bool bRet = pUCUnitTest->Start();
	CPPUNIT_ASSERT_MESSAGE("Start", bRet);
}

void UT_UCMeeting::tearDown()
{
	UCUnitTest* pUCUnitTest = UCUnitTest::Instance();
	bool bRet = pUCUnitTest->Stop();
	CPPUNIT_ASSERT_MESSAGE("Stop", bRet);
}

void UT_UCMeeting::UT_MakeMeetingGroup()
{
	char convId[CONVID_LENGTH] = {0};
	MakeMeetingGroup_(convId);

	//关闭convId
	if (0 != convId[0])
	{
		CloseMeeting_(convId, false);
	}
}

void UT_UCMeeting::UT_StartMeeting()
{
	char convId[CONVID_LENGTH] = {0};
	MakeMeetingGroup_(convId);
	StartMeeting_(convId);

	//离开会议
	if (0 != convId[0])
	{
		CloseMeeting_(convId);
	}
}

void UT_UCMeeting::UT_AcceptMeeting()
{

}

void UT_UCMeeting::UT_AddParticipant()
{
	//初始数据
	char convId[CONVID_LENGTH] = {0};
	MakeMeetingGroup_(convId);
	StartMeeting_(convId);

	if (0 != convId[0])
	{
		//增加成员
		UCUnitTest* pUCUnitTest = UCUnitTest::Instance();
		UCContact contact;
		memset(&contact, 0, sizeof(contact));
		memcpy(contact.ucAcc_, "yubinbin", strlen("yubinbin"));
		int iRet = pUCUnitTest->m_fpAddParticipant(&contact, convId);
		CPPUNIT_ASSERT_MESSAGE("AddParticipant", 0 == iRet);

		//离开会议
		CloseMeeting_(convId);
	}
}

void UT_UCMeeting::UT_ConnectParticipant()
{
	//初始数据
	char convId[CONVID_LENGTH] = {0};
	MakeMeetingGroup_(convId);
	StartMeeting_(convId);

	if (0 != convId[0])
	{
		UCUnitTest* pUCUnitTest = UCUnitTest::Instance();

		UCContact contact;
		memset(&contact, 0, sizeof(contact));
		memcpy(contact.ucAcc_, "ybb", strlen("ybb"));

		//先挂断
		int iRet = pUCUnitTest->m_fpKickParticipant(&contact, convId);
		CPPUNIT_ASSERT_MESSAGE("KickParticipant", 0 == iRet);

		//重新邀请成员
		iRet = pUCUnitTest->m_fpConnectParticipant(&contact, convId);
		CPPUNIT_ASSERT_MESSAGE("ConnectParticipant", 0 == iRet);

		//离开会议
		CloseMeeting_(convId);
	}
}

void UT_UCMeeting::UT_RemoveParticipant()
{
	//初始数据
	char convId[CONVID_LENGTH] = {0};
	MakeMeetingGroup_(convId);
	StartMeeting_(convId);

	if (0 != convId[0])
	{
		//删除成员
		UCUnitTest* pUCUnitTest = UCUnitTest::Instance();
		UCContact contact;
		memset(&contact, 0, sizeof(contact));
		memcpy(contact.ucAcc_, "ybb", strlen("ybb"));
		int iRet = pUCUnitTest->m_fpRemoveParticipant(&contact, convId);
		CPPUNIT_ASSERT_MESSAGE("RemoveParticipant", 0 == iRet);

		//离开会议
		CloseMeeting_(convId);
	}
}

void UT_UCMeeting::UT_KickParticipant()
{
	//初始数据
	char convId[CONVID_LENGTH] = {0};
	MakeMeetingGroup_(convId);
	StartMeeting_(convId);

	if (0 != convId[0])
	{
		UCUnitTest* pUCUnitTest = UCUnitTest::Instance();

		UCContact contact;
		memset(&contact, 0, sizeof(contact));
		memcpy(contact.ucAcc_, "ybb", strlen("ybb"));

		//挂断成员
		int iRet = pUCUnitTest->m_fpKickParticipant(&contact, convId);
		CPPUNIT_ASSERT_MESSAGE("KickParticipant", 0 == iRet);

		//离开会议
		CloseMeeting_(convId);
	}
}

void UT_UCMeeting::UT_MuteMeeting()
{
	//初始数据
	char convId[CONVID_LENGTH] = {0};
	MakeMeetingGroup_(convId);
	StartMeeting_(convId);

	if (0 != convId[0])
	{
		UCUnitTest* pUCUnitTest = UCUnitTest::Instance();

		UCContact contact;
		memset(&contact, 0, sizeof(contact));
		memcpy(contact.ucAcc_, "ybb", strlen("ybb"));

		//静音成员
		int iRet = pUCUnitTest->m_fpMuteMeeting(&contact, convId);
		CPPUNIT_ASSERT_MESSAGE("MuteMeeting", 0 == iRet);

		//离开会议
		CloseMeeting_(convId);
	}
}

void UT_UCMeeting::UT_UnMuteMeeting()
{
	//初始数据
	char convId[CONVID_LENGTH] = {0};
	MakeMeetingGroup_(convId);
	StartMeeting_(convId);

	if (0 != convId[0])
	{
		UCUnitTest* pUCUnitTest = UCUnitTest::Instance();

		UCContact contact;
		memset(&contact, 0, sizeof(contact));
		memcpy(contact.ucAcc_, "ybb", strlen("ybb"));

		//静音成员
		int iRet = pUCUnitTest->m_fpMuteMeeting(&contact, convId);
		CPPUNIT_ASSERT_MESSAGE("MuteMeeting", 0 == iRet);

		//取消静音成员
		iRet = pUCUnitTest->m_fpUnMuteMeeting(&contact, convId);
		CPPUNIT_ASSERT_MESSAGE("UnMuteMeeting", 0 == iRet);

		//离开会议
		CloseMeeting_(convId);
	}
}

void UT_UCMeeting::UT_GetBookConfList()
{
	std::vector<UCBookConf> vecList;
	GetBookConfList_(vecList);
}

void UT_UCMeeting::UT_JoinMeeting()
{
	std::vector<UCBookConf> vecList;
	GetBookConfList_(vecList);
	
	for (size_t i=0; i<vecList.size(); i++)
	{
		if (1 == vecList[i].confType)
		{
			//加入会议
			char convId[CONVID_LENGTH] = {0};
			UCUnitTest* pUCUnitTest = UCUnitTest::Instance();
			int iRet = pUCUnitTest->m_fpJoinMeeting(&vecList[0], convId);
			CPPUNIT_ASSERT_MESSAGE("JoinMeeting", 0 == iRet);
			CPPUNIT_ASSERT_MESSAGE("JoinMeeting", 0 != strcmp(convId, ""));

			//离开会议
			CloseMeeting_(convId);

			break;
		}
	}
}

void UT_UCMeeting::UT_LeaveMeeting()
{
	//初始数据
	char convId[CONVID_LENGTH] = {0};
	MakeMeetingGroup_(convId);
	StartMeeting_(convId);

	if (0 != convId[0])
	{
		////挂断
		//int iRet = pUCUnitTest->m_fpHangup(convId, UC_Audio);
		//CPPUNIT_ASSERT_MESSAGE("Hangup", 0 == iRet);

		//离开会议
		UCUnitTest* pUCUnitTest = UCUnitTest::Instance();
		int iRet = pUCUnitTest->m_fpLeaveMeeting(convId);
		CPPUNIT_ASSERT_MESSAGE("LeaveMeeting", 0 == iRet);
	}
}

void UT_UCMeeting::MakeMeetingGroup_(char convId[CONVID_LENGTH])
{
	UCUnitTest* pUCUnitTest = UCUnitTest::Instance();

	memset(convId, 0, CONVID_LENGTH);
	UCContactList contactlist;
	memset(&contactlist, 0, sizeof(contactlist));
	contactlist.contact = (UCContact*)malloc(sizeof(UCContact)*2);
	memset(contactlist.contact, 0, sizeof(UCContact)*2);
	contactlist.iFrom = 0;
	contactlist.iTo = 1;
	contactlist.iTotal = 2;
	memcpy(contactlist.contact[0].ucAcc_, "ybb", strlen("ybb"));
	memcpy(contactlist.contact[1].ucAcc_, "bby01", strlen("bby01"));

	int iRet = pUCUnitTest->m_fpMakeMeetingGroup(&contactlist, convId);
	CPPUNIT_ASSERT_MESSAGE("MakeMeetingGroup", 0 == iRet);
	CPPUNIT_ASSERT_MESSAGE("MakeMeetingGroup", 0 != strcmp(convId, ""));
}

void UT_UCMeeting::StartMeeting_(const char* convId)
{
	CPPUNIT_ASSERT_MESSAGE("StartMeeting", NULL != convId);

	UCUnitTest* pUCUnitTest = UCUnitTest::Instance();

	int iRet = pUCUnitTest->m_fpStartMeeting(convId);
	CPPUNIT_ASSERT_MESSAGE("StartMeeting", 0 == iRet);
}

void UT_UCMeeting::GetBookConfList_(std::vector<UCBookConf>& vecList)
{
	vecList.clear();
	UCUnitTest* pUCUnitTest = UCUnitTest::Instance();

	const int SIZE = 10;
	int iFrom = 0;
	int iTo = SIZE - 1;
	UCBookConfList bookconflist;
	memset(&bookconflist, 0, sizeof(bookconflist));
	bookconflist.bookConf = (UCBookConf*)malloc(sizeof(UCBookConf)*SIZE);

	do
	{
		memset(bookconflist.bookConf, 0, sizeof(UCBookConf)*SIZE);
		int iRet = pUCUnitTest->m_fpGetBookConfList(iFrom, iTo, &bookconflist);
		CPPUNIT_ASSERT_MESSAGE("GetBookConfList", 0 == iRet);
		for (int i=0; i<=bookconflist.iTo - bookconflist.iFrom; i++)
		{
			vecList.push_back(bookconflist.bookConf[i]);
		}
		iFrom += SIZE;
		iTo += SIZE;

	} while(bookconflist.iTo + 1 < bookconflist.iTotal);

	free(bookconflist.bookConf);
	memset(&bookconflist, 0, sizeof(bookconflist));
}

void UT_UCMeeting::CloseMeeting_(const char* convId, bool bHasAV)
{
	CPPUNIT_ASSERT_MESSAGE("CloseMeeting", NULL != convId);

	UCUnitTest* pUCUnitTest = UCUnitTest::Instance();

	if (bHasAV)
	{
		//挂断
		int iRet = pUCUnitTest->m_fpHangup(convId, UC_Audio);
		CPPUNIT_ASSERT_MESSAGE("Hangup", 0 == iRet);
	}

	Sleep(5000);
	//关闭
	int iRet = pUCUnitTest->m_fpCloseConversation(convId);
	CPPUNIT_ASSERT_MESSAGE("CloseConversation", 0 == iRet);
}