
// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件

#pragma once

#ifndef _SECURE_ATL
#define _SECURE_ATL 1
#endif

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // 从 Windows 头中排除极少使用的资料
#endif

#include "targetver.h"

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // 某些 CString 构造函数将是显式的

// 关闭 MFC 对某些常见但经常可放心忽略的警告消息的隐藏
#define _AFX_ALL_WARNINGS

#include <afxwin.h>         // MFC 核心组件和标准组件
#include <afxext.h>         // MFC 扩展


#include <afxdisp.h>        // MFC 自动化类



#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           // MFC 对 Internet Explorer 4 公共控件的支持
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>             // MFC 对 Windows 公共控件的支持
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <afxcontrolbars.h>     // 功能区和控件条的 MFC 支持







#ifdef _UNICODE
#if defined _M_IX86
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_IA64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='ia64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif
#endif


#include "eSDKClientPlatform.h"
#include "UCSDKAbsProxy.h"
#include "UCContactMgrAbsProxy.h"
#include "UCSignalRecvAbsProxy.h"
#include "UCGroupAbsProxy.h"
#include "UCIMAbsProxy.h"
#include "UCVoIPAbsProxy.h"
#include "UCMeetingAbsProxy.h"
#include "UCPublicAbsProxy.h"

using namespace eSDK::UC;

#pragma comment(lib, "eSDKClientPlatform.lib")


#define ECS_MSG_BEGIN			(WM_APP + 1001) //消息开始ID
#define WM_SIGNIN_NOTIFY		(ECS_MSG_BEGIN+1)
#define WM_STATUS_CHANGED		(ECS_MSG_BEGIN+2)
#define WM_AVSESSION_ADDED		(ECS_MSG_BEGIN+3)
#define WM_AVSESSION_CONNECTED	(ECS_MSG_BEGIN+4)
#define WM_AVSESSION_CLOSED		(ECS_MSG_BEGIN+5)
#define WM_INPUT_STRING			(ECS_MSG_BEGIN+6)
#define WM_CHAT_CLOSEED			(ECS_MSG_BEGIN+7)
#define WM_ACCEPT_CALL			(ECS_MSG_BEGIN+8)
#define WM_REJECT_CALL			(ECS_MSG_BEGIN+9)
#define WM_FORWARD_CALL			(ECS_MSG_BEGIN+10)
#define WM_RECV_IM				(ECS_MSG_BEGIN+11)
#define WM_CONF_STATUS_CHANGE	(ECS_MSG_BEGIN+12)
#define WM_CONF_ALLOW_SPEAK		(ECS_MSG_BEGIN+13)
#define WM_CONF_FORBID_SPEAK	(ECS_MSG_BEGIN+14)
#define WM_CONF_CUR_SPEAKER		(ECS_MSG_BEGIN+15)
#define WM_IM_SESS_REMOVE		(ECS_MSG_BEGIN+16)
#define WM_JOIN_CONFERENCE		(ECS_MSG_BEGIN+17)
#define WM_BASE_CLOSE			(ECS_MSG_BEGIN+18)
#define WM_GROUP_INVITATION		(ECS_MSG_BEGIN+19)
#define WM_GROUP_INVITATIONRES	(ECS_MSG_BEGIN+20)
#define WM_GROUP_MEMBER_CHANGED (ECS_MSG_BEGIN+21)
#define WM_GROUP_LEAVE_FIXED	(ECS_MSG_BEGIN+22)
#define WM_GROUP_JOIN_FIXED_REQ	(ECS_MSG_BEGIN+23)
#define WM_GROUP_JOIN_FIXED_RSP	(ECS_MSG_BEGIN+24)


#define ID_MENU_CONTACT_BEGIN		33100
#define ID_MENU_IM					(ID_MENU_CONTACT_BEGIN+1)
#define ID_MENU_CALL				(ID_MENU_CONTACT_BEGIN+2)
#define ID_MENU_VIDEOCALL			(ID_MENU_CONTACT_BEGIN+3)
#define ID_MENU_ADD_GROUP			(ID_MENU_CONTACT_BEGIN+4)
#define ID_MENU_RM_GROUP			(ID_MENU_CONTACT_BEGIN+5)
#define ID_MENU_ADD_CONTACT			(ID_MENU_CONTACT_BEGIN+6)
#define ID_MENU_RM_CONTACT			(ID_MENU_CONTACT_BEGIN+7)
#define ID_MENU_MOVE_CONTACT		(ID_MENU_CONTACT_BEGIN+8)

#define ID_MENU_DISMISS_FIXED		(ID_MENU_CONTACT_BEGIN+20)
#define ID_MENU_ADD_FIXED			(ID_MENU_CONTACT_BEGIN+21)
#define ID_MENU_RM_FIXED_CONTACT	(ID_MENU_CONTACT_BEGIN+22)
#define ID_MENU_ADD_FIXED_CONTACT	(ID_MENU_CONTACT_BEGIN+23)
#define ID_MENU_RENAME_FIXED		(ID_MENU_CONTACT_BEGIN+24)

#define ID_MENU_CONTACT_END			(ID_MENU_CONTACT_BEGIN+99)


