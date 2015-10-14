#ifndef _DATA_DEFINE_HEADER_
#define _DATA_DEFINE_HEADER_

#ifdef ESDKCLIENTPLATFORM_EXPORTS
#ifndef UCSDK_EXPORTS
#define UCSDK_EXPORTS
#endif
#endif

#ifndef CALLBACK
#define CALLBACK __stdcall
#endif

#ifndef UCSDK_CALL
#define UCSDK_CALL __stdcall
#endif

#ifdef UCSDK_EXPORTS
#define UCSDK_API __declspec(dllexport)
#else
#define UCSDK_API __declspec(dllimport)
#endif

#ifndef __cplusplus
typedef int bool;
#define false 0
#define true 1
#endif

//////////////////////////////////////////////////////////////////////////
//UCSDK������
typedef enum
{
	UC_Succ = 0,					//�ɹ�
	UC_Fail,						//ʧ��
	UC_InvalidParam,				//�������
	UC_NullPoint,					//��ָ��
	UC_NotFound,					//û���ҵ�
	UC_ExistAVSess					//�Ѿ�����AVSession
} UC_RETURN_CODE_E;

//��½״̬
typedef enum
{
	UC_Client_Uninited,
	UC_Client_SignedFailed,			//��½ʧ��
	UC_Client_SigningIn,			//��½��
	UC_Client_SignedIn,				//��½�ɹ�
	UC_Client_KickedOut,			//�����
	UC_Client_Invalid				//����
} UC_SIGNIN_STATE_E;

//��������
typedef enum
{
	UC_Audio = 0,					//��������
	UC_Video						//��Ƶ����
} UC_CALL_TYPE_E;

//�����豸����
typedef enum
{
	UC_Mic = 0,						//��˷��豸
	UC_Speaker						//�������豸
} UC_MUTE_DEVICE_E;

//IM��Ϣ����
typedef enum
{
	UC_ChatP2PIM = 0,				//��Ե���Ϣ
	UC_ChatFixedGroup = 1,			//�̶�Ⱥ��Ϣ
	UC_ChatInputStatus = 3,			//��ǰ���촰������״̬
	UC_ChatOfflineFile = 4,			//�����ļ�����
	UC_ChatAddFriend = 5,			//ϵͳԤ������δʹ��
	UC_ChatErrorMsg = 6,			//ϵͳԤ������δʹ��
} UC_INSTANT_MSG_TYPE_E;

//������ϵ����Ϣ����
typedef enum
{
	UC_Availability = 0,			//״̬
	UC_CustomStatusDesc,			//�Զ���״̬���������ݲ�ʹ�ã�
	UC_Position,					//ְλ���ݲ�ʹ�ã�
	UC_Location,					//��ַ���ݲ�ʹ�ã�
	UC_AVTool,						//�豸���ݲ�ʹ�ã�
	UC_Signature,					//ǩ��
	UC_HeadImage,					//ͷ���ݲ�ʹ�ã�
	UC_CallDeviceDesc,				//�����豸�������ݲ�ʹ�ã�
	UC_Invalid						//���Ϸ�
} UC_PUB_CONTACT_INFO_TYPE_E;

//��ϵ��״̬
typedef enum
{
	UC_Offline = 0,					//����
	UC_Online,						//����
	UC_Hide,						//����
	UC_Busy,						//æµ
	UC_Leave,						//�뿪
	UC_NoDisturb,					//�����
	UC_InvalidStatus				//״̬δ֪
} UC_CONTACT_AVAILABILITY_E;

//Ⱥ������
typedef enum
{
	UC_CustomGroupType = 0,
	UC_FixedGroupType,
	UC_FavoriteGroupType
} UC_GROUP_TYPE_E;

//�Ự���Ͷ���
typedef enum
{
	UC_SessInvalid = 0,				//���Ϸ�
	UC_InstantMessage = 1,			//��ʱ��Ϣ�Ự
	UC_AudioVideo,					//����Ƶ����(����)�Ự
	UC_DataSharing,					//���ݹ���Ự
	UC_CallExBusiness,				//������չ�Ự
	UC_Reserved1,					//����
	UC_Reserved2,					//����
} UC_SESSION_TYPE_E;

//����״̬
typedef enum
{
	UC_Inviting = 0,
	UC_Hangup,
	UC_InConf,
	UC_Quit,
	UC_InHold,
	UC_Needreffer = 5
} UC_MEM_CHG_STATUS_E;

