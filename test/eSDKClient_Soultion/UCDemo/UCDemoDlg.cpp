
// UCDemoDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "UCDemo.h"
#include "UCDemoDlg.h"
#include "SignalMgr.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CUCDemoDlg �Ի���


CUCDemoDlg::CUCDemoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CUCDemoDlg::IDD, pParent)
	, m_szSSOUrl(_T(""))
	, m_szHostIp(_T(""))
	, m_szUpdateUrl(_T(""))
	, m_szUCUrl(_T(""))
	, m_szAccount(_T(""))
	, m_szPasswd(_T(""))
	, m_szToken(_T(""))
	, m_szLang(_T(""))
	, m_pCBaseDlg(NULL)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CUCDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON_INIT, m_btnInit);
	DDX_Control(pDX, IDC_BUTTON_UNINIT, m_btnUnInit);
	DDX_Control(pDX, IDC_BUTTON_PASSWD, m_btnLoginByPwd);
	DDX_Control(pDX, IDC_BUTTON_TOKEN, m_btnLoginByToken);
	DDX_Control(pDX, IDC_BUTTON_LOGOUT, m_btnLogout);
	DDX_Text(pDX, IDC_EDIT_SSOURL, m_szSSOUrl);
	DDX_Text(pDX, IDC_EDIT_HOSTIP, m_szHostIp);
	DDX_Text(pDX, IDC_EDIT_UPDURL, m_szUpdateUrl);
	DDX_Text(pDX, IDC_EDIT_UCURL, m_szUCUrl);
	DDX_Text(pDX, IDC_EDIT_ACCOUNT, m_szAccount);
	DDX_Text(pDX, IDC_EDIT_PASSWD, m_szPasswd);
	DDX_Control(pDX, IDC_COMBO_TYPE, m_cmbLoginType);
	DDX_Text(pDX, IDC_EDIT_TOKEN, m_szToken);
}

BEGIN_MESSAGE_MAP(CUCDemoDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BUTTON_INIT, &CUCDemoDlg::OnBnClickedButtonInit)
	ON_BN_CLICKED(IDC_BUTTON_UNINIT, &CUCDemoDlg::OnBnClickedButtonUninit)
	ON_BN_CLICKED(IDC_BUTTON_PASSWD, &CUCDemoDlg::OnBnClickedButtonPasswd)
	ON_BN_CLICKED(IDC_BUTTON_TOKEN, &CUCDemoDlg::OnBnClickedButtonToken)
	ON_BN_CLICKED(IDC_BUTTON_LOGOUT, &CUCDemoDlg::OnBnClickedButtonLogout)
	ON_EN_CHANGE(IDC_EDIT_SSOURL, &CUCDemoDlg::OnEnChangeEditSsourl)
	ON_EN_CHANGE(IDC_EDIT_HOSTIP, &CUCDemoDlg::OnEnChangeEditHostip)
	ON_EN_CHANGE(IDC_EDIT_UPDURL, &CUCDemoDlg::OnEnChangeEditUpdurl)
	ON_EN_CHANGE(IDC_EDIT_UCURL, &CUCDemoDlg::OnEnChangeEditUcurl)
	ON_EN_CHANGE(IDC_EDIT_ACCOUNT, &CUCDemoDlg::OnEnChangeEditAccount)
	ON_EN_CHANGE(IDC_EDIT_PASSWD, &CUCDemoDlg::OnEnChangeEditPasswd)
	ON_CBN_SELCHANGE(IDC_COMBO_TYPE, &CUCDemoDlg::OnCbnSelchangeComboType)
	ON_MESSAGE(WM_BASE_CLOSE, &CUCDemoDlg::OnMsgBaseDlgClose)
END_MESSAGE_MAP()


// CUCDemoDlg ��Ϣ�������

