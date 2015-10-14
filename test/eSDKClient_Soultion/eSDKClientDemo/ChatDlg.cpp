// ChatDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "eSDKClientDemo.h"
#include "ChatDlg.h"
#include "CodeTools.h"
#include "BaseDlg.h"

#include <strstream>

// CChatDlg �Ի���

IMPLEMENT_DYNAMIC(CChatDlg, CDialog)

CChatDlg::CChatDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CChatDlg::IDD, pParent)
	, m_szAccount(_T(""))
	, m_szCompere(_T(""))
	, m_szTargetAcc(_T(""))
	, m_convId("")
	, m_pCBaseDlg(NULL)
	, m_pCInputDlg(NULL)
	, m_pUCIMAbsProxy(NULL)
	, m_pUCVoIPAbsProxy(NULL)
	, m_pUCMeetingAbsProxy(NULL)
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

	//���ó�Ա�б���Ϊ��ѡģʽ
	m_ConfMemList.ModifyStyle(0,LVS_SINGLESEL);
	//�����б�ͷ
	m_ConfMemList.InsertColumn(LIST_NAME, _T("Name"), LVCFMT_LEFT, WIDTH_MEMBER_NAME);
	m_ConfMemList.InsertColumn(LIST_COMPERE_IMAGE, _T("Compere"), LVCFMT_LEFT, WIDTH_MEMBER_COMPERE_IMAGE);
	m_ConfMemList.InsertColumn(LIST_CALL_STATE_IMAGE, _T("ConfStatus"), LVCFMT_LEFT, WIDTH_MEMBER_CALLSTATE_IMAGE);
	m_ConfMemList.InsertColumn(LIST_SPEAKING, _T("Speaking"), LVCFMT_LEFT, WIDTH_MEMBER_SPEAKING);

	//ͼƬ�б������ڵ����б��е������л���ͬ��ͼ��
	m_lstImage.Create(20, 20, ILC_COLORDDB, 10, 1);//10��20*20��ͼ��
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

	//����List���:ȫѡ������֧��ͼƬ
	m_ConfMemList.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_HEADERDRAGDROP | LVS_EX_SUBITEMIMAGES | LVS_EX_INFOTIP);

	//�������յ�richedit�ؼ�
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

	m_pUCIMAbsProxy = UCIMAbsProxy::GetInstance();
	m_pUCVoIPAbsProxy = UCVoIPAbsProxy::GetInstance();
	m_pUCMeetingAbsProxy = UCMeetingAbsProxy::GetInstance();

	return TRUE;
}

BOOL CChatDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: �ڴ�����ר�ô����/����û���
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

// CChatDlg ��Ϣ��������

void CChatDlg::OnClose()
{
	// TODO: �ڴ�������Ϣ������������/�����Ĭ��ֵ

	//�رջỰ
	if (!m_convId.empty() && m_pUCIMAbsProxy->CloseConversation(m_convId))
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

	m_pUCIMAbsProxy = NULL;
	m_pUCVoIPAbsProxy = NULL;
	m_pUCMeetingAbsProxy = NULL;

	CDialog::OnClose();
}

void CChatDlg::OnBnClickedButtonHold()
{
	// TODO: �ڴ����ӿؼ�֪ͨ�����������
	//���б���
	if (m_pUCVoIPAbsProxy->Hold(m_convId))
	{
		MessageBox(_T("Hold call failed."),_T("Failed"),MB_OK);
		return;
	}

	m_btnHold.EnableWindow(FALSE);
	m_btnResume.EnableWindow(TRUE);
}

void CChatDlg::OnBnClickedButtonResume()
{
	// TODO: �ڴ����ӿؼ�֪ͨ�����������
	//���лָ�
	if (m_pUCVoIPAbsProxy->Resume(m_convId))
	{
		MessageBox(_T("Resume call failed."),_T("Failed"),MB_OK);
		return;
	}

	m_btnHold.EnableWindow(TRUE);
	m_btnResume.EnableWindow(FALSE);
}

