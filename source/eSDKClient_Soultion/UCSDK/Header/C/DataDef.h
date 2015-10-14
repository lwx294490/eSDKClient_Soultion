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
//UCSDK返回码
typedef enum
{
	UC_Succ = 0,					//成功
	UC_Fail,						//失败
	UC_InvalidParam,				//错误入参
	UC_NullPoint,					//空指针
	UC_NotFound,					//没有找到
	UC_ExistAVSess					//已经存在AVSession
} UC_RETURN_CODE_E;

//登陆状态
typedef enum
{
	UC_Client_Uninited,
	UC_Client_SignedFailed,			//登陆失败
	UC_Client_SigningIn,			//登陆中
	UC_Client_SignedIn,				//登陆成功
	UC_Client_KickedOut,			//被提出
	UC_Client_Invalid				//保留
} UC_SIGNIN_STATE_E;

//呼叫类型
typedef enum
{
	UC_Audio = 0,					//语音呼叫
	UC_Video						//视频呼叫
} UC_CALL_TYPE_E;

//静音设备类型
typedef enum
{
	UC_Mic = 0,						//麦克风设备
	UC_Speaker						//扬声器设备
} UC_MUTE_DEVICE_E;

//IM消息类型
typedef enum
{
	UC_ChatP2PIM = 0,				//点对点消息
	UC_ChatFixedGroup = 1,			//固定群消息
	UC_ChatInputStatus = 3,			//当前聊天窗口输入状态
	UC_ChatOfflineFile = 4,			//离线文件传输
	UC_ChatAddFriend = 5,			//系统预留，暂未使用
	UC_ChatErrorMsg = 6,			//系统预留，暂未使用
} UC_INSTANT_MSG_TYPE_E;

//发布联系人信息类型
typedef enum
{
	UC_Availability = 0,			//状态
	UC_CustomStatusDesc,			//自定义状态的描述（暂不使用）
	UC_Position,					//职位（暂不使用）
	UC_Location,					//地址（暂不使用）
	UC_AVTool,						//设备（暂不使用）
	UC_Signature,					//签名
	UC_HeadImage,					//头像（暂不使用）
	UC_CallDeviceDesc,				//呼叫设备描述（暂不使用）
	UC_Invalid						//不合法
} UC_PUB_CONTACT_INFO_TYPE_E;

//联系人状态
typedef enum
{
	UC_Offline = 0,					//离线
	UC_Online,						//在线
	UC_Hide,						//隐身
	UC_Busy,						//忙碌
	UC_Leave,						//离开
	UC_NoDisturb,					//免打扰
	UC_InvalidStatus				//状态未知
} UC_CONTACT_AVAILABILITY_E;

//群组类型
typedef enum
{
	UC_CustomGroupType = 0,
	UC_FixedGroupType,
	UC_FavoriteGroupType
} UC_GROUP_TYPE_E;

//会话类型定义
typedef enum
{
	UC_SessInvalid = 0,				//不合法
	UC_InstantMessage = 1,			//即时消息会话
	UC_AudioVideo,					//音视频呼叫(会议)会话
	UC_DataSharing,					//数据共享会话
	UC_CallExBusiness,				//呼叫扩展会话
	UC_Reserved1,					//保留
	UC_Reserved2,					//保留
} UC_SESSION_TYPE_E;

//会议状态
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

//会话参数的枚举
typedef enum
{
	UC_ConvIdentifier = 0,			//会话ID
	UC_ConvSubject,					//会话主题

	UC_ConvConfIdentifier,			//语音会议ID

	UC_ConvTempGroupUri,			//临时群URI
	UC_ConvFixedGroupUri,			//固定群URI
	UC_ConvHistoryGroupUri,			//历史临时群URI

	UC_ConvBookingConfUri,			/*!< mark if join booking conference*/
	UC_ConvTypeUri,					//保留
	UC_ConvConfSubject,				//保留
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
	char origin[URI_LENGTH];		//消息发送方SIP地址（URI）
	char target[URI_LENGTH];		//消息接收方对象（SIP URI + 终端类型）
	char content[CONTENT_LENGTH];	//消息内容
	char rcv_time[TIME_LENGTH];		//接收时间
	char name[NAME_LENGTH];			//发送方称呼
	char msgid[MSGID_LENGTH];		//消息ID
	int  chatType;					//消息类型
} UCIMMessage;