BOOL CUCDemoDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	m_szSSOUrl = _T("https://10.135.42.58:18643/");	//SSO������
	m_szHostIp = _T("127.0.0.1");
	m_szUpdateUrl = _T("http://10.135.43.43:8080/");//����������
	m_szUCUrl = _T("10.170.103.40:8081");			//UC������
	m_szAccount = _T("yubinbin");	//UC�˺�
	m_szPasswd = _T("UcAAaa_11");	//UC����
	m_szToken = _T("TestToken");	//token������Ĭ������Ϊ��׮��ֵ
	m_szLang = _T("2052");	//chinese��2052, English��1033 ����Ĭ��ʹ������

	m_btnInit.EnableWindow(TRUE);
	m_btnUnInit.EnableWindow(FALSE);
	m_btnLoginByPwd.EnableWindow(FALSE);
	m_btnLoginByToken.EnableWindow(FALSE);
	m_btnLogout.EnableWindow(FALSE);

	m_cmbLoginType.InsertString(0, _T("LoginService"));	//��½��UC SDK �Ȳ�Ʒ
	m_cmbLoginType.InsertString(0, _T("LoginSSO"));		//��½��SSO
	m_cmbLoginType.SetCurSel(0);
	m_iLoginType = 0;

	UpdateData(FALSE);

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

BOOL CUCDemoDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: �ڴ����ר�ô����/����û���

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

void CUCDemoDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CUCDemoDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CUCDemoDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CUCDemoDlg::OnClose()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	CDialog::OnClose();
}

void CUCDemoDlg::OnBnClickedButtonInit()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//���ð汾����������
	int iRet = eSDKClientPlatform_SetUpdateServer(m_szUpdateUrl.GetBuffer());
	if (0 != iRet)
	{
		MessageBox(_T("Set update server url failed."));
		return;
	}

	//���ð汾�����ص�����
	if (!eSDKClientPlatform_SetMessageCallBack(UpdateMessageCallBack))
	{
		MessageBox(_T("Set message call back failed."));
		return;
	}

	//��ʼ���ͻ���ƽ̨������ƽ̨��ʼ��SSO,�汾����,UC�ȣ�
	iRet = eSDKClientPlatform_Init();
	if (0 != iRet)
	{
		MessageBox(_T("Init failed."));
		if (eSDKClientPlatform_Uninit())	//�����ʼ��ʧ�ܣ��п�����SSO,UC,�汾�������м����һ��ʧ�ܣ������û��ʧ�ܵĽ���ȥ��ʼ��
		{
			MessageBox(_T("UnInit failed."));
		}
		return;
	}
	m_btnInit.EnableWindow(FALSE);
	m_btnUnInit.EnableWindow(TRUE);

	//����SSO������
	iRet = eSDKClientPlatform_SetSSOServerUrl(m_szSSOUrl.GetBuffer());
	if (0 != iRet)
	{
		MessageBox(_T("Set SSO server url failed."));
		return;
	}
	//���ñ���IP
	iRet = eSDKClientPlatform_SetHostIP(m_szHostIp.GetBuffer());
	if (0 != iRet)
	{
		MessageBox(_T("setHostIP failed."), _T("Error"), MB_OK);
		return;
	}

	m_btnLoginByPwd.EnableWindow(TRUE);
	m_btnLoginByToken.EnableWindow(TRUE);
}

void CUCDemoDlg::OnBnClickedButtonUninit()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//ȥ��ʼ��
	int iRet = eSDKClientPlatform_Uninit();
	if (0 != iRet)
	{
		MessageBox(_T("UnInit failed."));
		return;
	}

	m_btnInit.EnableWindow(TRUE);
	m_btnUnInit.EnableWindow(FALSE);
	m_btnLoginByPwd.EnableWindow(FALSE);
	m_btnLoginByToken.EnableWindow(FALSE);
}

