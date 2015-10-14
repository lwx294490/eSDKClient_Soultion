// BookConfDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "eSDKClientDemo.h"
#include "BookConfDlg.h"
#include "CodeTools.h"


// CBookConfDlg 对话框

IMPLEMENT_DYNAMIC(CBookConfDlg, CDialog)

CBookConfDlg::CBookConfDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CBookConfDlg::IDD, pParent)
	, m_convId("")
	, m_pCBaseDlg(NULL)
	, m_pUCMeetingAbsProxy(NULL)
{

}

CBookConfDlg::~CBookConfDlg()
{
}

void CBookConfDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON_LEAVE, m_btnLeaveConf);
	DDX_Control(pDX, IDC_LIST_BOOKCONF, m_BookConfList);
}


BEGIN_MESSAGE_MAP(CBookConfDlg, CDialog)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BUTTON_LEAVE, &CBookConfDlg::OnBnClickedButtonLeave)
	ON_NOTIFY(NM_RCLICK, IDC_LIST_BOOKCONF, &CBookConfDlg::OnNMRClickListBookconf)
	ON_COMMAND_RANGE(ID_MENU_BOOK_CONF_BEGIN, ID_MENU_BOOK_CONF_END, &CBookConfDlg::OnClickBookConfMenuItem)
END_MESSAGE_MAP()


BOOL CBookConfDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	//设置成员列表框为单选模式
	m_BookConfList.ModifyStyle(0,LVS_SINGLESEL);
	//插入列表头
	m_BookConfList.InsertColumn(LIST_topic, _T("Topic"), LVCFMT_LEFT, WIDTH_topic);
	m_BookConfList.InsertColumn(LIST_meetingtime, _T("MeetTime"), LVCFMT_LEFT, WIDTH_meetingtime);
	m_BookConfList.InsertColumn(LIST_convenername, _T("ConvenerName"), LVCFMT_LEFT, WIDTH_convenername);
	m_BookConfList.InsertColumn(LIST_startdate, _T("StartDate"), LVCFMT_LEFT, WIDTH_startdate);
	m_BookConfList.InsertColumn(LIST_content, _T("Content"), LVCFMT_LEFT, WIDTH_content);
	m_BookConfList.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_HEADERDRAGDROP | LVS_EX_SUBITEMIMAGES | LVS_EX_INFOTIP);

	m_btnLeaveConf.EnableWindow(FALSE);

	m_convId = "";
	m_UCSDKBookConfList.clear();
	m_bHaveJoin = false;
	m_pCBaseDlg = NULL;
	m_pUCMeetingAbsProxy = UCMeetingAbsProxy::GetInstance();
	GetBookConfList();

	return TRUE;
}

// CBookConfDlg 消息处理程序

void CBookConfDlg::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CDialog::OnClose();

	if (!m_bHaveJoin && !m_convId.empty())
		OnBnClickedButtonLeave();

	m_convId = "";
	m_pCBaseDlg = NULL;
	m_bHaveJoin = false;
	m_UCSDKBookConfList.clear();
	m_pUCMeetingAbsProxy = NULL;
}

void CBookConfDlg::OnBnClickedButtonLeave()
{
	// TODO: 在此添加控件通知处理程序代码
	if (m_pUCMeetingAbsProxy->LeaveMeeting(m_convId))
	{
		MessageBox(_T("Leave conference failed."),_T("Leave"),MB_OK);
		return;
	}

	m_convId = "";
	m_btnLeaveConf.EnableWindow(FALSE);
}

void CBookConfDlg::OnNMRClickListBookconf(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;

	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	*pResult = 0;
	int nItem = pNMListView->iItem;
	if (-1 == nItem)
	{
		return;
	}

	//主持人弹出以下菜单
	CMenu menu;
	menu.CreatePopupMenu();
	menu.AppendMenu(MF_STRING, ID_MENU_JOIN_BOOK_CONF, _T("Join book conference"));

	CPoint pmenu;
	::GetCursorPos(&pmenu);
	menu.TrackPopupMenu(0, pmenu.x, pmenu.y, this);
}

void CBookConfDlg::OnClickBookConfMenuItem(UINT uID)
{
	POSITION pos = m_BookConfList.GetFirstSelectedItemPosition();
	int item = m_BookConfList.GetNextSelectedItem(pos);

	switch (uID)
	{
		//加入预约会议
	case ID_MENU_JOIN_BOOK_CONF:
		{
			//m_BookConfList中的index与m_UCSDKBookConfList相互对应
			if (m_pUCMeetingAbsProxy->JoinMeeting(m_convId, m_UCSDKBookConfList[item]))
			{
				MessageBox(_T("Join conference failed."),_T("Failed"),MB_OK);
				return;
			}

			JoinConfInfo* pJoinConfInfo = new JoinConfInfo;
			pJoinConfInfo->convId = m_convId;
			pJoinConfInfo->convener = m_UCSDKBookConfList[item].convener;
			m_bHaveJoin = true;
			m_pCBaseDlg->PostMessage(WM_JOIN_CONFERENCE,0,(LPARAM)pJoinConfInfo);
			PostMessage(WM_CLOSE);
		}
		break;
	}
}

void CBookConfDlg::GetBookConfList()
{
	if (m_pUCMeetingAbsProxy->GetBookConfList(m_UCSDKBookConfList))
	{
		MessageBox(_T("Get book conference list failed."),_T("Failed"),MB_OK);
		return;
	}

	UCSDKBookConfList::iterator it = m_UCSDKBookConfList.begin();
	for (; it != m_UCSDKBookConfList.end(); it++)
	{
		CString szResult = UTF8ToANSI(it->convenername.c_str());

		int item = m_BookConfList.InsertItem(m_BookConfList.GetItemCount(), _T(""), NULL);
		m_BookConfList.SetItemText(item, LIST_topic, it->topic.c_str());
		m_BookConfList.SetItemText(item, LIST_meetingtime, it->meetingtime.c_str());
		m_BookConfList.SetItemText(item, LIST_convenername, szResult);
		m_BookConfList.SetItemText(item, LIST_startdate, it->startdate.c_str());
		m_BookConfList.SetItemText(item, LIST_content, it->content.c_str());
	}
}