typedef enum
{
	UC_AllowSpk = 6,
	UC_ForbidSpk,
	UC_CurSpker
} UC_MEM_SPK_STATUS_E;

typedef enum
{
	UC_MemAdd = 9,
	UC_MemDel
} UC_GROUP_MEM_CHANGED_E;

//�Ự������ö��
typedef enum
{
	UC_ConvIdentifier = 0,			//�ỰID
	UC_ConvSubject,					//�Ự����

	UC_ConvConfIdentifier,			//��������ID

	UC_ConvTempGroupUri,			//��ʱȺURI
	UC_ConvFixedGroupUri,			//�̶�ȺURI
	UC_ConvHistoryGroupUri,			//��ʷ��ʱȺURI

	UC_ConvBookingConfUri,			/*!< mark if join booking conference*/
	UC_ConvTypeUri,					//����
	UC_ConvConfSubject,				//����
	UC_ConvReserved2,				/*!< reserver property for future*/
	UC_ConvReserved3,				/*!< reserver property for future*/
	UC_ConvReserved4,				/*!< reserver property for future*/
	UC_ConvReserved5,				/*!< reserver property for future*/
} UC_CONVERSATION_PROPERTY_E;

//////////////////////////////////////////////////////////////////////////
//SignIn reason
#define UC_SIGNINFAIL_GETUPDATE		"getupdate"; // aa:AAresult
#define UC_SIGNINFAIL_AA			"aa"; // aa:AAresult
#define UC_SIGNINFAIL_CONTACT		"contact";
#define UC_SIGNINFAIL_SIP			"sip";
#define UC_SIGNINFAIL_SIP_KICKOUT	"sipkickout";

#define UC_SIGNIN_NOK				"signin";
#define UC_SIGNOUT_OK				"signout";
#define UC_SIGNOUT_FAILED			"signoutfailed";

#define UC_SIGNINFAIL_NOIP			"noip";
#define UC_SIGNINFAIL_HASIP			"hasip";

//////////////////////////////////////////////////////////////////////////

#define NORMAL_LENGTH				128
#define NAME_LENGTH					64
#define URI_LENGTH					64				//30,46
#define CONVID_LENGTH				40				//36
#define FILEID_LENGTH				32
#define MSGID_LENGTH				32				//19
#define TIME_LENGTH					20				//19
#define ID_LENGTH					16
#define NUMBER_LENGTH				16
#define ADDRESS_LENGTH				128
#define EMAIL_LENGTH				32
#define WEB_LENGTH					128
#define TYPE_LENGTH					32
#define BOOL_LENGTH					8
#define PWD_LENGTH					32
#define LINEINDEX					32
#define IMAGE_LENGTH				256
#define CONTENT_LENGTH				512

#define PUB_LENGTH					9				//UC_PUB_CONTACT_INFO_TYPE_E
#define PUB_INFO_LENGTH				64
#define PROP_LENGTH					13				//UC_CONVERSATION_PROPERTY_E
#define PROP_INFO_LENGTH			64

typedef struct
{
	char str[NAME_LENGTH];
} UCAccount;

typedef struct
{
	char origin[URI_LENGTH];		//��Ϣ���ͷ�SIP��ַ��URI��
	char target[URI_LENGTH];		//��Ϣ���շ�����SIP URI + �ն����ͣ�
	char content[CONTENT_LENGTH];	//��Ϣ����
	char rcv_time[TIME_LENGTH];		//����ʱ��
	char name[NAME_LENGTH];			//���ͷ��ƺ�
	char msgid[MSGID_LENGTH];		//��ϢID
	int  chatType;					//��Ϣ����
} UCIMMessage;

