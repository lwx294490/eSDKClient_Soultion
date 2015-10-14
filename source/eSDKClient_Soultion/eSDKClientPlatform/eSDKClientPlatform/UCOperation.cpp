#include "UCContactMgr.h"
#include "UCGroup.h"
#include "UCIM.h"
#include "UCMeeting.h"
#include "UCPublic.h"
#include "UCSignalRecv.h"
#include "UCSignIn.h"
#include "UCVoIP.h"
#include "UCOperation.h"
#include "eSDKClientPlatformExecute.h"
#include "eSDKLog.h"

//UCContactMgr
#pragma comment(linker, "/EXPORT:GetAllContactlist=_GetAllContactlist@12")
#pragma comment(linker, "/EXPORT:GetContactByAccount=_GetContactByAccount@8")
#pragma comment(linker, "/EXPORT:GetContactById=_GetContactById@8")
#pragma comment(linker, "/EXPORT:GetContactByPhoneNum=_GetContactByPhoneNum@8")
#pragma comment(linker, "/EXPORT:GetContactByUri=_GetContactByUri@8")
#pragma comment(linker, "/EXPORT:HasContact=_HasContact@4")
#pragma comment(linker, "/EXPORT:RefreshContactByAccount=_RefreshContactByAccount@8")
#pragma comment(linker, "/EXPORT:RefreshContactById=_RefreshContactById@8")
#pragma comment(linker, "/EXPORT:RefreshContactByUri=_RefreshContactByUri@8")
#pragma comment(linker, "/EXPORT:RemoveContactById=_RemoveContactById@4")
#pragma comment(linker, "/EXPORT:SearchContact=_SearchContact@32")
#pragma comment(linker, "/EXPORT:Modify=_Modify@4")
#pragma comment(linker, "/EXPORT:GetHeadImagePath=_GetHeadImagePath@8")
#pragma comment(linker, "/EXPORT:MoveToGroup=_MoveToGroup@12")
#pragma comment(linker, "/EXPORT:AddToGroup=_AddToGroup@8")
#pragma comment(linker, "/EXPORT:RemoveFromGroup=_RemoveFromGroup@8")
#pragma comment(linker, "/EXPORT:CanStartSession=_CanStartSession@8")
#pragma comment(linker, "/EXPORT:CanMoveToGroup=_CanMoveToGroup@12")
#pragma comment(linker, "/EXPORT:GetCustomGroups=_GetCustomGroups@16")
#pragma comment(linker, "/EXPORT:IsFavourite=_IsFavourite@4")

//UCGroup
#pragma comment(linker, "/EXPORT:AddFixedGroup=_AddFixedGroup@4")
#pragma comment(linker, "/EXPORT:GetFixedGroupByID=_GetFixedGroupByID@8")
#pragma comment(linker, "/EXPORT:GetFixedGroupByUri=_GetFixedGroupByUri@8")
#pragma comment(linker, "/EXPORT:RemoveFixedGroup=_RemoveFixedGroup@4")
#pragma comment(linker, "/EXPORT:RefreshFixedGrouplist=_RefreshFixedGrouplist@12")
#pragma comment(linker, "/EXPORT:GetFixedGrouplist=_GetFixedGrouplist@12")
#pragma comment(linker, "/EXPORT:SearchFixedGroup=_SearchFixedGroup@20")
#pragma comment(linker, "/EXPORT:AddCustomGroup=_AddCustomGroup@4")
#pragma comment(linker, "/EXPORT:AddFavoriteGroup=_AddFavoriteGroup@4")
#pragma comment(linker, "/EXPORT:GetCustomGroupById=_GetCustomGroupById@8")
#pragma comment(linker, "/EXPORT:GetCustomGrouplist=_GetCustomGrouplist@12")
#pragma comment(linker, "/EXPORT:RemoveCustomGroup=_RemoveCustomGroup@4")
#pragma comment(linker, "/EXPORT:RemoveFavoriteGroup=_RemoveFavoriteGroup@4")
#pragma comment(linker, "/EXPORT:AddContactToFavoriteGroup=_AddContactToFavoriteGroup@8")
#pragma comment(linker, "/EXPORT:RemoveContactFromFavoriteGroup=_RemoveContactFromFavoriteGroup@8")
#pragma comment(linker, "/EXPORT:RenameToFavoriteGroup=_RenameToFavoriteGroup@8")
#pragma comment(linker, "/EXPORT:GetContactlistFromFavoriteGroup=_GetContactlistFromFavoriteGroup@16")
#pragma comment(linker, "/EXPORT:AddContactToCustomGroup=_AddContactToCustomGroup@8")
#pragma comment(linker, "/EXPORT:RemoveContactFromCustomGroup=_RemoveContactFromCustomGroup@8")
#pragma comment(linker, "/EXPORT:RenameToCustomGroup=_RenameToCustomGroup@8")
#pragma comment(linker, "/EXPORT:GetContactlistFromCustomGroup=_GetContactlistFromCustomGroup@16")
#pragma comment(linker, "/EXPORT:MoveUp=_MoveUp@4")
#pragma comment(linker, "/EXPORT:MoveDown=_MoveDown@4")
#pragma comment(linker, "/EXPORT:AddContactToFixedGroup=_AddContactToFixedGroup@8")
#pragma comment(linker, "/EXPORT:RemoveContactFromFixedGroup=_RemoveContactFromFixedGroup@8")
#pragma comment(linker, "/EXPORT:RenameToFixedGroup=_RenameToFixedGroup@8")
#pragma comment(linker, "/EXPORT:GetContactlistFromFixedGroup=_GetContactlistFromFixedGroup@16")
#pragma comment(linker, "/EXPORT:ChangeGroupInfo=_ChangeGroupInfo@4")
#pragma comment(linker, "/EXPORT:ChangeGroupOwner=_ChangeGroupOwner@8")
#pragma comment(linker, "/EXPORT:RefreshContactList=_RefreshContactList@16")
#pragma comment(linker, "/EXPORT:RefreshGroup=_RefreshGroup@4")
#pragma comment(linker, "/EXPORT:AcceptInvitation=_AcceptInvitation@4")
#pragma comment(linker, "/EXPORT:RejectInvitation=_RejectInvitation@4")
#pragma comment(linker, "/EXPORT:AcceptJoinReq=_AcceptJoinReq@8")
#pragma comment(linker, "/EXPORT:RejectJoinReq=_RejectJoinReq@8")

//UCIM
#pragma comment(linker, "/EXPORT:SendIMMessage=_SendIMMessage@12")
#pragma comment(linker, "/EXPORT:CloseConversation=_CloseConversation@4")
#pragma comment(linker, "/EXPORT:AcceptFile=_AcceptFile@8")
#pragma comment(linker, "/EXPORT:CancelFile=_CancelFile@4")
#pragma comment(linker, "/EXPORT:RejectFile=_RejectFile@4")
#pragma comment(linker, "/EXPORT:TransferFile=_TransferFile@20")

//UCMeeting
#pragma comment(linker, "/EXPORT:MakeMeetingGroup=_MakeMeetingGroup@8")
#pragma comment(linker, "/EXPORT:StartMeeting=_StartMeeting@4")
#pragma comment(linker, "/EXPORT:AcceptMeeting=_AcceptMeeting@4")
#pragma comment(linker, "/EXPORT:AddParticipant=_AddParticipant@8")
#pragma comment(linker, "/EXPORT:ConnectParticipant=_ConnectParticipant@8")
#pragma comment(linker, "/EXPORT:RemoveParticipant=_RemoveParticipant@8")
#pragma comment(linker, "/EXPORT:KickParticipant=_KickParticipant@8")
#pragma comment(linker, "/EXPORT:MuteMeeting=_MuteMeeting@8")
#pragma comment(linker, "/EXPORT:UnMuteMeeting=_UnMuteMeeting@8")
#pragma comment(linker, "/EXPORT:GetBookConfList=_GetBookConfList@12")
#pragma comment(linker, "/EXPORT:JoinMeeting=_JoinMeeting@8")
#pragma comment(linker, "/EXPORT:LeaveMeeting=_LeaveMeeting@4")

//UCPublic
#pragma comment(linker, "/EXPORT:PublishSelfInformation=_PublishSelfInformation@4")
#pragma comment(linker, "/EXPORT:GetContactStatus=_GetContactStatus@8")

//UCSignalRecv
#pragma comment(linker, "/EXPORT:OnClientSignInNotify=_OnClientSignInNotify@4")
#pragma comment(linker, "/EXPORT:OnStatusChanged=_OnStatusChanged@4")
#pragma comment(linker, "/EXPORT:OnIncreContactsChanged=_OnIncreContactsChanged@4")
#pragma comment(linker, "/EXPORT:OnAVSessAdded=_OnAVSessAdded@4")
#pragma comment(linker, "/EXPORT:OnAVSessionConnected=_OnAVSessionConnected@4")
#pragma comment(linker, "/EXPORT:OnAVSessionClosed=_OnAVSessionClosed@4")
#pragma comment(linker, "/EXPORT:OnConvMemberStatusChanged=_OnConvMemberStatusChanged@4")
#pragma comment(linker, "/EXPORT:OnConvMemAllowSpeak=_OnConvMemAllowSpeak@4")
#pragma comment(linker, "/EXPORT:OnConvMemForbidSpeak=_OnConvMemForbidSpeak@4")
#pragma comment(linker, "/EXPORT:OnConvMemCurSpeaker=_OnConvMemCurSpeaker@4")
#pragma comment(linker, "/EXPORT:OnConvGroupMemberChanged=_OnConvGroupMemberChanged@4")
#pragma comment(linker, "/EXPORT:OnReceivedIMMessage=_OnReceivedIMMessage@4")
#pragma comment(linker, "/EXPORT:OnInstantSessRemoved=_OnInstantSessRemoved@4")
#pragma comment(linker, "/EXPORT:OnInstantSessRemoved=_OnInstantSessRemoved@4")
#pragma comment(linker, "/EXPORT:OnInstantSessAdded=_OnInstantSessAdded@4")
#pragma comment(linker, "/EXPORT:OnSysMsgRecved=_OnSysMsgRecved@4")
#pragma comment(linker, "/EXPORT:OnGroupInvitation=_OnGroupInvitation@4")
#pragma comment(linker, "/EXPORT:OnGroupInvitationRes=_OnGroupInvitationRes@4")
#pragma comment(linker, "/EXPORT:OnLeaveFromFixedGroup=_OnLeaveFromFixedGroup@4")
#pragma comment(linker, "/EXPORT:OnJoinFixedGroupRequest=_OnJoinFixedGroupRequest@4")
#pragma comment(linker, "/EXPORT:OnJoinFixedGroupRes=_OnJoinFixedGroupRes@4")
#pragma comment(linker, "/EXPORT:OnMemberAdded=_OnMemberAdded@4")
#pragma comment(linker, "/EXPORT:OnMemberRemoved=_OnMemberRemoved@4")
#pragma comment(linker, "/EXPORT:OnMemberFlowChanged=_OnMemberFlowChanged@4")
#pragma comment(linker, "/EXPORT:OnFixedGroupInfoChanged=_OnFixedGroupInfoChanged@4")
#pragma comment(linker, "/EXPORT:OnNewFileRercved=_OnNewFileRercved@4")
#pragma comment(linker, "/EXPORT:OnFileAccept=_OnFileAccept@4")
#pragma comment(linker, "/EXPORT:OnFileCancel=_OnFileCancel@4")
#pragma comment(linker, "/EXPORT:OnFileProgress=_OnFileProgress@4")

//UCSignIn
#pragma comment(linker, "/EXPORT:Init=_Init@0")
#pragma comment(linker, "/EXPORT:UnInit=_UnInit@0")
#pragma comment(linker, "/EXPORT:LoginByToken=_LoginByToken@4")
#pragma comment(linker, "/EXPORT:LoginByPasswd=_LoginByPasswd@8")
#pragma comment(linker, "/EXPORT:Logout=_Logout@0")
#pragma comment(linker, "/EXPORT:Config=_Config@4")
#pragma comment(linker, "/EXPORT:SetLang=_SetLang@4")

//UCVoIP
#pragma comment(linker, "/EXPORT:MakeCall=_MakeCall@20")
#pragma comment(linker, "/EXPORT:Accept=_Accept@16")
#pragma comment(linker, "/EXPORT:Reject=_Reject@8")
#pragma comment(linker, "/EXPORT:Hangup=_Hangup@8")
#pragma comment(linker, "/EXPORT:Hold=_Hold@4")
#pragma comment(linker, "/EXPORT:Resume=_Resume@4")
#pragma comment(linker, "/EXPORT:Forward=_Forward@8")
#pragma comment(linker, "/EXPORT:StartRecord=_StartRecord@8")
#pragma comment(linker, "/EXPORT:StopRecord=_StopRecord@4")
#pragma comment(linker, "/EXPORT:MuteVoIP=_MuteVoIP@4")
#pragma comment(linker, "/EXPORT:UnMuteVoIP=_UnMuteVoIP@4")

fp_GetAllContactlist g_fpGetAllContactlist = NULL;
fp_GetContactByAccount g_fpGetContactByAccount = NULL;
fp_GetContactById g_fpGetContactById = NULL;
fp_GetContactByPhoneNum g_fpGetContactByPhoneNum = NULL;
fp_GetContactByUri g_fpGetContactByUri = NULL;
fp_HasContact g_fpHasContact = NULL;
fp_RefreshContactByAccount g_fpRefreshContactByAccount = NULL;
fp_RefreshContactById g_fpRefreshContactById = NULL;
fp_RefreshContactByUri g_fpRefreshContactByUri = NULL;
fp_RemoveContactById g_fpRemoveContactById = NULL;
fp_SearchContact g_fpSearchContact = NULL;
fp_Modify g_fpModify = NULL; 
fp_GetHeadImagePath g_fpGetHeadImagePath = NULL;
fp_MoveToGroup g_fpMoveToGroup = NULL;
fp_AddToGroup g_fpAddToGroup = NULL;
fp_RemoveFromGroup g_fpRemoveFromGroup = NULL;
fp_CanStartSession g_fpCanStartSession = NULL;
fp_CanMoveToGroup g_fpCanMoveToGroup = NULL;
fp_GetCustomGroups g_fpGetCustomGroups = NULL;
fp_IsFavourite g_fpIsFavourite = NULL;
fp_AddFixedGroup g_fpAddFixedGroup = NULL;
fp_GetFixedGroupByID g_fpGetFixedGroupByID = NULL;
fp_GetFixedGroupByUri g_fpGetFixedGroupByUri = NULL;
fp_RemoveFixedGroup g_fpRemoveFixedGroup = NULL;
fp_RefreshFixedGrouplist g_fpRefreshFixedGrouplist = NULL;
fp_GetFixedGrouplist g_fpGetFixedGrouplist = NULL;
fp_SearchFixedGroup g_fpSearchFixedGroup = NULL;
fp_AddCustomGroup g_fpAddCustomGroup = NULL;
fp_AddFavoriteGroup g_fpAddFavoriteGroup = NULL; 
fp_GetCustomGroupById g_fpGetCustomGroupById = NULL; 
fp_GetCustomGrouplist g_fpGetCustomGrouplist = NULL; 
fp_RemoveCustomGroup g_fpRemoveCustomGroup = NULL;
fp_RemoveFavoriteGroup g_fpRemoveFavoriteGroup = NULL;
fp_AddContactToFavoriteGroup g_fpAddContactToFavoriteGroup = NULL;
fp_RemoveContactFromFavoriteGroup g_fpRemoveContactFromFavoriteGroup = NULL;
fp_RenameToFavoriteGroup g_fpRenameToFavoriteGroup = NULL;
fp_GetContactlistFromFavoriteGroup g_fpGetContactlistFromFavoriteGroup = NULL;
fp_AddContactToCustomGroup g_fpAddContactToCustomGroup = NULL;
fp_RemoveContactFromCustomGroup g_fpRemoveContactFromCustomGroup = NULL;
fp_RenameToCustomGroup g_fpRenameToCustomGroup = NULL;
fp_GetContactlistFromCustomGroup g_fpGetContactlistFromCustomGroup = NULL;
fp_MoveUp g_fpMoveUp = NULL;
fp_MoveDown g_fpMoveDown = NULL;
fp_AddContactToFixedGroup g_fpAddContactToFixedGroup = NULL;
fp_RemoveContactFromFixedGroup g_fpRemoveContactFromFixedGroup = NULL; 
fp_RenameToFixedGroup g_fpRenameToFixedGroup = NULL;
fp_GetContactlistFromFixedGroup g_fpGetContactlistFromFixedGroup = NULL;
fp_ChangeGroupInfo g_fpChangeGroupInfo = NULL;
fp_ChangeGroupOwner g_fpChangeGroupOwner = NULL;
fp_RefreshContactList g_fpRefreshContactList = NULL;
fp_RefreshGroup g_fpRefreshGroup = NULL;
fp_AcceptInvitation g_fpAcceptInvitation = NULL;
fp_RejectInvitation g_fpRejectInvitation = NULL;
fp_AcceptJoinReq g_fpAcceptJoinReq = NULL;
fp_RejectJoinReq g_fpRejectJoinReq = NULL;
fp_SendIMMessage g_fpSendIMMessage = NULL;
fp_CloseConversation g_fpCloseConversation = NULL;
fp_AcceptFile g_fpAcceptFile = NULL;
fp_CancelFile g_fpCancelFile = NULL;   
fp_RejectFile g_fpRejectFile = NULL;   
fp_TransferFile g_fpTransferFile = NULL;
fp_MakeMeetingGroup g_fpMakeMeetingGroup = NULL;
fp_StartMeeting g_fpStartMeeting = NULL; 
fp_AcceptMeeting g_fpAcceptMeeting = NULL;
fp_AddParticipant g_fpAddParticipant = NULL;
fp_ConnectParticipant g_fpConnectParticipant = NULL;
fp_RemoveParticipant g_fpRemoveParticipant = NULL;
fp_KickParticipant g_fpKickParticipant = NULL;
fp_MuteMeeting g_fpMuteMeeting = NULL;
fp_UnMuteMeeting g_fpUnMuteMeeting = NULL;
fp_GetBookConfList g_fpGetBookConfList = NULL;
fp_JoinMeeting g_fpJoinMeeting = NULL;
fp_LeaveMeeting g_fpLeaveMeeting = NULL;
fp_PublishSelfInformation g_fpPublishSelfInformation = NULL;
fp_GetContactStatus g_fpGetContactStatus = NULL;
fp_OnClientSignInNotify g_fpOnClientSignInNotify = NULL;
fp_OnStatusChanged g_fpOnStatusChanged = NULL;
fp_OnIncreContactsChanged g_fpOnIncreContactsChanged = NULL;
fp_OnAVSessAdded g_fpOnAVSessAdded = NULL;
fp_OnAVSessionConnected g_fpOnAVSessionConnected = NULL;
fp_OnAVSessionClosed g_fpOnAVSessionClosed = NULL;
fp_OnConvMemberStatusChanged g_fpOnConvMemberStatusChanged = NULL;
fp_OnConvMemAllowSpeak g_fpOnConvMemAllowSpeak = NULL;
fp_OnConvMemForbidSpeak g_fpOnConvMemForbidSpeak = NULL;
fp_OnConvMemCurSpeaker g_fpOnConvMemCurSpeaker = NULL;
fp_OnConvGroupMemberChanged g_fpOnConvGroupMemberChanged = NULL;
fp_OnReceivedIMMessage g_fpOnReceivedIMMessage = NULL;
fp_OnInstantSessRemoved g_fpOnInstantSessRemoved = NULL;
fp_OnInstantSessAdded g_fpOnInstantSessAdded = NULL;
fp_OnSysMsgRecved g_fpOnSysMsgRecved = NULL;
fp_OnGroupInvitation g_fpOnGroupInvitation = NULL;
fp_OnGroupInvitationRes g_fpOnGroupInvitationRes = NULL;
fp_OnLeaveFromFixedGroup g_fpOnLeaveFromFixedGroup = NULL;
fp_OnJoinFixedGroupRequest g_fpOnJoinFixedGroupRequest = NULL;
fp_OnJoinFixedGroupRes g_fpOnJoinFixedGroupRes = NULL;
fp_OnMemberAdded g_fpOnMemberAdded = NULL; 
fp_OnMemberRemoved g_fpOnMemberRemoved = NULL;
fp_OnMemberFlowChanged g_fpOnMemberFlowChanged = NULL;
fp_OnFixedGroupInfoChanged g_fpOnFixedGroupInfoChanged = NULL;
fp_OnNewFileRercved g_fpOnNewFileRercved = NULL;
fp_OnFileAccept g_fpOnFileAccept = NULL;
fp_OnFileCancel g_fpOnFileCancel = NULL;
fp_OnFileProgress g_fpOnFileProgress = NULL;
fp_Init g_fpInit = NULL;                           
fp_UnInit g_fpUnInit = NULL;                         
fp_LoginByToken g_fpLoginByToken = NULL;  
fp_LoginByPasswd g_fpLoginByPasswd = NULL;
fp_Logout g_fpLogout = NULL;                         
fp_Config g_fpConfig = NULL;       
fp_SetLang g_fpSetLang = NULL;
fp_MakeCall g_fpMakeCall = NULL;
fp_Accept g_fpAccept = NULL;
fp_Reject g_fpReject = NULL;
fp_Hangup g_fpHangup = NULL;
fp_Hold g_fpHold = NULL;         
fp_Resume g_fpResume = NULL;       
fp_Forward g_fpForward = NULL; 
fp_StartRecord g_fpStartRecord = NULL;
fp_StopRecord g_fpStopRecord = NULL;   
fp_MuteVoIP g_fpMuteVoIP = NULL;              
fp_UnMuteVoIP g_fpUnMuteVoIP = NULL;            

