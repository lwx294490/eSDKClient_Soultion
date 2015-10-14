/******************************************************************************
* Huawei Enterprise Communication API
* group.h
* Author :  Huawei
* Description :  Group related API
* Create Time:  2011-7-02 16:00:00
* Copyright (c) 2012 Huawei Technologies Co., Ltd.
* All rights reserved.

* Revision History :  2011-7-02 1.00  First version
******************************************************************************/

#pragma  once

namespace uc {
  namespace model {
    namespace conversation {

class Conversation;

// ! An enum
/** \brief  instant message type definition
*/
enum APPCLASSLAYER_API InstantMsgType
{
  ChatP2PIM = 0,
  ChatFixedGroup = 1,
  ChatInputStatus = 3,
  ChatOfflineFile = 4,
  ChatAddFriend = 5,
  ChatErrorMsg = 6,
  ChatCalling = 7,
};

enum APPCLASSLAYER_API ParticipantChgType
{
  PartAdded = 0,
  PartRemoved,
  PartStatusChanged,
};

enum APPCLASSLAYER_API MemChgType
{
    MemAdded = 0,
    MemRemoved,
    OwnerChanged,
    GroupDel,
};

// ! An enum
/** \brief  Conversation state enum
*/
enum APPCLASSLAYER_API ConversationState
{
  ConvInactive,       /*!<  conversation is inactive */
  ConvActive,         /*!<  conversation is active*/
  ConvParked,         /*!<  conversation is been parked*/
  ConvTerminated,     /*!<  conversation is been terminated*/
  ConvInvalidState,
};

// ! An enum
/** \brief  Conversation property enum
*/
enum APPCLASSLAYER_API ConversationProperty
{
  ConvIdentifier,     /*!< conversation ID*/
  ConvSubject,        /*!< conversation subject*/

  ConvConfIdentifier, /*< audio conference identifier*/

  ConvTempGroupUri,   /*< if have, conversation combined tempgroup uri*/
  ConvFixedGroupUri,  /*< if have, conversation combined fixedgroup uri*/
  ConvHistoryGroupUri, /*< if have, conversation is a history temp group*/

  ConvBookingConfUri, /*!< mark if join booking conference*/
  ConvTypeUri,      /*!< reserver property for future*/
  ConvConfSubject,      /*!< save conference subject*/
  ConvReserved2,      /*!< reserver property for future*/
  ConvReserved3,      /*!< reserver property for future*/
  ConvReserved4,      /*!< reserver property for future*/
  ConvReserved5,      /*!< reserver property for future*/
};

// ! An enum
/** \brief  Session property enum
*/
enum APPCLASSLAYER_API SessionState
{
  SessionDisconnected,   /*!<  session disconnected*/
  SessionConnecting,     /*!<  session is connecting*/
  SessionConnected,      /*!<  session connected*/  
  SessionOnHold,         /*!<  session is on hold*/
  SessionBeHeld,         /*!<  session is on hold*/
  SessionSuspended,      /*!<  session suspended, few capabilities*/
  SessionForwarding,     /*!<  session is forwarding*/
  SessionTransfering,    /*!<  session is transfering*/
};

// ! An enum
/** \brief  Business session property enum
*/
enum APPCLASSLAYER_API SessionProperty
{
  InstantMsgSessionRole,           /*!< self role in this instant message session*/
  AVSessionIdentifier,             /*!< call session identifier*/
  AVSessionConferenceRole,         /*!< self role in audio conference session*/
  AVSessionAudioRenderVolume,      /*!< incoming audio volume level*/
  AVSessionAudioRenderMute,        /*!< incoming audio volume is muted*/
  AVSessionAudioCaptureVolume,     /*!< outgoing audio volume level*/
  AVSessionAudioCaptureMute,       /*!< outgoing audio volume is muted*/
  CallExSessionCode,               /*!< special call extended session code*/
  AVSessionVoiceMail,              /*!< session call forwarding voice mail*/
  AVSessionLocation,               /*!< session call exist local or remote(phone joint)*/
  SessionPropReserved3,
};

// ! An enum
/** \brief  enum which device to join the session
*/
enum APPCLASSLAYER_API SessionConnType
{
  SessionConnUri,     /*!< default value, connect soft client*/
  SessionConnMobile,  /*!< connect the mobile phone of the participant*/
  SessionConnFixedPhone, /*!< connect the fixed phone of the participant*/
  
