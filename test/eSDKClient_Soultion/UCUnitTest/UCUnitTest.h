#ifndef __UC_UNIT_TEST_H__
#define __UC_UNIT_TEST_H__

#ifndef UCSDK_CALL
#define UCSDK_CALL CALLBACK
#endif

#ifndef ESDKCLIENTPLATFORM_CALL
#define ESDKCLIENTPLATFORM_CALL CALLBACK
#endif

//////////////////////////////////////////////////////////////////////////
typedef int (ESDKCLIENTPLATFORM_CALL *fp_eSDKClientPlatform_Init)(void);
typedef int (ESDKCLIENTPLATFORM_CALL *fp_eSDKClientPlatform_Uninit)(void);
typedef int (ESDKCLIENTPLATFORM_CALL *fp_eSDKClientPlatform_LoginByPassword)(const char* name, const char* password, const int type);
typedef int (ESDKCLIENTPLATFORM_CALL *fp_eSDKClientPlatform_Logout)(void);

//////////////////////////////////////////////////////////////////////////
typedef int (UCSDK_CALL *fp_GetAllContactlist)(int iFrom, int iTo, UCContactList* memberList);
typedef int (UCSDK_CALL *fp_GetContactByAccount)(const char* pAcc, UCContact* member);
typedef int (UCSDK_CALL *fp_GetContactById)(const char* pId, UCContact* member);
typedef int (UCSDK_CALL *fp_GetContactByPhoneNum)(const char* pPhoneNum, UCContact* member);
typedef int (UCSDK_CALL *fp_GetContactByUri)(const char* pUri, UCContact* member);
typedef int (UCSDK_CALL *fp_HasContact)(const char* pUri);
typedef int (UCSDK_CALL *fp_RefreshContactByAccount)(const char* pAcc, UCContact* member);
typedef int (UCSDK_CALL *fp_RefreshContactById)(const char* pId, UCContact* member);
typedef int (UCSDK_CALL *fp_RefreshContactByUri)(const char* pUri, UCContact* member);
typedef int (UCSDK_CALL *fp_RemoveContactById)(const char* pId);
typedef int (UCSDK_CALL *fp_SearchContact)(const char* condition, const char* deptid,
										   int querysubdept, int offset, int count, int ordertype,
										   int* recamount, UCContactList* memberList);
typedef int (UCSDK_CALL *fp_Modify)(const UCContact* member);
typedef int (UCSDK_CALL *fp_GetHeadImagePath)(const UCContact* member, char path[IMAGE_LENGTH]);
typedef int (UCSDK_CALL *fp_MoveToGroup)(const UCContact* member, const UCGroup* _src, const UCGroup* _target);
typedef int (UCSDK_CALL *fp_AddToGroup)(const UCContact* member, const UCGroup* _target);
typedef int (UCSDK_CALL *fp_RemoveFromGroup)(const UCContact* member, const UCGroup* _target);
typedef int (UCSDK_CALL *fp_CanStartSession)(const UCContact* member, int _type);
typedef int (UCSDK_CALL *fp_CanMoveToGroup)(const UCContact* member, const UCGroup* _src, const UCGroup* _target);
typedef int (UCSDK_CALL *fp_GetCustomGroups)(const UCContact* member, int iFrom, int iTo, UCCustomGroupList* _groups);
typedef int (UCSDK_CALL *fp_IsFavourite)(const UCContact* member);

//UCGroup
typedef int (UCSDK_CALL *fp_AddFixedGroup)(UCFixedGroup* group);
typedef int (UCSDK_CALL *fp_GetFixedGroupByID)(const char* pGId, UCFixedGroup* group);
typedef int (UCSDK_CALL *fp_GetFixedGroupByUri)(const char* pGUri, UCFixedGroup* group);
typedef int (UCSDK_CALL *fp_RemoveFixedGroup)(const UCFixedGroup* group);
typedef int (UCSDK_CALL *fp_RefreshFixedGrouplist)(int iFrom, int iTo, UCFixedGroupList* groupList);
typedef int (UCSDK_CALL *fp_GetFixedGrouplist)(int iFrom, int iTo, UCFixedGroupList* groupList);
typedef int (UCSDK_CALL *fp_SearchFixedGroup)(const char* groupNo, const char* groupName,
											  int offset, int count, UCFixedGroupList* groupList);
