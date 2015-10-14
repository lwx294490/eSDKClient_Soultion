/******************************************************************************
* Huawei Enterprise Communication API
* ecsclient.h
* Author :  Huawei
* Description :  UCSelf and UCClient related API
* Create Time:  2011-7-02 16:00:00
* Copyright (c) 2012 Huawei Technologies Co., Ltd.
* All rights reserved.

* Revision History :  2011-7-02 1.00  First version
******************************************************************************/
#pragma  once

namespace uc {
  namespace model {

// ! An enum
/** \brief  permission field definition
*/
enum APPCLASSLAYER_API PermissionType
{
  AbbDial,                 //��λ����    01 
  PwdCallLimit,
  CallLimit,               //��������       03
  LostCallNotifySms,       //δ������ת����  04    
  BlackWhiteList,          //�ڰ�����   05   
  Ctd,                     //�������   06
  CallAllNewSev,           //��������ҵ��  07
  OneNum,                  //һ��ͨ  08
  CallDeflection,          //����ƫת  09
  RemoteReg,               //Զ��ע��  10
  MainNum,                 //��ҵ�ܻ�  11
  Attendant,               //����Ա  12
  SecretarySev,            //����ҵ��  13
  SecretaryStationSev,     //����̨  14
  Clir,                    //������ʶ������  15
  ClirOverride,            //������ʶ��������Խ  16
  Clip,                    //������ʶ����ʾ  17
  DisplayUsrName,          //������ʾ����  18
  CallerId,                //����������ʾ  19
  AnonymousCallReject,     //�������оܾ�  20
  GroupPickUp,             //ͬ�����  21
  DesignatePick,           //ָ������  22
  AlarmClock,              //����ҵ��  23
  Acb,                     //�Զ��ؽ�ҵ��  24
  Recording,               //¼��  25
  CallTransfer,            //����ת��  26
  CallPark,                //����פ��  27
  CallWait,                //���еȴ�  28
  CallHold,                //���б���  29
  DisRinging,              //��������  30
  BargeInsert,             //ǿ��  31
  BargeDisconnect,         //ǿ��  32
  BargeOverride,           //ǿ��  33
  BargeMonitor,            //����  34
  NightService,            //ҹ������  35
  DoNotDisturb,            //�����  36
  ThreePartyConf,          //����ͨ��  37
  CallForwardUnCondi,      //������ת��  38
  CallForwardOnBusy,       //��æת��  39
  CallForwardOnReply,      //��Ӧ��ת��  40
  CallForwardOffline,      //����ת��  41
  ForwarVoimailBoxUnCon,   //������ת��������  42
  ForwarVoimailBoxBusy,    //��æת��������  43
  ForwarVoimailBoxNoReply, //��Ӧ��ת��������  44
  ForwarFaxMailBoxUnCon,   //������ת����  45
  ForwarOnCon,             //����ת��  46
  ForwarVoiMailBoxOffline, //����ת��������  47
  HuntingGroup,            //HuntingѰ��  48
  VipList,                 //˽���б�  49
  FaxMail,                 //��������  50
  DataConf,                //��ý�����  51
  FileTrans,               //�ļ�����  52
  VideoCall,               //��Ƶͨ������  53
  VoiceConf,               //��������  54
  EnterBussBook,           //��ҵ��ַ��   55
  PersonBook,              //���˵�ַ��  56
  Sms,                     //���Ź���  57
  Mms,                     //���Ź���  58
  IM,                      //��ʱ��Ϣ  59
  TurnPhone,               //һ��ת��  60
  VoiceCall,               //��Ƶͨ������  61
  CreateGroup,             //����Ⱥ��  62
  DeptNotificaton,         //����֪ͨ  63
  GroupMessage,            //Ⱥ����Ϣ  64

  VideoConf = 79,          //��Ƶ����  79
  DenyForwarding = 81,     //����ǰת�ܾ�
  FwdIntelligence,         //����ǰת
  FollowMe,                //Follow Me
  Immediate2Voicemail,     //�������伴ʱת
  DoPhoneJoint ,           //��������  86

  LBS = 88,                //LBS
  Intercom,                //�Խ���
  Mobility,                //IP�����ƶ�
  CallLog,                 //������־
  
  SrvRecordPermission = 91,           //���μ�¼ 92

  MsgWaiting = 96,         //���Ե�
  HotLine,                 //����

