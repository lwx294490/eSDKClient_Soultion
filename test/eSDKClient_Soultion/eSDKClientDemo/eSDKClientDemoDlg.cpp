
// eSDKClientDemoDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "eSDKClientDemo.h"
#include "eSDKClientDemoDlg.h"

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


// CeSDKClientDemoDlg �Ի���

CeSDKClientDemoDlg* CeSDKClientDemoDlg::m_pCeSDKClientDemoDlg = NULL;

CeSDKClientDemoDlg::CeSDKClientDemoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CeSDKClientDemoDlg::IDD, pParent)
	, m_szSSOSrvUrl(_T(""))
	, m_szHostIP(_T(""))
	, m_szUpdSrvUrl(_T(""))
	, m_szUCSrvUrl(_T(""))
	, m_szAccount(_T(""))
	, m_szPasswd(_T(""))
	, m_szToken(_T(""))	
	, m_szLang(_T(""))
	, m_pCBaseDlg(NULL)
	, m_peSDKClientPlatform(NULL)
	, m_pUCSDKAbsProxy(NULL)
	, m_pUCSignalRecvAbsProxy(NULL)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CeSDKClientDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_URL, m_szSSOSrvUrl);
	DDX_Text(pDX, IDC_EDIT_HOSTIP, m_szHostIP);
	DDX_Text(pDX, IDC_EDIT_UPDATESRV, m_szUpdSrvUrl);
	DDX_Text(pDX, IDC_EDIT_NAME, m_szAccount);
	DDX_Text(pDX, IDC_EDIT_PASSWD, m_szPasswd);
	DDX_Text(pDX, IDC_EDIT_TOKEN, m_szToken);
	DDX_Control(pDX, IDC_COMBO_TYPE, m_cmbType);
	DDX_Control(pDX, IDC_BUTTON_INIT, m_btnInit);
	DDX_Control(pDX, IDC_BUTTON_UNINIT, m_btnUnInit);
	DDX_Control(pDX, IDC_BUTTON_PASSWD, m_btnLoginPasswd);
	DDX_Control(pDX, IDC_BUTTON_TOKEN, m_btnLoginToken);
	DDX_Control(pDX, IDC_BUTTON_LOGOUT, m_btnLogout);
	DDX_Text(pDX, IDC_EDIT_UCURL, m_szUCSrvUrl);
}

BEGIN_MESSAGE_MAP(CeSDKClientDemoDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON_INIT, &CeSDKClientDemoDlg::OnBnClickedButtonInit)
	ON_BN_CLICKED(IDC_BUTTON_UNINIT, &CeSDKClientDemoDlg::OnBnClickedButtonUninit)
	ON_BN_CLICKED(IDC_BUTTON_PASSWD, &CeSDKClientDemoDlg::OnBnClickedButtonPasswd)
	ON_BN_CLICKED(IDC_BUTTON_TOKEN, &CeSDKClientDemoDlg::OnBnClickedButtonToken)
	ON_BN_CLICKED(IDC_BUTTON_LOGOUT, &CeSDKClientDemoDlg::OnBnClickedButtonLogout)
	ON_CBN_SELCHANGE(IDC_COMBO_TYPE, &CeSDKClientDemoDlg::OnCbnSelchangeComboType)
	ON_EN_CHANGE(IDC_EDIT_URL, &CeSDKClientDemoDlg::OnEnChangeEditUrl)
	ON_EN_CHANGE(IDC_EDIT_HOSTIP, &CeSDKClientDemoDlg::OnEnChangeEditHostip)
	ON_EN_CHANGE(IDC_EDIT_UPDATESRV, &CeSDKClientDemoDlg::OnEnChangeEditUpdatesrv)
	ON_EN_CHANGE(IDC_EDIT_NAME, &CeSDKClientDemoDlg::OnEnChangeEditName)
	ON_EN_CHANGE(IDC_EDIT_PASSWD, &CeSDKClientDemoDlg::OnEnChangeEditPasswd)
	ON_MESSAGE(WM_BASE_CLOSE, &CeSDKClientDemoDlg::OnMsgBaseDlgClose)
	ON_WM_CLOSE()
	ON_EN_CHANGE(IDC_EDIT_UCURL, &CeSDKClientDemoDlg::OnEnChangeEditUcurl)