typedef int (UCSDK_CALL *fp_AddCustomGroup)(UCCustomGroup* group);
typedef int (UCSDK_CALL *fp_AddFavoriteGroup)(UCFavoriteGroup* group);
typedef int (UCSDK_CALL *fp_GetCustomGroupById)(const char* pGId, UCCustomGroup* group);
typedef int (UCSDK_CALL *fp_GetCustomGrouplist)(int iFrom, int iTo, UCCustomGroupList* groupList);
typedef int (UCSDK_CALL *fp_RemoveCustomGroup)(const UCCustomGroup* group);
typedef int (UCSDK_CALL *fp_RemoveFavoriteGroup)(const UCFavoriteGroup* group);
typedef int (UCSDK_CALL *fp_AddContactToFavoriteGroup)(const UCFavoriteGroup* group, UCContact* _contact);
typedef int (UCSDK_CALL *fp_RemoveContactFromFavoriteGroup)(const UCFavoriteGroup* group, const UCContact* _contact);
typedef int (UCSDK_CALL *fp_RenameToFavoriteGroup)(const UCFavoriteGroup* group, const char* _name);
typedef int (UCSDK_CALL *fp_GetContactlistFromFavoriteGroup)(const UCFavoriteGroup* group, int iFrom, int iTo, UCContactList* _contactlist);
typedef int (UCSDK_CALL *fp_AddContactToCustomGroup)(const UCCustomGroup* group, UCContact* _contact);
typedef int (UCSDK_CALL *fp_RemoveContactFromCustomGroup)(const UCCustomGroup* group, const UCContact* _contact);
typedef int (UCSDK_CALL *fp_RenameToCustomGroup)(const UCCustomGroup* group, const char* _name);
typedef int (UCSDK_CALL *fp_GetContactlistFromCustomGroup)(const UCCustomGroup* group, int iFrom, int iTo, UCContactList* _contactlist);
typedef int (UCSDK_CALL *fp_MoveUp)(const UCCustomGroup* group);
typedef int (UCSDK_CALL *fp_MoveDown)(const UCCustomGroup* group);
typedef int (UCSDK_CALL *fp_AddContactToFixedGroup)(const UCFixedGroup* group, UCContact* _contact);
typedef int (UCSDK_CALL *fp_RemoveContactFromFixedGroup)(const UCFixedGroup* group, const UCContact* _contact);
typedef int (UCSDK_CALL *fp_RenameToFixedGroup)(const UCFixedGroup* group, const char* _name);
typedef int (UCSDK_CALL *fp_GetContactlistFromFixedGroup)(const UCFixedGroup* group, int iFrom, int iTo, UCContactList* _contactlist);
typedef int (UCSDK_CALL *fp_ChangeGroupInfo)(const UCFixedGroup* group);
typedef int (UCSDK_CALL *fp_ChangeGroupOwner)(const UCFixedGroup* group, const UCContact* _owner);
typedef int (UCSDK_CALL *fp_RefreshContactList)(const UCFixedGroup* group, int iFrom, int iTo, UCContactList* _contactlist);
typedef int (UCSDK_CALL *fp_RefreshGroup)(const UCFixedGroup* group);
typedef int (UCSDK_CALL *fp_AcceptInvitation)(const UCFixedGroup* group);
typedef int (UCSDK_CALL *fp_RejectInvitation)(const UCFixedGroup* group);
typedef int (UCSDK_CALL *fp_AcceptJoinReq)(const UCFixedGroup* group, const UCContact* _contact);
typedef int (UCSDK_CALL *fp_RejectJoinReq)(const UCFixedGroup* group, const UCContact* _contact);

//UCIM
typedef int (UCSDK_CALL *fp_SendIMMessage)(const char* pMsg, const UCAccountList* accountList, char convId[CONVID_LENGTH]);
typedef int (UCSDK_CALL *fp_CloseConversation)(const char* convId);
typedef int (UCSDK_CALL *fp_AcceptFile)(const char* fileId, const char* filePath);
typedef int (UCSDK_CALL *fp_CancelFile)(const char* fileId);
typedef int (UCSDK_CALL *fp_RejectFile)(const char* fileId);
typedef int (UCSDK_CALL *fp_TransferFile)(const char* pAcc, const char* filePath, const char* transType,
										  int bIsOfflineFile, char fileId[FILEID_LENGTH]);