  SNR = 99,                //Single Number Reach
  Presence,               //״̬����
  ExchangeStatus,          //Exchange״̬ͬ��

  FixGroupShareSpaceFunFlag  = 109, //110Ⱥ����
  
  OffLineFileTranslate = 110,//��111λ�����ļ�����
  
  UnknownPermission = 200
};

// ! An enum
/** \brief  playing ringtone type definition
*/
enum APPCLASSLAYER_API RingType
{
  ContactRing = 0,
  GroupRing,
  InsideRing,
  OutsideRing,
  CallbackRing,
  SystemRing
};

/**
* \brief OnlineConfig
* \note The OnlineConfig class is used for reminder when user login
* \author  y00135380
* \version 1.0.0  initial version
*/
class APPCLASSLAYER_API OnlineConfig
{
public:
  int GetOnlineTipsList(std::vector<std::string>& _list) const;
  int SaveOnlineTipsList(const std::vector<std::string>& _list) const;
};

class APPCLASSLAYER_API SMSSignatureConfig
{
public:
  int GetSMSSignatureList(std::vector<std::string>& _list) const;
  int SaveSMSSignatureList(const std::vector<std::string>& _list) const;
};

class APPCLASSLAYER_API TransferNumberConfig
{
public:
  int GetNumberList(std::vector<std::string>& _list) const;
  int SaveNumberList(const std::vector<std::string>& _list) const;
  bool AddNumber(const std::string & number) const;
};

/**
* \brief RingToneConfig
* \note The RingToneConfig class is used for playing ringtone when new call arrives
* \author  y00135380
* \version 1.0.0  initial version
*/
class APPCLASSLAYER_API RingToneConfig
{
public:
  bool SaveContactGroupRing(
    const std::string& _id, const std::string& _ringtone) const;
  bool SaveGlobalRing(const int _type, const std::string& _ringtone) const;
  bool GetContactGroupRing(
    const std::string &_id, std::string& _ringtone) const;
  void GetGlobalRing(const int _type, std::string& _ringtone) const;
  bool RemoveContactGroupRing(const std::string& _id) const;
};

/**
* \brief StringItem
* \note The StringItem class is used for storing quick (auto) reply messages
* \author  c00161520
* \version 1.0.0  initial version
*/
typedef long long IDType;
struct APPCLASSLAYER_API StringItem
{
  IDType id;
  std::string content;

  StringItem() : id(0) {}
};

/**
* \brief QuickReplyConfig
* \note The QuickReplyConfig class is used for storing quick reply messages
* \author  y00135380
* \version 1.0.0  initial version
*/
class APPCLASSLAYER_API ReplyConfig
{
public:
  int SaveQuickReplyList(const std::vector<StringItem> & _list) const;
  bool AddQuickReply(StringItem & strItem) const;
  bool UpdateQuickReply(const StringItem & strItem) const;
  bool RemoveQuickReply(const IDType & id) const;
  int ClearQuickReply() const;
  int GetQuickReplyList(std::vector<StringItem> & strItems) const;

public:
  int SaveAutoReplyList(const std::vector<StringItem> & _list) const;
  bool AddAutoReply(StringItem & strItem) const;
  bool UpdateAutoReply(const StringItem & strItem) const;
  bool RemoveAutoReply(const IDType & id) const;
  int ClearAutoReply() const;
  int GetAutoReplyList(std::vector<StringItem> & strItems) const;
};

/**
* \brief SimpleConfig
* \note The SimpleConfig class is used for UI to store simple key/value pair config
* \author  y00135380
* \version 1.0.0  initial version
*/
class APPCLASSLAYER_API SimpleConfig
{
public:
  bool GetUserConfig(
    const std::string & _strkey, std::string & _strValue) const;
  bool SaveUserConfig(
    const std::string & _strkey, const std::string & _strValue) const;
};

/**
* \brief   �û��Զ���״̬
* \note    Ŀǰ֧��æµ���뿪�������࣬С����û��Լ�����
* \author  liwenwqing 217212 20121226
* \version 1.0.0  initial version
*/
typedef long long UserDefineStateID;
struct APPCLASSLAYER_API UserDefineStateDateType
{
  UserDefineStateID userDefineStateId;  //����������
  std::string strParentState;           //�Զ���״̬�����Ĵ��࣬Ŀǰ֧��æµ���뿪�������� liwenwqing 217212 20121226
  std::string strChildStateContent;     //�û��Զ���״̬����
};

class APPCLASSLAYER_API UserDefineStateConfig
{
public:
  /*************************************************************/
  /*
  /* �������ã����ĳһ������û��Զ���״̬������æµ��Ϊ��״̬
  /* ����    ��
  /*          [in ]_strParentState ����״̬
  /*          [out]vectorUserDefineState_ ���������״̬
  /*
  /* ��ע�� Ŀǰ֧��æµ���뿪����״̬�¿����Զ���״̬
  /*
  /*************************************************************/
  int GetUserDefineStateByParentState(const std::string & _strParentState, std::vector<UserDefineStateDateType> & vectorUserDefineState_) const;

