// UCUnitTest.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "UCUnitTest.h"
#include "UT_UCSignalRecv.h"


int _tmain(int argc, _TCHAR* argv[])
{
	CppUnit::TextUi::TestRunner runner;

#ifdef _DEBUG
	std::ofstream outputFile("..\\output\\debug\\UnitTest_Results.xml");
#else
	std::ofstream outputFile("..\\output\\release\\UnitTest_Results.xml");
#endif

	CppUnit::Outputter *myoutputter;
	myoutputter = new CppUnit::XmlOutputter(&runner.result(), outputFile, "UTF-8");
	runner.setOutputter(myoutputter);

	CppUnit::TestFactoryRegistry &registry = CppUnit::TestFactoryRegistry::getRegistry("UCUnitTest");
	runner.addTest( registry.makeTest() );

	runner.run();

	return 0;
}

//////////////////////////////////////////////////////////////////////////
UCUnitTest* UCUnitTest::m_pUCUnitTest = NULL;
UCUnitTest::UCUnitTest()
	: m_hDll(NULL)
	, m_strAcc("bby")
	, m_strPwd("UcAAaa_11")
	, m_fpeSDKClientPlatform_Init(NULL)
	, m_fpeSDKClientPlatform_Uninit(NULL)
	, m_fpeSDKClientPlatform_LoginByPassword(NULL)
	, m_fpeSDKClientPlatform_Logout(NULL)
	, m_fpGetAllContactlist(NULL)
	, m_fpGetContactByAccount(NULL)
	, m_fpGetContactById(NULL)
	, m_fpGetContactByPhoneNum(NULL)
	, m_fpGetContactByUri(NULL)
	, m_fpHasContact(NULL)
	, m_fpRefreshContactByAccount(NULL)
	, m_fpRefreshContactById(NULL)
	, m_fpRefreshContactByUri(NULL)
	, m_fpRemoveContactById(NULL)
	, m_fpSearchContact(NULL)
	, m_fpModify(NULL)
	, m_fpGetHeadImagePath(NULL)
	, m_fpMoveToGroup(NULL)
	, m_fpAddToGroup(NULL)
	, m_fpRemoveFromGroup(NULL)
	, m_fpCanStartSession(NULL)
	, m_fpCanMoveToGroup(NULL)
	, m_fpGetCustomGroups(NULL)
	, m_fpIsFavourite(NULL)
	, m_fpAddFixedGroup(NULL)
	, m_fpGetFixedGroupByID(NULL)
	, m_fpGetFixedGroupByUri(NULL)
	, m_fpRemoveFixedGroup(NULL)
	, m_fpRefreshFixedGrouplist(NULL)
	, m_fpGetFixedGrouplist(NULL)
	, m_fpSearchFixedGroup(NULL)
	, m_fpAddCustomGroup(NULL)
	, m_fpAddFavoriteGroup(NULL)
	, m_fpGetCustomGroupById(NULL)
	, m_fpGetCustomGrouplist(NULL)
	, m_fpRemoveCustomGroup(NULL)
	, m_fpRemoveFavoriteGroup(NULL)
	, m_fpAddContactToFavoriteGroup(NULL)
	, m_fpRemoveContactFromFavoriteGroup(NULL)
	, m_fpRenameToFavoriteGroup(NULL)
	, m_fpGetContactlistFromFavoriteGroup(NULL)
	, m_fpAddContactToCustomGroup(NULL)
	, m_fpRemoveContactFromCustomGroup(NULL)
	, m_fpRenameToCustomGroup(NULL)
	, m_fpGetContactlistFromCustomGroup(NULL)
	, m_fpMoveUp(NULL)
	, m_fpMoveDown(NULL)
	, m_fpAddContactToFixedGroup(NULL)
	, m_fpRemoveContactFromFixedGroup(NULL)
	, m_fpRenameToFixedGroup(NULL)
	, m_fpGetContactlistFromFixedGroup(NULL)
	, m_fpChangeGroupInfo(NULL)
	, m_fpChangeGroupOwner(NULL)
	, m_fpRefreshContactList(NULL)
	, m_fpRefreshGroup(NULL)
	, m_fpAcceptInvitation(NULL)
	, m_fpRejectInvitation(NULL)
	, m_fpAcceptJoinReq(NULL)
	, m_fpRejectJoinReq(NULL)
	, m_fpSendIMMessage(NULL)
	, m_fpCloseConversation(NULL)
	, m_fpAcceptFile(NULL)
	, m_fpCancelFile(NULL)
	, m_fpRejectFile(NULL)
	, m_fpTransferFile(NULL)
	, m_fpMakeMeetingGroup(NULL)
	, m_fpStartMeeting(NULL)
	, m_fpAcceptMeeting(NULL)
	, m_fpAddParticipant(NULL)
	, m_fpConnectParticipant(NULL)
	, m_fpRemoveParticipant(NULL)
	, m_fpKickParticipant(NULL)
	, m_fpMuteMeeting(NULL)
	, m_fpUnMuteMeeting(NULL)
	, m_fpGetBookConfList(NULL)
	, m_fpJoinMeeting(NULL)
	, m_fpLeaveMeeting(NULL)
	, m_fpPublishSelfInformation(NULL)
	, m_fpGetContactStatus(NULL)
	, m_fpOnClientSignInNotify(NULL)
	, m_fpOnStatusChanged(NULL)
	, m_fpOnIncreContactsChanged(NULL)
	, m_fpOnAVSessAdded(NULL)
	, m_fpOnAVSessionConnected(NULL)
	, m_fpOnAVSessionClosed(NULL)
	, m_fpOnConvMemberStatusChanged(NULL)
	, m_fpOnConvMemAllowSpeak(NULL)
	, m_fpOnConvMemForbidSpeak(NULL)
	, m_fpOnConvMemCurSpeaker(NULL)
	, m_fpOnConvGroupMemberChanged(NULL)
	, m_fpOnReceivedIMMessage(NULL)
	, m_fpOnInstantSessRemoved(NULL)
	, m_fpOnInstantSessAdded(NULL)
	, m_fpOnSysMsgRecved(NULL)
	, m_fpOnGroupInvitation(NULL)
	, m_fpOnGroupInvitationRes(NULL)
	, m_fpOnLeaveFromFixedGroup(NULL)
	, m_fpOnJoinFixedGroupRequest(NULL)
	, m_fpOnJoinFixedGroupRes(NULL)
	, m_fpOnMemberAdded(NULL)
	, m_fpOnMemberRemoved(NULL)
	, m_fpOnMemberFlowChanged(NULL)
	, m_fpOnFixedGroupInfoChanged(NULL)
	, m_fpOnNewFileRercved(NULL)
	, m_fpOnFileAccept(NULL)
	, m_fpOnFileCancel(NULL)
	, m_fpOnFileProgress(NULL)
	, m_fpInit(NULL)
	, m_fpUnInit(NULL)
	, m_fpLoginByToken(NULL)
	, m_fpLoginByPasswd(NULL)
	, m_fpLogout(NULL)
	, m_fpConfig(NULL)
	, m_fpSetLang(NULL)
	, m_fpMakeCall(NULL)
	, m_fpAccept(NULL)
	, m_fpReject(NULL)
	, m_fpHangup(NULL)
	, m_fpHold(NULL)
	, m_fpResume(NULL)
	, m_fpForward(NULL)
	, m_fpStartRecord(NULL)
	, m_fpStopRecord(NULL)
	, m_fpMuteVoIP(NULL)
	, m_fpUnMuteVoIP(NULL)
{

}