void CChatDlg::OnBnClickedButtonStartRecord()
{
	// TODO: �ڴ����ӿؼ�֪ͨ�����������

	//��ȡ¼��Ŀ¼
	std::string dllPath = GetModulePath(_T("UCSDK.dll"));
	std::string recordPath = dllPath;
	recordPath.append(_T("\\UserData\\"));
	recordPath.append(m_szAccount.GetBuffer());
	recordPath.append(_T("\\RecordFile\\"));

	//����¼���ļ���
	std::string recordName = GetDateTimeString();
	recordPath.append(recordName);

	if (m_bIsVideo)
	{
		recordPath.append(_T(".avi"));
	}
	else
	{
		recordPath.append(_T(".wav"));
	}

	// �ַ���װ��
	std::string sRecordPath = ANSIToUTF8(recordPath.c_str());

	//��ʼ¼��
	int iRet = m_pUCVoIPAbsProxy->StartRecord(m_convId, sRecordPath);
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
	// TODO: �ڴ����ӿؼ�֪ͨ�����������
	//ֹͣ¼��
	int iRet = m_pUCVoIPAbsProxy->StopRecord(m_convId);
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
	// TODO: �ڴ����ӿؼ�֪ͨ�����������
	if (m_pUCVoIPAbsProxy->Mute(Dev_Mic))
	{
		MessageBox(_T("Mic mute failed."),_T("Failed"),MB_OK);
		return;
	}
	m_btnMicMute.EnableWindow(FALSE);
	m_btnMicUnMute.EnableWindow(TRUE);
}

void CChatDlg::OnBnClickedButtonMicunmute()
{
	// TODO: �ڴ����ӿؼ�֪ͨ�����������
	if (m_pUCVoIPAbsProxy->UnMute(Dev_Mic))
	{
		MessageBox(_T("Mic unmute failed."),_T("Failed"),MB_OK);
		return;
	}
	m_btnMicMute.EnableWindow(TRUE);
	m_btnMicUnMute.EnableWindow(FALSE);
}

void CChatDlg::OnBnClickedButtonSpkmute()
{
	// TODO: �ڴ����ӿؼ�֪ͨ�����������
	if (m_pUCVoIPAbsProxy->Mute(Dev_Speaker))
	{
		MessageBox(_T("Speaker mute failed."),_T("Failed"),MB_OK);
		return;
	}
	m_btnSpkMute.EnableWindow(FALSE);
	m_btnSpkUnMute.EnableWindow(TRUE);
}

void CChatDlg::OnBnClickedButtonSpkunmute()
{
	// TODO: �ڴ����ӿؼ�֪ͨ�����������
	if (m_pUCVoIPAbsProxy->UnMute(Dev_Speaker))
	{
		MessageBox(_T("Speaker unmute failed."),_T("Failed"),MB_OK);
		return;
	}
	m_btnSpkMute.EnableWindow(TRUE);
	m_btnSpkUnMute.EnableWindow(FALSE);
}

