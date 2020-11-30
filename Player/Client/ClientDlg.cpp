
// ClientDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "Client.h"
#include "ClientDlg.h"
#include "afxdialogex.h"
#include"afxsock.h"
#include<iostream>
#include<cstring>
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

using namespace std;

// CClientDlg dialog



CClientDlg::CClientDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CLIENT_DIALOG, pParent)
	, m_status2(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EnterUSN, m_username);
	DDX_Control(pDX, status, m_status);
	DDX_Control(pDX, questions, m_question);
	DDX_Control(pDX, ansA, m_btnA);
	DDX_Control(pDX, ansC, m_btnC);
	DDX_Control(pDX, ansB, m_btnB);
	DDX_Control(pDX, ansD, m_btnD);
	DDX_Text(pDX, status, m_status2);
}

BEGIN_MESSAGE_MAP(CClientDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_Login, &CClientDlg::OnBnClickedLogin)
	ON_BN_CLICKED(IDC_Skip, &CClientDlg::OnBnClickedSkip)
	ON_BN_CLICKED(IDC_Start, &CClientDlg::OnBnClickedStart)
	ON_BN_CLICKED(IDC_Logout, &CClientDlg::OnBnClickedLogout)
	ON_BN_CLICKED(IDC_btnA, &CClientDlg::OnBnClickedA)
	//ON_BN_CLICKED(IDC_btnB, &CClientDlg::OnBnClickedB)
	//ON_BN_CLICKED(IDC_btnC, &CClientDlg::OnBnClickedC)
	//ON_BN_CLICKED(IDC_btnD, &CClientDlg::OnBnClickedD)

END_MESSAGE_MAP()


// CClientDlg message handlers

BOOL CClientDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CClientDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CClientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}





void CClientDlg::OnBnClickedLogin()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	/*unsigned int port = 1234;
	
	CSocket client;
	AfxSocketInit(NULL);

	client.Create();

	if (!client.Connect(_T("192.168.1.1"), port)) {
		m_status.SetWindowTextW(_T("Cannot connect to server"));
	}	
	else
	{
		m_status.SetWindowText(_T("Login success!"));
		client.Send()

	}*/
	m_status.SetWindowTextW(_T("Success\n"));
	

	
}


void CClientDlg::OnBnClickedSkip()
{
	// TODO: Add your control notification handler code here
	int start = 0;
	int end = m_question.GetWindowTextLength();
	m_question.SetSel(start, end);
	m_question.ReplaceSel(L"Question 2");
}

void CClientDlg::OnBnClickedStart() {
	m_question.SetWindowTextW(_T("Question 1"));
	m_btnA.SetWindowTextW(_T("A"));
	m_btnB.SetWindowTextW(_T("B"));
	m_btnC.SetWindowTextW(_T("C"));
	m_btnD.SetWindowTextW(_T("D"));
	int start = 0;
	int end = m_status.GetWindowTextLength();
	m_status.SetSel(start, end);
	m_status.ReplaceSel(L"Start");
}

void CClientDlg::OnBnClickedA() {
	m_status.SetWindowTextW(_T("Correct!"));
}

void CClientDlg::OnBnClickedLogout() {
	CSocket client;
	client.Close();
}