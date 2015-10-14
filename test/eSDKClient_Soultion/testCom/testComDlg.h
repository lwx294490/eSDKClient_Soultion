
// testComDlg.h : 头文件
//

#pragma once
#include "afxwin.h"

interface IComIdl_eSDKSSO;

// CtestComDlg 对话框
class CtestComDlg : public CDialog
{
// 构造
public:
	CtestComDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_TESTCOM_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CButton m_btnWriteToken;
	CString m_szToken;
	CString m_szName;
	CString m_szPassword;
	CString m_szUri;
	CButton m_btnGetToken;
	CButton m_btnClearToken;
	CButton m_btnSSOLogin;
	afx_msg void OnBnClickedButtonWritetoken();
	afx_msg void OnBnClickedButtonGettoken();
	afx_msg void OnBnClickedButtonCleartoken();
	afx_msg void OnBnClickedButtonSsologin();
	afx_msg void OnEnChangeEditToken();
	afx_msg void OnEnChangeEditName();
	afx_msg void OnEnChangeEditPassword();
	afx_msg void OnEnChangeEditUri();
	afx_msg void OnClose();

public:
	IComIdl_eSDKSSO *m_pIntf;
};