UCUnitTest::~UCUnitTest()
{

}

UCUnitTest* UCUnitTest::Instance()
{
	if (NULL == m_pUCUnitTest)
	{
		m_pUCUnitTest = new UCUnitTest;
	}

	return m_pUCUnitTest;
}

void UCUnitTest::Destroy()
{
	if (NULL != m_pUCUnitTest)
	{
		delete m_pUCUnitTest;
		m_pUCUnitTest = NULL;
	}
}

bool UCUnitTest::Start(bool bIsNeedLogin)
{
	if (!LoadDll())
		return false;

	int iRet = m_fpeSDKClientPlatform_Init();
	if (0 != iRet)
	{
		return false;
	}

	SetUCSignalRecvCB();

	m_fpConfig("10.170.103.52:8081");
	m_fpSetLang("2052");
	if (bIsNeedLogin)
	{
		if (!Login())
		{
			return false;
		}
	}

	return true;
}

bool UCUnitTest::Stop(bool bIsNeedLogout)
{
	if (bIsNeedLogout)
	{
		if (!Logout())
		{
			return false;
		}
	}

	//int iRet = m_fpeSDKClientPlatform_Uninit();
	//if (0 != iRet)
	//{
	//	return false;
	//}

	if (!FreeDll())
	{
		return false;
	}

	return true;
}