typedef struct
{
	char id_[ID_LENGTH];			//�û�ID
	char uri_[URI_LENGTH];			//SIP URI
	char ucAcc_[NAME_LENGTH];		//�˺�
	char staffNo_[ID_LENGTH];		//����
	char name_[NAME_LENGTH];		//����
	char nickName_[NAME_LENGTH];	//�ǳ�
	char qpinyin_[NAME_LENGTH];		//����ƴ��ȫ��
	char spinyin_[NAME_LENGTH];		//����ƴ�����
	char homePhone_[NUMBER_LENGTH];	//��ͥ�绰����
	char officePhone_[NUMBER_LENGTH];//�칫�ҵ绰����
	char mobile_[NUMBER_LENGTH];	//�ֻ�����
	char otherPhone_[NUMBER_LENGTH];//�����绰����
	char address_[ADDRESS_LENGTH];	//��ַ��Ϣ
	char email_[EMAIL_LENGTH];		//EMAIL��ַ
	char fax_[NUMBER_LENGTH];		//�������
	char corpName_[NAME_LENGTH];	//��˾����
	char deptName_[NAME_LENGTH];	//��������
	char webSite_[WEB_LENGTH];		//��վ��ַ
	char desc_[NORMAL_LENGTH];		//����
	char zip_[NUMBER_LENGTH];		//��������
	char signature_[NORMAL_LENGTH];	//����ǩ��
	char imageID_[ID_LENGTH];		//ͷ��ID
	char position_[NORMAL_LENGTH];	//λ��
	char location_[NORMAL_LENGTH];	//��ַ
	char tzone_[TIME_LENGTH];		//����ʱ��
	char avtool_[NORMAL_LENGTH];	//���õ��豸������˷硢������������ͷ��
	char device_[TYPE_LENGTH];		//�豸����
	char terminalType_[TYPE_LENGTH];//�����ն����ͣ�PC��Mobile�ȣ�
} UCContact;

typedef struct
{
	char topic[NORMAL_LENGTH];		//��������
	char meetingtime[TIME_LENGTH];	//�ٿ�ʱ��
	char convener[URI_LENGTH];		//�ټ���
	char convenername[NAME_LENGTH];	//������
	UCAccount* attendeelist;		//������б�
	char accessnum[NUMBER_LENGTH];	//�����
	char securitycode[NUMBER_LENGTH];//���밲ȫ��
	char iscycle[BOOL_LENGTH];		//�Ƿ������ڻ���
	char startdate[TIME_LENGTH];	//��ʼ����
	char validityperiod[TIME_LENGTH];//����ʱ��
	char content[CONTENT_LENGTH];	//��������
	char chairmanpwd[PWD_LENGTH];	//��ϯ����
	char partmanpwd[PWD_LENGTH];	//���������
	char recordcode[PWD_LENGTH];	//¼���룬����
	char funcbits[TYPE_LENGTH];		//���鹦��λ
	char mediaBits[TYPE_LENGTH];	//ý������
	int	 confType;					//�������ͣ�0����ʱ���� 1��ԤԼ���� 2�����ڻ��� 3�����û���
	char confid[ID_LENGTH];			//����ID
	char confStyle[TYPE_LENGTH];	//��������
} UCBookConf;

//Ⱥ��
typedef struct
{
	char name_[NAME_LENGTH];		//Ⱥ����
	char id_[ID_LENGTH];			//Ⱥ��ID
	int	 type_;						//Ⱥ������
	int  readonly_;					//Ⱥ���Ƿ�ֻ��
} UCGroup;

typedef struct
{
	char name_[NAME_LENGTH];		//Ⱥ����
	char id_[ID_LENGTH];			//Ⱥ��ID
	int	 type_;						//Ⱥ������
	int  readonly_;					//Ⱥ���Ƿ�ֻ��
	int  indexno_;					//group index no.
} UCCustomGroup;

typedef struct
{
	char name_[NAME_LENGTH];		//Ⱥ����
	char id_[ID_LENGTH];			//Ⱥ��ID
	int	 type_;						//Ⱥ������
	int  readonly_;					//Ⱥ���Ƿ�ֻ��
} UCFavoriteGroup;

typedef struct
{
	char name_[NAME_LENGTH];		//Ⱥ����
	char id_[ID_LENGTH];			//Ⱥ��ID
	int	 type_;						//Ⱥ������
	int  readonly_;					//Ⱥ���Ƿ�ֻ��
	char creator_[NAME_LENGTH];		//Ⱥ�鴴����
	char uri_[URI_LENGTH];			//Ⱥ��uri
	char groupno_[ID_LENGTH];		//Ⱥ���
	char desc_[NORMAL_LENGTH];		//Ⱥ������
	char bulletin_[CONTENT_LENGTH];	//Ⱥ�鹫��
	char owneruri_[URI_LENGTH];		//Ⱥ��uri
	int  capacity_;					//Ⱥ������Ա��
	char needpermit_[BOOL_LENGTH];	//�Ƿ���Ҫͨ��Ⱥ����֤�����
} UCFixedGroup;