void CChatDlg::OnBnClickedButtonAdd()
{
	// TODO: �ڴ����ӿؼ�֪ͨ�����������
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
	// TODO: �ڴ����ӿؼ�֪ͨ�����������
	AccountList acclist;
	if (m_convId.empty())	//�����ǰ�����ڻỰ������Ҫ����AccountList
	{
		//����ǻ���
		if (IsMeetingConv())
		{
			for (int i=0; i<m_ConfMemList.GetItemCount(); i++)
			{
				CString szAccTemp = m_ConfMemList.GetItemText(i, LIST_NAME);
				if (szAccTemp == m_szAccount)	//AccountList�������Լ�
				{ 
					continue;
				}
				acclist.push_back(szAccTemp.GetBuffer());
			}
		}
		//����ǵ�Ե�
		else
		{
			acclist.push_back(m_szTargetAcc.GetBuffer());
		}
	}

	CString szSendMsg;
	m_RichSendMsg.GetWindowText(szSendMsg);
	if (szSendMsg.IsEmpty())
		return;

	/************************************************************************/
	/*	IM ��ʽ
	/*	<imbody>
	/*	<imagelist>
	/*	<img>
	/*	<imgname>ͼƬ��</imgname>
	/*	<imgdata>ͼƬ����</imgdata>
	/*	</img>
	/*	����
	/*	</imagelist>
	/*	<content>���ı�+����ת���</content>
	/*	<html>html��Ϣ��</html>
	/*	</imbody>
	/************************************************************************/

	//IM ����
	CString szFont(_T("<FONT style='font-size:18px' face='΢���ź�' color='0000ff'><B>"));
	szFont.Append(szSendMsg);
	szFont.Append(_T("</FONT>"));

	std::string sImage = "";
	std::string sMsg = ANSIToUTF8(szSendMsg.GetString());
	std::string sFont = ANSIToUTF8(szFont.GetString());

	//ƴ��IM��ʽ
	std::ostrstream OutMsgXML;
	OutMsgXML << "<imbody>";
	OutMsgXML << "<imagelist>" << sImage << "</imagelist>";
	OutMsgXML << "<html><![CDATA[" << sFont.c_str() << "]]></html>";
	OutMsgXML << "<content>" << sMsg.c_str() << "</content>";
	OutMsgXML << "</imbody>";
	OutMsgXML << std::ends;

	if (m_pUCIMAbsProxy->SendIMMessage(OutMsgXML.str(), acclist, m_convId))
	{
		MessageBox(_T("Send Message failed."),_T("Failed."),MB_OK);
		return;
	}

	//��շ�����
	m_RichSendMsg.SetSel(0, -1);
	m_RichSendMsg.ReplaceSel(_T(""));

	//�����ͳ�ȥ����Ϣ��ʾ����Ϣ������
	SYSTEMTIME time;
	GetSystemTime(&time);
	CString szTime;
	szTime.Format("  %4d-%02d-%02d %02d:%02d:%02d", time.wYear, time.wMonth, time.wDay, time.wHour, time.wMinute, time.wSecond);
	CString cstrHead = m_szAccount+szTime;

	m_RichRecvMsg.SetSel(-1, -1);
	m_RichRecvMsg.ReplaceSel(cstrHead + _T("\r\n") + szSendMsg);
	m_RichRecvMsg.SetSel(-1, -1);
	m_RichRecvMsg.ReplaceSel(_T("\r\n"),TRUE);
	m_RichRecvMsg.UpdateData(FALSE);
}

void CChatDlg::OnBnClickedButtonCall()
{
	// TODO: �ڴ����ӿؼ�֪ͨ�����������
	//conference call	������У�ǰ����MakeMeetingGroup��
	if (IsMeetingConv())
	{
		if (m_pUCMeetingAbsProxy->StartMeeting(m_convId))
		{
			MessageBox(_T("StartMeeting failed."),_T("Failed"),MB_OK);
			return;
		}
		for (int i=0; i<m_ConfMemList.GetItemCount(); i++)
		{
			CString szAcc = m_ConfMemList.GetItemText(i, LIST_NAME);
			UpdateConfMemList(szAcc, Conf_Inviting);
		}
	}
	//voip call	��Ե����
	else
	{
		UCSDKContact member;
		member.ucAcc_ = m_szTargetAcc.GetBuffer();

		STVideoWindow local;
		STVideoWindow remote;
		memset(&local, 0, sizeof(local));
		memset(&remote, 0, sizeof(remote));
		if (m_pUCVoIPAbsProxy->MakeCall(m_convId, member, Call_Audio, local, remote))
		{
			MessageBox(_T("Make Call failed."),_T("Failed"),MB_OK);
			return;
		}		
	}

	//����æµ״̬
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
	// TODO: �ڴ����ӿؼ�֪ͨ�����������

	//����ǻ��鲻�ܽ�����Ƶ����
	if (IsMeetingConv())
	{
		MessageBox(_T("can't make video call in conference."),_T("Error"),MB_OK);
		return;
	}

	UCSDKContact member;
	member.ucAcc_ = m_szTargetAcc.GetBuffer();

	CRect rectLocat;
	m_stLocal.GetClientRect(&rectLocat);
	ClientToScreen(&rectLocat);
	CRect rectRemote;
	m_stRemote.GetClientRect(&rectRemote);
	ClientToScreen(&rectRemote);

	STVideoWindow local;
	local.hWnd = (int)m_stLocal.GetSafeHwnd();
	local.height = rectLocat.Height();
	local.width = rectLocat.Width();
	local.top = rectLocat.top;
	local.left = rectLocat.left;
	STVideoWindow remote;
	remote.hWnd = (int)m_stRemote.GetSafeHwnd();
	remote.height = rectRemote.Height();
	remote.width = rectRemote.Width();
	remote.top = rectRemote.top;
	remote.left = rectRemote.left;

	if (m_pUCVoIPAbsProxy->MakeCall(m_convId, member, Call_Video, local, remote))
	{
		MessageBox(_T("Make Call failed."),_T("Failed"),MB_OK);
		return;
	}

	//����æµ״̬
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
	// TODO: �ڴ����ӿؼ�֪ͨ�����������
	if (m_pUCVoIPAbsProxy->Hangup(m_convId, Call_Audio))
	{
		MessageBox(_T("Hangup failed."),_T("Failed"),MB_OK);
		return;
	}

	//hangup conference ����ǻ���Ҷ�������Ҫ�޸Ľ�������Ա״̬��ʾ
	if (IsMeetingConv())
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

	//��������״̬
	CBaseDlg* pDlg = dynamic_cast<CBaseDlg*>(m_pCBaseDlg);
	if (pDlg)
	{
		pDlg->PublishSelfState(1);
	}
}

