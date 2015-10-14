
// eSDKClientDemoDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "eSDKClientDemo.h"
#include "eSDKClientDemoDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CeSDKClientDemoDlg 对话框

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


// CeSDKClientDemoDlg 消息处理程序

BOOL CeSDKClientDemoDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	m_szSSOSrvUrl = _T("https://10.135.42.58:18643/");
	m_szHostIP= _T("127.0.0.1");
	m_szUpdSrvUrl = _T("http://10.135.43.43:8080/");
	m_szUCSrvUrl = _T("10.170.103.40:8081");
	m_szAccount = _T("yubinbin");
	m_szPasswd = _T("UcAAaa_11");
	m_szToken = _T("eSDK token");
	m_szLang = _T("2052");	//chinese：2052, English：1033 这里默认使用中文

	m_btnInit.EnableWindow(TRUE);
	m_btnUnInit.EnableWindow(FALSE);
	m_btnLoginPasswd.EnableWindow(FALSE);
	m_btnLoginToken.EnableWindow(FALSE);
	m_btnLogout.EnableWindow(FALSE);
	
	m_cmbType.InsertString(0, _T("LoginService"));	//登陆到UC SDK 等产品
	m_cmbType.InsertString(0, _T("LoginSSO"));		//登陆到SSO
	m_iType = 0;
	m_cmbType.SetCurSel(0);

	UpdateData(FALSE);

	m_pUCSDKAbsProxy = NULL;
	m_pUCSignalRecvAbsProxy = NULL;

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

BOOL CeSDKClientDemoDlg::PreTranslateMessage(MSG* pMsg)
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CeSDKClientDemoDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CeSDKClientDemoDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CeSDKClientDemoDlg::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	//如果关闭时没有去初始化，先进行去初始化
	if (m_pUCSDKAbsProxy)
		OnBnClickedButtonUninit();

	CDialog::OnClose();
}

void CeSDKClientDemoDlg::OnBnClickedButtonInit()
{
	// TODO: 在此添加控件通知处理程序代码
	//获取平台实例指针
	m_peSDKClientPlatform = eSDKClientPlatform::getInstance();
	if (NULL == m_peSDKClientPlatform)
	{
		MessageBox(_T("Get eSDKClientPlatform instance failed."), _T("Error"), MB_OK);
		return;
	}

	//设置版本升级服务器和回调函数接口
	m_peSDKClientPlatform->SetMessageCallBack(UpdateVersionCB);
	m_peSDKClientPlatform->setUpdateServer(m_szUpdSrvUrl.GetBuffer());

	//平台初始化，会自动对UC进行初始化
	int iRet = m_peSDKClientPlatform->init();
	if (0 != iRet)
	{
		MessageBox(_T("Init failed."));
		return;
	}

	//设置SSO服务器地址和本地HostIP
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
	// TODO: 在此添加控件通知处理程序代码
	if (m_pCBaseDlg && IsWindow(m_pCBaseDlg->GetSafeHwnd()))
		m_pCBaseDlg->PostMessage(WM_CLOSE);

	//平台去初始化，会对UC进行去初始化，并且释放UCSDK.dll
	int iRet = m_peSDKClientPlatform->uninit();
	if (0 != iRet)
	{
		MessageBox(_T("UnInit failed."));
		return;
	}

	//释放平台实例
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
	// TODO: 在此添加控件通知处理程序代码
	if (m_iType == 0)	//使用用户名和密码登陆SSO服务器
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
	else if (m_iType == 1)	//使用用户名和密码登陆平台业务，这里是UC业务
	{
		//重建界面
		if (m_pCBaseDlg && m_pCBaseDlg->GetSafeHwnd())
		{
			m_pCBaseDlg->DestroyWindow();
			delete m_pCBaseDlg;
		}
		m_pCBaseDlg = new CBaseDlg;
		m_pCBaseDlg->Create(CBaseDlg::IDD, CWnd::GetDesktopWindow());
		m_pCBaseDlg->m_pCeSDKClientDemoDlg = this;
		m_pCBaseDlg->m_szAccount = m_szAccount;

		//设置登录参数
		if (NULL == m_pUCSDKAbsProxy)
		{
			m_pUCSDKAbsProxy = UCSDKAbsProxy::GetInstance();
		}
		m_pUCSDKAbsProxy->Config(m_szUCSrvUrl.GetBuffer());
		m_pUCSDKAbsProxy->SetLang(m_szLang.GetBuffer());

		//设置回调函数
		m_UCSignalRecvProxy.m_pDlg = m_pCBaseDlg;
		m_pUCSDKAbsProxy->SetUCSignalRecvAbsProxy(&m_UCSignalRecvProxy);

		//登录
		int iRet = m_peSDKClientPlatform->login(m_szAccount.GetBuffer(), m_szPasswd.GetBuffer(), m_iType);
		if (0 != iRet)
		{
			MessageBox(_T("login by passwd failed."));
			return;
		}

		m_btnLoginPasswd.EnableWindow(FALSE);
		m_btnLogout.EnableWindow(TRUE);

		//初始化联系人列表和群组列表
		m_pCBaseDlg->InitContactList();
		m_pCBaseDlg->InitGroupList();
		m_pCBaseDlg->ShowWindow(TRUE);
	}
}

