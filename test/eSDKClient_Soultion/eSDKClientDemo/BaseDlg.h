/*****************************************************************
 filename    :    BaseDlg.h
 author      :    yWX200189
 created     :    2014/05/14
 description :    UCSDK�����棬������ϵ�ˡ�Ⱥ�顢VoIP��Meeting����Ϣ�ص����߼�����
 copyright   :    Copyright (c) 2012-2016 Huawei Tech.Co.,Ltd
 history     :    2014/05/14 ��ʼ�汾
*****************************************************************/

#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include "InputDlg.h"
#include "ChatDlg.h"
#include "RingDlg.h"
#include "BookConfDlg.h"


// CBaseDlg �Ի���

class CBaseDlg : public CDialog
{
	DECLARE_DYNAMIC(CBaseDlg)

public:
	CBaseDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CBaseDlg();

// �Ի�������
	enum { IDD = IDD_BASE_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);

	afx_msg void OnClose();
	afx_msg void OnBnClickedButtonContact();
	afx_msg void OnBnClickedButtonGroup();
	afx_msg void OnBnClickedButtonBookconf();
	afx_msg void OnCbnSelchangeComboState();
	afx_msg void OnNMDblclkTreeContact(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMRClickTreeContact(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMDblclkTreeGroup(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMRClickTreeGroup(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnClickContactMenuItem(UINT uID);
	afx_msg LRESULT OnMsgInputString(WPARAM wParm, LPARAM Lparam);		//����OnClickContactMenuItem�Ĳ�����Ϣ
	afx_msg LRESULT OnMsgChatWinClosed(WPARAM wParm, LPARAM Lparam);

	//��Ӧ����
	afx_msg LRESULT OnMsgAcceptCall(WPARAM wParm, LPARAM Lparam);		//��������
	afx_msg LRESULT OnMsgRejectCall(WPARAM wParm, LPARAM Lparam);		//�ܾ�����
	afx_msg LRESULT OnMsgForwardCall(WPARAM wParm, LPARAM Lparam);		//����ǰת
	afx_msg LRESULT OnMsgJoinConference(WPARAM wParm, LPARAM Lparam);	//����ԤԼ����

	//�ص���Ϣ����
	afx_msg LRESULT OnMsgLogin(WPARAM wParm, LPARAM Lparam);			//��¼
	afx_msg LRESULT OnMsgStatus(WPARAM wParm, LPARAM Lparam);			//��ϵ��״̬�ı�
	afx_msg LRESULT OnMsgAVSessAdded(WPARAM wParm, LPARAM Lparam);		//������
	afx_msg LRESULT OnMsgAVSessConnected(WPARAM wParm, LPARAM Lparam);	//ͨ������
	afx_msg LRESULT OnMsgAVSessClosed(WPARAM wParm, LPARAM Lparam);		//ͨ���ر�
	afx_msg LRESULT OnMsgReceivedIM(WPARAM wParm, LPARAM Lparam);		//���ռ�ʱ��Ϣ
	afx_msg LRESULT OnMsgConfStatusChg(WPARAM wParm, LPARAM Lparam);	//�����Ա״̬�ı�
	afx_msg LRESULT OnMsgConfAllowSpk(WPARAM wParm, LPARAM Lparam);		//�����Ա������
	afx_msg LRESULT OnMsgConfForbidSpk(WPARAM wParm, LPARAM Lparam);	//�����Ա��ֹ����
	afx_msg LRESULT OnMsgConfCurSpker(WPARAM wParm, LPARAM Lparam);		//�����Ա���ڷ���
	afx_msg LRESULT OnMsgIMSessRemove(WPARAM wParm, LPARAM Lparam);		//��ʱȺ��ر�	
	afx_msg LRESULT OnMsgGroupInvitation(WPARAM wParm, LPARAM Lparam);	//�̶�Ⱥ��������Ϣ
	afx_msg LRESULT OnMsgGroupInvitationRes(WPARAM wParm, LPARAM Lparam);//�̶�Ⱥ����������Ϣ
	afx_msg LRESULT OnMsgGroupMemberChanged(WPARAM wParm, LPARAM Lparam);//Ⱥ���Ա�䶯
	afx_msg LRESULT OnMsgGroupLeaveFixed(WPARAM wParm, LPARAM Lparam);	//�뿪�̶�Ⱥ�飬����Ⱥ���ɢ
	afx_msg LRESULT OnMsgGroupJoinFixedReq(WPARAM wParm, LPARAM Lparam);//����̶�Ⱥ������
	afx_msg LRESULT OnMsgGroupJoinFixedRsp(WPARAM wParm, LPARAM Lparam);//����̶�Ⱥ�����󷵻�
	DECLARE_MESSAGE_MAP()

	//��ʼ����ϵ��Ⱥ���б�
public:
	void InitContactList();
	void InitGroupList();
	void PublishSelfState(int iState);

public:
	void AddImage(CImageList& imageList, UINT _id);
	void UpdateContactTree(int _state, const CString& szAcc);
	CChatDlg* GetChatDlgByAccount(const CString& ucAcc);

	int GetStatusImageID(const std::string& uri);	//ͨ����ϵ��uri��ȡ��ϵ��״̬��Ȼ�󷵻�״̬ͼƬID
	int GetStatusImageID(int state);				//ֱ��ͨ��״̬����״̬ͼƬID

	void ClearTree(CTreeCtrl& tree, const HTREEITEM& hItem);
	void DelTreeNode(CTreeCtrl& tree, const HTREEITEM& hItem);

public:
	CStatic m_stPhoto;
	CString m_szAccount;
	CComboBox m_cmbState;
	CButton m_btnContact;
	CButton m_btnGroup;
	CButton m_btnBookConf;
	CTreeCtrl m_ContactList;
	CTreeCtrl m_GroupList;
	CImageList m_lstImage;

	//���촰���б�keyֵΪ�ỰID
public:
	std::map<std::string, CChatDlg*> m_ChatDlgList;	//key:convId

	//���ڽ���ָ��
public:
	CBookConfDlg m_CBookConfDlg;
	CInputDlg *m_pCInputDlg;
	CRingDlg* m_pCRingDlg;
	CDialog* m_pCeSDKClientDemoDlg;
	
	//UCSDK�ӿ�ʵ��ָ��
public:
	UCSDKAbsProxy* m_pUCSDKAbsProxy;
	UCContactMgrAbsProxy* m_pUCContactMgrAbsProxy;
	UCGroupAbsProxy* m_pUCGroupAbsProxy;
	UCVoIPAbsProxy* m_pUCVoIPAbsProxy;
	UCPublicAbsProxy* m_pUCPublicAbsProxy;
};