bool UCUnitTest::LoadDll()
{
	m_hDll = LoadLibrary("eSDKClientPlatform.dll");
	if (NULL == m_hDll)
	{
		return false;
	}

	m_fpeSDKClientPlatform_Init = (fp_eSDKClientPlatform_Init)GetProcAddress(m_hDll, "eSDKClientPlatform_Init");
	m_fpeSDKClientPlatform_Uninit = (fp_eSDKClientPlatform_Uninit)GetProcAddress(m_hDll, "eSDKClientPlatform_Uninit");
	m_fpeSDKClientPlatform_LoginByPassword = (fp_eSDKClientPlatform_LoginByPassword)GetProcAddress(m_hDll, "eSDKClientPlatform_LoginByPassword");
	m_fpeSDKClientPlatform_Logout = (fp_eSDKClientPlatform_Logout)GetProcAddress(m_hDll, "eSDKClientPlatform_Logout");
	m_fpGetAllContactlist = (fp_GetAllContactlist)GetProcAddress(m_hDll, "GetAllContactlist");
	m_fpGetContactByAccount = (fp_GetContactByAccount)GetProcAddress(m_hDll, "GetContactByAccount");
	m_fpGetContactById = (fp_GetContactById)GetProcAddress(m_hDll, "GetContactById");
	m_fpGetContactByPhoneNum = (fp_GetContactByPhoneNum)GetProcAddress(m_hDll, "GetContactByPhoneNum");
	m_fpGetContactByUri = (fp_GetContactByUri)GetProcAddress(m_hDll, "GetContactByUri");
	m_fpHasContact = (fp_HasContact)GetProcAddress(m_hDll, "HasContact");
	m_fpRefreshContactByAccount = (fp_RefreshContactByAccount)GetProcAddress(m_hDll, "RefreshContactByAccount");
	m_fpRefreshContactById = (fp_RefreshContactById)GetProcAddress(m_hDll, "RefreshContactById");
	m_fpRefreshContactByUri = (fp_RefreshContactByUri)GetProcAddress(m_hDll, "RefreshContactByUri");
	m_fpRemoveContactById = (fp_RemoveContactById)GetProcAddress(m_hDll, "RemoveContactById");
	m_fpSearchContact = (fp_SearchContact)GetProcAddress(m_hDll, "SearchContact");
	m_fpModify = (fp_Modify)GetProcAddress(m_hDll, "Modify");
	m_fpGetHeadImagePath = (fp_GetHeadImagePath)GetProcAddress(m_hDll, "GetHeadImagePath");
	m_fpMoveToGroup = (fp_MoveToGroup)GetProcAddress(m_hDll, "MoveToGroup");
	m_fpAddToGroup = (fp_AddToGroup)GetProcAddress(m_hDll, "AddToGroup");
	m_fpRemoveFromGroup = (fp_RemoveFromGroup)GetProcAddress(m_hDll, "RemoveFromGroup");
	m_fpCanStartSession = (fp_CanStartSession)GetProcAddress(m_hDll, "CanStartSession");
	m_fpCanMoveToGroup = (fp_CanMoveToGroup)GetProcAddress(m_hDll, "CanMoveToGroup");
	m_fpGetCustomGroups = (fp_GetCustomGroups)GetProcAddress(m_hDll, "GetCustomGroups");
	m_fpIsFavourite = (fp_IsFavourite)GetProcAddress(m_hDll, "IsFavourite");
	m_fpAddFixedGroup = (fp_AddFixedGroup)GetProcAddress(m_hDll, "AddFixedGroup");
	m_fpGetFixedGroupByID = (fp_GetFixedGroupByID)GetProcAddress(m_hDll, "GetFixedGroupByID");
	m_fpGetFixedGroupByUri = (fp_GetFixedGroupByUri)GetProcAddress(m_hDll, "GetFixedGroupByUri");
	m_fpRemoveFixedGroup = (fp_RemoveFixedGroup)GetProcAddress(m_hDll, "RemoveFixedGroup");
	m_fpRefreshFixedGrouplist = (fp_RefreshFixedGrouplist)GetProcAddress(m_hDll, "RefreshFixedGrouplist");
	m_fpGetFixedGrouplist = (fp_GetFixedGrouplist)GetProcAddress(m_hDll, "GetFixedGrouplist");
	m_fpSearchFixedGroup = (fp_SearchFixedGroup)GetProcAddress(m_hDll, "SearchFixedGroup");
	m_fpAddCustomGroup = (fp_AddCustomGroup)GetProcAddress(m_hDll, "AddCustomGroup");
	m_fpAddFavoriteGroup = (fp_AddFavoriteGroup)GetProcAddress(m_hDll, "AddFavoriteGroup");
	m_fpGetCustomGroupById = (fp_GetCustomGroupById)GetProcAddress(m_hDll, "GetCustomGroupById");
	m_fpGetCustomGrouplist = (fp_GetCustomGrouplist)GetProcAddress(m_hDll, "GetCustomGrouplist");
	m_fpRemoveCustomGroup = (fp_RemoveCustomGroup)GetProcAddress(m_hDll, "RemoveCustomGroup");
	m_fpRemoveFavoriteGroup = (fp_RemoveFavoriteGroup)GetProcAddress(m_hDll, "RemoveFavoriteGroup");
	m_fpAddContactToFavoriteGroup = (fp_AddContactToFavoriteGroup)GetProcAddress(m_hDll, "AddContactToFavoriteGroup");
	m_fpRemoveContactFromFavoriteGroup = (fp_RemoveContactFromFavoriteGroup)GetProcAddress(m_hDll, "RemoveContactFromFavoriteGroup");
	m_fpRenameToFavoriteGroup = (fp_RenameToFavoriteGroup)GetProcAddress(m_hDll, "RenameToFavoriteGroup");
	m_fpGetContactlistFromFavoriteGroup = (fp_GetContactlistFromFavoriteGroup)GetProcAddress(m_hDll, "GetContactlistFromFavoriteGroup");
	m_fpAddContactToCustomGroup = (fp_AddContactToCustomGroup)GetProcAddress(m_hDll, "AddContactToCustomGroup");
	m_fpRemoveContactFromCustomGroup = (fp_RemoveContactFromCustomGroup)GetProcAddress(m_hDll, "RemoveContactFromCustomGroup");
	m_fpRenameToCustomGroup = (fp_RenameToCustomGroup)GetProcAddress(m_hDll, "RenameToCustomGroup");
	m_fpGetContactlistFromCustomGroup = (fp_GetContactlistFromCustomGroup)GetProcAddress(m_hDll, "GetContactlistFromCustomGroup");
	m_fpMoveUp = (fp_MoveUp)GetProcAddress(m_hDll, "MoveUp");
	m_fpMoveDown = (fp_MoveDown)GetProcAddress(m_hDll, "MoveDown");
	m_fpAddContactToFixedGroup = (fp_AddContactToFixedGroup)GetProcAddress(m_hDll, "AddContactToFixedGroup");
	m_fpRemoveContactFromFixedGroup = (fp_RemoveContactFromFixedGroup)GetProcAddress(m_hDll, "RemoveContactFromFixedGroup");
	m_fpRenameToFixedGroup = (fp_RenameToFixedGroup)GetProcAddress(m_hDll, "RenameToFixedGroup");
	m_fpGetContactlistFromFixedGroup = (fp_GetContactlistFromFixedGroup)GetProcAddress(m_hDll, "GetContactlistFromFixedGroup");
	m_fpChangeGroupInfo = (fp_ChangeGroupInfo)GetProcAddress(m_hDll, "ChangeGroupInfo");
	m_fpChangeGroupOwner = (fp_ChangeGroupOwner)GetProcAddress(m_hDll, "ChangeGroupOwner");
	m_fpRefreshContactList = (fp_RefreshContactList)GetProcAddress(m_hDll, "RefreshContactList");
	m_fpRefreshGroup = (fp_RefreshGroup)GetProcAddress(m_hDll, "RefreshGroup");
	m_fpAcceptInvitation = (fp_AcceptInvitation)GetProcAddress(m_hDll, "AcceptInvitation");
	m_fpRejectInvitation = (fp_RejectInvitation)GetProcAddress(m_hDll, "RejectInvitation");
	m_fpAcceptJoinReq = (fp_AcceptJoinReq)GetProcAddress(m_hDll, "AcceptJoinReq");
	m_fpRejectJoinReq = (fp_RejectJoinReq)GetProcAddress(m_hDll, "RejectJoinReq");
	m_fpSendIMMessage = (fp_SendIMMessage)GetProcAddress(m_hDll, "SendIMMessage");
	m_fpCloseConversation = (fp_CloseConversation)GetProcAddress(m_hDll, "CloseConversation");
	m_fpAcceptFile = (fp_AcceptFile)GetProcAddress(m_hDll, "AcceptFile");
	m_fpCancelFile = (fp_CancelFile)GetProcAddress(m_hDll, "CancelFile");
	m_fpRejectFile = (fp_RejectFile)GetProcAddress(m_hDll, "RejectFile");
	m_fpTransferFile = (fp_TransferFile)GetProcAddress(m_hDll, "TransferFile");
	m_fpMakeMeetingGroup = (fp_MakeMeetingGroup)GetProcAddress(m_hDll, "MakeMeetingGroup");
	m_fpStartMeeting = (fp_StartMeeting)GetProcAddress(m_hDll, "StartMeeting");
	m_fpAcceptMeeting = (fp_AcceptMeeting)GetProcAddress(m_hDll, "AcceptMeeting");
	m_fpAddParticipant = (fp_AddParticipant)GetProcAddress(m_hDll, "AddParticipant");
	m_fpConnectParticipant = (fp_ConnectParticipant)GetProcAddress(m_hDll, "ConnectParticipant");
	m_fpRemoveParticipant = (fp_RemoveParticipant)GetProcAddress(m_hDll, "RemoveParticipant");
	m_fpKickParticipant = (fp_KickParticipant)GetProcAddress(m_hDll, "KickParticipant");
	m_fpMuteMeeting = (fp_MuteMeeting)GetProcAddress(m_hDll, "MuteMeeting");
	m_fpUnMuteMeeting = (fp_UnMuteMeeting)GetProcAddress(m_hDll, "UnMuteMeeting");
	m_fpGetBookConfList = (fp_GetBookConfList)GetProcAddress(m_hDll, "GetBookConfList");
	m_fpJoinMeeting = (fp_JoinMeeting)GetProcAddress(m_hDll, "JoinMeeting");
	m_fpLeaveMeeting = (fp_LeaveMeeting)GetProcAddress(m_hDll, "LeaveMeeting");
	m_fpPublishSelfInformation = (fp_PublishSelfInformation)GetProcAddress(m_hDll, "PublishSelfInformation");
	m_fpGetContactStatus = (fp_GetContactStatus)GetProcAddress(m_hDll, "GetContactStatus");
	m_fpOnClientSignInNotify = (fp_OnClientSignInNotify)GetProcAddress(m_hDll, "OnClientSignInNotify");
	m_fpOnStatusChanged = (fp_OnStatusChanged)GetProcAddress(m_hDll, "OnStatusChanged");
	m_fpOnIncreContactsChanged = (fp_OnIncreContactsChanged)GetProcAddress(m_hDll, "OnIncreContactsChanged");
	m_fpOnAVSessAdded = (fp_OnAVSessAdded)GetProcAddress(m_hDll, "OnAVSessAdded");
	m_fpOnAVSessionConnected = (fp_OnAVSessionConnected)GetProcAddress(m_hDll, "OnAVSessionConnected");
	m_fpOnAVSessionClosed = (fp_OnAVSessionClosed)GetProcAddress(m_hDll, "OnAVSessionClosed");
	m_fpOnConvMemberStatusChanged = (fp_OnConvMemberStatusChanged)GetProcAddress(m_hDll, "OnConvMemberStatusChanged");
	m_fpOnConvMemAllowSpeak = (fp_OnConvMemAllowSpeak)GetProcAddress(m_hDll, "OnConvMemAllowSpeak");
	m_fpOnConvMemForbidSpeak = (fp_OnConvMemForbidSpeak)GetProcAddress(m_hDll, "OnConvMemForbidSpeak");
	m_fpOnConvMemCurSpeaker = (fp_OnConvMemCurSpeaker)GetProcAddress(m_hDll, "OnConvMemCurSpeaker");
	m_fpOnConvGroupMemberChanged = (fp_OnConvGroupMemberChanged)GetProcAddress(m_hDll, "OnConvGroupMemberChanged");
	m_fpOnReceivedIMMessage = (fp_OnReceivedIMMessage)GetProcAddress(m_hDll, "OnReceivedIMMessage");
	m_fpOnInstantSessRemoved = (fp_OnInstantSessRemoved)GetProcAddress(m_hDll, "OnInstantSessRemoved");
	m_fpOnInstantSessAdded = (fp_OnInstantSessAdded)GetProcAddress(m_hDll, "OnInstantSessAdded");
	m_fpOnSysMsgRecved = (fp_OnSysMsgRecved)GetProcAddress(m_hDll, "OnSysMsgRecved");
	m_fpOnGroupInvitation = (fp_OnGroupInvitation)GetProcAddress(m_hDll, "OnGroupInvitation");
	m_fpOnGroupInvitationRes = (fp_OnGroupInvitationRes)GetProcAddress(m_hDll, "OnGroupInvitationRes");
	m_fpOnLeaveFromFixedGroup = (fp_OnLeaveFromFixedGroup)GetProcAddress(m_hDll, "OnLeaveFromFixedGroup");
	m_fpOnJoinFixedGroupRequest = (fp_OnJoinFixedGroupRequest)GetProcAddress(m_hDll, "OnJoinFixedGroupRequest");
	m_fpOnJoinFixedGroupRes = (fp_OnJoinFixedGroupRes)GetProcAddress(m_hDll, "OnJoinFixedGroupRes");
	m_fpOnMemberAdded = (fp_OnMemberAdded)GetProcAddress(m_hDll, "OnMemberAdded");
	m_fpOnMemberRemoved = (fp_OnMemberRemoved)GetProcAddress(m_hDll, "OnMemberRemoved");
	m_fpOnMemberFlowChanged = (fp_OnMemberFlowChanged)GetProcAddress(m_hDll, "OnMemberFlowChanged");
	m_fpOnFixedGroupInfoChanged = (fp_OnFixedGroupInfoChanged)GetProcAddress(m_hDll, "OnFixedGroupInfoChanged");
	m_fpOnNewFileRercved = (fp_OnNewFileRercved)GetProcAddress(m_hDll, "OnNewFileRercved");
	m_fpOnFileAccept = (fp_OnFileAccept)GetProcAddress(m_hDll, "OnFileAccept");
	m_fpOnFileCancel = (fp_OnFileCancel)GetProcAddress(m_hDll, "OnFileCancel");
	m_fpOnFileProgress = (fp_OnFileProgress)GetProcAddress(m_hDll, "OnFileProgress");
	m_fpInit = (fp_Init)GetProcAddress(m_hDll, "Init");
	m_fpUnInit = (fp_UnInit)GetProcAddress(m_hDll, "UnInit");
	m_fpLoginByToken = (fp_LoginByToken)GetProcAddress(m_hDll, "LoginByToken");
	m_fpLoginByPasswd = (fp_LoginByPasswd)GetProcAddress(m_hDll, "LoginByPasswd");
	m_fpLogout = (fp_Logout)GetProcAddress(m_hDll, "Logout");
	m_fpConfig = (fp_Config)GetProcAddress(m_hDll, "Config");
	m_fpSetLang = (fp_SetLang)GetProcAddress(m_hDll, "SetLang");
	m_fpMakeCall = (fp_MakeCall)GetProcAddress(m_hDll, "MakeCall");
	m_fpAccept = (fp_Accept)GetProcAddress(m_hDll, "Accept");
	m_fpReject = (fp_Reject)GetProcAddress(m_hDll, "Reject");
	m_fpHangup = (fp_Hangup)GetProcAddress(m_hDll, "Hangup");
	m_fpHold = (fp_Hold)GetProcAddress(m_hDll, "Hold");
	m_fpResume = (fp_Resume)GetProcAddress(m_hDll, "Resume");
	m_fpForward = (fp_Forward)GetProcAddress(m_hDll, "Forward");
	m_fpStartRecord = (fp_StartRecord)GetProcAddress(m_hDll, "StartRecord");
	m_fpStopRecord = (fp_StopRecord)GetProcAddress(m_hDll, "StopRecord");
	m_fpMuteVoIP = (fp_MuteVoIP)GetProcAddress(m_hDll, "MuteVoIP");
	m_fpUnMuteVoIP = (fp_UnMuteVoIP)GetProcAddress(m_hDll, "UnMuteVoIP");

	return true;
}

