#include "stdafx.h"
#include "UT_UCGroup.h"
#include "UCUnitTest.h"
#include "UT_UCContactMgr.h"

CPPUNIT_TEST_SUITE_NAMED_REGISTRATION(UT_UCGroup, "UCUnitTest");

UT_UCGroup::UT_UCGroup()
{

}

UT_UCGroup::~UT_UCGroup()
{

}

void UT_UCGroup::setUp()
{
	UCUnitTest* pUCUnitTest = UCUnitTest::Instance();
	bool bRet = pUCUnitTest->Start();
	CPPUNIT_ASSERT_MESSAGE("Start", bRet);
}

void UT_UCGroup::tearDown()
{
	UCUnitTest* pUCUnitTest = UCUnitTest::Instance();
	bool bRet = pUCUnitTest->Stop();
	CPPUNIT_ASSERT_MESSAGE("Stop", bRet);
}

void UT_UCGroup::UT_GetCustomGrouplist()
{
	//��������
	UT_UCContactMgr::RemoveAllContactExceptSelf();
	RemoveAllCustomGroupExceptDefault();

	//�����б��ѯ
	std::vector<UCCustomGroup> vecList;
	GetCustomGrouplist_(vecList);
	CPPUNIT_ASSERT_MESSAGE("GetCustomGrouplist", 1 == vecList.size());
	CPPUNIT_ASSERT_MESSAGE("GetCustomGrouplist", 0 == strcmp(vecList[0].id_, "-1"));

	//�½�����
	UCUnitTest* pUCUnitTest = UCUnitTest::Instance();
	UCCustomGroup customgroup;
	memset(&customgroup, 0, sizeof(customgroup));
	memcpy(customgroup.name_, "MyTestCustomGroup", strlen("MyTestCustomGroup"));
	int iRet = pUCUnitTest->m_fpAddCustomGroup(&customgroup);
	CPPUNIT_ASSERT_MESSAGE("AddCustomGroup", 0 == iRet);

	//�����б��ѯ
	vecList.clear();
	GetCustomGrouplist_(vecList);
	CPPUNIT_ASSERT_MESSAGE("GetCustomGrouplist", 2 == vecList.size());
	CPPUNIT_ASSERT_MESSAGE("GetCustomGrouplist", (0 == strcmp(vecList[0].id_, "-1") && 0 == strcmp(vecList[1].name_, customgroup.name_))
												|| (0 == strcmp(vecList[1].id_, "-1") && 0 == strcmp(vecList[0].name_, customgroup.name_)));

	//ɾ������	ע�⣺�������գ�����������ϵ���޷���
	iRet = pUCUnitTest->m_fpRemoveCustomGroup(&customgroup);
	CPPUNIT_ASSERT_MESSAGE("AddCustomGroup", 0 == iRet);

	//�����б��ѯ
	vecList.clear();
	GetCustomGrouplist_(vecList);
	CPPUNIT_ASSERT_MESSAGE("GetCustomGrouplist", 1 == vecList.size());
	CPPUNIT_ASSERT_MESSAGE("GetCustomGrouplist", 0 == strcmp(vecList[0].id_, "-1"));	
}

void UT_UCGroup::UT_GetContactlistFromCustomGroup()
{
	UCUnitTest* pUCUnitTest = UCUnitTest::Instance();

	//�����б��ѯ
	std::vector<UCCustomGroup> vecList;
	GetCustomGrouplist_(vecList);
	CPPUNIT_ASSERT_MESSAGE("GetCustomGrouplist", 1 == vecList.size());
	CPPUNIT_ASSERT_MESSAGE("GetCustomGrouplist", 0 == strcmp(vecList[0].id_, "-1"));

	//��ѯ������ϵ��
	std::vector<UCContact> contactlist;
	GetContactlistFromCustomGroup_(&vecList[0], contactlist);
	CPPUNIT_ASSERT_MESSAGE("GetCustomGrouplist", 1 == contactlist.size());
	CPPUNIT_ASSERT_MESSAGE("GetCustomGrouplist", 0 == strcmp(pUCUnitTest->m_strAcc.c_str(), contactlist[0].ucAcc_));

	//������������ϵ��
	UCContact contact;
	memset(&contact, 0, sizeof(contact));
	memcpy(contact.ucAcc_, "bby01", strlen("bby01"));
	int iRet = pUCUnitTest->m_fpAddContactToCustomGroup(&vecList[0], &contact);
	CPPUNIT_ASSERT_MESSAGE("AddContactToCustomGroup", 0 == iRet);

	//��ѯ������ϵ��
	contactlist.clear();
	GetContactlistFromCustomGroup_(&vecList[0], contactlist);
	CPPUNIT_ASSERT_MESSAGE("GetCustomGrouplist", 2 == contactlist.size());
	CPPUNIT_ASSERT_MESSAGE("GetCustomGrouplist", (0 == strcmp("bby01", contactlist[0].ucAcc_))
												|| (0 == strcmp("bby01", contactlist[1].ucAcc_)));

	//ɾ����ϵ��
	iRet = pUCUnitTest->m_fpRemoveContactFromCustomGroup(&vecList[0], &contact);
	CPPUNIT_ASSERT_MESSAGE("RemoveContactFromCustomGroup", 0 == iRet);
	contactlist.clear();
	GetContactlistFromCustomGroup_(&vecList[0], contactlist);
	CPPUNIT_ASSERT_MESSAGE("GetCustomGrouplist", 1 == contactlist.size());
	CPPUNIT_ASSERT_MESSAGE("GetCustomGrouplist", 0 == strcmp(pUCUnitTest->m_strAcc.c_str(), contactlist[0].ucAcc_));
}

