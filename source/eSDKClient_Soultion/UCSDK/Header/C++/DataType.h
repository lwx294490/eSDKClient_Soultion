#ifndef _DATA_TYPE_H_
#define _DATA_TYPE_H_

#ifdef ESDKCLIENTPLATFORM_EXPORTS
#ifndef UCSDK_EXPORTS
#define UCSDK_EXPORTS
#endif
#endif

#ifndef CALLBACK
#define CALLBACK __stdcall
#endif

#ifdef UCSDK_EXPORTS
#define UCSDK_API __declspec(dllexport)
#else
#define UCSDK_API __declspec(dllimport)
#endif

#include <string>
#include <map>
#include <vector>


namespace eSDK {
	namespace UC {


//////////////////////////////////////////////////////////////////////////
//UCSDK返回码
enum UCSDK_API UCSDK_RETURN_CODE_E
{
	UCSDK_Succ = 0,					//成功
	UCSDK_Fail,						//失败
	UCSDK_InvalidParam,				//错误入参
	UCSDK_NullPoint,				//空指针
	UCSDK_NotFound,					//没有找到
	UCSDK_ExistAVSess				//已经存在AVSession
};

//登陆状态
enum UCSDK_API UCSDK_SIGNIN_STATE_E
{
	SIGN_Client_Uninited,
	SIGN_Client_SignedFailed,		//登陆失败
	SIGN_Client_SigningIn,			//登陆中
	SIGN_Client_SignedIn,			//登陆成功
	SIGN_Client_KickedOut,			//被提出
	SIGN_Client_Invalid				//保留
};

//呼叫类型
enum UCSDK_API CALL_TYPE_E
{
	Call_Audio = 0,					//语音呼叫
	Call_Video						//视频呼叫
};

//静音设备类型
enum UCSDK_API MUTE_DEVICE_E
{
	Dev_Mic = 0,					//麦克风设备
	Dev_Speaker						//扬声器设备
};

//IM消息类型
enum UCSDK_API INSTANT_MSG_TYPE_E
{
	IM_ChatP2PIM = 0,				//点对点消息
	IM_ChatFixedGroup = 1,			//固定群消息
	IM_ChatInputStatus = 3,			//当前聊天窗口输入状态
	IM_ChatOfflineFile = 4,			//离线文件传输
	IM_ChatAddFriend = 5,			//系统预留，暂未使用
	IM_ChatErrorMsg = 6,			//系统预留，暂未使用
};

//发布联系人信息类型
enum UCSDK_API PUB_CONTACT_INFO_TYPE_E
{
	PUB_Availability = 0,			//状态
	PUB_CustomStatusDesc,			//自定义状态的描述（暂不使用）
	PUB_Position,					//职位（暂不使用）
	PUB_Location,					//地址（暂不使用）
	PUB_AVTool,						//设备（暂不使用）
	PUB_Signature,					//签名
	PUB_HeadImage,					//头像（暂不使用）
	PUB_CallDeviceDesc,				//呼叫设备描述（暂不使用）
	PUB_Invalid						//不合法
};

//联系人状态
enum UCSDK_API CONTACT_AVAILABILITY_E
{
	State_Offline = 0,				//离线
	State_Online,					//在线
	State_Hide,						//隐身
	State_Busy,						//忙碌
	State_Leave,					//离开
	State_NoDisturb,				//免打扰
	State_InvalidStatus				//状态未知
};

//群组类型
enum UCSDK_API GROUP_TYPE_E
{
	GT_CustomGroupType = 0,
	GT_FixedGroupType,
	GT_FavoriteGroupType
};

//会话类型定义
enum UCSDK_API SESSION_TYPE_E
{
	Sess_Invalid = 0,				//不合法
	Sess_InstantMessage = 1,		//即时消息会话
	Sess_AudioVideo,				//音视频呼叫(会议)会话
	Sess_DataSharing,				//数据共享会话
	Sess_CallExBusiness,			//呼叫扩展会话
	Sess_Reserved1,					//保留
	Sess_Reserved2,					//保留
};

//会议状态
enum UCSDK_API MEM_CHG_STATUS_E
{
	Conf_Inviting = 0,
	Conf_Hangup,
	Conf_InConf,
	Conf_Quit,
	Conf_InHold,
	Conf_Needreffer = 5
};
enum UCSDK_API MEM_SPK_STATUS_E
{
	Conf_AllowSpk = 6,
	Conf_ForbidSpk,
	Conf_CurSpker
};

enum UCSDK_API GROUP_MEM_CHANGED_E
{
	Conf_MemAdd = 9,
	Conf_MemDel
};

//会话参数的枚举
enum UCSDK_API CONVERSATION_PROPERTY_E
{
	Prop_ConvIdentifier = 0,		//会话ID
	Prop_ConvSubject,				//会话主题

	Prop_ConvConfIdentifier,		//语音会议ID

	Prop_ConvTempGroupUri,			//临时群URI
	Prop_ConvFixedGroupUri,			//固定群URI
	Prop_ConvHistoryGroupUri,		//历史临时群URI