typedef struct
{
	int  hWnd;						//���ھ��
	int  left;       
	int	 top;  
	int	 width;
	int	 height;	
} UCVideoWindow;

typedef struct
{
	char caller_[URI_LENGTH];
	char callername_[NAME_LENGTH];
	int	 callalertinfo_;
	int	 autoanswerdelay;			//�Զ�Ӧ����ʱʱ��(��λ����)���ı���ֻ����callalertinfo_==3���������Ч
	char lineindex_[LINEINDEX];
	int  isvideo_;
	int  callmode_;
	int  isdataconf_;
} UCAudioVideoParam;

//////////////////////////////////////////////////////////////////////////
typedef struct
{
	int iFrom;
	int iTo;
	int iTotal;
	UCAccount* account;
} UCAccountList;

typedef struct
{
	char publish[PUB_LENGTH][PUB_INFO_LENGTH];
} UCPublishInfoMap;

typedef struct
{
	int iFrom;
	int iTo;
	int iTotal;
	UCBookConf* bookConf;
} UCBookConfList;

typedef struct
{
	int iFrom;
	int iTo;
	int iTotal;
	UCContact* contact;
} UCContactList;

typedef struct
{
	int iFrom;
	int iTo;
	int iTotal;
	UCFixedGroup* group;
} UCFixedGroupList;

typedef struct
{
	int iFrom;
	int iTo;
	int iTotal;
	UCCustomGroup* group;
} UCCustomGroupList;

typedef struct
{
	char prop[PROP_LENGTH][PROP_INFO_LENGTH];
} UCConversationPropMap;

//////////////////////////////////////////////////////////////////////////
//�ص�����ָ��

/**
 *��¼�ǳ��ص�����
 * 
 *�ú������ڵ�¼�ǳ��ص�����
 *
 *@param[in] 	state		��½״̬ �ο�UC_SIGNIN_STATE_E
 *@param[in] 	reason		�ο� DataDef.h ����SignIn reason
 *@attention	��
 *@par 			��
**/
typedef void (CALLBACK *UCClientSignInNotify)(int state, const char* reason);

/**
 *��ϵ��״̬�ı�ص�����
 * 
 *�ú���������ϵ��״̬�ı�ص�����
 *
 *@param[in] 	state		״̬
 *@param[in] 	desc		
 *@param[in] 	contact
 *@param[in] 	param
 *@attention	��
 *@par 			��
**/
typedef void (CALLBACK *UCStatusChanged)(int state, const char* desc, const UCContact* contact, const char* param);

/**
 *��ϵ���б����ص�����
 * 
 *�ú���������ϵ���б����ص�����
 *
 *@attention	��
 *@par 			��
**/
typedef void (CALLBACK *UCIncreContactsChanged)(void);

/**
 *�������磨�����������VoIP���ص�����
 * 
 *�ú��������������磨�����������VoIP���ص�����
 *
 *@param[in] 	propMap		
 *@param[in] 	memberlist	��Ա�б�����ǻ�����memberlist[0]�ǻ�����ϯ
 *@param[in] 	avParam		��Ƶ����
 *@attention	��
 *@par 			��
**/
typedef void (CALLBACK *UCAVSessAdded)(const UCConversationPropMap* propMap, const UCAccountList* memberlist, const UCAudioVideoParam* avParam);//memberlist: the first value of the vector is leader if it's conference.

/**
 *����ͨ�������������������VoIP���ص�����
 * 
 *�ú�����������ͨ�������������������VoIP���ص�����
 *
 *@param[in] 	convId		�ỰID
 *@attention	��
 *@par 			��
**/
typedef void (CALLBACK *UCAVSessionConnected)(const char* convId);

/**
 *����ͨ���رգ������������VoIP���ص�����
 * 
 *�ú�����������ͨ���رգ������������VoIP���ص�����
 *
 *@param[in] 	convId		�ỰID
 *@attention	��
 *@par 			��
**/
typedef void (CALLBACK *UCAVSessionClosed)(const char* convId);