void UT_UCGroup::UT_RefreshFixedGrouplist()
{
	UCUnitTest* pUCUnitTest = UCUnitTest::Instance();

	//��������
	RemoveAllFixedGroup();

	//�½��̶�Ⱥ��
	UCFixedGroup fixedgroup;
	memset(&fixedgroup, 0, sizeof(fixedgroup));
	memcpy(fixedgroup.name_, "MyTestFixedGroup", strlen("MyTestFixedGroup"));
	int iRet = pUCUnitTest->m_fpAddFixedGroup(&fixedgroup);
	CPPUNIT_ASSERT_MESSAGE("AddFixedGroup", 0 == iRet);

	//��ȡ�̶�Ⱥ���б�
	std::vector<UCFixedGroup> fixedlist;
	RefreshFixedGrouplist_(fixedlist);
	CPPUNIT_ASSERT_MESSAGE("RefreshFixedGrouplist", 1 == fixedlist.size());

	//ɾ���̶�Ⱥ��
	iRet = pUCUnitTest->m_fpRemoveFixedGroup(&fixedgroup);
	CPPUNIT_ASSERT_MESSAGE("RemoveFixedGroup", 0 == iRet);

	//��ȡ�̶�Ⱥ���б�
	fixedlist.clear();
	RefreshFixedGrouplist_(fixedlist);
	CPPUNIT_ASSERT_MESSAGE("RefreshFixedGrouplist", 0 == fixedlist.size());
}

void UT_UCGroup::UT_RefreshContactList()
{
	UCUnitTest* pUCUnitTest = UCUnitTest::Instance();

	//��������
	RemoveAllFixedGroup();

	//�½��̶�Ⱥ��
	UCFixedGroup fixedgroup;
	memset(&fixedgroup, 0, sizeof(fixedgroup));
	memcpy(fixedgroup.name_, "MyTestFixedGroup", strlen("MyTestFixedGroup"));
	int iRet = pUCUnitTest->m_fpAddFixedGroup(&fixedgroup);
	CPPUNIT_ASSERT_MESSAGE("AddFixedGroup", 0 == iRet);

	//��ȡ�̶�Ⱥ���б�
	std::vector<UCFixedGroup> fixedlist;
	RefreshFixedGrouplist_(fixedlist);
	CPPUNIT_ASSERT_MESSAGE("AddFixedGroup", 1 == fixedlist.size());

	//���ӹ̶�Ⱥ���Ա
	UCContact contact;
	memset(&contact, 0, sizeof(contact));
	memcpy(contact.ucAcc_, "bby01", strlen("bby01"));
	iRet = pUCUnitTest->m_fpAddContactToFixedGroup(&fixedgroup, &contact);
	CPPUNIT_ASSERT_MESSAGE("AddContactToFixedGroup", 0 == iRet);

	//��ȡ�̶�Ⱥ���Ա�б�
	std::vector<UCContact> contactlist;
	RefreshContactList_(&fixedgroup, contactlist);
	CPPUNIT_ASSERT_MESSAGE("RefreshContactList", 2 == contactlist.size());

	//ɾ���̶�Ⱥ���Ա
	iRet = pUCUnitTest->m_fpRemoveContactFromFixedGroup(&fixedgroup, &contact);
	CPPUNIT_ASSERT_MESSAGE("RemoveContactFromFixedGroup", 0 == iRet);

	//��ȡ�̶�Ⱥ���Ա�б�
	contactlist.clear();
	RefreshContactList_(&fixedgroup, contactlist);
	CPPUNIT_ASSERT_MESSAGE("RefreshContactList", 1 == contactlist.size());

	//ɾ���̶�Ⱥ��
	iRet = pUCUnitTest->m_fpRemoveFixedGroup(&fixedgroup);
	CPPUNIT_ASSERT_MESSAGE("RemoveFixedGroup", 0 == iRet);

	//��ȡ�̶�Ⱥ���б�
	fixedlist.clear();
	RefreshFixedGrouplist_(fixedlist);
	CPPUNIT_ASSERT_MESSAGE("RefreshFixedGrouplist", 0 == fixedlist.size());
}

