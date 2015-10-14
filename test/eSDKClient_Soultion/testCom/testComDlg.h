
// testComDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"

interface IComIdl_eSDKSSO;

// CtestComDlg �Ի���
class CtestComDlg : public CDialog
{
// ����
public:
	CtestComDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_TESTCOM_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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
