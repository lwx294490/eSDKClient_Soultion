#ifndef _UT_CONTACT_MGR_H
#define _UT_CONTACT_MGR_H

#include "cppunit/extensions/HelperMacros.h"
#include "UCContactMgrAbsProxy.h"

class UTContactMgrAbsProxy : public CppUnit::TestFixture
{
public:
	UTContactMgrAbsProxy();
	~UTContactMgrAbsProxy();

public:
	CPPUNIT_TEST_SUITE( UTContactMgrAbsProxy );
	CPPUNIT_TEST(UTContactMgrAbsProxy_GetContactById);
	CPPUNIT_TEST(UTContactMgrAbsProxy_GetContactByAccount);
	CPPUNIT_TEST(UTContactMgrAbsProxy_GetContactByPhoneNum);
	CPPUNIT_TEST(UTContactMgrAbsProxy_GetContactByUri);
	CPPUNIT_TEST(UTContactMgrAbsProxy_HasContact);
	CPPUNIT_TEST(UTContactMgrAbsProxy_RefreshContactByAccount);
	CPPUNIT_TEST(UTContactMgrAbsProxy_RefreshContactByUri);
	CPPUNIT_TEST(UTContactMgrAbsProxy_RefreshContactById);
	CPPUNIT_TEST(UTContactMgrAbsProxy_RemoveContactById);
	CPPUNIT_TEST(UTContactMgrAbsProxy_SearchContact);
	CPPUNIT_TEST(UTContactMgrAbsProxy_Modify);
	CPPUNIT_TEST(UTContactMgrAbsProxy_GetHeadImagePath);
	CPPUNIT_TEST(UTContactMgrAbsProxy_MoveToGroup);
	CPPUNIT_TEST(UTContactMgrAbsProxy_AddToGroup);
	CPPUNIT_TEST(UTContactMgrAbsProxy_RemoveFromGroup);
	CPPUNIT_TEST(UTContactMgrAbsProxy_CanStartSession);
	CPPUNIT_TEST(UTContactMgrAbsProxy_CanMoveToGroup);
	CPPUNIT_TEST(UTContactMgrAbsProxy_GetCustomGroups);
	CPPUNIT_TEST(UTContactMgrAbsProxy_IsFavourite);
 	CPPUNIT_TEST_SUITE_END();

public:
	// 初始化函数
	virtual void setUp();
	// 清理函数
	virtual void tearDown();

public:
	//测试用例
	void UTContactMgrAbsProxy_GetContactById();
	void UTContactMgrAbsProxy_GetContactByAccount();
	void UTContactMgrAbsProxy_GetContactByPhoneNum();
	void UTContactMgrAbsProxy_GetContactByUri();
	void UTContactMgrAbsProxy_HasContact();
	void UTContactMgrAbsProxy_RefreshContactByAccount();
	void UTContactMgrAbsProxy_RefreshContactByUri();
	void UTContactMgrAbsProxy_RefreshContactById();
	void UTContactMgrAbsProxy_RemoveContactById();
	void UTContactMgrAbsProxy_SearchContact();
	void UTContactMgrAbsProxy_Modify();
	void UTContactMgrAbsProxy_GetHeadImagePath();
	void UTContactMgrAbsProxy_MoveToGroup();
	void UTContactMgrAbsProxy_AddToGroup();
	void UTContactMgrAbsProxy_RemoveFromGroup();
	void UTContactMgrAbsProxy_CanStartSession();
	void UTContactMgrAbsProxy_CanMoveToGroup();
	void UTContactMgrAbsProxy_GetCustomGroups();
	void UTContactMgrAbsProxy_IsFavourite();

	//辅助函数
private:
	void UTSignIn();
	void UTSignOut();
	void RemoveContact();

	//call back
private:
	static void CALLBACK TurnOnClientSignInNotify(int state, const std::string& reason);
	//static void CALLBACK OnStatusChanged(int _state,const STContact& _contact);
	//static void CALLBACK OnAVSessionClosed(const STMsgAVSessionClosedParam& _avParam);
	//static void CALLBACK OnAVSessionConnected();
	//static void CALLBACK OnAVSessAdded(const STAudioVideoParam& _avParam);
	//static void CALLBACK ConfMemberEventCB(const STConfParam& _avParam);
	//static void CALLBACK OnVideoEvent(const STVideoCallParam& _callPara);
	
private:
	static int m_iSignFlag;
};

#endif