//UCContactMgr
int UCSDK_CALL GetAllContactlist(int iFrom, int iTo, UCContactList* memberList)
{
	if (NULL == g_fpGetAllContactlist)
	{
		eSDKClientPlatformExecute *peSDKClient = eSDKClientPlatformExecute::Instance();
		if (NULL == peSDKClient)
		{
			ERROR_LOG() << "Get eSDKClientPlatformExecute instance failed.";
			return UC_Fail;
		}

		HINSTANCE hDllHandle = peSDKClient->getServiceHandleByName("UCSDK");
		if (NULL == hDllHandle)
		{
			ERROR_LOG() << "getServiceHandleByName failed.";
			return UC_Fail;
		}

		g_fpGetAllContactlist = (fp_GetAllContactlist)GetProcAddress(hDllHandle,"GetAllContactlist");
		if (NULL == g_fpGetAllContactlist)
		{
			ERROR_LOG() << "GetProcAddress \"GetAllContactlist\" failed.";
			return UC_Fail;
		}
	}
	
	int iRet = (*g_fpGetAllContactlist)(iFrom, iTo, memberList);
	return iRet;
}

int UCSDK_CALL GetContactByAccount(const char* pAcc, UCContact* member)
{
	if (NULL == g_fpGetContactByAccount)
	{
		eSDKClientPlatformExecute *peSDKClient = eSDKClientPlatformExecute::Instance();
		if (NULL == peSDKClient)
		{
			ERROR_LOG() << "Get eSDKClientPlatformExecute instance failed.";
			return UC_Fail;
		}

		HINSTANCE hDllHandle = peSDKClient->getServiceHandleByName("UCSDK");
		if (NULL == hDllHandle)
		{
			ERROR_LOG() << "getServiceHandleByName failed.";
			return UC_Fail;
		}

		g_fpGetContactByAccount = (fp_GetContactByAccount)GetProcAddress(hDllHandle,"GetContactByAccount");
		if (NULL == g_fpGetContactByAccount)
		{
			ERROR_LOG() << "GetProcAddress \"GetContactByAccount\" failed.";
			return UC_Fail;
		}
	}

	int iRet = (*g_fpGetContactByAccount)(pAcc, member);
	return iRet;

}

int UCSDK_CALL GetContactById(const char* pId, UCContact* member)
{
	if (NULL == g_fpGetContactById)
	{
		eSDKClientPlatformExecute *peSDKClient = eSDKClientPlatformExecute::Instance();
		if (NULL == peSDKClient)
		{
			ERROR_LOG() << "Get eSDKClientPlatformExecute instance failed.";
			return UC_Fail;
		}

		HINSTANCE hDllHandle = peSDKClient->getServiceHandleByName("UCSDK");
		if (NULL == hDllHandle)
		{
			ERROR_LOG() << "getServiceHandleByName failed.";
			return UC_Fail;
		}

		g_fpGetContactById = (fp_GetContactById)GetProcAddress(hDllHandle,"GetContactById");
		if (NULL == g_fpGetContactById)
		{
			ERROR_LOG() << "GetProcAddress \"GetContactById\" failed.";
			return UC_Fail;
		}
	}

	int iRet = (*g_fpGetContactById)(pId, member);
	return iRet;

}

int UCSDK_CALL GetContactByPhoneNum(const char* pPhoneNum, UCContact* member)
{
	if (NULL == g_fpGetContactByPhoneNum)
	{
		eSDKClientPlatformExecute *peSDKClient = eSDKClientPlatformExecute::Instance();
		if (NULL == peSDKClient)
		{
			ERROR_LOG() << "Get eSDKClientPlatformExecute instance failed.";
			return UC_Fail;
		}

		HINSTANCE hDllHandle = peSDKClient->getServiceHandleByName("UCSDK");
		if (NULL == hDllHandle)
		{
			ERROR_LOG() << "getServiceHandleByName failed.";
			return UC_Fail;
		}

		g_fpGetContactByPhoneNum = (fp_GetContactByPhoneNum)GetProcAddress(hDllHandle,"GetContactByPhoneNum");
		if (NULL == g_fpGetContactByPhoneNum)
		{
			ERROR_LOG() << "GetProcAddress \"GetContactByPhoneNum\" failed.";
			return UC_Fail;
		}
	}

	int iRet = (*g_fpGetContactByPhoneNum)(pPhoneNum, member);
	return iRet;

}

int UCSDK_CALL GetContactByUri(const char* pUri, UCContact* member)
{
	if (NULL == g_fpGetContactByUri)
	{
		eSDKClientPlatformExecute *peSDKClient = eSDKClientPlatformExecute::Instance();
		if (NULL == peSDKClient)
		{
			ERROR_LOG() << "Get eSDKClientPlatformExecute instance failed.";
			return UC_Fail;
		}

		HINSTANCE hDllHandle = peSDKClient->getServiceHandleByName("UCSDK");
		if (NULL == hDllHandle)
		{
			ERROR_LOG() << "getServiceHandleByName failed.";
			return UC_Fail;
		}

		g_fpGetContactByUri = (fp_GetContactByUri)GetProcAddress(hDllHandle,"GetContactByUri");
		if (NULL == g_fpGetContactByUri)
		{
			ERROR_LOG() << "GetProcAddress \"GetContactByUri\" failed.";
			return UC_Fail;
		}
	}

	int iRet = (*g_fpGetContactByUri)(pUri, member);
	return iRet;

}

int UCSDK_CALL HasContact(const char* pUri)
{
	if (NULL == g_fpHasContact)
	{
		eSDKClientPlatformExecute *peSDKClient = eSDKClientPlatformExecute::Instance();
		if (NULL == peSDKClient)
		{
			ERROR_LOG() << "Get eSDKClientPlatformExecute instance failed.";
			return false;
		}

		HINSTANCE hDllHandle = peSDKClient->getServiceHandleByName("UCSDK");
		if (NULL == hDllHandle)
		{
			ERROR_LOG() << "getServiceHandleByName failed.";
			return false;
		}

		g_fpHasContact = (fp_HasContact)GetProcAddress(hDllHandle,"HasContact");
		if (NULL == g_fpHasContact)
		{
			ERROR_LOG() << "GetProcAddress \"HasContact\" failed.";
			return false;
		}
	}

	int iRet = (*g_fpHasContact)(pUri);
	return iRet;

}

int UCSDK_CALL RefreshContactByAccount(const char* pAcc, UCContact* member)
{
	if (NULL == g_fpRefreshContactByAccount)
	{
		eSDKClientPlatformExecute *peSDKClient = eSDKClientPlatformExecute::Instance();
		if (NULL == peSDKClient)
		{
			ERROR_LOG() << "Get eSDKClientPlatformExecute instance failed.";
			return UC_Fail;
		}

		HINSTANCE hDllHandle = peSDKClient->getServiceHandleByName("UCSDK");
		if (NULL == hDllHandle)
		{
			ERROR_LOG() << "getServiceHandleByName failed.";
			return UC_Fail;
		}

		g_fpRefreshContactByAccount = (fp_RefreshContactByAccount)GetProcAddress(hDllHandle,"RefreshContactByAccount");
		if (NULL == g_fpRefreshContactByAccount)
		{
			ERROR_LOG() << "GetProcAddress \"RefreshContactByAccount\" failed.";
			return UC_Fail;
		}
	}

	int iRet = (*g_fpRefreshContactByAccount)(pAcc, member);
	return iRet;

}

int UCSDK_CALL RefreshContactById(const char* pId, UCContact* member)
{
	if (NULL == g_fpRefreshContactById)
	{
		eSDKClientPlatformExecute *peSDKClient = eSDKClientPlatformExecute::Instance();
		if (NULL == peSDKClient)
		{
			ERROR_LOG() << "Get eSDKClientPlatformExecute instance failed.";
			return UC_Fail;
		}

		HINSTANCE hDllHandle = peSDKClient->getServiceHandleByName("UCSDK");
		if (NULL == hDllHandle)
		{
			ERROR_LOG() << "getServiceHandleByName failed.";
			return UC_Fail;
		}

		g_fpRefreshContactById = (fp_RefreshContactById)GetProcAddress(hDllHandle,"RefreshContactById");
		if (NULL == g_fpRefreshContactById)
		{
			ERROR_LOG() << "GetProcAddress \"RefreshContactById\" failed.";
			return UC_Fail;
		}
	}

	int iRet = (*g_fpRefreshContactById)(pId, member);
	return iRet;

}

int UCSDK_CALL RefreshContactByUri(const char* pUri, UCContact* member)
{
	if (NULL == g_fpRefreshContactByUri)
	{
		eSDKClientPlatformExecute *peSDKClient = eSDKClientPlatformExecute::Instance();
		if (NULL == peSDKClient)
		{
			ERROR_LOG() << "Get eSDKClientPlatformExecute instance failed.";
			return UC_Fail;
		}

		HINSTANCE hDllHandle = peSDKClient->getServiceHandleByName("UCSDK");
		if (NULL == hDllHandle)
		{
			ERROR_LOG() << "getServiceHandleByName failed.";
			return UC_Fail;
		}

		g_fpRefreshContactByUri = (fp_RefreshContactByUri)GetProcAddress(hDllHandle,"RefreshContactByUri");
		if (NULL == g_fpRefreshContactByUri)
		{
			ERROR_LOG() << "GetProcAddress \"RefreshContactByUri\" failed.";
			return UC_Fail;
		}
	}

	int iRet = (*g_fpRefreshContactByUri)(pUri, member);
	return iRet;

}

int UCSDK_CALL RemoveContactById(const char* pId)
{
	if (NULL == g_fpRemoveContactById)
	{
		eSDKClientPlatformExecute *peSDKClient = eSDKClientPlatformExecute::Instance();
		if (NULL == peSDKClient)
		{
			ERROR_LOG() << "Get eSDKClientPlatformExecute instance failed.";
			return UC_Fail;
		}

		HINSTANCE hDllHandle = peSDKClient->getServiceHandleByName("UCSDK");
		if (NULL == hDllHandle)
		{
			ERROR_LOG() << "getServiceHandleByName failed.";
			return UC_Fail;
		}

		g_fpRemoveContactById = (fp_RemoveContactById)GetProcAddress(hDllHandle,"RemoveContactById");
		if (NULL == g_fpRemoveContactById)
		{
			ERROR_LOG() << "GetProcAddress \"RemoveContactById\" failed.";
			return UC_Fail;
		}
	}

	int iRet = (*g_fpRemoveContactById)(pId);
	return iRet;

}

int UCSDK_CALL SearchContact(const char* condition, const char* deptid,
							 int querysubdept, int offset, int count, int ordertype,
							 int* recamount, UCContactList* memberList)
{
	if (NULL == g_fpSearchContact)
	{
		eSDKClientPlatformExecute *peSDKClient = eSDKClientPlatformExecute::Instance();
		if (NULL == peSDKClient)
		{
			ERROR_LOG() << "Get eSDKClientPlatformExecute instance failed.";
			return UC_Fail;
		}

		HINSTANCE hDllHandle = peSDKClient->getServiceHandleByName("UCSDK");
		if (NULL == hDllHandle)
		{
			ERROR_LOG() << "getServiceHandleByName failed.";
			return UC_Fail;
		}

		g_fpSearchContact = (fp_SearchContact)GetProcAddress(hDllHandle,"SearchContact");
		if (NULL == g_fpSearchContact)
		{
			ERROR_LOG() << "GetProcAddress \"SearchContact\" failed.";
			return UC_Fail;
		}
	}

	int iRet = (*g_fpSearchContact)(condition, deptid, querysubdept, offset, count, ordertype, recamount, memberList);
	return iRet;

}

int UCSDK_CALL Modify(const UCContact* member)
{
	if (NULL == g_fpModify)
	{
		eSDKClientPlatformExecute *peSDKClient = eSDKClientPlatformExecute::Instance();
		if (NULL == peSDKClient)
		{
			ERROR_LOG() << "Get eSDKClientPlatformExecute instance failed.";
			return false;
		}

		HINSTANCE hDllHandle = peSDKClient->getServiceHandleByName("UCSDK");
		if (NULL == hDllHandle)
		{
			ERROR_LOG() << "getServiceHandleByName failed.";
			return false;
		}

		g_fpModify = (fp_Modify)GetProcAddress(hDllHandle,"Modify");
		if (NULL == g_fpModify)
		{
			ERROR_LOG() << "GetProcAddress \"Modify\" failed.";
			return false;
		}
	}

	int iRet = (*g_fpModify)(member);
	return iRet;

}

int UCSDK_CALL GetHeadImagePath(const UCContact* member, char path[IMAGE_LENGTH])
{
	if (NULL == g_fpGetHeadImagePath)
	{
		eSDKClientPlatformExecute *peSDKClient = eSDKClientPlatformExecute::Instance();
		if (NULL == peSDKClient)
		{
			ERROR_LOG() << "Get eSDKClientPlatformExecute instance failed.";
			return UC_Fail;
		}

		HINSTANCE hDllHandle = peSDKClient->getServiceHandleByName("UCSDK");
		if (NULL == hDllHandle)
		{
			ERROR_LOG() << "getServiceHandleByName failed.";
			return UC_Fail;
		}

		g_fpGetHeadImagePath = (fp_GetHeadImagePath)GetProcAddress(hDllHandle,"GetHeadImagePath");
		if (NULL == g_fpGetHeadImagePath)
		{
			ERROR_LOG() << "GetProcAddress \"GetHeadImagePath\" failed.";
			return UC_Fail;
		}
	}

	int iRet = (*g_fpGetHeadImagePath)(member, path);
	return iRet;

}

int UCSDK_CALL MoveToGroup(const UCContact* member, const UCGroup* _src, const UCGroup* _target)
{
	if (NULL == g_fpMoveToGroup)
	{
		eSDKClientPlatformExecute *peSDKClient = eSDKClientPlatformExecute::Instance();
		if (NULL == peSDKClient)
		{
			ERROR_LOG() << "Get eSDKClientPlatformExecute instance failed.";
			return UC_Fail;
		}

		HINSTANCE hDllHandle = peSDKClient->getServiceHandleByName("UCSDK");
		if (NULL == hDllHandle)
		{
			ERROR_LOG() << "getServiceHandleByName failed.";
			return UC_Fail;
		}

		g_fpMoveToGroup = (fp_MoveToGroup)GetProcAddress(hDllHandle,"MoveToGroup");
		if (NULL == g_fpMoveToGroup)
		{
			ERROR_LOG() << "GetProcAddress \"MoveToGroup\" failed.";
			return UC_Fail;
		}
	}

	int iRet = (*g_fpMoveToGroup)(member, _src, _target);
	return iRet;

}

int UCSDK_CALL AddToGroup(const UCContact* member, const UCGroup* _target)
{
	if (NULL == g_fpAddToGroup)
	{
		eSDKClientPlatformExecute *peSDKClient = eSDKClientPlatformExecute::Instance();
		if (NULL == peSDKClient)
		{
			ERROR_LOG() << "Get eSDKClientPlatformExecute instance failed.";
			return UC_Fail;
		}

		HINSTANCE hDllHandle = peSDKClient->getServiceHandleByName("UCSDK");
		if (NULL == hDllHandle)
		{
			ERROR_LOG() << "getServiceHandleByName failed.";
			return UC_Fail;
		}

		g_fpAddToGroup = (fp_AddToGroup)GetProcAddress(hDllHandle,"AddToGroup");
		if (NULL == g_fpAddToGroup)
		{
			ERROR_LOG() << "GetProcAddress \"AddToGroup\" failed.";
			return UC_Fail;
		}
	}

	int iRet = (*g_fpAddToGroup)(member, _target);
	return iRet;

}

int UCSDK_CALL RemoveFromGroup(const UCContact* member, const UCGroup* _target)
{
	if (NULL == g_fpRemoveFromGroup)
	{
		eSDKClientPlatformExecute *peSDKClient = eSDKClientPlatformExecute::Instance();
		if (NULL == peSDKClient)
		{
			ERROR_LOG() << "Get eSDKClientPlatformExecute instance failed.";
			return UC_Fail;
		}

		HINSTANCE hDllHandle = peSDKClient->getServiceHandleByName("UCSDK");
		if (NULL == hDllHandle)
		{
			ERROR_LOG() << "getServiceHandleByName failed.";
			return UC_Fail;
		}

		g_fpRemoveFromGroup = (fp_RemoveFromGroup)GetProcAddress(hDllHandle,"RemoveFromGroup");
		if (NULL == g_fpRemoveFromGroup)
		{
			ERROR_LOG() << "GetProcAddress \"RemoveFromGroup\" failed.";
			return UC_Fail;
		}
	}

	int iRet = (*g_fpRemoveFromGroup)(member, _target);
	return iRet;

}

int UCSDK_CALL CanStartSession(const UCContact* member, int _type)
{
	if (NULL == g_fpCanStartSession)
	{
		eSDKClientPlatformExecute *peSDKClient = eSDKClientPlatformExecute::Instance();
		if (NULL == peSDKClient)
		{
			ERROR_LOG() << "Get eSDKClientPlatformExecute instance failed.";
			return false;
		}

		HINSTANCE hDllHandle = peSDKClient->getServiceHandleByName("UCSDK");
		if (NULL == hDllHandle)
		{
			ERROR_LOG() << "getServiceHandleByName failed.";
			return false;
		}

		g_fpCanStartSession = (fp_CanStartSession)GetProcAddress(hDllHandle,"CanStartSession");
		if (NULL == g_fpCanStartSession)
		{
			ERROR_LOG() << "GetProcAddress \"CanStartSession\" failed.";
			return false;
		}
	}

	int iRet = (*g_fpCanStartSession)(member, _type);
	return iRet;

}