//UCMeeting
typedef int (UCSDK_CALL *fp_MakeMeetingGroup)(const UCContactList* memberlist, char convId[CONVID_LENGTH]);
typedef int (UCSDK_CALL *fp_StartMeeting)(const char* convId);
typedef int (UCSDK_CALL *fp_AcceptMeeting)(const char* convId);
typedef int (UCSDK_CALL *fp_AddParticipant)(const UCContact* member, const char* convId);
typedef int (UCSDK_CALL *fp_ConnectParticipant)(const UCContact* member, const char* convId);
typedef int (UCSDK_CALL *fp_RemoveParticipant)(const UCContact* member, const char* convId);
typedef int (UCSDK_CALL *fp_KickParticipant)(const UCContact* member, const char* convId);
typedef int (UCSDK_CALL *fp_MuteMeeting)(const UCContact* member, const char* convId);
typedef int (UCSDK_CALL *fp_UnMuteMeeting)(const UCContact* member, const char* convId);
typedef int (UCSDK_CALL *fp_GetBookConfList)(int iFrom, int iTo, UCBookConfList* bookConfList);
typedef int (UCSDK_CALL *fp_JoinMeeting)(const UCBookConf* meetingInfo, char convId[CONVID_LENGTH]);
typedef int (UCSDK_CALL *fp_LeaveMeeting)(const char* convId);

//UCPublic
typedef int (UCSDK_CALL *fp_PublishSelfInformation)(const UCPublishInfoMap* publishInfoMap);
typedef int (UCSDK_CALL *fp_GetContactStatus)(const char* _uri, int* _status);

//UCSignalRecv
typedef int (UCSDK_CALL *fp_OnClientSignInNotify)(const UCClientSignInNotify fpClientSignInNotify);
typedef int (UCSDK_CALL *fp_OnStatusChanged)(const UCStatusChanged fpStatusChanged);
typedef int (UCSDK_CALL *fp_OnIncreContactsChanged)(const UCIncreContactsChanged fpIncreContactsChanged);
typedef int (UCSDK_CALL *fp_OnAVSessAdded)(const UCAVSessAdded fpAVSessAdded);
typedef int (UCSDK_CALL *fp_OnAVSessionConnected)(const UCAVSessionConnected fpAVSessionConnected);
typedef int (UCSDK_CALL *fp_OnAVSessionClosed)(const UCAVSessionClosed fpAVSessionClosed);
typedef int (UCSDK_CALL *fp_OnConvMemberStatusChanged)(const UCConvMemberStatusChanged fpConvMemberStatusChanged);
typedef int (UCSDK_CALL *fp_OnConvMemAllowSpeak)(const UCConvMemAllowSpeak fpConvMemAllowSpeak);
typedef int (UCSDK_CALL *fp_OnConvMemForbidSpeak)(const UCConvMemForbidSpeak fpConvMemForbidSpeak);
typedef int (UCSDK_CALL *fp_OnConvMemCurSpeaker)(const UCConvMemCurSpeaker fpConvMemCurSpeaker);
typedef int (UCSDK_CALL *fp_OnConvGroupMemberChanged)(const UCConvGroupMemberChanged fpConvGroupMemberChanged);
typedef int (UCSDK_CALL *fp_OnReceivedIMMessage)(const UCReceivedIMMessage fpReceivedIMMessage);
typedef int (UCSDK_CALL *fp_OnInstantSessRemoved)(const UCInstantSessRemoved fpInstantSessRemoved);
typedef int (UCSDK_CALL *fp_OnInstantSessAdded)(const UCInstantSessAdded fpInstantSessAdded);
typedef int (UCSDK_CALL *fp_OnSysMsgRecved)(const UCSysMsgRecved fpSysMsgRecved);
typedef int (UCSDK_CALL *fp_OnGroupInvitation)(const UCGroupInvitation fpGroupInvitation);
typedef int (UCSDK_CALL *fp_OnGroupInvitationRes)(const UCGroupInvitationRes fpGroupInvitationRes);
typedef int (UCSDK_CALL *fp_OnLeaveFromFixedGroup)(const UCLeaveFromFixedGroup fpLeaveFromFixedGroup);
typedef int (UCSDK_CALL *fp_OnJoinFixedGroupRequest)(const UCJoinFixedGroupRequest fpJoinFixedGroupRequest);
typedef int (UCSDK_CALL *fp_OnJoinFixedGroupRes)(const UCJoinFixedGroupRes fpJoinFixedGroupRes);
typedef int (UCSDK_CALL *fp_OnMemberAdded)(const UCMemberAdded fpMemberAdded);
typedef int (UCSDK_CALL *fp_OnMemberRemoved)(const UCMemberRemoved fpMemberRemoved);
typedef int (UCSDK_CALL *fp_OnMemberFlowChanged)(const UCMemberFlowChanged fpMemberFlowChanged);
typedef int (UCSDK_CALL *fp_OnFixedGroupInfoChanged)(const UCFixedGroupInfoChanged fpFixedGroupInfoChanged);
typedef int (UCSDK_CALL *fp_OnNewFileRercved)(const UCNewFileRercved fpNewFileRercved);
typedef int (UCSDK_CALL *fp_OnFileAccept)(const UCFileAccept fpFileAccept);
typedef int (UCSDK_CALL *fp_OnFileCancel)(const UCFileCancel fpFileCancel);
typedef int (UCSDK_CALL *fp_OnFileProgress)(const UCFileProgress fpFileProgress);

