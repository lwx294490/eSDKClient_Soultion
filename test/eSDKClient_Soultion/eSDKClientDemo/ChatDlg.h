/*****************************************************************
 filename    :    ChatDlg.h
 author      :    yWX200189
 created     :    2014/05/14
 description :    ���촰�ڽ��棬����IM��VoIP��Meeting���߼�����ͽ���չʾ
 copyright   :    Copyright (c) 2012-2016 Huawei Tech.Co.,Ltd
 history     :    2014/05/14 ��ʼ�汾
*****************************************************************/

#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include "InputDlg.h"


// CChatDlg �Ի���

class CChatDlg : public CDialog
{
	DECLARE_DYNAMIC(CChatDlg)

public:
	CChatDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CChatDlg();

// �Ի�������
	enum { IDD = IDD_CHAT_DIALOG };

public:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);

	afx_msg void OnClose();
	afx_msg void OnBnClickedButtonHold();		//���б���
	afx_msg void OnBnClickedButtonResume();		//���лָ�
	afx_msg void OnBnClickedButtonStartRecord();	//��ʼ¼��
	afx_msg void OnBnClickedButtonStopRecord();	//�ܾ�¼��
	afx_msg void OnBnClickedButtonMicmute();	//��˷羲��
	afx_msg void OnBnClickedButtonMicunmute();	//��˷�ȡ������
	afx_msg void OnBnClickedButtonSpkmute();	//����������
	afx_msg void OnBnClickedButtonSpkunmute();	//������ȡ������
	afx_msg void OnBnClickedButtonAdd();		//��ӳ�Ա
	afx_msg void OnBnClickedButtonSend();		//���ͼ�ʱ��Ϣ
	afx_msg void OnBnClickedButtonCall();		//������������
	afx_msg void OnBnClickedButtonVideocall();	//������Ƶ����
	afx_msg void OnBnClickedButtonHangup();		//�ҶϺ���
	afx_msg void OnNMRClickListCont(NMHDR *pNMHDR, LRESULT *pResult);	//�һ������Ա�б�
	afx_msg void OnClickListContMenuItem(UINT uID);
	afx_msg LRESULT OnMsgInputString(WPARAM wParm, LPARAM Lparam);		//��������Ա��Ϣ����
	DECLARE_MESSAGE_MAP()

public:
	void AddImage(CImageList& imageList, UINT _id);
	void CreateURichEdit(CRichEditCtrl &RichEdit , RECT& rcRichEdit, BOOL bIsReadOnly ,UINT controlID);

public:
	void RecvIMMsg(CString header, CString body);				//���ռ�ʱ��Ϣ
	std::string CreateConvID();									//�����ỰID����֤չʾ��Chatdlg�������һ�����õĻỰID
	void UpdateConfMemList(const CString& szAcc, int nStatus);	//���»����Ա״̬
	void AddConfCompere(const CString& szAcc, int nStatus);		//���ӻ�����ϯ
	void AddConfMember(const CString& szAcc, int nStatus);		//��������Ա
	void UpdateConfMember(const CString& szAcc, int nStatus);	//���������Ա
	std::string GetModulePath(const CString& dllName);			//��ȡģ��·��
	std::string GetDateTimeString();							//��ȡ����ʱ���ַ���
	BOOL IsMeetingConv();										//�Ƿ�Ϊ����Ự

public:
	CButton m_btnHold;
	CButton m_btnResume;
	CButton m_btnStartRecord;
	CButton m_btnStopRecord;
	CButton m_btnMicMute;
	CButton m_btnMicUnMute;
	CButton m_btnSpkMute;
	CButton m_btnSpkUnMute;
	CButton m_btnCall;
	CButton m_btnVideoCall;
	CButton m_btnAdd;
	CButton m_btnHangup;
	CButton m_btnSend;
	CListCtrl m_ConfMemList;
	CStatic m_stRemote;
	CStatic m_stLocal;
	CStatic m_stRecvMsg;
	CStatic m_stSendMsg;
	CRichEditCtrl m_RichRecvMsg;
	CRichEditCtrl m_RichSendMsg;
	CImageList m_lstImage;

	//��������
public:
	CString m_szAccount;	//��½�û��˺�
	CString m_szCompere;	//�����������˺�
	CString m_szTargetAcc;	//��������˺�
	std::string m_convId;	//�ỰID
	BOOL m_bIsVideo;		//��Ƶ��ʾ

	//����չʾ��ʵ��ָ��
public:
	CDialog* m_pCBaseDlg;
	CInputDlg* m_pCInputDlg;

	//UCSDK��ʵ��ָ��
public:
	UCIMAbsProxy* m_pUCIMAbsProxy;
	UCVoIPAbsProxy* m_pUCVoIPAbsProxy;
	UCMeetingAbsProxy* m_pUCMeetingAbsProxy;
};