void UT_UCGroup::UT_GetFixedGrouplist()
{
	//ע�⣺������RefreshFixedGrouplist��GetFixedGrouplist������Ч
	UCUnitTest* pUCUnitTest = UCUnitTest::Instance();

	//��������
	RemoveAllFixedGroup();

	//�½��̶�Ⱥ��
	UCFixedGroup fixedgroup;
	memset(&fixedgroup, 0, sizeof(fixedgroup));
	memcpy(fixedgroup.name_, "MyTestFixedGroup", strlen("MyTestFixedGroup"));
	int iRet = pUCUnitTest->m_fpAddFixedGroup(&fixedgroup);
	CPPUNIT_ASSERT_MESSAGE("AddFixedGroup", 0 == iRet);

	//ˢ�¹̶�Ⱥ���б�
	std::vector<UCFixedGroup> fixedlist;
	RefreshFixedGrouplist_(fixedlist);
	CPPUNIT_ASSERT_MESSAGE("RefreshFixedGrouplist", 1 == fixedlist.size());

	//��ȡ���ع̶�Ⱥ���б�
	std::vector<UCFixedGroup> locallist;
	GetFixedGrouplist_(locallist);
	CPPUNIT_ASSERT_MESSAGE("GetFixedGrouplist", 1 == locallist.size());
	CPPUNIT_ASSERT_MESSAGE("GetFixedGrouplist", 0 == strcmp(fixedlist[0].id_, locallist[0].id_));

	//ɾ���̶�Ⱥ��
	iRet = pUCUnitTest->m_fpRemoveFixedGroup(&fixedgroup);
	CPPUNIT_ASSERT_MESSAGE("RemoveFixedGroup", 0 == iRet);

	//ˢ�¹̶�Ⱥ���б�
	fixedlist.clear();
	RefreshFixedGrouplist_(fixedlist);
	CPPUNIT_ASSERT_MESSAGE("RefreshFixedGrouplist", 0 == fixedlist.size());

	//��ȡ���ع̶�Ⱥ���б�
	locallist.clear();
	GetFixedGrouplist_(locallist);
	CPPUNIT_ASSERT_MESSAGE("GetFixedGrouplist", 0 == locallist.size());
}

void UT_UCGroup::UT_GetFixedGroupByID()
{
	UCUnitTest* pUCUnitTest = UCUnitTest::Instance();

	//��������
	RemoveAllFixedGroup();

	//�½��̶�Ⱥ��
	UCFixedGroup fixedgroup;
	memset(&fixedgroup, 0, sizeof(fixedgroup));
	memcpy(fixedgroup.name_, "MyTestFixedGroup", strlen("MyTestFixedGroup"));
	int iRet = pUCUnitTest->m_fpAddFixedGroup(&fixedgroup);
	CPPUNIT_ASSERT_MESSAGE("AddFixedGroup", 0 == iRet);

	//ˢ�¹̶�Ⱥ�飬ͬ���̶�Ⱥ����Ϣ
	std::vector<UCContact> contactlist;
	RefreshContactList_(&fixedgroup, contactlist);
	CPPUNIT_ASSERT_MESSAGE("RefreshContactList", 1 == contactlist.size());

	//ͨ��ID��ȡ�̶�Ⱥ��
	UCFixedGroup tmpgroup;
	memset(&tmpgroup, 0, sizeof(tmpgroup));
	iRet = pUCUnitTest->m_fpGetFixedGroupByID(fixedgroup.id_, &tmpgroup);
	CPPUNIT_ASSERT_MESSAGE("GetFixedGroupByID", 0 == iRet);
	CPPUNIT_ASSERT_MESSAGE("GetFixedGroupByID", 0 == strcmp(fixedgroup.name_, tmpgroup.name_));

	memset(&tmpgroup, 0, sizeof(tmpgroup));
	iRet = pUCUnitTest->m_fpGetFixedGroupByID("ErrorFixedGroupId", &tmpgroup);
	CPPUNIT_ASSERT_MESSAGE("GetFixedGroupByID", 0 != iRet);
	CPPUNIT_ASSERT_MESSAGE("GetFixedGroupByID", 0 == strcmp("", tmpgroup.name_));

	//ɾ���̶�Ⱥ��
	iRet = pUCUnitTest->m_fpRemoveFixedGroup(&fixedgroup);
	CPPUNIT_ASSERT_MESSAGE("RemoveFixedGroup", 0 == iRet);

	//��ȡ�̶�Ⱥ���б�
	std::vector<UCFixedGroup> fixedlist;
	RefreshFixedGrouplist_(fixedlist);
	CPPUNIT_ASSERT_MESSAGE("RefreshFixedGrouplist", 0 == fixedlist.size());
}

void UT_UCGroup::UT_GetFixedGroupByUri()
{
	UCUnitTest* pUCUnitTest = UCUnitTest::Instance();

	//��������
	RemoveAllFixedGroup();

	//�½��̶�Ⱥ��
	UCFixedGroup fixedgroup;
	memset(&fixedgroup, 0, sizeof(fixedgroup));
	memcpy(fixedgroup.name_, "MyTestFixedGroup", strlen("MyTestFixedGroup"));
	int iRet = pUCUnitTest->m_fpAddFixedGroup(&fixedgroup);
	CPPUNIT_ASSERT_MESSAGE("AddFixedGroup", 0 == iRet);

	//ˢ�¹̶�Ⱥ�飬ͬ���̶�Ⱥ����Ϣ
	std::vector<UCContact> contactlist;
	RefreshContactList_(&fixedgroup, contactlist);
	CPPUNIT_ASSERT_MESSAGE("RefreshContactList", 1 == contactlist.size());

	//ͨ��ID��ȡ�̶�Ⱥ��
	UCFixedGroup tmpgroup;
	memset(&tmpgroup, 0, sizeof(tmpgroup));
	iRet = pUCUnitTest->m_fpGetFixedGroupByUri(fixedgroup.uri_, &tmpgroup);
	CPPUNIT_ASSERT_MESSAGE("GetFixedGroupByUri", 0 == iRet);
	CPPUNIT_ASSERT_MESSAGE("GetFixedGroupByUri", 0 == strcmp(fixedgroup.name_, tmpgroup.name_));

	memset(&tmpgroup, 0, sizeof(tmpgroup));
	iRet = pUCUnitTest->m_fpGetFixedGroupByUri("ErrorFixedGroupUri", &tmpgroup);
	CPPUNIT_ASSERT_MESSAGE("GetFixedGroupByUri", 0 != iRet);
	CPPUNIT_ASSERT_MESSAGE("GetFixedGroupByUri", 0 == strcmp("", tmpgroup.name_));

	//ɾ���̶�Ⱥ��
	iRet = pUCUnitTest->m_fpRemoveFixedGroup(&fixedgroup);
	CPPUNIT_ASSERT_MESSAGE("RemoveFixedGroup", 0 == iRet);

	//��ȡ�̶�Ⱥ���б�
	std::vector<UCFixedGroup> fixedlist;
	RefreshFixedGrouplist_(fixedlist);
	CPPUNIT_ASSERT_MESSAGE("RefreshFixedGrouplist", 0 == fixedlist.size());
}

