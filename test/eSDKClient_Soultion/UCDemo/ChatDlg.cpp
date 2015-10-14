// ChatDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "UCDemo.h"
#include "ChatDlg.h"
#include "CodeTools.h"
#include "BaseDlg.h"

#include <strstream>


// CChatDlg 对话框

IMPLEMENT_DYNAMIC(CChatDlg, CDialog)

CChatDlg::CChatDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CChatDlg::IDD, pParent)
	, m_szAccount(_T(""))
	, m_szCompere(_T(""))
	, m_szTargetAcc(_T(""))
	, m_convId("")
	, m_pCBaseDlg(NULL)
	, m_pCInputDlg(NULL)
{

}

CChatDlg::~CChatDlg()
{
}

void CChatDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON_HOLD, m_btnHold);
	DDX_Control(pDX, IDC_BUTTON_RESUME, m_btnResume);
	DDX_Control(pDX, IDC_BUTTON_OPENVIDEO, m_btnStartRecord);
	DDX_Control(pDX, IDC_BUTTON_CLOSEVIDEO, m_btnStopRecord);
	DDX_Control(pDX, IDC_BUTTON_MICMUTE, m_btnMicMute);
	DDX_Control(pDX, IDC_BUTTON_MICUNMUTE, m_btnMicUnMute);
	DDX_Control(pDX, IDC_BUTTON_SPKMUTE, m_btnSpkMute);
	DDX_Control(pDX, IDC_BUTTON_SPKUNMUTE, m_btnSpkUnMute);
	DDX_Control(pDX, IDC_BUTTON_CALL, m_btnCall);
	DDX_Control(pDX, IDC_BUTTON_VIDEOCALL, m_btnVideoCall);
	DDX_Control(pDX, IDC_BUTTON_ADD, m_btnAdd);
	DDX_Control(pDX, IDC_BUTTON_HANGUP, m_btnHangup);
	DDX_Control(pDX, IDC_BUTTON_SEND, m_btnSend);
	DDX_Control(pDX, IDC_LIST_CONT, m_ConfMemList);
	DDX_Control(pDX, IDC_STATIC_REMOTE, m_stRemote);
	DDX_Control(pDX, IDC_STATIC_LOCAL, m_stLocal);
	DDX_Control(pDX, IDC_STATIC_RECV, m_stRecvMsg);
	DDX_Control(pDX, IDC_STATIC_SEND, m_stSendMsg);
}


BEGIN_MESSAGE_MAP(CChatDlg, CDialog)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BUTTON_HOLD, &CChatDlg::OnBnClickedButtonHold)
	ON_BN_CLICKED(IDC_BUTTON_RESUME, &CChatDlg::OnBnClickedButtonResume)
	ON_BN_CLICKED(IDC_BUTTON_OPENVIDEO, &CChatDlg::OnBnClickedButtonStartRecord)
	ON_BN_CLICKED(IDC_BUTTON_CLOSEVIDEO, &CChatDlg::OnBnClickedButtonStopRecord)
	ON_BN_CLICKED(IDC_BUTTON_MICMUTE, &CChatDlg::OnBnClickedButtonMicmute)
	ON_BN_CLICKED(IDC_BUTTON_MICUNMUTE, &CChatDlg::OnBnClickedButtonMicunmute)
	ON_BN_CLICKED(IDC_BUTTON_SPKMUTE, &CChatDlg::OnBnClickedButtonSpkmute)
	ON_BN_CLICKED(IDC_BUTTON_SPKUNMUTE, &CChatDlg::OnBnClickedButtonSpkunmute)
	ON_BN_CLICKED(IDC_BUTTON_ADD, &CChatDlg::OnBnClickedButtonAdd)
	ON_BN_CLICKED(IDC_BUTTON_SEND, &CChatDlg::OnBnClickedButtonSend)
	ON_BN_CLICKED(IDC_BUTTON_CALL, &CChatDlg::OnBnClickedButtonCall)
	ON_BN_CLICKED(IDC_BUTTON_VIDEOCALL, &CChatDlg::OnBnClickedButtonVideocall)
	ON_BN_CLICKED(IDC_BUTTON_HANGUP, &CChatDlg::OnBnClickedButtonHangup)
	ON_NOTIFY(NM_RCLICK, IDC_LIST_CONT, &CChatDlg::OnNMRClickListCont)
	ON_COMMAND_RANGE(ID_MENU_DELETE_MEM, ID_MENU_UNMUTE_MEM, &CChatDlg::OnClickListContMenuItem)
	ON_MESSAGE(WM_INPUT_STRING, &CChatDlg::OnMsgInputString)
END_MESSAGE_MAP()


