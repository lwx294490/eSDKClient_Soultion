// BaseDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "eSDKClientDemo.h"
#include "BaseDlg.h"
#include "CodeTools.h"
#include <sstream>


// CBaseDlg 对话框

IMPLEMENT_DYNAMIC(CBaseDlg, CDialog)

CBaseDlg::CBaseDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CBaseDlg::IDD, pParent)
	, m_szAccount(_T(""))
	, m_CBookConfDlg(NULL)
	, m_pCInputDlg(NULL)
	, m_pCRingDlg(NULL)
	, m_pCeSDKClientDemoDlg(NULL)
	, m_pUCSDKAbsProxy(NULL)
	, m_pUCContactMgrAbsProxy(NULL)
	, m_pUCGroupAbsProxy(NULL)
	, m_pUCVoIPAbsProxy(NULL)
	, m_pUCPublicAbsProxy(NULL)
{

}

CBaseDlg::~CBaseDlg()
{
}

void CBaseDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_PHOTO, m_stPhoto);
	DDX_Text(pDX, IDC_STATIC_ACCOUNT, m_szAccount);
	DDX_Control(pDX, IDC_COMBO_STATE, m_cmbState);
	DDX_Control(pDX, IDC_BUTTON_CONTACT, m_btnContact);
	DDX_Control(pDX, IDC_BUTTON_GROUP, m_btnGroup);
	DDX_Control(pDX, IDC_BUTTON_BOOKCONF, m_btnBookConf);
	DDX_Control(pDX, IDC_TREE_CONTACT, m_ContactList);
	DDX_Control(pDX, IDC_TREE_GROUP, m_GroupList);
}


BEGIN_MESSAGE_MAP(CBaseDlg, CDialog)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BUTTON_CONTACT, &CBaseDlg::OnBnClickedButtonContact)
	ON_BN_CLICKED(IDC_BUTTON_GROUP, &CBaseDlg::OnBnClickedButtonGroup)
	ON_BN_CLICKED(IDC_BUTTON_BOOKCONF, &CBaseDlg::OnBnClickedButtonBookconf)
	ON_CBN_SELCHANGE(IDC_COMBO_STATE, &CBaseDlg::OnCbnSelchangeComboState)
	ON_NOTIFY(NM_DBLCLK, IDC_TREE_CONTACT, &CBaseDlg::OnNMDblclkTreeContact)
	ON_NOTIFY(NM_RCLICK, IDC_TREE_CONTACT, &CBaseDlg::OnNMRClickTreeContact)
	ON_NOTIFY(NM_DBLCLK, IDC_TREE_GROUP, &CBaseDlg::OnNMDblclkTreeGroup)
	ON_NOTIFY(NM_RCLICK, IDC_TREE_GROUP, &CBaseDlg::OnNMRClickTreeGroup)
	ON_COMMAND_RANGE(ID_MENU_CONTACT_BEGIN, ID_MENU_CONTACT_END, &CBaseDlg::OnClickContactMenuItem)
	ON_MESSAGE(WM_SIGNIN_NOTIFY, &CBaseDlg::OnMsgLogin)
	ON_MESSAGE(WM_STATUS_CHANGED, &CBaseDlg::OnMsgStatus)
	ON_MESSAGE(WM_INPUT_STRING, &CBaseDlg::OnMsgInputString)
	ON_MESSAGE(WM_CHAT_CLOSEED, &CBaseDlg::OnMsgChatWinClosed)
	ON_MESSAGE(WM_AVSESSION_ADDED, &CBaseDlg::OnMsgAVSessAdded)
	ON_MESSAGE(WM_AVSESSION_CONNECTED, &CBaseDlg::OnMsgAVSessConnected)
	ON_MESSAGE(WM_AVSESSION_CLOSED, &CBaseDlg::OnMsgAVSessClosed)
	ON_MESSAGE(WM_RECV_IM, &CBaseDlg::OnMsgReceivedIM)
	ON_MESSAGE(WM_ACCEPT_CALL, &CBaseDlg::OnMsgAcceptCall)
	ON_MESSAGE(WM_REJECT_CALL, &CBaseDlg::OnMsgRejectCall)
	ON_MESSAGE(WM_FORWARD_CALL, &CBaseDlg::OnMsgForwardCall)
	ON_MESSAGE(WM_CONF_STATUS_CHANGE, &CBaseDlg::OnMsgConfStatusChg)
	ON_MESSAGE(WM_CONF_ALLOW_SPEAK, &CBaseDlg::OnMsgConfAllowSpk)
	ON_MESSAGE(WM_CONF_FORBID_SPEAK, &CBaseDlg::OnMsgConfForbidSpk)
	ON_MESSAGE(WM_CONF_CUR_SPEAKER, &CBaseDlg::OnMsgConfCurSpker)
	ON_MESSAGE(WM_IM_SESS_REMOVE, &CBaseDlg::OnMsgIMSessRemove)
	ON_MESSAGE(WM_JOIN_CONFERENCE, &CBaseDlg::OnMsgJoinConference)
	ON_MESSAGE(WM_GROUP_INVITATION, &CBaseDlg::OnMsgGroupInvitation)
	ON_MESSAGE(WM_GROUP_INVITATIONRES, &CBaseDlg::OnMsgGroupInvitationRes)
	ON_MESSAGE(WM_GROUP_MEMBER_CHANGED, &CBaseDlg::OnMsgGroupMemberChanged)
	ON_MESSAGE(WM_GROUP_LEAVE_FIXED, &CBaseDlg::OnMsgGroupLeaveFixed)
	ON_MESSAGE(WM_GROUP_JOIN_FIXED_REQ, &CBaseDlg::OnMsgGroupJoinFixedReq)
	ON_MESSAGE(WM_GROUP_JOIN_FIXED_RSP, &CBaseDlg::OnMsgGroupJoinFixedRsp)
END_MESSAGE_MAP()

BOOL CBaseDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	CRect rect;
	::GetWindowRect(::GetDesktopWindow(),&rect);
	CRect temp;
	GetWindowRect(&temp);
	CPoint point;
	point.x = rect.Width()-temp.Width()-20;
	point.y = 20;
	CRect t_rect(point,temp.Size());
	MoveWindow(t_rect);

	//list:Offline, Online, Hide, Busy, Leave, Nodis
	m_cmbState.ResetContent();
	m_cmbState.InsertString(0,_T("Nodis"));
	m_cmbState.InsertString(0,_T("Leave"));
	m_cmbState.InsertString(0,_T("Busy"));
	m_cmbState.InsertString(0,_T("Hide"));
	m_cmbState.InsertString(0,_T("Online"));
	m_cmbState.InsertString(0,_T("Offline"));	
	m_cmbState.SetCurSel(1);

	// 状态图片列表
	m_lstImage.Create(WIDTH, HEIGHT, ILC_COLORDDB, IMGLIST_SIZE, 1);
	AddImage(m_lstImage, IDB_BITMAP_FOLD);			//0
	AddImage(m_lstImage, IDB_BITMAP_UNFOLD);		//1
	AddImage(m_lstImage, IDB_BITMAP_BUSY);			//2
	AddImage(m_lstImage, IDB_BITMAP_LEAVE);			//3
	AddImage(m_lstImage, IDB_BITMAP_NODISTURB);		//4
	AddImage(m_lstImage, IDB_BITMAP_OFFLINE);		//5
	AddImage(m_lstImage, IDB_BITMAP_ONLINE);		//6
	AddImage(m_lstImage, IDB_BITMAP_GROUP);			//7
	m_ContactList.SetImageList(&m_lstImage, LVSIL_NORMAL);
	m_GroupList.SetImageList(&m_lstImage, LVSIL_NORMAL);

	m_ContactList.ShowWindow(TRUE);
	m_GroupList.ShowWindow(FALSE);
	m_btnContact.EnableWindow(FALSE);
	m_btnGroup.EnableWindow(TRUE);

	//获取UC实例指针
	m_pUCSDKAbsProxy = UCSDKAbsProxy::GetInstance();
	m_pUCContactMgrAbsProxy = UCContactMgrAbsProxy::GetInstance();
	m_pUCGroupAbsProxy = UCGroupAbsProxy::GetInstance();
	m_pUCVoIPAbsProxy = UCVoIPAbsProxy::GetInstance();
	m_pUCPublicAbsProxy = UCPublicAbsProxy::GetInstance();

	return TRUE;
}

BOOL CBaseDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
	if(pMsg->message == WM_KEYDOWN)
	{
		switch(pMsg->wParam)
		{
		case VK_RETURN:
			return TRUE;
		case VK_ESCAPE:
			return TRUE;
		}
	}

	return CDialog::PreTranslateMessage(pMsg);
}

// CBaseDlg 消息处理程序

void CBaseDlg::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (m_pCeSDKClientDemoDlg && m_pCeSDKClientDemoDlg->GetSafeHwnd())
	{
		m_pCeSDKClientDemoDlg->PostMessage(WM_BASE_CLOSE);
		m_pCeSDKClientDemoDlg = NULL;
	}	

	if (m_pCInputDlg && m_pCInputDlg->GetSafeHwnd())
		m_pCInputDlg->PostMessage(WM_CLOSE);
	if (m_pCInputDlg)
		delete m_pCInputDlg;
	m_pCInputDlg = NULL;

	if (m_pCRingDlg && m_pCRingDlg->GetSafeHwnd())
		m_pCRingDlg->PostMessage(WM_CLOSE);
	if (m_pCRingDlg)
		delete m_pCRingDlg;
	m_pCRingDlg = NULL;

	if (m_CBookConfDlg.GetSafeHwnd())
		m_CBookConfDlg.DestroyWindow();

	std::map<std::string, CChatDlg*>::iterator itor = m_ChatDlgList.begin();
	for (; m_ChatDlgList.end() != itor; itor++)
	{
		CChatDlg*& pChatDlg = itor->second;
		if (pChatDlg->GetSafeHwnd())
			pChatDlg->PostMessage(WM_CLOSE);
		delete pChatDlg;
	}
	m_ChatDlgList.clear();

	m_pUCSDKAbsProxy = NULL;
	m_pUCContactMgrAbsProxy = NULL;
	m_pUCGroupAbsProxy = NULL;
	m_pUCVoIPAbsProxy = NULL;
	m_pUCPublicAbsProxy = NULL;

	CDialog::OnClose();
}

void CBaseDlg::OnBnClickedButtonContact()
{
	// TODO: 在此添加控件通知处理程序代码
	m_ContactList.ShowWindow(TRUE);
	m_GroupList.ShowWindow(FALSE);

	m_btnContact.EnableWindow(FALSE);
	m_btnGroup.EnableWindow(TRUE);
	UpdateData(FALSE);
}

void CBaseDlg::OnBnClickedButtonGroup()
{
	// TODO: 在此添加控件通知处理程序代码
	m_ContactList.ShowWindow(FALSE);
	m_GroupList.ShowWindow(TRUE);

	m_btnContact.EnableWindow(TRUE);
	m_btnGroup.EnableWindow(FALSE);
	UpdateData(FALSE);
}

void CBaseDlg::OnBnClickedButtonBookconf()
{
	// TODO: 在此添加控件通知处理程序代码
	if (m_CBookConfDlg.GetSafeHwnd())
	{
		m_CBookConfDlg.DestroyWindow();
	}
	m_CBookConfDlg.Create(CBookConfDlg::IDD, CWnd::GetDesktopWindow());
	m_CBookConfDlg.ShowWindow(SW_SHOWNORMAL);
	m_CBookConfDlg.BringWindowToTop();
	m_CBookConfDlg.m_pCBaseDlg = this;
}