int UCSDK_CALL CanMoveToGroup(const UCContact* member, const UCGroup* _src, const UCGroup* _target)
{
	if (NULL == g_fpCanMoveToGroup)
	{
		eSDKClientPlatformExecute *peSDKClient = eSDKClientPlatformExecute::Instance();
		if (NULL == peSDKClient)
		{
			ERROR_LOG() << "Get eSDKClientPlatformExecute instance failed.";
			return false;
		}

		HINSTANCE hDllHandle = peSDKClient->getServiceHandleByName("UCSDK");
		if (NULL == hDllHandle)
		{
			ERROR_LOG() << "getServiceHandleByName failed.";
			return false;
		}

		g_fpCanMoveToGroup = (fp_CanMoveToGroup)GetProcAddress(hDllHandle,"CanMoveToGroup");
		if (NULL == g_fpCanMoveToGroup)
		{
			ERROR_LOG() << "GetProcAddress \"CanMoveToGroup\" failed.";
			return false;
		}
	}

	int iRet = (*g_fpCanMoveToGroup)(member, _src, _target);
	return iRet;

}

int UCSDK_CALL GetCustomGroups(const UCContact* member, int iFrom, int iTo, UCCustomGroupList* _groups)
{
	if (NULL == g_fpGetCustomGroups)
	{
		eSDKClientPlatformExecute *peSDKClient = eSDKClientPlatformExecute::Instance();
		if (NULL == peSDKClient)
		{
			ERROR_LOG() << "Get eSDKClientPlatformExecute instance failed.";
			return UC_Fail;
		}

		HINSTANCE hDllHandle = peSDKClient->getServiceHandleByName("UCSDK");
		if (NULL == hDllHandle)
		{
			ERROR_LOG() << "getServiceHandleByName failed.";
			return UC_Fail;
		}

		g_fpGetCustomGroups = (fp_GetCustomGroups)GetProcAddress(hDllHandle,"GetCustomGroups");
		if (NULL == g_fpGetCustomGroups)
		{
			ERROR_LOG() << "GetProcAddress \"GetCustomGroups\" failed.";
			return UC_Fail;
		}
	}

	int iRet = (*g_fpGetCustomGroups)(member, iFrom, iTo, _groups);
	return iRet;

}

int UCSDK_CALL IsFavourite(const UCContact* member)
{
	if (NULL == g_fpIsFavourite)
	{
		eSDKClientPlatformExecute *peSDKClient = eSDKClientPlatformExecute::Instance();
		if (NULL == peSDKClient)
		{
			ERROR_LOG() << "Get eSDKClientPlatformExecute instance failed.";
			return false;
		}

		HINSTANCE hDllHandle = peSDKClient->getServiceHandleByName("UCSDK");
		if (NULL == hDllHandle)
		{
			ERROR_LOG() << "getServiceHandleByName failed.";
			return false;
		}

		g_fpIsFavourite = (fp_IsFavourite)GetProcAddress(hDllHandle,"IsFavourite");
		if (NULL == g_fpIsFavourite)
		{
			ERROR_LOG() << "GetProcAddress \"IsFavourite\" failed.";
			return false;
		}
	}

	int iRet = (*g_fpIsFavourite)(member);
	return iRet;

}

int UCSDK_CALL AddFixedGroup(UCFixedGroup* group)
{
	if (NULL == g_fpAddFixedGroup)
	{
		eSDKClientPlatformExecute *peSDKClient = eSDKClientPlatformExecute::Instance();
		if (NULL == peSDKClient)
		{
			ERROR_LOG() << "Get eSDKClientPlatformExecute instance failed.";
			return UC_Fail;
		}

		HINSTANCE hDllHandle = peSDKClient->getServiceHandleByName("UCSDK");
		if (NULL == hDllHandle)
		{
			ERROR_LOG() << "getServiceHandleByName failed.";
			return UC_Fail;
		}

		g_fpAddFixedGroup = (fp_AddFixedGroup)GetProcAddress(hDllHandle,"AddFixedGroup");
		if (NULL == g_fpAddFixedGroup)
		{
			ERROR_LOG() << "GetProcAddress \"AddFixedGroup\" failed.";
			return UC_Fail;
		}
	}

	int iRet = (*g_fpAddFixedGroup)(group);
	return iRet;

}

int UCSDK_CALL GetFixedGroupByID(const char* pGId, UCFixedGroup* group)
{
	if (NULL == g_fpGetFixedGroupByID)
	{
		eSDKClientPlatformExecute *peSDKClient = eSDKClientPlatformExecute::Instance();
		if (NULL == peSDKClient)
		{
			ERROR_LOG() << "Get eSDKClientPlatformExecute instance failed.";
			return UC_Fail;
		}

		HINSTANCE hDllHandle = peSDKClient->getServiceHandleByName("UCSDK");
		if (NULL == hDllHandle)
		{
			ERROR_LOG() << "getServiceHandleByName failed.";
			return UC_Fail;
		}

		g_fpGetFixedGroupByID = (fp_GetFixedGroupByID)GetProcAddress(hDllHandle,"GetFixedGroupByID");
		if (NULL == g_fpGetFixedGroupByID)
		{
			ERROR_LOG() << "GetProcAddress \"GetFixedGroupByID\" failed.";
			return UC_Fail;
		}
	}

	int iRet = (*g_fpGetFixedGroupByID)(pGId, group);
	return iRet;

}

int UCSDK_CALL GetFixedGroupByUri(const char* pGUri, UCFixedGroup* group)
{
	if (NULL == g_fpGetFixedGroupByUri)
	{
		eSDKClientPlatformExecute *peSDKClient = eSDKClientPlatformExecute::Instance();
		if (NULL == peSDKClient)
		{
			ERROR_LOG() << "Get eSDKClientPlatformExecute instance failed.";
			return UC_Fail;
		}

		HINSTANCE hDllHandle = peSDKClient->getServiceHandleByName("UCSDK");
		if (NULL == hDllHandle)
		{
			ERROR_LOG() << "getServiceHandleByName failed.";
			return UC_Fail;
		}

		g_fpGetFixedGroupByUri = (fp_GetFixedGroupByUri)GetProcAddress(hDllHandle,"GetFixedGroupByUri");
		if (NULL == g_fpGetFixedGroupByUri)
		{
			ERROR_LOG() << "GetProcAddress \"GetFixedGroupByUri\" failed.";
			return UC_Fail;
		}
	}

	int iRet = (*g_fpGetFixedGroupByUri)(pGUri, group);
	return iRet;

}

int UCSDK_CALL RemoveFixedGroup(const UCFixedGroup* group)
{
	if (NULL == g_fpRemoveFixedGroup)
	{
		eSDKClientPlatformExecute *peSDKClient = eSDKClientPlatformExecute::Instance();
		if (NULL == peSDKClient)
		{
			ERROR_LOG() << "Get eSDKClientPlatformExecute instance failed.";
			return UC_Fail;
		}

		HINSTANCE hDllHandle = peSDKClient->getServiceHandleByName("UCSDK");
		if (NULL == hDllHandle)
		{
			ERROR_LOG() << "getServiceHandleByName failed.";
			return UC_Fail;
		}

		g_fpRemoveFixedGroup = (fp_RemoveFixedGroup)GetProcAddress(hDllHandle,"RemoveFixedGroup");
		if (NULL == g_fpRemoveFixedGroup)
		{
			ERROR_LOG() << "GetProcAddress \"RemoveFixedGroup\" failed.";
			return UC_Fail;
		}
	}

	int iRet = (*g_fpRemoveFixedGroup)(group);
	return iRet;

}

int UCSDK_CALL RefreshFixedGrouplist(int iFrom, int iTo, UCFixedGroupList* groupList)
{
	if (NULL == g_fpRefreshFixedGrouplist)
	{
		eSDKClientPlatformExecute *peSDKClient = eSDKClientPlatformExecute::Instance();
		if (NULL == peSDKClient)
		{
			ERROR_LOG() << "Get eSDKClientPlatformExecute instance failed.";
			return UC_Fail;
		}

		HINSTANCE hDllHandle = peSDKClient->getServiceHandleByName("UCSDK");
		if (NULL == hDllHandle)
		{
			ERROR_LOG() << "getServiceHandleByName failed.";
			return UC_Fail;
		}

		g_fpRefreshFixedGrouplist = (fp_RefreshFixedGrouplist)GetProcAddress(hDllHandle,"RefreshFixedGrouplist");
		if (NULL == g_fpRefreshFixedGrouplist)
		{
			ERROR_LOG() << "GetProcAddress \"RefreshFixedGrouplist\" failed.";
			return UC_Fail;
		}
	}

	int iRet = (*g_fpRefreshFixedGrouplist)(iFrom, iTo, groupList);
	return iRet;

}

int UCSDK_CALL GetFixedGrouplist(int iFrom, int iTo, UCFixedGroupList* groupList)
{
	if (NULL == g_fpGetFixedGrouplist)
	{
		eSDKClientPlatformExecute *peSDKClient = eSDKClientPlatformExecute::Instance();
		if (NULL == peSDKClient)
		{
			ERROR_LOG() << "Get eSDKClientPlatformExecute instance failed.";
			return UC_Fail;
		}

		HINSTANCE hDllHandle = peSDKClient->getServiceHandleByName("UCSDK");
		if (NULL == hDllHandle)
		{
			ERROR_LOG() << "getServiceHandleByName failed.";
			return UC_Fail;
		}

		g_fpGetFixedGrouplist = (fp_GetFixedGrouplist)GetProcAddress(hDllHandle,"GetFixedGrouplist");
		if (NULL == g_fpGetFixedGrouplist)
		{
			ERROR_LOG() << "GetProcAddress \"GetFixedGrouplist\" failed.";
			return UC_Fail;
		}
	}

	int iRet = (*g_fpGetFixedGrouplist)(iFrom, iTo, groupList);
	return iRet;

}

int UCSDK_CALL SearchFixedGroup(const char* groupNo, const char* groupName,
								int offset, int count, UCFixedGroupList* groupList)
{
	if (NULL == g_fpSearchFixedGroup)
	{
		eSDKClientPlatformExecute *peSDKClient = eSDKClientPlatformExecute::Instance();
		if (NULL == peSDKClient)
		{
			ERROR_LOG() << "Get eSDKClientPlatformExecute instance failed.";
			return UC_Fail;
		}

		HINSTANCE hDllHandle = peSDKClient->getServiceHandleByName("UCSDK");
		if (NULL == hDllHandle)
		{
			ERROR_LOG() << "getServiceHandleByName failed.";
			return UC_Fail;
		}

		g_fpSearchFixedGroup = (fp_SearchFixedGroup)GetProcAddress(hDllHandle,"SearchFixedGroup");
		if (NULL == g_fpSearchFixedGroup)
		{
			ERROR_LOG() << "GetProcAddress \"SearchFixedGroup\" failed.";
			return UC_Fail;
		}
	}

	int iRet = (*g_fpSearchFixedGroup)(groupNo, groupName, offset, count, groupList);
	return iRet;

}

int UCSDK_CALL AddCustomGroup(UCCustomGroup* group)
{
	if (NULL == g_fpAddCustomGroup)
	{
		eSDKClientPlatformExecute *peSDKClient = eSDKClientPlatformExecute::Instance();
		if (NULL == peSDKClient)
		{
			ERROR_LOG() << "Get eSDKClientPlatformExecute instance failed.";
			return UC_Fail;
		}

		HINSTANCE hDllHandle = peSDKClient->getServiceHandleByName("UCSDK");
		if (NULL == hDllHandle)
		{
			ERROR_LOG() << "getServiceHandleByName failed.";
			return UC_Fail;
		}

		g_fpAddCustomGroup = (fp_AddCustomGroup)GetProcAddress(hDllHandle,"AddCustomGroup");
		if (NULL == g_fpAddCustomGroup)
		{
			ERROR_LOG() << "GetProcAddress \"AddCustomGroup\" failed.";
			return UC_Fail;
		}
	}

	int iRet = (*g_fpAddCustomGroup)(group);
	return iRet;

}

int UCSDK_CALL AddFavoriteGroup(UCFavoriteGroup* group)
{
	if (NULL == g_fpAddFavoriteGroup)
	{
		eSDKClientPlatformExecute *peSDKClient = eSDKClientPlatformExecute::Instance();
		if (NULL == peSDKClient)
		{
			ERROR_LOG() << "Get eSDKClientPlatformExecute instance failed.";
			return UC_Fail;
		}

		HINSTANCE hDllHandle = peSDKClient->getServiceHandleByName("UCSDK");
		if (NULL == hDllHandle)
		{
			ERROR_LOG() << "getServiceHandleByName failed.";
			return UC_Fail;
		}

		g_fpAddFavoriteGroup = (fp_AddFavoriteGroup)GetProcAddress(hDllHandle,"AddFavoriteGroup");
		if (NULL == g_fpAddFavoriteGroup)
		{
			ERROR_LOG() << "GetProcAddress \"AddFavoriteGroup\" failed.";
			return UC_Fail;
		}
	}

	int iRet = (*g_fpAddFavoriteGroup)(group);
	return iRet;

}

int UCSDK_CALL GetCustomGroupById(const char* pGId, UCCustomGroup* group)
{
	if (NULL == g_fpGetCustomGroupById)
	{
		eSDKClientPlatformExecute *peSDKClient = eSDKClientPlatformExecute::Instance();
		if (NULL == peSDKClient)
		{
			ERROR_LOG() << "Get eSDKClientPlatformExecute instance failed.";
			return UC_Fail;
		}

		HINSTANCE hDllHandle = peSDKClient->getServiceHandleByName("UCSDK");
		if (NULL == hDllHandle)
		{
			ERROR_LOG() << "getServiceHandleByName failed.";
			return UC_Fail;
		}

		g_fpGetCustomGroupById = (fp_GetCustomGroupById)GetProcAddress(hDllHandle,"GetCustomGroupById");
		if (NULL == g_fpGetCustomGroupById)
		{
			ERROR_LOG() << "GetProcAddress \"GetCustomGroupById\" failed.";
			return UC_Fail;
		}
	}

	int iRet = (*g_fpGetCustomGroupById)(pGId, group);
	return iRet;

}

int UCSDK_CALL GetCustomGrouplist(int iFrom, int iTo, UCCustomGroupList* groupList)
{
	if (NULL == g_fpGetCustomGrouplist)
	{
		eSDKClientPlatformExecute *peSDKClient = eSDKClientPlatformExecute::Instance();
		if (NULL == peSDKClient)
		{
			ERROR_LOG() << "Get eSDKClientPlatformExecute instance failed.";
			return UC_Fail;
		}

		HINSTANCE hDllHandle = peSDKClient->getServiceHandleByName("UCSDK");
		if (NULL == hDllHandle)
		{
			ERROR_LOG() << "getServiceHandleByName failed.";
			return UC_Fail;
		}

		g_fpGetCustomGrouplist = (fp_GetCustomGrouplist)GetProcAddress(hDllHandle,"GetCustomGrouplist");
		if (NULL == g_fpGetCustomGrouplist)
		{
			ERROR_LOG() << "GetProcAddress \"GetCustomGrouplist\" failed.";
			return UC_Fail;
		}
	}

	int iRet = (*g_fpGetCustomGrouplist)(iFrom, iTo, groupList);
	return iRet;

}

int UCSDK_CALL RemoveCustomGroup(const UCCustomGroup* group)
{
	if (NULL == g_fpRemoveCustomGroup)
	{
		eSDKClientPlatformExecute *peSDKClient = eSDKClientPlatformExecute::Instance();
		if (NULL == peSDKClient)
		{
			ERROR_LOG() << "Get eSDKClientPlatformExecute instance failed.";
			return UC_Fail;
		}

		HINSTANCE hDllHandle = peSDKClient->getServiceHandleByName("UCSDK");
		if (NULL == hDllHandle)
		{
			ERROR_LOG() << "getServiceHandleByName failed.";
			return UC_Fail;
		}

		g_fpRemoveCustomGroup = (fp_RemoveCustomGroup)GetProcAddress(hDllHandle,"RemoveCustomGroup");
		if (NULL == g_fpRemoveCustomGroup)
		{
			ERROR_LOG() << "GetProcAddress \"RemoveCustomGroup\" failed.";
			return UC_Fail;
		}
	}

	int iRet = (*g_fpRemoveCustomGroup)(group);
	return iRet;

}

int UCSDK_CALL RemoveFavoriteGroup(const UCFavoriteGroup* group)
{
	if (NULL == g_fpRemoveFavoriteGroup)
	{
		eSDKClientPlatformExecute *peSDKClient = eSDKClientPlatformExecute::Instance();
		if (NULL == peSDKClient)
		{
			ERROR_LOG() << "Get eSDKClientPlatformExecute instance failed.";
			return UC_Fail;
		}

		HINSTANCE hDllHandle = peSDKClient->getServiceHandleByName("UCSDK");
		if (NULL == hDllHandle)
		{
			ERROR_LOG() << "getServiceHandleByName failed.";
			return UC_Fail;
		}

		g_fpRemoveFavoriteGroup = (fp_RemoveFavoriteGroup)GetProcAddress(hDllHandle,"RemoveFavoriteGroup");
		if (NULL == g_fpRemoveFavoriteGroup)
		{
			ERROR_LOG() << "GetProcAddress \"RemoveFavoriteGroup\" failed.";
			return UC_Fail;
		}
	}

	int iRet = (*g_fpRemoveFavoriteGroup)(group);
	return iRet;

}

int UCSDK_CALL AddContactToFavoriteGroup(const UCFavoriteGroup* group, UCContact* _contact)
{
	if (NULL == g_fpAddContactToFavoriteGroup)
	{
		eSDKClientPlatformExecute *peSDKClient = eSDKClientPlatformExecute::Instance();
		if (NULL == peSDKClient)
		{
			ERROR_LOG() << "Get eSDKClientPlatformExecute instance failed.";
			return UC_Fail;
		}

		HINSTANCE hDllHandle = peSDKClient->getServiceHandleByName("UCSDK");
		if (NULL == hDllHandle)
		{
			ERROR_LOG() << "getServiceHandleByName failed.";
			return UC_Fail;
		}

		g_fpAddContactToFavoriteGroup = (fp_AddContactToFavoriteGroup)GetProcAddress(hDllHandle,"AddContactToFavoriteGroup");
		if (NULL == g_fpAddContactToFavoriteGroup)
		{
			ERROR_LOG() << "GetProcAddress \"AddContactToFavoriteGroup\" failed.";
			return UC_Fail;
		}
	}

	int iRet = (*g_fpAddContactToFavoriteGroup)(group, _contact);
	return iRet;

}

int UCSDK_CALL RemoveContactFromFavoriteGroup(const UCFavoriteGroup* group, const UCContact* _contact)
{
	if (NULL == g_fpRemoveContactFromFavoriteGroup)
	{
		eSDKClientPlatformExecute *peSDKClient = eSDKClientPlatformExecute::Instance();
		if (NULL == peSDKClient)
		{
			ERROR_LOG() << "Get eSDKClientPlatformExecute instance failed.";
			return UC_Fail;
		}

		HINSTANCE hDllHandle = peSDKClient->getServiceHandleByName("UCSDK");
		if (NULL == hDllHandle)
		{
			ERROR_LOG() << "getServiceHandleByName failed.";
			return UC_Fail;
		}

		g_fpRemoveContactFromFavoriteGroup = (fp_RemoveContactFromFavoriteGroup)GetProcAddress(hDllHandle,"RemoveContactFromFavoriteGroup");
		if (NULL == g_fpRemoveContactFromFavoriteGroup)
		{
			ERROR_LOG() << "GetProcAddress \"RemoveContactFromFavoriteGroup\" failed.";
			return UC_Fail;
		}
	}

	int iRet = (*g_fpRemoveContactFromFavoriteGroup)(group, _contact);
	return iRet;

}

