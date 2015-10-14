
// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���Ǿ���ʹ�õ��������ĵ�
// �ض�����Ŀ�İ����ļ�

#pragma once

#ifndef _SECURE_ATL
#define _SECURE_ATL 1
#endif

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // �� Windows ͷ���ų�����ʹ�õ�����
#endif

#include "targetver.h"

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // ĳЩ CString ���캯��������ʽ��

// �ر� MFC ��ĳЩ�����������ɷ��ĺ��Եľ�����Ϣ������
#define _AFX_ALL_WARNINGS

#include <afxwin.h>         // MFC ��������ͱ�׼���
#include <afxext.h>         // MFC ��չ


#include <afxdisp.h>        // MFC �Զ�����



#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           // MFC �� Internet Explorer 4 �����ؼ���֧��
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>             // MFC �� Windows �����ؼ���֧��
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <afxcontrolbars.h>     // �������Ϳؼ����� MFC ֧��







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


#include <string>
#include <map>
#include <vector>
//Ӧ��UC SDKͷ�ļ�
#include "eSDKClient_Platform.h"
#include "UCSignIn.h"
#include "UCContactMgr.h"
#include "UCSignalRecv.h"
#include "UCGroup.h"
#include "UCIM.h"
#include "UCVoIP.h"
#include "UCMeeting.h"
#include "UCPublic.h"

//��̬Ӧ��Dll���ļ�
#pragma comment(lib, "eSDKClientPlatform.lib")

//////////////////////////////////////////////////////////////////////////
#define ECS_MSG_BEGIN			(WM_APP + 1001) //��Ϣ��ʼID
#define WM_SIGNIN_NOTIFY		(ECS_MSG_BEGIN+1)	//��½�ǳ���Ȩ��Ϣ
#define WM_STATUS_CHANGED		(ECS_MSG_BEGIN+2)	//��ϵ��״̬�ı���Ϣ
#define WM_AVSESSION_ADDED		(ECS_MSG_BEGIN+3)	//�����磨VoIP��Meeting����Ϣ
#define WM_AVSESSION_CONNECTED	(ECS_MSG_BEGIN+4)	//ͨ��������Ϣ
#define WM_AVSESSION_CLOSED		(ECS_MSG_BEGIN+5)	//ͨ���ر���Ϣ
#define WM_INPUT_STRING			(ECS_MSG_BEGIN+6)	//������¼���Ϣ
#define WM_CHAT_CLOSEED			(ECS_MSG_BEGIN+7)	//���촰�ڹر�
#define WM_ACCEPT_CALL			(ECS_MSG_BEGIN+8)	//��������
#define WM_REJECT_CALL			(ECS_MSG_BEGIN+9)	//�ܾ�����
#define WM_FORWARD_CALL			(ECS_MSG_BEGIN+10)	//����ǰת
#define WM_RECV_IM				(ECS_MSG_BEGIN+11)	//���ռ�ʱ��Ϣ
#define WM_CONF_STATUS_CHANGE	(ECS_MSG_BEGIN+12)	//����Ա״̬�ı�
#define WM_CONF_ALLOW_SPEAK		(ECS_MSG_BEGIN+13)	//����Ա������
#define WM_CONF_FORBID_SPEAK	(ECS_MSG_BEGIN+14)	//����Ա��ֹ����
#define WM_CONF_CUR_SPEAKER		(ECS_MSG_BEGIN+15)	//����Ա���ڷ���
#define WM_IM_SESS_REMOVE		(ECS_MSG_BEGIN+16)	//��ʱȺ������ر�
#define WM_JOIN_CONFERENCE		(ECS_MSG_BEGIN+17)	//����ԤԼ����
#define WM_BASE_CLOSE			(ECS_MSG_BEGIN+18)	//UC�����ڹر�
#define WM_GROUP_INVITATION		(ECS_MSG_BEGIN+19)	//�յ��̶�Ⱥ��������Ϣ
#define WM_GROUP_INVITATIONRES	(ECS_MSG_BEGIN+20)	//�յ��̶�Ⱥ��������Ϣ��Ӧ
#define WM_GROUP_MEMBER_CHANGED (ECS_MSG_BEGIN+21)	//�̶�Ⱥ���Ա�䶯��Ϣ
#define WM_GROUP_LEAVE_FIXED	(ECS_MSG_BEGIN+22)	//�̶�Ⱥ���ɢ���߳��̶�Ⱥ��
#define WM_GROUP_JOIN_FIXED_REQ	(ECS_MSG_BEGIN+23)	//����̶�Ⱥ������
#define WM_GROUP_JOIN_FIXED_RSP	(ECS_MSG_BEGIN+23)	//����̶�Ⱥ������Ӧ��


