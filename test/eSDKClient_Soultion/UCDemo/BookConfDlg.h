/*****************************************************************
 filename    :    BookConfDlg.h
 author      :    yWX200189
 created     :    2014/05/14
 description :    ԤԼ������棬������ȡԤԼ�����б�����ԤԼ������߼�����
 copyright   :    Copyright (c) 2012-2016 Huawei Tech.Co.,Ltd
 history     :    2014/05/14 ��ʼ�汾
*****************************************************************/

#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// CBookConfDlg �Ի���

class CBookConfDlg : public CDialog
{
	DECLARE_DYNAMIC(CBookConfDlg)

public:
	CBookConfDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CBookConfDlg();

// �Ի�������
	enum { IDD = IDD_BOOKCONF_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
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