  UnknownConnType,
};

// ! An enum
/** \brief  FileTrans related notifiction type define
*/
enum APPCLASSLAYER_API FileTransNotifyType
{
  FileSendAckNotify = 0,
  FileAcceptedNotify,
  ReceivedFileNotify,
  FileCancelNotfiy,
  FileTransProcessNotify
};

// ! An enum
/** \brief  File transfer state define
*/
enum FileTransState
{
  FileConnecting,
  FileSend,
  FileReceive,
};

// ! An enum
/** \brief  Supported instant message content type
*/
enum APPCLASSLAYER_API InstantMessageContentType
{
  IMPlainText,     /*!< normal plain text*/
  IMHtml,          /*!< html style content*/
  IMRichText,      /*!< rtf style content*/
  IMGif,           /*!< gif style content*/
  IMInk,           /*!< ink style content*/
};

// ! An enum
/** \brief  Sms related notifiction type define
*/
enum APPCLASSLAYER_API SmsNotifyType
{
  SendSmsAck = 0,
  ReceivedSmsNotify,
  SmsResponseNotify,
  SmsResultNotify
};

// ! An enum
/** \brief  System msg related notifiction type define
*/
enum APPCLASSLAYER_API SysNotifyType
{
    DeptNotificaton = 0,//���Ź���
    SysNotifycation     //ϵͳ����
};

// ! An enum
/** \brief  Support send result message type define
*/
enum APPCLASSLAYER_API MsgTypeSendResult
{
    MSGTYPE_IM, //��ʱ��Ϣ
    MSGTYPE_TEMP_IM, //��ʱȺ��ʱ��Ϣ
    MSGTYPE_SYS, //ϵͳ��Ϣ
};

typedef APPCLASSLAYER_API struct
{
  std::string msgid_;
  std::string content_;
  std::string nickname_;
  std::string time_;
  std::string peeracc_;
  std::string result_;
  std::string errorcode_;
  SmsNotifyType notifyType_;
}sSmsParam, *PSmsParam;

typedef APPCLASSLAYER_API struct _sImMsgItem
{
  std::string origin;
  std::string target;
  std::string content;
  std::string rcv_time;
  std::string server_transfer_time;
  std::string name;
  std::string msgid;
  InstantMsgType chatType;
  bool isbigmsg;
public:
  _sImMsgItem():chatType(ChatP2PIM),isbigmsg(false){}
} sImMsgItem, *PImMsgItem;

typedef APPCLASSLAYER_API struct 
{
  std::string origin;
  std::string subject;
  std::string content;
  std::string rcv_time;
  std::string msgid;
  SysNotifyType msgtype;
} sSysMsgItem, *PSysMsgItem;
std::ostream & operator<<(std::ostream & _os, 
						  const uc::model::conversation::sSysMsgItem & sysmsg);    


typedef APPCLASSLAYER_API struct __sFileTransParam
{
public:
  std::string sessionID_; 
  std::string reason_;   /*!< cancel or reject reason*/
  std::string errcode_;  /*!< cancel or reject errorcode*/
  std::string time_;
  std::string origin_;   /*!< sender's url*/
  std::string originName_; /*!< sender's name*/
  std::string filename_; /*!< �ļ�ȫ·��*/
  unsigned long filesize_;  /*!< �ļ���С*/
  unsigned long cursize_;   /*!< �ѽ��ջ��ѷ��ʹ�С*/
  int procent_;

  FileTransNotifyType notifyType_; /*< type of received notify */
public:
    __sFileTransParam(): filesize_(0), cursize_(0), procent_(0), notifyType_(FileSendAckNotify){}
}sFileTransParam, *PFileTransParam;

typedef APPCLASSLAYER_API struct
{
public:
  int   nOwner_;
  int   nType_;
  int   nValue1_;
  long  nValue2_;
  void* pVoid_;
  int	nSize_;

}sDataShareParam,*PDataShareParam;

typedef APPCLASSLAYER_API struct __sAudioVideoParam
{
  std::string caller_;
  std::string callername_;
  int callalertinfo_;
  int autoanswerdelay;//�Զ�Ӧ����ʱʱ��(��λ����)���ı���ֻ����callalertinfo_==3���������Ч
  std::string lineindex_;
  bool isvideo_;
  bool callmode_;
  bool isdataconf_;
public:
    __sAudioVideoParam():callalertinfo_(0),autoanswerdelay(0),isvideo_(false), callmode_(false)
	                     , isdataconf_(false){}
}sAudioVideoParam, *PAudioVideoParam;


//��Ϣ���ͽ���ϱ���Ϣ��
typedef APPCLASSLAYER_API struct
{
    std::string targeturi_;    //�Է�uri
    std::string result_;       //���ͽ��
    std::string errorcode_;    //������
    std::string warningcode;   //�������ͣ�501/�Է���Ȩ��
    MsgTypeSendResult msgType_;//��Ϣ����
}sMsgSendResultParam,*PMsgSendResultParam;

//��Ϣ���ͽ���ϱ���Ϣ��
typedef APPCLASSLAYER_API struct
{
    std::string caller_;       //�Է�uri
    std::string AVSessionId_;  
    std::string reason_;        //������
}sMsgAVSessionClosedParam,*PMsgAVSessionClosedParam;
/**
* \brief Business Session class
* \note The session class is the basis of all business flow.
* \author  y00135380
* \version 1.0.0  initial version
*/
class APPCLASSLAYER_API Session
{
public:
  Session(Conversation* pConv)
    : pConv_(pConv), state_(SessionDisconnected), type_(Invalid)
  {

  }
  virtual ~Session();
  virtual bool Accept() = 0;
  virtual bool Reject() = 0;
  virtual bool Connect() = 0;
  virtual bool Disconnect() = 0;