BOOL CChatDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	//设置成员列表框为单选模式
	m_ConfMemList.ModifyStyle(0,LVS_SINGLESEL);
	//插入列表头
	m_ConfMemList.InsertColumn(LIST_NAME, _T("Name"), LVCFMT_LEFT, WIDTH_MEMBER_NAME);
	m_ConfMemList.InsertColumn(LIST_COMPERE_IMAGE, _T("Compere"), LVCFMT_LEFT, WIDTH_MEMBER_COMPERE_IMAGE);
	m_ConfMemList.InsertColumn(LIST_CALL_STATE_IMAGE, _T("ConfStatus"), LVCFMT_LEFT, WIDTH_MEMBER_CALLSTATE_IMAGE);
	m_ConfMemList.InsertColumn(LIST_SPEAKING, _T("Speaking"), LVCFMT_LEFT, WIDTH_MEMBER_SPEAKING);

	//图片列表，用于单个列表中单个列切换不同的图像
	m_lstImage.Create(20, 20, ILC_COLORDDB, 10, 1);//10个20*20的图像
	AddImage(m_lstImage, IDB_BITMAP_CALLING);		//0
	AddImage(m_lstImage, IDB_BITMAP_CALLEST);		//1
	AddImage(m_lstImage, IDB_BITMAP_CALLLEAVE);		//2
	AddImage(m_lstImage, IDB_BITMAP_CALLMISS);		//3
	AddImage(m_lstImage, IDB_BITMAP_COMPERE);		//4
	AddImage(m_lstImage, IDB_BITMAP_SPEAKER);		//5
	AddImage(m_lstImage, IDB_BITMAP_CONFMAN);		//6
	AddImage(m_lstImage, IDB_BITMAP_CONFWOMAN);		//7
	AddImage(m_lstImage, IDB_BITMAP_MIC_MUTE);		//8
	AddImage(m_lstImage, IDB_BITMAP_MIC_UNMUTE);	//9
	m_ConfMemList.SetImageList(&m_lstImage, LVSIL_SMALL);
	m_lstImage.Detach();

	//设置List风格:全选、子列支持图片
	m_ConfMemList.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_HEADERDRAGDROP | LVS_EX_SUBITEMIMAGES | LVS_EX_INFOTIP);

	//创建接收的richedit控件
	RECT rcRichEdit;
	m_stRecvMsg.GetWindowRect(&rcRichEdit);
	ScreenToClient(&rcRichEdit);
	CreateURichEdit(m_RichRecvMsg, rcRichEdit, TRUE, IDC_RICHEDIT_RECV);
	m_stSendMsg.GetWindowRect(&rcRichEdit);
	ScreenToClient(&rcRichEdit);
	CreateURichEdit(m_RichSendMsg, rcRichEdit, FALSE, IDC_RICHEDIT_SEND);

	m_btnHold.EnableWindow(FALSE);
	m_btnResume.EnableWindow(FALSE);
	//m_btnAdd.EnableWindow(FALSE);
	m_btnHangup.EnableWindow(FALSE);
	m_btnSend.EnableWindow(TRUE);
	m_btnCall.EnableWindow(FALSE);
	m_btnVideoCall.EnableWindow(FALSE);
	m_btnMicMute.EnableWindow(FALSE);
	m_btnMicUnMute.EnableWindow(FALSE);
	m_btnSpkMute.EnableWindow(FALSE);
	m_btnSpkUnMute.EnableWindow(FALSE);
	m_btnStartRecord.EnableWindow(FALSE);
	m_btnStopRecord.EnableWindow(FALSE);


	m_szAccount = _T("");
	m_szCompere = _T("");
	m_szTargetAcc = _T("");
	m_convId = "";
	m_bIsVideo = FALSE;

	m_pCBaseDlg = NULL;
	m_pCInputDlg = NULL;

	return TRUE;
}

BOOL CChatDlg::PreTranslateMessage(MSG* pMsg)
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

// CChatDlg 消息处理程序

void CChatDlg::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	//关闭会话
	if (!m_convId.empty() && CloseConversation(m_convId.c_str()))
	{
		MessageBox(_T("Close conversation failed."),_T("Failed"),MB_OK);
	}

	std::string* convId = new std::string(m_convId);
	if (m_pCBaseDlg->GetSafeHwnd())
		::PostMessage(m_pCBaseDlg->GetSafeHwnd(),WM_CHAT_CLOSEED,0,(LPARAM)convId);

	if (m_pCInputDlg && m_pCInputDlg->GetSafeHwnd())
		m_pCInputDlg->PostMessage(WM_CLOSE);
	if (m_pCInputDlg)
		delete m_pCInputDlg;


	m_szAccount = _T("");
	m_szCompere = _T("");
	m_szTargetAcc = _T("");
	m_convId = "";
	m_bIsVideo = FALSE;

	m_pCBaseDlg = NULL;
	m_pCInputDlg = NULL;

	CDialog::OnClose();
}

void CChatDlg::OnBnClickedButtonHold()
{
	// TODO: 在此添加控件通知处理程序代码
	if (Hold(m_convId.c_str()))
	{
		MessageBox(_T("Hold call failed."),_T("Failed"),MB_OK);
		return;
	}

	m_btnHold.EnableWindow(FALSE);
	m_btnResume.EnableWindow(TRUE);
}

void CChatDlg::OnBnClickedButtonResume()
{
	// TODO: 在此添加控件通知处理程序代码
	if (Resume(m_convId.c_str()))
	{
		MessageBox(_T("Resume call failed."),_T("Failed"),MB_OK);
		return;
	}

	m_btnHold.EnableWindow(TRUE);
	m_btnResume.EnableWindow(FALSE);
}