/**
 *�����Ա״̬�仯�ص�����
 * 
 *�ú������ڻ����Ա״̬�仯�ص�����
 *
 *@param[in] 	convId		�ỰID
 *@param[in] 	chgtype		����״̬ �ο�MEM_CHG_STATUS_E
 *@param[in] 	memberuri	�����Աuri
 *@attention	��
 *@par 			��
**/
typedef void (CALLBACK *UCConvMemberStatusChanged)(const char* convId, int chgtype, const char* memberuri);

/**
 *����������Իص�����
 * 
 *�ú�����������������Իص�����
 *
 *@param[in] 	convId		�ỰID
 *@param[in] 	member		����Ա
 *@attention	��
 *@par 			��
**/
typedef void (CALLBACK *UCConvMemAllowSpeak)(const char* convId, const UCContact* member);

/**
 *����߽�ֹ���Իص�����
 * 
 *�ú�����������߽�ֹ���Իص�����
 *
 *@param[in] 	convId		�ỰID
 *@param[in] 	member		����Ա
 *@attention	��
 *@par 			��
**/
typedef void (CALLBACK *UCConvMemForbidSpeak)(const char* convId, const UCContact* member);

/**
 *��������ڷ��Իص�����
 * 
 *�ú���������������ڷ��Իص�����
 *
 *@param[in] 	convId		�ỰID
 *@param[in] 	member		����Ա
 *@attention	��
 *@par 			��
**/
typedef void (CALLBACK *UCConvMemCurSpeaker)(const char* convId, const UCContact* member);

/**
 *����Ա�䶯�ص�����
 * 
 *�ú�����������Ա�䶯�ص�����
 *
 *@param[in] 	convId		�ỰID
 *@param[in] 	chgtype		�ο� GROUP_MEM_CHANGED_E
 *@param[in] 	memberuri	�����Աuri
 *@attention	��
 *@par 			��
**/
typedef void (CALLBACK *UCConvGroupMemberChanged)(const char* convId, int chgtype, const char* memberuri);

/**
 *���ռ�ʱ��Ϣ�ص�����
 * 
 *�ú������ڽ��ռ�ʱ��Ϣ�ص�����
 *
 *@param[in] 	propMap
 *@param[in] 	memberlist	��Ա�б�����ǻ�����memberlist[0]�ǻ�����ϯ
 *@param[in] 	ImMessage	IM��Ϣ
 *@attention	��
 *@par 			��
**/
typedef void (CALLBACK *UCReceivedIMMessage)(const UCConversationPropMap* propMap, const UCAccountList* memberlist, const UCIMMessage* ImMessage);//memberlist: the first value of the vector is leader if it's conference.

/**
 *��ʱȺ��رջص�����
 * 
 *�ú���������ʱȺ��رջص�����
 *
 *@param[in] 	convId
 *@attention	��
 *@par 			��
**/
typedef void (CALLBACK *UCInstantSessRemoved)(const char* convId);

/**
 *������ʱȺ��ص�����
 * 
 *�ú������ڼ�����ʱȺ��ص�����
 *
 *@param[in] 	convId
 *@param[in] 	member
 *@attention	��
 *@par 			��
**/
typedef void (CALLBACK *UCInstantSessAdded)(const char* convId, const UCContact* member);

/**
 *����ϵͳ��Ϣ�ص�����
 * 
 *�ú������ڽ���ϵͳ��Ϣ�ص�����
 *
 *@param[in] 	origin
 *@param[in] 	subject
 *@param[in] 	content
 *@param[in] 	rcv_time
 *@param[in] 	msgid
 *@param[in] 	msgtype
 *@attention	�ο� IMMessage
 *@par 			��
**/
typedef void (CALLBACK *UCSysMsgRecved)(const char* origin, const char* subject, const char* content, const char* rcv_time, const char* msgid, int msgtype);

/**
 *���������Ⱥ��ص�����
 * 
 *�ú������ڱ��������Ⱥ��ص�����
 *
 *@param[in] 	fixedGroup
 *@attention	��
 *@par 			��
**/
typedef void (CALLBACK *UCGroupInvitation)(const UCFixedGroup* fixedGroup);

/**
 *���������ϵ��Ӧ�����Ⱥ��ص�����
 * 
 *�ú������ڱ��������ϵ��Ӧ�����Ⱥ��ص�����
 *
 *@param[in] 	fixedGroup
 *@param[in] 	invitername
 *@param[in] 	result			1ͬ�⣬�����ܾ�
 *@attention	��
 *@par 			��
**/
typedef void (CALLBACK *UCGroupInvitationRes)(const UCFixedGroup* fixedGroup, const char* invitername, int result);