  virtual bool KickParticipant(const Participant& _member) = 0;
  virtual bool ConnectParticipant(const Participant& _member) = 0;

  virtual bool Connect(SessionConnType _conntype) = 0;

  virtual bool HasConnected() { return true;}

public:
  Conversation* pConv_;  //!< conversation this session belongs to

  uc::model::SessionType type_;  //!< business session type
  SessionState state_;   //!< business session state

  typedef std::map<SessionProperty, std::string> SessionProperties_;
  SessionProperties_ propmap_;  //!< properties of this conversation
};

/**
* \brief Conversation class
* \note This class is the session container of user business action.
* \author  y00135380
* \version 1.0.0  initial version
*/
class APPCLASSLAYER_API Conversation
{
public:
  Conversation()
    : state_(ConvInactive), merged_(false), confmute(false)
  {
  }

  ~Conversation();

  /**
  * \brief merge another conversation into this one
  *        SessionType specifies which Session is needed to be merged
  * \param[in]  SessionType
  * \param[out] N/A
  * \return  new business session
  */        
  bool Merge(Conversation* _pconv, uc::model::SessionType _type);

  /**
  * \brief Add Business to this conversation
  * \param[in]  SessionType
  * \param[out] N/A
  * \return  new business session
  */
  Session* AddSession(uc::model::SessionType _type);

  /**
  * \brief Get related business session
  * \param[in]  SessionType
  * \param[out] N/A
  * \return  exist business session
  */
  Session* GetSession(uc::model::SessionType _type);

  /**
  * \brief Remove specified type session
  * \param[in]  SessionType
  * \param[out] N/A
  * \return  true: success; false: faield
  */
  bool RemoveSession(uc::model::SessionType _type);

  /**
  * \brief check if have specified type session
  * \param[in]  SessionType
  * \param[out] N/A
  * \return  true: success; false: faield
  */
  bool HasSession(uc::model::SessionType _type);