END_MESSAGE_MAP()


// CeSDKClientDemoDlg ��Ϣ�������

BOOL CeSDKClientDemoDlg::OnInitDialog()
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
	m_szSSOSrvUrl = _T("https://10.135.42.58:18643/");
	m_szHostIP= _T("127.0.0.1");
	m_szUpdSrvUrl = _T("http://10.135.43.43:8080/");
	m_szUCSrvUrl = _T("10.170.103.40:8081");
	m_szAccount = _T("yubinbin");
	m_szPasswd = _T("UcAAaa_11");
	m_szToken = _T("eSDK token");
	m_szLang = _T("2052");	//chinese��2052, English��1033 ����Ĭ��ʹ������

	m_btnInit.EnableWindow(TRUE);
	m_btnUnInit.EnableWindow(FALSE);
	m_btnLoginPasswd.EnableWindow(FALSE);
	m_btnLoginToken.EnableWindow(FALSE);
	m_btnLogout.EnableWindow(FALSE);
	
	m_cmbType.InsertString(0, _T("LoginService"));	//��½��UC SDK �Ȳ�Ʒ
	m_cmbType.InsertString(0, _T("LoginSSO"));		//��½��SSO
	m_iType = 0;
	m_cmbType.SetCurSel(0);

	UpdateData(FALSE);

	m_pUCSDKAbsProxy = NULL;
	m_pUCSignalRecvAbsProxy = NULL;

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

BOOL CeSDKClientDemoDlg::PreTranslateMessage(MSG* pMsg)
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

void CeSDKClientDemoDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CeSDKClientDemoDlg::OnPaint()
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
HCURSOR CeSDKClientDemoDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CeSDKClientDemoDlg::OnClose()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	//����ر�ʱû��ȥ��ʼ�����Ƚ���ȥ��ʼ��
	if (m_pUCSDKAbsProxy)
		OnBnClickedButtonUninit();

	CDialog::OnClose();
}

void CeSDKClientDemoDlg::OnBnClickedButtonInit()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//��ȡƽ̨ʵ��ָ��
	m_peSDKClientPlatform = eSDKClientPlatform::getInstance();
	if (NULL == m_peSDKClientPlatform)
	{
		MessageBox(_T("Get eSDKClientPlatform instance failed."), _T("Error"), MB_OK);
		return;
	}

	//���ð汾�����������ͻص������ӿ�
	m_peSDKClientPlatform->SetMessageCallBack(UpdateVersionCB);
	m_peSDKClientPlatform->setUpdateServer(m_szUpdSrvUrl.GetBuffer());

	//ƽ̨��ʼ�������Զ���UC���г�ʼ��
	int iRet = m_peSDKClientPlatform->init();
	if (0 != iRet)
	{
		MessageBox(_T("Init failed."));
		return;
	}

	//����SSO��������ַ�ͱ���HostIP
	iRet = m_peSDKClientPlatform->setConfig(m_szSSOSrvUrl.GetBuffer());
	if (0 != iRet)
	{
		MessageBox(_T("setConfig failed."));
		return;
	}
	iRet = m_peSDKClientPlatform->setHostIP(m_szHostIP.GetBuffer());
	if (0 != iRet)
	{
		MessageBox(_T("setHostIP failed."));
		return;
	}

	m_btnInit.EnableWindow(FALSE);
	m_btnUnInit.EnableWindow(TRUE);
	m_btnLoginPasswd.EnableWindow(TRUE);
	m_btnLoginToken.EnableWindow(TRUE);
	m_btnLogout.EnableWindow(FALSE);
}