void CChatDlg::OnBnClickedButtonStartRecord()
{
	// TODO: 在此添加控件通知处理程序代码
	
	//获取录音目录
	std::string dllPath = GetModulePath(_T("UCSDK.dll"));
	std::string recordPath = dllPath;
	recordPath.append(_T("\\UserData\\"));
	recordPath.append(m_szAccount.GetBuffer());
	recordPath.append(_T("\\RecordFile\\"));

	//设置录音文件名
	std::string recordName = GetDateTimeString();
	recordPath.append(recordName);

	if (m_bIsVideo)	//录制视频
	{
		recordPath.append(_T(".avi"));
	}
	else			//录制语音
	{
		recordPath.append(_T(".wav"));
	}

	// 字符码装换
	std::string sRecordPath = ANSIToUTF8(recordPath.c_str());

	//开始录音
	int iRet = StartRecord(m_convId.c_str(), sRecordPath.c_str());
	if (iRet)
	{
		MessageBox(_T("StartRecord failed."));
		return;
	}

	m_btnStartRecord.EnableWindow(FALSE);
	m_btnStopRecord.EnableWindow(TRUE);
}

void CChatDlg::OnBnClickedButtonStopRecord()
{
	// TODO: 在此添加控件通知处理程序代码

	//停止录音
	int iRet = StopRecord(m_convId.c_str());
	if (iRet)
	{
		MessageBox(_T("StopRecord failed."));
		return;
	}
	m_btnStartRecord.EnableWindow(TRUE);
	m_btnStopRecord.EnableWindow(FALSE);
}

void CChatDlg::OnBnClickedButtonMicmute()
{
	// TODO: 在此添加控件通知处理程序代码
	if (MuteVoIP(UC_Mic))
	{
		MessageBox(_T("Mic mute failed."),_T("Failed"),MB_OK);
		return;
	}
	m_btnMicMute.EnableWindow(FALSE);
	m_btnMicUnMute.EnableWindow(TRUE);
}

void CChatDlg::OnBnClickedButtonMicunmute()
{
	// TODO: 在此添加控件通知处理程序代码
	if (UnMuteVoIP(UC_Mic))
	{
		MessageBox(_T("Mic unmute failed."),_T("Failed"),MB_OK);
		return;
	}
	m_btnMicMute.EnableWindow(TRUE);
	m_btnMicUnMute.EnableWindow(FALSE);
}

void CChatDlg::OnBnClickedButtonSpkmute()
{
	// TODO: 在此添加控件通知处理程序代码
	if (MuteVoIP(UC_Speaker))
	{
		MessageBox(_T("Speaker mute failed."),_T("Failed"),MB_OK);
		return;
	}
	m_btnSpkMute.EnableWindow(FALSE);
	m_btnSpkUnMute.EnableWindow(TRUE);
}

void CChatDlg::OnBnClickedButtonSpkunmute()
{
	// TODO: 在此添加控件通知处理程序代码
	if (UnMuteVoIP(UC_Speaker))
	{
		MessageBox(_T("Speaker unmute failed."),_T("Failed"),MB_OK);
		return;
	}
	m_btnSpkMute.EnableWindow(TRUE);
	m_btnSpkUnMute.EnableWindow(FALSE);
}

void CChatDlg::OnBnClickedButtonAdd()
{
	// TODO: 在此添加控件通知处理程序代码
	if (!m_pCInputDlg)
	{
		m_pCInputDlg = new CInputDlg(this);
		m_pCInputDlg->Create(CInputDlg::IDD, this);
	}
	m_pCInputDlg->Init();
	m_pCInputDlg->ShowWindow(TRUE);
}

void CChatDlg::OnBnClickedButtonSend()
{
	// TODO: 在此添加控件通知处理程序代码
	std::vector<std::string> list;
	if (m_convId.empty())	//如果当前不存在会话，则需要添加AccountList
	{
		//如果是会议
		if (IsMeetingConv())
		{
			for (int i=0; i<m_ConfMemList.GetItemCount(); i++)
			{
				CString szAccTemp = m_ConfMemList.GetItemText(i, LIST_NAME);
				if (szAccTemp == m_szAccount)
				{ 
					continue;
				}
				list.push_back(szAccTemp.GetBuffer());
			}
		}
		//如果是点对点
		else
		{
			list.push_back(m_szTargetAcc.GetBuffer());
		}
	}

	CString szSendMsg;
	m_RichSendMsg.GetWindowText(szSendMsg);
	if (szSendMsg.IsEmpty())
		return;

	/************************************************************************/
	/*	IM 格式
	/*	<imbody>
	/*	<imagelist>
	/*	<img>
	/*	<imgname>图片名</imgname>
	/*	<imgdata>图片数据</imgdata>
	/*	</img>
	/*	……
	/*	</imagelist>
	/*	<content>纯文本+表情转义符</content>
	/*	<html>html消息体</html>
	/*	</imbody>
	/************************************************************************/

	//IM 字体
	CString szFont(_T("<FONT style='font-size:18px' face='微软雅黑' color='0000ff'><B>"));
	szFont.Append(szSendMsg);
	szFont.Append(_T("</FONT>"));

	std::string sImage = "";
	std::string sMsg = ANSIToUTF8(szSendMsg.GetString());
	std::string sFont = ANSIToUTF8(szFont.GetString());

	//拼凑IM格式
	std::ostrstream OutMsgXML;
	OutMsgXML << "<imbody>";
	OutMsgXML << "<imagelist>" << sImage << "</imagelist>";
	OutMsgXML << "<html><![CDATA[" << sFont.c_str() << "]]></html>";
	OutMsgXML << "<content>" << sMsg.c_str() << "</content>";
	OutMsgXML << "</imbody>";
	OutMsgXML << std::ends;

	UCAccountList acclist;
	acclist.iFrom = 0;
	acclist.iTo = -1;
	acclist.iTotal = 0;
	acclist.account = NULL;
	if (list.size() > 0)
	{
		acclist.account = (UCAccount*)malloc(sizeof(UCAccount)*list.size());
		acclist.iTo = list.size() - 1;
		acclist.iTotal = list.size();
	}
	char convId[CONVID_LENGTH] = {0};
	if (!m_convId.empty())	//把string类型的convId转化为char数组
	{
		MemCopy(convId, m_convId.c_str(), CONVID_LENGTH);
	}
	if (SendIMMessage(OutMsgXML.str(), &acclist, convId))	//发送即时消息
	{
		MessageBox(_T("Send Message failed."),_T("Failed."),MB_OK);
		return;
	}
	if (m_convId.empty())
		m_convId = convId;
	if (acclist.account)
		free(acclist.account);

	//清空发送区
	m_RichSendMsg.SetSel(0, -1);
	m_RichSendMsg.ReplaceSel(_T(""));

	//将发送出去的消息显示在消息接收区
	SYSTEMTIME time;
	GetSystemTime(&time);
	CString szTime;
	szTime.Format("  %4d-%02d-%02d %02d:%02d:%02d", time.wYear, time.wMonth, time.wDay, time.wHour, time.wMinute, time.wSecond);
	CString cstrHead = m_szAccount+szTime;//ctk::to_utf8str((m_szAccount + szTime).GetBuffer());

	m_RichRecvMsg.SetSel(-1, -1);
	m_RichRecvMsg.ReplaceSel(cstrHead + _T("\r\n") + szSendMsg);
	m_RichRecvMsg.SetSel(-1, -1);
	m_RichRecvMsg.ReplaceSel(_T("\r\n"),TRUE);
	m_RichRecvMsg.UpdateData(FALSE);
}