  /**
  * \brief Judge if this contact has been added
  * \param[in]  Contact
  * \param[out] N/A
  * \return  true: success; false: failed
  */
  bool HasParticipant(const uc::model::Contact& _contact);

  /**
  * \brief Judge if this contact has been added
  * \param[in]  Contact
  * \param[out] N/A
  * \return  true: success; false: failed
  */
  bool HasSmsParticipant(const uc::model::Contact& _contact);

  /**
  * \brief Get the conversation participant by phone number
  * \param[in]  number
  * \param[out] Participant
  * \return  true: success; false: failed
  */
  bool GetParticipantByNum(const std::string& _num, Participant& _part);

  /**
  * \brief Get the conversation participant by uri
  * \param[in]  uri
  * \param[out] Participant
  * \return  true: success; false: failed
  */
  bool GetParticipantByUri(const std::string& _uri, Participant& _part);

  /**
  * \brief Add Participant to this conversation
  * \param[in]  Contact can be a phone number or a real contact
  * \param[out] N/A
  * \return  true: success; false: failed
  */
  bool AddParticipant(const uc::model::Contact& _contact);

  /**
  * \brief Remove Participant from this conversation
  * \param[in]  Contact can be a phone number or a real contact
  * \param[out] N/A
  * \return  true: success; false: failed
  */
  bool RemoveParticipant(const uc::model::Contact& _contact);

  /**
  * \brief Get the leader of this conversation
  * \param[out]  Contact of the leader
  * \return  true: success; false: failed
  */
  bool GetLeader(uc::model::Contact& _contact) const;

  /**
  * \brief End this conversation.All sessions will be auto ended.
  * \param[in]  N/A
  * \param[out] N/A
  * \return  true: success; false: failed
  */
  bool End();

  /**
  * \brief Used to mute a set of participants in a conference
  * \param[in]  Participant list
  * \param[out] N/A
  * \return  true: success; false: failed
  */
  bool Mute(const std::vector<Participant>& _members);

  /**
  * \brief Used to mute a set of participants in a conference
  * \param[in]  Participant list
  * \param[out] N/A
  * \return  true: success; false: failed
  */
  bool UnMute(const std::vector<Participant>& _members);

  /**
  * \brief Used to set video source in a convergent conference 
  * \param[in]  Participant list
  * \param[out] N/A
  * \return  true: success; false: failed
  */
  bool SetVideoSource(const uc::model::Contact& _contact);
  /**
  * \brief Used to mute all participants in a conference
  * \param[in]  N/A
  * \param[out] N/A
  * \return  true: success; false: failed
  */
  bool MuteAllAttender();

  /**
  * \brief Used to mute a set of participants in a conference
  * \param[in]  N/A
  * \param[out] N/A
  * \return  true: success; false: failed
  */
  bool UnMuteAllAttender();

  /**
  * \brief Whether this conversation is been merged.
  *        If true, then this conversation is invalid.
  * \param[in]  N/A
  * \param[out] N/A
  * \return  true; false
  */
  bool IsMerged();

public:
  typedef std::map<uc::model::SessionType, Session*> SessMap_;
  SessMap_ sessions_;  //!< current business sessions for this conversation 

  typedef std::map<std::string, Participant*> MemList_;
  MemList_ members_;  //!< participant list of this conversation(including all business session attender)

  typedef std::map<ConversationProperty, std::string> ConvProperties_;
  ConvProperties_ propmap_;  //!< properties of this conversation

  ConversationState state_;  //!< current conversation state

  /**
  * \brief Occurs when avsession participants status changed
  *        UI need to implement has_slots<> and connect to the signal.
  *        Like this:  void OnAVSessionMemberStatusChanged(uc::model::conversation::Conversation* _conv); 
  */
  sigslot::signal3<Conversation*, int, std::string> ConvMemberStatusChanged;

  /**
  * \brief Occurs when group participants changed
  *        UI need to implement has_slots<> and connect to the signal.
  *        Like this:  void ConvGroupMemberChanged(uc::model::conversation::Conversation* _conv, 
  *                             std::vector<std::string> _kicklist, std::vector<std::string> _addlist); 
  */
  sigslot::signal3<Conversation*, std::vector<std::string>, std::vector<std::string>> ConvGroupMemberChanged;

