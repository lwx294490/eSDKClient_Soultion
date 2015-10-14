
// testComDlg.cpp : ʵ���ļ�
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


// CtestComDlg �Ի���




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


// CtestComDlg ��Ϣ�������

BOOL CtestComDlg::OnInitDialog()
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

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CtestComDlg::OnPaint()
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
HCURSOR CtestComDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CtestComDlg::OnBnClickedButtonWritetoken()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	BSTR bsToken = m_szToken.AllocSysString();
	HRESULT hr = m_pIntf->WriteToken(bsToken);
	if (S_OK != hr)
	{
		MessageBox(_T("Write token fail"),"",MB_OK);
	}
	SysFreeString(bsToken);


	//*************** 2014/10/14 ��֤����eSpace�ͻ��˵�ͬʱ�ܲ��ܽ�tokenд��COM�ӿ�
	//����COM
	CComPtr<eSpace::IECSEspaceApp>  pEspace;
	HRESULT hreSpace = pEspace.CoCreateInstance(__uuidof(eSpace::ECSEspaceApp),NULL, CLSCTX_ALL);
	if(SUCCEEDED(hreSpace) && pEspace)
	{
		eSpace::IECSEspaceApp * pEntity=NULL;
		//��ѯ�ӿ�
		hreSpace = pEspace->QueryInterface(__uuidof(eSpace::IECSEspaceApp), (void**)&pEntity);
		if(pEntity)
		{
			try
			{
				//��ʾ��¼����
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	HRESULT hr = m_pIntf->ClearToken();
	if (S_OK != hr)
	{
		MessageBox(_T("Clear token fail"),"",MB_OK);
	}
}

void CtestComDlg::OnBnClickedButtonSsologin()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialog::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	GetDlgItemText(IDC_EDIT_Token, m_szToken);
}

void CtestComDlg::OnEnChangeEditName()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialog::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	GetDlgItemText(IDC_EDIT_Name, m_szName);
}

void CtestComDlg::OnEnChangeEditPassword()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialog::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	GetDlgItemText(IDC_EDIT_Password, m_szPassword);
}

void CtestComDlg::OnEnChangeEditUri()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialog::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	GetDlgItemText(IDC_EDIT_Uri, m_szUri);
}

void CtestComDlg::OnClose()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if (NULL != m_pIntf)
	{
		m_pIntf->Release();		
	}

	CoUninitialize();

	CDialog::OnClose();
}