void CBaseDlg::OnCbnSelchangeComboState()
{
	// TODO: 在此添加控件通知处理程序代码
	int state = m_cmbState.GetCurSel();
	
	PublishSelfState(state);
}

void CBaseDlg::OnNMDblclkTreeContact(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;

	CPoint pt;
	::GetCursorPos(&pt);
	m_ContactList.ScreenToClient(&pt);

	UINT uFlag = 0;
	HTREEITEM hSelectedItem = m_ContactList.HitTest(pt,&uFlag);
	if (NULL == hSelectedItem || !(TVHT_ONITEM & uFlag))
	{
		return;
	}

	m_ContactList.SelectItem(hSelectedItem);
	if (m_ContactList.GetParentItem(hSelectedItem) == NULL)
	{
		int iImageID = -1;
		int iSelectImageID = -1;
		m_ContactList.GetItemImage(hSelectedItem,iImageID,iSelectImageID);
		if(BITMAP_FOLD_ImgID == iImageID)
		{
			m_ContactList.SetItemImage(hSelectedItem,BITMAP_UNFOLD_ImgID,BITMAP_UNFOLD_ImgID);	
		}
		else
		{
			m_ContactList.SetItemImage(hSelectedItem,BITMAP_FOLD_ImgID,BITMAP_FOLD_ImgID);
		}
	}
}

void CBaseDlg::OnNMRClickTreeContact(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;

	CPoint pt, pmenu;
	::GetCursorPos(&pt);
	::GetCursorPos(&pmenu);
	m_ContactList.ScreenToClient(&pt);

	UINT uFlag = 0;
	HTREEITEM hSelectedItem = m_ContactList.HitTest(pt,&uFlag);
	if (NULL == hSelectedItem || !(TVHT_ONITEM & uFlag))
	{
		return;
	}

	m_ContactList.SelectItem(hSelectedItem);

	if (m_ContactList.GetParentItem(hSelectedItem) != NULL)
	{
		//联系人节点
		CMenu menu;
		menu.CreatePopupMenu();
		menu.AppendMenu(MF_STRING, ID_MENU_IM, _T("InstantMsg"));
		menu.AppendMenu(MF_STRING, ID_MENU_CALL, _T("Call"));
		menu.AppendMenu(MF_STRING, ID_MENU_VIDEOCALL, _T("VideoCall"));
		menu.AppendMenu(MF_STRING, ID_MENU_RM_CONTACT, _T("RemoveContact"));
		menu.AppendMenu(MF_STRING, ID_MENU_MOVE_CONTACT, _T("MoveContact"));		
		menu.TrackPopupMenu(0, pmenu.x, pmenu.y, this);
	}
	else
	{
		//组节点
		CMenu menu;
		menu.CreatePopupMenu();
		menu.AppendMenu(MF_STRING, ID_MENU_ADD_GROUP, _T("AddGroup"));
		menu.AppendMenu(MF_STRING, ID_MENU_RM_GROUP, _T("RemoveGroup"));
		menu.AppendMenu(MF_STRING, ID_MENU_ADD_CONTACT, _T("AddContact"));		
		menu.TrackPopupMenu(0, pmenu.x, pmenu.y, this);
	}
}

void CBaseDlg::OnNMDblclkTreeGroup(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;

	CPoint pt;
	::GetCursorPos(&pt);
	m_GroupList.ScreenToClient(&pt);

	UINT uFlag = 0;
	HTREEITEM hSelectedItem = m_GroupList.HitTest(pt,&uFlag);
	if (NULL == hSelectedItem || !(TVHT_ONITEM & uFlag))
	{
		return;
	}

	m_GroupList.SelectItem(hSelectedItem);
}

void CBaseDlg::OnNMRClickTreeGroup(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;

	CPoint pt, pmenu;
	::GetCursorPos(&pt);
	::GetCursorPos(&pmenu);
	m_GroupList.ScreenToClient(&pt);

	UINT uFlag = 0;
	HTREEITEM hSelectedItem = m_GroupList.HitTest(pt,&uFlag);
	if (NULL == hSelectedItem || !(TVHT_ONITEM & uFlag))
	{
		//组节点
		CMenu menu;
		menu.CreatePopupMenu();
		menu.AppendMenu(MF_STRING, ID_MENU_ADD_FIXED, _T("AddFixedGroup"));
		menu.TrackPopupMenu(0, pmenu.x, pmenu.y, this);
		return;
	}

	m_GroupList.SelectItem(hSelectedItem);

	if (m_GroupList.GetParentItem(hSelectedItem) != NULL)
	{
		//联系人节点
		CMenu menu;
		menu.CreatePopupMenu();
		menu.AppendMenu(MF_STRING, ID_MENU_RM_FIXED_CONTACT, _T("RemoveFixedContact"));	
		menu.TrackPopupMenu(0, pmenu.x, pmenu.y, this);
	}
	else
	{
		//组节点
		CMenu menu;
		menu.CreatePopupMenu();
		menu.AppendMenu(MF_STRING, ID_MENU_ADD_FIXED, _T("AddFixedGroup"));
		menu.AppendMenu(MF_STRING, ID_MENU_DISMISS_FIXED, _T("DismissFixedGroup"));
		menu.AppendMenu(MF_STRING, ID_MENU_ADD_FIXED_CONTACT, _T("AddFixedContact"));
		menu.AppendMenu(MF_STRING, ID_MENU_RENAME_FIXED, _T("ReName"));
		menu.TrackPopupMenu(0, pmenu.x, pmenu.y, this);
	}
}