void CChatDlg::OnNMRClickListCont(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: �ڴ����ӿؼ�֪ͨ�����������
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

	//�����˵������²˵�
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
		//�Ƴ������
	case ID_MENU_DELETE_MEM:
		{
			UCSDKContact member;
			member.ucAcc_ = szAcc.GetBuffer();
			if (m_pUCMeetingAbsProxy->RemoveParticipant(member, m_convId))
			{
				MessageBox(_T("RemoveParticipant failed."),_T("Failed"),MB_OK);
				return;
			}
			UpdateConfMemList(szAcc, Conf_MemDel);
		}
		break;
		//�Ҷ������
	case ID_MENU_ENDCALL_MEM:
		{
			UCSDKContact member;
			member.ucAcc_ = szAcc.GetBuffer();
			if (m_pUCMeetingAbsProxy->KickParticipant(member, m_convId))
			{
				MessageBox(_T("KickParticipant failed."),_T("Failed"),MB_OK);
				return;
			}
		}
		break;
		//�������������
	case ID_MENU_REINVITE_MEM:
		{
			UCSDKContact member;
			member.ucAcc_ = szAcc.GetBuffer();
			if (m_pUCMeetingAbsProxy->ConnectParticipant(member, m_convId))
			{
				MessageBox(_T("ConnectParticipant failed."),_T("Failed"),MB_OK);
				return;
			}
			UpdateConfMemList(szAcc, Conf_Inviting);
		}
		break;
		//��ֹ����˷���
	case ID_MENU_MUTE_MEM:
		{
			UCSDKContact member;
			member.ucAcc_ = szAcc.GetBuffer();
			if (m_pUCMeetingAbsProxy->Mute(member, m_convId))
			{
				MessageBox(_T("Mute failed."),_T("Failed"),MB_OK);
				return;
			}
		}
		break;
		//��������˷���
	case ID_MENU_UNMUTE_MEM:
		{
			UCSDKContact member;
			member.ucAcc_ = szAcc.GetBuffer();
			if (m_pUCMeetingAbsProxy->UnMute(member, m_convId))
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

	//���û�лỰ���ȴ�����ʱ��
	if (m_convId.empty())
	{
		UCSDKContactList memberlist;
		UCSDKContact member;
		member.ucAcc_ = m_szTargetAcc.GetBuffer();
		memberlist.push_back(member);
		member.ucAcc_ = pInputInfo->szInput.GetBuffer();
		memberlist.push_back(member);

		if (m_pUCMeetingAbsProxy->MakeMeetingGroup(memberlist,m_convId))
		{
			MessageBox(_T("Make meeting failed."),_T("Failed"),MB_OK);
			delete pInputInfo;
			return -1L;
		}

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
	//������лỰ����ֱ����������Ա
	else
	{
		// �Ƿ��Ѿ�����
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

		UCSDKContact member;
		member.ucAcc_ = pInputInfo->szInput.GetBuffer();
		if (m_pUCMeetingAbsProxy->AddParticipant(member, m_convId))
		{
			MessageBox(_T("AddParticipant failed."),_T("Failed"),MB_OK);
			delete pInputInfo;
			return -1L;
		}
		if (m_ConfMemList.GetItemCount() == 0)
		{
			AddConfCompere(m_szAccount, -1);
			AddConfMember(m_szTargetAcc, -1);
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
	/*	IM ��ʽ
	/*	<imbody>
	/*	<imagelist>
	/*	<img>
	/*	<imgname>ͼƬ��</imgname>
	/*	<imgdata>ͼƬ����</imgdata>
	/*	</img>
	/*	����
	/*	</imagelist>
	/*	<content>���ı�+����ת���</content>
	/*	<html>html��Ϣ��</html>
	/*	</imbody>
	/************************************************************************/

	//����ֻȡ<content></content>֮��Ĵ��ı��������Ҫȡ�����͵��ı������ʽ����ʹ��<html>��</html>֮��ģ����н�����
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
			case Conf_Inviting:			//���ں���ĳ��Ա
				{
					m_ConfMemList.SetItem(i, LIST_CALL_STATE_IMAGE, LVIF_TEXT|LVIF_IMAGE, _T(""), BITMAP_CallIng, 0, 0, 0);
				}
				break;
			case Conf_Hangup:			//ĳ��Ա�Ҷ�
				{
					m_ConfMemList.SetItem(i, LIST_CALL_STATE_IMAGE, LVIF_TEXT|LVIF_IMAGE, _T(""), BITMAP_CallMiss, 0, 0, 0);
				}
				break;
			case Conf_InConf:			//���ڻ�����
				{
					m_ConfMemList.SetItem(i, LIST_CALL_STATE_IMAGE, LVIF_TEXT|LVIF_IMAGE, _T(""), BITMAP_CallEst, 0, 0, 0);
				}
				break;
			case Conf_Quit:				//��Ա�뿪
				{
					m_ConfMemList.SetItem(i, LIST_CALL_STATE_IMAGE, LVIF_TEXT|LVIF_IMAGE, _T(""), BITMAP_CallLeave, 0, 0, 0);
				}
				break;
			case Conf_ForbidSpk:		//��Ա������
				{
					m_ConfMemList.SetItem(i, LIST_CALL_STATE_IMAGE, LVIF_TEXT|LVIF_IMAGE, _T(""), BITMAP_MicMute, 0, 0, 0);
				}
				break;
			case Conf_AllowSpk:			//��Ա��ȡ������
				{
					m_ConfMemList.SetItem(i, LIST_CALL_STATE_IMAGE, LVIF_TEXT|LVIF_IMAGE, _T(""), BITMAP_MicUnMute, 0, 0, 0);
				}
				break;
			case Conf_CurSpker:			//��Ա��˵��
				{
					m_ConfMemList.SetItem(i, LIST_SPEAKING, LVIF_TEXT|LVIF_IMAGE, _T(""), BITMAP_Speaker, 0, 0, 0);
				}
				break;
			case Conf_MemAdd:			//������Ա
				{
					m_ConfMemList.SetItem(i, LIST_CALL_STATE_IMAGE, LVIF_TEXT|LVIF_IMAGE, _T(""), -1/*BITMAP_CallIng*/, 0, 0, 0);
				}
				break;
			case Conf_MemDel:			//��Ա��ɾ��
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

	// ��ǰ������״̬����
	if (Conf_CurSpker == nStatus)
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

	//�����������б�����û���ҵ�������������б��������Ӹ�����ˡ�
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
	//�������ý����жϣ��������Ա�б���Ϊ�����ǻ��飬������������ַ�ʽ������
	return m_ConfMemList.GetItemCount()>0?TRUE:FALSE;
}

std::string CChatDlg::CreateConvID()
{
	AccountList acclist;
	acclist.push_back(m_szTargetAcc.GetBuffer());
	if (m_pUCIMAbsProxy->SendIMMessage("", acclist, m_convId))
	{
		MessageBox(_T("Send Message failed."),_T("Failed."),MB_OK);
		return "";
	}

	return m_convId;
}