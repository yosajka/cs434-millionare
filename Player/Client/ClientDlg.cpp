
// ClientDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "Client.h"
#include "ClientDlg.h"
#include "afxdialogex.h"
#include<iostream>
#include<cstring>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

using namespace std;

// CClientDlg dialog



CClientDlg::CClientDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CLIENT_DIALOG, pParent)
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
	DDX_Control(pDX, timeCount, m_time);
}

BEGIN_MESSAGE_MAP(CClientDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_Login, &CClientDlg::OnBnClickedLogin)
	ON_BN_CLICKED(IDC_Skip, &CClientDlg::OnBnClickedSkip)
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
	unsigned int port = 1234;


	CClientDlg dlg;

	AfxSocketInit(NULL);
	
	client.Create();
	if (!client.Connect(_T("127.0.0.1"), port)) {
		m_status.SetWindowText(_T("Cannot connect to server"));
		client.Close();
	}
	else
	{
		m_status.SetWindowText(_T("Login success!"));
		//msgSize = m_username.GetWindowTextLengthW();
		//client.Send(&msgSize, sizeof(msgSize), 0);
		//GetDlgItemText(IDC_EnterUSN, msg, 500);
		//client.Send(msg, msgSize, 0);

		int num_quest;
		client.Receive((char*)&num_quest, sizeof(int), 0);

		//for (int q = 0; q < num_quest; q++) {

			client.Receive((char*)&msgSize, sizeof(int), 0);
			temp = new char[msgSize + 1];
			client.Receive((char*)temp, msgSize, 0);
			temp[msgSize] = '\0';
			question = CString(temp);
			m_question.SetWindowText(question);
			delete temp;


			client.Receive((char*)&msgSize, sizeof(int), 0);
			temp = new char[msgSize + 1];
			client.Receive((char*)temp, msgSize, 0);
			temp[msgSize] = '\0';
			choiceA = CString(temp);
			m_btnA.SetWindowTextW(choiceA);
			delete temp;

			client.Receive((char*)&msgSize, sizeof(int), 0);
			temp = new char[msgSize + 1];
			client.Receive((char*)temp, msgSize, 0);
			temp[msgSize] = '\0';
			choiceB = CString(temp);
			m_btnB.SetWindowTextW(choiceB);
			delete temp;

			client.Receive((char*)&msgSize, sizeof(int), 0);
			temp = new char[msgSize + 1];
			client.Receive((char*)temp, msgSize, 0);
			temp[msgSize] = '\0';
			choiceC = CString(temp);
			m_btnC.SetWindowTextW(choiceC);
			delete temp;

			client.Receive((char*)&msgSize, sizeof(int), 0);
			temp = new char[msgSize + 1];
			client.Receive((char*)temp, msgSize, 0);
			temp[msgSize] = '\0';
			choiceD = CString(temp);
			m_btnD.SetWindowTextW(choiceD);
			delete temp;

			//}
	}

}


void CClientDlg::OnBnClickedSkip()
{
	// TODO: Add your control notification handler code here
	client.Send("0", 1, 0);
	client.Receive(&question, sizeof(question), 0);
	m_question.SetWindowTextW(question);
	client.Receive(&choiceA, sizeof(choiceA), 0);
	m_btnA.SetWindowTextW(choiceA);
	client.Receive(&choiceB, sizeof(choiceB), 0);
	m_btnA.SetWindowTextW(choiceB);
	client.Receive(&choiceC, sizeof(choiceC), 0);
	m_btnA.SetWindowTextW(choiceC);
	client.Receive(&choiceD, sizeof(choiceD), 0);
	m_btnA.SetWindowTextW(choiceD);
	GetDlgItem(IDC_Skip)->EnableWindow(FALSE);
}


void CClientDlg::OnBnClickedA() {
	answer = "A";
	client.Send((char*)&answer, sizeof(answer), 0);
	client.Receive((char*)&msgSize, sizeof(int), 0);
	temp = new char[msgSize + 1];
	client.Receive((char*)temp, msgSize, 0);
	if (temp == "0") {
		m_status.SetWindowTextW(_T("Eliminated"));
		GetDlgItem(IDC_btnA)->EnableWindow(FALSE);
		GetDlgItem(IDC_btnB)->EnableWindow(FALSE);
		GetDlgItem(IDC_btnC)->EnableWindow(FALSE);
		GetDlgItem(IDC_btnD)->EnableWindow(FALSE);
	}
	delete temp;
}

void CClientDlg::OnBnClickedLogout() {
	client.Close();
}

void CClientDlg::OnBnClickedB(){
	answer = "B";
	client.Send((char*)&answer, sizeof(answer), 0);
	client.Receive((char*)&msgSize, sizeof(int), 0);
	temp = new char[msgSize + 1];
	client.Receive((char*)temp, msgSize, 0);
	temp[msgSize] = '\0';
	question = CString(temp);
	m_question.SetWindowText(question);
	delete temp;


	client.Receive((char*)&msgSize, sizeof(int), 0);
	temp = new char[msgSize + 1];
	client.Receive((char*)temp, msgSize, 0);
	temp[msgSize] = '\0';
	choiceA = CString(temp);
	m_btnA.SetWindowTextW(choiceA);
	delete temp;

	client.Receive((char*)&msgSize, sizeof(int), 0);
	temp = new char[msgSize + 1];
	client.Receive((char*)temp, msgSize, 0);
	temp[msgSize] = '\0';
	choiceB = CString(temp);
	m_btnB.SetWindowTextW(choiceB);
	delete temp;

	client.Receive((char*)&msgSize, sizeof(int), 0);
	temp = new char[msgSize + 1];
	client.Receive((char*)temp, msgSize, 0);
	temp[msgSize] = '\0';
	choiceC = CString(temp);
	m_btnC.SetWindowTextW(choiceC);
	delete temp;

	client.Receive((char*)&msgSize, sizeof(int), 0);
	temp = new char[msgSize + 1];
	client.Receive((char*)temp, msgSize, 0);
	temp[msgSize] = '\0';
	choiceD = CString(temp);
	m_btnD.SetWindowTextW(choiceD);
	delete temp;
}

void CClientDlg::OnBnClickedC(){
	answer = "C";
	client.Send((char*)&answer, sizeof(answer), 0);
}

void CClientDlg::OnBnClickedD(){
	answer = "D";
	client.Send((char*)&answer, sizeof(answer), 0);
}

void CClientDlg::countdown() {
	int t = 60;
	string cd;
	int n = t-1;
	m_time.SetWindowText(_T("60"));
	for (int i = 0; i < n; i++) {
		int start = 0;
		int end = m_time.GetWindowTextLength();
		cd = to_string(n);
		LPCTSTR new_cd = new TCHAR[cd.size() + 1];
		m_time.SetSel(start, end);
		m_time.ReplaceSel(new_cd);
		n--;
		Sleep(100);
	}
}