void CBaseDlg::OnClickContactMenuItem(UINT uID)
{
	switch(uID)
	{
	case ID_MENU_IM:	//即时消息
		{
			HTREEITEM selectedItem = m_ContactList.GetSelectedItem();
			PTREEITEMDATA pTreeItemData = (PTREEITEMDATA)m_ContactList.GetItemData(selectedItem);
			if (NULL == pTreeItemData)
			{
				MessageBox(_T("GetItemData failed."));
				return;
			}

			CString szAcc = pTreeItemData->ucAcc_;
			if (szAcc.IsEmpty())
			{
				MessageBox(_T("Account is Empty."));
				return;
			}

			CChatDlg* pCChatDlg = GetChatDlgByAccount(szAcc);
			if (!pCChatDlg)
			{
				pCChatDlg = new CChatDlg;
				pCChatDlg->Create(CChatDlg::IDD, CWnd::GetDesktopWindow());
				pCChatDlg->SetWindowText(szAcc);
				pCChatDlg->m_szAccount = m_szAccount;
				pCChatDlg->m_szCompere = _T("");
				pCChatDlg->m_szTargetAcc = szAcc;				
				pCChatDlg->m_pCBaseDlg = this;
				pCChatDlg->m_convId.clear();

				pCChatDlg->m_btnCall.EnableWindow(TRUE);
				pCChatDlg->m_btnVideoCall.EnableWindow(TRUE);
				pCChatDlg->ShowWindow(TRUE);

				std::string convId = pCChatDlg->CreateConvID();
				m_ChatDlgList.insert(std::make_pair(convId, pCChatDlg));
			}

			pCChatDlg->BringWindowToTop();
		}
		break;
	case ID_MENU_CALL:	//语音呼叫
		{
			HTREEITEM selectedItem = m_ContactList.GetSelectedItem();
			PTREEITEMDATA pTreeItemData = (PTREEITEMDATA)m_ContactList.GetItemData(selectedItem);
			if (NULL == pTreeItemData)
			{
				MessageBox(_T("GetItemData failed."));
				return;
			}

			CString szAcc = pTreeItemData->ucAcc_;
			if (szAcc.IsEmpty())
			{
				MessageBox(_T("Account is Empty."));
				return;
			}

			CChatDlg* pCChatDlg = GetChatDlgByAccount(szAcc);
			if (!pCChatDlg)
			{
				pCChatDlg = new CChatDlg;
				pCChatDlg->Create(CChatDlg::IDD, CWnd::GetDesktopWindow());
				pCChatDlg->SetWindowText(szAcc);
				pCChatDlg->m_szAccount = m_szAccount;
				pCChatDlg->m_szCompere = _T("");
				pCChatDlg->m_szTargetAcc = szAcc;				
				pCChatDlg->m_pCBaseDlg = this;
				pCChatDlg->m_convId.clear();

				pCChatDlg->m_btnHangup.EnableWindow(TRUE);
				pCChatDlg->ShowWindow(TRUE);

				std::string convId = pCChatDlg->CreateConvID();
				m_ChatDlgList.insert(std::make_pair(convId, pCChatDlg));
			}

			pCChatDlg->BringWindowToTop();
			pCChatDlg->OnBnClickedButtonCall();
		}
		break;
	case ID_MENU_VIDEOCALL:	//视频呼叫
		{
			HTREEITEM selectedItem = m_ContactList.GetSelectedItem();
			PTREEITEMDATA pTreeItemData = (PTREEITEMDATA)m_ContactList.GetItemData(selectedItem);
			if (NULL == pTreeItemData)
			{
				MessageBox(_T("GetItemData failed."));
				return;
			}

			CString szAcc = pTreeItemData->ucAcc_;
			if (szAcc.IsEmpty())
			{
				MessageBox(_T("Account is Empty."));
				return;
			}

			CChatDlg* pCChatDlg = GetChatDlgByAccount(szAcc);
			if (!pCChatDlg)
			{
				pCChatDlg = new CChatDlg;
				pCChatDlg->Create(CChatDlg::IDD, CWnd::GetDesktopWindow());
				pCChatDlg->SetWindowText(szAcc);
				pCChatDlg->m_szAccount = m_szAccount;
				pCChatDlg->m_szCompere = _T("");
				pCChatDlg->m_szTargetAcc = szAcc;				
				pCChatDlg->m_pCBaseDlg = this;
				pCChatDlg->m_convId.clear();

				pCChatDlg->m_btnHangup.EnableWindow(TRUE);
				pCChatDlg->ShowWindow(TRUE);

				std::string convId = pCChatDlg->CreateConvID();
				m_ChatDlgList.insert(std::make_pair(convId, pCChatDlg));
			}

			pCChatDlg->BringWindowToTop();
			pCChatDlg->OnBnClickedButtonVideocall();
		}
		break;
	case ID_MENU_ADD_GROUP:	//增加联系人分组
		{
			if (!m_pCInputDlg)
			{
				m_pCInputDlg = new CInputDlg(this);
				m_pCInputDlg->Create(CInputDlg::IDD, this);
			}
			//m_pCInputDlg->m_szRect = "right_down";
			m_pCInputDlg->Init();
			m_pCInputDlg->m_szFlag = _T("AddGroup");
			m_pCInputDlg->ShowWindow(TRUE);
		}
		break;
	case ID_MENU_RM_GROUP:	//删除联系人分组
		{
			HTREEITEM selectedItem = m_ContactList.GetSelectedItem();
			//如果联系人分组不为空，则不能删除
			HTREEITEM item = m_ContactList.GetChildItem(selectedItem);
			if (item)
			{
				MessageBox(_T("Custom group is not empty. Please remove contact in this group first."));
				return;
			}

			PTREEITEMDATA pTreeItemData = (PTREEITEMDATA)m_ContactList.GetItemData(selectedItem);
			if (NULL == pTreeItemData)
			{
				MessageBox(_T("GetItemData failed."));
				return;
			}

			//删除联系人分组
			UCSDKCustomGroup group;
			group.id_ = pTreeItemData->id_;
			group.name_ = pTreeItemData->name_;
			int iRet = m_pUCGroupAbsProxy->RemoveCustomGroup(group);
			if (0 != iRet)
			{
				MessageBox(_T("RemoveCustomGroup failed."));
				return;
			}

			//删除节点
			DelTreeNode(m_ContactList, selectedItem);		
		}
		break;
	case ID_MENU_ADD_CONTACT:	//联系人分组中添加联系人
		{
			HTREEITEM selectedItem = m_ContactList.GetSelectedItem();
			PTREEITEMDATA pTreeItemData = (PTREEITEMDATA)m_ContactList.GetItemData(selectedItem);
			if (NULL == pTreeItemData)
			{
				MessageBox(_T("GetItemData failed."));
				return;
			}

			if (!m_pCInputDlg)
			{
				m_pCInputDlg = new CInputDlg(this);
				m_pCInputDlg->Create(CInputDlg::IDD, this);
			}
			//m_pCInputDlg->m_szRect = "right_down";
			m_pCInputDlg->Init();
			m_pCInputDlg->m_pTreeItemData = pTreeItemData;
			m_pCInputDlg->m_szFlag = _T("AddContact");
			m_pCInputDlg->ShowWindow(TRUE);
		}
		break;
	case ID_MENU_RM_CONTACT:	//联系人分组中删除联系人
		{
			HTREEITEM selectedItem = m_ContactList.GetSelectedItem();
			PTREEITEMDATA pTreeItemData = (PTREEITEMDATA)m_ContactList.GetItemData(selectedItem);
			if (NULL == pTreeItemData)
			{
				MessageBox(_T("GetItemData failed."));
				return;
			}

			if (pTreeItemData->id_.IsEmpty())
			{
				MessageBox(_T("Contact's Id is empty."));
				return;
			}

			//1111111111111111111111  "111111"和"22222"两种方法都可以正常删除联系人
			//删除联系人
			/*int iRet = m_pUCContactMgrAbsProxy->RemoveContactById(pTreeItemData->id_.GetBuffer());
			if (0 != iRet)
			{
				MessageBox(_T("Remove contact by id failed."));
				return;
			}*/

			
			//222222222222222222222
			HTREEITEM parentItem = m_GroupList.GetParentItem(selectedItem);
			PTREEITEMDATA pDataGroup = (PTREEITEMDATA)m_GroupList.GetItemData(parentItem);
			if (NULL == pDataGroup)
			{
				MessageBox(_T("GetItemData failed."));
				return;
			}

			UCSDKCustomGroup group;
			UCSDKContact contact;
			group.id_ = pDataGroup->id_;
			contact.uri_ = pTreeItemData->uri_;
			int iRet = m_pUCGroupAbsProxy->RemoveContact(group,contact);
			if (0 != iRet)
			{
				MessageBox(_T("RemoveContact failed."));
				return;
			}

			//删除节点
			DelTreeNode(m_ContactList, selectedItem);
		}
		break;
	case ID_MENU_MOVE_CONTACT:	//移动联系人到XXX分组
		{
			HTREEITEM selectedItem = m_ContactList.GetSelectedItem();
			PTREEITEMDATA pTreeItemData = (PTREEITEMDATA)m_ContactList.GetItemData(selectedItem);
			if (NULL == pTreeItemData)
			{
				MessageBox(_T("GetItemData failed."));
				return;
			}

			if (!m_pCInputDlg)
			{
				m_pCInputDlg = new CInputDlg(this);
				m_pCInputDlg->Create(CInputDlg::IDD, this);
			}
			//m_pCInputDlg->m_szRect = "right_down";
			m_pCInputDlg->m_pTreeItemData = pTreeItemData;
			m_pCInputDlg->m_szFlag = _T("MoveContact");
			m_pCInputDlg->ShowWindow(TRUE);
		}
		break;
		//----------------------------------------------
	case ID_MENU_RM_FIXED_CONTACT:	//固定群组删除联系人
		{
			HTREEITEM selectedItem = m_GroupList.GetSelectedItem();
			HTREEITEM parentItem = m_GroupList.GetParentItem(selectedItem);

			PTREEITEMDATA pDataContact = (PTREEITEMDATA)m_GroupList.GetItemData(selectedItem);
			if (NULL == pDataContact)
			{
				MessageBox(_T("GetItemData failed."));
				return;
			}
			PTREEITEMDATA pDataGroup = (PTREEITEMDATA)m_GroupList.GetItemData(parentItem);
			if (NULL == pDataGroup)
			{
				MessageBox(_T("GetItemData failed."));
				return;
			}

			UCSDKFixedGroup group;
			UCSDKContact contact;
			group.id_ = pDataGroup->id_.GetBuffer();
			contact.uri_ = pDataContact->uri_.GetBuffer();

			//删除联系人
			int iRet = m_pUCGroupAbsProxy->RemoveContact(group, contact);
			if (0 != iRet)
			{
				MessageBox(_T("RemoveContactFromFixedGroup failed."));
				return;
			}

			//删除节点
			DelTreeNode(m_GroupList, selectedItem);
		}
		break;
	case ID_MENU_ADD_FIXED:		//增加固定群组
		{
			if (!m_pCInputDlg)
			{
				m_pCInputDlg = new CInputDlg(this);
				m_pCInputDlg->Create(CInputDlg::IDD, this);
			}
			//m_pCInputDlg->m_szRect = "right_down";
			m_pCInputDlg->Init();
			m_pCInputDlg->m_szFlag = _T("AddFixedGroup");
			m_pCInputDlg->ShowWindow(TRUE);
		}
		break;
	case ID_MENU_DISMISS_FIXED:	//解散固定群组
		{
			HTREEITEM selectedItem = m_GroupList.GetSelectedItem();
			PTREEITEMDATA pTreeItemData = (PTREEITEMDATA)m_GroupList.GetItemData(selectedItem);
			if (NULL == pTreeItemData)
			{
				MessageBox(_T("GetItemData failed."));
				return;
			}

			UCSDKFixedGroup group;
			group.id_ = pTreeItemData->id_.GetBuffer();

			//解散固定群组
			int iRet = m_pUCGroupAbsProxy->RemoveFixedGroup(group);
			if (0 != iRet)
			{
				MessageBox(_T("RemoveFixedGroup failed."));
				return;
			}

			//删除节点
			DelTreeNode(m_GroupList, selectedItem);
		}
		break;
	case ID_MENU_ADD_FIXED_CONTACT:	//固定群组增加联系人
		{
			HTREEITEM selectedItem = m_GroupList.GetSelectedItem();
			PTREEITEMDATA pTreeItemData = (PTREEITEMDATA)m_GroupList.GetItemData(selectedItem);
			if (NULL == pTreeItemData)
			{
				MessageBox(_T("GetItemData failed."));
				return;
			}

			if (!m_pCInputDlg)
			{
				m_pCInputDlg = new CInputDlg(this);
				m_pCInputDlg->Create(CInputDlg::IDD, this);
			}
			//m_pCInputDlg->m_szRect = "right_down";
			m_pCInputDlg->Init();
			m_pCInputDlg->m_pTreeItemData = pTreeItemData;
			m_pCInputDlg->m_szFlag = _T("AddFixedContact");
			m_pCInputDlg->ShowWindow(TRUE);
		}
		break;
	case ID_MENU_RENAME_FIXED:	//固定群组重命名
		{
			HTREEITEM selectedItem = m_GroupList.GetSelectedItem();
			PTREEITEMDATA pTreeItemData = (PTREEITEMDATA)m_GroupList.GetItemData(selectedItem);
			if (NULL == pTreeItemData)
			{
				MessageBox(_T("GetItemData failed."));
				return;
			}

			if (!m_pCInputDlg)
			{
				m_pCInputDlg = new CInputDlg(this);
				m_pCInputDlg->Create(CInputDlg::IDD, this);
			}
			//m_pCInputDlg->m_szRect = "right_down";
			m_pCInputDlg->Init();
			m_pCInputDlg->m_pTreeItemData = pTreeItemData;
			m_pCInputDlg->m_szFlag = _T("RenameToFixedGroup");
			m_pCInputDlg->ShowWindow(TRUE);
		}
		break;
	}
}

//登录鉴权回调
LRESULT CBaseDlg::OnMsgLogin(WPARAM wParm, LPARAM Lparam)
{
	int _state = (int)wParm;
	CString* pszReason = (CString*)Lparam;

	if (3 == _state)		//UCClient::Client_SignedIn登录成功
	{
		/* 这里在eSDKClientDemoDlg.cpp中的登录函数内已经实现，这里暂不操作。
		//MessageBox(_T("SignIn Success."),_T("Login"),MB_OK);
		InitContactList();
		InitGroupList();
		ShowWindow(FALSE);
		*/
	}
	else if (1 == _state)	//UCClient::Client_SignedFailed登录失败
	{
		if ("sipkickout" == *pszReason)	//被挤下线
		{
			MessageBox(_T("Sorry,Client have been Kicked Out."),_T("Login"),MB_OK);
			PostMessage(WM_CLOSE);
		}
		else if ("signout" == *pszReason)	//登出成功
		{
			/* 这里在eSDKClientDemoDlg.cpp中登出函数内已经实现，这里暂不操作
			//MessageBox(_T("SignedOut Success."),_T("Logout"),MB_OK);
			PostMessage(WM_CLOSE);
			*/
		}
		else if ("noip" == *pszReason)		//网络连接中断
		{
			MessageBox(_T("NetWork disconnect."),_T("Login"),MB_OK);
			//PostMessage(WM_CLOSE);
		}
		else if ("hasip" == *pszReason)		//网络已经连接
		{
			MessageBox(_T("NetWork connect."),_T("Login"),MB_OK);
			//PostMessage(WM_CLOSE);
		}
		else	//其他失败
		{
			MessageBox(_T("SignIn Failed."),_T("Login"),MB_OK);
			PostMessage(WM_CLOSE);
		}
	}
	else	//其他失败
	{
		MessageBox(_T("SignIn Failed."),_T("Login"),MB_OK);
		PostMessage(WM_CLOSE);
	}

	delete pszReason;

	return 0L;
}

//状态回调处理
LRESULT CBaseDlg::OnMsgStatus(WPARAM wParm, LPARAM Lparam)
{	
	int state = (int)wParm;
	CString* pszAcc = (CString*)Lparam;
	if (NULL == pszAcc)
		return -1L;

	UpdateContactTree(state, *pszAcc);

	delete pszAcc;
	return 0L;
}

