
// eSDKClientLogTestDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"


// CeSDKClientLogTestDlg �Ի���
class CeSDKClientLogTestDlg : public CDialog
{
// ����
public:
	CeSDKClientLogTestDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_ESDKCLIENTLOGTEST_DIALOG };

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
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	// ��־��ʼ��·��
	CEdit m_Path;
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton6();
	afx_msg void OnBnClickedButton5();
};