  /*************************************************************/
  /*
  /* �������ã�����һ���û��Զ���״̬
  /* ����    ��
  /*          [out]UserDefineStateId_ �����ӵ�״̬IDֵ��
  /*               �����ݿ���������������
  /*          [in ]_strParentState ��״̬
  /*          [in ]_strStateContent �û��Զ����״̬
  /*
  /* ����ֵ�� ture��ʾ����ɹ���false��ʾ����ʧ��
  /*
  /* ��ע�� ������û�Ҫ�õ��ող�����������Ա�ɾ���ü�¼
  /*
  /*************************************************************/
  bool AddOneUserDefineState(int &UserDefineStateId_, const std::string & _strParentState, const std::string & _strStateContent) const;

  /*************************************************************/
  /*
  /* �������ã�ͨ��������״̬id��ɾ���û��Զ���״̬
  /* ����    ��
  /*          [in ]_userDefineStateId ״̬id�������ݿ�����������
  /*
  /* ����ֵ�� ture��ʾɾ���ɹ���false��ʾɾ��ʧ��
  /*
  /*************************************************************/
  bool DeleteOneUserDefineState(const UserDefineStateID _userDefineStateId) const;

};

struct APPCLASSLAYER_API WorkspacePanel
{
  std::string name;
  std::string url;
  std::string image;
  std::string type;
};

/**
* \brief WorkspaceConfig
* \note The WorkspaceConfig class is used for manage user workspace panels
* \author  c00161520
* \version 1.0.0  initial version
*/
class APPCLASSLAYER_API WorkspaceConfig
{
public:
  int SaveWorkspaceList(const std::vector<WorkspacePanel> & panels) const;
  bool AddWorkspace(const WorkspacePanel & panel) const;
  bool RemoveWorkspace(const std::string & name) const;
  int ClearWorkspace() const;
  bool GetWorkspace(const std::string & name, WorkspacePanel panel) const;
  int GetWorkspaceList(std::vector<WorkspacePanel> & panels) const;
  int GetWorkspaceListByType(const std::string & type, 
    std::vector<WorkspacePanel> & panels) const;

};

// ! An enum
/** \brief  Booked conference related push messages
*/
enum APPCLASSLAYER_API BookConfCnType
{
  BOOKCONF_CNCREATE = 0,
  BOOKCONF_CNMODIFY,
  BOOKCONF_CNCANCEL,

  BOOKCONF_CNUNKNOWN,
};

struct APPCLASSLAYER_API UCBookConfInfo
{
  std::string topic;  //!< conf subject
  std::string meetingtime;  //!< conf time
  std::string convener; //!< conf convener
  std::string convenername; //!< convener name
  std::vector<std::string> attendeelist;    //!< conf member list
  std::string accessnum;    //!< conf access number
  std::string securitycode;    //!< conf security number
  std::string iscycle;    //!< whether it's a cycle conf
  std::string startdate;    //!< conf start date
  std::string validityperiod;    //!< conf duration period
  std::string content;         //!< conf content
  std::string chairmanpwd;  //!< chairman password
  std::string partmanpwd;  //!< participant password
  std::string recordcode;  //!< conf record code
  std::string funcbits;    //!< conf funcbits 
  std::string mediaBits;  //!< media type,1:audio 2:video 3:data ,exm 001 only have data media
  ctk::int16 confType;    //!< conference type, 0instant 1booking 2cycle 3persistent	
  std::string confid;      //!< conf id
  std::string confStyle;    //!< conf Style

  UCBookConfInfo() : confType(-1) {}
};
std::ostream & operator<<(std::ostream & _os, 
						  const uc::model::UCBookConfInfo & bookConf);   


