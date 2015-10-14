/*****************************************************************
 filename    :    RingDlg.h
 author      :    yWX200189
 created     :    2014/05/14
 description :    ������Ƶ���紦��������Ӧ�߼�����
 copyright   :    Copyright (c) 2012-2016 Huawei Tech.Co.,Ltd
 history     :    2014/05/14 ��ʼ�汾
*****************************************************************/

#pragma once
#include "afxwin.h"


// CRingDlg �Ի���

class CRingDlg : public CDialog
{
	DECLARE_DYNAMIC(CRingDlg)

public:
	CRingDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CRingDlg();

// �Ի�������
	enum { IDD = IDD_RING_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	afx_msg void OnClose();
	afx_msg void OnBnClickedButtonForward();
	afx_msg void OnBnClickedButtonAccept();
	afx_msg void OnBnClickedButtonReject();
	afx_msg void OnEnChangeEditForward();
	DECLARE_MESSAGE_MAP()

public:
	void Init();	//��ʼ����������

public:
	CString m_szForward;	//ǰת����
	CButton m_btnForward;
	CButton m_btnAccept;
	CButton m_btnReject;
	CStatic m_stVideo;

public:
	bool m_bIsOperator;
	AVSessAddedInfo* m_pAVAdd;
};