void CeSDKClientDemoDlg::OnBnClickedButtonUninit()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (m_pCBaseDlg && IsWindow(m_pCBaseDlg->GetSafeHwnd()))
		m_pCBaseDlg->PostMessage(WM_CLOSE);

	//ƽ̨ȥ��ʼ�������UC����ȥ��ʼ���������ͷ�UCSDK.dll
	int iRet = m_peSDKClientPlatform->uninit();
	if (0 != iRet)
	{
		MessageBox(_T("UnInit failed."));
		return;
	}

	//�ͷ�ƽ̨ʵ��
	eSDKClientPlatform::ReleaseInstance();
	m_peSDKClientPlatform = NULL;
	m_pUCSDKAbsProxy = NULL;
	m_pUCSignalRecvAbsProxy = NULL;

	m_btnInit.EnableWindow(TRUE);
	m_btnUnInit.EnableWindow(FALSE);
	m_btnLoginPasswd.EnableWindow(FALSE);
	m_btnLoginToken.EnableWindow(FALSE);
	m_btnLogout.EnableWindow(FALSE);
}

void CeSDKClientDemoDlg::OnBnClickedButtonPasswd()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (m_iType == 0)	//ʹ���û����������½SSO������
	{
		int iRet = m_peSDKClientPlatform->login(m_szAccount.GetBuffer(), m_szPasswd.GetBuffer(), m_iType);
		if (0 != iRet)
		{
			MessageBox(_T("login SSO by passwd failed."));
			return;
		}
		else
		{
			MessageBox(_T("login SSO successful."));
		}
	}
	else if (m_iType == 1)	//ʹ���û����������½ƽ̨ҵ��������UCҵ��
	{
		//�ؽ�����
		if (m_pCBaseDlg && m_pCBaseDlg->GetSafeHwnd())
		{
			m_pCBaseDlg->DestroyWindow();
			delete m_pCBaseDlg;
		}
		m_pCBaseDlg = new CBaseDlg;
		m_pCBaseDlg->Create(CBaseDlg::IDD, CWnd::GetDesktopWindow());
		m_pCBaseDlg->m_pCeSDKClientDemoDlg = this;
		m_pCBaseDlg->m_szAccount = m_szAccount;

		//���õ�¼����
		if (NULL == m_pUCSDKAbsProxy)
		{
			m_pUCSDKAbsProxy = UCSDKAbsProxy::GetInstance();
		}
		m_pUCSDKAbsProxy->Config(m_szUCSrvUrl.GetBuffer());
		m_pUCSDKAbsProxy->SetLang(m_szLang.GetBuffer());

		//���ûص�����
		m_UCSignalRecvProxy.m_pDlg = m_pCBaseDlg;
		m_pUCSDKAbsProxy->SetUCSignalRecvAbsProxy(&m_UCSignalRecvProxy);

		//��¼
		int iRet = m_peSDKClientPlatform->login(m_szAccount.GetBuffer(), m_szPasswd.GetBuffer(), m_iType);
		if (0 != iRet)
		{
			MessageBox(_T("login by passwd failed."));
			return;
		}

		m_btnLoginPasswd.EnableWindow(FALSE);
		m_btnLogout.EnableWindow(TRUE);

		//��ʼ����ϵ���б��Ⱥ���б�
		m_pCBaseDlg->InitContactList();
		m_pCBaseDlg->InitGroupList();
		m_pCBaseDlg->ShowWindow(TRUE);
	}
}

void CeSDKClientDemoDlg::OnBnClickedButtonToken()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//�ؽ�����
	if (m_pCBaseDlg && m_pCBaseDlg->GetSafeHwnd())
	{
		m_pCBaseDlg->DestroyWindow();
		delete m_pCBaseDlg;
	}
	m_pCBaseDlg = new CBaseDlg;
	m_pCBaseDlg->Create(CBaseDlg::IDD, CWnd::GetDesktopWindow());
	m_pCBaseDlg->m_pCeSDKClientDemoDlg = this;
	m_pCBaseDlg->m_szAccount = m_szAccount;

	//���õ�¼����
	if (NULL == m_pUCSDKAbsProxy)
	{
		m_pUCSDKAbsProxy = UCSDKAbsProxy::GetInstance();
	}
	m_pUCSDKAbsProxy->Config(m_szUCSrvUrl.GetBuffer());
	m_pUCSDKAbsProxy->SetLang(m_szLang.GetBuffer());

	//���ûص�����
	m_UCSignalRecvProxy.m_pDlg = m_pCBaseDlg;
	m_pUCSDKAbsProxy->SetUCSignalRecvAbsProxy(&m_UCSignalRecvProxy);

	//token��½
	int iRet = m_peSDKClientPlatform->login(m_szToken.GetBuffer());
	if (0 != iRet)
	{
		MessageBox(_T("login by token failed."), _T("Error"), MB_OK);
		return;
	}

	m_btnLoginToken.EnableWindow(FALSE);
	m_btnLogout.EnableWindow(TRUE);

	//��ʼ����ϵ���б��Ⱥ���б�
	m_pCBaseDlg->InitContactList();
	m_pCBaseDlg->InitGroupList();
	m_pCBaseDlg->ShowWindow(TRUE);
}