  /**
  * \brief Occurs when group participants changed
  *        UI need to implement has_slots<> and connect to the signal.
  *        Like this:  void ConvFixGRoupChanged(Conversation*, int, std::string); 
  */
  sigslot::signal3<Conversation*, int, std::string> ConvFixGRoupChanged;

  /**
  * \brief Occurs when the participant be allowed to speak
  *        UI need to implement has_slots<> and connect to the signal.
  *        Like this:  void OnAVSessionMemAllowSpeak(uc::model::conversation::Conversation*, uc::model::conversation::Participant _sess); 
  */
  sigslot::signal2<Conversation*, Participant>  ConvMemAllowSpeak;

  /**
  * \brief Occurs when the participant be allowed to speak
  *        UI need to implement has_slots<> and connect to the signal.
  *        Like this:  void OnAVSessionMemForbidSpeak(uc::model::conversation::Conversation*, uc::model::conversation::Participant _sess); 
  */
  sigslot::signal2<Conversation*, Participant>  ConvMemForbidSpeak;

  /**
  * \brief Occurs when remove memeber successfully
  *        UI need to implement has_slots<> and connect to the signal.
  *        Like this:  void OnAVSessionDelMemSucc(uc::model::conversation::Conversation*, uc::model::conversation::Participant _sess); 
  */
  sigslot::signal2<Conversation*, std::string>  ConfDelMemSucc;

  /**
  * \brief Occurs when the participant's video soure is set
  *        UI need to implement has_slots<> and connect to the signal.
  *        Like this:  void OnAVSessionSetVideoSource(uc::model::conversation::Conversation*, uc::model::conversation::Participant _sess); 
  */
  sigslot::signal2<Conversation*, std::string>  ConvSetVideoSource;

  /**
  * \brief Occurs when the participant be speaking
  *        UI need to implement has_slots<> and connect to the signal.
  *        Like this:  void OnAVSessionMemCurSpeaker(uc::model::conversation::Conversation*, uc::model::conversation::Participant _sess); 
  */
  sigslot::signal2<Conversation*, std::string>  ConvCurSpeaker;

    /**
  * \brief Occurs when the participant request to speak
  *        UI need to implement has_slots<> and connect to the signal.
  *        Like this:  void OnAVSessionMemCurSpeaker(uc::model::conversation::Conversation*, uc::model::conversation::Participant _sess); 
  */
  sigslot::signal3<Conversation*, std::string,bool>  ConvRequstToSpeak;

  /**
  * \brief new datashare session has been added signal.
  *        incoming datashre request for UE
  *        UI need to implement has_slots<> and connect to the signal.
  *        Like this:  void OnDataShareSessAdded(uc::model::conversation::Conversation* _con); 
  */
  sigslot::signal2<Conversation*, std::string> DataShareSessAdded;

  /**
  * \brief Another instant session has been merged into current conversation
  * \note  Emitted when audio call been converted into a new conference
  *        UI need to implement has_slots<> and connect to the signal.
  *        Like this:  void OnInstantSessMerged(uc::model::conversation::Conversation* _conv, 
  *                           uc::model::conversation::Conversation* _convmerged); 
  */
  sigslot::signal2<Conversation*, Conversation*> InstantSessMerged;

    /**
  * \brief weather mute all attender is success or not
  * \note  Emitted when audio call been converted into a new conference
  *        UI need to implement has_slots<> and connect to the signal.
  *        Like this:  void OnInstantSessMerged(uc::model::conversation::Conversation* _conv, 
  *                           uc::model::conversation::Conversation* _convmerged); 
  */
  sigslot::signal2<Conversation*,bool> MuteAllSuc;

  /**
  * \brief instant session has been connected.
  *        1. if connect succeed, then this signal will be emitted
  *        UI need to implement has_slots<> and connect to the signal.
  *        Like this:  void InstantSessConnected(uc::model::conversation::Conversation* _con); 
  */
  sigslot::signal1<Conversation*> InstantSessConnected;