void UT_UCGroup::UT_GetCustomGroupById()
{
	UCUnitTest* pUCUnitTest = UCUnitTest::Instance();

	//�����б��ѯ
	std::vector<UCCustomGroup> vecList;
	GetCustomGrouplist_(vecList);
	CPPUNIT_ASSERT_MESSAGE("GetCustomGrouplist", 1 == vecList.size());
	CPPUNIT_ASSERT_MESSAGE("GetCustomGrouplist", 0 == strcmp(vecList[0].id_, "-1"));

	//��ȡĬ�Ϸ���
	UCCustomGroup tmpgroup;
	memset(&tmpgroup, 0, sizeof(tmpgroup));
	int iRet = pUCUnitTest->m_fpGetCustomGroupById("-1", &tmpgroup);
	CPPUNIT_ASSERT_MESSAGE("GetCustomGroupById", 0 == iRet);
	CPPUNIT_ASSERT_MESSAGE("GetCustomGroupById", 0 == strcmp(tmpgroup.name_, "defaultgroup"));

	memset(&tmpgroup, 0, sizeof(tmpgroup));
	iRet = pUCUnitTest->m_fpGetCustomGroupById("ErrorCustomGroupId", &tmpgroup);
	CPPUNIT_ASSERT_MESSAGE("GetCustomGroupById", 0 != iRet);
	CPPUNIT_ASSERT_MESSAGE("GetCustomGroupById", 0 == strcmp(tmpgroup.name_, ""));

	//�½�����
	UCCustomGroup customgroup;
	memset(&customgroup, 0, sizeof(customgroup));
	memcpy(customgroup.name_, "MyTestCustomGroup", strlen("MyTestCustomGroup"));
	iRet = pUCUnitTest->m_fpAddCustomGroup(&customgroup);
	CPPUNIT_ASSERT_MESSAGE("AddCustomGroup", 0 == iRet);

	//��ȡ�½�����
	memset(&tmpgroup, 0, sizeof(tmpgroup));
	iRet = pUCUnitTest->m_fpGetCustomGroupById(customgroup.id_, &tmpgroup);
	CPPUNIT_ASSERT_MESSAGE("GetCustomGroupById", 0 == iRet);
	CPPUNIT_ASSERT_MESSAGE("GetCustomGroupById", 0 == strcmp(tmpgroup.name_, customgroup.name_));

	//ɾ������	ע�⣺�������գ�����������ϵ���޷���
	iRet = pUCUnitTest->m_fpRemoveCustomGroup(&customgroup);
	CPPUNIT_ASSERT_MESSAGE("AddCustomGroup", 0 == iRet);

	//��ȡ�����б�
	vecList.clear();
	GetCustomGrouplist_(vecList);
	CPPUNIT_ASSERT_MESSAGE("GetCustomGrouplist", 1 == vecList.size());
	CPPUNIT_ASSERT_MESSAGE("GetCustomGrouplist", 0 == strcmp(vecList[0].id_, "-1"));	
}