void CUCDemoDlg::OnBnClickedButtonPasswd()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//ʹ���û����������½SSO
	if (m_iLoginType == 0)
	{
		//��½SSO
		int iRet = eSDKClientPlatform_LoginByPassword(m_szAccount.GetBuffer(), m_szPasswd.GetBuffer(), m_iLoginType);
		if (0 != iRet)
		{
			MessageBox(_T("LoginByPasswd failed."));
			return;
		}
		else
		{
			MessageBox(_T("login SSO successful."));
			return;
		}
	}
	//ʹ���û����������½UC�Ȳ�Ʒ
	else if (m_iLoginType == 1)
	{
		//�������UC�����棬�����٣������½���
		if (m_pCBaseDlg && m_pCBaseDlg->GetSafeHwnd())
		{
			m_pCBaseDlg->DestroyWindow();
			delete m_pCBaseDlg;
			m_pCBaseDlg = NULL;
		}
		m_pCBaseDlg = new CBaseDlg;
		m_pCBaseDlg->Create(CBaseDlg::IDD, CWnd::GetDesktopWindow());
		m_pCBaseDlg->m_pCUCDemoDlg = this;
		m_pCBaseDlg->m_szAccount = m_szAccount;

		//����UC�ص�����
		SetCallBack();
		//����UC������
		int iRet = Config(m_szUCUrl.GetBuffer());
		if (iRet)
		{
			MessageBox(_T("Config failed."),_T("Failed"),MB_OK);
			return;
		}
		//����UC��½����
		iRet = SetLang(m_szLang.GetBuffer());
		if (iRet)
		{
			MessageBox(_T("SetLang failed."),_T("Failed"),MB_OK);
			return;
		}

		//��½UC
		iRet = eSDKClientPlatform_LoginByPassword(m_szAccount.GetBuffer(), m_szPasswd.GetBuffer(), m_iLoginType);
		if (iRet)
		{
			MessageBox(_T("LoginByPasswd failed."));
			return;
		}

		m_btnLoginByPwd.EnableWindow(FALSE);
		m_btnLogout.EnableWindow(TRUE);

		//��ʼ����ϵ���б��Ⱥ���б�
		m_pCBaseDlg->InitContactList();
		m_pCBaseDlg->InitGroupList();

		m_pCBaseDlg->ShowWindow(TRUE);
	}
}

void CUCDemoDlg::OnBnClickedButtonToken()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//�������UC�����棬�����٣������½���
	if (m_pCBaseDlg && m_pCBaseDlg->GetSafeHwnd())
	{
		m_pCBaseDlg->DestroyWindow();
		delete m_pCBaseDlg;
		m_pCBaseDlg = NULL;
	}
	m_pCBaseDlg = new CBaseDlg;
	m_pCBaseDlg->Create(CBaseDlg::IDD, CWnd::GetDesktopWindow());
	m_pCBaseDlg->m_pCUCDemoDlg = this;
	m_pCBaseDlg->m_szAccount = m_szAccount;

	//����UC�ص�����
	SetCallBack();
	//����UC������
	int iRet = Config(m_szUCUrl.GetBuffer());
	if (iRet)
	{
		MessageBox(_T("Config failed."),_T("Failed"),MB_OK);
		return;
	}
	//����UC��½����
	iRet = SetLang(m_szLang.GetBuffer());
	if (iRet)
	{
		MessageBox(_T("SetLang failed."),_T("Failed"),MB_OK);
		return;
	}

	//��½
	iRet = eSDKClientPlatform_LoginByToken(m_szToken.GetBuffer());
	if (0 != iRet)
	{
		m_pCBaseDlg->DestroyWindow();
		delete m_pCBaseDlg;
		m_pCBaseDlg = NULL;

		MessageBox(_T("LoginByToken failed."));
		return;
	}

	//MessageBox(_T("LoginByToken success."));

	m_btnLogout.EnableWindow(TRUE);
	m_btnLoginByToken.EnableWindow(FALSE);

	//��ʼ����ϵ���б��Ⱥ���б�
	m_pCBaseDlg->InitContactList();
	m_pCBaseDlg->InitGroupList();
	m_pCBaseDlg->ShowWindow(TRUE);
}

void CUCDemoDlg::OnBnClickedButtonLogout()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (m_pCBaseDlg && m_pCBaseDlg->GetSafeHwnd())
	{
		if (NULL != m_pCBaseDlg->m_pCUCDemoDlg)
		{
			//�ǳ�
			int iRet = eSDKClientPlatform_Logout();
			if (0 != iRet)
			{
				MessageBox(_T("Logout failed."));
				return;
			}
		}

		m_btnLogout.EnableWindow(FALSE);
		m_btnLoginByPwd.EnableWindow(TRUE);
		m_btnLoginByToken.EnableWindow(TRUE);

		m_pCBaseDlg->DestroyWindow();
		delete m_pCBaseDlg;
		m_pCBaseDlg = NULL;
	}
}

void CUCDemoDlg::OnEnChangeEditSsourl()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialog::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	GetDlgItemText(IDC_EDIT_SSOURL, m_szSSOUrl);
}