bool UCUnitTest::FreeDll()
{
	if (NULL == m_hDll)
	{
		return false;
	}

	if (!FreeLibrary(m_hDll))
	{
		return false;
	}

	m_hDll = NULL;
	m_fpeSDKClientPlatform_Init = NULL;
	m_fpeSDKClientPlatform_Uninit = NULL;
	m_fpeSDKClientPlatform_LoginByPassword = NULL;
	m_fpeSDKClientPlatform_Logout = NULL;
	m_fpGetAllContactlist = NULL;
	m_fpGetContactByAccount = NULL;
	m_fpGetContactById = NULL;
	m_fpGetContactByPhoneNum = NULL;
	m_fpGetContactByUri = NULL;
	m_fpHasContact = NULL;
	m_fpRefreshContactByAccount = NULL;
	m_fpRefreshContactById = NULL;
	m_fpRefreshContactByUri = NULL;
	m_fpRemoveContactById = NULL;
	m_fpSearchContact = NULL;
	m_fpModify = NULL;
	m_fpGetHeadImagePath = NULL;
	m_fpMoveToGroup = NULL;
	m_fpAddToGroup = NULL;
	m_fpRemoveFromGroup = NULL;
	m_fpCanStartSession = NULL;
	m_fpCanMoveToGroup = NULL;
	m_fpGetCustomGroups = NULL;
	m_fpIsFavourite = NULL;
	m_fpAddFixedGroup = NULL;
	m_fpGetFixedGroupByID = NULL;
	m_fpGetFixedGroupByUri = NULL;
	m_fpRemoveFixedGroup = NULL;
	m_fpRefreshFixedGrouplist = NULL;
	m_fpGetFixedGrouplist = NULL;
	m_fpSearchFixedGroup = NULL;
	m_fpAddCustomGroup = NULL;
	m_fpAddFavoriteGroup = NULL;
	m_fpGetCustomGroupById = NULL;
	m_fpGetCustomGrouplist = NULL;
	m_fpRemoveCustomGroup = NULL;
	m_fpRemoveFavoriteGroup = NULL;
	m_fpAddContactToFavoriteGroup = NULL;
	m_fpRemoveContactFromFavoriteGroup = NULL;
	m_fpRenameToFavoriteGroup = NULL;
	m_fpGetContactlistFromFavoriteGroup = NULL;
	m_fpAddContactToCustomGroup = NULL;
	m_fpRemoveContactFromCustomGroup = NULL;
	m_fpRenameToCustomGroup = NULL;
	m_fpGetContactlistFromCustomGroup = NULL;
	m_fpMoveUp = NULL;
	m_fpMoveDown = NULL;
	m_fpAddContactToFixedGroup = NULL;
	m_fpRemoveContactFromFixedGroup = NULL;
	m_fpRenameToFixedGroup = NULL;
	m_fpGetContactlistFromFixedGroup = NULL;
	m_fpChangeGroupInfo = NULL;
	m_fpChangeGroupOwner = NULL;
	m_fpRefreshContactList = NULL;
	m_fpRefreshGroup = NULL;
	m_fpAcceptInvitation = NULL;
	m_fpRejectInvitation = NULL;
	m_fpAcceptJoinReq = NULL;
	m_fpRejectJoinReq = NULL;
	m_fpSendIMMessage = NULL;
	m_fpCloseConversation = NULL;
	m_fpAcceptFile = NULL;
	m_fpCancelFile = NULL;
	m_fpRejectFile = NULL;
	m_fpTransferFile = NULL;
	m_fpMakeMeetingGroup = NULL;
	m_fpStartMeeting = NULL;
	m_fpAcceptMeeting = NULL;
	m_fpAddParticipant = NULL;
	m_fpConnectParticipant = NULL;
	m_fpRemoveParticipant = NULL;
	m_fpKickParticipant = NULL;
	m_fpMuteMeeting = NULL;
	m_fpUnMuteMeeting = NULL;
	m_fpGetBookConfList = NULL;
	m_fpJoinMeeting = NULL;
	m_fpLeaveMeeting = NULL;
	m_fpPublishSelfInformation = NULL;
	m_fpGetContactStatus = NULL;
	m_fpOnClientSignInNotify = NULL;
	m_fpOnStatusChanged = NULL;
	m_fpOnIncreContactsChanged = NULL;
	m_fpOnAVSessAdded = NULL;
	m_fpOnAVSessionConnected = NULL;
	m_fpOnAVSessionClosed = NULL;
	m_fpOnConvMemberStatusChanged = NULL;
	m_fpOnConvMemAllowSpeak = NULL;
	m_fpOnConvMemForbidSpeak = NULL;
	m_fpOnConvMemCurSpeaker = NULL;
	m_fpOnConvGroupMemberChanged = NULL;
	m_fpOnReceivedIMMessage = NULL;
	m_fpOnInstantSessRemoved = NULL;
	m_fpOnInstantSessAdded = NULL;
	m_fpOnSysMsgRecved = NULL;
	m_fpOnGroupInvitation = NULL;
	m_fpOnGroupInvitationRes = NULL;
	m_fpOnLeaveFromFixedGroup = NULL;
	m_fpOnJoinFixedGroupRequest = NULL;
	m_fpOnJoinFixedGroupRes = NULL;
	m_fpOnMemberAdded = NULL;
	m_fpOnMemberRemoved = NULL;
	m_fpOnMemberFlowChanged = NULL;
	m_fpOnFixedGroupInfoChanged = NULL;
	m_fpOnNewFileRercved = NULL;
	m_fpOnFileAccept = NULL;
	m_fpOnFileCancel = NULL;
	m_fpOnFileProgress = NULL;
	m_fpInit = NULL;
	m_fpUnInit = NULL;
	m_fpLoginByToken = NULL;
	m_fpLoginByPasswd = NULL;
	m_fpLogout = NULL;
	m_fpConfig = NULL;
	m_fpSetLang = NULL;
	m_fpMakeCall = NULL;
	m_fpAccept = NULL;
	m_fpReject = NULL;
	m_fpHangup = NULL;
	m_fpHold = NULL;
	m_fpResume = NULL;
	m_fpForward = NULL;
	m_fpStartRecord = NULL;
	m_fpStopRecord = NULL;
	m_fpMuteVoIP = NULL;
	m_fpUnMuteVoIP = NULL;

	return true;
}

