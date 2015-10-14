// InputDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "eSDKClientDemo.h"
#include "InputDlg.h"


// CInputDlg 对话框

IMPLEMENT_DYNAMIC(CInputDlg, CDialog)

CInputDlg::CInputDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CInputDlg::IDD, pParent)
	, m_szInput(_T(""))
	, m_szRect(_T(""))
	, m_szFlag(_T(""))
	, m_pTreeItemData(NULL)
{

}

CInputDlg::~CInputDlg()
{
}

void CInputDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_INPUT, m_szInput);
	DDX_Control(pDX, IDC_BUTTON_OK, m_btnOK);
	DDX_Control(pDX, IDC_BUTTON_CANCEL, m_btnCancel);
}


BEGIN_MESSAGE_MAP(CInputDlg, CDialog)
	ON_WM_CLOSE()
	ON_EN_CHANGE(IDC_EDIT_INPUT, &CInputDlg::OnEnChangeEditInput)
	ON_BN_CLICKED(IDC_BUTTON_OK, &CInputDlg::OnBnClickedButtonOk)
	ON_BN_CLICKED(IDC_BUTTON_CANCEL, &CInputDlg::OnBnClickedButtonCancel)
END_MESSAGE_MAP()


void CInputDlg::Init()
{
	if ("right_top" == m_szRect)
	{
		CRect rect;
		GetParent()->GetWindowRect(&rect);
		CPoint point;
		point.x = rect.left+rect.Width();
		point.y = rect.top;

		CRect temp;
		GetWindowRect(&temp);

		CRect t_rect(point, temp.Size());
		MoveWindow(t_rect);
	}
	else if ("right_down" == m_szRect)
	{
		CRect rect;
		GetParent()->GetWindowRect(&rect);
		CRect temp;
		GetWindowRect(&temp);

		CPoint point;
		point.x = rect.left-temp.Width();
		point.y = rect.bottom-temp.Height();

		CRect t_rect(point, temp.Size());
		MoveWindow(t_rect);
	}

	m_szInput = _T("");
	m_szRect = _T("");
	m_szFlag = _T("");
	m_pTreeItemData = NULL;
	
	GetDlgItem(IDC_EDIT_INPUT)->SetFocus();
	UpdateData(FALSE);
}

// CInputDlg 消息处理程序

void CInputDlg::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	m_szInput = _T("");
	m_szRect = _T("");
	m_szFlag = _T("");
	m_pTreeItemData = NULL;
	UpdateData(FALSE);

	CDialog::OnClose();
}

void CInputDlg::OnEnChangeEditInput()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	GetDlgItemText(IDC_EDIT_INPUT, m_szInput);
}

void CInputDlg::OnBnClickedButtonOk()
{
	// TODO: 在此添加控件通知处理程序代码
	if (m_szInput.IsEmpty())
	{
		MessageBox(_T("Please input"),_T(""),MB_OK);
		return;
	}

	InputInfo* pInputInfo = new InputInfo;
	pInputInfo->szInput = m_szInput;
	pInputInfo->szFlag = m_szFlag;
	pInputInfo->pTreeItemData = m_pTreeItemData;
	GetParent()->PostMessage(WM_INPUT_STRING,0,(LPARAM)pInputInfo);
	PostMessage(WM_CLOSE);
}

void CInputDlg::OnBnClickedButtonCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	PostMessage(WM_CLOSE);
}