int UCSDK_CALL RenameToFavoriteGroup(const UCFavoriteGroup* group, const char* _name)
{
	if (NULL == g_fpRenameToFavoriteGroup)
	{
		eSDKClientPlatformExecute *peSDKClient = eSDKClientPlatformExecute::Instance();
		if (NULL == peSDKClient)
		{
			ERROR_LOG() << "Get eSDKClientPlatformExecute instance failed.";
			return UC_Fail;
		}

		HINSTANCE hDllHandle = peSDKClient->getServiceHandleByName("UCSDK");
		if (NULL == hDllHandle)
		{
			ERROR_LOG() << "getServiceHandleByName failed.";
			return UC_Fail;
		}

		g_fpRenameToFavoriteGroup = (fp_RenameToFavoriteGroup)GetProcAddress(hDllHandle,"RenameToFavoriteGroup");
		if (NULL == g_fpRenameToFavoriteGroup)
		{
			ERROR_LOG() << "GetProcAddress \"RenameToFavoriteGroup\" failed.";
			return UC_Fail;
		}
	}

	int iRet = (*g_fpRenameToFavoriteGroup)(group, _name);
	return iRet;

}

int UCSDK_CALL GetContactlistFromFavoriteGroup(const UCFavoriteGroup* group, int iFrom, int iTo, UCContactList* _contactlist)
{
	if (NULL == g_fpGetContactlistFromFavoriteGroup)
	{
		eSDKClientPlatformExecute *peSDKClient = eSDKClientPlatformExecute::Instance();
		if (NULL == peSDKClient)
		{
			ERROR_LOG() << "Get eSDKClientPlatformExecute instance failed.";
			return UC_Fail;
		}

		HINSTANCE hDllHandle = peSDKClient->getServiceHandleByName("UCSDK");
		if (NULL == hDllHandle)
		{
			ERROR_LOG() << "getServiceHandleByName failed.";
			return UC_Fail;
		}

		g_fpGetContactlistFromFavoriteGroup = (fp_GetContactlistFromFavoriteGroup)GetProcAddress(hDllHandle,"GetContactlistFromFavoriteGroup");
		if (NULL == g_fpGetContactlistFromFavoriteGroup)
		{
			ERROR_LOG() << "GetProcAddress \"GetContactlistFromFavoriteGroup\" failed.";
			return UC_Fail;
		}
	}

	int iRet = (*g_fpGetContactlistFromFavoriteGroup)(group, iFrom, iTo, _contactlist);
	return iRet;

}

int UCSDK_CALL AddContactToCustomGroup(const UCCustomGroup* group, UCContact* _contact)
{
	if (NULL == g_fpAddContactToCustomGroup)
	{
		eSDKClientPlatformExecute *peSDKClient = eSDKClientPlatformExecute::Instance();
		if (NULL == peSDKClient)
		{
			ERROR_LOG() << "Get eSDKClientPlatformExecute instance failed.";
			return UC_Fail;
		}

		HINSTANCE hDllHandle = peSDKClient->getServiceHandleByName("UCSDK");
		if (NULL == hDllHandle)
		{
			ERROR_LOG() << "getServiceHandleByName failed.";
			return UC_Fail;
		}

		g_fpAddContactToCustomGroup = (fp_AddContactToCustomGroup)GetProcAddress(hDllHandle,"AddContactToCustomGroup");
		if (NULL == g_fpAddContactToCustomGroup)
		{
			ERROR_LOG() << "GetProcAddress \"AddContactToCustomGroup\" failed.";
			return UC_Fail;
		}
	}

	int iRet = (*g_fpAddContactToCustomGroup)(group, _contact);
	return iRet;

}

int UCSDK_CALL RemoveContactFromCustomGroup(const UCCustomGroup* group, const UCContact* _contact)
{
	if (NULL == g_fpRemoveContactFromCustomGroup)
	{
		eSDKClientPlatformExecute *peSDKClient = eSDKClientPlatformExecute::Instance();
		if (NULL == peSDKClient)
		{
			ERROR_LOG() << "Get eSDKClientPlatformExecute instance failed.";
			return UC_Fail;
		}

		HINSTANCE hDllHandle = peSDKClient->getServiceHandleByName("UCSDK");
		if (NULL == hDllHandle)
		{
			ERROR_LOG() << "getServiceHandleByName failed.";
			return UC_Fail;
		}

		g_fpRemoveContactFromCustomGroup = (fp_RemoveContactFromCustomGroup)GetProcAddress(hDllHandle,"RemoveContactFromCustomGroup");
		if (NULL == g_fpRemoveContactFromCustomGroup)
		{
			ERROR_LOG() << "GetProcAddress \"RemoveContactFromCustomGroup\" failed.";
			return UC_Fail;
		}
	}

	int iRet = (*g_fpRemoveContactFromCustomGroup)(group, _contact);
	return iRet;

}

int UCSDK_CALL RenameToCustomGroup(const UCCustomGroup* group, const char* _name)
{
	if (NULL == g_fpRenameToCustomGroup)
	{
		eSDKClientPlatformExecute *peSDKClient = eSDKClientPlatformExecute::Instance();
		if (NULL == peSDKClient)
		{
			ERROR_LOG() << "Get eSDKClientPlatformExecute instance failed.";
			return UC_Fail;
		}

		HINSTANCE hDllHandle = peSDKClient->getServiceHandleByName("UCSDK");
		if (NULL == hDllHandle)
		{
			ERROR_LOG() << "getServiceHandleByName failed.";
			return UC_Fail;
		}

		g_fpRenameToCustomGroup = (fp_RenameToCustomGroup)GetProcAddress(hDllHandle,"RenameToCustomGroup");
		if (NULL == g_fpRenameToCustomGroup)
		{
			ERROR_LOG() << "GetProcAddress \"RenameToCustomGroup\" failed.";
			return UC_Fail;
		}
	}

	int iRet = (*g_fpRenameToCustomGroup)(group, _name);
	return iRet;

}

int UCSDK_CALL GetContactlistFromCustomGroup(const UCCustomGroup* group, int iFrom, int iTo, UCContactList* _contactlist)
{
	if (NULL == g_fpGetContactlistFromCustomGroup)
	{
		eSDKClientPlatformExecute *peSDKClient = eSDKClientPlatformExecute::Instance();
		if (NULL == peSDKClient)
		{
			ERROR_LOG() << "Get eSDKClientPlatformExecute instance failed.";
			return UC_Fail;
		}

		HINSTANCE hDllHandle = peSDKClient->getServiceHandleByName("UCSDK");
		if (NULL == hDllHandle)
		{
			ERROR_LOG() << "getServiceHandleByName failed.";
			return UC_Fail;
		}

		g_fpGetContactlistFromCustomGroup = (fp_GetContactlistFromCustomGroup)GetProcAddress(hDllHandle,"GetContactlistFromCustomGroup");
		if (NULL == g_fpGetContactlistFromCustomGroup)
		{
			ERROR_LOG() << "GetProcAddress \"GetContactlistFromCustomGroup\" failed.";
			return UC_Fail;
		}
	}

	int iRet = (*g_fpGetContactlistFromCustomGroup)(group, iFrom, iTo, _contactlist);
	return iRet;

}

int UCSDK_CALL MoveUp(const UCCustomGroup* group)
{
	if (NULL == g_fpMoveUp)
	{
		eSDKClientPlatformExecute *peSDKClient = eSDKClientPlatformExecute::Instance();
		if (NULL == peSDKClient)
		{
			ERROR_LOG() << "Get eSDKClientPlatformExecute instance failed.";
			return UC_Fail;
		}

		HINSTANCE hDllHandle = peSDKClient->getServiceHandleByName("UCSDK");
		if (NULL == hDllHandle)
		{
			ERROR_LOG() << "getServiceHandleByName failed.";
			return UC_Fail;
		}

		g_fpMoveUp = (fp_MoveUp)GetProcAddress(hDllHandle,"MoveUp");
		if (NULL == g_fpMoveUp)
		{
			ERROR_LOG() << "GetProcAddress \"MoveUp\" failed.";
			return UC_Fail;
		}
	}

	int iRet = (*g_fpMoveUp)(group);
	return iRet;

}

int UCSDK_CALL MoveDown(const UCCustomGroup* group)
{
	if (NULL == g_fpMoveDown)
	{
		eSDKClientPlatformExecute *peSDKClient = eSDKClientPlatformExecute::Instance();
		if (NULL == peSDKClient)
		{
			ERROR_LOG() << "Get eSDKClientPlatformExecute instance failed.";
			return UC_Fail;
		}

		HINSTANCE hDllHandle = peSDKClient->getServiceHandleByName("UCSDK");
		if (NULL == hDllHandle)
		{
			ERROR_LOG() << "getServiceHandleByName failed.";
			return UC_Fail;
		}

		g_fpMoveDown = (fp_MoveDown)GetProcAddress(hDllHandle,"MoveDown");
		if (NULL == g_fpMoveDown)
		{
			ERROR_LOG() << "GetProcAddress \"MoveDown\" failed.";
			return UC_Fail;
		}
	}

	int iRet = (*g_fpMoveDown)(group);
	return iRet;

}

int UCSDK_CALL AddContactToFixedGroup(const UCFixedGroup* group, UCContact* _contact)
{
	if (NULL == g_fpAddContactToFixedGroup)
	{
		eSDKClientPlatformExecute *peSDKClient = eSDKClientPlatformExecute::Instance();
		if (NULL == peSDKClient)
		{
			ERROR_LOG() << "Get eSDKClientPlatformExecute instance failed.";
			return UC_Fail;
		}

		HINSTANCE hDllHandle = peSDKClient->getServiceHandleByName("UCSDK");
		if (NULL == hDllHandle)
		{
			ERROR_LOG() << "getServiceHandleByName failed.";
			return UC_Fail;
		}

		g_fpAddContactToFixedGroup = (fp_AddContactToFixedGroup)GetProcAddress(hDllHandle,"AddContactToFixedGroup");
		if (NULL == g_fpAddContactToFixedGroup)
		{
			ERROR_LOG() << "GetProcAddress \"AddContactToFixedGroup\" failed.";
			return UC_Fail;
		}
	}

	int iRet = (*g_fpAddContactToFixedGroup)(group, _contact);
	return iRet;

}

int UCSDK_CALL RemoveContactFromFixedGroup(const UCFixedGroup* group, const UCContact* _contact)
{
	if (NULL == g_fpRemoveContactFromFixedGroup)
	{
		eSDKClientPlatformExecute *peSDKClient = eSDKClientPlatformExecute::Instance();
		if (NULL == peSDKClient)
		{
			ERROR_LOG() << "Get eSDKClientPlatformExecute instance failed.";
			return UC_Fail;
		}

		HINSTANCE hDllHandle = peSDKClient->getServiceHandleByName("UCSDK");
		if (NULL == hDllHandle)
		{
			ERROR_LOG() << "getServiceHandleByName failed.";
			return UC_Fail;
		}

		g_fpRemoveContactFromFixedGroup = (fp_RemoveContactFromFixedGroup)GetProcAddress(hDllHandle,"RemoveContactFromFixedGroup");
		if (NULL == g_fpRemoveContactFromFixedGroup)
		{
			ERROR_LOG() << "GetProcAddress \"RemoveContactFromFixedGroup\" failed.";
			return UC_Fail;
		}
	}

	int iRet = (*g_fpRemoveContactFromFixedGroup)(group, _contact);
	return iRet;

}

int UCSDK_CALL RenameToFixedGroup(const UCFixedGroup* group, const char* _name)
{
	if (NULL == g_fpRenameToFixedGroup)
	{
		eSDKClientPlatformExecute *peSDKClient = eSDKClientPlatformExecute::Instance();
		if (NULL == peSDKClient)
		{
			ERROR_LOG() << "Get eSDKClientPlatformExecute instance failed.";
			return UC_Fail;
		}

		HINSTANCE hDllHandle = peSDKClient->getServiceHandleByName("UCSDK");
		if (NULL == hDllHandle)
		{
			ERROR_LOG() << "getServiceHandleByName failed.";
			return UC_Fail;
		}

		g_fpRenameToFixedGroup = (fp_RenameToFixedGroup)GetProcAddress(hDllHandle,"RenameToFixedGroup");
		if (NULL == g_fpRenameToFixedGroup)
		{
			ERROR_LOG() << "GetProcAddress \"RenameToFixedGroup\" failed.";
			return UC_Fail;
		}
	}

	int iRet = (*g_fpRenameToFixedGroup)(group, _name);
	return iRet;

}

int UCSDK_CALL GetContactlistFromFixedGroup(const UCFixedGroup* group, int iFrom, int iTo, UCContactList* _contactlist)
{
	if (NULL == g_fpGetContactlistFromFixedGroup)
	{
		eSDKClientPlatformExecute *peSDKClient = eSDKClientPlatformExecute::Instance();
		if (NULL == peSDKClient)
		{
			ERROR_LOG() << "Get eSDKClientPlatformExecute instance failed.";
			return UC_Fail;
		}

		HINSTANCE hDllHandle = peSDKClient->getServiceHandleByName("UCSDK");
		if (NULL == hDllHandle)
		{
			ERROR_LOG() << "getServiceHandleByName failed.";
			return UC_Fail;
		}

		g_fpGetContactlistFromFixedGroup = (fp_GetContactlistFromFixedGroup)GetProcAddress(hDllHandle,"GetContactlistFromFixedGroup");
		if (NULL == g_fpGetContactlistFromFixedGroup)
		{
			ERROR_LOG() << "GetProcAddress \"GetContactlistFromFixedGroup\" failed.";
			return UC_Fail;
		}
	}

	int iRet = (*g_fpGetContactlistFromFixedGroup)(group, iFrom, iTo, _contactlist);
	return iRet;

}

int UCSDK_CALL ChangeGroupInfo(const UCFixedGroup* group)
{
	if (NULL == g_fpChangeGroupInfo)
	{
		eSDKClientPlatformExecute *peSDKClient = eSDKClientPlatformExecute::Instance();
		if (NULL == peSDKClient)
		{
			ERROR_LOG() << "Get eSDKClientPlatformExecute instance failed.";
			return UC_Fail;
		}

		HINSTANCE hDllHandle = peSDKClient->getServiceHandleByName("UCSDK");
		if (NULL == hDllHandle)
		{
			ERROR_LOG() << "getServiceHandleByName failed.";
			return UC_Fail;
		}

		g_fpChangeGroupInfo = (fp_ChangeGroupInfo)GetProcAddress(hDllHandle,"ChangeGroupInfo");
		if (NULL == g_fpChangeGroupInfo)
		{
			ERROR_LOG() << "GetProcAddress \"ChangeGroupInfo\" failed.";
			return UC_Fail;
		}
	}

	int iRet = (*g_fpChangeGroupInfo)(group);
	return iRet;

}

int UCSDK_CALL ChangeGroupOwner(const UCFixedGroup* group, const UCContact* _owner)
{
	if (NULL == g_fpChangeGroupOwner)
	{
		eSDKClientPlatformExecute *peSDKClient = eSDKClientPlatformExecute::Instance();
		if (NULL == peSDKClient)
		{
			ERROR_LOG() << "Get eSDKClientPlatformExecute instance failed.";
			return UC_Fail;
		}

		HINSTANCE hDllHandle = peSDKClient->getServiceHandleByName("UCSDK");
		if (NULL == hDllHandle)
		{
			ERROR_LOG() << "getServiceHandleByName failed.";
			return UC_Fail;
		}

		g_fpChangeGroupOwner = (fp_ChangeGroupOwner)GetProcAddress(hDllHandle,"ChangeGroupOwner");
		if (NULL == g_fpChangeGroupOwner)
		{
			ERROR_LOG() << "GetProcAddress \"ChangeGroupOwner\" failed.";
			return UC_Fail;
		}
	}

	int iRet = (*g_fpChangeGroupOwner)(group, _owner);
	return iRet;

}

int UCSDK_CALL RefreshContactList(const UCFixedGroup* group, int iFrom, int iTo, UCContactList* _contactlist)
{
	if (NULL == g_fpRefreshContactList)
	{
		eSDKClientPlatformExecute *peSDKClient = eSDKClientPlatformExecute::Instance();
		if (NULL == peSDKClient)
		{
			ERROR_LOG() << "Get eSDKClientPlatformExecute instance failed.";
			return UC_Fail;
		}

		HINSTANCE hDllHandle = peSDKClient->getServiceHandleByName("UCSDK");
		if (NULL == hDllHandle)
		{
			ERROR_LOG() << "getServiceHandleByName failed.";
			return UC_Fail;
		}

		g_fpRefreshContactList = (fp_RefreshContactList)GetProcAddress(hDllHandle,"RefreshContactList");
		if (NULL == g_fpRefreshContactList)
		{
			ERROR_LOG() << "GetProcAddress \"RefreshContactList\" failed.";
			return UC_Fail;
		}
	}

	int iRet = (*g_fpRefreshContactList)(group, iFrom, iTo, _contactlist);
	return iRet;

}

int UCSDK_CALL RefreshGroup(const UCFixedGroup* group)
{
	if (NULL == g_fpRefreshGroup)
	{
		eSDKClientPlatformExecute *peSDKClient = eSDKClientPlatformExecute::Instance();
		if (NULL == peSDKClient)
		{
			ERROR_LOG() << "Get eSDKClientPlatformExecute instance failed.";
			return UC_Fail;
		}

		HINSTANCE hDllHandle = peSDKClient->getServiceHandleByName("UCSDK");
		if (NULL == hDllHandle)
		{
			ERROR_LOG() << "getServiceHandleByName failed.";
			return UC_Fail;
		}

		g_fpRefreshGroup = (fp_RefreshGroup)GetProcAddress(hDllHandle,"RefreshGroup");
		if (NULL == g_fpRefreshGroup)
		{
			ERROR_LOG() << "GetProcAddress \"RefreshGroup\" failed.";
			return UC_Fail;
		}
	}

	int iRet = (*g_fpRefreshGroup)(group);
	return iRet;

}

int UCSDK_CALL AcceptInvitation(const UCFixedGroup* group)
{
	if (NULL == g_fpAcceptInvitation)
	{
		eSDKClientPlatformExecute *peSDKClient = eSDKClientPlatformExecute::Instance();
		if (NULL == peSDKClient)
		{
			ERROR_LOG() << "Get eSDKClientPlatformExecute instance failed.";
			return UC_Fail;
		}

		HINSTANCE hDllHandle = peSDKClient->getServiceHandleByName("UCSDK");
		if (NULL == hDllHandle)
		{
			ERROR_LOG() << "getServiceHandleByName failed.";
			return UC_Fail;
		}

		g_fpAcceptInvitation = (fp_AcceptInvitation)GetProcAddress(hDllHandle,"AcceptInvitation");
		if (NULL == g_fpAcceptInvitation)
		{
			ERROR_LOG() << "GetProcAddress \"AcceptInvitation\" failed.";
			return UC_Fail;
		}
	}

	int iRet = (*g_fpAcceptInvitation)(group);
	return iRet;

}