void CChatDlg::OnBnClickedButtonCall()
{
	// TODO: 在此添加控件通知处理程序代码
	if (IsMeetingConv())	//conference call  会议呼叫（前提先MakeMeetingGroup）
	{
		if (StartMeeting(m_convId.c_str()))
		{
			MessageBox(_T("StartMeeting failed."),_T("Failed"),MB_OK);
			return;
		}
		for (int i=0; i<m_ConfMemList.GetItemCount(); i++)
		{
			CString szAcc = m_ConfMemList.GetItemText(i, LIST_NAME);
			UpdateConfMemList(szAcc, UC_Inviting);
		}
	}
	else		//voip call	点对点呼叫
	{
		UCContact contact;
		ZeroMemory(&contact, sizeof(contact));
		MemCopy(contact.ucAcc_, m_szTargetAcc, sizeof(contact.ucAcc_));

		UCVideoWindow local;
		UCVideoWindow remote;
		memset(&local, 0, sizeof(local));
		memset(&remote, 0, sizeof(remote));
		char convId[CONVID_LENGTH] = {0};
		if (!m_convId.empty())
			MemCopy(convId, m_convId.c_str(), CONVID_LENGTH);
		if (MakeCall(&contact, UC_Audio, &local, &remote, convId))
		{
			MessageBox(_T("Make Call failed."),_T("Failed"),MB_OK);
			return;
		}
		if (m_convId.empty())
			m_convId = convId;
	}

	//发布忙碌状态
	CBaseDlg* pDlg = dynamic_cast<CBaseDlg*>(m_pCBaseDlg);
	if (pDlg)
	{
		pDlg->PublishSelfState(3);
	}

	m_btnCall.EnableWindow(FALSE);
	m_btnVideoCall.EnableWindow(FALSE);
	m_btnHangup.EnableWindow(TRUE);
}

void CChatDlg::OnBnClickedButtonVideocall()
{
	// TODO: 在此添加控件通知处理程序代码
	//如果是会议不能进行视频呼叫
	if (IsMeetingConv())
	{
		MessageBox(_T("can't make video call in conference."),_T("Error"),MB_OK);
		return;
	}

	UCContact contact;
	ZeroMemory(&contact, sizeof(contact));
	MemCopy(contact.ucAcc_, m_szTargetAcc, sizeof(contact.ucAcc_));

	CRect rectLocat;
	m_stLocal.GetClientRect(&rectLocat);
	ClientToScreen(&rectLocat);
	CRect rectRemote;
	m_stRemote.GetClientRect(&rectRemote);
	ClientToScreen(&rectRemote);

	UCVideoWindow local;
	local.hWnd = (int)m_stLocal.GetSafeHwnd();
	local.height = rectLocat.Height();
	local.width = rectLocat.Width();
	local.top = rectLocat.top;
	local.left = rectLocat.left;
	UCVideoWindow remote;
	remote.hWnd = (int)m_stRemote.GetSafeHwnd();
	remote.height = rectRemote.Height();
	remote.width = rectRemote.Width();
	remote.top = rectRemote.top;
	remote.left = rectRemote.left;

	char convId[CONVID_LENGTH] = {0};
	if (!m_convId.empty())
		MemCopy(convId, m_convId.c_str(), CONVID_LENGTH);
	if (MakeCall(&contact, UC_Video, &local, &remote, convId))
	{
		MessageBox(_T("Make Call failed."),_T("Failed"),MB_OK);
		return;
	}
	if (m_convId.empty())
		m_convId = convId;

	//发布忙碌状态
	CBaseDlg* pDlg = dynamic_cast<CBaseDlg*>(m_pCBaseDlg);
	if (pDlg)
	{
		pDlg->PublishSelfState(3);
	}

	m_btnCall.EnableWindow(FALSE);
	m_btnVideoCall.EnableWindow(FALSE);
	m_btnHangup.EnableWindow(TRUE);
	m_bIsVideo = TRUE;
}

