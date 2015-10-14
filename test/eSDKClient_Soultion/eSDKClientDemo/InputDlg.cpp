// InputDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "eSDKClientDemo.h"
#include "InputDlg.h"


// CInputDlg �Ի���

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

// CInputDlg ��Ϣ�������

void CInputDlg::OnClose()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	m_szInput = _T("");
	m_szRect = _T("");
	m_szFlag = _T("");
	m_pTreeItemData = NULL;
	UpdateData(FALSE);

	CDialog::OnClose();
}

void CInputDlg::OnEnChangeEditInput()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialog::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	GetDlgItemText(IDC_EDIT_INPUT, m_szInput);
}

void CInputDlg::OnBnClickedButtonOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	PostMessage(WM_CLOSE);
}