int UCSDK_CALL RejectInvitation(const UCFixedGroup* group)
{
	if (NULL == g_fpRejectInvitation)
	{
		eSDKClientPlatformExecute *peSDKClient = eSDKClientPlatformExecute::Instance();
		if (NULL == peSDKClient)
		{
			ERROR_LOG() << "Get eSDKClientPlatformExecute instance failed.";
			return UC_Fail;
		}

		HINSTANCE hDllHandle = peSDKClient->getServiceHandleByName("UCSDK");
		if (NULL == hDllHandle)
		{
			ERROR_LOG() << "getServiceHandleByName failed.";
			return UC_Fail;
		}

		g_fpRejectInvitation = (fp_RejectInvitation)GetProcAddress(hDllHandle,"RejectInvitation");
		if (NULL == g_fpRejectInvitation)
		{
			ERROR_LOG() << "GetProcAddress \"RejectInvitation\" failed.";
			return UC_Fail;
		}
	}

	int iRet = (*g_fpRejectInvitation)(group);
	return iRet;

}

int UCSDK_CALL AcceptJoinReq(const UCFixedGroup* group, const UCContact* _contact)
{
	if (NULL == g_fpAcceptJoinReq)
	{
		eSDKClientPlatformExecute *peSDKClient = eSDKClientPlatformExecute::Instance();
		if (NULL == peSDKClient)
		{
			ERROR_LOG() << "Get eSDKClientPlatformExecute instance failed.";
			return UC_Fail;
		}

		HINSTANCE hDllHandle = peSDKClient->getServiceHandleByName("UCSDK");
		if (NULL == hDllHandle)
		{
			ERROR_LOG() << "getServiceHandleByName failed.";
			return UC_Fail;
		}

		g_fpAcceptJoinReq = (fp_AcceptJoinReq)GetProcAddress(hDllHandle,"AcceptJoinReq");
		if (NULL == g_fpAcceptJoinReq)
		{
			ERROR_LOG() << "GetProcAddress \"AcceptJoinReq\" failed.";
			return UC_Fail;
		}
	}

	int iRet = (*g_fpAcceptJoinReq)(group, _contact);
	return iRet;
}

int UCSDK_CALL RejectJoinReq(const UCFixedGroup* group, const UCContact* _contact)
{
	if (NULL == g_fpRejectJoinReq)
	{
		eSDKClientPlatformExecute *peSDKClient = eSDKClientPlatformExecute::Instance();
		if (NULL == peSDKClient)
		{
			ERROR_LOG() << "Get eSDKClientPlatformExecute instance failed.";
			return UC_Fail;
		}

		HINSTANCE hDllHandle = peSDKClient->getServiceHandleByName("UCSDK");
		if (NULL == hDllHandle)
		{
			ERROR_LOG() << "getServiceHandleByName failed.";
			return UC_Fail;
		}

		g_fpRejectJoinReq = (fp_RejectJoinReq)GetProcAddress(hDllHandle,"RejectJoinReq");
		if (NULL == g_fpRejectJoinReq)
		{
			ERROR_LOG() << "GetProcAddress \"RejectJoinReq\" failed.";
			return UC_Fail;
		}
	}

	int iRet = (*g_fpRejectJoinReq)(group, _contact);
	return iRet;
}

int UCSDK_CALL SendIMMessage(const char* pMsg, const UCAccountList* accountList, char convId[CONVID_LENGTH])
{
	if (NULL == g_fpSendIMMessage)
	{
		eSDKClientPlatformExecute *peSDKClient = eSDKClientPlatformExecute::Instance();
		if (NULL == peSDKClient)
		{
			ERROR_LOG() << "Get eSDKClientPlatformExecute instance failed.";
			return UC_Fail;
		}

		HINSTANCE hDllHandle = peSDKClient->getServiceHandleByName("UCSDK");
		if (NULL == hDllHandle)
		{
			ERROR_LOG() << "getServiceHandleByName failed.";
			return UC_Fail;
		}

		g_fpSendIMMessage = (fp_SendIMMessage)GetProcAddress(hDllHandle,"SendIMMessage");
		if (NULL == g_fpSendIMMessage)
		{
			ERROR_LOG() << "GetProcAddress \"SendIMMessage\" failed.";
			return UC_Fail;
		}
	}

	int iRet = (*g_fpSendIMMessage)(pMsg, accountList, convId);
	return iRet;

}

int UCSDK_CALL CloseConversation(const char* convId)
{
	if (NULL == g_fpCloseConversation)
	{
		eSDKClientPlatformExecute *peSDKClient = eSDKClientPlatformExecute::Instance();
		if (NULL == peSDKClient)
		{
			ERROR_LOG() << "Get eSDKClientPlatformExecute instance failed.";
			return UC_Fail;
		}

		HINSTANCE hDllHandle = peSDKClient->getServiceHandleByName("UCSDK");
		if (NULL == hDllHandle)
		{
			ERROR_LOG() << "getServiceHandleByName failed.";
			return UC_Fail;
		}

		g_fpCloseConversation = (fp_CloseConversation)GetProcAddress(hDllHandle,"CloseConversation");
		if (NULL == g_fpCloseConversation)
		{
			ERROR_LOG() << "GetProcAddress \"CloseConversation\" failed.";
			return UC_Fail;
		}
	}

	int iRet = (*g_fpCloseConversation)(convId);
	return iRet;

}

int UCSDK_CALL AcceptFile(const char* fileId, const char* filePath)
{
	if (NULL == g_fpAcceptFile)
	{
		eSDKClientPlatformExecute *peSDKClient = eSDKClientPlatformExecute::Instance();
		if (NULL == peSDKClient)
		{
			ERROR_LOG() << "Get eSDKClientPlatformExecute instance failed.";
			return UC_Fail;
		}

		HINSTANCE hDllHandle = peSDKClient->getServiceHandleByName("UCSDK");
		if (NULL == hDllHandle)
		{
			ERROR_LOG() << "getServiceHandleByName failed.";
			return UC_Fail;
		}

		g_fpAcceptFile = (fp_AcceptFile)GetProcAddress(hDllHandle,"AcceptFile");
		if (NULL == g_fpAcceptFile)
		{
			ERROR_LOG() << "GetProcAddress \"AcceptFile\" failed.";
			return UC_Fail;
		}
	}

	int iRet = (*g_fpAcceptFile)(fileId, filePath);
	return iRet;

}

int UCSDK_CALL CancelFile(const char* fileId)
{
	if (NULL == g_fpCancelFile)
	{
		eSDKClientPlatformExecute *peSDKClient = eSDKClientPlatformExecute::Instance();
		if (NULL == peSDKClient)
		{
			ERROR_LOG() << "Get eSDKClientPlatformExecute instance failed.";
			return UC_Fail;
		}

		HINSTANCE hDllHandle = peSDKClient->getServiceHandleByName("UCSDK");
		if (NULL == hDllHandle)
		{
			ERROR_LOG() << "getServiceHandleByName failed.";
			return UC_Fail;
		}

		g_fpCancelFile = (fp_CancelFile)GetProcAddress(hDllHandle,"CancelFile");
		if (NULL == g_fpCancelFile)
		{
			ERROR_LOG() << "GetProcAddress \"CancelFile\" failed.";
			return UC_Fail;
		}
	}

	int iRet = (*g_fpCancelFile)(fileId);
	return iRet;

}

int UCSDK_CALL RejectFile(const char* fileId)
{
	if (NULL == g_fpRejectFile)
	{
		eSDKClientPlatformExecute *peSDKClient = eSDKClientPlatformExecute::Instance();
		if (NULL == peSDKClient)
		{
			ERROR_LOG() << "Get eSDKClientPlatformExecute instance failed.";
			return UC_Fail;
		}

		HINSTANCE hDllHandle = peSDKClient->getServiceHandleByName("UCSDK");
		if (NULL == hDllHandle)
		{
			ERROR_LOG() << "getServiceHandleByName failed.";
			return UC_Fail;
		}

		g_fpRejectFile = (fp_RejectFile)GetProcAddress(hDllHandle,"RejectFile");
		if (NULL == g_fpRejectFile)
		{
			ERROR_LOG() << "GetProcAddress \"RejectFile\" failed.";
			return UC_Fail;
		}
	}

	int iRet = (*g_fpRejectFile)(fileId);
	return iRet;

}

int UCSDK_CALL TransferFile(const char* pAcc, const char* filePath,
							const char* transType, int bIsOfflineFile, char fileId[FILEID_LENGTH])
{
	if (NULL == g_fpTransferFile)
	{
		eSDKClientPlatformExecute *peSDKClient = eSDKClientPlatformExecute::Instance();
		if (NULL == peSDKClient)
		{
			ERROR_LOG() << "Get eSDKClientPlatformExecute instance failed.";
			return UC_Fail;
		}

		HINSTANCE hDllHandle = peSDKClient->getServiceHandleByName("UCSDK");
		if (NULL == hDllHandle)
		{
			ERROR_LOG() << "getServiceHandleByName failed.";
			return UC_Fail;
		}

		g_fpTransferFile = (fp_TransferFile)GetProcAddress(hDllHandle,"TransferFile");
		if (NULL == g_fpTransferFile)
		{
			ERROR_LOG() << "GetProcAddress \"TransferFile\" failed.";
			return UC_Fail;
		}
	}

	int iRet = (*g_fpTransferFile)(pAcc, filePath,transType, bIsOfflineFile, fileId);
	return iRet;

}

int UCSDK_CALL MakeMeetingGroup(const UCContactList* memberlist, char convId[CONVID_LENGTH])
{
	if (NULL == g_fpMakeMeetingGroup)
	{
		eSDKClientPlatformExecute *peSDKClient = eSDKClientPlatformExecute::Instance();
		if (NULL == peSDKClient)
		{
			ERROR_LOG() << "Get eSDKClientPlatformExecute instance failed.";
			return UC_Fail;
		}

		HINSTANCE hDllHandle = peSDKClient->getServiceHandleByName("UCSDK");
		if (NULL == hDllHandle)
		{
			ERROR_LOG() << "getServiceHandleByName failed.";
			return UC_Fail;
		}

		g_fpMakeMeetingGroup = (fp_MakeMeetingGroup)GetProcAddress(hDllHandle,"MakeMeetingGroup");
		if (NULL == g_fpMakeMeetingGroup)
		{
			ERROR_LOG() << "GetProcAddress \"MakeMeetingGroup\" failed.";
			return UC_Fail;
		}
	}

	int iRet = (*g_fpMakeMeetingGroup)(memberlist, convId);
	return iRet;

}

int UCSDK_CALL StartMeeting(const char* convId)
{
	if (NULL == g_fpStartMeeting)
	{
		eSDKClientPlatformExecute *peSDKClient = eSDKClientPlatformExecute::Instance();
		if (NULL == peSDKClient)
		{
			ERROR_LOG() << "Get eSDKClientPlatformExecute instance failed.";
			return UC_Fail;
		}

		HINSTANCE hDllHandle = peSDKClient->getServiceHandleByName("UCSDK");
		if (NULL == hDllHandle)
		{
			ERROR_LOG() << "getServiceHandleByName failed.";
			return UC_Fail;
		}

		g_fpStartMeeting = (fp_StartMeeting)GetProcAddress(hDllHandle,"StartMeeting");
		if (NULL == g_fpStartMeeting)
		{
			ERROR_LOG() << "GetProcAddress \"StartMeeting\" failed.";
			return UC_Fail;
		}
	}

	int iRet = (*g_fpStartMeeting)(convId);
	return iRet;

}

int UCSDK_CALL AcceptMeeting(const char* convId)
{
	if (NULL == g_fpAcceptMeeting)
	{
		eSDKClientPlatformExecute *peSDKClient = eSDKClientPlatformExecute::Instance();
		if (NULL == peSDKClient)
		{
			ERROR_LOG() << "Get eSDKClientPlatformExecute instance failed.";
			return UC_Fail;
		}

		HINSTANCE hDllHandle = peSDKClient->getServiceHandleByName("UCSDK");
		if (NULL == hDllHandle)
		{
			ERROR_LOG() << "getServiceHandleByName failed.";
			return UC_Fail;
		}

		g_fpAcceptMeeting = (fp_AcceptMeeting)GetProcAddress(hDllHandle,"AcceptMeeting");
		if (NULL == g_fpAcceptMeeting)
		{
			ERROR_LOG() << "GetProcAddress \"AcceptMeeting\" failed.";
			return UC_Fail;
		}
	}

	int iRet = (*g_fpAcceptMeeting)(convId);
	return iRet;

}

int UCSDK_CALL AddParticipant(const UCContact* member, const char* convId)
{
	if (NULL == g_fpAddParticipant)
	{
		eSDKClientPlatformExecute *peSDKClient = eSDKClientPlatformExecute::Instance();
		if (NULL == peSDKClient)
		{
			ERROR_LOG() << "Get eSDKClientPlatformExecute instance failed.";
			return UC_Fail;
		}

		HINSTANCE hDllHandle = peSDKClient->getServiceHandleByName("UCSDK");
		if (NULL == hDllHandle)
		{
			ERROR_LOG() << "getServiceHandleByName failed.";
			return UC_Fail;
		}

		g_fpAddParticipant = (fp_AddParticipant)GetProcAddress(hDllHandle,"AddParticipant");
		if (NULL == g_fpAddParticipant)
		{
			ERROR_LOG() << "GetProcAddress \"AddParticipant\" failed.";
			return UC_Fail;
		}
	}

	int iRet = (*g_fpAddParticipant)(member, convId);
	return iRet;

}

int UCSDK_CALL ConnectParticipant(const UCContact* member, const char* convId)
{
	if (NULL == g_fpConnectParticipant)
	{
		eSDKClientPlatformExecute *peSDKClient = eSDKClientPlatformExecute::Instance();
		if (NULL == peSDKClient)
		{
			ERROR_LOG() << "Get eSDKClientPlatformExecute instance failed.";
			return UC_Fail;
		}

		HINSTANCE hDllHandle = peSDKClient->getServiceHandleByName("UCSDK");
		if (NULL == hDllHandle)
		{
			ERROR_LOG() << "getServiceHandleByName failed.";
			return UC_Fail;
		}

		g_fpConnectParticipant = (fp_ConnectParticipant)GetProcAddress(hDllHandle,"ConnectParticipant");
		if (NULL == g_fpConnectParticipant)
		{
			ERROR_LOG() << "GetProcAddress \"ConnectParticipant\" failed.";
			return UC_Fail;
		}
	}

	int iRet = (*g_fpConnectParticipant)(member, convId);
	return iRet;

}

int UCSDK_CALL RemoveParticipant(const UCContact* member, const char* convId)
{
	if (NULL == g_fpRemoveParticipant)
	{
		eSDKClientPlatformExecute *peSDKClient = eSDKClientPlatformExecute::Instance();
		if (NULL == peSDKClient)
		{
			ERROR_LOG() << "Get eSDKClientPlatformExecute instance failed.";
			return UC_Fail;
		}

		HINSTANCE hDllHandle = peSDKClient->getServiceHandleByName("UCSDK");
		if (NULL == hDllHandle)
		{
			ERROR_LOG() << "getServiceHandleByName failed.";
			return UC_Fail;
		}

		g_fpRemoveParticipant = (fp_RemoveParticipant)GetProcAddress(hDllHandle,"RemoveParticipant");
		if (NULL == g_fpRemoveParticipant)
		{
			ERROR_LOG() << "GetProcAddress \"RemoveParticipant\" failed.";
			return UC_Fail;
		}
	}

	int iRet = (*g_fpRemoveParticipant)(member, convId);
	return iRet;

}

int UCSDK_CALL KickParticipant(const UCContact* member, const char* convId)
{
	if (NULL == g_fpKickParticipant)
	{
		eSDKClientPlatformExecute *peSDKClient = eSDKClientPlatformExecute::Instance();
		if (NULL == peSDKClient)
		{
			ERROR_LOG() << "Get eSDKClientPlatformExecute instance failed.";
			return UC_Fail;
		}

		HINSTANCE hDllHandle = peSDKClient->getServiceHandleByName("UCSDK");
		if (NULL == hDllHandle)
		{
			ERROR_LOG() << "getServiceHandleByName failed.";
			return UC_Fail;
		}

		g_fpKickParticipant = (fp_KickParticipant)GetProcAddress(hDllHandle,"KickParticipant");
		if (NULL == g_fpKickParticipant)
		{
			ERROR_LOG() << "GetProcAddress \"KickParticipant\" failed.";
			return UC_Fail;
		}
	}

	int iRet = (*g_fpKickParticipant)(member, convId);
	return iRet;

}

int UCSDK_CALL MuteMeeting(const UCContact* member, const char* convId)
{
	if (NULL == g_fpMuteMeeting)
	{
		eSDKClientPlatformExecute *peSDKClient = eSDKClientPlatformExecute::Instance();
		if (NULL == peSDKClient)
		{
			ERROR_LOG() << "Get eSDKClientPlatformExecute instance failed.";
			return UC_Fail;
		}

		HINSTANCE hDllHandle = peSDKClient->getServiceHandleByName("UCSDK");
		if (NULL == hDllHandle)
		{
			ERROR_LOG() << "getServiceHandleByName failed.";
			return UC_Fail;
		}

		g_fpMuteMeeting = (fp_MuteMeeting)GetProcAddress(hDllHandle,"MuteMeeting");
		if (NULL == g_fpMuteMeeting)
		{
			ERROR_LOG() << "GetProcAddress \"MuteMeeting\" failed.";
			return UC_Fail;
		}
	}

	int iRet = (*g_fpMuteMeeting)(member, convId);
	return iRet;

}

int UCSDK_CALL UnMuteMeeting(const UCContact* member, const char* convId)
{
	if (NULL == g_fpUnMuteMeeting)
	{
		eSDKClientPlatformExecute *peSDKClient = eSDKClientPlatformExecute::Instance();
		if (NULL == peSDKClient)
		{
			ERROR_LOG() << "Get eSDKClientPlatformExecute instance failed.";
			return UC_Fail;
		}

		HINSTANCE hDllHandle = peSDKClient->getServiceHandleByName("UCSDK");
		if (NULL == hDllHandle)
		{
			ERROR_LOG() << "getServiceHandleByName failed.";
			return UC_Fail;
		}

		g_fpUnMuteMeeting = (fp_UnMuteMeeting)GetProcAddress(hDllHandle,"UnMuteMeeting");
		if (NULL == g_fpUnMuteMeeting)
		{
			ERROR_LOG() << "GetProcAddress \"UnMuteMeeting\" failed.";
			return UC_Fail;
		}
	}

	int iRet = (*g_fpUnMuteMeeting)(member, convId);
	return iRet;

}

int UCSDK_CALL GetBookConfList(int iFrom, int iTo, UCBookConfList* bookConfList)
{
	if (NULL == g_fpGetBookConfList)
	{
		eSDKClientPlatformExecute *peSDKClient = eSDKClientPlatformExecute::Instance();
		if (NULL == peSDKClient)
		{
			ERROR_LOG() << "Get eSDKClientPlatformExecute instance failed.";
			return UC_Fail;
		}

		HINSTANCE hDllHandle = peSDKClient->getServiceHandleByName("UCSDK");
		if (NULL == hDllHandle)
		{
			ERROR_LOG() << "getServiceHandleByName failed.";
			return UC_Fail;
		}

		g_fpGetBookConfList = (fp_GetBookConfList)GetProcAddress(hDllHandle,"GetBookConfList");
		if (NULL == g_fpGetBookConfList)
		{
			ERROR_LOG() << "GetProcAddress \"GetBookConfList\" failed.";
			return UC_Fail;
		}
	}

	int iRet = (*g_fpGetBookConfList)(iFrom, iTo, bookConfList);
	return iRet;

}

