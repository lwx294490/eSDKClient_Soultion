#ifndef _UT_GROUP_ABS_PROXY_H
#define _UT_GROUP_ABS_PROXY_H

#include "cppunit/extensions/HelperMacros.h"
#include "UCGroupAbsProxy.h"

class UTGroupAbsProxy : public CppUnit::TestFixture
{
public:
	UTGroupAbsProxy();
	~UTGroupAbsProxy();

public:
	CPPUNIT_TEST_SUITE( UTGroupAbsProxy );
	CPPUNIT_TEST(UTGroupAbsProxy_AddFixedGroup);
	CPPUNIT_TEST(UTGroupAbsProxy_GetFixedGroupByID);
	CPPUNIT_TEST(UTGroupAbsProxy_GetFixedGroupByUri);
	CPPUNIT_TEST(UTGroupAbsProxy_RemoveFixedGroup);
	CPPUNIT_TEST(UTGroupAbsProxy_RefreshFixedGrouplist);
	CPPUNIT_TEST(UTGroupAbsProxy_GetFixedGrouplist);
	CPPUNIT_TEST(UTGroupAbsProxy_SearchFixedGroup);
	CPPUNIT_TEST(UTGroupAbsProxy_AddCustomGroup);
	CPPUNIT_TEST(UTGroupAbsProxy_AddFavoriteGroup);
	CPPUNIT_TEST(UTGroupAbsProxy_GetCustomGroupById);
	CPPUNIT_TEST(UTGroupAbsProxy_GetCustomGrouplist);
	CPPUNIT_TEST(UTGroupAbsProxy_RemoveCustomGroup);
	CPPUNIT_TEST(UTGroupAbsProxy_AddContact);
	CPPUNIT_TEST(UTGroupAbsProxy_RemoveContact);
	CPPUNIT_TEST(UTGroupAbsProxy_Rename);
	CPPUNIT_TEST(UTGroupAbsProxy_GetContactlist);
	CPPUNIT_TEST(UTGroupAbsProxy_FixedGroup_AddContact);
	CPPUNIT_TEST(UTGroupAbsProxy_FixedGroup_RemoveContact);
	CPPUNIT_TEST(UTGroupAbsProxy_FixedGroup_Rename);
	CPPUNIT_TEST(UTGroupAbsProxy_FixedGroup_GetContactlist);
	CPPUNIT_TEST(UTGroupAbsProxy_FixedGroup_ChangeGroupInfo);
	CPPUNIT_TEST(UTGroupAbsProxy_FixedGroup_ChangeGroupOwner);
	CPPUNIT_TEST(UTGroupAbsProxy_FixedGroup_Refresh);
	CPPUNIT_TEST(UTGroupAbsProxy_FixedGroup_Refresh_SYNC);
	CPPUNIT_TEST_SUITE_END();

public:
	// 初始化函数
	virtual void setUp();
	// 清理函数
	virtual void tearDown();

public:
	//测试用例
	void UTGroupAbsProxy_AddFixedGroup();
	void UTGroupAbsProxy_GetFixedGroupByID();
	void UTGroupAbsProxy_GetFixedGroupByUri();
	void UTGroupAbsProxy_RemoveFixedGroup();
	void UTGroupAbsProxy_RefreshFixedGrouplist();
	void UTGroupAbsProxy_GetFixedGrouplist();
	void UTGroupAbsProxy_SearchFixedGroup();
	void UTGroupAbsProxy_AddCustomGroup();
	void UTGroupAbsProxy_AddFavoriteGroup();
	void UTGroupAbsProxy_GetCustomGroupById();
	void UTGroupAbsProxy_GetCustomGrouplist();
	void UTGroupAbsProxy_RemoveCustomGroup();
	void UTGroupAbsProxy_AddContact();
	void UTGroupAbsProxy_RemoveContact();
	void UTGroupAbsProxy_Rename();
	void UTGroupAbsProxy_GetContactlist();
	void UTGroupAbsProxy_FixedGroup_AddContact();
	void UTGroupAbsProxy_FixedGroup_RemoveContact();
	void UTGroupAbsProxy_FixedGroup_Rename();
	void UTGroupAbsProxy_FixedGroup_GetContactlist();
	void UTGroupAbsProxy_FixedGroup_ChangeGroupInfo();
	void UTGroupAbsProxy_FixedGroup_ChangeGroupOwner();
	void UTGroupAbsProxy_FixedGroup_Refresh();
	void UTGroupAbsProxy_FixedGroup_Refresh_SYNC();

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