typedef struct
{
	char id_[ID_LENGTH];			//用户ID
	char uri_[URI_LENGTH];			//SIP URI
	char ucAcc_[NAME_LENGTH];		//账号
	char staffNo_[ID_LENGTH];		//工号
	char name_[NAME_LENGTH];		//姓名
	char nickName_[NAME_LENGTH];	//昵称
	char qpinyin_[NAME_LENGTH];		//姓名拼音全称
	char spinyin_[NAME_LENGTH];		//姓名拼音简称
	char homePhone_[NUMBER_LENGTH];	//家庭电话号码
	char officePhone_[NUMBER_LENGTH];//办公室电话号码
	char mobile_[NUMBER_LENGTH];	//手机号码
	char otherPhone_[NUMBER_LENGTH];//其他电话号码
	char address_[ADDRESS_LENGTH];	//地址信息
	char email_[EMAIL_LENGTH];		//EMAIL地址
	char fax_[NUMBER_LENGTH];		//传真号码
	char corpName_[NAME_LENGTH];	//公司名称
	char deptName_[NAME_LENGTH];	//部门名称
	char webSite_[WEB_LENGTH];		//网站地址
	char desc_[NORMAL_LENGTH];		//描叙
	char zip_[NUMBER_LENGTH];		//邮政编码
	char signature_[NORMAL_LENGTH];	//个性签名
	char imageID_[ID_LENGTH];		//头像ID
	char position_[NORMAL_LENGTH];	//位置
	char location_[NORMAL_LENGTH];	//地址
	char tzone_[TIME_LENGTH];		//所在时区
	char avtool_[NORMAL_LENGTH];	//可用的设备（如麦克风、扬声器、摄像头）
	char device_[TYPE_LENGTH];		//设备类型
	char terminalType_[TYPE_LENGTH];//接入终端类型（PC或Mobile等）
} UCContact;

typedef struct
{
	char topic[NORMAL_LENGTH];		//会议主题
	char meetingtime[TIME_LENGTH];	//召开时间
	char convener[URI_LENGTH];		//召集人
	char convenername[NAME_LENGTH];	//主持人
	UCAccount* attendeelist;		//与会人列表
	char accessnum[NUMBER_LENGTH];	//接入号
	char securitycode[NUMBER_LENGTH];//接入安全码
	char iscycle[BOOL_LENGTH];		//是否是周期会议
	char startdate[TIME_LENGTH];	//开始日期
	char validityperiod[TIME_LENGTH];//持续时间
	char content[CONTENT_LENGTH];	//会议内容
	char chairmanpwd[PWD_LENGTH];	//主席密码
	char partmanpwd[PWD_LENGTH];	//与会者密码
	char recordcode[PWD_LENGTH];	//录音码，保留
	char funcbits[TYPE_LENGTH];		//会议功能位
	char mediaBits[TYPE_LENGTH];	//媒体类型
	int	 confType;					//会议类型：0：即时会议 1：预约会议 2：周期会议 3：永久会议
	char confid[ID_LENGTH];			//会议ID
	char confStyle[TYPE_LENGTH];	//会议类型
} UCBookConf;

//群组
typedef struct
{
	char name_[NAME_LENGTH];		//群组名
	char id_[ID_LENGTH];			//群组ID
	int	 type_;						//群组类型
	int  readonly_;					//群组是否只读
} UCGroup;

typedef struct
{
	char name_[NAME_LENGTH];		//群组名
	char id_[ID_LENGTH];			//群组ID
	int	 type_;						//群组类型
	int  readonly_;					//群组是否只读
	int  indexno_;					//group index no.
} UCCustomGroup;