/**
 *�뿪�̶�Ⱥ��ص�����
 * 
 *�ú��������뿪�̶�Ⱥ��ص�����
 *
 *@param[in] 	fixedGroup
 *@param[in] 	reason			0: ���߳�Ⱥ��, 1: Ⱥ���ɢ
 *@attention	��
 *@par 			��
**/
typedef void (CALLBACK *UCLeaveFromFixedGroup)(const UCFixedGroup* fixedGroup, int reason);

/**
 *�������̶�Ⱥ��ص�����
 * 
 *�ú��������������̶�Ⱥ��ص�����
 *
 *@param[in] 	fixedGroup
 *@param[in] 	inviteruri
 *@attention	��
 *@par 			��
**/
typedef void (CALLBACK *UCJoinFixedGroupRequest)(const UCFixedGroup* fixedGroup, const char* inviteruri);

/**
 *�������̶�Ⱥ�鷵�ػص�����
 * 
 *�ú��������������̶�Ⱥ�鷵�ػص�����
 *
 *@param[in] 	fixedGroup
 *@param[in] 	invitername
 *@param[in] 	result			1ͬ�⣬�����ܾ�
 *@attention	��
 *@par 			��
**/
typedef void (CALLBACK *UCJoinFixedGroupRes)(const UCFixedGroup* fixedGroup, const char* invitername, int result);

/**
 *Ⱥ���Ա���ӻص�����
 * 
 *�ú�������Ⱥ���Ա���ӻص�����
 *
 *@param[in] 	fixedGroup
 *@param[in] 	member
 *@attention	��
 *@par 			��
**/
typedef void (CALLBACK *UCMemberAdded)(const UCFixedGroup* fixedGroup, const UCContact* member);

/**
 *Ⱥ���Ա�뿪�ص�����
 * 
 *�ú�������Ⱥ���Ա�뿪�ص�����
 *
 *@param[in] 	fixedGroup
 *@param[in] 	member
 *@attention	��
 *@par 			��
**/
typedef void (CALLBACK *UCMemberRemoved)(const UCFixedGroup* fixedGroup, const UCContact* member);

/**
 *Ⱥ�����Ա����ص�����
 * 
 *�ú�������Ⱥ�����Ա����ص�����
 *
 *@param[in] 	fixedGroup
 *@param[in] 	member
 *@attention	��
 *@par 			��
**/
typedef void (CALLBACK *UCMemberFlowChanged)(const UCFixedGroup* fixedGroup, const UCContact* member);

/**
 *Ⱥ����Ϣ����ص�����
 * 
 *�ú�������Ⱥ����Ϣ����ص�����
 *
 *@param[in] 	fixedGroup
 *@attention	��
 *@par 			��
**/
typedef void (CALLBACK *UCFixedGroupInfoChanged)(const UCFixedGroup* fixedGroup);

/**
 *�յ��ļ�����ص�����
 * 
 *�ú��������յ��ļ�����ص�����
 *
 *@param[in] 	fileid
 *@param[in] 	filename
 *@param[in] 	filesize
 *@param[in] 	originName
 *@attention	��
 *@par 			��
**/
typedef void (CALLBACK *UCNewFileRercved)(const char* fileid, const char* filename, int filesize, const char* originName);

/**
 *�����ļ��ص�����
 * 
 *�ú������ڽ����ļ��ص�����
 *
 *@param[in] 	fileid
 *@attention	��
 *@par 			��
**/
typedef void (CALLBACK *UCFileAccept)(const char* fileid);

/**
 *ȡ���ļ�����ص�����
 * 
 *�ú�������ȡ���ļ�����ص�����
 *
 *@param[in] 	fileid
 *@param[in] 	reason
 *@param[in] 	errcode
 *@attention	��
 *@par 			��
**/
typedef void (CALLBACK *UCFileCancel)(const char* fileid, const char* reason, const char* errcode);

/**
 *�ļ�������Ȼص�����
 * 
 *�ú��������ļ�������Ȼص�����
 *
 *@param[in] 	fileid
 *@param[in] 	procent
 *@attention	��
 *@par 			��
**/
typedef void (CALLBACK *UCFileProgress)(const char* fileid, const char* procent);

//////////////////////////////////////////////////////////////////////////


#endif