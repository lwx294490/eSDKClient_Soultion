/*****************************************************************
 filename    :    InputDlg.h
 author      :    yWX200189
 created     :    2014/05/14
 description :    �������չʾ�࣬����Ӧ�߼�����
 copyright   :    Copyright (c) 2012-2016 Huawei Tech.Co.,Ltd
 history     :    2014/05/14 ��ʼ�汾
*****************************************************************/

#pragma once
#include "afxwin.h"


// CInputDlg �Ի���

class CInputDlg : public CDialog
{
	DECLARE_DYNAMIC(CInputDlg)

public:
	CInputDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CInputDlg();

// �Ի�������
	enum { IDD = IDD_INPUT_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	afx_msg void OnClose();
	afx_msg void OnEnChangeEditInput();
	afx_msg void OnBnClickedButtonOk();
	afx_msg void OnBnClickedButtonCancel();
	DECLARE_MESSAGE_MAP()

public:
	void Init();

public:
	CString m_szInput;
	CButton m_btnOK;
	CButton m_btnCancel;

public:
	CString m_szRect;
	CString m_szFlag;
	PTREEITEMDATA m_pTreeItemData;
};