void CeSDKClientDemoDlg::OnBnClickedButtonToken()
{
	// TODO: 在此添加控件通知处理程序代码
	//重建界面
	if (m_pCBaseDlg && m_pCBaseDlg->GetSafeHwnd())
	{
		m_pCBaseDlg->DestroyWindow();
		delete m_pCBaseDlg;
	}
	m_pCBaseDlg = new CBaseDlg;
	m_pCBaseDlg->Create(CBaseDlg::IDD, CWnd::GetDesktopWindow());
	m_pCBaseDlg->m_pCeSDKClientDemoDlg = this;
	m_pCBaseDlg->m_szAccount = m_szAccount;

	//设置登录参数
	if (NULL == m_pUCSDKAbsProxy)
	{
		m_pUCSDKAbsProxy = UCSDKAbsProxy::GetInstance();
	}
	m_pUCSDKAbsProxy->Config(m_szUCSrvUrl.GetBuffer());
	m_pUCSDKAbsProxy->SetLang(m_szLang.GetBuffer());

	//设置回调函数
	m_UCSignalRecvProxy.m_pDlg = m_pCBaseDlg;
	m_pUCSDKAbsProxy->SetUCSignalRecvAbsProxy(&m_UCSignalRecvProxy);

	//token登陆
	int iRet = m_peSDKClientPlatform->login(m_szToken.GetBuffer());
	if (0 != iRet)
	{
		MessageBox(_T("login by token failed."), _T("Error"), MB_OK);
		return;
	}

	m_btnLoginToken.EnableWindow(FALSE);
	m_btnLogout.EnableWindow(TRUE);

	//初始化联系人列表和群组列表
	m_pCBaseDlg->InitContactList();
	m_pCBaseDlg->InitGroupList();
	m_pCBaseDlg->ShowWindow(TRUE);
}

void CeSDKClientDemoDlg::OnBnClickedButtonLogout()
{
	// TODO: 在此添加控件通知处理程序代码
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
	// TODO: 在此添加控件通知处理程序代码
	m_iType = m_cmbType.GetCurSel();
}

void CeSDKClientDemoDlg::OnEnChangeEditUrl()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	GetDlgItemText(IDC_EDIT_URL, m_szSSOSrvUrl);
}

void CeSDKClientDemoDlg::OnEnChangeEditHostip()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	GetDlgItemText(IDC_EDIT_HOSTIP, m_szHostIP);
}

void CeSDKClientDemoDlg::OnEnChangeEditUpdatesrv()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	GetDlgItemText(IDC_EDIT_UPDATESRV, m_szUpdSrvUrl);
}

void CeSDKClientDemoDlg::OnEnChangeEditUcurl()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	GetDlgItemText(IDC_EDIT_UCURL, m_szUCSrvUrl);
}

void CeSDKClientDemoDlg::OnEnChangeEditName()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	GetDlgItemText(IDC_EDIT_NAME, m_szAccount);
}

void CeSDKClientDemoDlg::OnEnChangeEditPasswd()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
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