 // ! An enum

/** \brief  record msgtype define
 */
enum APPCLASSLAYER_API SrvRecordMsgType
{
    InvalidRcdType = 0,
    P2PRcdype, //1��Ե���Ϣ
    GroupRcdType, //2Ⱥ����Ϣ
    SystemRcdType, //3ϵͳ��Ϣ
    DeptNtfRcdType, //4����֪ͨ
    MeetingNtfRcdType, //5����֪ͨ
    SysAndMeetingNtfRcdType, //6ϵͳ�ͻ���֪ͨ
};

/**
 * \brief UCSrvRecord
 * \note The UCSrvRecord class is used for server record history
 * \author  l00193975
 * \version 1.0.0  initial version
 */
struct APPCLASSLAYER_API SrvRecord
{
    std::string id; //!< ��Ϣ��¼ID
    SrvRecordMsgType msgtype; //!<��Ϣ����
    std::string name;
    std::string sender; //!< ��Ϣ���ͷ�
    std::string recver; //!< ��Ϣ���շ�
    std::string msgtime; //!< ��Ϣʱ��
    std::string subject;
    std::string msgsvctype;
    std::string content; //!<��Ϣ����
    std::string encodetype; //!<��Ϣ�����ʽ
};

std::ostream & operator<<(std::ostream &  _os, const uc::model::SrvRecord & _rcd);

/**
* \brief profile of current user
* \note get value from ecs::ecsdata::UserProfile
* \author  c00161520
* \version 1.0.0  initial version
*/
struct APPCLASSLAYER_API SelfProfile
{
  std::string profilepath_;    //!< user data path
  std::string headimagepath_;  //!< Cached image header file path
  std::string imagefilepath_;  //!< cached image in im message
  std::string receivefilepath_;  //!< file transfer
  std::string recordfilepath_;  //!< record files
  std::string portaladdr;      //!< Personal PORTAL address
  std::string confportal;      //!< Main conf PORTAL address
  std::string confportalback;  //!< Bakup conf PORTAL address
  std::string confaccesscodelist; //!< access code list of conferences

  std::map<std::string, std::string> callexcodelist;  //!< Extended call business code

  int curcenter;               //!< Real center belongs to: 0 South ; 1 North
  int retrytimes;		           //!< Remaining retry times
  int maxretrytimes;		       //!< max retry times 
  int maxcontact;              //!< Max allowed contact count
  int firstlogin;              //!< Whether first login

  std::string zone;            //!< user zone
  std::string netLocation;     //!< network location: 1 internal network, 2 external network

  std::map<std::string, std::string> pluginconfigs_;  //plugin params fetched from the server

  std::string corpId;
  std::string lastLoginTime;        //!< Last login time

  std::vector<std::string> sensewordlist; //!< sensible words list

  bool bPhoneJoint;
  std::string voicemailaccesscode;
  int voiceMailFlg;
  bool bInputStatus; //!< Whether you notify your input status

  SelfProfile() 
    : curcenter(-1), retrytimes(-1), maxretrytimes(-1), maxcontact(-1), firstlogin(-1)
  {
      bInputStatus=false;
      bPhoneJoint=false;
      voiceMailFlg=0;
  }
  ~SelfProfile() {}
};

/**
* \brief vip list item
* \note get value from ecs::ecsdata::UserProfile
* \author  c00161520
* \version 1.0.0  initial version
*/
struct APPCLASSLAYER_API PrivateListItem
{
  std::string bindNo;   //<! bind number
  std::string name;     //<! vip name
  std::string reserve;  //<! not used
};

struct APPCLASSLAYER_API ACBItem
{
public:
  std::string callee_;  //!< auto call back number
  int time_;    //!< call back time
};

class APPCLASSLAYER_API ACBConfig
{
public:
  int GetACBLineNum() const;
  int GetACBList(std::vector<ACBItem> & acblist) const;
  void SetACBList(const std::vector<ACBItem> & acblist);

  sigslot::signal1<std::string> ACBNotify_;
};

class APPCLASSLAYER_API BossSecConfig
{
public:
	int GetIdentity() const;
	bool IsShareLine(int lineindex) const;
};

/**
* \brief UCSelf
* \note The UCSelf class is the Self detailed information manipulation class
* \author  y00135380
* \version 1.0.0  initial version
*/
class APPCLASSLAYER_API UCSelf
{
public:
  enum PubContactInfoType
  {
    Availability,
    CustomStatusDesc,
    Position, 
    Location, 
    AVTool, 
    Signature,
    HeadImage,
    CallDeviceDesc,
    Invalid, 
  };