int UCSDK_CALL JoinMeeting(const UCBookConf* meetingInfo, char convId[CONVID_LENGTH])
{
	if (NULL == g_fpJoinMeeting)
	{
		eSDKClientPlatformExecute *peSDKClient = eSDKClientPlatformExecute::Instance();
		if (NULL == peSDKClient)
		{
			ERROR_LOG() << "Get eSDKClientPlatformExecute instance failed.";
			return UC_Fail;
		}

		HINSTANCE hDllHandle = peSDKClient->getServiceHandleByName("UCSDK");
		if (NULL == hDllHandle)
		{
			ERROR_LOG() << "getServiceHandleByName failed.";
			return UC_Fail;
		}

		g_fpJoinMeeting = (fp_JoinMeeting)GetProcAddress(hDllHandle,"JoinMeeting");
		if (NULL == g_fpJoinMeeting)
		{
			ERROR_LOG() << "GetProcAddress \"JoinMeeting\" failed.";
			return UC_Fail;
		}
	}

	int iRet = (*g_fpJoinMeeting)(meetingInfo, convId);
	return iRet;

}

int UCSDK_CALL LeaveMeeting(const char* convId)
{
	if (NULL == g_fpLeaveMeeting)
	{
		eSDKClientPlatformExecute *peSDKClient = eSDKClientPlatformExecute::Instance();
		if (NULL == peSDKClient)
		{
			ERROR_LOG() << "Get eSDKClientPlatformExecute instance failed.";
			return UC_Fail;
		}

		HINSTANCE hDllHandle = peSDKClient->getServiceHandleByName("UCSDK");
		if (NULL == hDllHandle)
		{
			ERROR_LOG() << "getServiceHandleByName failed.";
			return UC_Fail;
		}

		g_fpLeaveMeeting = (fp_LeaveMeeting)GetProcAddress(hDllHandle,"LeaveMeeting");
		if (NULL == g_fpLeaveMeeting)
		{
			ERROR_LOG() << "GetProcAddress \"LeaveMeeting\" failed.";
			return UC_Fail;
		}
	}

	int iRet = (*g_fpLeaveMeeting)(convId);
	return iRet;

}

int UCSDK_CALL PublishSelfInformation(const UCPublishInfoMap* publishInfoMap)
{
	if (NULL == g_fpPublishSelfInformation)
	{
		eSDKClientPlatformExecute *peSDKClient = eSDKClientPlatformExecute::Instance();
		if (NULL == peSDKClient)
		{
			ERROR_LOG() << "Get eSDKClientPlatformExecute instance failed.";
			return UC_Fail;
		}

		HINSTANCE hDllHandle = peSDKClient->getServiceHandleByName("UCSDK");
		if (NULL == hDllHandle)
		{
			ERROR_LOG() << "getServiceHandleByName failed.";
			return UC_Fail;
		}

		g_fpPublishSelfInformation = (fp_PublishSelfInformation)GetProcAddress(hDllHandle,"PublishSelfInformation");
		if (NULL == g_fpPublishSelfInformation)
		{
			ERROR_LOG() << "GetProcAddress \"PublishSelfInformation\" failed.";
			return UC_Fail;
		}
	}

	int iRet = (*g_fpPublishSelfInformation)(publishInfoMap);
	return iRet;
}

int UCSDK_CALL GetContactStatus(const char* _uri, int* _status)
{
	if (NULL == g_fpGetContactStatus)
	{
		eSDKClientPlatformExecute *peSDKClient = eSDKClientPlatformExecute::Instance();
		if (NULL == peSDKClient)
		{
			ERROR_LOG() << "Get eSDKClientPlatformExecute instance failed.";
			return UC_Fail;
		}

		HINSTANCE hDllHandle = peSDKClient->getServiceHandleByName("UCSDK");
		if (NULL == hDllHandle)
		{
			ERROR_LOG() << "getServiceHandleByName failed.";
			return UC_Fail;
		}

		g_fpGetContactStatus = (fp_GetContactStatus)GetProcAddress(hDllHandle,"GetContactStatus");
		if (NULL == g_fpGetContactStatus)
		{
			ERROR_LOG() << "GetProcAddress \"GetContactStatus\" failed.";
			return UC_Fail;
		}
	}

	int iRet = (*g_fpGetContactStatus)(_uri, _status);
	return iRet;
}

int UCSDK_CALL OnClientSignInNotify(const UCClientSignInNotify fpClientSignInNotify)
{
	if (NULL == g_fpOnClientSignInNotify)
	{
		eSDKClientPlatformExecute *peSDKClient = eSDKClientPlatformExecute::Instance();
		if (NULL == peSDKClient)
		{
			ERROR_LOG() << "Get eSDKClientPlatformExecute instance failed.";
			return UC_Fail;
		}

		HINSTANCE hDllHandle = peSDKClient->getServiceHandleByName("UCSDK");
		if (NULL == hDllHandle)
		{
			ERROR_LOG() << "getServiceHandleByName failed.";
			return UC_Fail;
		}

		g_fpOnClientSignInNotify = (fp_OnClientSignInNotify)GetProcAddress(hDllHandle,"OnClientSignInNotify");
		if (NULL == g_fpOnClientSignInNotify)
		{
			ERROR_LOG() << "GetProcAddress \"OnClientSignInNotify\" failed.";
			return UC_Fail;
		}
	}

	int iRet = (*g_fpOnClientSignInNotify)(fpClientSignInNotify);
	return iRet;

}

int UCSDK_CALL OnStatusChanged(const UCStatusChanged fpStatusChanged)
{
	if (NULL == g_fpOnStatusChanged)
	{
		eSDKClientPlatformExecute *peSDKClient = eSDKClientPlatformExecute::Instance();
		if (NULL == peSDKClient)
		{
			ERROR_LOG() << "Get eSDKClientPlatformExecute instance failed.";
			return UC_Fail;
		}

		HINSTANCE hDllHandle = peSDKClient->getServiceHandleByName("UCSDK");
		if (NULL == hDllHandle)
		{
			ERROR_LOG() << "getServiceHandleByName failed.";
			return UC_Fail;
		}

		g_fpOnStatusChanged = (fp_OnStatusChanged)GetProcAddress(hDllHandle,"OnStatusChanged");
		if (NULL == g_fpOnStatusChanged)
		{
			ERROR_LOG() << "GetProcAddress \"OnStatusChanged\" failed.";
			return UC_Fail;
		}
	}

	int iRet = (*g_fpOnStatusChanged)(fpStatusChanged);
	return iRet;

}

int UCSDK_CALL OnIncreContactsChanged(const UCIncreContactsChanged fpIncreContactsChanged)
{
	if (NULL == g_fpOnIncreContactsChanged)
	{
		eSDKClientPlatformExecute *peSDKClient = eSDKClientPlatformExecute::Instance();
		if (NULL == peSDKClient)
		{
			ERROR_LOG() << "Get eSDKClientPlatformExecute instance failed.";
			return UC_Fail;
		}

		HINSTANCE hDllHandle = peSDKClient->getServiceHandleByName("UCSDK");
		if (NULL == hDllHandle)
		{
			ERROR_LOG() << "getServiceHandleByName failed.";
			return UC_Fail;
		}

		g_fpOnIncreContactsChanged = (fp_OnIncreContactsChanged)GetProcAddress(hDllHandle,"OnIncreContactsChanged");
		if (NULL == g_fpOnIncreContactsChanged)
		{
			ERROR_LOG() << "GetProcAddress \"OnIncreContactsChanged\" failed.";
			return UC_Fail;
		}
	}

	int iRet = (*g_fpOnIncreContactsChanged)(fpIncreContactsChanged);
	return iRet;

}

int UCSDK_CALL OnAVSessAdded(const UCAVSessAdded fpAVSessAdded)
{
	if (NULL == g_fpOnAVSessAdded)
	{
		eSDKClientPlatformExecute *peSDKClient = eSDKClientPlatformExecute::Instance();
		if (NULL == peSDKClient)
		{
			ERROR_LOG() << "Get eSDKClientPlatformExecute instance failed.";
			return UC_Fail;
		}

		HINSTANCE hDllHandle = peSDKClient->getServiceHandleByName("UCSDK");
		if (NULL == hDllHandle)
		{
			ERROR_LOG() << "getServiceHandleByName failed.";
			return UC_Fail;
		}

		g_fpOnAVSessAdded = (fp_OnAVSessAdded)GetProcAddress(hDllHandle,"OnAVSessAdded");
		if (NULL == g_fpOnAVSessAdded)
		{
			ERROR_LOG() << "GetProcAddress \"OnAVSessAdded\" failed.";
			return UC_Fail;
		}
	}

	int iRet = (*g_fpOnAVSessAdded)(fpAVSessAdded);
	return iRet;

}

int UCSDK_CALL OnAVSessionConnected(const UCAVSessionConnected fpAVSessionConnected)
{
	if (NULL == g_fpOnAVSessionConnected)
	{
		eSDKClientPlatformExecute *peSDKClient = eSDKClientPlatformExecute::Instance();
		if (NULL == peSDKClient)
		{
			ERROR_LOG() << "Get eSDKClientPlatformExecute instance failed.";
			return UC_Fail;
		}

		HINSTANCE hDllHandle = peSDKClient->getServiceHandleByName("UCSDK");
		if (NULL == hDllHandle)
		{
			ERROR_LOG() << "getServiceHandleByName failed.";
			return UC_Fail;
		}

		g_fpOnAVSessionConnected = (fp_OnAVSessionConnected)GetProcAddress(hDllHandle,"OnAVSessionConnected");
		if (NULL == g_fpOnAVSessionConnected)
		{
			ERROR_LOG() << "GetProcAddress \"OnAVSessionConnected\" failed.";
			return UC_Fail;
		}
	}

	int iRet = (*g_fpOnAVSessionConnected)(fpAVSessionConnected);
	return iRet;

}

int UCSDK_CALL OnAVSessionClosed(const UCAVSessionClosed fpAVSessionClosed)
{
	if (NULL == g_fpOnAVSessionClosed)
	{
		eSDKClientPlatformExecute *peSDKClient = eSDKClientPlatformExecute::Instance();
		if (NULL == peSDKClient)
		{
			ERROR_LOG() << "Get eSDKClientPlatformExecute instance failed.";
			return UC_Fail;
		}

		HINSTANCE hDllHandle = peSDKClient->getServiceHandleByName("UCSDK");
		if (NULL == hDllHandle)
		{
			ERROR_LOG() << "getServiceHandleByName failed.";
			return UC_Fail;
		}

		g_fpOnAVSessionClosed = (fp_OnAVSessionClosed)GetProcAddress(hDllHandle,"OnAVSessionClosed");
		if (NULL == g_fpOnAVSessionClosed)
		{
			ERROR_LOG() << "GetProcAddress \"OnAVSessionClosed\" failed.";
			return UC_Fail;
		}
	}

	int iRet = (*g_fpOnAVSessionClosed)(fpAVSessionClosed);
	return iRet;

}

int UCSDK_CALL OnConvMemberStatusChanged(const UCConvMemberStatusChanged fpConvMemberStatusChanged)
{
	if (NULL == g_fpOnConvMemberStatusChanged)
	{
		eSDKClientPlatformExecute *peSDKClient = eSDKClientPlatformExecute::Instance();
		if (NULL == peSDKClient)
		{
			ERROR_LOG() << "Get eSDKClientPlatformExecute instance failed.";
			return UC_Fail;
		}

		HINSTANCE hDllHandle = peSDKClient->getServiceHandleByName("UCSDK");
		if (NULL == hDllHandle)
		{
			ERROR_LOG() << "getServiceHandleByName failed.";
			return UC_Fail;
		}

		g_fpOnConvMemberStatusChanged = (fp_OnConvMemberStatusChanged)GetProcAddress(hDllHandle,"OnConvMemberStatusChanged");
		if (NULL == g_fpOnConvMemberStatusChanged)
		{
			ERROR_LOG() << "GetProcAddress \"OnConvMemberStatusChanged\" failed.";
			return UC_Fail;
		}
	}

	int iRet = (*g_fpOnConvMemberStatusChanged)(fpConvMemberStatusChanged);
	return iRet;

}

int UCSDK_CALL OnConvMemAllowSpeak(const UCConvMemAllowSpeak fpConvMemAllowSpeak)
{
	if (NULL == g_fpOnConvMemAllowSpeak)
	{
		eSDKClientPlatformExecute *peSDKClient = eSDKClientPlatformExecute::Instance();
		if (NULL == peSDKClient)
		{
			ERROR_LOG() << "Get eSDKClientPlatformExecute instance failed.";
			return UC_Fail;
		}

		HINSTANCE hDllHandle = peSDKClient->getServiceHandleByName("UCSDK");
		if (NULL == hDllHandle)
		{
			ERROR_LOG() << "getServiceHandleByName failed.";
			return UC_Fail;
		}

		g_fpOnConvMemAllowSpeak = (fp_OnConvMemAllowSpeak)GetProcAddress(hDllHandle,"OnConvMemAllowSpeak");
		if (NULL == g_fpOnConvMemAllowSpeak)
		{
			ERROR_LOG() << "GetProcAddress \"OnConvMemAllowSpeak\" failed.";
			return UC_Fail;
		}
	}

	int iRet = (*g_fpOnConvMemAllowSpeak)(fpConvMemAllowSpeak);
	return iRet;

}

int UCSDK_CALL OnConvMemForbidSpeak(const UCConvMemForbidSpeak fpConvMemForbidSpeak)
{
	if (NULL == g_fpOnConvMemForbidSpeak)
	{
		eSDKClientPlatformExecute *peSDKClient = eSDKClientPlatformExecute::Instance();
		if (NULL == peSDKClient)
		{
			ERROR_LOG() << "Get eSDKClientPlatformExecute instance failed.";
			return UC_Fail;
		}

		HINSTANCE hDllHandle = peSDKClient->getServiceHandleByName("UCSDK");
		if (NULL == hDllHandle)
		{
			ERROR_LOG() << "getServiceHandleByName failed.";
			return UC_Fail;
		}

		g_fpOnConvMemForbidSpeak = (fp_OnConvMemForbidSpeak)GetProcAddress(hDllHandle,"OnConvMemForbidSpeak");
		if (NULL == g_fpOnConvMemForbidSpeak)
		{
			ERROR_LOG() << "GetProcAddress \"OnConvMemForbidSpeak\" failed.";
			return UC_Fail;
		}
	}

	int iRet = (*g_fpOnConvMemForbidSpeak)(fpConvMemForbidSpeak);
	return iRet;

}

int UCSDK_CALL OnConvMemCurSpeaker(const UCConvMemCurSpeaker fpConvMemCurSpeaker)
{
	if (NULL == g_fpOnConvMemCurSpeaker)
	{
		eSDKClientPlatformExecute *peSDKClient = eSDKClientPlatformExecute::Instance();
		if (NULL == peSDKClient)
		{
			ERROR_LOG() << "Get eSDKClientPlatformExecute instance failed.";
			return UC_Fail;
		}

		HINSTANCE hDllHandle = peSDKClient->getServiceHandleByName("UCSDK");
		if (NULL == hDllHandle)
		{
			ERROR_LOG() << "getServiceHandleByName failed.";
			return UC_Fail;
		}

		g_fpOnConvMemCurSpeaker = (fp_OnConvMemCurSpeaker)GetProcAddress(hDllHandle,"OnConvMemCurSpeaker");
		if (NULL == g_fpOnConvMemCurSpeaker)
		{
			ERROR_LOG() << "GetProcAddress \"OnConvMemCurSpeaker\" failed.";
			return UC_Fail;
		}
	}

	int iRet = (*g_fpOnConvMemCurSpeaker)(fpConvMemCurSpeaker);
	return iRet;

}

int UCSDK_CALL OnConvGroupMemberChanged(const UCConvGroupMemberChanged fpConvGroupMemberChanged)
{
	if (NULL == g_fpOnConvGroupMemberChanged)
	{
		eSDKClientPlatformExecute *peSDKClient = eSDKClientPlatformExecute::Instance();
		if (NULL == peSDKClient)
		{
			ERROR_LOG() << "Get eSDKClientPlatformExecute instance failed.";
			return UC_Fail;
		}

		HINSTANCE hDllHandle = peSDKClient->getServiceHandleByName("UCSDK");
		if (NULL == hDllHandle)
		{
			ERROR_LOG() << "getServiceHandleByName failed.";
			return UC_Fail;
		}

		g_fpOnConvGroupMemberChanged = (fp_OnConvGroupMemberChanged)GetProcAddress(hDllHandle,"OnConvGroupMemberChanged");
		if (NULL == g_fpOnConvGroupMemberChanged)
		{
			ERROR_LOG() << "GetProcAddress \"OnConvGroupMemberChanged\" failed.";
			return UC_Fail;
		}
	}

	int iRet = (*g_fpOnConvGroupMemberChanged)(fpConvGroupMemberChanged);
	return iRet;

}

int UCSDK_CALL OnReceivedIMMessage(const UCReceivedIMMessage fpReceivedIMMessage)
{
	if (NULL == g_fpOnReceivedIMMessage)
	{
		eSDKClientPlatformExecute *peSDKClient = eSDKClientPlatformExecute::Instance();
		if (NULL == peSDKClient)
		{
			ERROR_LOG() << "Get eSDKClientPlatformExecute instance failed.";
			return UC_Fail;
		}

		HINSTANCE hDllHandle = peSDKClient->getServiceHandleByName("UCSDK");
		if (NULL == hDllHandle)
		{
			ERROR_LOG() << "getServiceHandleByName failed.";
			return UC_Fail;
		}

		g_fpOnReceivedIMMessage = (fp_OnReceivedIMMessage)GetProcAddress(hDllHandle,"OnReceivedIMMessage");
		if (NULL == g_fpOnReceivedIMMessage)
		{
			ERROR_LOG() << "GetProcAddress \"OnReceivedIMMessage\" failed.";
			return UC_Fail;
		}
	}

	int iRet = (*g_fpOnReceivedIMMessage)(fpReceivedIMMessage);
	return iRet;

}

int UCSDK_CALL OnInstantSessRemoved(const UCInstantSessRemoved fpInstantSessRemoved)
{
	if (NULL == g_fpOnInstantSessRemoved)
	{
		eSDKClientPlatformExecute *peSDKClient = eSDKClientPlatformExecute::Instance();
		if (NULL == peSDKClient)
		{
			ERROR_LOG() << "Get eSDKClientPlatformExecute instance failed.";
			return UC_Fail;
		}

		HINSTANCE hDllHandle = peSDKClient->getServiceHandleByName("UCSDK");
		if (NULL == hDllHandle)
		{
			ERROR_LOG() << "getServiceHandleByName failed.";
			return UC_Fail;
		}

		g_fpOnInstantSessRemoved = (fp_OnInstantSessRemoved)GetProcAddress(hDllHandle,"OnInstantSessRemoved");
		if (NULL == g_fpOnInstantSessRemoved)
		{
			ERROR_LOG() << "GetProcAddress \"OnInstantSessRemoved\" failed.";
			return UC_Fail;
		}
	}

	int iRet = (*g_fpOnInstantSessRemoved)(fpInstantSessRemoved);
	return iRet;

}

int UCSDK_CALL OnInstantSessAdded(const UCInstantSessAdded fpInstantSessAdded)
{
	if (NULL == g_fpOnInstantSessAdded)
	{
		eSDKClientPlatformExecute *peSDKClient = eSDKClientPlatformExecute::Instance();
		if (NULL == peSDKClient)
		{
			ERROR_LOG() << "Get eSDKClientPlatformExecute instance failed.";
			return UC_Fail;
		}

		HINSTANCE hDllHandle = peSDKClient->getServiceHandleByName("UCSDK");
		if (NULL == hDllHandle)
		{
			ERROR_LOG() << "getServiceHandleByName failed.";
			return UC_Fail;
		}

		g_fpOnInstantSessAdded = (fp_OnInstantSessAdded)GetProcAddress(hDllHandle,"OnInstantSessAdded");
		if (NULL == g_fpOnInstantSessAdded)
		{
			ERROR_LOG() << "GetProcAddress \"OnInstantSessAdded\" failed.";
			return UC_Fail;
		}
	}

	int iRet = (*g_fpOnInstantSessAdded)(fpInstantSessAdded);
	return iRet;

}

