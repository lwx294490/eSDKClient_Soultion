/*****************************************************************
 filename    :    ChatDlg.h
 author      :    yWX200189
 created     :    2014/05/14
 description :    聊天窗口界面，包括IM、VoIP、Meeting等逻辑处理和界面展示
 copyright   :    Copyright (c) 2012-2016 Huawei Tech.Co.,Ltd
 history     :    2014/05/14 初始版本
*****************************************************************/

#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include "InputDlg.h"


// CChatDlg 对话框

class CChatDlg : public CDialog
{
	DECLARE_DYNAMIC(CChatDlg)

public:
	CChatDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CChatDlg();

// 对话框数据
	enum { IDD = IDD_CHAT_DIALOG };

public:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);

	afx_msg void OnClose();
	afx_msg void OnBnClickedButtonHold();		//呼叫保持
	afx_msg void OnBnClickedButtonResume();		//呼叫恢复
	afx_msg void OnBnClickedButtonStartRecord();	//开始录音
	afx_msg void OnBnClickedButtonStopRecord();	//拒绝录音
	afx_msg void OnBnClickedButtonMicmute();	//麦克风静音
	afx_msg void OnBnClickedButtonMicunmute();	//麦克风取消静音
	afx_msg void OnBnClickedButtonSpkmute();	//扬声器静音
	afx_msg void OnBnClickedButtonSpkunmute();	//扬声器取消静音
	afx_msg void OnBnClickedButtonAdd();		//添加成员
	afx_msg void OnBnClickedButtonSend();		//发送即时消息
	afx_msg void OnBnClickedButtonCall();		//发起语音呼叫
	afx_msg void OnBnClickedButtonVideocall();	//发起视频呼叫
	afx_msg void OnBnClickedButtonHangup();		//挂断呼叫
	afx_msg void OnNMRClickListCont(NMHDR *pNMHDR, LRESULT *pResult);	//右击会议成员列表
	afx_msg void OnClickListContMenuItem(UINT uID);
	afx_msg LRESULT OnMsgInputString(WPARAM wParm, LPARAM Lparam);		//添加聊天成员消息处理
	DECLARE_MESSAGE_MAP()

public:
	void AddImage(CImageList& imageList, UINT _id);
	void CreateURichEdit(CRichEditCtrl &RichEdit , RECT& rcRichEdit, BOOL bIsReadOnly ,UINT controlID);

public:
	void RecvIMMsg(CString header, CString body);				//接收即时消息
	std::string CreateConvID();									//创建会话ID，保证展示的Chatdlg界面存在一个可用的会话ID
	void UpdateConfMemList(const CString& szAcc, int nStatus);	//更新会议成员状态
	void AddConfCompere(const CString& szAcc, int nStatus);		//增加会议主席
	void AddConfMember(const CString& szAcc, int nStatus);		//增加与会成员
	void UpdateConfMember(const CString& szAcc, int nStatus);	//更新与会人员
	std::string GetModulePath(const CString& dllName);			//获取模块路径
	std::string GetDateTimeString();							//获取日期时间字符串
	BOOL IsMeetingConv();										//是否为会议会话

public:
	CButton m_btnHold;
	CButton m_btnResume;
	CButton m_btnStartRecord;
	CButton m_btnStopRecord;
	CButton m_btnMicMute;
	CButton m_btnMicUnMute;
	CButton m_btnSpkMute;
	CButton m_btnSpkUnMute;
	CButton m_btnCall;
	CButton m_btnVideoCall;
	CButton m_btnAdd;
	CButton m_btnHangup;
	CButton m_btnSend;
	CListCtrl m_ConfMemList;
	CStatic m_stRemote;
	CStatic m_stLocal;
	CStatic m_stRecvMsg;
	CStatic m_stSendMsg;
	CRichEditCtrl m_RichRecvMsg;
	CRichEditCtrl m_RichSendMsg;
	CImageList m_lstImage;

	//辅助变量
public:
	CString m_szAccount;	//登陆用户账号
	CString m_szCompere;	//会议主持人账号
	CString m_szTargetAcc;	//聊天对象账号
	std::string m_convId;	//会话ID
	BOOL m_bIsVideo;		//视频标示

	//界面展示类实例指针
public:
	CDialog* m_pCBaseDlg;
	CInputDlg* m_pCInputDlg;

	//UCSDK类实例指针
public:
	UCIMAbsProxy* m_pUCIMAbsProxy;
	UCVoIPAbsProxy* m_pUCVoIPAbsProxy;
	UCMeetingAbsProxy* m_pUCMeetingAbsProxy;
};