//UCSignIn
typedef int (UCSDK_CALL *fp_Init)();
typedef int (UCSDK_CALL *fp_UnInit)();
typedef int (UCSDK_CALL *fp_LoginByToken)(const char* token);
typedef int (UCSDK_CALL *fp_LoginByPasswd)(const char* account, const char* passwd);
typedef int (UCSDK_CALL *fp_Logout)();
typedef int (UCSDK_CALL *fp_Config)(const char* srvUrl);
typedef int (UCSDK_CALL *fp_SetLang)(const char* lang);

//UCVoIP
typedef int (UCSDK_CALL *fp_MakeCall)(const UCContact* member, int iType, const UCVideoWindow* localWnd,
									  const UCVideoWindow* remoteWnd, char convId[CONVID_LENGTH]);
typedef int (UCSDK_CALL *fp_Accept)(const char* convId, int iType, const UCVideoWindow* localWnd, const UCVideoWindow* remoteWnd);
typedef int (UCSDK_CALL *fp_Reject)(const char* convId, int iType);
typedef int (UCSDK_CALL *fp_Hangup)(const char* convId, int iType);
typedef int (UCSDK_CALL *fp_Hold)(const char* convId);
typedef int (UCSDK_CALL *fp_Resume)(const char* convId);
typedef int (UCSDK_CALL *fp_Forward)(const char* convId, const char* account);
typedef int (UCSDK_CALL *fp_StartRecord)(const char* convId, const char* filePath);
typedef int (UCSDK_CALL *fp_StopRecord)(const char* convId);
typedef int (UCSDK_CALL *fp_MuteVoIP)(int iType);
typedef int (UCSDK_CALL *fp_UnMuteVoIP)(int iType);

//////////////////////////////////////////////////////////////////////////

class UCUnitTest
{
public:
	static UCUnitTest* Instance();
	static void Destroy();
	bool Start(bool bIsNeedLogin = true);
	bool Stop(bool bIsNeedLogout = true);
	bool Login();
	bool Logout();

private:
	bool LoadDll();
	bool FreeDll();
	void SetUCSignalRecvCB();

private:
	UCUnitTest();
	~UCUnitTest();
	static UCUnitTest* m_pUCUnitTest;

public:
	HMODULE m_hDll;
	std::string m_strAcc;
	std::string m_strPwd;

public:
	fp_eSDKClientPlatform_Init m_fpeSDKClientPlatform_Init;
	fp_eSDKClientPlatform_Uninit m_fpeSDKClientPlatform_Uninit;
	fp_eSDKClientPlatform_LoginByPassword m_fpeSDKClientPlatform_LoginByPassword;
	fp_eSDKClientPlatform_Logout m_fpeSDKClientPlatform_Logout;

