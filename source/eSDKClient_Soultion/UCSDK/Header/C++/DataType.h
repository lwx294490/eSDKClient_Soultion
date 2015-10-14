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
//UCSDK������
enum UCSDK_API UCSDK_RETURN_CODE_E
{
	UCSDK_Succ = 0,					//�ɹ�
	UCSDK_Fail,						//ʧ��
	UCSDK_InvalidParam,				//�������
	UCSDK_NullPoint,				//��ָ��
	UCSDK_NotFound,					//û���ҵ�
	UCSDK_ExistAVSess				//�Ѿ�����AVSession
};

//��½״̬
enum UCSDK_API UCSDK_SIGNIN_STATE_E
{
	SIGN_Client_Uninited,
	SIGN_Client_SignedFailed,		//��½ʧ��
	SIGN_Client_SigningIn,			//��½��
	SIGN_Client_SignedIn,			//��½�ɹ�
	SIGN_Client_KickedOut,			//�����
	SIGN_Client_Invalid				//����
};

//��������
enum UCSDK_API CALL_TYPE_E
{
	Call_Audio = 0,					//��������
	Call_Video						//��Ƶ����
};

//�����豸����
enum UCSDK_API MUTE_DEVICE_E
{
	Dev_Mic = 0,					//��˷��豸
	Dev_Speaker						//�������豸
};

//IM��Ϣ����
enum UCSDK_API INSTANT_MSG_TYPE_E
{
	IM_ChatP2PIM = 0,				//��Ե���Ϣ
	IM_ChatFixedGroup = 1,			//�̶�Ⱥ��Ϣ
	IM_ChatInputStatus = 3,			//��ǰ���촰������״̬
	IM_ChatOfflineFile = 4,			//�����ļ�����
	IM_ChatAddFriend = 5,			//ϵͳԤ������δʹ��
	IM_ChatErrorMsg = 6,			//ϵͳԤ������δʹ��
};

//������ϵ����Ϣ����
enum UCSDK_API PUB_CONTACT_INFO_TYPE_E
{
	PUB_Availability = 0,			//״̬
	PUB_CustomStatusDesc,			//�Զ���״̬���������ݲ�ʹ�ã�
	PUB_Position,					//ְλ���ݲ�ʹ�ã�
	PUB_Location,					//��ַ���ݲ�ʹ�ã�
	PUB_AVTool,						//�豸���ݲ�ʹ�ã�
	PUB_Signature,					//ǩ��
	PUB_HeadImage,					//ͷ���ݲ�ʹ�ã�
	PUB_CallDeviceDesc,				//�����豸�������ݲ�ʹ�ã�
	PUB_Invalid						//���Ϸ�
};

//��ϵ��״̬
enum UCSDK_API CONTACT_AVAILABILITY_E
{
	State_Offline = 0,				//����
	State_Online,					//����
	State_Hide,						//����
	State_Busy,						//æµ
	State_Leave,					//�뿪
	State_NoDisturb,				//�����
	State_InvalidStatus				//״̬δ֪
};

//Ⱥ������
enum UCSDK_API GROUP_TYPE_E
{
	GT_CustomGroupType = 0,
	GT_FixedGroupType,
	GT_FavoriteGroupType
};

//�Ự���Ͷ���
enum UCSDK_API SESSION_TYPE_E
{
	Sess_Invalid = 0,				//���Ϸ�
	Sess_InstantMessage = 1,		//��ʱ��Ϣ�Ự
	Sess_AudioVideo,				//����Ƶ����(����)�Ự
	Sess_DataSharing,				//���ݹ���Ự
	Sess_CallExBusiness,			//������չ�Ự
	Sess_Reserved1,					//����
	Sess_Reserved2,					//����
};

//����״̬
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

//�Ự������ö��
enum UCSDK_API CONVERSATION_PROPERTY_E
{
	Prop_ConvIdentifier = 0,		//�ỰID
	Prop_ConvSubject,				//�Ự����

	Prop_ConvConfIdentifier,		//��������ID