int UCSDK_CALL OnSysMsgRecved(const UCSysMsgRecved fpSysMsgRecved)
{
	if (NULL == g_fpOnSysMsgRecved)
	{
		eSDKClientPlatformExecute *peSDKClient = eSDKClientPlatformExecute::Instance();
		if (NULL == peSDKClient)
		{
			ERROR_LOG() << "Get eSDKClientPlatformExecute instance failed.";
			return UC_Fail;
		}

		HINSTANCE hDllHandle = peSDKClient->getServiceHandleByName("UCSDK");
		if (NULL == hDllHandle)
		{
			ERROR_LOG() << "getServiceHandleByName failed.";
			return UC_Fail;
		}

		g_fpOnSysMsgRecved = (fp_OnSysMsgRecved)GetProcAddress(hDllHandle,"OnSysMsgRecved");
		if (NULL == g_fpOnSysMsgRecved)
		{
			ERROR_LOG() << "GetProcAddress \"OnSysMsgRecved\" failed.";
			return UC_Fail;
		}
	}

	int iRet = (*g_fpOnSysMsgRecved)(fpSysMsgRecved);
	return iRet;

}

int UCSDK_CALL OnGroupInvitation(const UCGroupInvitation fpGroupInvitation)
{
	if (NULL == g_fpOnGroupInvitation)
	{
		eSDKClientPlatformExecute *peSDKClient = eSDKClientPlatformExecute::Instance();
		if (NULL == peSDKClient)
		{
			ERROR_LOG() << "Get eSDKClientPlatformExecute instance failed.";
			return UC_Fail;
		}

		HINSTANCE hDllHandle = peSDKClient->getServiceHandleByName("UCSDK");
		if (NULL == hDllHandle)
		{
			ERROR_LOG() << "getServiceHandleByName failed.";
			return UC_Fail;
		}

		g_fpOnGroupInvitation = (fp_OnGroupInvitation)GetProcAddress(hDllHandle,"OnGroupInvitation");
		if (NULL == g_fpOnGroupInvitation)
		{
			ERROR_LOG() << "GetProcAddress \"OnGroupInvitation\" failed.";
			return UC_Fail;
		}
	}

	int iRet = (*g_fpOnGroupInvitation)(fpGroupInvitation);
	return iRet;

}

int UCSDK_CALL OnGroupInvitationRes(const UCGroupInvitationRes fpGroupInvitationRes)
{
	if (NULL == g_fpOnGroupInvitationRes)
	{
		eSDKClientPlatformExecute *peSDKClient = eSDKClientPlatformExecute::Instance();
		if (NULL == peSDKClient)
		{
			ERROR_LOG() << "Get eSDKClientPlatformExecute instance failed.";
			return UC_Fail;
		}

		HINSTANCE hDllHandle = peSDKClient->getServiceHandleByName("UCSDK");
		if (NULL == hDllHandle)
		{
			ERROR_LOG() << "getServiceHandleByName failed.";
			return UC_Fail;
		}

		g_fpOnGroupInvitationRes = (fp_OnGroupInvitationRes)GetProcAddress(hDllHandle,"OnGroupInvitationRes");
		if (NULL == g_fpOnGroupInvitationRes)
		{
			ERROR_LOG() << "GetProcAddress \"OnGroupInvitationRes\" failed.";
			return UC_Fail;
		}
	}

	int iRet = (*g_fpOnGroupInvitationRes)(fpGroupInvitationRes);
	return iRet;

}

int UCSDK_CALL OnLeaveFromFixedGroup(const UCLeaveFromFixedGroup fpLeaveFromFixedGroup)
{
	if (NULL == g_fpOnLeaveFromFixedGroup)
	{
		eSDKClientPlatformExecute *peSDKClient = eSDKClientPlatformExecute::Instance();
		if (NULL == peSDKClient)
		{
			ERROR_LOG() << "Get eSDKClientPlatformExecute instance failed.";
			return UC_Fail;
		}

		HINSTANCE hDllHandle = peSDKClient->getServiceHandleByName("UCSDK");
		if (NULL == hDllHandle)
		{
			ERROR_LOG() << "getServiceHandleByName failed.";
			return UC_Fail;
		}

		g_fpOnLeaveFromFixedGroup = (fp_OnLeaveFromFixedGroup)GetProcAddress(hDllHandle,"OnLeaveFromFixedGroup");
		if (NULL == g_fpOnLeaveFromFixedGroup)
		{
			ERROR_LOG() << "GetProcAddress \"OnLeaveFromFixedGroup\" failed.";
			return UC_Fail;
		}
	}

	int iRet = (*g_fpOnLeaveFromFixedGroup)(fpLeaveFromFixedGroup);
	return iRet;

}

int UCSDK_CALL OnJoinFixedGroupRequest(const UCJoinFixedGroupRequest fpJoinFixedGroupRequest)
{
	if (NULL == g_fpOnJoinFixedGroupRequest)
	{
		eSDKClientPlatformExecute *peSDKClient = eSDKClientPlatformExecute::Instance();
		if (NULL == peSDKClient)
		{
			ERROR_LOG() << "Get eSDKClientPlatformExecute instance failed.";
			return UC_Fail;
		}

		HINSTANCE hDllHandle = peSDKClient->getServiceHandleByName("UCSDK");
		if (NULL == hDllHandle)
		{
			ERROR_LOG() << "getServiceHandleByName failed.";
			return UC_Fail;
		}

		g_fpOnJoinFixedGroupRequest = (fp_OnJoinFixedGroupRequest)GetProcAddress(hDllHandle,"OnJoinFixedGroupRequest");
		if (NULL == g_fpOnJoinFixedGroupRequest)
		{
			ERROR_LOG() << "GetProcAddress \"OnJoinFixedGroupRequest\" failed.";
			return UC_Fail;
		}
	}

	int iRet = (*g_fpOnJoinFixedGroupRequest)(fpJoinFixedGroupRequest);
	return iRet;

}

int UCSDK_CALL OnJoinFixedGroupRes(const UCJoinFixedGroupRes fpJoinFixedGroupRes)
{
	if (NULL == g_fpOnJoinFixedGroupRes)
	{
		eSDKClientPlatformExecute *peSDKClient = eSDKClientPlatformExecute::Instance();
		if (NULL == peSDKClient)
		{
			ERROR_LOG() << "Get eSDKClientPlatformExecute instance failed.";
			return UC_Fail;
		}

		HINSTANCE hDllHandle = peSDKClient->getServiceHandleByName("UCSDK");
		if (NULL == hDllHandle)
		{
			ERROR_LOG() << "getServiceHandleByName failed.";
			return UC_Fail;
		}

		g_fpOnJoinFixedGroupRes = (fp_OnJoinFixedGroupRes)GetProcAddress(hDllHandle,"OnJoinFixedGroupRes");
		if (NULL == g_fpOnJoinFixedGroupRes)
		{
			ERROR_LOG() << "GetProcAddress \"OnJoinFixedGroupRes\" failed.";
			return UC_Fail;
		}
	}

	int iRet = (*g_fpOnJoinFixedGroupRes)(fpJoinFixedGroupRes);
	return iRet;

}

int UCSDK_CALL OnMemberAdded(const UCMemberAdded fpMemberAdded)
{
	if (NULL == g_fpOnMemberAdded)
	{
		eSDKClientPlatformExecute *peSDKClient = eSDKClientPlatformExecute::Instance();
		if (NULL == peSDKClient)
		{
			ERROR_LOG() << "Get eSDKClientPlatformExecute instance failed.";
			return UC_Fail;
		}

		HINSTANCE hDllHandle = peSDKClient->getServiceHandleByName("UCSDK");
		if (NULL == hDllHandle)
		{
			ERROR_LOG() << "getServiceHandleByName failed.";
			return UC_Fail;
		}

		g_fpOnMemberAdded = (fp_OnMemberAdded)GetProcAddress(hDllHandle,"OnMemberAdded");
		if (NULL == g_fpOnMemberAdded)
		{
			ERROR_LOG() << "GetProcAddress \"OnMemberAdded\" failed.";
			return UC_Fail;
		}
	}

	int iRet = (*g_fpOnMemberAdded)(fpMemberAdded);
	return iRet;

}

int UCSDK_CALL OnMemberRemoved(const UCMemberRemoved fpMemberRemoved)
{
	if (NULL == g_fpOnMemberRemoved)
	{
		eSDKClientPlatformExecute *peSDKClient = eSDKClientPlatformExecute::Instance();
		if (NULL == peSDKClient)
		{
			ERROR_LOG() << "Get eSDKClientPlatformExecute instance failed.";
			return UC_Fail;
		}

		HINSTANCE hDllHandle = peSDKClient->getServiceHandleByName("UCSDK");
		if (NULL == hDllHandle)
		{
			ERROR_LOG() << "getServiceHandleByName failed.";
			return UC_Fail;
		}

		g_fpOnMemberRemoved = (fp_OnMemberRemoved)GetProcAddress(hDllHandle,"OnMemberRemoved");
		if (NULL == g_fpOnMemberRemoved)
		{
			ERROR_LOG() << "GetProcAddress \"OnMemberRemoved\" failed.";
			return UC_Fail;
		}
	}

	int iRet = (*g_fpOnMemberRemoved)(fpMemberRemoved);
	return iRet;

}

int UCSDK_CALL OnMemberFlowChanged(const UCMemberFlowChanged fpMemberFlowChanged)
{
	if (NULL == g_fpOnMemberFlowChanged)
	{
		eSDKClientPlatformExecute *peSDKClient = eSDKClientPlatformExecute::Instance();
		if (NULL == peSDKClient)
		{
			ERROR_LOG() << "Get eSDKClientPlatformExecute instance failed.";
			return UC_Fail;
		}

		HINSTANCE hDllHandle = peSDKClient->getServiceHandleByName("UCSDK");
		if (NULL == hDllHandle)
		{
			ERROR_LOG() << "getServiceHandleByName failed.";
			return UC_Fail;
		}

		g_fpOnMemberFlowChanged = (fp_OnMemberFlowChanged)GetProcAddress(hDllHandle,"OnMemberFlowChanged");
		if (NULL == g_fpOnMemberFlowChanged)
		{
			ERROR_LOG() << "GetProcAddress \"OnMemberFlowChanged\" failed.";
			return UC_Fail;
		}
	}

	int iRet = (*g_fpOnMemberFlowChanged)(fpMemberFlowChanged);
	return iRet;

}

int UCSDK_CALL OnFixedGroupInfoChanged(const UCFixedGroupInfoChanged fpFixedGroupInfoChanged)
{
	if (NULL == g_fpOnFixedGroupInfoChanged)
	{
		eSDKClientPlatformExecute *peSDKClient = eSDKClientPlatformExecute::Instance();
		if (NULL == peSDKClient)
		{
			ERROR_LOG() << "Get eSDKClientPlatformExecute instance failed.";
			return UC_Fail;
		}

		HINSTANCE hDllHandle = peSDKClient->getServiceHandleByName("UCSDK");
		if (NULL == hDllHandle)
		{
			ERROR_LOG() << "getServiceHandleByName failed.";
			return UC_Fail;
		}

		g_fpOnFixedGroupInfoChanged = (fp_OnFixedGroupInfoChanged)GetProcAddress(hDllHandle,"OnFixedGroupInfoChanged");
		if (NULL == g_fpOnFixedGroupInfoChanged)
		{
			ERROR_LOG() << "GetProcAddress \"OnFixedGroupInfoChanged\" failed.";
			return UC_Fail;
		}
	}

	int iRet = (*g_fpOnFixedGroupInfoChanged)(fpFixedGroupInfoChanged);
	return iRet;

}

int UCSDK_CALL OnNewFileRercved(const UCNewFileRercved fpNewFileRercved)
{
	if (NULL == g_fpOnNewFileRercved)
	{
		eSDKClientPlatformExecute *peSDKClient = eSDKClientPlatformExecute::Instance();
		if (NULL == peSDKClient)
		{
			ERROR_LOG() << "Get eSDKClientPlatformExecute instance failed.";
			return UC_Fail;
		}

		HINSTANCE hDllHandle = peSDKClient->getServiceHandleByName("UCSDK");
		if (NULL == hDllHandle)
		{
			ERROR_LOG() << "getServiceHandleByName failed.";
			return UC_Fail;
		}

		g_fpOnNewFileRercved = (fp_OnNewFileRercved)GetProcAddress(hDllHandle,"OnNewFileRercved");
		if (NULL == g_fpOnNewFileRercved)
		{
			ERROR_LOG() << "GetProcAddress \"OnNewFileRercved\" failed.";
			return UC_Fail;
		}
	}

	int iRet = (*g_fpOnNewFileRercved)(fpNewFileRercved);
	return iRet;

}

int UCSDK_CALL OnFileAccept(const UCFileAccept fpFileAccept)
{
	if (NULL == g_fpOnFileAccept)
	{
		eSDKClientPlatformExecute *peSDKClient = eSDKClientPlatformExecute::Instance();
		if (NULL == peSDKClient)
		{
			ERROR_LOG() << "Get eSDKClientPlatformExecute instance failed.";
			return UC_Fail;
		}

		HINSTANCE hDllHandle = peSDKClient->getServiceHandleByName("UCSDK");
		if (NULL == hDllHandle)
		{
			ERROR_LOG() << "getServiceHandleByName failed.";
			return UC_Fail;
		}

		g_fpOnFileAccept = (fp_OnFileAccept)GetProcAddress(hDllHandle,"OnFileAccept");
		if (NULL == g_fpOnFileAccept)
		{
			ERROR_LOG() << "GetProcAddress \"OnFileAccept\" failed.";
			return UC_Fail;
		}
	}

	int iRet = (*g_fpOnFileAccept)(fpFileAccept);
	return iRet;

}

int UCSDK_CALL OnFileCancel(const UCFileCancel fpFileCancel)
{
	if (NULL == g_fpOnFileCancel)
	{
		eSDKClientPlatformExecute *peSDKClient = eSDKClientPlatformExecute::Instance();
		if (NULL == peSDKClient)
		{
			ERROR_LOG() << "Get eSDKClientPlatformExecute instance failed.";
			return UC_Fail;
		}

		HINSTANCE hDllHandle = peSDKClient->getServiceHandleByName("UCSDK");
		if (NULL == hDllHandle)
		{
			ERROR_LOG() << "getServiceHandleByName failed.";
			return UC_Fail;
		}

		g_fpOnFileCancel = (fp_OnFileCancel)GetProcAddress(hDllHandle,"OnFileCancel");
		if (NULL == g_fpOnFileCancel)
		{
			ERROR_LOG() << "GetProcAddress \"OnFileCancel\" failed.";
			return UC_Fail;
		}
	}

	int iRet = (*g_fpOnFileCancel)(fpFileCancel);
	return iRet;

}

int UCSDK_CALL OnFileProgress(const UCFileProgress fpFileProgress)
{
	if (NULL == g_fpOnFileProgress)
	{
		eSDKClientPlatformExecute *peSDKClient = eSDKClientPlatformExecute::Instance();
		if (NULL == peSDKClient)
		{
			ERROR_LOG() << "Get eSDKClientPlatformExecute instance failed.";
			return UC_Fail;
		}

		HINSTANCE hDllHandle = peSDKClient->getServiceHandleByName("UCSDK");
		if (NULL == hDllHandle)
		{
			ERROR_LOG() << "getServiceHandleByName failed.";
			return UC_Fail;
		}

		g_fpOnFileProgress = (fp_OnFileProgress)GetProcAddress(hDllHandle,"OnFileProgress");
		if (NULL == g_fpOnFileProgress)
		{
			ERROR_LOG() << "GetProcAddress \"OnFileProgress\" failed.";
			return UC_Fail;
		}
	}

	int iRet = (*g_fpOnFileProgress)(fpFileProgress);
	return iRet;

}

int UCSDK_CALL Init()
{
	if (NULL == g_fpInit)
	{
		eSDKClientPlatformExecute *peSDKClient = eSDKClientPlatformExecute::Instance();
		if (NULL == peSDKClient)
		{
			ERROR_LOG() << "Get eSDKClientPlatformExecute instance failed.";
			return UC_Fail;
		}

		HINSTANCE hDllHandle = peSDKClient->getServiceHandleByName("UCSDK");
		if (NULL == hDllHandle)
		{
			ERROR_LOG() << "getServiceHandleByName failed.";
			return UC_Fail;
		}

		g_fpInit = (fp_Init)GetProcAddress(hDllHandle,"Init");
		if (NULL == g_fpInit)
		{
			ERROR_LOG() << "GetProcAddress \"Init\" failed.";
			return UC_Fail;
		}
	}

	int iRet = (*g_fpInit)();
	return iRet;

}

int UCSDK_CALL UnInit()
{
	if (NULL == g_fpUnInit)
	{
		eSDKClientPlatformExecute *peSDKClient = eSDKClientPlatformExecute::Instance();
		if (NULL == peSDKClient)
		{
			ERROR_LOG() << "Get eSDKClientPlatformExecute instance failed.";
			return UC_Fail;
		}

		HINSTANCE hDllHandle = peSDKClient->getServiceHandleByName("UCSDK");
		if (NULL == hDllHandle)
		{
			ERROR_LOG() << "getServiceHandleByName failed.";
			return UC_Fail;
		}

		g_fpUnInit = (fp_UnInit)GetProcAddress(hDllHandle,"UnInit");
		if (NULL == g_fpUnInit)
		{
			ERROR_LOG() << "GetProcAddress \"UnInit\" failed.";
			return UC_Fail;
		}
	}

	int iRet = (*g_fpUnInit)();
	return iRet;

}

int UCSDK_CALL LoginByToken(const char* token)
{
	if (NULL == g_fpLoginByToken)
	{
		eSDKClientPlatformExecute *peSDKClient = eSDKClientPlatformExecute::Instance();
		if (NULL == peSDKClient)
		{
			ERROR_LOG() << "Get eSDKClientPlatformExecute instance failed.";
			return UC_Fail;
		}

		HINSTANCE hDllHandle = peSDKClient->getServiceHandleByName("UCSDK");
		if (NULL == hDllHandle)
		{
			ERROR_LOG() << "getServiceHandleByName failed.";
			return UC_Fail;
		}

		g_fpLoginByToken = (fp_LoginByToken)GetProcAddress(hDllHandle,"LoginByToken");
		if (NULL == g_fpLoginByToken)
		{
			ERROR_LOG() << "GetProcAddress \"LoginByToken\" failed.";
			return UC_Fail;
		}
	}

	int iRet = (*g_fpLoginByToken)(token);
	return iRet;

}

int UCSDK_CALL LoginByPasswd(const char* account, const char* passwd)
{
	if (NULL == g_fpLoginByPasswd)
	{
		eSDKClientPlatformExecute *peSDKClient = eSDKClientPlatformExecute::Instance();
		if (NULL == peSDKClient)
		{
			ERROR_LOG() << "Get eSDKClientPlatformExecute instance failed.";
			return UC_Fail;
		}

		HINSTANCE hDllHandle = peSDKClient->getServiceHandleByName("UCSDK");
		if (NULL == hDllHandle)
		{
			ERROR_LOG() << "getServiceHandleByName failed.";
			return UC_Fail;
		}

		g_fpLoginByPasswd = (fp_LoginByPasswd)GetProcAddress(hDllHandle,"LoginByPasswd");
		if (NULL == g_fpLoginByPasswd)
		{
			ERROR_LOG() << "GetProcAddress \"LoginByPasswd\" failed.";
			return UC_Fail;
		}
	}

	int iRet = (*g_fpLoginByPasswd)(account, passwd);
	return iRet;

}

