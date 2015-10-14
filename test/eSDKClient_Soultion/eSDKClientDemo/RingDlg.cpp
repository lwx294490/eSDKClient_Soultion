// RingDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "eSDKClientDemo.h"
#include "RingDlg.h"


// CRingDlg 对话框

IMPLEMENT_DYNAMIC(CRingDlg, CDialog)

CRingDlg::CRingDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CRingDlg::IDD, pParent)
	, m_szForward(_T(""))
	, m_pAVAdd(NULL)
{

}

CRingDlg::~CRingDlg()
{
}

void CRingDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_FORWARD, m_szForward);
	DDX_Control(pDX, IDC_BUTTON_FORWARD, m_btnForward);
	DDX_Control(pDX, IDC_BUTTON_ACCEPT, m_btnAccept);
	DDX_Control(pDX, IDC_BUTTON_REJECT, m_btnReject);
	DDX_Control(pDX, IDC_STATIC_VIDEO, m_stVideo);
}


BEGIN_MESSAGE_MAP(CRingDlg, CDialog)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BUTTON_FORWARD, &CRingDlg::OnBnClickedButtonForward)
	ON_BN_CLICKED(IDC_BUTTON_ACCEPT, &CRingDlg::OnBnClickedButtonAccept)
	ON_BN_CLICKED(IDC_BUTTON_REJECT, &CRingDlg::OnBnClickedButtonReject)
	ON_EN_CHANGE(IDC_EDIT_FORWARD, &CRingDlg::OnEnChangeEditForward)	
END_MESSAGE_MAP()


void CRingDlg::Init()
{
	CRect rect;
	::GetWindowRect(::GetDesktopWindow(),&rect);
	CRect temp;
	GetWindowRect(&temp);
	CPoint point;
	point.x = rect.Width()-temp.Width()-20;
	point.y = rect.Height()-temp.Height()-50;
	CRect t_rect(point,temp.Size());
	MoveWindow(t_rect);

	m_stVideo.ShowWindow(FALSE);
	m_szForward = _T("");
	m_pAVAdd = NULL;
	m_bIsOperator = false;
	UpdateData(FALSE);
}

// CRingDlg 消息处理程序

void CRingDlg::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CDialog::OnClose();

	if (!m_bIsOperator)
	{
		GetParent()->PostMessage(WM_REJECT_CALL,0,(LPARAM)m_pAVAdd);
	}

	m_szForward = _T("");
	m_pAVAdd = NULL;
	m_bIsOperator = false;
}

void CRingDlg::OnBnClickedButtonForward()
{
	// TODO: 在此添加控件通知处理程序代码
	if (m_szForward.IsEmpty())
	{
		MessageBox(_T("Please input forward number."),_T(""),MB_OK);
		return;
	}

	m_pAVAdd->forwardAcc = m_szForward.GetBuffer();
	GetParent()->PostMessage(WM_FORWARD_CALL,0,(LPARAM)m_pAVAdd);
	m_bIsOperator = true;
	PostMessage(WM_CLOSE);
}

void CRingDlg::OnBnClickedButtonAccept()
{
	// TODO: 在此添加控件通知处理程序代码
	GetParent()->PostMessage(WM_ACCEPT_CALL,0,(LPARAM)m_pAVAdd);
	m_bIsOperator = true;
	PostMessage(WM_CLOSE);
}

void CRingDlg::OnBnClickedButtonReject()
{
	// TODO: 在此添加控件通知处理程序代码
	GetParent()->PostMessage(WM_REJECT_CALL,0,(LPARAM)m_pAVAdd);
	m_bIsOperator = true;
	PostMessage(WM_CLOSE);
}

void CRingDlg::OnEnChangeEditForward()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	GetDlgItemText(IDC_EDIT_FORWARD, m_szForward);
}