  bool merged_;  //!< whether this conversation is been merged to another. If true, then this conv should be abandoned.
  bool confmute; //�᳡������־  1 ����  0�Ǿ���
};

/**
* \brief AVSession class handles audio or audio conference call 
* \note This class is basic class of audio/video session.
* \author  y00135380
* \version 1.0.0  initial version
*/
class APPCLASSLAYER_API AVSession: public Session
{
  typedef Session Base_;
public:
  AVSession(Conversation* pConv)
    : Base_(pConv)
  {
    type_ = uc::model::AudioVideo;
    state_ = SessionDisconnected;
  }

  virtual ~AVSession();

  /**
  * \brief hold audio/video call
  * \param[in]  N/A
  * \param[out] N/A
  * \return  true:  success ; false: Otherwise 
  */
  virtual bool Hold() = 0;

  virtual bool Switch() = 0;

  /**
  * \brief resume audio/video call
  * \param[in]  N/A
  * \param[out] N/A
  * \return  true:  success ; false: Otherwise 
  */
  virtual bool Resume() = 0;

  /**
  * \brief Reinvite audio call
  * \param[in]  N/A
  * \param[out] N/A
  * \return  true:  success ; false: Otherwise 
  */
  virtual bool Reinvite() = 0;
  /**
  * \brief Forward the call before accepting the call.
  * \param[in]  N/A
  * \param[out] N/A
  * \return  true:  success ; false: Otherwise 
  */
  virtual bool Forward(const uc::model::Contact& _contact) = 0;

  /**
  * \brief Consulttative call transfer. Just can operate when there is two call established
  * \param[in]  _contact Target Contact
  * \param[in]  _conv    another Conversation
  * \param[out] N/A
  * \return  true:  success ; false: Otherwise 
  */
  virtual bool ConsultativeTransfer(const uc::model::Contact& _contact, Conversation* _conv) = 0;

  /**
  * \brief Blind call transfer. Just can operate when there is two call established
  * \param[in]  _contact Target Contact
  * \param[out] N/A
  * \return  true:  success ; false: Otherwise 
  */
  virtual bool BlindTransfer(const uc::model::Contact& _contact) = 0;

  /**
  * \brief Mute just really implemented when this is audio conf and self is compere
  * \param[in]  _members Participant list
  * \param[out] N/A
  * \return  true:  success ; false: Otherwise 
  */
  virtual bool Mute(const std::vector<Participant>& _members) = 0;

  /**
  * \brief UnMute just really be implemented when this is audio conf and self is compere
  * \param[in]  _members Participant list
  * \param[out] N/A
  * \return  true:  success ; false: Otherwise 
  */
  virtual bool UnMute(const std::vector<Participant>& _members) = 0;

  /**
  * \brief Reserve the call for Parking
  * \param[in]  N/A
  * \param[out] N/A
  * \return  true:  success ; false: Otherwise 
  */
  virtual bool Reserve() = 0;

  /**
  * \brief Refer the contact to another conference conversation
  * \param[in]  N/A
  * \param[out] N/A
  * \return  true:  success ; false: Otherwise 
  */
  virtual bool Refer(const uc::model::Contact& _part) = 0;

  /**
  * \brief Start audio/video record 
  * \param[in]  file storing path
  * \param[out] N/A
  * \return  true:  success ; false: Otherwise 
  */
  virtual bool StartRecord(const std::string& _path) = 0;
  /**
  * \brief Stop audio/video record 
  * \param[in]  N/A
  * \param[out] N/A
  * \return  true:  success ; false: Otherwise 
  */
  virtual bool StopRecord() = 0;

  /**
  * \brief Get current audio call/conf mos value
  * \param[in]  N/A
  * \param[out] N/A
  * \return  current audio mos value
  */
  virtual int GetRealTimeAudioMos() = 0;

  virtual bool SendNotify(const std::string& code) = 0;

public:
  avchannel::AudioChannel audiochannel_;  //!< audio stream channel
  avchannel::VideoChannel videochannel_;  //!< video stream channel

