
// UCDemoDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "UCDemo.h"
#include "UCDemoDlg.h"
#include "SignalMgr.h"

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


// CUCDemoDlg 对话框


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


// CUCDemoDlg 消息处理程序

BOOL CUCDemoDlg::OnInitDialog()
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
	m_szSSOUrl = _T("https://10.135.42.58:18643/");	//SSO服务器
	m_szHostIp = _T("127.0.0.1");
	m_szUpdateUrl = _T("http://10.135.43.43:8080/");//升级服务器
	m_szUCUrl = _T("10.170.103.40:8081");			//UC服务器
	m_szAccount = _T("yubinbin");	//UC账号
	m_szPasswd = _T("UcAAaa_11");	//UC密码
	m_szToken = _T("TestToken");	//token，这里默认设置为打桩数值
	m_szLang = _T("2052");	//chinese：2052, English：1033 这里默认使用中文

	m_btnInit.EnableWindow(TRUE);
	m_btnUnInit.EnableWindow(FALSE);
	m_btnLoginByPwd.EnableWindow(FALSE);
	m_btnLoginByToken.EnableWindow(FALSE);
	m_btnLogout.EnableWindow(FALSE);

	m_cmbLoginType.InsertString(0, _T("LoginService"));	//登陆到UC SDK 等产品
	m_cmbLoginType.InsertString(0, _T("LoginSSO"));		//登陆到SSO
	m_cmbLoginType.SetCurSel(0);
	m_iLoginType = 0;

	UpdateData(FALSE);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

BOOL CUCDemoDlg::PreTranslateMessage(MSG* pMsg)
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CUCDemoDlg::OnPaint()
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
HCURSOR CUCDemoDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CUCDemoDlg::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CDialog::OnClose();
}

