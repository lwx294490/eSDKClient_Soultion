// RingDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "eSDKClientDemo.h"
#include "RingDlg.h"


// CRingDlg �Ի���

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

// CRingDlg ��Ϣ�������

void CRingDlg::OnClose()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	GetParent()->PostMessage(WM_ACCEPT_CALL,0,(LPARAM)m_pAVAdd);
	m_bIsOperator = true;
	PostMessage(WM_CLOSE);
}

void CRingDlg::OnBnClickedButtonReject()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	GetParent()->PostMessage(WM_REJECT_CALL,0,(LPARAM)m_pAVAdd);
	m_bIsOperator = true;
	PostMessage(WM_CLOSE);
}

void CRingDlg::OnEnChangeEditForward()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialog::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	GetDlgItemText(IDC_EDIT_FORWARD, m_szForward);
}
