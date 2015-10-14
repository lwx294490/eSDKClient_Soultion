/*****************************************************************
 filename    :    eSDKClientDemoDlg.h
 author      :    yWX200189
 created     :    2014/05/14
 description :    Demo�����棬������ʼ������¼�ȼ�Ȩ��ͨ��ƽ̨��¼SSO��UCSDKҵ�񣬲���̨���а汾����
 copyright   :    Copyright (c) 2012-2016 Huawei Tech.Co.,Ltd
 history     :    2014/05/14 ��ʼ�汾
*****************************************************************/

// eSDKClientDemoDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"
#include "BaseDlg.h"
#include "UCSignalRecvProxy.h"


// CeSDKClientDemoDlg �Ի���
class CeSDKClientDemoDlg : public CDialog
{
// ����
public:
	CeSDKClientDemoDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_ESDKCLIENTDEMO_DIALOG };

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
	//�汾�����ص�����
	static bool CALLBACK UpdateVersionCB(int iMsgID, std::string strDes);

public:
	CString m_szSSOSrvUrl;	//SSO������Url
	CString m_szHostIP;		//����hostIP
	CString m_szUpdSrvUrl;	//�汾����������Url
	CString m_szUCSrvUrl;	//UC������Url
	CString m_szAccount;	//UC�˺�
	CString m_szPasswd;		//UC����
	CString m_szToken;		//token
	CString m_szLang;		//��½����
	CComboBox m_cmbType;
	CButton m_btnInit;
	CButton m_btnUnInit;
	CButton m_btnLoginPasswd;
	CButton m_btnLoginToken;
	CButton m_btnLogout;
	int m_iType;

	//���ڽ���ָ��
public:	
	static CeSDKClientDemoDlg* m_pCeSDKClientDemoDlg;
	CBaseDlg* m_pCBaseDlg;

	//�źŻص�������
public:
	UCSignalRecvProxy m_UCSignalRecvProxy;

	//SDKʵ��ָ��
public:
	eSDKClientPlatform* m_peSDKClientPlatform;
	UCSDKAbsProxy* m_pUCSDKAbsProxy;
	UCSignalRecvAbsProxy* m_pUCSignalRecvAbsProxy;
};