	fp_GetAllContactlist m_fpGetAllContactlist;
	fp_GetContactByAccount m_fpGetContactByAccount;
	fp_GetContactById m_fpGetContactById;
	fp_GetContactByPhoneNum m_fpGetContactByPhoneNum;
	fp_GetContactByUri m_fpGetContactByUri;
	fp_HasContact m_fpHasContact;
	fp_RefreshContactByAccount m_fpRefreshContactByAccount;
	fp_RefreshContactById m_fpRefreshContactById;
	fp_RefreshContactByUri m_fpRefreshContactByUri;
	fp_RemoveContactById m_fpRemoveContactById;
	fp_SearchContact m_fpSearchContact;
	fp_Modify m_fpModify; 
	fp_GetHeadImagePath m_fpGetHeadImagePath;
	fp_MoveToGroup m_fpMoveToGroup;
	fp_AddToGroup m_fpAddToGroup;
	fp_RemoveFromGroup m_fpRemoveFromGroup;
	fp_CanStartSession m_fpCanStartSession;
	fp_CanMoveToGroup m_fpCanMoveToGroup;
	fp_GetCustomGroups m_fpGetCustomGroups;
	fp_IsFavourite m_fpIsFavourite;
	fp_AddFixedGroup m_fpAddFixedGroup;
	fp_GetFixedGroupByID m_fpGetFixedGroupByID;
	fp_GetFixedGroupByUri m_fpGetFixedGroupByUri;
	fp_RemoveFixedGroup m_fpRemoveFixedGroup;
	fp_RefreshFixedGrouplist m_fpRefreshFixedGrouplist;
	fp_GetFixedGrouplist m_fpGetFixedGrouplist;
	fp_SearchFixedGroup m_fpSearchFixedGroup;
	fp_AddCustomGroup m_fpAddCustomGroup;
	fp_AddFavoriteGroup m_fpAddFavoriteGroup; 
	fp_GetCustomGroupById m_fpGetCustomGroupById; 
	fp_GetCustomGrouplist m_fpGetCustomGrouplist; 
	fp_RemoveCustomGroup m_fpRemoveCustomGroup;
	fp_RemoveFavoriteGroup m_fpRemoveFavoriteGroup;
	fp_AddContactToFavoriteGroup m_fpAddContactToFavoriteGroup;
	fp_RemoveContactFromFavoriteGroup m_fpRemoveContactFromFavoriteGroup;
	fp_RenameToFavoriteGroup m_fpRenameToFavoriteGroup;
	fp_GetContactlistFromFavoriteGroup m_fpGetContactlistFromFavoriteGroup;
	fp_AddContactToCustomGroup m_fpAddContactToCustomGroup;
	fp_RemoveContactFromCustomGroup m_fpRemoveContactFromCustomGroup;
	fp_RenameToCustomGroup m_fpRenameToCustomGroup;
	fp_GetContactlistFromCustomGroup m_fpGetContactlistFromCustomGroup;
	fp_MoveUp m_fpMoveUp;
	fp_MoveDown m_fpMoveDown;
	fp_AddContactToFixedGroup m_fpAddContactToFixedGroup;
	fp_RemoveContactFromFixedGroup m_fpRemoveContactFromFixedGroup; 
	fp_RenameToFixedGroup m_fpRenameToFixedGroup;
	fp_GetContactlistFromFixedGroup m_fpGetContactlistFromFixedGroup;
	fp_ChangeGroupInfo m_fpChangeGroupInfo;
	fp_ChangeGroupOwner m_fpChangeGroupOwner;
	fp_RefreshContactList m_fpRefreshContactList;
	fp_RefreshGroup m_fpRefreshGroup;
	fp_AcceptInvitation m_fpAcceptInvitation;
	fp_RejectInvitation m_fpRejectInvitation;
	fp_AcceptJoinReq m_fpAcceptJoinReq;
	fp_RejectJoinReq m_fpRejectJoinReq;
	fp_SendIMMessage m_fpSendIMMessage;
	fp_CloseConversation m_fpCloseConversation;
	fp_AcceptFile m_fpAcceptFile;
	fp_CancelFile m_fpCancelFile;   
	fp_RejectFile m_fpRejectFile;   
	fp_TransferFile m_fpTransferFile;
	fp_MakeMeetingGroup m_fpMakeMeetingGroup;
	fp_StartMeeting m_fpStartMeeting; 
	fp_AcceptMeeting m_fpAcceptMeeting;
	fp_AddParticipant m_fpAddParticipant;
	fp_ConnectParticipant m_fpConnectParticipant;
	fp_RemoveParticipant m_fpRemoveParticipant;
	fp_KickParticipant m_fpKickParticipant;
	fp_MuteMeeting m_fpMuteMeeting;
	fp_UnMuteMeeting m_fpUnMuteMeeting;
	fp_GetBookConfList m_fpGetBookConfList;
	fp_JoinMeeting m_fpJoinMeeting;
	fp_LeaveMeeting m_fpLeaveMeeting;
	fp_PublishSelfInformation m_fpPublishSelfInformation;
	fp_GetContactStatus m_fpGetContactStatus;
	fp_OnClientSignInNotify m_fpOnClientSignInNotify;
	fp_OnStatusChanged m_fpOnStatusChanged;
	fp_OnIncreContactsChanged m_fpOnIncreContactsChanged;
	fp_OnAVSessAdded m_fpOnAVSessAdded;
	fp_OnAVSessionConnected m_fpOnAVSessionConnected;
	fp_OnAVSessionClosed m_fpOnAVSessionClosed;
	fp_OnConvMemberStatusChanged m_fpOnConvMemberStatusChanged;
	fp_OnConvMemAllowSpeak m_fpOnConvMemAllowSpeak;
	fp_OnConvMemForbidSpeak m_fpOnConvMemForbidSpeak;
	fp_OnConvMemCurSpeaker m_fpOnConvMemCurSpeaker;
	fp_OnConvGroupMemberChanged m_fpOnConvGroupMemberChanged;
	fp_OnReceivedIMMessage m_fpOnReceivedIMMessage;
	fp_OnInstantSessRemoved m_fpOnInstantSessRemoved;
	fp_OnInstantSessAdded m_fpOnInstantSessAdded;
	fp_OnSysMsgRecved m_fpOnSysMsgRecved;
	fp_OnGroupInvitation m_fpOnGroupInvitation;
	fp_OnGroupInvitationRes m_fpOnGroupInvitationRes;
	fp_OnLeaveFromFixedGroup m_fpOnLeaveFromFixedGroup;
	fp_OnJoinFixedGroupRequest m_fpOnJoinFixedGroupRequest;
	fp_OnJoinFixedGroupRes m_fpOnJoinFixedGroupRes;
	fp_OnMemberAdded m_fpOnMemberAdded; 
	fp_OnMemberRemoved m_fpOnMemberRemoved;
	fp_OnMemberFlowChanged m_fpOnMemberFlowChanged;
	fp_OnFixedGroupInfoChanged m_fpOnFixedGroupInfoChanged;
	fp_OnNewFileRercved m_fpOnNewFileRercved;
	fp_OnFileAccept m_fpOnFileAccept;
	fp_OnFileCancel m_fpOnFileCancel;
	fp_OnFileProgress m_fpOnFileProgress;
	fp_Init m_fpInit;                           
	fp_UnInit m_fpUnInit;                         
	fp_LoginByToken m_fpLoginByToken;  
	fp_LoginByPasswd m_fpLoginByPasswd;
	fp_Logout m_fpLogout;                         
	fp_Config m_fpConfig;       
	fp_SetLang m_fpSetLang;
	fp_MakeCall m_fpMakeCall;
	fp_Accept m_fpAccept;
	fp_Reject m_fpReject;
	fp_Hangup m_fpHangup;
	fp_Hold m_fpHold;         
	fp_Resume m_fpResume;       
	fp_Forward m_fpForward; 
	fp_StartRecord m_fpStartRecord;
	fp_StopRecord m_fpStopRecord;   
	fp_MuteVoIP m_fpMuteVoIP;              
	fp_UnMuteVoIP m_fpUnMuteVoIP;
};

#endif