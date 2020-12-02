
// ClientDlg.h : header file
//
#include"afxsock.h"
#include<string>
#include<windowsx.h>
#pragma once


// CClientDlg dialog
class CClientDlg : public CDialogEx
{
	// Construction
public:
	CClientDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CLIENT_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	CString question, choiceA, choiceB, choiceC, choiceD;
	CString parse;
	int num_quest;
	HICON m_hIcon;
	CSocket client;
	TCHAR msg[500];

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	int msgSize;
	char* temp;
	CString answer;
	//afx_msg void OnEnChangeUsername();
	afx_msg void OnBnClickedSkip();
	afx_msg void OnBnClickedLogin();
	afx_msg void OnBnClickedLogout();
	afx_msg void OnBnClickedA();
	afx_msg void OnBnClickedB();
	afx_msg void OnBnClickedC();
	afx_msg void OnBnClickedD();
	void countdown();
	CEdit m_username;
	CEdit m_status;
	CEdit m_question;
	CEdit m_btnA;
	CEdit m_btnC;
	CEdit m_btnB;
	CEdit m_btnD;
	CEdit result, edit;
	CEdit m_time;
};