void CChatDlg::OnBnClickedButtonHangup()
{
	// TODO: 在此添加控件通知处理程序代码
	if (Hangup(m_convId.c_str(), UC_Audio))
	{
		MessageBox(_T("Hangup failed."),_T("Failed"),MB_OK);
		return;
	}

	//hangup conference 如果是会议挂断语音，要修改界面与会成员状态显示
	if (m_ConfMemList.GetItemCount() > 0)
	{
		for (int i=0; i<m_ConfMemList.GetItemCount(); i++)
		{
			CString szAcc = m_ConfMemList.GetItemText(i, LIST_NAME);
			UpdateConfMemList(szAcc, -1);
		}
		m_btnHold.EnableWindow(FALSE);
		m_btnResume.EnableWindow(FALSE);
		//m_btnAdd.EnableWindow(FALSE);
		m_btnHangup.EnableWindow(FALSE);
		m_btnCall.EnableWindow(TRUE);
		m_btnVideoCall.EnableWindow(FALSE);
		m_btnMicMute.EnableWindow(FALSE);
		m_btnMicUnMute.EnableWindow(FALSE);
		m_btnSpkMute.EnableWindow(FALSE);
		m_btnSpkUnMute.EnableWindow(FALSE);
		m_btnStartRecord.EnableWindow(FALSE);
		m_btnStopRecord.EnableWindow(FALSE);
	}
	//hangup voip
	else
	{
		m_btnHold.EnableWindow(FALSE);
		m_btnResume.EnableWindow(FALSE);
		//m_btnAdd.EnableWindow(FALSE);
		m_btnHangup.EnableWindow(FALSE);
		m_btnCall.EnableWindow(TRUE);
		m_btnVideoCall.EnableWindow(TRUE);
		m_btnMicMute.EnableWindow(FALSE);
		m_btnMicUnMute.EnableWindow(FALSE);
		m_btnSpkMute.EnableWindow(FALSE);
		m_btnSpkUnMute.EnableWindow(FALSE);
		m_btnStartRecord.EnableWindow(FALSE);
		m_btnStopRecord.EnableWindow(FALSE);
	}

	//发布空闲状态
	CBaseDlg* pDlg = dynamic_cast<CBaseDlg*>(m_pCBaseDlg);
	if (pDlg)
	{
		pDlg->PublishSelfState(1);
	}
}

void CChatDlg::OnNMRClickListCont(NMHDR *pNMHDR, LRESULT *pResult)
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

	if (m_szCompere != m_szAccount)
		return;

	POSITION pos = m_ConfMemList.GetFirstSelectedItemPosition();
	int item = m_ConfMemList.GetNextSelectedItem(pos);
	CString szAcc = m_ConfMemList.GetItemText(item, LIST_NAME);
	if (szAcc == m_szAccount)
		return;

	//主持人弹出以下菜单
	CMenu menu;
	menu.CreatePopupMenu();
	menu.AppendMenu(MF_STRING, ID_MENU_DELETE_MEM, _T("Remove"));
	menu.AppendMenu(MF_STRING, ID_MENU_ENDCALL_MEM, _T("Kick"));
	menu.AppendMenu(MF_STRING, ID_MENU_REINVITE_MEM, _T("ReInvite"));
	menu.AppendMenu(MF_STRING, ID_MENU_MUTE_MEM, _T("Mute"));
	menu.AppendMenu(MF_STRING, ID_MENU_UNMUTE_MEM, _T("UnMute"));

	CPoint pmenu;
	::GetCursorPos(&pmenu);
	menu.TrackPopupMenu(0, pmenu.x, pmenu.y, this);
}