void CeSDKClientDemoDlg::OnBnClickedButtonLogout()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (m_pCBaseDlg && m_pCBaseDlg->GetSafeHwnd())
	{
		if (NULL != m_pCBaseDlg->m_pCeSDKClientDemoDlg)
		{
			int iRet = m_peSDKClientPlatform->logout();
			if (0 != iRet)
			{
				MessageBox(_T("Logout failed."));
			}
		}

		m_btnInit.EnableWindow(FALSE);
		m_btnUnInit.EnableWindow(TRUE);
		m_btnLoginPasswd.EnableWindow(TRUE);
		m_btnLoginToken.EnableWindow(TRUE);
		m_btnLogout.EnableWindow(FALSE);

		m_pCBaseDlg->DestroyWindow();
		delete m_pCBaseDlg;
		m_pCBaseDlg = NULL;
	}
}

void CeSDKClientDemoDlg::OnCbnSelchangeComboType()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_iType = m_cmbType.GetCurSel();
}

void CeSDKClientDemoDlg::OnEnChangeEditUrl()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialog::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	GetDlgItemText(IDC_EDIT_URL, m_szSSOSrvUrl);
}

void CeSDKClientDemoDlg::OnEnChangeEditHostip()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialog::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	GetDlgItemText(IDC_EDIT_HOSTIP, m_szHostIP);
}

void CeSDKClientDemoDlg::OnEnChangeEditUpdatesrv()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialog::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	GetDlgItemText(IDC_EDIT_UPDATESRV, m_szUpdSrvUrl);
}

void CeSDKClientDemoDlg::OnEnChangeEditUcurl()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialog::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	GetDlgItemText(IDC_EDIT_UCURL, m_szUCSrvUrl);
}

void CeSDKClientDemoDlg::OnEnChangeEditName()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialog::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	GetDlgItemText(IDC_EDIT_NAME, m_szAccount);
}

void CeSDKClientDemoDlg::OnEnChangeEditPasswd()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialog::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	GetDlgItemText(IDC_EDIT_PASSWD, m_szPasswd);
}

LRESULT CeSDKClientDemoDlg::OnMsgBaseDlgClose(WPARAM wParm, LPARAM Lparam)
{
	OnBnClickedButtonLogout();

	return 0L;
}

bool CALLBACK CeSDKClientDemoDlg::UpdateVersionCB(int iMsgID, std::string strDes)
{
	if (iMsgID == 0) //UPDATE_ASK
	{
		int iRet = ::MessageBox(m_pCeSDKClientDemoDlg->GetSafeHwnd(), _T("Do you want to update version?"), _T("Update"), MB_YESNO);
		if (IDYES == iRet)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else if (iMsgID == 1) //UPDATE_START
	{
		::MessageBox(m_pCeSDKClientDemoDlg->GetSafeHwnd(), _T("Update start."), _T("Update"), MB_OK);
	}
	else if (iMsgID == 2) //UPDATE_FINISHED
	{
		CString szDes(strDes.c_str());
		::MessageBox(m_pCeSDKClientDemoDlg->GetSafeHwnd(), szDes, _T("Update finished"), MB_OK);
	}
	else
	{
		::MessageBox(m_pCeSDKClientDemoDlg->GetSafeHwnd(), _T("Error message code."), _T("Update"), MB_OK);
	}

	return true;
}