void CUCDemoDlg::OnEnChangeEditHostip()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialog::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	GetDlgItemText(IDC_EDIT_HOSTIP, m_szHostIp);
}

void CUCDemoDlg::OnEnChangeEditUpdurl()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialog::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	GetDlgItemText(IDC_EDIT_UPDURL, m_szUpdateUrl);
}

void CUCDemoDlg::OnEnChangeEditUcurl()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialog::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	GetDlgItemText(IDC_EDIT_UCURL, m_szUCUrl);
}

void CUCDemoDlg::OnEnChangeEditAccount()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialog::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	GetDlgItemText(IDC_EDIT_ACCOUNT, m_szAccount);
}

void CUCDemoDlg::OnEnChangeEditPasswd()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialog::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	GetDlgItemText(IDC_EDIT_PASSWD, m_szPasswd);
}

void CUCDemoDlg::OnCbnSelchangeComboType()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_iLoginType = m_cmbLoginType.GetCurSel();
}

LRESULT CUCDemoDlg::OnMsgBaseDlgClose(WPARAM wparam, LPARAM lparam)
{
	//�ǳ�
	OnBnClickedButtonLogout();

	return 0L;
}

void CUCDemoDlg::SetCallBack()
{
	SignalMgr::m_pCBaseDlg = m_pCBaseDlg;
	OnClientSignInNotify(SignalMgr::OnLoginCB);
	OnStatusChanged(SignalMgr::OnStatusCB);
	OnAVSessAdded(SignalMgr::OnAVSessAdded);
	OnAVSessionConnected(SignalMgr::OnAVSessConnected);
	OnAVSessionClosed(SignalMgr::OnAVSessClosed);
	OnReceivedIMMessage(SignalMgr::OnReceivedIM);
	OnConvMemberStatusChanged(SignalMgr::OnConvMemberStatusChanged);
	OnConvMemAllowSpeak(SignalMgr::OnConvMemAllowSpeak);
	OnConvMemForbidSpeak(SignalMgr::OnConvMemForbidSpeak);
	OnConvMemCurSpeaker(SignalMgr::OnConvMemCurSpeaker);
	OnConvGroupMemberChanged(SignalMgr::OnConvGroupMemberChanged);
	OnInstantSessRemoved(SignalMgr::OnInstantSessRemoved);
	OnGroupInvitation(SignalMgr::OnGroupInvitation);
	OnGroupInvitationRes(SignalMgr::OnGroupInvitationRes);
	OnLeaveFromFixedGroup(SignalMgr::OnLeaveFromFixedGroup);
	OnJoinFixedGroupRequest(SignalMgr::OnJoinFixedGroupRequest);
	OnJoinFixedGroupRes(SignalMgr::OnJoinFixedGroupRes);
	OnMemberAdded(SignalMgr::OnMemberAdded);
	OnMemberRemoved(SignalMgr::OnMemberRemoved);
	OnMemberFlowChanged(SignalMgr::OnMemberFlowChanged);
	OnFixedGroupInfoChanged(SignalMgr::OnFixedGroupInfoChanged);
}

bool CALLBACK CUCDemoDlg::UpdateMessageCallBack(int iMsgID, char* pchDescription)
{
	if (iMsgID == 0) //UPDATE_ASK ����ѯ��
	{
		int iRet = ::MessageBox(CWnd::GetDesktopWindow()->GetSafeHwnd(), _T("Do you want to update version?"), _T("Update"), MB_YESNO);
		if (IDYES == iRet)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else if (iMsgID == 1) //UPDATE_START	������ʼ
	{
		::MessageBox(CWnd::GetDesktopWindow()->GetSafeHwnd(), _T("Update start."), _T("Update"), MB_OK);
	}
	else if (iMsgID == 2) //UPDATE_FINISHED �������
	{
		CString szDes(pchDescription);
		::MessageBox(CWnd::GetDesktopWindow()->GetSafeHwnd(), szDes, _T("Update finished"), MB_OK);
	}
	else	//�Ƿ�msgid
	{
		::MessageBox(CWnd::GetDesktopWindow()->GetSafeHwnd(), _T("Error message code."), _T("Update"), MB_OK);
	}

	return true;
}