void CUCDemoDlg::OnBnClickedButtonInit()
{
	// TODO: 在此添加控件通知处理程序代码
	//设置版本升级服务器
	int iRet = eSDKClientPlatform_SetUpdateServer(m_szUpdateUrl.GetBuffer());
	if (0 != iRet)
	{
		MessageBox(_T("Set update server url failed."));
		return;
	}

	//设置版本升级回调函数
	if (!eSDKClientPlatform_SetMessageCallBack(UpdateMessageCallBack))
	{
		MessageBox(_T("Set message call back failed."));
		return;
	}

	//初始化客户端平台（会由平台初始化SSO,版本升级,UC等）
	iRet = eSDKClientPlatform_Init();
	if (0 != iRet)
	{
		MessageBox(_T("Init failed."));
		if (eSDKClientPlatform_Uninit())	//如果初始化失败，有可能是SSO,UC,版本升级等中间的任一个失败，这里对没有失败的进行去初始化
		{
			MessageBox(_T("UnInit failed."));
		}
		return;
	}
	m_btnInit.EnableWindow(FALSE);
	m_btnUnInit.EnableWindow(TRUE);

	//设置SSO服务器
	iRet = eSDKClientPlatform_SetSSOServerUrl(m_szSSOUrl.GetBuffer());
	if (0 != iRet)
	{
		MessageBox(_T("Set SSO server url failed."));
		return;
	}
	//设置本地IP
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
	// TODO: 在此添加控件通知处理程序代码
	//去初始化
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
	// TODO: 在此添加控件通知处理程序代码
	//使用用户名和密码登陆SSO
	if (m_iLoginType == 0)
	{
		//登陆SSO
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
	//使用用户名和密码登陆UC等产品
	else if (m_iLoginType == 1)
	{
		//如果存在UC主界面，先销毁，再重新建立
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

		//设置UC回调函数
		SetCallBack();
		//设置UC服务器
		int iRet = Config(m_szUCUrl.GetBuffer());
		if (iRet)
		{
			MessageBox(_T("Config failed."),_T("Failed"),MB_OK);
			return;
		}
		//设置UC登陆语言
		iRet = SetLang(m_szLang.GetBuffer());
		if (iRet)
		{
			MessageBox(_T("SetLang failed."),_T("Failed"),MB_OK);
			return;
		}

		//登陆UC
		iRet = eSDKClientPlatform_LoginByPassword(m_szAccount.GetBuffer(), m_szPasswd.GetBuffer(), m_iLoginType);
		if (iRet)
		{
			MessageBox(_T("LoginByPasswd failed."));
			return;
		}

		m_btnLoginByPwd.EnableWindow(FALSE);
		m_btnLogout.EnableWindow(TRUE);

		//初始化联系人列表和群组列表
		m_pCBaseDlg->InitContactList();
		m_pCBaseDlg->InitGroupList();

		m_pCBaseDlg->ShowWindow(TRUE);
	}
}

void CUCDemoDlg::OnBnClickedButtonToken()
{
	// TODO: 在此添加控件通知处理程序代码
	//如果存在UC主界面，先销毁，再重新建立
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

	//设置UC回调函数
	SetCallBack();
	//设置UC服务器
	int iRet = Config(m_szUCUrl.GetBuffer());
	if (iRet)
	{
		MessageBox(_T("Config failed."),_T("Failed"),MB_OK);
		return;
	}
	//设置UC登陆语言
	iRet = SetLang(m_szLang.GetBuffer());
	if (iRet)
	{
		MessageBox(_T("SetLang failed."),_T("Failed"),MB_OK);
		return;
	}

	//登陆
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

	//初始化联系人列表和群组列表
	m_pCBaseDlg->InitContactList();
	m_pCBaseDlg->InitGroupList();
	m_pCBaseDlg->ShowWindow(TRUE);
}

void CUCDemoDlg::OnBnClickedButtonLogout()
{
	// TODO: 在此添加控件通知处理程序代码
	if (m_pCBaseDlg && m_pCBaseDlg->GetSafeHwnd())
	{
		if (NULL != m_pCBaseDlg->m_pCUCDemoDlg)
		{
			//登出
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
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	GetDlgItemText(IDC_EDIT_SSOURL, m_szSSOUrl);
}

void CUCDemoDlg::OnEnChangeEditHostip()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	GetDlgItemText(IDC_EDIT_HOSTIP, m_szHostIp);
}

void CUCDemoDlg::OnEnChangeEditUpdurl()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	GetDlgItemText(IDC_EDIT_UPDURL, m_szUpdateUrl);
}

void CUCDemoDlg::OnEnChangeEditUcurl()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	GetDlgItemText(IDC_EDIT_UCURL, m_szUCUrl);
}

void CUCDemoDlg::OnEnChangeEditAccount()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	GetDlgItemText(IDC_EDIT_ACCOUNT, m_szAccount);
}

void CUCDemoDlg::OnEnChangeEditPasswd()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	GetDlgItemText(IDC_EDIT_PASSWD, m_szPasswd);
}

void CUCDemoDlg::OnCbnSelchangeComboType()
{
	// TODO: 在此添加控件通知处理程序代码
	m_iLoginType = m_cmbLoginType.GetCurSel();
}

LRESULT CUCDemoDlg::OnMsgBaseDlgClose(WPARAM wparam, LPARAM lparam)
{
	//登出
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
	if (iMsgID == 0) //UPDATE_ASK 升级询问
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
	else if (iMsgID == 1) //UPDATE_START	升级开始
	{
		::MessageBox(CWnd::GetDesktopWindow()->GetSafeHwnd(), _T("Update start."), _T("Update"), MB_OK);
	}
	else if (iMsgID == 2) //UPDATE_FINISHED 升级完成
	{
		CString szDes(pchDescription);
		::MessageBox(CWnd::GetDesktopWindow()->GetSafeHwnd(), szDes, _T("Update finished"), MB_OK);
	}
	else	//非法msgid
	{
		::MessageBox(CWnd::GetDesktopWindow()->GetSafeHwnd(), _T("Error message code."), _T("Update"), MB_OK);
	}

	return true;
}