void UT_UCGroup::UT_SearchFixedGroup()
{
	UCUnitTest* pUCUnitTest = UCUnitTest::Instance();

	//��������
	RemoveAllFixedGroup();

	//�½��̶�Ⱥ��
	UCFixedGroup fixedgroup;
	memset(&fixedgroup, 0, sizeof(fixedgroup));
	memcpy(fixedgroup.name_, "MyTestFixedGroup", strlen("MyTestFixedGroup"));
	int iRet = pUCUnitTest->m_fpAddFixedGroup(&fixedgroup);
	CPPUNIT_ASSERT_MESSAGE("AddFixedGroup", 0 == iRet);

	//��ȡ�̶�Ⱥ���б�
	std::vector<UCFixedGroup> fixedlist;
	RefreshFixedGrouplist_(fixedlist);
	CPPUNIT_ASSERT_MESSAGE("RefreshFixedGrouplist", 1 == fixedlist.size());

	//�����̶�Ⱥ��
	const int SIZE = 10;
	UCFixedGroupList searchlist;
	memset(&searchlist, 0, sizeof(searchlist));
	searchlist.group = (UCFixedGroup*)malloc(sizeof(UCFixedGroup)*SIZE);
	memset(searchlist.group, 0, sizeof(UCFixedGroup)*SIZE);
	iRet = pUCUnitTest->m_fpSearchFixedGroup("", "MyTestFixedGroup", 1, SIZE, &searchlist);
	CPPUNIT_ASSERT_MESSAGE("SearchFixedGroup", 0 == iRet);
	CPPUNIT_ASSERT_MESSAGE("SearchFixedGroup", 0 < searchlist.iTotal);
	if (0 == iRet)
	{
		bool bFound = false;
		for (int i=0; i<=searchlist.iTo - searchlist.iFrom; i++)
		{
			if (0 == strcmp(searchlist.group[i].name_, "MyTestFixedGroup"))
			{
				bFound = true;
				break;
			}
		}
		CPPUNIT_ASSERT_MESSAGE("SearchFixedGroup", bFound);
	}

	memset(searchlist.group, 0, sizeof(UCFixedGroup)*SIZE);
	iRet = pUCUnitTest->m_fpSearchFixedGroup("", "MyTest", 1, SIZE, &searchlist);
	CPPUNIT_ASSERT_MESSAGE("SearchFixedGroup", 0 == iRet);
	CPPUNIT_ASSERT_MESSAGE("SearchFixedGroup", 0 < searchlist.iTotal);
	if (0 == iRet)
	{
		bool bFound = false;
		for (int i=0; i<=searchlist.iTo - searchlist.iFrom; i++)
		{
			if (0 == strcmp(searchlist.group[i].name_, "MyTestFixedGroup"))
			{
				bFound = true;
				break;
			}
		}
		CPPUNIT_ASSERT_MESSAGE("SearchFixedGroup", bFound);
	}

	memset(searchlist.group, 0, sizeof(UCFixedGroup)*SIZE);
	iRet = pUCUnitTest->m_fpSearchFixedGroup("", "ErrorSearchFixedGroupName", 1, SIZE, &searchlist);
	CPPUNIT_ASSERT_MESSAGE("SearchFixedGroup", 0 == iRet);
	CPPUNIT_ASSERT_MESSAGE("SearchFixedGroup", 0 == searchlist.iTotal);

	//ɾ���̶�Ⱥ��
	iRet = pUCUnitTest->m_fpRemoveFixedGroup(&fixedgroup);
	CPPUNIT_ASSERT_MESSAGE("RemoveFixedGroup", 0 == iRet);

	//��ȡ�̶�Ⱥ���б�
	fixedlist.clear();
	RefreshFixedGrouplist_(fixedlist);
	CPPUNIT_ASSERT_MESSAGE("RefreshFixedGrouplist", 0 == fixedlist.size());
}

void UT_UCGroup::UT_RenameToCustomGroup()
{
	UCUnitTest* pUCUnitTest = UCUnitTest::Instance();

	//�����б��ѯ
	std::vector<UCCustomGroup> vecList;
	GetCustomGrouplist_(vecList);
	CPPUNIT_ASSERT_MESSAGE("GetCustomGrouplist", 1 == vecList.size());
	CPPUNIT_ASSERT_MESSAGE("GetCustomGrouplist", 0 == strcmp(vecList[0].id_, "-1"));

	//�½�����
	UCCustomGroup customgroup;
	memset(&customgroup, 0, sizeof(customgroup));
	memcpy(customgroup.name_, "MyTestCustomGroup", strlen("MyTestCustomGroup"));
	int iRet = pUCUnitTest->m_fpAddCustomGroup(&customgroup);
	CPPUNIT_ASSERT_MESSAGE("AddCustomGroup", 0 == iRet);

	//�����б��ѯ
	vecList.clear();
	GetCustomGrouplist_(vecList);
	CPPUNIT_ASSERT_MESSAGE("GetCustomGrouplist", 2 == vecList.size());
	CPPUNIT_ASSERT_MESSAGE("GetCustomGrouplist", (0 == strcmp(vecList[0].id_, "-1") && 0 == strcmp(vecList[1].name_, customgroup.name_))
		|| (0 == strcmp(vecList[1].id_, "-1") && 0 == strcmp(vecList[0].name_, customgroup.name_)));

	//�޸��½�������
	iRet = pUCUnitTest->m_fpRenameToCustomGroup(&customgroup, "MyTestCustomGroup_Rename");
	CPPUNIT_ASSERT_MESSAGE("RenameToCustomGroup", 0 == iRet);

	//�����б��ѯ
	vecList.clear();
	GetCustomGrouplist_(vecList);
	CPPUNIT_ASSERT_MESSAGE("GetCustomGrouplist", 2 == vecList.size());
	CPPUNIT_ASSERT_MESSAGE("GetCustomGrouplist", (0 == strcmp(vecList[0].id_, "-1") && 0 == strcmp(vecList[1].name_, "MyTestCustomGroup_Rename"))
		|| (0 == strcmp(vecList[1].id_, "-1") && 0 == strcmp(vecList[0].name_, "MyTestCustomGroup_Rename")));

	//ɾ������	ע�⣺�������գ�����������ϵ���޷���
	int index = (0 == strcmp(vecList[0].id_, "-1")) ? 1 : 0;
	iRet = pUCUnitTest->m_fpRemoveCustomGroup(&vecList[index]);
	CPPUNIT_ASSERT_MESSAGE("AddCustomGroup", 0 == iRet);

	//�����б��ѯ
	vecList.clear();
	GetCustomGrouplist_(vecList);
	CPPUNIT_ASSERT_MESSAGE("GetCustomGrouplist", 1 == vecList.size());
	CPPUNIT_ASSERT_MESSAGE("GetCustomGrouplist", 0 == strcmp(vecList[0].id_, "-1"));	
}

