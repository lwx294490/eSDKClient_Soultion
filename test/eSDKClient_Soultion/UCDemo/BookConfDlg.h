/*****************************************************************
 filename    :    BookConfDlg.h
 author      :    yWX200189
 created     :    2014/05/14
 description :    预约会议界面，包括获取预约会议列表，加入预约会议等逻辑处理
 copyright   :    Copyright (c) 2012-2016 Huawei Tech.Co.,Ltd
 history     :    2014/05/14 初始版本
*****************************************************************/

#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// CBookConfDlg 对话框

class CBookConfDlg : public CDialog
{
	DECLARE_DYNAMIC(CBookConfDlg)

public:
	CBookConfDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CBookConfDlg();

// 对话框数据
	enum { IDD = IDD_BOOKCONF_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();

	afx_msg void OnClose();
	afx_msg void OnBnClickedButtonLeave();
	afx_msg void OnNMRClickListBookconf(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnClickBookConfMenuItem(UINT uID);
	DECLARE_MESSAGE_MAP()

public:
	void ShowBookConfList();
	BOOL GetBookConfList_(std::vector<UCBookConf>& list);

public:
	CButton m_btnLeaveConf;
	CListCtrl m_BookConfList;

public:
	bool m_bHaveJoin;
	std::string m_convId;
	std::vector<UCBookConf> m_UCBookConfList;
	CDialog* m_pCBaseDlg;
};