LRESULT CBaseDlg::OnMsgInputString(WPARAM wParm, LPARAM Lparam)
{
	if (!Lparam)
		return -1L;

	InputInfo *pInputInfo = (InputInfo*)Lparam;

	//增加联系人分组
	if (_T("AddGroup") == pInputInfo->szFlag)
	{
		CString szGroupName = pInputInfo->szInput;
		UCSDKCustomGroup customGroup;
		customGroup.name_ = szGroupName.GetBuffer();
		int iRet = m_pUCGroupAbsProxy->AddCustomGroup(customGroup);
		if (0 != iRet)
		{
			MessageBox(_T("AddCustomGroup failed."));
			delete pInputInfo;
			return -1L;
		}

		//增加节点
		HTREEITEM itemgrproot_ = m_ContactList.InsertItem(szGroupName, BITMAP_UNFOLD_ImgID, BITMAP_UNFOLD_ImgID, NULL);
		PTREEITEMDATA pTreeItemData = new TREEITEMDATA;
		pTreeItemData->hItem = itemgrproot_;
		pTreeItemData->id_ = customGroup.id_.c_str();
		pTreeItemData->name_ = customGroup.name_.c_str();
		m_ContactList.SetItemData(itemgrproot_,(DWORD_PTR)pTreeItemData);
		m_ContactList.Expand(itemgrproot_,TVE_EXPAND);
	}
	//联系人分组中增加联系人
	else if (_T("AddContact") == pInputInfo->szFlag)
	{
		UCSDKCustomGroup group;
		UCSDKContact contact;
		group.id_ = pInputInfo->pTreeItemData->id_.GetBuffer();
		contact.ucAcc_ = pInputInfo->szInput.GetBuffer();
		int iRet = m_pUCGroupAbsProxy->AddContact(group, contact);
		if (iRet)
		{
			MessageBox(_T("AddContactToCustomGroup failed."));
			delete pInputInfo;
			return -1L;
		}

		//增加节点
		int iStatusImg = GetStatusImageID(contact.uri_);
		CString szName;
		szName.Format(_T("%s(%s)"), UTF8ToANSI(contact.name_.c_str()), contact.ucAcc_.c_str());
		HTREEITEM item = m_ContactList.InsertItem(szName, iStatusImg, iStatusImg, pInputInfo->pTreeItemData->hItem);
		PTREEITEMDATA pTreeItemData = new TREEITEMDATA;
		pTreeItemData->hItem = item;
		pTreeItemData->id_ = contact.id_.c_str();
		pTreeItemData->name_ = contact.name_.c_str();
		pTreeItemData->uri_ = contact.uri_.c_str();
		pTreeItemData->ucAcc_ = contact.ucAcc_.c_str();
		m_ContactList.SetItemData(item,(DWORD_PTR)pTreeItemData);
	}
	//移动联系人到XXX分组
	else if (_T("MoveContact") == pInputInfo->szFlag)
	{
		PTREEITEMDATA pData = NULL;
		HTREEITEM rootItem = m_ContactList.GetRootItem();
		while (rootItem)
		{
			pData = (PTREEITEMDATA)m_ContactList.GetItemData(rootItem);
			if (pData->name_ == ANSIToUTF8(pInputInfo->szInput))
			{
				break;
			}
			rootItem = m_ContactList.GetNextSiblingItem(rootItem);
			pData = NULL;
		}
		if (!pData)
		{
			MessageBox(_T("Can't found the group which you want to move."));
			delete pInputInfo;
			return -1L;
		}

		HTREEITEM contactItem =  pInputInfo->pTreeItemData->hItem;
		HTREEITEM groupItem = m_ContactList.GetParentItem(contactItem);
		PTREEITEMDATA pContactData = pInputInfo->pTreeItemData;
		PTREEITEMDATA pGroupData = (PTREEITEMDATA)m_ContactList.GetItemData(groupItem);

		UCSDKGroup oldgroup;
		UCSDKGroup newgroup;
		UCSDKContact contact;
		oldgroup.id_ = pGroupData->id_.GetBuffer();
		newgroup.id_ = pData->id_.GetBuffer();
		contact.uri_ = pContactData->uri_.GetBuffer();

		//移动分组，先从原分组中移除，在加入新分组
		bool bRet = m_pUCContactMgrAbsProxy->RemoveFromGroup(contact, oldgroup);
		if (!bRet)
		{
			MessageBox(_T("Remove from Group failed."));
			delete pInputInfo;
			return -1L;
		}
		bRet = m_pUCContactMgrAbsProxy->AddToGroup(contact, newgroup);
		if (!bRet)
		{
			MessageBox(_T("Add to Group failed."));
			delete pInputInfo;
			return -1L;
		}

		//增加节点
		int iStatusImg = GetStatusImageID(pContactData->uri_.GetBuffer());
		CString szName;
		szName.Format(_T("%s(%s)"), UTF8ToANSI(pContactData->name_), pContactData->ucAcc_);
		HTREEITEM item = m_ContactList.InsertItem(szName, iStatusImg, iStatusImg, pData->hItem);
		PTREEITEMDATA pTreeItemData = new TREEITEMDATA;
		pTreeItemData->hItem = item;
		pTreeItemData->id_ = pContactData->id_;
		pTreeItemData->name_ = pContactData->name_;
		pTreeItemData->uri_ = pContactData->uri_;
		pTreeItemData->ucAcc_ = pContactData->ucAcc_;
		m_ContactList.SetItemData(item,(DWORD_PTR)pTreeItemData);
		//删除节点
		DelTreeNode(m_ContactList, contactItem);
	}
	//增加固定群组
	else if (_T("AddFixedGroup") == pInputInfo->szFlag)
	{
		CString szGroupName = pInputInfo->szInput;

		UCSDKFixedGroup group;
		group.name_ = szGroupName.GetBuffer();
		int iRet = m_pUCGroupAbsProxy->AddFixedGroup(group);
		if (0 != iRet)
		{
			delete pInputInfo;
			MessageBox(_T("AddFixedGroup failed."));
			return -1L;
		}

		//增加节点
		HTREEITEM itemroot = m_GroupList.InsertItem(UTF8ToANSI(group.name_.c_str()), BITMAP_GROUP_ImgID, BITMAP_GROUP_ImgID, NULL);
		PTREEITEMDATA pTreeItemData = new TREEITEMDATA;
		pTreeItemData->hItem = itemroot;
		pTreeItemData->id_ = group.id_.c_str();
		pTreeItemData->name_ = group.name_.c_str();
		pTreeItemData->uri_ = group.uri_.c_str();
		m_GroupList.SetItemData(itemroot, (DWORD_PTR)pTreeItemData);

		//刷新群组
		std::vector<UCSDKContact> contactlist;
		iRet = m_pUCGroupAbsProxy->Refresh(group, contactlist);
		if (0 != iRet)
		{
			MessageBox(_T("Refresh failed."));
			delete pInputInfo;
			return -1L;
		}
		std::vector<UCSDKContact>::iterator it = contactlist.begin();
		for (; it != contactlist.end(); it++)
		{
			CString szName;
			szName.Format(_T("%s(%s)"), UTF8ToANSI(it->name_.c_str()), UTF8ToANSI(it->ucAcc_.c_str()));
			int iStateImg = GetStatusImageID(it->uri_);
			HTREEITEM item = m_GroupList.InsertItem(szName, iStateImg, iStateImg, itemroot);
			pTreeItemData = new TREEITEMDATA;
			pTreeItemData->hItem = item;
			pTreeItemData->id_ = it->id_.c_str();
			pTreeItemData->name_ = it->name_.c_str();
			pTreeItemData->uri_ = it->uri_.c_str();
			pTreeItemData->ucAcc_ = it->ucAcc_.c_str();
			m_GroupList.SetItemData(item, (DWORD_PTR)pTreeItemData);
		}
		m_GroupList.Expand(itemroot,TVE_EXPAND);
	}
	//固定群组增加联系人
	else if (_T("AddFixedContact") == pInputInfo->szFlag)
	{
		UCSDKFixedGroup group;
		UCSDKContact contact;
		group.id_ = pInputInfo->pTreeItemData->id_.GetBuffer();
		contact.ucAcc_ = pInputInfo->szInput.GetBuffer();

		int iRet = m_pUCGroupAbsProxy->AddContact(group, contact);
		if (iRet)
		{
			delete pInputInfo;
			MessageBox(_T("AddContact to fixedgroup failed."));
			return -1L;
		}

		//界面显示：这里暂不添加，等收到回调后添加
	}
	//固定群组重命名
	else if (_T("RenameToFixedGroup") == pInputInfo->szFlag)
	{
		UCSDKFixedGroup group;
		group.id_ = pInputInfo->pTreeItemData->id_.GetBuffer();

		int iRet = m_pUCGroupAbsProxy->Rename(group, pInputInfo->szInput.GetBuffer());
		if (iRet)
		{
			delete pInputInfo;
			MessageBox(_T("Rename fixedGroup failed."));
			return -1L;
		}

		//修改节点
		pInputInfo->pTreeItemData->name_ = ANSIToUTF8(pInputInfo->szInput.GetBuffer());
		m_GroupList.SetItemText(pInputInfo->pTreeItemData->hItem, pInputInfo->szInput);
	}

	delete pInputInfo;
	return 0L;
}

//聊天窗口关闭
LRESULT CBaseDlg::OnMsgChatWinClosed(WPARAM wParm, LPARAM Lparam)
{
	if (!Lparam)
		return -1L;

	std::string* convId = (std::string*)Lparam;

	std::map<std::string, CChatDlg*>::iterator itor = m_ChatDlgList.find(*convId);
	if (itor == m_ChatDlgList.end())
	{
		MessageBox(_T("Can't find the closed chat window."),_T("Error"),MB_OK);
		delete convId;
		return -1L;
	}

	CChatDlg*& pCChatDlg = itor->second;
	delete pCChatDlg;
	pCChatDlg = NULL;
	m_ChatDlgList.erase(itor);

	delete convId;
	return 0L;
}

LRESULT CBaseDlg::OnMsgAVSessAdded(WPARAM wParm, LPARAM Lparam)
{
	if (!Lparam)
		return -1L;

	AVSessAddedInfo* pAVAdd = (AVSessAddedInfo*)Lparam;

	UCSDKContact member;
	m_pUCContactMgrAbsProxy->GetContactByUri(member, pAVAdd->avParam.caller_);
	pAVAdd->avParam.caller_ = member.ucAcc_;

	if (!m_pCRingDlg)
	{
		m_pCRingDlg = new CRingDlg(this);
		m_pCRingDlg->Create(CRingDlg::IDD, this);
	}

	m_pCRingDlg->Init();
	m_pCRingDlg->m_pAVAdd = pAVAdd;
	m_pCRingDlg->SetWindowText(pAVAdd->avParam.caller_.c_str());
	m_pCRingDlg->BringWindowToTop();

	//video
	if (pAVAdd->avParam.isvideo_)
	{
		m_pCRingDlg->m_stVideo.ShowWindow(TRUE);
	}

	//发布忙碌状态
	PublishSelfState(3);

	m_pCRingDlg->UpdateData(FALSE);
	m_pCRingDlg->ShowWindow(TRUE);

	return 0L;
}

LRESULT CBaseDlg::OnMsgAVSessConnected(WPARAM wParm, LPARAM Lparam)
{
	if (!Lparam)
		return -1L;

	CString* pszConvId = (CString*)Lparam;

	std::string convId = (*pszConvId).GetBuffer();
	std::map<std::string, CChatDlg*>::iterator it = m_ChatDlgList.find(convId);
	if (it == m_ChatDlgList.end())
	{
		MessageBox(_T("Can't found the chatdlg in av session connected."),_T("Error"),MB_OK);
		delete pszConvId;
		return -1L;
	}

	CChatDlg* pCChatDlg = it->second;
	pCChatDlg->m_btnHold.EnableWindow(TRUE);
	pCChatDlg->m_btnResume.EnableWindow(TRUE);
	pCChatDlg->m_btnAdd.EnableWindow(TRUE);
	pCChatDlg->m_btnHangup.EnableWindow(TRUE);
	pCChatDlg->m_btnCall.EnableWindow(FALSE);
	pCChatDlg->m_btnVideoCall.EnableWindow(FALSE);
	pCChatDlg->m_btnMicMute.EnableWindow(TRUE);
	pCChatDlg->m_btnMicUnMute.EnableWindow(FALSE);
	pCChatDlg->m_btnSpkMute.EnableWindow(TRUE);
	pCChatDlg->m_btnSpkUnMute.EnableWindow(FALSE);

	//conference
	if (!pCChatDlg->m_szCompere.IsEmpty())
	{
		if (m_szAccount != pCChatDlg->m_szCompere)
		{
			pCChatDlg->m_btnAdd.EnableWindow(FALSE);
		}
	}
	else
	{
		pCChatDlg->m_btnStartRecord.EnableWindow(TRUE);
		pCChatDlg->m_btnStopRecord.EnableWindow(FALSE);
	}

	delete pszConvId;
	return 0L;
}