void UT_UCGroup::UT_RenameToFixedGroup()
{
	UCUnitTest* pUCUnitTest = UCUnitTest::Instance();

	//��������
	RemoveAllFixedGroup();

	//�½��̶�Ⱥ��
	UCFixedGroup fixedgroup;
	memset(&fixedgroup, 0, sizeof(fixedgroup));
	memcpy(fixedgroup.name_, "MyTestFixedGroup", strlen("MyTestFixedGroup"));
	int iRet = pUCUnitTest->m_fpAddFixedGroup(&fixedgroup);
	CPPUNIT_ASSERT_MESSAGE("AddFixedGroup", 0 == iRet);

	//��ȡ�̶�Ⱥ���б�
	std::vector<UCFixedGroup> fixedlist;
	RefreshFixedGrouplist_(fixedlist);
	CPPUNIT_ASSERT_MESSAGE("RefreshFixedGrouplist", 1 == fixedlist.size());
	CPPUNIT_ASSERT_MESSAGE("RefreshFixedGrouplist", 0 == strcmp(fixedlist[0].name_, "MyTestFixedGroup"));

	//�̶�Ⱥ��������
	iRet = pUCUnitTest->m_fpRenameToFixedGroup(&fixedgroup, "MyTestFixedGroup_Rename");
	CPPUNIT_ASSERT_MESSAGE("RenameToFixedGroup", 0 == iRet);

	//��ȡ�̶�Ⱥ���б�
	fixedlist.clear();
	RefreshFixedGrouplist_(fixedlist);
	CPPUNIT_ASSERT_MESSAGE("RefreshFixedGrouplist", 1 == fixedlist.size());
	CPPUNIT_ASSERT_MESSAGE("RefreshFixedGrouplist", 0 == strcmp(fixedlist[0].name_, "MyTestFixedGroup_Rename"));

	//ɾ���̶�Ⱥ��
	iRet = pUCUnitTest->m_fpRemoveFixedGroup(&fixedlist[0]);
	CPPUNIT_ASSERT_MESSAGE("RemoveFixedGroup", 0 == iRet);

	//��ȡ�̶�Ⱥ���б�
	fixedlist.clear();
	RefreshFixedGrouplist_(fixedlist);
	CPPUNIT_ASSERT_MESSAGE("RefreshFixedGrouplist", 0 == fixedlist.size());
}

void UT_UCGroup::UT_ChangeGroupInfo()
{
	UCUnitTest* pUCUnitTest = UCUnitTest::Instance();

	//��������
	RemoveAllFixedGroup();

	//�½��̶�Ⱥ��
	UCFixedGroup fixedgroup;
	memset(&fixedgroup, 0, sizeof(fixedgroup));
	memcpy(fixedgroup.name_, "MyTestFixedGroup", strlen("MyTestFixedGroup"));
	int iRet = pUCUnitTest->m_fpAddFixedGroup(&fixedgroup);
	CPPUNIT_ASSERT_MESSAGE("AddFixedGroup", 0 == iRet);

	//��ȡ�̶�Ⱥ���б�
	std::vector<UCFixedGroup> fixedlist;
	RefreshFixedGrouplist_(fixedlist);
	CPPUNIT_ASSERT_MESSAGE("RefreshFixedGrouplist", 1 == fixedlist.size());
	CPPUNIT_ASSERT_MESSAGE("RefreshFixedGrouplist", 0 == strcmp(fixedlist[0].name_, "MyTestFixedGroup"));

	//�޸Ĺ̶�Ⱥ����Ϣ
	memcpy(fixedgroup.name_, "MyTestFixedGroup_Rename", strlen("MyTestFixedGroup_Rename"));
	memcpy(fixedgroup.bulletin_, "bulletin_", strlen("bulletin_"));
	memcpy(fixedgroup.desc_, "desc_", strlen("desc_"));
	memset(fixedgroup.needpermit_, 0, sizeof(fixedgroup.needpermit_));
	memcpy(fixedgroup.needpermit_, "true", strlen("true"));
	iRet = pUCUnitTest->m_fpChangeGroupInfo(&fixedgroup);
	CPPUNIT_ASSERT_MESSAGE("ChangeGroupInfo", 0 == iRet);

	//��ȡ�̶�Ⱥ���б�
	fixedlist.clear();
	RefreshFixedGrouplist_(fixedlist);
	CPPUNIT_ASSERT_MESSAGE("RefreshFixedGrouplist", 1 == fixedlist.size());
	CPPUNIT_ASSERT_MESSAGE("RefreshFixedGrouplist", 0 == strcmp(fixedlist[0].name_, "MyTestFixedGroup_Rename"));
	CPPUNIT_ASSERT_MESSAGE("RefreshFixedGrouplist", 0 == strcmp(fixedlist[0].bulletin_, "bulletin_"));
	CPPUNIT_ASSERT_MESSAGE("RefreshFixedGrouplist", 0 == strcmp(fixedlist[0].desc_, "desc_"));
	CPPUNIT_ASSERT_MESSAGE("RefreshFixedGrouplist", 0 == strcmp(fixedlist[0].needpermit_, "true"));

	//ɾ���̶�Ⱥ��
	iRet = pUCUnitTest->m_fpRemoveFixedGroup(&fixedlist[0]);
	CPPUNIT_ASSERT_MESSAGE("RemoveFixedGroup", 0 == iRet);

	//��ȡ�̶�Ⱥ���б�
	fixedlist.clear();
	RefreshFixedGrouplist_(fixedlist);
	CPPUNIT_ASSERT_MESSAGE("RefreshFixedGrouplist", 0 == fixedlist.size());
}

