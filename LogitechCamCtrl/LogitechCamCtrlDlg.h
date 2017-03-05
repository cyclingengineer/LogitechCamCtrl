// LogitechCamCtrlDlg.h : header file
//

#if !defined(AFX_LOGITECHCAMCTRLDLG_H__6280AA2E_1F62_44C3_B5BC_36C5424D1F6D__INCLUDED_)
#define AFX_LOGITECHCAMCTRLDLG_H__6280AA2E_1F62_44C3_B5BC_36C5424D1F6D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CLogitechCamCtrlDlg dialog

class CLogitechCamCtrlDlg : public CDialog
{
// Construction
public:
	CLogitechCamCtrlDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CLogitechCamCtrlDlg)
	enum { IDD = IDD_LOGITECHCAMCTRL_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLogitechCamCtrlDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	bool initController();
	void initGUI(bool camctrlIsOpen);
	void autoExposure(bool on);
	void loadExposure();
	void updateUI_WB(bool on);
protected:
	CButton* ckRL;
	CSliderCtrl* sldEX;
	CSliderCtrl* sldGA;
	CSliderCtrl* sldBR;
	CSliderCtrl* sldCO;
	CSliderCtrl* sldIN;
	CSliderCtrl* sldWB;
	CButton* ckGA;
	CButton* ckWB;
	CComboBox* cbxFL;
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CLogitechCamCtrlDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnButton_ZoomIN();
	afx_msg void OnButton_ZoomOut();
	afx_msg void OnButton_Up();
	afx_msg void OnButton_Down();
	afx_msg void OnButton_Right();
	afx_msg void OnButton_Left();
	afx_msg void OnCheck_AutoExposure();
	afx_msg void OnCheck_AutoWB();
	afx_msg void OnCheck_RightLight();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LOGITECHCAMCTRLDLG_H__6280AA2E_1F62_44C3_B5BC_36C5424D1F6D__INCLUDED_)