LRESULT CBaseDlg::OnMsgAVSessClosed(WPARAM wParm, LPARAM Lparam)
{
	if (!Lparam)
		return -1L;

	//发布空闲状态
	PublishSelfState(1);

	CString* pszConvId = (CString*)Lparam;

	bool bNotOperator = false;
	if (m_pCRingDlg && m_pCRingDlg->GetSafeHwnd())
	{
		bNotOperator = true;
		m_pCRingDlg->m_bIsOperator = true;
		m_pCRingDlg->PostMessage(WM_CLOSE);
	}

	std::string convId = (*pszConvId).GetBuffer();
	std::map<std::string, CChatDlg*>::iterator it = m_ChatDlgList.find(convId);
	if (it == m_ChatDlgList.end())
	{
		if (!bNotOperator)
			MessageBox(_T("Can't found the chatdlg in av session closed."),_T("Error"),MB_OK);
		delete pszConvId;
		return -1L;
	}

	CChatDlg* pCChatDlg = it->second;
	pCChatDlg->m_btnHold.EnableWindow(FALSE);
	pCChatDlg->m_btnResume.EnableWindow(FALSE);
	pCChatDlg->m_btnAdd.EnableWindow(FALSE);
	pCChatDlg->m_btnHangup.EnableWindow(FALSE);
	pCChatDlg->m_btnCall.EnableWindow(TRUE);
	pCChatDlg->m_btnVideoCall.EnableWindow(TRUE);
	pCChatDlg->m_btnMicMute.EnableWindow(FALSE);
	pCChatDlg->m_btnMicUnMute.EnableWindow(FALSE);
	pCChatDlg->m_btnSpkMute.EnableWindow(FALSE);
	pCChatDlg->m_btnSpkUnMute.EnableWindow(FALSE);
	pCChatDlg->m_btnStartRecord.EnableWindow(FALSE);
	pCChatDlg->m_btnStopRecord.EnableWindow(FALSE);
	pCChatDlg->m_bIsVideo = FALSE;

	//conference
	if (!pCChatDlg->m_szCompere.IsEmpty())
	{
		pCChatDlg->m_btnVideoCall.EnableWindow(FALSE);

		for (int i=0; i<pCChatDlg->m_ConfMemList.GetItemCount(); i++)
		{
			CString szAcc = pCChatDlg->m_ConfMemList.GetItemText(i, 0);
			pCChatDlg->UpdateConfMemList(szAcc, -1);
		}		
		if (pCChatDlg->m_szCompere != m_szAccount)
		{
			pCChatDlg->m_btnCall.EnableWindow(FALSE);
		}
	}

	delete pszConvId;
	return 0L;
}

LRESULT CBaseDlg::OnMsgReceivedIM(WPARAM wParm, LPARAM Lparam)
{
	if (!Lparam)
		return -1L;

	IMMessageInfo* pRecvIM = (IMMessageInfo*)Lparam;

	UCSDKContact member;
	if (m_pUCContactMgrAbsProxy->GetContactByUri(member, pRecvIM->imMsg.origin))
	{
		MessageBox(_T("GetContactByUri failed."),_T("Failed"),MB_OK);
		delete pRecvIM;
		return -1L;
	}

	//conference IM temp group
	if (pRecvIM->propMap[Prop_ConvTempGroupUri] != "")
	{
		std::string convId = pRecvIM->propMap[Prop_ConvIdentifier];
		CChatDlg* pCChatDlg = NULL;
		std::map<std::string, CChatDlg*>::iterator it = m_ChatDlgList.find(convId);
		if (it == m_ChatDlgList.end())
		{
			pCChatDlg = new CChatDlg;
			pCChatDlg->Create(CChatDlg::IDD, CWnd::GetDesktopWindow());
			pCChatDlg->m_pCBaseDlg = this;
			pCChatDlg->m_szAccount = m_szAccount;
			pCChatDlg->m_szCompere = pRecvIM->memlist[0].c_str();
			pCChatDlg->m_szTargetAcc = pRecvIM->memlist[0].c_str();
			pCChatDlg->m_convId = convId;

			CString szWnd(pRecvIM->memlist[0].c_str());
			szWnd.Append(_T(" Conference"));
			pCChatDlg->SetWindowText(szWnd);
			pCChatDlg->m_btnCall.EnableWindow(TRUE);
			pCChatDlg->m_btnVideoCall.EnableWindow(FALSE);
			pCChatDlg->m_btnAdd.EnableWindow(FALSE);
			pCChatDlg->ShowWindow(TRUE);

			//add conference memlist
			pCChatDlg->AddConfCompere(pRecvIM->memlist[0].c_str(), -1);
			for (int i=1; i<(int)pRecvIM->memlist.size(); i++)
				pCChatDlg->AddConfMember(pRecvIM->memlist[i].c_str(), -1);

			m_ChatDlgList.insert(std::make_pair(convId, pCChatDlg));
		}
		else
		{
			pCChatDlg = it->second;
			for (int i=0; i<(int)pRecvIM->memlist.size(); i++)
				pCChatDlg->UpdateConfMember(pRecvIM->memlist[i].c_str(), -1);	
		}	

		pCChatDlg->BringWindowToTop();

		CString header(member.ucAcc_.c_str());
		header.Append(_T("  "));
		header.Append(pRecvIM->imMsg.rcv_time.c_str());
		CString body = pRecvIM->imMsg.content.c_str();
		pCChatDlg->RecvIMMsg(header, body);
	}
	//p2p IM
	else
	{
		std::string convId = pRecvIM->propMap[Prop_ConvIdentifier];
		CChatDlg* pCChatDlg = NULL;
		std::map<std::string, CChatDlg*>::iterator it = m_ChatDlgList.find(convId);
		if (it == m_ChatDlgList.end())
		{
			pCChatDlg = new CChatDlg;
			pCChatDlg->Create(CChatDlg::IDD, CWnd::GetDesktopWindow());
			pCChatDlg->m_pCBaseDlg = this;
			pCChatDlg->m_szAccount = m_szAccount;
			pCChatDlg->m_szCompere = _T("");
			pCChatDlg->m_szTargetAcc = member.ucAcc_.c_str();
			pCChatDlg->m_convId = convId;

			pCChatDlg->SetWindowText(member.ucAcc_.c_str());
			pCChatDlg->m_btnCall.EnableWindow(TRUE);
			pCChatDlg->m_btnVideoCall.EnableWindow(TRUE);
			pCChatDlg->ShowWindow(TRUE);

			m_ChatDlgList.insert(std::make_pair(convId, pCChatDlg));		
		}
		else
		{
			pCChatDlg = it->second;
		}

		pCChatDlg->BringWindowToTop();

		CString header(member.ucAcc_.c_str());
		header.Append(_T("  "));
		header.Append(pRecvIM->imMsg.rcv_time.c_str());
		CString body = pRecvIM->imMsg.content.c_str();
		pCChatDlg->RecvIMMsg(header, body);
	}

	delete pRecvIM;
	return 0L;
}

LRESULT CBaseDlg::OnMsgAcceptCall(WPARAM wParm, LPARAM Lparam)
{
	if (!Lparam)
		return -1L;

	AVSessAddedInfo* pAVAdd = (AVSessAddedInfo*)Lparam;

	//conference
	if ("" != pAVAdd->propMap[Prop_ConvConfIdentifier])
	{
		CString szAcc(pAVAdd->memlist[0].c_str());
		std::string convId = pAVAdd->propMap[Prop_ConvIdentifier];
		CChatDlg* pCChatDlg = NULL;

		std::map<std::string, CChatDlg*>::iterator it = m_ChatDlgList.find(convId);
		if (it == m_ChatDlgList.end())
		{
			pCChatDlg = new CChatDlg;
			pCChatDlg->Create(CChatDlg::IDD, CWnd::GetDesktopWindow());
			pCChatDlg->m_pCBaseDlg = this;
			pCChatDlg->m_szAccount = m_szAccount;
			pCChatDlg->m_szCompere = _T("");
			pCChatDlg->m_szTargetAcc = szAcc;
			pCChatDlg->m_convId = convId;
			pCChatDlg->m_bIsVideo = TRUE;

			pCChatDlg->SetWindowText(szAcc + _T(" Conference"));
			pCChatDlg->ShowWindow(TRUE);

			//add conference memlist
			pCChatDlg->AddConfCompere(pAVAdd->memlist[0].c_str(), Conf_Inviting);

			m_ChatDlgList.insert(std::make_pair(convId, pCChatDlg));
		}
		else
		{
			pCChatDlg = it->second;
		}

		for (int i=0; i<(int)pAVAdd->memlist.size(); i++)
			pCChatDlg->UpdateConfMember(pAVAdd->memlist[i].c_str(), Conf_Inviting);	

		pCChatDlg->m_btnCall.EnableWindow(FALSE);
		pCChatDlg->m_btnVideoCall.EnableWindow(FALSE);
		pCChatDlg->m_btnHangup.EnableWindow(FALSE);
		pCChatDlg->m_btnAdd.EnableWindow(FALSE);
		pCChatDlg->BringWindowToTop();

		if (UCMeetingAbsProxy::GetInstance()->AcceptMeeting(convId))
		{
			MessageBox(_T("Accept meeting failed."),_T("Error"),MB_OK);
		}
	}
	//voip
	else
	{
		CString szAcc(pAVAdd->memlist[0].c_str());
		std::string convId = pAVAdd->propMap[Prop_ConvIdentifier];
		CChatDlg* pCChatDlg = NULL;

		std::map<std::string, CChatDlg*>::iterator it = m_ChatDlgList.find(convId);
		if (it == m_ChatDlgList.end())
		{
			pCChatDlg = new CChatDlg;
			pCChatDlg->Create(CChatDlg::IDD, CWnd::GetDesktopWindow());
			pCChatDlg->m_pCBaseDlg = this;
			pCChatDlg->m_szAccount = m_szAccount;
			pCChatDlg->m_szCompere = _T("");
			pCChatDlg->m_szTargetAcc = szAcc;
			pCChatDlg->m_convId = convId;

			pCChatDlg->SetWindowText(szAcc);
			pCChatDlg->ShowWindow(TRUE);

			m_ChatDlgList.insert(std::make_pair(convId, pCChatDlg));
		}
		else
		{
			pCChatDlg = it->second;
		}

		pCChatDlg->m_btnCall.EnableWindow(FALSE);
		pCChatDlg->m_btnVideoCall.EnableWindow(FALSE);
		pCChatDlg->m_btnHangup.EnableWindow(FALSE);
		pCChatDlg->BringWindowToTop();

		int iIsVideo = pAVAdd->avParam.isvideo_?Call_Video:Call_Audio;
		STVideoWindow local;
		STVideoWindow remote;
		if (Call_Video == iIsVideo)
		{
			CRect rectLocat;
			pCChatDlg->m_stLocal.GetClientRect(&rectLocat);
			ClientToScreen(&rectLocat);
			CRect rectRemote;
			pCChatDlg->m_stRemote.GetClientRect(&rectRemote);
			ClientToScreen(&rectRemote);

			local.hWnd = (int)pCChatDlg->m_stLocal.GetSafeHwnd();
			local.height = rectLocat.Height();
			local.width = rectLocat.Width();
			local.top = rectLocat.top;
			local.left = rectLocat.left;

			remote.hWnd = (int)pCChatDlg->m_stRemote.GetSafeHwnd();
			remote.height = rectRemote.Height();
			remote.width = rectRemote.Width();
			remote.top = rectRemote.top;
			remote.left = rectRemote.left;
		}

		if (m_pUCVoIPAbsProxy->Accept(pCChatDlg->m_convId, iIsVideo, local, remote))
		{
			pCChatDlg->PostMessage(WM_CLOSE);
			MessageBox(_T("Accept call failed."),_T("Failed"),MB_OK);		
		}
	}

	delete pAVAdd;
	return 0L;
}