void UT_UCGroup::UT_ChangeGroupOwner()
{

}

void UT_UCGroup::UT_RefreshGroup()
{
	UCUnitTest* pUCUnitTest = UCUnitTest::Instance();

	//��������
	RemoveAllFixedGroup();

	//�½��̶�Ⱥ��
	UCFixedGroup fixedgroup;
	memset(&fixedgroup, 0, sizeof(fixedgroup));
	memcpy(fixedgroup.name_, "MyTestFixedGroup", strlen("MyTestFixedGroup"));
	int iRet = pUCUnitTest->m_fpAddFixedGroup(&fixedgroup);
	CPPUNIT_ASSERT_MESSAGE("AddFixedGroup", 0 == iRet);

	//ˢ�¹̶�Ⱥ��
	iRet = pUCUnitTest->m_fpRefreshGroup(&fixedgroup);
	CPPUNIT_ASSERT_MESSAGE("RefreshGroup", 0 == iRet);

	//��ȡ�̶�Ⱥ���б�
	std::vector<UCFixedGroup> fixedlist;
	RefreshFixedGrouplist_(fixedlist);
	CPPUNIT_ASSERT_MESSAGE("RefreshFixedGrouplist", 1 == fixedlist.size());

	//ɾ���̶�Ⱥ��
	iRet = pUCUnitTest->m_fpRemoveFixedGroup(&fixedgroup);
	CPPUNIT_ASSERT_MESSAGE("RemoveFixedGroup", 0 == iRet);

	//��ȡ�̶�Ⱥ���б�
	fixedlist.clear();
	RefreshFixedGrouplist_(fixedlist);
	CPPUNIT_ASSERT_MESSAGE("RefreshFixedGrouplist", 0 == fixedlist.size());
}

void UT_UCGroup::UT_AcceptInvitation()
{

}

void UT_UCGroup::UT_RejectInvitation()
{

}

void UT_UCGroup::UT_AcceptJoinReq()
{

}

void UT_UCGroup::UT_RejectJoinReq()
{

}

void UT_UCGroup::GetCustomGrouplist_(std::vector<UCCustomGroup>& vecList)
{
	vecList.clear();
	UCUnitTest* pUCUnitTest = UCUnitTest::Instance();

	const int SIZE = 10;
	int iFrom = 0;
	int iTo = SIZE - 1;
	UCCustomGroupList customlist;
	memset(&customlist, 0, sizeof(customlist));
	customlist.group = (UCCustomGroup*)malloc(sizeof(UCCustomGroup)*SIZE);

	do
	{
		memset(customlist.group, 0, sizeof(UCCustomGroup)*SIZE);
		int iRet = pUCUnitTest->m_fpGetCustomGrouplist(iFrom, iTo, &customlist);
		CPPUNIT_ASSERT_MESSAGE("GetCustomGrouplist", 0 == iRet);
		for (int i=0; i<=customlist.iTo - customlist.iFrom; i++)
		{
			vecList.push_back(customlist.group[i]);
		}
		iFrom += SIZE;
		iTo += SIZE;

	} while(customlist.iTo + 1 < customlist.iTotal);

	free(customlist.group);
	memset(&customlist, 0, sizeof(customlist));
}

void UT_UCGroup::RemoveAllCustomGroupExceptDefault()
{
	UCUnitTest* pUCUnitTest = UCUnitTest::Instance();

	std::vector<UCCustomGroup> vecList;
	GetCustomGrouplist_(vecList);

	std::vector<UCCustomGroup>::iterator itor = vecList.begin();
	for (; itor != vecList.end(); itor++)
	{
		if (0 == strcmp(itor->id_, "-1"))
		{
			continue;
		}

		UCCustomGroup& group = *itor;
		int iRet = pUCUnitTest->m_fpRemoveCustomGroup(&group);
		CPPUNIT_ASSERT_MESSAGE("RemoveCustomGroup", 0 == iRet);
	}
}