void UCUnitTest::SetUCSignalRecvCB()
{
	m_fpOnClientSignInNotify(UT_UCSignalRecv::OnLoginCB);
	m_fpOnStatusChanged(UT_UCSignalRecv::OnStatusCB);
	m_fpOnAVSessAdded(UT_UCSignalRecv::OnAVSessAdded);
	m_fpOnAVSessionConnected(UT_UCSignalRecv::OnAVSessConnected);
	m_fpOnAVSessionClosed(UT_UCSignalRecv::OnAVSessClosed);
	m_fpOnReceivedIMMessage(UT_UCSignalRecv::OnReceivedIM);
	m_fpOnConvMemberStatusChanged(UT_UCSignalRecv::OnConvMemberStatusChanged);
	m_fpOnConvMemAllowSpeak(UT_UCSignalRecv::OnConvMemAllowSpeak);
	m_fpOnConvMemForbidSpeak(UT_UCSignalRecv::OnConvMemForbidSpeak);
	m_fpOnConvMemCurSpeaker(UT_UCSignalRecv::OnConvMemCurSpeaker);
	m_fpOnConvGroupMemberChanged(UT_UCSignalRecv::OnConvGroupMemberChanged);
	m_fpOnInstantSessRemoved(UT_UCSignalRecv::OnInstantSessRemoved);
	m_fpOnGroupInvitation(UT_UCSignalRecv::OnGroupInvitation);
	m_fpOnGroupInvitationRes(UT_UCSignalRecv::OnGroupInvitationRes);
	m_fpOnLeaveFromFixedGroup(UT_UCSignalRecv::OnLeaveFromFixedGroup);
	m_fpOnJoinFixedGroupRequest(UT_UCSignalRecv::OnJoinFixedGroupRequest);
	m_fpOnJoinFixedGroupRes(UT_UCSignalRecv::OnJoinFixedGroupRes);
	m_fpOnMemberAdded(UT_UCSignalRecv::OnMemberAdded);
	m_fpOnMemberRemoved(UT_UCSignalRecv::OnMemberRemoved);
	m_fpOnMemberFlowChanged(UT_UCSignalRecv::OnMemberFlowChanged);
	m_fpOnFixedGroupInfoChanged(UT_UCSignalRecv::OnFixedGroupInfoChanged);
}

bool UCUnitTest::Login()
{
	int iRet = m_fpeSDKClientPlatform_LoginByPassword(m_strAcc.c_str(), m_strPwd.c_str(), 1);
	if (0 != iRet)
	{
		return false;
	}

	return true;
}

bool UCUnitTest::Logout()
{
	int iRet = m_fpeSDKClientPlatform_Logout();
	if (0 != iRet)
	{
		return false;
	}

	return true;
}