LRESULT CBaseDlg::OnMsgRejectCall(WPARAM wParm, LPARAM Lparam)
{
	if (!Lparam)
		return -1L;

	AVSessAddedInfo* pAVAdd = (AVSessAddedInfo*)Lparam;
	std::string convId = pAVAdd->propMap[Prop_ConvIdentifier];
	if (m_pUCVoIPAbsProxy->Reject(convId, pAVAdd->avParam.isvideo_?Call_Video:Call_Audio))
	{
		MessageBox(_T("Reject call failed."),_T("Failed"),MB_OK);
	}

	delete pAVAdd;
	return 0L;
}

LRESULT CBaseDlg::OnMsgForwardCall(WPARAM wParm, LPARAM Lparam)
{
	if (!Lparam)
		return -1L;

	AVSessAddedInfo* pAVAdd = (AVSessAddedInfo*)Lparam;
	std::string convId = pAVAdd->propMap[Prop_ConvIdentifier];
	if (m_pUCVoIPAbsProxy->Forward(convId, pAVAdd->forwardAcc))
	{
		MessageBox(_T("Forward call failed."),_T("Failed"),MB_OK);
	}

	delete pAVAdd;
	return 0L;
}

LRESULT CBaseDlg::OnMsgConfStatusChg(WPARAM wParm, LPARAM Lparam)
{
	if (!Lparam)
		return -1L;

	ConfMemChgInfo* pConfMemChgInfo = (ConfMemChgInfo*)Lparam;

	UCSDKContact member;
	if (m_pUCContactMgrAbsProxy->GetContactByUri(member, pConfMemChgInfo->memUri))
	{
		MessageBox(_T("GetContactByUri failed."),_T("Failed"),MB_OK);
		delete pConfMemChgInfo;
		return -1L;
	}

	std::string convId = pConfMemChgInfo->convId;
	std::map<std::string, CChatDlg*>::iterator it = m_ChatDlgList.find(convId);
	if (it == m_ChatDlgList.end())
	{
		MessageBox(_T("Can't found the chatdlg in conference status changed."),_T("Failed"),MB_OK);
		delete pConfMemChgInfo;
		return -1L;
	}

	CChatDlg*& pCChatDlg = it->second;
	pCChatDlg->UpdateConfMemList(member.ucAcc_.c_str(), pConfMemChgInfo->state);

	delete pConfMemChgInfo;
	return 0L;
}

LRESULT CBaseDlg::OnMsgConfAllowSpk(WPARAM wParm, LPARAM Lparam)
{
	if (!Lparam)
		return -1L;

	ConfMemSpkInfo* pConfMemSpkInfo = (ConfMemSpkInfo*)Lparam;

	std::string convId = pConfMemSpkInfo->convId;
	std::map<std::string, CChatDlg*>::iterator it = m_ChatDlgList.find(convId);
	if (it == m_ChatDlgList.end())
	{
		MessageBox(_T("Can't found the chatdlg in conference allow speak."),_T("Failed"),MB_OK);
		delete pConfMemSpkInfo;
		return -1L;
	}

	CChatDlg*& pCChatDlg = it->second;
	pCChatDlg->UpdateConfMemList(pConfMemSpkInfo->ucAcc.c_str(), pConfMemSpkInfo->state);

	delete pConfMemSpkInfo;
	return 0L;
}

LRESULT CBaseDlg::OnMsgConfForbidSpk(WPARAM wParm, LPARAM Lparam)
{
	if (!Lparam)
		return -1L;

	ConfMemSpkInfo* pConfMemSpkInfo = (ConfMemSpkInfo*)Lparam;

	std::string convId = pConfMemSpkInfo->convId;
	std::map<std::string, CChatDlg*>::iterator it = m_ChatDlgList.find(convId);
	if (it == m_ChatDlgList.end())
	{
		MessageBox(_T("Can't found the chatdlg in conference forbid speak."),_T("Failed"),MB_OK);
		delete pConfMemSpkInfo;
		return -1L;
	}

	CChatDlg*& pCChatDlg = it->second;
	pCChatDlg->UpdateConfMemList(pConfMemSpkInfo->ucAcc.c_str(), pConfMemSpkInfo->state);

	delete pConfMemSpkInfo;
	return 0L;
}

LRESULT CBaseDlg::OnMsgConfCurSpker(WPARAM wParm, LPARAM Lparam)
{
	if (!Lparam)
		return -1L;

	ConfMemSpkInfo* pConfMemSpkInfo = (ConfMemSpkInfo*)Lparam;

	std::string convId = pConfMemSpkInfo->convId;
	std::map<std::string, CChatDlg*>::iterator it = m_ChatDlgList.find(convId);
	if (it == m_ChatDlgList.end())
	{
		MessageBox(_T("Can't found the chatdlg in conference current speaker."),_T("Failed"),MB_OK);
		delete pConfMemSpkInfo;
		return -1L;
	}

	CChatDlg*& pCChatDlg = it->second;
	pCChatDlg->UpdateConfMemList(pConfMemSpkInfo->ucAcc.c_str(), pConfMemSpkInfo->state);

	delete pConfMemSpkInfo;
	return 0L;
}

LRESULT CBaseDlg::OnMsgIMSessRemove(WPARAM wParm, LPARAM Lparam)
{
	if (!Lparam)
		return -1L;

	CString* pszConvId = (CString*)Lparam;

	std::string convId = (*pszConvId).GetBuffer();
	std::map<std::string, CChatDlg*>::iterator it = m_ChatDlgList.find(convId);
	if (it == m_ChatDlgList.end())
	{
		delete pszConvId;
		return -1L;
	}

	CChatDlg*& pCChatDlg = it->second;
	pCChatDlg->PostMessage(WM_CLOSE);

	delete pszConvId;
	return 0L;
}

LRESULT CBaseDlg::OnMsgJoinConference(WPARAM wParm, LPARAM Lparam)
{
	if (!Lparam)
		return -1L;	

	JoinConfInfo* pJoinConfInfo = (JoinConfInfo*)Lparam;

	UCSDKContact member;
	if (m_pUCContactMgrAbsProxy->GetContactByUri(member, pJoinConfInfo->convener))
	{
		MessageBox(_T("GetContactByUri failed."),_T("Failed"),MB_OK);
		delete pJoinConfInfo;
		return -1L;
	}

	std::map<std::string, CChatDlg*>::iterator it = m_ChatDlgList.find(pJoinConfInfo->convId);
	if (it != m_ChatDlgList.end())
	{
		MessageBox(_T("The convId is exist in Join conference."),_T("Error"),MB_OK);
		delete pJoinConfInfo;
		return -1L;
	}

	CChatDlg* pCChatDlg = new CChatDlg;
	pCChatDlg->Create(CChatDlg::IDD, CWnd::GetDesktopWindow());
	CString szWndTxt(member.ucAcc_.c_str());
	szWndTxt.Append(_T(" Book Conference"));
	pCChatDlg->SetWindowText(szWndTxt);
	pCChatDlg->m_szAccount = m_szAccount;
	pCChatDlg->m_szCompere = _T("");
	pCChatDlg->m_szTargetAcc = member.ucAcc_.c_str();				
	pCChatDlg->m_pCBaseDlg = this;
	pCChatDlg->m_convId = pJoinConfInfo->convId;

	pCChatDlg->m_btnHangup.EnableWindow(TRUE);
	pCChatDlg->ShowWindow(TRUE);
	pCChatDlg->BringWindowToTop();

	pCChatDlg->AddConfCompere(member.ucAcc_.c_str(), -1);
	pCChatDlg->UpdateConfMember(m_szAccount, Conf_Inviting);

	m_ChatDlgList.insert(std::make_pair(pJoinConfInfo->convId, pCChatDlg));

	delete pJoinConfInfo;
	return 0L;
}

LRESULT CBaseDlg::OnMsgGroupInvitation(WPARAM wParm, LPARAM Lparam)
{
	if (!Lparam)
		return -1L;	

	FixedGroupInfo* pFixedGroupInfo = (FixedGroupInfo*)Lparam;

	CString szMsg("Invitation to the group: ");
	CString szTemp = UTF8ToANSI(pFixedGroupInfo->name_.c_str());
	szMsg.Append(szTemp);

	UCSDKFixedGroup group;
	group.id_ = pFixedGroupInfo->id_;
	group.groupno_ = pFixedGroupInfo->groupno_;
	group.name_ = pFixedGroupInfo->name_;

	int iRet = MessageBox(szMsg, "Invitation", MB_YESNO);
	if (IDYES == iRet)
	{
		int iRet = m_pUCGroupAbsProxy->AcceptInvitation(group);	//群主邀请你加入某固定群组，你同意
		if (0 != iRet)
		{
			MessageBox(_T("AcceptInvitation failed."));
			delete pFixedGroupInfo;
			return -1L;
		}

		//增加节点
		HTREEITEM itemroot = m_GroupList.InsertItem(UTF8ToANSI(pFixedGroupInfo->name_.c_str()), BITMAP_GROUP_ImgID, BITMAP_GROUP_ImgID, NULL);
		PTREEITEMDATA pTreeItemData = new TREEITEMDATA;
		pTreeItemData->hItem = itemroot;
		pTreeItemData->id_ = pFixedGroupInfo->id_.c_str();
		pTreeItemData->name_ = pFixedGroupInfo->name_.c_str();
		pTreeItemData->uri_ = pFixedGroupInfo->uri_.c_str();
		m_GroupList.SetItemData(itemroot, (DWORD_PTR)pTreeItemData);

		//刷新群组
		std::vector<UCSDKContact> contactlist;
		iRet = m_pUCGroupAbsProxy->Refresh(group, contactlist);
		if (0 != iRet)
		{
			MessageBox(_T("Refresh failed."));
			delete pFixedGroupInfo;
			return -1L;
		}

		std::vector<UCSDKContact>::iterator it = contactlist.begin();
		for (; it != contactlist.end(); it++)
		{
			CString szName;
			szName.Format(_T("%s(%s)"), UTF8ToANSI(it->name_.c_str()), UTF8ToANSI(it->ucAcc_.c_str()));
			int iStateImg = GetStatusImageID(it->uri_);
			HTREEITEM item = m_GroupList.InsertItem(szName, iStateImg, iStateImg, itemroot);
			pTreeItemData = new TREEITEMDATA;
			pTreeItemData->hItem = item;
			pTreeItemData->id_ = it->id_.c_str();
			pTreeItemData->name_ = it->name_.c_str();
			pTreeItemData->uri_ = it->uri_.c_str();
			pTreeItemData->ucAcc_ = it->ucAcc_.c_str();
			m_GroupList.SetItemData(item, (DWORD_PTR)pTreeItemData);
		}
		m_GroupList.Expand(itemroot,TVE_EXPAND);
	}
	else	//群主邀请你加入某固定群组，你拒绝
	{
		int iRet = m_pUCGroupAbsProxy->RejectInvitation(group);
		if (0 != iRet)
		{
			MessageBox(_T("RejectInvitation failed."));
		}
	}

	delete pFixedGroupInfo;
	return 0L;
}