typedef struct
{
	char name_[NAME_LENGTH];		//群组名
	char id_[ID_LENGTH];			//群组ID
	int	 type_;						//群组类型
	int  readonly_;					//群组是否只读
} UCFavoriteGroup;

typedef struct
{
	char name_[NAME_LENGTH];		//群组名
	char id_[ID_LENGTH];			//群组ID
	int	 type_;						//群组类型
	int  readonly_;					//群组是否只读
	char creator_[NAME_LENGTH];		//群组创建者
	char uri_[URI_LENGTH];			//群组uri
	char groupno_[ID_LENGTH];		//群组号
	char desc_[NORMAL_LENGTH];		//群组描叙
	char bulletin_[CONTENT_LENGTH];	//群组公告
	char owneruri_[URI_LENGTH];		//群主uri
	int  capacity_;					//群组最大成员数
	char needpermit_[BOOL_LENGTH];	//是否需要通过群主验证后加入
} UCFixedGroup;

typedef struct
{
	int  hWnd;						//窗口句柄
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
	int	 autoanswerdelay;			//自动应答延时时长(单位：秒)，改变量只有在callalertinfo_==3的情况下生效
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
//回调函数指针

/**
 *登录登出回调函数
 * 
 *该函数用于登录登出回调函数
 *
 *@param[in] 	state		登陆状态 参考UC_SIGNIN_STATE_E
 *@param[in] 	reason		参考 DataDef.h 定义SignIn reason
 *@attention	无
 *@par 			无
**/
typedef void (CALLBACK *UCClientSignInNotify)(int state, const char* reason);

/**
 *联系人状态改变回调函数
 * 
 *该函数用于联系人状态改变回调函数
 *
 *@param[in] 	state		状态
 *@param[in] 	desc		
 *@param[in] 	contact
 *@param[in] 	param
 *@attention	无
 *@par 			无
**/
typedef void (CALLBACK *UCStatusChanged)(int state, const char* desc, const UCContact* contact, const char* param);

/**
 *联系人列表变更回调函数
 * 
 *该函数用于联系人列表变更回调函数
 *
 *@attention	无
 *@par 			无
**/
typedef void (CALLBACK *UCIncreContactsChanged)(void);

/**
 *语音来电（包括：会议和VoIP）回调函数
 * 
 *该函数用于语音来电（包括：会议和VoIP）回调函数
 *
 *@param[in] 	propMap		
 *@param[in] 	memberlist	成员列表，如果是会议则memberlist[0]是会议主席
 *@param[in] 	avParam		视频参数
 *@attention	无
 *@par 			无
**/
typedef void (CALLBACK *UCAVSessAdded)(const UCConversationPropMap* propMap, const UCAccountList* memberlist, const UCAudioVideoParam* avParam);//memberlist: the first value of the vector is leader if it's conference.

/**
 *语音通话建立（包括：会议和VoIP）回调函数
 * 
 *该函数用于语音通话建立（包括：会议和VoIP）回调函数
 *
 *@param[in] 	convId		会话ID
 *@attention	无
 *@par 			无
**/
typedef void (CALLBACK *UCAVSessionConnected)(const char* convId);

/**
 *语音通话关闭（包括：会议和VoIP）回调函数
 * 
 *该函数用于语音通话关闭（包括：会议和VoIP）回调函数
 *
 *@param[in] 	convId		会话ID
 *@attention	无
 *@par 			无
**/
typedef void (CALLBACK *UCAVSessionClosed)(const char* convId);

/**
 *会议成员状态变化回调函数
 * 
 *该函数用于会议成员状态变化回调函数
 *
 *@param[in] 	convId		会话ID
 *@param[in] 	chgtype		会议状态 参考MEM_CHG_STATUS_E
 *@param[in] 	memberuri	会议成员uri
 *@attention	无
 *@par 			无
**/
typedef void (CALLBACK *UCConvMemberStatusChanged)(const char* convId, int chgtype, const char* memberuri);

/**
 *与会者允许发言回调函数
 * 
 *该函数用于与会者允许发言回调函数
 *
 *@param[in] 	convId		会话ID
 *@param[in] 	member		与会成员
 *@attention	无
 *@par 			无
**/
typedef void (CALLBACK *UCConvMemAllowSpeak)(const char* convId, const UCContact* member);

/**
 *与会者禁止发言回调函数
 * 
 *该函数用于与会者禁止发言回调函数
 *
 *@param[in] 	convId		会话ID
 *@param[in] 	member		与会成员
 *@attention	无
 *@par 			无
**/
typedef void (CALLBACK *UCConvMemForbidSpeak)(const char* convId, const UCContact* member);

/**
 *与会者正在发言回调函数
 * 
 *该函数用于与会者正在发言回调函数
 *
 *@param[in] 	convId		会话ID
 *@param[in] 	member		与会成员
 *@attention	无
 *@par 			无
**/
typedef void (CALLBACK *UCConvMemCurSpeaker)(const char* convId, const UCContact* member);

/**
 *与会成员变动回调函数
 * 
 *该函数用于与会成员变动回调函数
 *
 *@param[in] 	convId		会话ID
 *@param[in] 	chgtype		参考 GROUP_MEM_CHANGED_E
 *@param[in] 	memberuri	会议成员uri
 *@attention	无
 *@par 			无
**/
typedef void (CALLBACK *UCConvGroupMemberChanged)(const char* convId, int chgtype, const char* memberuri);

/**
 *接收即时消息回调函数
 * 
 *该函数用于接收即时消息回调函数
 *
 *@param[in] 	propMap
 *@param[in] 	memberlist	成员列表，如果是会议则memberlist[0]是会议主席
 *@param[in] 	ImMessage	IM消息
 *@attention	无
 *@par 			无
**/
typedef void (CALLBACK *UCReceivedIMMessage)(const UCConversationPropMap* propMap, const UCAccountList* memberlist, const UCIMMessage* ImMessage);//memberlist: the first value of the vector is leader if it's conference.

/**
 *临时群组关闭回调函数
 * 
 *该函数用于临时群组关闭回调函数
 *
 *@param[in] 	convId
 *@attention	无
 *@par 			无
**/
typedef void (CALLBACK *UCInstantSessRemoved)(const char* convId);

/**
 *加入临时群组回调函数
 * 
 *该函数用于加入临时群组回调函数
 *
 *@param[in] 	convId
 *@param[in] 	member
 *@attention	无
 *@par 			无
**/
typedef void (CALLBACK *UCInstantSessAdded)(const char* convId, const UCContact* member);

/**
 *接收系统消息回调函数
 * 
 *该函数用于接收系统消息回调函数
 *
 *@param[in] 	origin
 *@param[in] 	subject
 *@param[in] 	content
 *@param[in] 	rcv_time
 *@param[in] 	msgid
 *@param[in] 	msgtype
 *@attention	参考 IMMessage
 *@par 			无
**/
typedef void (CALLBACK *UCSysMsgRecved)(const char* origin, const char* subject, const char* content, const char* rcv_time, const char* msgid, int msgtype);

/**
 *被邀请加入群组回调函数
 * 
 *该函数用于被邀请加入群组回调函数
 *
 *@param[in] 	fixedGroup
 *@attention	无
 *@par 			无
**/
typedef void (CALLBACK *UCGroupInvitation)(const UCFixedGroup* fixedGroup);

/**
 *被邀请的联系人应答加入群组回调函数
 * 
 *该函数用于被邀请的联系人应答加入群组回调函数
 *
 *@param[in] 	fixedGroup
 *@param[in] 	invitername
 *@param[in] 	result			1同意，其他拒绝
 *@attention	无
 *@par 			无
**/
typedef void (CALLBACK *UCGroupInvitationRes)(const UCFixedGroup* fixedGroup, const char* invitername, int result);

/**
 *离开固定群组回调函数
 * 
 *该函数用于离开固定群组回调函数
 *
 *@param[in] 	fixedGroup
 *@param[in] 	reason			0: 被踢出群组, 1: 群组解散
 *@attention	无
 *@par 			无
**/
typedef void (CALLBACK *UCLeaveFromFixedGroup)(const UCFixedGroup* fixedGroup, int reason);

/**
 *请求加入固定群组回调函数
 * 
 *该函数用于请求加入固定群组回调函数
 *
 *@param[in] 	fixedGroup
 *@param[in] 	inviteruri
 *@attention	无
 *@par 			无
**/
typedef void (CALLBACK *UCJoinFixedGroupRequest)(const UCFixedGroup* fixedGroup, const char* inviteruri);

/**
 *请求加入固定群组返回回调函数
 * 
 *该函数用于请求加入固定群组返回回调函数
 *
 *@param[in] 	fixedGroup
 *@param[in] 	invitername
 *@param[in] 	result			1同意，其他拒绝
 *@attention	无
 *@par 			无
**/
typedef void (CALLBACK *UCJoinFixedGroupRes)(const UCFixedGroup* fixedGroup, const char* invitername, int result);

/**
 *群组成员增加回调函数
 * 
 *该函数用于群组成员增加回调函数
 *
 *@param[in] 	fixedGroup
 *@param[in] 	member
 *@attention	无
 *@par 			无
**/
typedef void (CALLBACK *UCMemberAdded)(const UCFixedGroup* fixedGroup, const UCContact* member);

/**
 *群组成员离开回调函数
 * 
 *该函数用于群组成员离开回调函数
 *
 *@param[in] 	fixedGroup
 *@param[in] 	member
 *@attention	无
 *@par 			无
**/
typedef void (CALLBACK *UCMemberRemoved)(const UCFixedGroup* fixedGroup, const UCContact* member);

/**
 *群组管理员变更回调函数
 * 
 *该函数用于群组管理员变更回调函数
 *
 *@param[in] 	fixedGroup
 *@param[in] 	member
 *@attention	无
 *@par 			无
**/
typedef void (CALLBACK *UCMemberFlowChanged)(const UCFixedGroup* fixedGroup, const UCContact* member);

/**
 *群组信息变更回调函数
 * 
 *该函数用于群组信息变更回调函数
 *
 *@param[in] 	fixedGroup
 *@attention	无
 *@par 			无
**/
typedef void (CALLBACK *UCFixedGroupInfoChanged)(const UCFixedGroup* fixedGroup);

/**
 *收到文件传输回调函数
 * 
 *该函数用于收到文件传输回调函数
 *
 *@param[in] 	fileid
 *@param[in] 	filename
 *@param[in] 	filesize
 *@param[in] 	originName
 *@attention	无
 *@par 			无
**/
typedef void (CALLBACK *UCNewFileRercved)(const char* fileid, const char* filename, int filesize, const char* originName);

/**
 *接收文件回调函数
 * 
 *该函数用于接收文件回调函数
 *
 *@param[in] 	fileid
 *@attention	无
 *@par 			无
**/
typedef void (CALLBACK *UCFileAccept)(const char* fileid);

/**
 *取消文件传输回调函数
 * 
 *该函数用于取消文件传输回调函数
 *
 *@param[in] 	fileid
 *@param[in] 	reason
 *@param[in] 	errcode
 *@attention	无
 *@par 			无
**/
typedef void (CALLBACK *UCFileCancel)(const char* fileid, const char* reason, const char* errcode);

/**
 *文件传输进度回调函数
 * 
 *该函数用于文件传输进度回调函数
 *
 *@param[in] 	fileid
 *@param[in] 	procent
 *@attention	无
 *@par 			无
**/
typedef void (CALLBACK *UCFileProgress)(const char* fileid, const char* procent);

//////////////////////////////////////////////////////////////////////////


#endif