	Prop_ConvBookingConfUri,		/*!< mark if join booking conference*/
	Prop_ConvTypeUri,				//保留
	Prop_ConvConfSubject,			//保留
	Prop_ConvReserved2,				/*!< reserver property for future*/
	Prop_ConvReserved3,				/*!< reserver property for future*/
	Prop_ConvReserved4,				/*!< reserver property for future*/
	Prop_ConvReserved5,				/*!< reserver property for future*/
};

//////////////////////////////////////////////////////////////////////////
//SignIn reason
#define UCSDK_SIGNINFAIL_GETUPDATE		"getupdate"; // aa:AAresult
#define UCSDK_SIGNINFAIL_AA				"aa"; // aa:AAresult
#define UCSDK_SIGNINFAIL_CONTACT		"contact";
#define UCSDK_SIGNINFAIL_SIP			"sip";
#define UCSDK_SIGNINFAIL_SIP_KICKOUT	"sipkickout";

#define UCSDK_SIGNIN_NOK				"signin";
#define UCSDK_SIGNOUT_OK				"signout";
#define UCSDK_SIGNOUT_FAILED			"signoutfailed";

#define UCSDK_SIGNINFAIL_NOIP			"noip";
#define UCSDK_SIGNINFAIL_HASIP			"hasip";

//////////////////////////////////////////////////////////////////////////

struct UCSDK_API IMMessage
{
	std::string origin;				//消息发送方SIP地址（URI）
	std::string target;				//消息接收方对象（SIP URI + 终端类型）
	std::string content;			//消息内容
	std::string rcv_time;			//接收时间
	std::string name;				//发送方称呼
	std::string msgid;				//消息ID
	INSTANT_MSG_TYPE_E chatType;	//消息类型
};

struct UCSDK_API UCSDKContact
{
	std::string id_;				//用户ID
	std::string uri_;				//SIP URI
	std::string ucAcc_;				//账号
	std::string staffNo_;			//工号
	std::string name_;				//姓名
	std::string nickName_;			//昵称
	std::string qpinyin_;			//姓名拼音全称
	std::string spinyin_;			//姓名拼音简称
	std::string homePhone_;			//家庭电话号码
	std::string officePhone_;		//办公室电话号码
	std::string mobile_;			//手机号码
	std::string otherPhone_;		//其他电话号码
	std::string address_;			//地址信息
	std::string email_;				//EMAIL地址
	std::string fax_;				//传真号码
	std::string corpName_;			//公司名称
	std::string deptName_;			//部门名称
	std::string webSite_;			//网站地址
	std::string desc_;				//描叙
	std::string zip_;				//邮政编码
	std::string signature_;			//个性签名
	std::string imageID_;			//头像ID
	std::string position_;			//位置
	std::string location_;			//地址
	std::string tzone_;				//所在时区
	std::string avtool_;			//可用的设备（如麦克风、扬声器、摄像头）
	std::string device_;			//设备类型
	std::string terminalType_;		//接入终端类型（PC或Mobile等）
};

struct UCSDK_API UCSDKBookConfInfo
{
	std::string topic;				//会议主题
	std::string meetingtime;		//召开时间
	std::string convener;			//召集人
	std::string convenername;		//主持人
	std::vector<std::string> attendeelist;	//与会人列表
	std::string accessnum;			//接入号
	std::string securitycode;		//接入安全码
	std::string iscycle;			//是否是周期会议
	std::string startdate;			//开始日期
	std::string validityperiod;		//持续时间
	std::string content;			//会议内容
	std::string chairmanpwd;		//主席密码
	std::string partmanpwd;			//与会者密码
	std::string recordcode;			//录音码，保留
	std::string funcbits;			//会议功能位
	std::string mediaBits;			//媒体类型
	int			confType;			//会议类型：0：即时会议 1：预约会议 2：周期会议 3：永久会议
	std::string confid;				//会议ID
	std::string confStyle;			//会议类型
};

//群组
struct UCSDK_API UCSDKGroup
{
	std::string name_;				//群组名
	std::string id_;				//群组ID
	int			type_;				//群组类型
	bool		readonly_;			//群组是否只读
};

struct UCSDK_API UCSDKCustomGroup : public UCSDKGroup
{
	int			indexno_;			//group index no.
};

struct UCSDK_API UCSDKFavoriteGroup : public UCSDKGroup
{

};

struct UCSDK_API UCSDKFixedGroup : public UCSDKGroup
{
	std::string creator_;			//群组创建者
	std::string uri_;				//群组uri
	std::string groupno_;			//群组号
	std::string desc_;				//群组描叙
	std::string bulletin_;			//群组公告
	std::string owneruri_;			//群主uri
	int			capacity_;			//群组最大成员数
	std::string needpermit_;		//是否需要通过群主验证后加入
};

struct UCSDK_API STVideoWindow
{
	int			hWnd;				//窗口句柄
	int			left;       
	int			top;  
	int			width;
	int			height;	
};

struct UCSDK_API STAudioVideoParam
{
	std::string caller_;
	std::string callername_;
	int			callalertinfo_;
	int			autoanswerdelay;	//自动应答延时时长(单位：秒)，改变量只有在callalertinfo_==3的情况下生效
	std::string lineindex_;
	bool		isvideo_;
	bool		callmode_;
	bool		isdataconf_;
};

//////////////////////////////////////////////////////////////////////////
typedef std::vector<std::string>						AccountList;
typedef std::map<PUB_CONTACT_INFO_TYPE_E, std::string>	PublishInfoMap;
typedef std::vector<UCSDKBookConfInfo>					UCSDKBookConfList;
typedef std::vector<UCSDKContact>						UCSDKContactList;
typedef std::vector<UCSDKFixedGroup>					UCSDKFixedGroupList;
typedef std::vector<UCSDKCustomGroup>					UCSDKCustomGroupList;
typedef std::map<CONVERSATION_PROPERTY_E, std::string>	ConversationPropMap;


}
}

#endif