  sigslot::signal1<AVSession* > StreamConnected_;

  sigslot::signal1<AVSession*> StreamHolded_;
};

static const char* const FILE_TRANS_TYPE_P2P = "0";
static const char* const FILE_TRANS_TYPE_HTTP_UPLOAD = "1";
static const char* const FILE_TRANS_TYPE_HTTP_DOWNLOAD = "2";
static const char* const FILE_TRANS_TYPE_P2S = "8";

class APPCLASSLAYER_API InstantMsgSession: public Session
{
  typedef Session Base_;
public:
  InstantMsgSession(Conversation* pConv)
    : Base_(pConv)
  {
    type_ = uc::model::InstantMessage;
  }

  virtual ~InstantMsgSession() {}


  virtual std::string TransferFile(const std::string& _filepath, const std::string& _transType, const std::string& _transXmlParam = "") = 0;
  virtual bool AcceptFile(const std::string& _fileID, const std::string _filePath) = 0;
  virtual bool CancelFile(const std::string& _fileID) = 0;
  virtual bool RejectFile(const std::string& _fileID) = 0;
  virtual bool RejectOfflineFile(const std::string& _msgID, const std::string& _senderUri, const std::string& _fileUrl, int _reasonCode = 0) = 0;

  virtual bool SendSmsMessage(
    const std::string& _text, int & msgid, bool needResponse = false) = 0;
  virtual bool SendMessage(const std::string& _text) = 0;
  virtual bool SendMessage(const std::map<InstantMessageContentType, std::string>& _text) = 0;

  virtual bool SetComposing(bool _typing) = 0;

  /**
  * \brief Connect is a sync action. It may take seconds to finish it.
  * \param[in]  N/A
  * \param[out] N/A
  * \return  true:  success ; false: Otherwise 
  */
  virtual bool SyncConnect() = 0;

public:
  sFileTransParam fileparam_;  /*!< file related param*/

  sigslot::signal2<FileTransState, int> FileTransferStateChanged_;

  sigslot::signal1<bool> IsTypingChanged_;
};

#ifdef WIN32

static const int DATA_CONF_USERID_MAXBITS = 9;

class APPCLASSLAYER_API DataShareSession: public Session
{
  typedef Session Base_;
public:
  DataShareSession(Conversation* pConv)
    : Base_(pConv)
  {
    type_ = uc::model::DataSharing;
  }
public:
  sigslot::signal1<sDataShareParam> DataShareMessageReceived;

public://��ؽӿ�
  virtual void PrepareConfParm(std::string & _confparms) = 0;
};
#endif

/**
* \brief CallExSession class handles special extended call business 
* \note This class is basic class of call exetend command session.
* \author  y00135380
* \version 1.0.0  initial version
*/
class APPCLASSLAYER_API CallExSession: public Session
{
  typedef Session Base_;
public:
  CallExSession(Conversation* pConv)
    : Base_(pConv)
  {
    type_ = uc::model::CallExBusiness;
    state_ = SessionDisconnected;
  }

  virtual ~CallExSession();

public:

  /**
  * \brief call extended session connected result.
  *        temp group has been created for UE
  *        UI need to implement has_slots<> and connect to the signal.
  *        Like this:  void OnSessConnectRes(Conversation* _conv, int _res); 
  * \note  0: rejected;  1: connected
  */
  sigslot::signal2<Conversation*, std::string> SessConnectRes_;
};

class APPCLASSLAYER_API FixedGroupShareSpaceFile
{
public:
    FixedGroupShareSpaceFile():sno_(""), name_(""),
        ownerId_(""),ownerName_(""), size_(""), timeStamp_(""), downloadCount_(0),
        uploadState_("-1"), downloadUrl_(""), sessionID_("")
    {

    }

public:
    std::string sno_;
    std::string name_;
    std::string absPath_;
    std::string ownerId_;
    std::string ownerName_;
    std::string size_;
    std::string timeStamp_;
    int downloadCount_;
    std::string uploadState_;
    std::string downloadUrl_;
    std::string sessionID_;
};



    }
  }
}