void UT_UCGroup::GetContactlistFromCustomGroup_(const UCCustomGroup* group, std::vector<UCContact>& vecList)
{
	vecList.clear();
	UCUnitTest* pUCUnitTest = UCUnitTest::Instance();

	const int SIZE = 10;
	int iFrom = 0;
	int iTo = SIZE - 1;
	UCContactList contactlist;
	memset(&contactlist, 0, sizeof(contactlist));
	contactlist.contact = (UCContact*)malloc(sizeof(UCContact)*SIZE);

	do
	{
		memset(contactlist.contact, 0, sizeof(UCContact)*SIZE);
		int iRet = pUCUnitTest->m_fpGetContactlistFromCustomGroup(group, iFrom, iTo, &contactlist);
		//CPPUNIT_ASSERT_MESSAGE("GetContactlistFromCustomGroup", 0 == iRet);
		if (0 == iRet)
		{
			for (int i=0; i<=contactlist.iTo - contactlist.iFrom; i++)
			{
				vecList.push_back(contactlist.contact[i]);
			}
		}

		iFrom += SIZE;
		iTo += SIZE;

	} while(contactlist.iTo + 1 < contactlist.iTotal);

	free(contactlist.contact);
	memset(&contactlist, 0, sizeof(contactlist));
}

void UT_UCGroup::RefreshFixedGrouplist_(std::vector<UCFixedGroup>& vecList)
{
	vecList.clear();
	UCUnitTest* pUCUnitTest = UCUnitTest::Instance();

	const int SIZE = 10;
	int iFrom = 0;
	int iTo = SIZE - 1;
	UCFixedGroupList fixedlist;
	memset(&fixedlist, 0, sizeof(fixedlist));
	fixedlist.group = (UCFixedGroup*)malloc(sizeof(UCFixedGroup)*SIZE);

	do
	{
		memset(fixedlist.group, 0, sizeof(UCFixedGroup)*SIZE);
		int iRet = pUCUnitTest->m_fpRefreshFixedGrouplist(iFrom, iTo, &fixedlist);
		CPPUNIT_ASSERT_MESSAGE("RefreshFixedGrouplist", 0 == iRet);
		for (int i=0; i<=fixedlist.iTo - fixedlist.iFrom; i++)
		{
			vecList.push_back(fixedlist.group[i]);
		}
		iFrom += SIZE;
		iTo += SIZE;

	} while(fixedlist.iTo + 1 < fixedlist.iTotal);

	free(fixedlist.group);
	memset(&fixedlist, 0, sizeof(fixedlist));
}

void UT_UCGroup::RefreshContactList_(const UCFixedGroup* group, std::vector<UCContact>& vecList)
{
	vecList.clear();
	UCUnitTest* pUCUnitTest = UCUnitTest::Instance();

	const int SIZE = 10;
	int iFrom = 0;
	int iTo = SIZE - 1;
	UCContactList contactlist;
	memset(&contactlist, 0, sizeof(contactlist));
	contactlist.contact = (UCContact*)malloc(sizeof(UCContact)*SIZE);

	do
	{
		memset(contactlist.contact, 0, sizeof(UCContact)*SIZE);
		int iRet = pUCUnitTest->m_fpRefreshContactList(group, iFrom, iTo, &contactlist);
		CPPUNIT_ASSERT_MESSAGE("RefreshContactList", 0 == iRet);
		for (int i=0; i<=contactlist.iTo - contactlist.iFrom; i++)
		{
			vecList.push_back(contactlist.contact[i]);
		}
		iFrom += SIZE;
		iTo += SIZE;

	} while(contactlist.iTo + 1 < contactlist.iTotal);

	free(contactlist.contact);
	memset(&contactlist, 0, sizeof(contactlist));
}

void UT_UCGroup::GetFixedGrouplist_(std::vector<UCFixedGroup>& vecList)
{
	vecList.clear();
	UCUnitTest* pUCUnitTest = UCUnitTest::Instance();

	const int SIZE = 10;
	int iFrom = 0;
	int iTo = SIZE - 1;
	UCFixedGroupList fixedlist;
	memset(&fixedlist, 0, sizeof(fixedlist));
	fixedlist.group = (UCFixedGroup*)malloc(sizeof(UCFixedGroup)*SIZE);

	do
	{
		memset(fixedlist.group, 0, sizeof(UCFixedGroup)*SIZE);
		int iRet = pUCUnitTest->m_fpGetFixedGrouplist(iFrom, iTo, &fixedlist);
		CPPUNIT_ASSERT_MESSAGE("GetFixedGrouplist", 0 == iRet);
		for (int i=0; i<=fixedlist.iTo - fixedlist.iFrom; i++)
		{
			vecList.push_back(fixedlist.group[i]);
		}
		iFrom += SIZE;
		iTo += SIZE;

	} while(fixedlist.iTo + 1 < fixedlist.iTotal);

	free(fixedlist.group);
	memset(&fixedlist, 0, sizeof(fixedlist));
}

void UT_UCGroup::RemoveAllFixedGroup()
{
	UCUnitTest* pUCUnitTest = UCUnitTest::Instance();

	std::vector<UCFixedGroup> fixedlist;
	RefreshFixedGrouplist_(fixedlist);

	std::vector<UCFixedGroup>::iterator itor = fixedlist.begin();
	for (; itor != fixedlist.end(); itor++)
	{
		UCFixedGroup& group = *itor;
		int iRet = pUCUnitTest->m_fpRemoveFixedGroup(&group);
		CPPUNIT_ASSERT_MESSAGE("RemoveFixedGroup", 0 == iRet);
	}
}