LRESULT CBaseDlg::OnMsgGroupInvitationRes(WPARAM wParm, LPARAM Lparam)
{
	if (!Lparam)
		return -1L;	

	InvitationResInfo* pInvitationResInfo = (InvitationResInfo*)Lparam;

	CString szTemp = UTF8ToANSI(pInvitationResInfo->invName.c_str());
	if (1 == pInvitationResInfo->result)	//邀请某人加入固定群组，其同意
	{
		szTemp.Append(" accept to join the group.");
	}
	else	//邀请某人加入固定群组，其拒绝
	{
		szTemp.Append(" reject to join the group.");
	}
	
	MessageBox(szTemp);

	//更新节点
	if (1 == pInvitationResInfo->result)
	{
		/*这里暂不做更新*/
		////更新节点
		//HTREEITEM rootItem = m_GroupList.GetRootItem();
		//while (rootItem)
		//{
		//	PTREEITEMDATA pGroupData = (PTREEITEMDATA)m_GroupList.GetItemData(rootItem);
		//	CString szId = pInvitationResInfo->group.id_;
		//	if (pGroupData->id_ == szId)
		//	{
		//		HTREEITEM item = m_GroupList.GetChildItem(rootItem);
		//		PTREEITEMDATA pItemData = (PTREEITEMDATA)m_GroupList.GetItemData(item);
		//		CString szAcc = pInvitationResInfo->group.id_;
		//		if (pItemData->ucAcc_ == )
		//	}
		//}
	}
	else
	{
		/*
		//这里需要手动更新界面
		GroupMemberChangedInfo* pGroupMemberChangedInfo = new GroupMemberChangedInfo;
		pGroupMemberChangedInfo->type = 1;
		pGroupMemberChangedInfo->uri_ = ;//获取不到uri，只能暴力初始化固定群组了！！！
		PostMessage(WM_GROUP_MEMBER_CHANGED, 0, (LPARAM)pGroupMemberChangedInfo);
		*/

		InitGroupList();
	}	

	delete pInvitationResInfo;
	return 0L;
}

LRESULT CBaseDlg::OnMsgGroupMemberChanged(WPARAM wParm, LPARAM Lparam)
{
	if (!Lparam)
		return -1L;	

	GroupMemberChangedInfo* pGroupMemberChangedInfo = (GroupMemberChangedInfo*)Lparam;

	CString szTemp = UTF8ToANSI(pGroupMemberChangedInfo->name_.c_str());
	if (pGroupMemberChangedInfo->type == 0)	//add	固定群组增加成员
	{
		szTemp.Append(" Add to the fixed group: ");
	}
	else	// 固定群组成员删除
	{
		szTemp.Append(" leave from the fixed group: ");
	}
	szTemp.Append(UTF8ToANSI(pGroupMemberChangedInfo->group.name_.c_str()));

	//MessageBox(szTemp);


	if (pGroupMemberChangedInfo->type == 0)
	{
		//查找节点
		HTREEITEM rootItem = m_GroupList.GetRootItem();
		while (rootItem)
		{
			PTREEITEMDATA pGroupData = (PTREEITEMDATA)m_GroupList.GetItemData(rootItem);
			CString szId = pGroupMemberChangedInfo->group.id_.c_str();
			if (pGroupData->id_ == szId)
			{
				HTREEITEM item = m_GroupList.GetChildItem(rootItem);
				while (item)
				{
					PTREEITEMDATA pItemData = (PTREEITEMDATA)m_GroupList.GetItemData(item);
					CString szUri = pGroupMemberChangedInfo->uri_.c_str();
					if (pItemData->uri_ == szUri)
					{
						//找到了就直接返回
						delete pGroupMemberChangedInfo;
						return 0L;
					}
					item = m_GroupList.GetNextSiblingItem(item);
				}

				//没有找到
				break;
			}
			rootItem = m_GroupList.GetNextSiblingItem(rootItem);
		}

		if (NULL == rootItem)
		{
			MessageBox(_T("Not found the fixed group."));
			delete pGroupMemberChangedInfo;
			return -1L;
		}

		//增加节点
		int iStatusImg = GetStatusImageID(pGroupMemberChangedInfo->uri_);
		CString szName;
		szName.Format(_T("%s(%s)"), UTF8ToANSI(pGroupMemberChangedInfo->name_.c_str()), pGroupMemberChangedInfo->ucAcc_.c_str());
		HTREEITEM item = m_GroupList.InsertItem(szName, iStatusImg, iStatusImg, rootItem);
		PTREEITEMDATA pTreeItemData = new TREEITEMDATA;
		pTreeItemData->hItem = item;
		pTreeItemData->id_ = pGroupMemberChangedInfo->id_.c_str();
		pTreeItemData->name_ = pGroupMemberChangedInfo->name_.c_str();
		pTreeItemData->uri_ = pGroupMemberChangedInfo->uri_.c_str();
		pTreeItemData->ucAcc_ = pGroupMemberChangedInfo->ucAcc_.c_str();
		m_GroupList.SetItemData(item,(DWORD_PTR)pTreeItemData);
	}
	else
	{
		//查找节点
		HTREEITEM rootItem = m_GroupList.GetRootItem();
		while (rootItem)
		{
			PTREEITEMDATA pGroupData = (PTREEITEMDATA)m_GroupList.GetItemData(rootItem);
			CString szId = pGroupMemberChangedInfo->group.id_.c_str();
			if (pGroupData->id_ == szId)
			{
				HTREEITEM item = m_GroupList.GetChildItem(rootItem);
				while (item)
				{
					PTREEITEMDATA pItemData = (PTREEITEMDATA)m_GroupList.GetItemData(item);
					CString szUri = pGroupMemberChangedInfo->uri_.c_str();
					if (pItemData->uri_ == szUri)
					{
						//找到了就直接删除返回
						DelTreeNode(m_GroupList, item);
						delete pGroupMemberChangedInfo;
						return 0L;
					}
					item = m_GroupList.GetNextSiblingItem(item);
				}
				//没有找到
				break;
			}
			rootItem = m_GroupList.GetNextSiblingItem(rootItem);
		}
	}

	delete pGroupMemberChangedInfo;
	return 0L;
}

LRESULT CBaseDlg::OnMsgGroupLeaveFixed(WPARAM wParm, LPARAM Lparam)
{
	if (!Lparam)
		return -1L;	

	LeaveFromFixedGroupInfo* pLeaveFromFixedGroupInfo = (LeaveFromFixedGroupInfo*)Lparam;

	CString szTemp;
	if (pLeaveFromFixedGroupInfo->reason == 0)	//KickedFromFixedGroup	//被踢出固定群组
	{
		szTemp.Append("You have been kicked from the fixed group: ");
		szTemp.Append(pLeaveFromFixedGroupInfo->group.name_.c_str());
	}
	else if (pLeaveFromFixedGroupInfo->reason == 1)//FixedGroupDismissed	//固定群组解散
	{
		szTemp.Append("The fixed group: ");
		szTemp.Append(pLeaveFromFixedGroupInfo->group.name_.c_str());
		szTemp.Append(" have been dismissed.");
	}
	else
	{
		szTemp.Append("Leave from fixed group: ");
		szTemp.Append(pLeaveFromFixedGroupInfo->group.name_.c_str());
	}
	MessageBox(szTemp);

	//查找节点
	HTREEITEM rootItem = m_GroupList.GetRootItem();
	while (rootItem)
	{
		PTREEITEMDATA pGroupData = (PTREEITEMDATA)m_GroupList.GetItemData(rootItem);
		CString szId = pLeaveFromFixedGroupInfo->group.id_.c_str();
		if (pGroupData->id_ == szId)
		{
			//删除节点
			DelTreeNode(m_GroupList, rootItem);
			delete pLeaveFromFixedGroupInfo;
			return 0L;
		}
		rootItem = m_GroupList.GetNextSiblingItem(rootItem);
	}

	MessageBox(_T("Not found the fixed group which you leave from."));
	delete pLeaveFromFixedGroupInfo;
	return -1L;
}

LRESULT CBaseDlg::OnMsgGroupJoinFixedReq(WPARAM wParm, LPARAM Lparam)
{
	if (!Lparam)
		return -1L;	

	JoinFixedGroupReqInfo* pJoinFixedGroupReqInfo = (JoinFixedGroupReqInfo*)Lparam;

	UCSDKContact contact;
	m_pUCContactMgrAbsProxy->GetContactByUri(contact, pJoinFixedGroupReqInfo->uri);

	CString szTemp(UTF8ToANSI(contact.name_.c_str()));
	szTemp.Append(_T(" request to join the fixed group: "));
	szTemp.Append(UTF8ToANSI(pJoinFixedGroupReqInfo->group.name_.c_str()));

	UCSDKFixedGroup fixedgroup;
	fixedgroup.name_ = pJoinFixedGroupReqInfo->group.name_;
	fixedgroup.id_ = pJoinFixedGroupReqInfo->group.id_;
	fixedgroup.groupno_ = pJoinFixedGroupReqInfo->group.groupno_;
	fixedgroup.uri_ = pJoinFixedGroupReqInfo->group.uri_;

	int iSel = MessageBox(szTemp, _T(""), MB_YESNO);
	if (IDYES == iSel)
	{
		int iRet = m_pUCGroupAbsProxy->AcceptJoinReq(fixedgroup,contact);	//同意某人加入固定群组申请
		if (iRet)
		{
			MessageBox(_T("AcceptJoinReq failed."));
		}

		//这里暂时不更新群组显示
		//***********
	}
	else	//拒绝某人加入固定群组申请
	{
		int iRet = m_pUCGroupAbsProxy->RejectJoinReq(fixedgroup,contact);
		if (iRet)
		{
			MessageBox(_T("RejectJoinReq failed."));
			delete pJoinFixedGroupReqInfo;
			return -1L;
		}

		//查找节点
		HTREEITEM rootItem = m_GroupList.GetRootItem();
		while (rootItem)
		{
			PTREEITEMDATA pGroupData = (PTREEITEMDATA)m_GroupList.GetItemData(rootItem);
			CString szId = pJoinFixedGroupReqInfo->group.id_.c_str();
			if (pGroupData->id_ == szId)
			{
				HTREEITEM item = m_GroupList.GetChildItem(rootItem);
				while (item)
				{
					PTREEITEMDATA pItemData = (PTREEITEMDATA)m_GroupList.GetItemData(item);
					CString szUri = pJoinFixedGroupReqInfo->uri.c_str();
					if (pItemData->uri_ == szUri)
					{
						//找到了就直接删除返回
						DelTreeNode(m_GroupList, item);
						delete pJoinFixedGroupReqInfo;
						return 0L;
					}
					item = m_GroupList.GetNextSiblingItem(item);
				}
				//没有找到
				break;
			}
			rootItem = m_GroupList.GetNextSiblingItem(rootItem);
		}
	}

	delete pJoinFixedGroupReqInfo;
	return 0L;
}

LRESULT CBaseDlg::OnMsgGroupJoinFixedRsp(WPARAM wParm, LPARAM Lparam)
{
	if (!Lparam)
		return -1L;	

	JoinFixedGroupRspInfo* pJoinFixedGroupRspInfo = (JoinFixedGroupRspInfo*)Lparam;

	CString szResult(UTF8ToANSI(pJoinFixedGroupRspInfo->name.c_str()));
	if (1 == pJoinFixedGroupRspInfo->result)	//申请加入群组，被同意
	{
		szResult.Append(_T("accept join the fixedgroup \""));
		szResult.Append(UTF8ToANSI(pJoinFixedGroupRspInfo->group.name_.c_str()));
		szResult.Append(_T("\""));
		MessageBox(szResult);
	}
	else	//申请加入群组，被拒绝
	{
		szResult.Append(_T("reject join the fixedgroup \""));
		szResult.Append(UTF8ToANSI(pJoinFixedGroupRspInfo->group.name_.c_str()));
		szResult.Append(_T("\""));
		MessageBox(szResult);
	}

	delete pJoinFixedGroupRspInfo;
	return 0L;
}

