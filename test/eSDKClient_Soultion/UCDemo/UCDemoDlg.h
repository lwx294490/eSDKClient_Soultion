/*****************************************************************
 filename    :    UCDemoDlg.h
 author      :    yWX200189
 created     :    2014/05/14
 description :    Demo主界面，包括初始化、登录等鉴权，通过平台登录SSO和UCSDK业务，并后台进行版本升级
 copyright   :    Copyright (c) 2012-2016 Huawei Tech.Co.,Ltd
 history     :    2014/05/14 初始版本
*****************************************************************/

// UCDemoDlg.h : 头文件
//

#pragma once
#include "afxwin.h"
#include "BaseDlg.h"


// CUCDemoDlg 对话框
class CUCDemoDlg : public CDialog
{
// 构造
public:
	CUCDemoDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_UCDEMO_DIALOG };

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
	afx_msg void OnEnChangeEditSsourl();
	afx_msg void OnEnChangeEditHostip();
	afx_msg void OnEnChangeEditUpdurl();
	afx_msg void OnEnChangeEditUcurl();
	afx_msg void OnEnChangeEditAccount();
	afx_msg void OnEnChangeEditPasswd();
	afx_msg void OnCbnSelchangeComboType();
	afx_msg LRESULT OnMsgBaseDlgClose(WPARAM wparam, LPARAM lparam);
	DECLARE_MESSAGE_MAP()

	//设置UC SDK回调函数
public:
	void SetCallBack();

	//版本升级回调函数
public:
	static bool CALLBACK UpdateMessageCallBack(int iMsgID, char* pchDescription);

public:
	CButton m_btnInit;
	CButton m_btnUnInit;
	CButton m_btnLoginByPwd;
	CButton m_btnLoginByToken;
	CButton m_btnLogout;
	CString m_szSSOUrl;		//SSO服务器
	CString m_szHostIp;		//本地IP
	CString m_szUpdateUrl;	//版本升级服务器
	CString m_szUCUrl;		//UC服务器
	CString m_szAccount;	//登陆账号
	CString m_szPasswd;		//登陆密码
	CString m_szToken;		//token
	CString m_szLang;		//登陆语言
	CComboBox m_cmbLoginType;
	int m_iLoginType;
	
public:
	CBaseDlg* m_pCBaseDlg;
};
