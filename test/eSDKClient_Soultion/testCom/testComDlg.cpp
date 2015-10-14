
// testComDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "testCom.h"
#include "testComDlg.h"
#include "COM_eSDKSSO_i.h"
#include "COM_eSDKSSO_i.c"

#include <string>

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


// CtestComDlg 对话框




CtestComDlg::CtestComDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CtestComDlg::IDD, pParent)
	, m_szToken(_T(""))
	, m_szName(_T(""))
	, m_szPassword(_T(""))
	, m_szUri(_T(""))
	,m_pIntf(NULL)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CtestComDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON_WriteToken, m_btnWriteToken);
	DDX_Text(pDX, IDC_EDIT_Token, m_szToken);
	DDX_Text(pDX, IDC_EDIT_Name, m_szName);
	DDX_Text(pDX, IDC_EDIT_Password, m_szPassword);
	DDX_Text(pDX, IDC_EDIT_Uri, m_szUri);
	DDX_Control(pDX, IDC_BUTTON_GetToken, m_btnGetToken);
	DDX_Control(pDX, IDC_BUTTON_ClearToken, m_btnClearToken);
	DDX_Control(pDX, IDC_BUTTON_SSOLogin, m_btnSSOLogin);
}

BEGIN_MESSAGE_MAP(CtestComDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON_WriteToken, &CtestComDlg::OnBnClickedButtonWritetoken)
	ON_BN_CLICKED(IDC_BUTTON_GetToken, &CtestComDlg::OnBnClickedButtonGettoken)
	ON_BN_CLICKED(IDC_BUTTON_ClearToken, &CtestComDlg::OnBnClickedButtonCleartoken)
	ON_BN_CLICKED(IDC_BUTTON_SSOLogin, &CtestComDlg::OnBnClickedButtonSsologin)
	ON_EN_CHANGE(IDC_EDIT_Token, &CtestComDlg::OnEnChangeEditToken)
	ON_EN_CHANGE(IDC_EDIT_Name, &CtestComDlg::OnEnChangeEditName)
	ON_EN_CHANGE(IDC_EDIT_Password, &CtestComDlg::OnEnChangeEditPassword)
	ON_EN_CHANGE(IDC_EDIT_Uri, &CtestComDlg::OnEnChangeEditUri)
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// CtestComDlg 消息处理程序

BOOL CtestComDlg::OnInitDialog()
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
	m_szToken = "QWL9888888@Huawei";
	m_szName = "q64597";
	m_szPassword = "abcd1234";
	m_szUri = "https://10.135.42.58:18643/";
	UpdateData(FALSE);

	CoInitializeEx(NULL, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);
	HRESULT hr;
	hr = CoCreateInstance(CLSID_ComIdl_eSDKSSO,
		NULL,CLSCTX_LOCAL_SERVER,
		IID_IComIdl_eSDKSSO,
		(void **)& m_pIntf);
	if (S_OK != hr)
	{
		return FALSE;
	}

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CtestComDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CtestComDlg::OnPaint()
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
HCURSOR CtestComDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CtestComDlg::OnBnClickedButtonWritetoken()
{
	// TODO: 在此添加控件通知处理程序代码
	BSTR bsToken = m_szToken.AllocSysString();
	HRESULT hr = m_pIntf->WriteToken(bsToken);
	if (S_OK != hr)
	{
		MessageBox(_T("Write token fail"),"",MB_OK);
	}
	SysFreeString(bsToken);


	//*************** 2014/10/14 验证拉起eSpace客户端的同时能不能将token写入COM接口
	//创建COM
	CComPtr<eSpace::IECSEspaceApp>  pEspace;
	HRESULT hreSpace = pEspace.CoCreateInstance(__uuidof(eSpace::ECSEspaceApp),NULL, CLSCTX_ALL);
	if(SUCCEEDED(hreSpace) && pEspace)
	{
		eSpace::IECSEspaceApp * pEntity=NULL;
		//查询接口
		hreSpace = pEspace->QueryInterface(__uuidof(eSpace::IECSEspaceApp), (void**)&pEntity);
		if(pEntity)
		{
			try
			{
				//显示登录窗口
				hreSpace = pEntity->ShowLoginDialog();
			}
			catch (_com_error e)
			{

			}
		}
	}
	//***************/
}

void CtestComDlg::OnBnClickedButtonGettoken()
{
	// TODO: 在此添加控件通知处理程序代码
	std::string strTmpToken = "";
	BSTR bsToken = NULL;

	HRESULT hr = m_pIntf->GetToken(&bsToken);
	if (S_OK != hr)
	{
		MessageBox(_T("Get token fail"),"",MB_OK);
	}
	else
	{
		strTmpToken = _com_util::ConvertBSTRToString(bsToken);
		SysFreeString(bsToken);
		MessageBox(strTmpToken.c_str(),"",MB_OK);
	}	
}

void CtestComDlg::OnBnClickedButtonCleartoken()
{
	// TODO: 在此添加控件通知处理程序代码
	HRESULT hr = m_pIntf->ClearToken();
	if (S_OK != hr)
	{
		MessageBox(_T("Clear token fail"),"",MB_OK);
	}
}

void CtestComDlg::OnBnClickedButtonSsologin()
{
	// TODO: 在此添加控件通知处理程序代码
	BSTR bsName = m_szName.AllocSysString();
	BSTR bsPassword = m_szPassword.AllocSysString();
	BSTR bsUri = m_szUri.AllocSysString();

	HRESULT hr = m_pIntf->SSOLogin(bsName, bsPassword, bsUri);
	if (S_OK != hr)
	{
		MessageBox(_T("SSOLogin fail"),"",MB_OK);
	}

	SysFreeString(bsName);
	SysFreeString(bsPassword);
	SysFreeString(bsUri);
}

void CtestComDlg::OnEnChangeEditToken()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	GetDlgItemText(IDC_EDIT_Token, m_szToken);
}

void CtestComDlg::OnEnChangeEditName()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	GetDlgItemText(IDC_EDIT_Name, m_szName);
}

void CtestComDlg::OnEnChangeEditPassword()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	GetDlgItemText(IDC_EDIT_Password, m_szPassword);
}

void CtestComDlg::OnEnChangeEditUri()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	GetDlgItemText(IDC_EDIT_Uri, m_szUri);
}

void CtestComDlg::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (NULL != m_pIntf)
	{
		m_pIntf->Release();		
	}

	CoUninitialize();

	CDialog::OnClose();
}
