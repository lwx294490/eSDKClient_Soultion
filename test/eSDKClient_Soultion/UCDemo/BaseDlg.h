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
	afx_msg void OnBnClickedButtonContact();	//查看联系人列表
	afx_msg void OnBnClickedButtonGroup();		//查看固定群组列表
	afx_msg void OnBnClickedButtonBookconf();	//查看预约会议列表
	afx_msg void OnCbnSelchangeComboState();	//发布在线状态
	afx_msg void OnNMDblclkTreeContact(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMRClickTreeContact(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMDblclkTreeGroup(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMRClickTreeGroup(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnClickContactMenuItem(UINT uID);
	afx_msg LRESULT OnMsgInputString(WPARAM wParm, LPARAM Lparam);	//处理OnClickContactMenuItem的部分消息
	afx_msg LRESULT OnMsgChatWinClosed(WPARAM wParm, LPARAM Lparam);//聊天界面关闭

	//响应操作
	afx_msg LRESULT OnMsgAcceptCall(WPARAM wParm, LPARAM Lparam);	
	afx_msg LRESULT OnMsgRejectCall(WPARAM wParm, LPARAM Lparam);
	afx_msg LRESULT OnMsgForwardCall(WPARAM wParm, LPARAM Lparam);
	afx_msg LRESULT OnMsgJoinConference(WPARAM wParm, LPARAM Lparam);

	//回调消息处理
	afx_msg LRESULT OnMsgLogin(WPARAM wParm, LPARAM Lparam);		//登陆登出鉴权
	afx_msg LRESULT OnMsgStatus(WPARAM wParm, LPARAM Lparam);		//联系人状态改变	
	afx_msg LRESULT OnMsgAVSessAdded(WPARAM wParm, LPARAM Lparam);	//新来电（语言、视频、会议）
	afx_msg LRESULT OnMsgAVSessConnected(WPARAM wParm, LPARAM Lparam);//通话建立（语言、视频、会议）
	afx_msg LRESULT OnMsgAVSessClosed(WPARAM wParm, LPARAM Lparam);	//通话关闭（语言、视频、会议）
	afx_msg LRESULT OnMsgReceivedIM(WPARAM wParm, LPARAM Lparam);	//接收即时消息
	afx_msg LRESULT OnMsgConfStatusChg(WPARAM wParm, LPARAM Lparam);//与会成员状态变化
	afx_msg LRESULT OnMsgConfAllowSpk(WPARAM wParm, LPARAM Lparam);	//与会成员允许发言
	afx_msg LRESULT OnMsgConfForbidSpk(WPARAM wParm, LPARAM Lparam);//与会成员禁止发言
	afx_msg LRESULT OnMsgConfCurSpker(WPARAM wParm, LPARAM Lparam);	//当前发言人
	afx_msg LRESULT OnMsgIMSessRemove(WPARAM wParm, LPARAM Lparam);	//临时会议会话关闭	
	afx_msg LRESULT OnMsgGroupInvitation(WPARAM wParm, LPARAM Lparam);//固定群组邀请
	afx_msg LRESULT OnMsgGroupInvitationRes(WPARAM wParm, LPARAM Lparam);//固定群组邀请返回
	afx_msg LRESULT OnMsgGroupMemberChanged(WPARAM wParm, LPARAM Lparam);//固定群组成员数量变动
	afx_msg LRESULT OnMsgGroupLeaveFixed(WPARAM wParm, LPARAM Lparam);//被踢出固定群组或者固定群组解散
	afx_msg LRESULT OnMsgGroupJoinFixedReq(WPARAM wParm, LPARAM Lparam);//请求加入固定群组消息
	afx_msg LRESULT OnMsgGroupJoinFixedRsp(WPARAM wParm, LPARAM Lparam);//加入固定群组请求返回
	DECLARE_MESSAGE_MAP()

public:
	void InitContactList();		//初始化联系人列表
	void InitGroupList();		//初始化群组列表
	void PublishSelfState(int iState);	//发布自己状态
	void UpdateContactTree(int _state, const CString& szAcc);	//更新联系人列表状态
	int GetStatusImageID(const std::string& uri);	//获取联系人状态图片ID
	int GetStatusImageID(int state);				//获取联系人状态图片ID

	void AddImage(CImageList& imageList, UINT _id);
	CChatDlg* GetChatDlgByAccount(const CString& ucAcc);		//通过ucAcc获取聊天窗口
	void ClearTree(CTreeCtrl& tree, const HTREEITEM& hItem);	//清空Tree节点
	void DelTreeNode(CTreeCtrl& tree, const HTREEITEM& hItem);	//删除Tree节点

	//辅助函数
private:
	BOOL GetCustomGrouplist_(std::vector<UCCustomGroup>& list);//获取所有分组列表
	BOOL GetAllContactlist_(std::vector<UCContact>& list);//获取所有联系人列表
	BOOL GetContactlistFromCustomGroup_(const UCCustomGroup* group, std::vector<UCContact>& list);//获取分组内所有联系人列表
	BOOL RefreshFixedGrouplist_(std::vector<UCFixedGroup>& list);//刷新固定群组列表
	BOOL RefreshContactList_(const UCFixedGroup* group, std::vector<UCContact>& list);//刷新固定群组内联系人列表

private:
	static void MemCopy(char* dest, const CString& str, size_t size);//拷贝string内存

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