#define ID_MENU_CONTACT_BEGIN		33100
#define ID_MENU_IM					(ID_MENU_CONTACT_BEGIN+1)	//��ʱ��Ϣ�˵�
#define ID_MENU_CALL				(ID_MENU_CONTACT_BEGIN+2)	//�������в˵�
#define ID_MENU_VIDEOCALL			(ID_MENU_CONTACT_BEGIN+3)	//��Ƶ���в˵�
#define ID_MENU_ADD_GROUP			(ID_MENU_CONTACT_BEGIN+4)	//�����ϵ�˷���˵�
#define ID_MENU_RM_GROUP			(ID_MENU_CONTACT_BEGIN+5)	//ɾ����ϵ�˷���˵�
#define ID_MENU_ADD_CONTACT			(ID_MENU_CONTACT_BEGIN+6)	//����ϵ�˷���������ϵ�˲˵�
#define ID_MENU_RM_CONTACT			(ID_MENU_CONTACT_BEGIN+7)	//����ϵ�˷���ɾ����ϵ�˲˵�
#define ID_MENU_MOVE_CONTACT		(ID_MENU_CONTACT_BEGIN+8)	//�ƶ���ϵ�˵�XXX����˵�

#define ID_MENU_DISMISS_FIXED		(ID_MENU_CONTACT_BEGIN+20)	//�̶�Ⱥ���ɢ
#define ID_MENU_ADD_FIXED			(ID_MENU_CONTACT_BEGIN+21)	//��ӹ̶�Ⱥ��
#define ID_MENU_RM_FIXED_CONTACT	(ID_MENU_CONTACT_BEGIN+22)	//ɾ���̶�Ⱥ���Ա
#define ID_MENU_ADD_FIXED_CONTACT	(ID_MENU_CONTACT_BEGIN+23)	//���ӹ̶�Ⱥ���Ա
#define ID_MENU_RENAME_FIXED		(ID_MENU_CONTACT_BEGIN+24)	//�̶�Ⱥ��������

#define ID_MENU_CONTACT_END			(ID_MENU_CONTACT_BEGIN+99)


#define ID_MENU_CONF_BEGIN			33200
#define ID_MENU_DELETE_MEM			(ID_MENU_CONF_BEGIN+1)		//�Ƴ�����Ա�˵�
#define ID_MENU_ENDCALL_MEM			(ID_MENU_CONF_BEGIN+2)		//�Ҷ�����Ա�˵�
#define ID_MENU_REINVITE_MEM		(ID_MENU_CONF_BEGIN+3)		//������������Ա�˵�
#define ID_MENU_MUTE_MEM			(ID_MENU_CONF_BEGIN+4)		//��ֹ����Ա���Բ˵�
#define ID_MENU_UNMUTE_MEM			(ID_MENU_CONF_BEGIN+5)		//��������Ա���Բ˵�


#define ID_MENU_BOOK_CONF_BEGIN		33400
#define ID_MENU_JOIN_BOOK_CONF		(ID_MENU_BOOK_CONF_BEGIN+1)	//����ԤԼ����˵�
#define ID_MENU_BOOK_CONF_END		(ID_MENU_BOOK_CONF_BEGIN+10)
//////////////////////////////////////////////////////////////////////////
//��ϵ���б�͹̶�Ⱥ���б�����
typedef struct _treeItemData
{
	CString id_;
	CString uri_;
	CString name_;
	CString ucAcc_;
	HTREEITEM hItem;
} TREEITEMDATA, *PTREEITEMDATA;

//������ṹ��
struct AVParam
{
	std::string caller_;
	std::string callername_;
	std::string lineindex_;
	int callalertinfo_;
	int autoanswerdelay;
	bool isvideo_;
	bool callmode_;
	bool isdataconf_;
};
struct AVSessAddedInfo
{
	AVParam avParam;
	std::map<UC_CONVERSATION_PROPERTY_E, std::string> propMap;
	std::vector<std::string> memlist;
	std::string forwardAcc;
};


struct IMMsg
{
	std::string origin;
	std::string target;
	std::string content;
	std::string rcv_time;
	std::string name;
	std::string msgid;
	int chatType;
};
struct IMMessageInfo
{
	IMMsg imMsg;
	std::map<UC_CONVERSATION_PROPERTY_E, std::string> propMap;
	std::vector<std::string> memlist;
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
//��������
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
const int IMGLIST_SIZE					= 8;//ͼ���б�ؼ�������ͼ�����
const int WIDTH							= 14;//listCtrl����ͼ��Ŀ��
const int HEIGHT						= 14;//listCtrl����ͼ��ĳ���


enum BOOK_CONF_LIST_E
{
	LIST_topic = 0,
	LIST_meetingtime,
	LIST_convenername,
	LIST_startdate,
	LIST_content
};
//���п��
const int static WIDTH_topic			= 100;
const int static WIDTH_meetingtime		= 250;
const int static WIDTH_convenername		= 100;
const int static WIDTH_startdate		= 100;
const int static WIDTH_content			= 300;


//ͼƬ����
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


//չʾ�б���е����
enum CONF_MEM_LIST_E
{
	LIST_NAME = 0,
	LIST_COMPERE_IMAGE,
	LIST_CALL_STATE_IMAGE,
	LIST_SPEAKING
};
//���п��
const int static WIDTH_MEMBER_NAME				= 100;
const int static WIDTH_MEMBER_COMPERE_IMAGE		= 70;
const int static WIDTH_MEMBER_CALLSTATE_IMAGE   = 70;
const int static WIDTH_MEMBER_SPEAKING			= 70;
