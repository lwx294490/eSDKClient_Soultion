
// eSDKClientLogTestDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "eSDKClientLogTest.h"
#include "eSDKClientLogTestDlg.h"

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


// CeSDKClientLogTestDlg 对话框




CeSDKClientLogTestDlg::CeSDKClientLogTestDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CeSDKClientLogTestDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CeSDKClientLogTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_Path);
}

BEGIN_MESSAGE_MAP(CeSDKClientLogTestDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON1, &CeSDKClientLogTestDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CeSDKClientLogTestDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CeSDKClientLogTestDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CeSDKClientLogTestDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON6, &CeSDKClientLogTestDlg::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON5, &CeSDKClientLogTestDlg::OnBnClickedButton5)
END_MESSAGE_MAP()


// CeSDKClientLogTestDlg 消息处理程序

BOOL CeSDKClientLogTestDlg::OnInitDialog()
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
	m_Path.SetWindowText(".\\log\\");

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CeSDKClientLogTestDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CeSDKClientLogTestDlg::OnPaint()
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
HCURSOR CeSDKClientLogTestDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CeSDKClientLogTestDlg::OnBnClickedButton1()
{
	// TODO:
	unsigned int logLevel[3];
	logLevel[0] = 0;
	logLevel[1] = 0;
	logLevel[2] = 0;
	LogInit("UC", "D:\\Code\\eSDK_Platform_V100R005\\source\\eSDKClientLog\\output\\conf\\UC\\eSDKClientLogCfg.ini",logLevel,"D:\\Code\\eSDK_Platform_V100R005\\source\\eSDKClientLog\\output\\log\\UC");
}

void CeSDKClientLogTestDlg::OnBnClickedButton2()
{
	// TODO:
	LogFini("UC");
}
DWORD _stdcall writelog(void* p)
{
	//while(1)
	//{
	//	char *str="123";
	//	int i = 100;
	//	Log_Interface_Info("UC","1","ParlayX","createGroup","10.68.160.1","10.68.160.112","ID12345678","2012/11/15 15:45:01 06","2012/11/15 15:45:01 345","0","name=%d,str=%s",i,str);
	//	Log_Interface_Error("IVS","2","native","interfaceName","127.0.0.3","127.0.0.4","ID12345678","2012/11/15 15:45:01 06","2012/11/15 15:45:01 345","0","i=%d,str=%s",i,str);
	//	Log_Operate_Debug("moduleName","username","clientFlag","resultCode","keyInfo","i=%d,str=%s",i,str);
	//	Log_Operate_Info("moduleName","username","clientFlag","resultCode","keyInfo","i=%d,str=%s",i,str);
	//	Log_Operate_Warn("moduleName","username","clientFlag","resultCode","keyInfo","i=%d,str=%s",i,str);
	//	Log_Operate_Error("moduleName","username","clientFlag","resultCode","keyInfo","i=%d,str=%s",i,str);
	//	Log_Run_Debug("param");
	//	Log_Run_Info("param");
	//	Log_Run_Warn("param");
	//	Log_Run_Error("param");	
	//	//Sleep(1);
	//	break;
	//}
	return 0;
}
void CeSDKClientLogTestDlg::OnBnClickedButton3()
{
	// TODO: 
	//启动上传线程
	//DWORD threadid;
	//CreateThread(NULL,0,writelog,this,0,&threadid);
	char *str="123";
	int i = 100;
	Log_Interface_Info("UC","1","ParlayX","createGroup","10.68.160.1","10.68.160.112","ID12345678","2012/11/15 15:45:01 06","2012/11/15 15:45:01 345","0","name=%d,str=%s",i,str);
	Log_Interface_Error("UC","2","native","interfaceName","127.0.0.3","127.0.0.4","ID12345678","2012/11/15 15:45:01 06","2012/11/15 15:45:01 345","0","i=%d,str=%s",i,str);
	Log_Operate_Debug("UC","moduleName","username","clientFlag","resultCode","keyInfo","i=%d,str=%s",i,str);
	Log_Operate_Info("UC","moduleName","username","clientFlag","resultCode","keyInfo","i=%d,str=%s",i,str);
	Log_Operate_Warn("UC","moduleName","username","clientFlag","resultCode","keyInfo","i=%d,str=%s",i,str);
	Log_Operate_Error("UC","moduleName","username","clientFlag","resultCode","keyInfo","i=%d,str=%s",i,str);
	Log_Run_Debug("UC","param");
	Log_Run_Info("UC","param");
	Log_Run_Warn("UC","param");
	Log_Run_Error("UC","param");	
}



void CeSDKClientLogTestDlg::OnBnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码
	unsigned int logLevel[3];
	logLevel[0] = 0;
	logLevel[1] = 0;
	logLevel[2] = 0;
	LogInit("eLTE", "D:\\Code\\eSDK_Platform_V100R005\\source\\eSDKClientLog\\output\\conf\\eLTE\\eSDKClientLogCfg.ini",logLevel,"D:\\Code\\eSDK_Platform_V100R005\\source\\eSDKClientLog\\output\\log\\eLTE");
}

void CeSDKClientLogTestDlg::OnBnClickedButton6()
{
	// TODO: 在此添加控件通知处理程序代码
	char *str="123";
	int i = 100;
	Log_Interface_Info("eLTE","1","ParlayX","createGroup","10.68.160.1","10.68.160.112","ID12345678","2012/11/15 15:45:01 06","2012/11/15 15:45:01 345","0","name=%d,str=%s",i,str);
	Log_Interface_Error("eLTE","2","native","interfaceName","127.0.0.3","127.0.0.4","ID12345678","2012/11/15 15:45:01 06","2012/11/15 15:45:01 345","0","i=%d,str=%s",i,str);
	Log_Operate_Debug("eLTE","moduleName","username","clientFlag","resultCode","keyInfo","i=%d,str=%s",i,str);
	Log_Operate_Info("eLTE","moduleName","username","clientFlag","resultCode","keyInfo","i=%d,str=%s",i,str);
	Log_Operate_Warn("eLTE","moduleName","username","clientFlag","resultCode","keyInfo","i=%d,str=%s",i,str);
	Log_Operate_Error("eLTE","moduleName","username","clientFlag","resultCode","keyInfo","i=%d,str=%s",i,str);
	Log_Run_Debug("eLTE","param");
	Log_Run_Info("eLTE","param");
	Log_Run_Warn("eLTE","param");
	Log_Run_Error("eLTE","param");	
}

void CeSDKClientLogTestDlg::OnBnClickedButton5()
{
	// TODO: 在此添加控件通知处理程序代码
	LogFini("eLTE");
}
