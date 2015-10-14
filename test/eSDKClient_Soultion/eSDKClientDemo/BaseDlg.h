/*****************************************************************
 filename    :    BaseDlg.h
 author      :    yWX200189
 created     :    2014/05/14
 description :    UCSDK主界面，包含联系人、群组、VoIP、Meeting、消息回调等逻辑处理
 copyright   :    Copyright (c) 2012-2016 Huawei Tech.Co.,Ltd
 history     :    2014/05/14 初始版本
*****************************************************************/

#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include "InputDlg.h"
#include "ChatDlg.h"
#include "RingDlg.h"
#include "BookConfDlg.h"


// CBaseDlg 对话框

class CBaseDlg : public CDialog
{
	DECLARE_DYNAMIC(CBaseDlg)

public:
	CBaseDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CBaseDlg();

// 对话框数据
	enum { IDD = IDD_BASE_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
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
	afx_msg LRESULT OnMsgInputString(WPARAM wParm, LPARAM Lparam);		//处理OnClickContactMenuItem的部分消息
	afx_msg LRESULT OnMsgChatWinClosed(WPARAM wParm, LPARAM Lparam);

	//响应操作
	afx_msg LRESULT OnMsgAcceptCall(WPARAM wParm, LPARAM Lparam);		//接听来电
	afx_msg LRESULT OnMsgRejectCall(WPARAM wParm, LPARAM Lparam);		//拒绝来电
	afx_msg LRESULT OnMsgForwardCall(WPARAM wParm, LPARAM Lparam);		//呼叫前转
	afx_msg LRESULT OnMsgJoinConference(WPARAM wParm, LPARAM Lparam);	//加入预约会议

	//回调消息处理
	afx_msg LRESULT OnMsgLogin(WPARAM wParm, LPARAM Lparam);			//登录
	afx_msg LRESULT OnMsgStatus(WPARAM wParm, LPARAM Lparam);			//联系人状态改变
	afx_msg LRESULT OnMsgAVSessAdded(WPARAM wParm, LPARAM Lparam);		//新来电
	afx_msg LRESULT OnMsgAVSessConnected(WPARAM wParm, LPARAM Lparam);	//通话建立
	afx_msg LRESULT OnMsgAVSessClosed(WPARAM wParm, LPARAM Lparam);		//通过关闭
	afx_msg LRESULT OnMsgReceivedIM(WPARAM wParm, LPARAM Lparam);		//接收即时消息
	afx_msg LRESULT OnMsgConfStatusChg(WPARAM wParm, LPARAM Lparam);	//会议成员状态改变
	afx_msg LRESULT OnMsgConfAllowSpk(WPARAM wParm, LPARAM Lparam);		//会议成员允许发言
	afx_msg LRESULT OnMsgConfForbidSpk(WPARAM wParm, LPARAM Lparam);	//会议成员禁止发言
	afx_msg LRESULT OnMsgConfCurSpker(WPARAM wParm, LPARAM Lparam);		//会议成员正在发言
	afx_msg LRESULT OnMsgIMSessRemove(WPARAM wParm, LPARAM Lparam);		//临时群组关闭	
	afx_msg LRESULT OnMsgGroupInvitation(WPARAM wParm, LPARAM Lparam);	//固定群组邀请消息
	afx_msg LRESULT OnMsgGroupInvitationRes(WPARAM wParm, LPARAM Lparam);//固定群组邀请结果消息
	afx_msg LRESULT OnMsgGroupMemberChanged(WPARAM wParm, LPARAM Lparam);//群组成员变动
	afx_msg LRESULT OnMsgGroupLeaveFixed(WPARAM wParm, LPARAM Lparam);	//离开固定群组，或者群组解散
	afx_msg LRESULT OnMsgGroupJoinFixedReq(WPARAM wParm, LPARAM Lparam);//加入固定群组请求
	afx_msg LRESULT OnMsgGroupJoinFixedRsp(WPARAM wParm, LPARAM Lparam);//加入固定群组请求返回
	DECLARE_MESSAGE_MAP()

	//初始化联系和群组列表
public:
	void InitContactList();
	void InitGroupList();
	void PublishSelfState(int iState);

public:
	void AddImage(CImageList& imageList, UINT _id);
	void UpdateContactTree(int _state, const CString& szAcc);
	CChatDlg* GetChatDlgByAccount(const CString& ucAcc);

	int GetStatusImageID(const std::string& uri);	//通过联系人uri获取联系人状态，然后返回状态图片ID
	int GetStatusImageID(int state);				//直接通过状态返回状态图片ID

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

	//聊天窗口列表，key值为会话ID
public:
	std::map<std::string, CChatDlg*> m_ChatDlgList;	//key:convId

	//窗口界面指针
public:
	CBookConfDlg m_CBookConfDlg;
	CInputDlg *m_pCInputDlg;
	CRingDlg* m_pCRingDlg;
	CDialog* m_pCeSDKClientDemoDlg;
	
	//UCSDK接口实例指针
public:
	UCSDKAbsProxy* m_pUCSDKAbsProxy;
	UCContactMgrAbsProxy* m_pUCContactMgrAbsProxy;
	UCGroupAbsProxy* m_pUCGroupAbsProxy;
	UCVoIPAbsProxy* m_pUCVoIPAbsProxy;
	UCPublicAbsProxy* m_pUCPublicAbsProxy;
};
