/*****************************************************************
 filename    :    eSDKClientDemoDlg.h
 author      :    yWX200189
 created     :    2014/05/14
 description :    Demo主界面，包括初始化、登录等鉴权，通过平台登录SSO和UCSDK业务，并后台进行版本升级
 copyright   :    Copyright (c) 2012-2016 Huawei Tech.Co.,Ltd
 history     :    2014/05/14 初始版本
*****************************************************************/

// eSDKClientDemoDlg.h : 头文件
//

#pragma once
#include "afxwin.h"
#include "BaseDlg.h"
#include "UCSignalRecvProxy.h"


// CeSDKClientDemoDlg 对话框
class CeSDKClientDemoDlg : public CDialog
{
// 构造
public:
	CeSDKClientDemoDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_ESDKCLIENTDEMO_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnClose();
	afx_msg void OnBnClickedButtonInit();	//初始化
	afx_msg void OnBnClickedButtonUninit();	//去初始化
	afx_msg void OnBnClickedButtonPasswd();	//用户名密码登陆
	afx_msg void OnBnClickedButtonToken();	//token登陆
	afx_msg void OnBnClickedButtonLogout();	//登出
	afx_msg void OnCbnSelchangeComboType();
	afx_msg void OnEnChangeEditUrl();
	afx_msg void OnEnChangeEditHostip();
	afx_msg void OnEnChangeEditUpdatesrv();
	afx_msg void OnEnChangeEditUcurl();
	afx_msg void OnEnChangeEditName();
	afx_msg void OnEnChangeEditPasswd();
	afx_msg LRESULT OnMsgBaseDlgClose(WPARAM wParm, LPARAM Lparam);
	DECLARE_MESSAGE_MAP()

public:
	//版本升级回调函数
	static bool CALLBACK UpdateVersionCB(int iMsgID, std::string strDes);

public:
	CString m_szSSOSrvUrl;	//SSO服务器Url
	CString m_szHostIP;		//本地hostIP
	CString m_szUpdSrvUrl;	//版本升级服务器Url
	CString m_szUCSrvUrl;	//UC服务器Url
	CString m_szAccount;	//UC账号
	CString m_szPasswd;		//UC密码
	CString m_szToken;		//token
	CString m_szLang;		//登陆语言
	CComboBox m_cmbType;
	CButton m_btnInit;
	CButton m_btnUnInit;
	CButton m_btnLoginPasswd;
	CButton m_btnLoginToken;
	CButton m_btnLogout;
	int m_iType;

	//窗口界面指针
public:	
	static CeSDKClientDemoDlg* m_pCeSDKClientDemoDlg;
	CBaseDlg* m_pCBaseDlg;

	//信号回调管理类
public:
	UCSignalRecvProxy m_UCSignalRecvProxy;

	//SDK实例指针
public:
	eSDKClientPlatform* m_peSDKClientPlatform;
	UCSDKAbsProxy* m_pUCSDKAbsProxy;
	UCSignalRecvAbsProxy* m_pUCSignalRecvAbsProxy;
};