void CChatDlg::OnClickListContMenuItem(UINT uID)
{
	POSITION pos = m_ConfMemList.GetFirstSelectedItemPosition();
	int item = m_ConfMemList.GetNextSelectedItem(pos);
	CString szAcc = m_ConfMemList.GetItemText(item, LIST_NAME);

	switch(uID)
	{
	case ID_MENU_DELETE_MEM:	//移除与会人
		{
			UCContact contact;
			ZeroMemory(&contact, sizeof(contact));
			MemCopy(contact.ucAcc_, szAcc, sizeof(contact.ucAcc_));

			if (RemoveParticipant(&contact, m_convId.c_str()))
			{
				MessageBox(_T("RemoveParticipant failed."),_T("Failed"),MB_OK);
				return;
			}
			UpdateConfMemList(szAcc, UC_MemDel);
		}
		break;
	case ID_MENU_ENDCALL_MEM:	//挂断与会人
		{
			UCContact contact;
			ZeroMemory(&contact, sizeof(contact));
			MemCopy(contact.ucAcc_, szAcc, sizeof(contact.ucAcc_));

			if (KickParticipant(&contact, m_convId.c_str()))
			{
				MessageBox(_T("KickParticipant failed."),_T("Failed"),MB_OK);
				return;
			}
		}
		break;
	case ID_MENU_REINVITE_MEM:	//重新邀请与会人
		{
			UCContact contact;
			ZeroMemory(&contact, sizeof(contact));
			MemCopy(contact.ucAcc_, szAcc, sizeof(contact.ucAcc_));

			if (ConnectParticipant(&contact, m_convId.c_str()))
			{
				MessageBox(_T("ConnectParticipant failed."),_T("Failed"),MB_OK);
				return;
			}
			UpdateConfMemList(szAcc, UC_Inviting);
		}
		break;
	case ID_MENU_MUTE_MEM:		//禁止与会人发言
		{
			UCContact contact;
			ZeroMemory(&contact, sizeof(contact));
			MemCopy(contact.ucAcc_, szAcc, sizeof(contact.ucAcc_));

			if (MuteMeeting(&contact, m_convId.c_str()))
			{
				MessageBox(_T("Mute failed."),_T("Failed"),MB_OK);
				return;
			}
		}
		break;
	case ID_MENU_UNMUTE_MEM:	//允许与会人发言
		{
			UCContact contact;
			ZeroMemory(&contact, sizeof(contact));
			MemCopy(contact.ucAcc_, szAcc, sizeof(contact.ucAcc_));

			if (UnMuteMeeting(&contact, m_convId.c_str()))
			{
				MessageBox(_T("UnMute failed."),_T("Failed"),MB_OK);
				return;
			}
		}
		break;
	}
}

LRESULT CChatDlg::OnMsgInputString(WPARAM wParm, LPARAM Lparam)
{
	if (!Lparam)
		return -1L;

	InputInfo *pInputInfo = (InputInfo*)Lparam;

	//如果没有会话，先创建临时组
	if (m_convId.empty())
	{
		std::vector<CString> list;
		list.push_back(m_szTargetAcc);
		list.push_back(pInputInfo->szInput);
		
		UCContactList contactlist;
		contactlist.iFrom = 0;
		contactlist.iTo = list.size() - 1;
		contactlist.iTotal = list.size();
		contactlist.contact = (UCContact*)malloc(sizeof(UCContact)*list.size());
		for (int i=0; i < (int)list.size(); i++)
		{
			MemCopy(contactlist.contact[i].ucAcc_, list[i], sizeof(contactlist.contact[i].ucAcc_));
		}

		char convId[CONVID_LENGTH] = {0};
		if (!m_convId.empty())
			MemCopy(convId, m_convId.c_str(), CONVID_LENGTH);
		if (MakeMeetingGroup(&contactlist, convId))
		{
			MessageBox(_T("Make meeting failed."),_T("Failed"),MB_OK);
			delete pInputInfo;
			return -1L;
		}
		if (m_convId.empty())
			m_convId = convId;

		AddConfCompere(m_szAccount, -1);
		AddConfMember(m_szTargetAcc, -1);
		AddConfMember(pInputInfo->szInput, -1);

		m_btnVideoCall.EnableWindow(FALSE);

		CString szWin;
		GetWindowText(szWin);
		szWin.Append(_T(" Conference"));
		SetWindowText(szWin);
		m_szCompere = m_szAccount;
	}
	//如果已有会话，则直接添加与会成员
	else
	{
		// 是否已经存在
		if (pInputInfo->szInput == m_szAccount || pInputInfo->szInput == m_szTargetAcc)
		{
			MessageBox(_T("The account is exist."));
			return -1L;
		}
		for (int i=0; i<m_ConfMemList.GetItemCount(); i++)
		{
			CString szTmpAcc = m_ConfMemList.GetItemText(i, LIST_NAME);
			if (szTmpAcc == pInputInfo->szInput)
			{
				MessageBox(_T("The account is exist."));
				return -1L;
			}
		}

		UCContact contact;
		ZeroMemory(&contact, sizeof(contact));
		MemCopy(contact.ucAcc_, pInputInfo->szInput, sizeof(contact.ucAcc_));
		if (AddParticipant(&contact, m_convId.c_str()))
		{
			MessageBox(_T("AddParticipant failed."),_T("Failed"),MB_OK);
			delete pInputInfo;
			return -1L;
		}

		if (m_ConfMemList.GetItemCount() == 0)
		{
			UpdateConfMemList(m_szAccount, -1);
			UpdateConfMemList(m_szTargetAcc, -1);
			AddConfMember(pInputInfo->szInput, -1);
			m_szCompere = m_szAccount;
		}
		else
		{
			UpdateConfMemList(m_szAccount, -1);
			AddConfMember(pInputInfo->szInput, -1);
		}
	}

	delete pInputInfo;
	return 0L;
}

void CChatDlg::AddImage(CImageList& imageList, UINT _id)
{
	CBitmap bm;
	bm.LoadBitmap(_id);
	imageList.Add(&bm, RGB(0, 0, 0));
}

void CChatDlg::CreateURichEdit(CRichEditCtrl &RichEdit , RECT& rcRichEdit, BOOL bIsReadOnly ,UINT controlID)
{
	DWORD dwStyle;

	if (bIsReadOnly)
	{
		dwStyle = WS_VISIBLE | WS_CHILDWINDOW | WS_VSCROLL | ES_READONLY | ES_WANTRETURN | ES_MULTILINE | ES_AUTOVSCROLL ;
	}
	else
	{
		dwStyle = WS_VISIBLE | WS_CHILDWINDOW | WS_VSCROLL | ES_WANTRETURN | ES_MULTILINE | ES_AUTOVSCROLL  ;
	}
	RichEdit.Create( dwStyle, rcRichEdit, this, controlID );
	RichEdit.SetBackgroundColor(FALSE,RGB(255,255,255));
}

