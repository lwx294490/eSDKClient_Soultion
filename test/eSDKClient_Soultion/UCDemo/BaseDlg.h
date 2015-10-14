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
	afx_msg void OnBnClickedButtonContact();	//�鿴��ϵ���б�
	afx_msg void OnBnClickedButtonGroup();		//�鿴�̶�Ⱥ���б�
	afx_msg void OnBnClickedButtonBookconf();	//�鿴ԤԼ�����б�
	afx_msg void OnCbnSelchangeComboState();	//��������״̬
	afx_msg void OnNMDblclkTreeContact(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMRClickTreeContact(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMDblclkTreeGroup(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMRClickTreeGroup(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnClickContactMenuItem(UINT uID);
	afx_msg LRESULT OnMsgInputString(WPARAM wParm, LPARAM Lparam);	//����OnClickContactMenuItem�Ĳ�����Ϣ
	afx_msg LRESULT OnMsgChatWinClosed(WPARAM wParm, LPARAM Lparam);//�������ر�

	//��Ӧ����
	afx_msg LRESULT OnMsgAcceptCall(WPARAM wParm, LPARAM Lparam);	
	afx_msg LRESULT OnMsgRejectCall(WPARAM wParm, LPARAM Lparam);
	afx_msg LRESULT OnMsgForwardCall(WPARAM wParm, LPARAM Lparam);
	afx_msg LRESULT OnMsgJoinConference(WPARAM wParm, LPARAM Lparam);

	//�ص���Ϣ����
	afx_msg LRESULT OnMsgLogin(WPARAM wParm, LPARAM Lparam);		//��½�ǳ���Ȩ
	afx_msg LRESULT OnMsgStatus(WPARAM wParm, LPARAM Lparam);		//��ϵ��״̬�ı�	
	afx_msg LRESULT OnMsgAVSessAdded(WPARAM wParm, LPARAM Lparam);	//�����磨���ԡ���Ƶ�����飩
	afx_msg LRESULT OnMsgAVSessConnected(WPARAM wParm, LPARAM Lparam);//ͨ�����������ԡ���Ƶ�����飩
	afx_msg LRESULT OnMsgAVSessClosed(WPARAM wParm, LPARAM Lparam);	//ͨ���رգ����ԡ���Ƶ�����飩
	afx_msg LRESULT OnMsgReceivedIM(WPARAM wParm, LPARAM Lparam);	//���ռ�ʱ��Ϣ
	afx_msg LRESULT OnMsgConfStatusChg(WPARAM wParm, LPARAM Lparam);//����Ա״̬�仯
	afx_msg LRESULT OnMsgConfAllowSpk(WPARAM wParm, LPARAM Lparam);	//����Ա������
	afx_msg LRESULT OnMsgConfForbidSpk(WPARAM wParm, LPARAM Lparam);//����Ա��ֹ����
	afx_msg LRESULT OnMsgConfCurSpker(WPARAM wParm, LPARAM Lparam);	//��ǰ������
	afx_msg LRESULT OnMsgIMSessRemove(WPARAM wParm, LPARAM Lparam);	//��ʱ����Ự�ر�	
	afx_msg LRESULT OnMsgGroupInvitation(WPARAM wParm, LPARAM Lparam);//�̶�Ⱥ������
	afx_msg LRESULT OnMsgGroupInvitationRes(WPARAM wParm, LPARAM Lparam);//�̶�Ⱥ�����뷵��
	afx_msg LRESULT OnMsgGroupMemberChanged(WPARAM wParm, LPARAM Lparam);//�̶�Ⱥ���Ա�����䶯
	afx_msg LRESULT OnMsgGroupLeaveFixed(WPARAM wParm, LPARAM Lparam);//���߳��̶�Ⱥ����߹̶�Ⱥ���ɢ
	afx_msg LRESULT OnMsgGroupJoinFixedReq(WPARAM wParm, LPARAM Lparam);//�������̶�Ⱥ����Ϣ
	afx_msg LRESULT OnMsgGroupJoinFixedRsp(WPARAM wParm, LPARAM Lparam);//����̶�Ⱥ�����󷵻�
	DECLARE_MESSAGE_MAP()

public:
	void InitContactList();		//��ʼ����ϵ���б�
	void InitGroupList();		//��ʼ��Ⱥ���б�
	void PublishSelfState(int iState);	//�����Լ�״̬
	void UpdateContactTree(int _state, const CString& szAcc);	//������ϵ���б�״̬
	int GetStatusImageID(const std::string& uri);	//��ȡ��ϵ��״̬ͼƬID
	int GetStatusImageID(int state);				//��ȡ��ϵ��״̬ͼƬID

	void AddImage(CImageList& imageList, UINT _id);
	CChatDlg* GetChatDlgByAccount(const CString& ucAcc);		//ͨ��ucAcc��ȡ���촰��
	void ClearTree(CTreeCtrl& tree, const HTREEITEM& hItem);	//���Tree�ڵ�
	void DelTreeNode(CTreeCtrl& tree, const HTREEITEM& hItem);	//ɾ��Tree�ڵ�

	//��������
private:
	BOOL GetCustomGrouplist_(std::vector<UCCustomGroup>& list);//��ȡ���з����б�
	BOOL GetAllContactlist_(std::vector<UCContact>& list);//��ȡ������ϵ���б�
	BOOL GetContactlistFromCustomGroup_(const UCCustomGroup* group, std::vector<UCContact>& list);//��ȡ������������ϵ���б�
	BOOL RefreshFixedGrouplist_(std::vector<UCFixedGroup>& list);//ˢ�¹̶�Ⱥ���б�
	BOOL RefreshContactList_(const UCFixedGroup* group, std::vector<UCContact>& list);//ˢ�¹̶�Ⱥ������ϵ���б�

private:
	static void MemCopy(char* dest, const CString& str, size_t size);//����string�ڴ�

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

public:
	std::map<std::string, CChatDlg*> m_ChatDlgList;	//key:convId

public:
	CDialog* m_pCUCDemoDlg;
	CBookConfDlg m_CBookConfDlg;
	CInputDlg *m_pCInputDlg;
	CRingDlg* m_pCRingDlg;
};