void CBaseDlg::AddImage(CImageList& imageList, UINT _id)
{
	CBitmap bm;
	bm.LoadBitmap(_id);
	imageList.Add(&bm, RGB(0, 0, 0));
}

void CBaseDlg::UpdateContactTree(int _state, const CString& szAcc)
{
	HTREEITEM itemroot = m_ContactList.GetRootItem();
	bool bfound = false;

	while (itemroot)
	{
		HTREEITEM item = m_ContactList.GetChildItem(itemroot);
		while (item)
		{
			PTREEITEMDATA pTreeItemData = (PTREEITEMDATA)m_ContactList.GetItemData(item);
			if (NULL == pTreeItemData)
			{
				MessageBox(_T("GetItemData is null."));
				continue;
			}

			if (pTreeItemData->ucAcc_ == szAcc)
			{
				int iStateImg = GetStatusImageID(_state);
				m_ContactList.SetItemImage(item, iStateImg, iStateImg);
				goto HAVE_FOUND_ITEM;
			}
			item = m_ContactList.GetNextSiblingItem(item);
		}

		itemroot = m_ContactList.GetNextSiblingItem(itemroot);
	}

	HAVE_FOUND_ITEM:

	//list:Offline, Online, Hide, Busy, Leave, Nodis
	if (szAcc == m_szAccount)
	{
		m_cmbState.SetCurSel(_state);
		m_cmbState.UpdateData(FALSE);
	}

	//change group contact status
	HTREEITEM itemrootg = m_GroupList.GetRootItem();
	while (itemrootg)
	{
		HTREEITEM item = m_GroupList.GetChildItem(itemrootg);
		while (item)
		{
			PTREEITEMDATA pTreeItemData = (PTREEITEMDATA)m_ContactList.GetItemData(item);
			if (NULL == pTreeItemData)
			{
				MessageBox(_T("GetItemData is null."));
				continue;
			}

			if (pTreeItemData->ucAcc_ == szAcc)
			{
				int iStateImg = GetStatusImageID(_state);
				m_GroupList.SetItemImage(item, iStateImg, iStateImg);
				return;
			}
			item = m_GroupList.GetNextSiblingItem(item);
		}

		itemrootg = m_GroupList.GetNextSiblingItem(itemrootg);
	}
}

void CBaseDlg::InitContactList()
{
	if (IsWindow(m_ContactList.GetSafeHwnd()))
		ClearTree(m_ContactList, m_ContactList.GetRootItem());

	std::vector<UCSDKCustomGroup> list;
	int iRet = m_pUCGroupAbsProxy->GetCustomGrouplist(list);
	if (0 != iRet)
	{
		MessageBox(_T("GetCustomGrouplist failed."));
		return;
	}

	for (int i=0; i<(int)list.size(); i++)
	{
		HTREEITEM itemroot = m_ContactList.InsertItem(UTF8ToANSI(list[i].name_.c_str()), BITMAP_UNFOLD_ImgID, BITMAP_UNFOLD_ImgID, NULL);
		PTREEITEMDATA pTreeItemData = new TREEITEMDATA;
		pTreeItemData->hItem = itemroot;
		pTreeItemData->id_ = list[i].id_.c_str();
		pTreeItemData->name_ = list[i].name_.c_str();
		m_ContactList.SetItemData(itemroot, (DWORD_PTR)pTreeItemData);
		
		std::vector<UCSDKContact> contactlist;
		iRet = m_pUCGroupAbsProxy->GetContactlist(list[i], contactlist);
		if (0 != iRet)
		{
			MessageBox(_T("GetContactlist failed."));
			return;
		}

		std::vector<UCSDKContact>::iterator it = contactlist.begin();
		for (; it != contactlist.end(); it++)
		{
			CString szAcc(it->ucAcc_.c_str());
			if (szAcc == m_szAccount)
				continue;

			CString szName;
			szName.Format(_T("%s(%s)"), UTF8ToANSI(it->name_.c_str()), UTF8ToANSI(it->ucAcc_.c_str()));
			int iStateImg = GetStatusImageID(it->uri_);
			HTREEITEM item = m_ContactList.InsertItem(szName, iStateImg, iStateImg, itemroot);
			pTreeItemData = new TREEITEMDATA;
			pTreeItemData->hItem = item;
			pTreeItemData->id_ = it->id_.c_str();
			pTreeItemData->name_ = it->name_.c_str();
			pTreeItemData->uri_ = it->uri_.c_str();
			pTreeItemData->ucAcc_ = it->ucAcc_.c_str();
			m_ContactList.SetItemData(item, (DWORD_PTR)pTreeItemData);
		}
		m_ContactList.Expand(itemroot,TVE_EXPAND);
	}
}

void CBaseDlg::InitGroupList()
{
	if (IsWindow(m_GroupList.GetSafeHwnd()))
		ClearTree(m_GroupList, m_GroupList.GetRootItem());

	std::vector<UCSDKFixedGroup> list;
	int iRet = m_pUCGroupAbsProxy->RefreshFixedGrouplist(list);
	if (0 != iRet)
	{
		MessageBox(_T("RefreshFixedGrouplist failed."));
		return;
	}

	for (int i=0; i<(int)list.size(); i++)
	{
		HTREEITEM itemroot = m_GroupList.InsertItem(UTF8ToANSI(list[i].name_.c_str()), BITMAP_GROUP_ImgID, BITMAP_GROUP_ImgID, NULL);
		PTREEITEMDATA pTreeItemData = new TREEITEMDATA;
		pTreeItemData->hItem = itemroot;
		pTreeItemData->id_ = list[i].id_.c_str();
		pTreeItemData->name_ = list[i].name_.c_str();
		pTreeItemData->uri_ = list[i].uri_.c_str();
		m_GroupList.SetItemData(itemroot, (DWORD_PTR)pTreeItemData);		

		std::vector<UCSDKContact> contactlist;
		iRet = m_pUCGroupAbsProxy->Refresh(list[i], contactlist);
		if (0 != iRet)
		{
			MessageBox(_T("Refresh failed."));
			return;
		}

		std::vector<UCSDKContact>::iterator it = contactlist.begin();
		for (; it != contactlist.end(); it++)
		{
			CString szName;
			szName.Format(_T("%s(%s)"), UTF8ToANSI(it->name_.c_str()), UTF8ToANSI(it->ucAcc_.c_str()));
			int iStateImg = GetStatusImageID(it->uri_);
			HTREEITEM item = m_GroupList.InsertItem(szName, iStateImg, iStateImg, itemroot);
			pTreeItemData = new TREEITEMDATA;
			pTreeItemData->hItem = item;
			pTreeItemData->id_ = it->id_.c_str();
			pTreeItemData->name_ = it->name_.c_str();
			pTreeItemData->uri_ = it->uri_.c_str();
			pTreeItemData->ucAcc_ = it->ucAcc_.c_str();
			m_GroupList.SetItemData(item, (DWORD_PTR)pTreeItemData);
		}
		m_GroupList.Expand(itemroot,TVE_EXPAND);
	}
}

void CBaseDlg::PublishSelfState(int iState)
{
	PublishInfoMap pub;
	std::ostringstream os;
	os << iState;
	pub.insert(std::make_pair(PUB_Availability, os.str()));

	//发布个人状态
	int iRet = m_pUCPublicAbsProxy->PublishSelfInformation(pub);
	if (0 != iRet)
	{
		MessageBox(_T("PublishSelfInformation failed."));
	}

	//离线时无法收到状态回调，手动把自己状态设为离线状态
	if (iState == 0)
	{
		UpdateContactTree(iState, m_szAccount);
	}
}

CChatDlg* CBaseDlg::GetChatDlgByAccount(const CString& ucAcc)
{
	std::map<std::string, CChatDlg*>::iterator itor = m_ChatDlgList.begin();
	for (; itor != m_ChatDlgList.end(); itor++)
	{
		CChatDlg*& pChatDlg = itor->second;
		if (pChatDlg->m_ConfMemList.GetItemCount() == 0 && pChatDlg->m_szTargetAcc == ucAcc)
		{
			return pChatDlg;
		}
	}

	return NULL;
}

int CBaseDlg::GetStatusImageID(const std::string& uri)
{
	int status = -1;
	int iRet = m_pUCPublicAbsProxy->GetContactStatus(uri, status);
	if (0 != iRet)
	{
		//MessageBox(_T("GetContactStatus failed."));
		return BITMAP_OFFLINE_ImgID;
	}

	switch (status)
	{
	case 0:	//Offline
		return BITMAP_OFFLINE_ImgID;
	case 1:	//Online
		return BITMAP_ONLINE_ImgID;
	case 2:	//hide 只能是自己的状态
		return BITMAP_ONLINE_ImgID;
	case 3:	//Busy
		return BITMAP_BUSY_ImgID;
	case 4:	//Leave
		return BITMAP_LEAVE_ImgID;
	case 5:	//Nodis
		return BITMAP_NODIS_ImgID;
	default:
		return BITMAP_OFFLINE_ImgID;
	}
}

int CBaseDlg::GetStatusImageID(int state)
{
	switch (state)
	{
	case 0:	//Offline
		return BITMAP_OFFLINE_ImgID;
	case 1:	//Online
		return BITMAP_ONLINE_ImgID;
	case 2:	//hide 只能是自己的状态
		return BITMAP_ONLINE_ImgID;
	case 3:	//Busy
		return BITMAP_BUSY_ImgID;
	case 4:	//Leave
		return BITMAP_LEAVE_ImgID;
	case 5:	//Nodis
		return BITMAP_NODIS_ImgID;
	default:
		return BITMAP_OFFLINE_ImgID;
	}
}

void CBaseDlg::ClearTree(CTreeCtrl& tree, const HTREEITEM& hItem)
{
	if (NULL == hItem || !::IsWindow(tree.GetSafeHwnd()))
	{
		return;
	}

	//释放节点内存
	PTREEITEMDATA itemData = (PTREEITEMDATA)tree.GetItemData(hItem);
	ClearTree(tree, tree.GetChildItem(hItem));
	ClearTree(tree, tree.GetNextSiblingItem(hItem));
	tree.DeleteItem(hItem);
	if(itemData != NULL)
	{
		itemData->hItem = NULL;
		delete itemData;
		itemData = NULL;
	}
}

void CBaseDlg::DelTreeNode(CTreeCtrl& tree, const HTREEITEM& hItem)
{
	if (NULL == hItem || !::IsWindow(tree.GetSafeHwnd()))
	{
		return;
	}

	HTREEITEM hChildItem = tree.GetChildItem(hItem);
	while (hChildItem)
	{
		PTREEITEMDATA itemData = (PTREEITEMDATA)tree.GetItemData(hChildItem);
		if(itemData != NULL)
		{
			itemData->hItem = NULL;
			delete itemData;
			itemData = NULL;
		}

		HTREEITEM hSibItem = tree.GetNextSiblingItem(hChildItem);
		tree.DeleteItem(hChildItem);
		hChildItem = hSibItem;
	}

	PTREEITEMDATA itemData = (PTREEITEMDATA)tree.GetItemData(hItem);
	if(itemData != NULL)
	{
		itemData->hItem = NULL;
		delete itemData;
		itemData = NULL;
	}
	tree.DeleteItem(hItem);
}