	Prop_ConvTempGroupUri,			//��ʱȺURI
	Prop_ConvFixedGroupUri,			//�̶�ȺURI
	Prop_ConvHistoryGroupUri,		//��ʷ��ʱȺURI

	Prop_ConvBookingConfUri,		/*!< mark if join booking conference*/
	Prop_ConvTypeUri,				//����
	Prop_ConvConfSubject,			//����
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
	std::string origin;				//��Ϣ���ͷ�SIP��ַ��URI��
	std::string target;				//��Ϣ���շ�����SIP URI + �ն����ͣ�
	std::string content;			//��Ϣ����
	std::string rcv_time;			//����ʱ��
	std::string name;				//���ͷ��ƺ�
	std::string msgid;				//��ϢID
	INSTANT_MSG_TYPE_E chatType;	//��Ϣ����
};

struct UCSDK_API UCSDKContact
{
	std::string id_;				//�û�ID
	std::string uri_;				//SIP URI
	std::string ucAcc_;				//�˺�
	std::string staffNo_;			//����
	std::string name_;				//����
	std::string nickName_;			//�ǳ�
	std::string qpinyin_;			//����ƴ��ȫ��
	std::string spinyin_;			//����ƴ�����
	std::string homePhone_;			//��ͥ�绰����
	std::string officePhone_;		//�칫�ҵ绰����
	std::string mobile_;			//�ֻ�����
	std::string otherPhone_;		//�����绰����
	std::string address_;			//��ַ��Ϣ
	std::string email_;				//EMAIL��ַ
	std::string fax_;				//�������
	std::string corpName_;			//��˾����
	std::string deptName_;			//��������
	std::string webSite_;			//��վ��ַ
	std::string desc_;				//����
	std::string zip_;				//��������
	std::string signature_;			//����ǩ��
	std::string imageID_;			//ͷ��ID
	std::string position_;			//λ��
	std::string location_;			//��ַ
	std::string tzone_;				//����ʱ��
	std::string avtool_;			//���õ��豸������˷硢������������ͷ��
	std::string device_;			//�豸����
	std::string terminalType_;		//�����ն����ͣ�PC��Mobile�ȣ�
};

struct UCSDK_API UCSDKBookConfInfo
{
	std::string topic;				//��������
	std::string meetingtime;		//�ٿ�ʱ��
	std::string convener;			//�ټ���
	std::string convenername;		//������
	std::vector<std::string> attendeelist;	//������б�
	std::string accessnum;			//�����
	std::string securitycode;		//���밲ȫ��
	std::string iscycle;			//�Ƿ������ڻ���
	std::string startdate;			//��ʼ����
	std::string validityperiod;		//����ʱ��
	std::string content;			//��������
	std::string chairmanpwd;		//��ϯ����
	std::string partmanpwd;			//���������
	std::string recordcode;			//¼���룬����
	std::string funcbits;			//���鹦��λ
	std::string mediaBits;			//ý������
	int			confType;			//�������ͣ�0����ʱ���� 1��ԤԼ���� 2�����ڻ��� 3�����û���
	std::string confid;				//����ID
	std::string confStyle;			//��������
};

//Ⱥ��
struct UCSDK_API UCSDKGroup
{
	std::string name_;				//Ⱥ����
	std::string id_;				//Ⱥ��ID
	int			type_;				//Ⱥ������
	bool		readonly_;			//Ⱥ���Ƿ�ֻ��
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
	std::string creator_;			//Ⱥ�鴴����
	std::string uri_;				//Ⱥ��uri
	std::string groupno_;			//Ⱥ���
	std::string desc_;				//Ⱥ������
	std::string bulletin_;			//Ⱥ�鹫��
	std::string owneruri_;			//Ⱥ��uri
	int			capacity_;			//Ⱥ������Ա��
	std::string needpermit_;		//�Ƿ���Ҫͨ��Ⱥ����֤�����
};

struct UCSDK_API STVideoWindow
{
	int			hWnd;				//���ھ��
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
	int			autoanswerdelay;	//�Զ�Ӧ����ʱʱ��(��λ����)���ı���ֻ����callalertinfo_==3���������Ч
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
