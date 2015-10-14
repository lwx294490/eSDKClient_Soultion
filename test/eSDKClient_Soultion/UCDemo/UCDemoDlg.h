/*****************************************************************
 filename    :    UCDemoDlg.h
 author      :    yWX200189
 created     :    2014/05/14
 description :    Demo�����棬������ʼ������¼�ȼ�Ȩ��ͨ��ƽ̨��¼SSO��UCSDKҵ�񣬲���̨���а汾����
 copyright   :    Copyright (c) 2012-2016 Huawei Tech.Co.,Ltd
 history     :    2014/05/14 ��ʼ�汾
*****************************************************************/

// UCDemoDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"
#include "BaseDlg.h"


// CUCDemoDlg �Ի���
class CUCDemoDlg : public CDialog
{
// ����
public:
	CUCDemoDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_UCDEMO_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnClose();
	afx_msg void OnBnClickedButtonInit();	//��ʼ��
	afx_msg void OnBnClickedButtonUninit();	//ȥ��ʼ��
	afx_msg void OnBnClickedButtonPasswd();	//�û��������½
	afx_msg void OnBnClickedButtonToken();	//token��½
	afx_msg void OnBnClickedButtonLogout();	//�ǳ�
	afx_msg void OnEnChangeEditSsourl();
	afx_msg void OnEnChangeEditHostip();
	afx_msg void OnEnChangeEditUpdurl();
	afx_msg void OnEnChangeEditUcurl();
	afx_msg void OnEnChangeEditAccount();
	afx_msg void OnEnChangeEditPasswd();
	afx_msg void OnCbnSelchangeComboType();
	afx_msg LRESULT OnMsgBaseDlgClose(WPARAM wparam, LPARAM lparam);
	DECLARE_MESSAGE_MAP()

	//����UC SDK�ص�����
public:
	void SetCallBack();

	//�汾�����ص�����
public:
	static bool CALLBACK UpdateMessageCallBack(int iMsgID, char* pchDescription);

public:
	CButton m_btnInit;
	CButton m_btnUnInit;
	CButton m_btnLoginByPwd;
	CButton m_btnLoginByToken;
	CButton m_btnLogout;
	CString m_szSSOUrl;		//SSO������
	CString m_szHostIp;		//����IP
	CString m_szUpdateUrl;	//�汾����������
	CString m_szUCUrl;		//UC������
	CString m_szAccount;	//��½�˺�
	CString m_szPasswd;		//��½����
	CString m_szToken;		//token
	CString m_szLang;		//��½����
	CComboBox m_cmbLoginType;
	int m_iLoginType;
	
public:
	CBaseDlg* m_pCBaseDlg;
};