#define ID_MENU_CONF_BEGIN			33200
#define ID_MENU_DELETE_MEM			(ID_MENU_CONF_BEGIN+1)
#define ID_MENU_ENDCALL_MEM			(ID_MENU_CONF_BEGIN+2)
#define ID_MENU_REINVITE_MEM		(ID_MENU_CONF_BEGIN+3)
#define ID_MENU_MUTE_MEM			(ID_MENU_CONF_BEGIN+4)
#define ID_MENU_UNMUTE_MEM			(ID_MENU_CONF_BEGIN+5)


#define ID_MENU_HISTORY_BEGIN		33300
#define ID_MENU_HISTORY_DELETE		(ID_MENU_HISTORY_BEGIN+1)
#define ID_MENU_HISTORY_CLEAR		(ID_MENU_HISTORY_BEGIN+2)


#define ID_MENU_BOOK_CONF_BEGIN		33400
#define ID_MENU_JOIN_BOOK_CONF		(ID_MENU_BOOK_CONF_BEGIN+1)
#define ID_MENU_BOOK_CONF_END		(ID_MENU_BOOK_CONF_BEGIN+10)

typedef struct _treeItemData
{
	CString id_;
	CString uri_;
	CString name_;
	CString ucAcc_;
	HTREEITEM hItem;
} TREEITEMDATA, *PTREEITEMDATA;

struct AVSessAddedInfo
{
	STAudioVideoParam avParam;
	ConversationPropMap propMap;
	AccountList memlist;
	std::string forwardAcc;
};

struct IMMessageInfo
{
	IMMessage imMsg;
	ConversationPropMap propMap;
	AccountList memlist;
};

struct ConfMemChgInfo
{
	int state;
	std::string convId;
	std::string memUri;
};

struct ConfMemSpkInfo
{
	int state;
	std::string convId;
	std::string ucAcc;
};

struct InputInfo
{
	CString szInput;
	CString szFlag;
	PTREEITEMDATA pTreeItemData;
};

struct JoinConfInfo
{
	std::string convId;
	std::string convener;
};

struct FixedGroupInfo
{
	std::string name_;
	std::string id_;
	int	 type_;
	bool readonly_;
	std::string creator_;
	std::string uri_;
	std::string groupno_;
	std::string desc_;
	std::string bulletin_;
	std::string owneruri_;
	int  capacity_;
	std::string needpermit_;
};

struct InvitationResInfo
{
	FixedGroupInfo group;
	std::string invName;
	int result;
};

struct GroupMemberChangedInfo
{
	FixedGroupInfo group;
	std::string name_;
	std::string ucAcc_;
	std::string uri_;
	std::string id_;
	int type;				//0: add, 1:remove
};

struct LeaveFromFixedGroupInfo
{
	FixedGroupInfo group;
	int reason;				//0: KickedFromFixedGroup, 1: FixedGroupDismissed
};

struct JoinFixedGroupReqInfo
{
	FixedGroupInfo group;
	std::string uri;
};

struct JoinFixedGroupRspInfo
{
	FixedGroupInfo group;
	std::string name;
	int result;
};

//////////////////////////////////////////////////////////////////////////
//常量定义
enum STATE_IMG_ID_E
{
	BITMAP_FOLD_ImgID = 0,
	BITMAP_UNFOLD_ImgID,
	BITMAP_BUSY_ImgID,
	BITMAP_LEAVE_ImgID,
	BITMAP_NODIS_ImgID,
	BITMAP_OFFLINE_ImgID,
	BITMAP_ONLINE_ImgID,
	BITMAP_GROUP_ImgID
};
const int IMGLIST_SIZE					= 8;//图像列表控件关联的图像个数
const int WIDTH							= 14;//listCtrl关联图像的宽度
const int HEIGHT						= 14;//listCtrl关联图像的长度


enum BOOK_CONF_LIST_E
{
	LIST_topic = 0,
	LIST_meetingtime,
	LIST_convenername,
	LIST_startdate,
	LIST_content
};
//各列宽度
const int static WIDTH_topic			= 100;
const int static WIDTH_meetingtime		= 250;
const int static WIDTH_convenername		= 100;
const int static WIDTH_startdate		= 100;
const int static WIDTH_content			= 300;


//图片定义
enum CONF_IMG_ID_E
{
	BITMAP_CallIng = 0,
	BITMAP_CallEst,
	BITMAP_CallLeave,
	BITMAP_CallMiss,
	BITMAP_Compere,
	BITMAP_Speaker,
	BITMAP_ConfMan,
	BITMAP_ConfWoman,
	BITMAP_MicMute,
	BITMAP_MicUnMute
};


//展示列表的列的序号
enum CONF_MEM_LIST_E
{
	LIST_NAME = 0,
	LIST_COMPERE_IMAGE,
	LIST_CALL_STATE_IMAGE,
	LIST_SPEAKING
};
//各列宽度
const int static WIDTH_MEMBER_NAME				= 100;
const int static WIDTH_MEMBER_COMPERE_IMAGE		= 70;
const int static WIDTH_MEMBER_CALLSTATE_IMAGE   = 70;
const int static WIDTH_MEMBER_SPEAKING			= 70;