void CChatDlg::RecvIMMsg(CString header, CString body)
{	
	/************************************************************************/
	/*	IM 格式
	/*	<imbody>
	/*	<imagelist>
	/*	<img>
	/*	<imgname>图片名</imgname>
	/*	<imgdata>图片数据</imgdata>
	/*	</img>
	/*	……
	/*	</imagelist>
	/*	<content>纯文本+表情转义符</content>
	/*	<html>html消息体</html>
	/*	</imbody>
	/************************************************************************/

	//这里只取<content></content>之间的存文本。如果想要取到发送的文本字体格式等请使用<html>到</html>之间的，进行解析。
	std::string sBody = body.GetBuffer();
	std::size_t iFrom = sBody.find("<content>") + 9;
	std::string content = sBody.substr(iFrom, std::string::npos);
	std::size_t iEnd = content.find("</content>");
	content = content.substr(0, iEnd);

	CString szResult(_T(""));
	std::string strOut = UTF8ToANSI(content.c_str());
	szResult = strOut.c_str();

	CString szRecv = header + _T("\r\n");
	szRecv.Append(szResult);

	m_RichRecvMsg.SetSel(-1, -1);
	m_RichRecvMsg.ReplaceSel(szRecv);
	m_RichRecvMsg.SetSel(-1, -1);
	m_RichRecvMsg.ReplaceSel(_T("\r\n"),TRUE);
}

void CChatDlg::UpdateConfMemList(const CString& szAcc, int nStatus)
{
	bool bFind = false;
	for (int i=0; i<m_ConfMemList.GetItemCount(); i++)
	{
		CString szAccTemp = m_ConfMemList.GetItemText(i, LIST_NAME);
		if (szAccTemp == szAcc)
		{
			bFind = true;
			switch(nStatus)
			{
			case -1:
				{
					m_ConfMemList.SetItem(i, LIST_CALL_STATE_IMAGE, LVIF_TEXT|LVIF_IMAGE, _T(""), -1, 0, 0, 0);
				}
				break;
			case UC_Inviting:		//正在呼叫某成员
				{
					m_ConfMemList.SetItem(i, LIST_CALL_STATE_IMAGE, LVIF_TEXT|LVIF_IMAGE, _T(""), BITMAP_CallIng, 0, 0, 0);
				}
				break;
			case UC_Hangup:			//某成员挂断
				{
					m_ConfMemList.SetItem(i, LIST_CALL_STATE_IMAGE, LVIF_TEXT|LVIF_IMAGE, _T(""), BITMAP_CallMiss, 0, 0, 0);
				}
				break;
			case UC_InConf:			//正在会议中
				{
					m_ConfMemList.SetItem(i, LIST_CALL_STATE_IMAGE, LVIF_TEXT|LVIF_IMAGE, _T(""), BITMAP_CallEst, 0, 0, 0);
				}
				break;
			case UC_Quit:			//成员离开
				{
					m_ConfMemList.SetItem(i, LIST_CALL_STATE_IMAGE, LVIF_TEXT|LVIF_IMAGE, _T(""), BITMAP_CallLeave, 0, 0, 0);
				}
				break;
			case UC_ForbidSpk:		//成员被静音
				{
					m_ConfMemList.SetItem(i, LIST_CALL_STATE_IMAGE, LVIF_TEXT|LVIF_IMAGE, _T(""), BITMAP_MicMute, 0, 0, 0);
				}
				break;
			case UC_AllowSpk:		//成员被取消静音
				{
					m_ConfMemList.SetItem(i, LIST_CALL_STATE_IMAGE, LVIF_TEXT|LVIF_IMAGE, _T(""), BITMAP_MicUnMute, 0, 0, 0);
				}
				break;
			case UC_CurSpker:		//成员在说话
				{
					m_ConfMemList.SetItem(i, LIST_SPEAKING, LVIF_TEXT|LVIF_IMAGE, _T(""), BITMAP_Speaker, 0, 0, 0);
				}
				break;
			case UC_MemAdd:			//新增成员
				{
					m_ConfMemList.SetItem(i, LIST_CALL_STATE_IMAGE, LVIF_TEXT|LVIF_IMAGE, _T(""), -1/*BITMAP_CallIng*/, 0, 0, 0);
				}
				break;
			case UC_MemDel:			//成员被删除
				{
					m_ConfMemList.DeleteItem(i);
					//if (szAcc == m_szCompere)
					//{
					//	OnBnClickedButtonHangup();
					//	return;
					//}
				}
				break;
			}
			break;
		}
	}

	// 当前发言人状态控制
	if (UC_CurSpker == nStatus)
	{
		for (int i=0; i<m_ConfMemList.GetItemCount(); i++)
		{
			CString szAccTemp = m_ConfMemList.GetItemText(i, LIST_NAME);
			if (szAccTemp == szAcc)
			{
				m_ConfMemList.SetItem(i, LIST_SPEAKING, LVIF_TEXT|LVIF_IMAGE, _T(""), BITMAP_Speaker, 0, 0, 0);
			}
			else
			{
				m_ConfMemList.SetItem(i, LIST_SPEAKING, LVIF_TEXT|LVIF_IMAGE, _T(""), -1, 0, 0, 0);
			}
		}
	}

	//如果在与会人列表里面没有找到，则在与会人列表里面增加该与会人。
	if (!bFind)
	{
		if (szAcc.IsEmpty())
			return;
		int item = m_ConfMemList.InsertItem(m_ConfMemList.GetItemCount(), _T(""), BITMAP_ConfMan);
		m_ConfMemList.SetItemText(item, LIST_NAME, szAcc);
		UpdateConfMemList(szAcc, nStatus);
	}
}

