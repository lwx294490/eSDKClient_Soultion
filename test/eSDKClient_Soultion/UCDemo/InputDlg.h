/*****************************************************************
 filename    :    InputDlg.h
 author      :    yWX200189
 created     :    2014/05/14
 description :    输入界面展示类，和相应逻辑处理
 copyright   :    Copyright (c) 2012-2016 Huawei Tech.Co.,Ltd
 history     :    2014/05/14 初始版本
*****************************************************************/

#pragma once
#include "afxwin.h"


// CInputDlg 对话框

class CInputDlg : public CDialog
{
	DECLARE_DYNAMIC(CInputDlg)

public:
	CInputDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CInputDlg();

// 对话框数据
	enum { IDD = IDD_INPUT_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

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
