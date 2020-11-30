
// ClientDlg.h : header file
//

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
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	//afx_msg void OnEnChangeUsername();
	afx_msg void OnBnClickedSkip();
	afx_msg void OnBnClickedLogin();
	afx_msg void OnBnClickedStart();
	afx_msg void OnBnClickedLogout();
	afx_msg void OnBnClickedA();
	afx_msg void OnBnClickedB();
	afx_msg void OnBnClickedC();
	afx_msg void OnBnClickedD();
	CEdit m_username;
	CEdit m_status;
	CEdit m_question;
	CEdit m_btnA;
	CEdit m_btnC;
	CEdit m_btnB;
	CEdit m_btnD;
	CString m_status2;
};