void CChatDlg::AddConfCompere(const CString& szAcc, int nStatus)
{
	bool bFind = false;
	for (int i=0; i<m_ConfMemList.GetItemCount(); i++)
	{
		CString szAccTemp = m_ConfMemList.GetItemText(i, LIST_NAME);
		if (szAccTemp == szAcc)
		{
			bFind = true;
			m_ConfMemList.SetItem(i, LIST_CALL_STATE_IMAGE, LVIF_TEXT|LVIF_IMAGE, _T(""), nStatus, 0, 0, 0);
			break;
		}
	}

	if (!bFind)
	{
		if (szAcc.IsEmpty())
			return;
		int item = m_ConfMemList.InsertItem(m_ConfMemList.GetItemCount(), _T(""), BITMAP_ConfMan);
		m_ConfMemList.SetItemText(item, LIST_NAME, szAcc);
		m_ConfMemList.SetItem(item, LIST_COMPERE_IMAGE, LVIF_TEXT|LVIF_IMAGE, _T(""), BITMAP_Compere, 0, 0, 0);
		m_szCompere = szAcc;
		AddConfCompere(szAcc, nStatus);
	}
}

void CChatDlg::AddConfMember(const CString& szAcc, int nStatus)
{
	bool bFind = false;
	for (int i=0; i<m_ConfMemList.GetItemCount(); i++)
	{
		CString szAccTemp = m_ConfMemList.GetItemText(i, LIST_NAME);
		if (szAccTemp == szAcc)
		{
			bFind = true;
			m_ConfMemList.SetItem(i, LIST_CALL_STATE_IMAGE, LVIF_TEXT|LVIF_IMAGE, _T(""), nStatus, 0, 0, 0);
			break;
		}
	}

	if (!bFind)
	{
		if (szAcc.IsEmpty())
			return;
		int item = m_ConfMemList.InsertItem(m_ConfMemList.GetItemCount(), _T(""), BITMAP_ConfMan);
		m_ConfMemList.SetItemText(item, LIST_NAME, szAcc);
		AddConfMember(szAcc, nStatus);
	}
}

void CChatDlg::UpdateConfMember(const CString& szAcc, int nStatus)
{
	bool bFind = false;
	for (int i=0; i<m_ConfMemList.GetItemCount(); i++)
	{
		CString szAccTemp = m_ConfMemList.GetItemText(i, LIST_NAME);
		if (szAccTemp == szAcc)
		{
			return;
		}
	}

	if (szAcc.IsEmpty())
		return;
	int item = m_ConfMemList.InsertItem(m_ConfMemList.GetItemCount(), _T(""), BITMAP_ConfMan);
	m_ConfMemList.SetItemText(item, LIST_NAME, szAcc);
}

std::string CChatDlg::CreateConvID()
{
	UCAccountList acclist;
	acclist.iFrom = 0;
	acclist.iTo = 0;
	acclist.iTotal = 1;
	acclist.account = (UCAccount*)malloc(sizeof(UCAccount));
	MemCopy(acclist.account[0].str, m_szTargetAcc, sizeof(acclist.account[0].str));

	char convId[CONVID_LENGTH] = {0};
	if (SendIMMessage("", &acclist, convId))
	{
		MessageBox(_T("Send Message failed."),_T("Failed."),MB_OK);
		return "";
	}
	m_convId = convId;

	return m_convId;
}

std::string CChatDlg::GetModulePath(const CString& dllName)
{
	TCHAR pBuf[MAX_PATH] = {0};
	std::string strTemp;
	GetModuleFileName(::GetModuleHandle(dllName), pBuf, MAX_PATH-sizeof(TCHAR));
	strTemp.append(pBuf);	
	strTemp = strTemp.substr(0,strTemp.rfind('\\')+1);

	return strTemp;
}

std::string CChatDlg::GetDateTimeString()
{
	SYSTEMTIME systime;
	GetSystemTime(&systime);

	CString szTimeString;
	szTimeString.Format(_T("%04d%02d%02d_%02d%02d%02d"),systime.wYear,systime.wMonth,systime.wDay,systime.wHour,systime.wMinute,systime.wSecond);
	return szTimeString.GetBuffer();
}

BOOL CChatDlg::IsMeetingConv()
{
	//这里是用界面判断，如果与会成员列表不为空则是会议，不建议采用这种方式！！！
	return m_ConfMemList.GetItemCount()>0?TRUE:FALSE;
}

void CChatDlg::MemCopy(char* dest, const CString& str, size_t size)
{
	if (NULL == dest || size <= 0)
	{
		return;
	}

	size_t len = (size_t)str.GetLength();

	ZeroMemory(dest, size);
	CopyMemory(dest, str.GetString(), (len < size) ? len : (size-1));
}