  virtual ~UCSelf()
  {
  }

  virtual bool Init() = 0;

  virtual bool Uninit() = 0;

  /**
  * \brief Judge if we have the specified permission
  * \param[in]  permission type
  * \param[out] N/A
  * \return  true:  has permission ; false: Otherwise 
  */
  virtual bool HasPermission(PermissionType _type) = 0;

  /**
  * \brief Publish self information.
  *        Include status/signature/headimage etc.
  * \param[in]  N/A
  * \param[out] N/A
  * \return  true:  Success ; false: Failed 
  */
  virtual bool PublishSelfInformation(const std::map<PubContactInfoType, std::string>& _values) = 0;

  /**
  * \brief Sync Self information from local db.
  *        Include status/signature/head image etc.
  * \param[in]  N/A
  * \param[out] N/A
  * \return  true:  Success ; false: Failed 
  */
  virtual bool RefreshSelfInfo() = 0;

  /**
  * \brief Get self related booked conference list
  * \param[in]  N/A
  * \param[out] N/A
  * \return  true:  Success ; false: Failed 
  */
  virtual bool GetBookConfList(std::vector<UCBookConfInfo>& _list) = 0;

  /**
  * \brief Get current user profile value
  * \param[in]  
  * \param[out] _profile: user profile
  * \return  true:  Success ; false: Failed 
  */
  virtual bool RefreshSelfProfile() = 0;
  virtual SelfProfile & GetProfile() = 0;
  virtual std::string GetProfilePath() const = 0;  /*< assign user profile storage path*/
  virtual int GetSrvRecord(const std::string& userId, 
    const std::string& startTime, const std::string& endTime, 
    int msgType, int pageNum, int pageSize, int amount, 
    std::vector<uc::model::SrvRecord>& _rcdList) = 0;

  /**
  * \brief Get current user's private vip list
  * \param[in]  
  * \param[out] _list: private vip list
  * \return  number of private vips
  */
  virtual int GetPrivateList(std::vector<PrivateListItem> & _list) = 0;
  virtual int SetPrivateList(const std::vector<PrivateListItem> & _list) = 0;

  /**
  * \brief Get messages of specified type
  * \param[in]  _msgtype: message type
  * \param[out] N/A
  * \return  0 success
  */
  virtual int GetUnreadList(int _msgtype) = 0;

  /*
  *beacuse of Asynchronous getting unread messages, restarting GetUnreadList need to reset first.
  */
  virtual void ResetUnreadList() = 0;

  virtual void GetLinkageNum(std::string &_number) = 0;

public:
  uc::model::Contact selfInfo;  /*!< Self detailed information*/
  uc::model::ContactAvailability selfStatus;  /*!< Self status */
  std::string selfStatusDesc;   /*!< Self status description */

  OnlineConfig onlinecfg_;     /*!< online tips config*/
  SMSSignatureConfig smsSigncfg_;     /*!< sms signature config*/
  TransferNumberConfig transferNumCfg_; /*!< transfer number history list*/
  RingToneConfig ringtonecfg_; /*!< ring tone of incoming call config*/
  ReplyConfig quickreplycfg_; /*!< quick reply config*/
  SimpleConfig simplecfg_;     /*< value/pair simple config*/ 
  ACBConfig acbConfig_; /*< auto call back config*/
  UserDefineStateConfig userDefineStateConfig_; /**/

public:
  sigslot::signal1<int> VoiceMessageNotify_;

};

/**
* \brief LoginListItem
* \note The LoginListItem struct represents user login information;
* \author  c00161520
* \version 1.0.0  initial version
*/
struct APPCLASSLAYER_API LoginListItem
{
  std::string account;  /*< login account */
  std::string password; /*< login password */
  std::string datetime; /*< login date and time */
  bool rememberPwd;
  bool autoLogin;

};

/**
* \brief SystemConfig
* \note The SystemConfig class is used for UI to store login list
* \author  c00161520
* \version 1.0.0  initial version
*/
class APPCLASSLAYER_API SystemConfig
{
public:
  bool Initilize() const;
  bool Finalize() const;