int UCSDK_CALL Logout()
{
	if (NULL == g_fpLogout)
	{
		eSDKClientPlatformExecute *peSDKClient = eSDKClientPlatformExecute::Instance();
		if (NULL == peSDKClient)
		{
			ERROR_LOG() << "Get eSDKClientPlatformExecute instance failed.";
			return UC_Fail;
		}

		HINSTANCE hDllHandle = peSDKClient->getServiceHandleByName("UCSDK");
		if (NULL == hDllHandle)
		{
			ERROR_LOG() << "getServiceHandleByName failed.";
			return UC_Fail;
		}

		g_fpLogout = (fp_Logout)GetProcAddress(hDllHandle,"Logout");
		if (NULL == g_fpLogout)
		{
			ERROR_LOG() << "GetProcAddress \"Logout\" failed.";
			return UC_Fail;
		}
	}

	int iRet = (*g_fpLogout)();
	return iRet;

}

int UCSDK_CALL Config(const char* srvUrl)
{
	if (NULL == g_fpConfig)
	{
		eSDKClientPlatformExecute *peSDKClient = eSDKClientPlatformExecute::Instance();
		if (NULL == peSDKClient)
		{
			ERROR_LOG() << "Get eSDKClientPlatformExecute instance failed.";
			return UC_Fail;
		}

		HINSTANCE hDllHandle = peSDKClient->getServiceHandleByName("UCSDK");
		if (NULL == hDllHandle)
		{
			ERROR_LOG() << "getServiceHandleByName failed.";
			return UC_Fail;
		}

		g_fpConfig = (fp_Config)GetProcAddress(hDllHandle,"Config");
		if (NULL == g_fpConfig)
		{
			ERROR_LOG() << "GetProcAddress \"Config\" failed.";
			return UC_Fail;
		}
	}

	int iRet = (*g_fpConfig)(srvUrl);
	return iRet;

}

int UCSDK_CALL SetLang(const char* lang)
{
	if (NULL == g_fpSetLang)
	{
		eSDKClientPlatformExecute *peSDKClient = eSDKClientPlatformExecute::Instance();
		if (NULL == peSDKClient)
		{
			ERROR_LOG() << "Get eSDKClientPlatformExecute instance failed.";
			return UC_Fail;
		}

		HINSTANCE hDllHandle = peSDKClient->getServiceHandleByName("UCSDK");
		if (NULL == hDllHandle)
		{
			ERROR_LOG() << "getServiceHandleByName failed.";
			return UC_Fail;
		}

		g_fpSetLang = (fp_SetLang)GetProcAddress(hDllHandle,"SetLang");
		if (NULL == g_fpSetLang)
		{
			ERROR_LOG() << "GetProcAddress \"SetLang\" failed.";
			return UC_Fail;
		}
	}

	int iRet = (*g_fpSetLang)(lang);
	return iRet;

}

int UCSDK_CALL MakeCall(const UCContact* member, int iType, const UCVideoWindow* localWnd,
						const UCVideoWindow* remoteWnd, char convId[CONVID_LENGTH])
{
	if (NULL == g_fpMakeCall)
	{
		eSDKClientPlatformExecute *peSDKClient = eSDKClientPlatformExecute::Instance();
		if (NULL == peSDKClient)
		{
			ERROR_LOG() << "Get eSDKClientPlatformExecute instance failed.";
			return UC_Fail;
		}

		HINSTANCE hDllHandle = peSDKClient->getServiceHandleByName("UCSDK");
		if (NULL == hDllHandle)
		{
			ERROR_LOG() << "getServiceHandleByName failed.";
			return UC_Fail;
		}

		g_fpMakeCall = (fp_MakeCall)GetProcAddress(hDllHandle,"MakeCall");
		if (NULL == g_fpMakeCall)
		{
			ERROR_LOG() << "GetProcAddress \"MakeCall\" failed.";
			return UC_Fail;
		}
	}

	int iRet = (*g_fpMakeCall)(member, iType, localWnd, remoteWnd, convId);
	return iRet;

}

int UCSDK_CALL Accept(const char* convId, int iType, const UCVideoWindow* localWnd, const UCVideoWindow* remoteWnd)
{
	if (NULL == g_fpAccept)
	{
		eSDKClientPlatformExecute *peSDKClient = eSDKClientPlatformExecute::Instance();
		if (NULL == peSDKClient)
		{
			ERROR_LOG() << "Get eSDKClientPlatformExecute instance failed.";
			return UC_Fail;
		}

		HINSTANCE hDllHandle = peSDKClient->getServiceHandleByName("UCSDK");
		if (NULL == hDllHandle)
		{
			ERROR_LOG() << "getServiceHandleByName failed.";
			return UC_Fail;
		}

		g_fpAccept = (fp_Accept)GetProcAddress(hDllHandle,"Accept");
		if (NULL == g_fpAccept)
		{
			ERROR_LOG() << "GetProcAddress \"Accept\" failed.";
			return UC_Fail;
		}
	}

	int iRet = (*g_fpAccept)(convId, iType, localWnd, remoteWnd);
	return iRet;

}

int UCSDK_CALL Reject(const char* convId, int iType)
{
	if (NULL == g_fpReject)
	{
		eSDKClientPlatformExecute *peSDKClient = eSDKClientPlatformExecute::Instance();
		if (NULL == peSDKClient)
		{
			ERROR_LOG() << "Get eSDKClientPlatformExecute instance failed.";
			return UC_Fail;
		}

		HINSTANCE hDllHandle = peSDKClient->getServiceHandleByName("UCSDK");
		if (NULL == hDllHandle)
		{
			ERROR_LOG() << "getServiceHandleByName failed.";
			return UC_Fail;
		}

		g_fpReject = (fp_Reject)GetProcAddress(hDllHandle,"Reject");
		if (NULL == g_fpReject)
		{
			ERROR_LOG() << "GetProcAddress \"Reject\" failed.";
			return UC_Fail;
		}
	}

	int iRet = (*g_fpReject)(convId, iType);
	return iRet;

}

int UCSDK_CALL Hangup(const char* convId, int iType)
{
	if (NULL == g_fpHangup)
	{
		eSDKClientPlatformExecute *peSDKClient = eSDKClientPlatformExecute::Instance();
		if (NULL == peSDKClient)
		{
			ERROR_LOG() << "Get eSDKClientPlatformExecute instance failed.";
			return UC_Fail;
		}

		HINSTANCE hDllHandle = peSDKClient->getServiceHandleByName("UCSDK");
		if (NULL == hDllHandle)
		{
			ERROR_LOG() << "getServiceHandleByName failed.";
			return UC_Fail;
		}

		g_fpHangup = (fp_Hangup)GetProcAddress(hDllHandle,"Hangup");
		if (NULL == g_fpHangup)
		{
			ERROR_LOG() << "GetProcAddress \"Hangup\" failed.";
			return UC_Fail;
		}
	}

	int iRet = (*g_fpHangup)(convId, iType);
	return iRet;

}

int UCSDK_CALL Hold(const char* convId)
{
	if (NULL == g_fpHold)
	{
		eSDKClientPlatformExecute *peSDKClient = eSDKClientPlatformExecute::Instance();
		if (NULL == peSDKClient)
		{
			ERROR_LOG() << "Get eSDKClientPlatformExecute instance failed.";
			return UC_Fail;
		}

		HINSTANCE hDllHandle = peSDKClient->getServiceHandleByName("UCSDK");
		if (NULL == hDllHandle)
		{
			ERROR_LOG() << "getServiceHandleByName failed.";
			return UC_Fail;
		}

		g_fpHold = (fp_Hold)GetProcAddress(hDllHandle,"Hold");
		if (NULL == g_fpHold)
		{
			ERROR_LOG() << "GetProcAddress \"Hold\" failed.";
			return UC_Fail;
		}
	}

	int iRet = (*g_fpHold)(convId);
	return iRet;

}

int UCSDK_CALL Resume(const char* convId)
{
	if (NULL == g_fpResume)
	{
		eSDKClientPlatformExecute *peSDKClient = eSDKClientPlatformExecute::Instance();
		if (NULL == peSDKClient)
		{
			ERROR_LOG() << "Get eSDKClientPlatformExecute instance failed.";
			return UC_Fail;
		}

		HINSTANCE hDllHandle = peSDKClient->getServiceHandleByName("UCSDK");
		if (NULL == hDllHandle)
		{
			ERROR_LOG() << "getServiceHandleByName failed.";
			return UC_Fail;
		}

		g_fpResume = (fp_Resume)GetProcAddress(hDllHandle,"Resume");
		if (NULL == g_fpResume)
		{
			ERROR_LOG() << "GetProcAddress \"Resume\" failed.";
			return UC_Fail;
		}
	}

	int iRet = (*g_fpResume)(convId);
	return iRet;

}

int UCSDK_CALL Forward(const char* convId, const char* account)
{
	if (NULL == g_fpForward)
	{
		eSDKClientPlatformExecute *peSDKClient = eSDKClientPlatformExecute::Instance();
		if (NULL == peSDKClient)
		{
			ERROR_LOG() << "Get eSDKClientPlatformExecute instance failed.";
			return UC_Fail;
		}

		HINSTANCE hDllHandle = peSDKClient->getServiceHandleByName("UCSDK");
		if (NULL == hDllHandle)
		{
			ERROR_LOG() << "getServiceHandleByName failed.";
			return UC_Fail;
		}

		g_fpForward = (fp_Forward)GetProcAddress(hDllHandle,"Forward");
		if (NULL == g_fpForward)
		{
			ERROR_LOG() << "GetProcAddress \"Forward\" failed.";
			return UC_Fail;
		}
	}

	int iRet = (*g_fpForward)(convId, account);
	return iRet;

}

int UCSDK_CALL StartRecord(const char* convId, const char* filePath)
{
	if (NULL == g_fpStartRecord)
	{
		eSDKClientPlatformExecute *peSDKClient = eSDKClientPlatformExecute::Instance();
		if (NULL == peSDKClient)
		{
			ERROR_LOG() << "Get eSDKClientPlatformExecute instance failed.";
			return UC_Fail;
		}

		HINSTANCE hDllHandle = peSDKClient->getServiceHandleByName("UCSDK");
		if (NULL == hDllHandle)
		{
			ERROR_LOG() << "getServiceHandleByName failed.";
			return UC_Fail;
		}

		g_fpStartRecord = (fp_StartRecord)GetProcAddress(hDllHandle,"StartRecord");
		if (NULL == g_fpStartRecord)
		{
			ERROR_LOG() << "GetProcAddress \"StartRecord\" failed.";
			return UC_Fail;
		}
	}

	int iRet = (*g_fpStartRecord)(convId, filePath);
	return iRet;

}

int UCSDK_CALL StopRecord(const char* convId)
{
	if (NULL == g_fpStopRecord)
	{
		eSDKClientPlatformExecute *peSDKClient = eSDKClientPlatformExecute::Instance();
		if (NULL == peSDKClient)
		{
			ERROR_LOG() << "Get eSDKClientPlatformExecute instance failed.";
			return UC_Fail;
		}

		HINSTANCE hDllHandle = peSDKClient->getServiceHandleByName("UCSDK");
		if (NULL == hDllHandle)
		{
			ERROR_LOG() << "getServiceHandleByName failed.";
			return UC_Fail;
		}

		g_fpStopRecord = (fp_StopRecord)GetProcAddress(hDllHandle,"StopRecord");
		if (NULL == g_fpStopRecord)
		{
			ERROR_LOG() << "GetProcAddress \"StopRecord\" failed.";
			return UC_Fail;
		}
	}

	int iRet = (*g_fpStopRecord)(convId);
	return iRet;

}

int UCSDK_CALL MuteVoIP(int iType)
{
	if (NULL == g_fpMuteVoIP)
	{
		eSDKClientPlatformExecute *peSDKClient = eSDKClientPlatformExecute::Instance();
		if (NULL == peSDKClient)
		{
			ERROR_LOG() << "Get eSDKClientPlatformExecute instance failed.";
			return UC_Fail;
		}

		HINSTANCE hDllHandle = peSDKClient->getServiceHandleByName("UCSDK");
		if (NULL == hDllHandle)
		{
			ERROR_LOG() << "getServiceHandleByName failed.";
			return UC_Fail;
		}

		g_fpMuteVoIP = (fp_MuteVoIP)GetProcAddress(hDllHandle,"MuteVoIP");
		if (NULL == g_fpMuteVoIP)
		{
			ERROR_LOG() << "GetProcAddress \"MuteVoIP\" failed.";
			return UC_Fail;
		}
	}

	int iRet = (*g_fpMuteVoIP)(iType);
	return iRet;

}

int UCSDK_CALL UnMuteVoIP(int iType)
{
	if (NULL == g_fpUnMuteVoIP)
	{
		eSDKClientPlatformExecute *peSDKClient = eSDKClientPlatformExecute::Instance();
		if (NULL == peSDKClient)
		{
			ERROR_LOG() << "Get eSDKClientPlatformExecute instance failed.";
			return UC_Fail;
		}

		HINSTANCE hDllHandle = peSDKClient->getServiceHandleByName("UCSDK");
		if (NULL == hDllHandle)
		{
			ERROR_LOG() << "getServiceHandleByName failed.";
			return UC_Fail;
		}

		g_fpUnMuteVoIP = (fp_UnMuteVoIP)GetProcAddress(hDllHandle,"UnMuteVoIP");
		if (NULL == g_fpUnMuteVoIP)
		{
			ERROR_LOG() << "GetProcAddress \"UnMuteVoIP\" failed.";
			return UC_Fail;
		}
	}

	int iRet = (*g_fpUnMuteVoIP)(iType);
	return iRet;

}

void UninitAllPtr(void)
{
	g_fpGetAllContactlist = NULL;
	g_fpGetContactByAccount = NULL;
	g_fpGetContactById = NULL;
	g_fpGetContactByPhoneNum = NULL;
	g_fpGetContactByUri = NULL;
	g_fpHasContact = NULL;
	g_fpRefreshContactByAccount = NULL;
	g_fpRefreshContactById = NULL;
	g_fpRefreshContactByUri = NULL;
	g_fpRemoveContactById = NULL;
	g_fpSearchContact = NULL;
	g_fpModify = NULL; 
	g_fpGetHeadImagePath = NULL;
	g_fpMoveToGroup = NULL;
	g_fpAddToGroup = NULL;
	g_fpRemoveFromGroup = NULL;
	g_fpCanStartSession = NULL;
	g_fpCanMoveToGroup = NULL;
	g_fpGetCustomGroups = NULL;
	g_fpIsFavourite = NULL;
	g_fpAddFixedGroup = NULL;
	g_fpGetFixedGroupByID = NULL;
	g_fpGetFixedGroupByUri = NULL;
	g_fpRemoveFixedGroup = NULL;
	g_fpRefreshFixedGrouplist = NULL;
	g_fpGetFixedGrouplist = NULL;
	g_fpSearchFixedGroup = NULL;
	g_fpAddCustomGroup = NULL;
	g_fpAddFavoriteGroup = NULL; 
	g_fpGetCustomGroupById = NULL; 
	g_fpGetCustomGrouplist = NULL; 
	g_fpRemoveCustomGroup = NULL;
	g_fpRemoveFavoriteGroup = NULL;
	g_fpAddContactToFavoriteGroup = NULL;
	g_fpRemoveContactFromFavoriteGroup = NULL;
	g_fpRenameToFavoriteGroup = NULL;
	g_fpGetContactlistFromFavoriteGroup = NULL;
	g_fpAddContactToCustomGroup = NULL;
	g_fpRemoveContactFromCustomGroup = NULL;
	g_fpRenameToCustomGroup = NULL;
	g_fpGetContactlistFromCustomGroup = NULL;
	g_fpMoveUp = NULL;
	g_fpMoveDown = NULL;
	g_fpAddContactToFixedGroup = NULL;
	g_fpRemoveContactFromFixedGroup = NULL; 
	g_fpRenameToFixedGroup = NULL;
	g_fpGetContactlistFromFixedGroup = NULL;
	g_fpChangeGroupInfo = NULL;
	g_fpChangeGroupOwner = NULL;
	g_fpRefreshContactList = NULL;
	g_fpRefreshGroup = NULL;
	g_fpAcceptInvitation = NULL;
	g_fpRejectInvitation = NULL;
	g_fpAcceptJoinReq = NULL;
	g_fpRejectJoinReq = NULL;
	g_fpSendIMMessage = NULL;
	g_fpCloseConversation = NULL;
	g_fpAcceptFile = NULL;
	g_fpCancelFile = NULL;   
	g_fpRejectFile = NULL;   
	g_fpTransferFile = NULL;
	g_fpMakeMeetingGroup = NULL;
	g_fpStartMeeting = NULL; 
	g_fpAcceptMeeting = NULL;
	g_fpAddParticipant = NULL;
	g_fpConnectParticipant = NULL;
	g_fpRemoveParticipant = NULL;
	g_fpKickParticipant = NULL;
	g_fpMuteMeeting = NULL;
	g_fpUnMuteMeeting = NULL;
	g_fpGetBookConfList = NULL;
	g_fpJoinMeeting = NULL;
	g_fpLeaveMeeting = NULL;
	g_fpPublishSelfInformation = NULL;
	g_fpGetContactStatus = NULL;
	g_fpOnClientSignInNotify = NULL;
	g_fpOnStatusChanged = NULL;
	g_fpOnIncreContactsChanged = NULL;
	g_fpOnAVSessAdded = NULL;
	g_fpOnAVSessionConnected = NULL;
	g_fpOnAVSessionClosed = NULL;
	g_fpOnConvMemberStatusChanged = NULL;
	g_fpOnConvMemAllowSpeak = NULL;
	g_fpOnConvMemForbidSpeak = NULL;
	g_fpOnConvMemCurSpeaker = NULL;
	g_fpOnConvGroupMemberChanged = NULL;
	g_fpOnReceivedIMMessage = NULL;
	g_fpOnInstantSessRemoved = NULL;
	g_fpOnInstantSessAdded = NULL;
	g_fpOnSysMsgRecved = NULL;
	g_fpOnGroupInvitation = NULL;
	g_fpOnGroupInvitationRes = NULL;
	g_fpOnLeaveFromFixedGroup = NULL;
	g_fpOnJoinFixedGroupRequest = NULL;
	g_fpOnJoinFixedGroupRes = NULL;
	g_fpOnMemberAdded = NULL; 
	g_fpOnMemberRemoved = NULL;
	g_fpOnMemberFlowChanged = NULL;
	g_fpOnFixedGroupInfoChanged = NULL;
	g_fpOnNewFileRercved = NULL;
	g_fpOnFileAccept = NULL;
	g_fpOnFileCancel = NULL;
	g_fpOnFileProgress = NULL;
	g_fpInit = NULL;                           
	g_fpUnInit = NULL;                         
	g_fpLoginByToken = NULL;  
	g_fpLoginByPasswd = NULL;
	g_fpLogout = NULL;                         
	g_fpConfig = NULL;       
	g_fpSetLang = NULL;
	g_fpMakeCall = NULL;
	g_fpAccept = NULL;
	g_fpReject = NULL;
	g_fpHangup = NULL;
	g_fpHold = NULL;         
	g_fpResume = NULL;       
	g_fpForward = NULL; 
	g_fpStartRecord = NULL;
	g_fpStopRecord = NULL;   
	g_fpMuteVoIP = NULL;              
	g_fpUnMuteVoIP = NULL;  
}
