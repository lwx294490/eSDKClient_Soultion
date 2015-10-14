/*****************************************************************
 filename    :    RingDlg.h
 author      :    yWX200189
 created     :    2014/05/14
 description :    语音视频来电处理界面和相应逻辑处理
 copyright   :    Copyright (c) 2012-2016 Huawei Tech.Co.,Ltd
 history     :    2014/05/14 初始版本
*****************************************************************/

#pragma once
#include "afxwin.h"


// CRingDlg 对话框

class CRingDlg : public CDialog
{
	DECLARE_DYNAMIC(CRingDlg)

public:
	CRingDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CRingDlg();

// 对话框数据
	enum { IDD = IDD_RING_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	afx_msg void OnClose();
	afx_msg void OnBnClickedButtonForward();
	afx_msg void OnBnClickedButtonAccept();
	afx_msg void OnBnClickedButtonReject();
	afx_msg void OnEnChangeEditForward();
	DECLARE_MESSAGE_MAP()

public:
	void Init();	//初始化界面数据

public:
	CString m_szForward;	//前转号码
	CButton m_btnForward;
	CButton m_btnAccept;
	CButton m_btnReject;
	CStatic m_stVideo;

public:
	bool m_bIsOperator;
	AVSessAddedInfo* m_pAVAdd;
};