  int GetLoginList(std::vector<LoginListItem> & items) const;
  bool UpdateLoginList(
    const std::string & account, const std::string & password, 
    bool rememberPwd, bool autoLogin) const;
  bool UpdateRememberPwd(const std::string & account, bool rememberPwd) const;
  bool UpdateAutoLogin(const std::string & account, bool autoLogin) const;
  bool DeleteAccount(const std::string & account) const;

  bool GetSysConfig(
    const std::string & _strkey, std::string & _strValue) const;
  bool SaveSysConfig(
    const std::string & _strkey, const std::string & _strValue) const;
};

/**
* \brief UCClient
* \note The UCClient class is the basis for all Huawei UC2.0 API functionality
* \author  y00135380
* \version 1.0.0  initial version
*/
class APPCLASSLAYER_API UCClient
{
public:
  enum SignInState
  {
    Client_Uninited,
    Client_SignedFailed,
    Client_SigningIn,
    Client_SignedIn,
    Client_KickedOut,
    Client_Invalid
  };

  UCClient();
  virtual ~UCClient();

  /**
  * \brief Initialize the uc system
  * \param[in]  N/A
  * \param[out] N/A
  * \return  true:  Success ; false: Failed 
  */
  virtual bool Init() = 0;

  /**
  * \brief Initialize the uc system
  * \param[in]  N/A
  * \param[out] N/A
  * \return  true:  Success ; false: Failed 
  */
  virtual bool UnInit() = 0;

  virtual bool GetUpdateAddress(
    const std::string & ip, int port, const std::string account) = 0;

  /**
  * \brief Sign in the uc system
  * \param[in]  N/A
  * \param[out] N/A
  * \return  true:  Success ; false: Failed 
  */
  virtual bool SignIn() = 0;

  /**
  * \brief Sign Out the uc system
  * \param[in]  N/A
  * \param[out] N/A
  * \return  true:  Success ; false: Failed 
  */
  virtual bool SignOut() = 0;

  /**
  * \brief Get the UC client class instance
  * \param[in]  N/A
  * \param[out] N/A
  * \return  UCClient 
  */
  static UCClient* GetClient();
  static void ReleaseClient();

public:
  uc::model::UCSelf* Self;     /*!< Self privacy */
  uc::model::ContactMgr* ContactManager;   /*!< Personal addressbook manager*/
  uc::model::ContactSubscription* ContactSubManager;  /*!< Contact presence subscription manager*/
  uc::model::FavouriteMgr* FavouriteManager;  /*!< My favourite manager*/

  uc::model::device::DeviceMgr* DeviceManager;   /*!< Audio/Video device manager*/

  uc::model::conversation::ConversationMgr* ConvManager;  /*!< IM/Call/Conference conversation manager*/

  uc::model::SignInConfig SignConfig;  /*!< Sign in param configuration*/
  uc::model::SystemConfig SysConfig; /*!< System config interface */
  uc::model::EntAddrbookMgr EntAddrbookManager_;  /*!< Enterprise addressbook manager*/

    /**
  * \brief User Permission changed notification
  *        UI need to implement has_slots<> and connect to the signal.
  *        Like this:  void OnPermissionChgedNotify_();
  * \param[in]  N/A
  * \param[out] N/A
  * \return   
  */
  sigslot::signal0<> PermissionChgedNotify_;

  /**
  * \brief client signin result notify Signal
  *        UI need to implement has_slots<> and connect to the signal.
  *        Like this:  void OnStateChanged(uc::model::UCClient::SignInState _state, std::string);
  * \param[in]  N/A
  * \param[out] N/A
  * \return   
  */
  sigslot::signal2<SignInState, std::string> SignInNotify_;
  sigslot::signal1<std::string> GetUpdateAddrNotify_;
 

};

static const std::string SIGNINFAIL_GETUPDATE = "getupdate"; // aa:AAresult
static const std::string SIGNINFAIL_AA = "aa"; // aa:AAresult
static const std::string SIGNINFAIL_CONTACT = "contact";
static const std::string SIGNINFAIL_SIP = "sip";
static const std::string SIGNINFAIL_SIP_KICKOUT = "sipkickout";

static const std::string SIGNIN_NOK = "signin";
static const std::string SIGNOUT_OK = "signout";
static const std::string SIGNOUT_FAILED = "signoutfailed";

static const std::string SIGNINFAIL_NOIP = "noip";
static const std::string SIGNINFAIL_HASIP = "hasip";

  }
}
