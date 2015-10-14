#include "stdafx.h"
#include "UT_UCIM.h"
#include "UCUnitTest.h"

CPPUNIT_TEST_SUITE_NAMED_REGISTRATION(UT_UCIM, "UCUnitTest");

UT_UCIM::UT_UCIM()
{

}

UT_UCIM::~UT_UCIM()
{

}

void UT_UCIM::setUp()
{
	UCUnitTest* pUCUnitTest = UCUnitTest::Instance();
	bool bRet = pUCUnitTest->Start();
	CPPUNIT_ASSERT_MESSAGE("Start", bRet);
}

void UT_UCIM::tearDown()
{
	UCUnitTest* pUCUnitTest = UCUnitTest::Instance();
	bool bRet = pUCUnitTest->Stop();
	CPPUNIT_ASSERT_MESSAGE("Stop", bRet);
}

void UT_UCIM::UT_SendIMMessage()
{
	UCUnitTest* pUCUnitTest = UCUnitTest::Instance();

	/************************************************************************/
	/*	IM ��ʽ
	/*	<imbody>
	/*	<imagelist>
	/*	<img>
	/*	<imgname>ͼƬ��</imgname>
	/*	<imgdata>ͼƬ����</imgdata>
	/*	</img>
	/*	����
	/*	</imagelist>
	/*	<content>���ı�+����ת���</content>
	/*	<html>html��Ϣ��</html>
	/*	</imbody>
	/************************************************************************/
	std::ostringstream os;
	os << "<imbody>";
	os << "<content>";
	os << "Hello World";
	os << "</content>";
	os << "</imbody>";	

	//����������
	{
		//��convId
		char convId[CONVID_LENGTH] = {0};
		UCAccountList acclist;
		memset(&acclist, 0, sizeof(acclist));
		acclist.account = (UCAccount*)malloc(sizeof(UCAccount));
		memset(acclist.account, 0, sizeof(UCAccount));
		memcpy(acclist.account->str, "ybb", strlen("ybb"));
		acclist.iFrom = 0;
		acclist.iTo = 0;
		acclist.iTotal = 1;
		int iRet = pUCUnitTest->m_fpSendIMMessage(os.str().c_str(), &acclist, convId);
		CPPUNIT_ASSERT_MESSAGE("SendIMMessage", 0 == iRet);
		CPPUNIT_ASSERT_MESSAGE("SendIMMessage", 0 != strcmp(convId, ""));
		free(acclist.account);

		//��convId
		if (0 != convId[0])
		{
			memset(&acclist, 0, sizeof(acclist));
			iRet = pUCUnitTest->m_fpSendIMMessage(os.str().c_str(), &acclist, convId);
			CPPUNIT_ASSERT_MESSAGE("SendIMMessage", 0 == iRet);
			CPPUNIT_ASSERT_MESSAGE("SendIMMessage", 0 != strcmp(convId, ""));
		}

		//�ر�convId
		if (0 != convId[0])
		{
			iRet = pUCUnitTest->m_fpCloseConversation(convId);
			CPPUNIT_ASSERT_MESSAGE("CloseConversation", 0 == iRet);
		}
	}


	//��������
	{
		//��convId
		char convId[CONVID_LENGTH] = {0};
		UCAccountList acclist;
		memset(&acclist, 0, sizeof(acclist));
		acclist.account = (UCAccount*)malloc(sizeof(UCAccount)*2);
		memset(acclist.account, 0, sizeof(UCAccount)*2);
		memcpy(acclist.account[0].str, "ybb", strlen("ybb"));
		memcpy(acclist.account[1].str, "bby01", strlen("bby01"));
		acclist.iFrom = 0;
		acclist.iTo = 1;
		acclist.iTotal = 2;
		int iRet = pUCUnitTest->m_fpSendIMMessage(os.str().c_str(), &acclist, convId);
		CPPUNIT_ASSERT_MESSAGE("SendIMMessage", 0 == iRet);
		CPPUNIT_ASSERT_MESSAGE("SendIMMessage", 0 != strcmp(convId, ""));
		free(acclist.account);

		//��convId
		if (0 != convId[0])
		{
			memset(&acclist, 0, sizeof(acclist));
			iRet = pUCUnitTest->m_fpSendIMMessage(os.str().c_str(), &acclist, convId);
			CPPUNIT_ASSERT_MESSAGE("SendIMMessage", 0 == iRet);
			CPPUNIT_ASSERT_MESSAGE("SendIMMessage", 0 != strcmp(convId, ""));
		}

		//�ر�convId
		if (0 != convId[0])
		{
			iRet = pUCUnitTest->m_fpCloseConversation(convId);
			CPPUNIT_ASSERT_MESSAGE("CloseConversation", 0 == iRet);
		}
	}
}

void UT_UCIM::UT_CloseConversation()
{
	//���� UT_SendIMMessage
}