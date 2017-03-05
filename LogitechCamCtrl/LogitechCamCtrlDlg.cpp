// LogitechCamCtrlDlg.cpp : implementation file
//

#include "stdafx.h"
#include "LogitechCamCtrl.h"
#include "LogitechCamCtrlDlg.h"

#include "logitechcamctrl1.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define ZOOM_STEP		10
#define PANTILT_STEP	10

LogitechCamCtrl camCtrl;

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLogitechCamCtrlDlg dialog

CLogitechCamCtrlDlg::CLogitechCamCtrlDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CLogitechCamCtrlDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CLogitechCamCtrlDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CLogitechCamCtrlDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLogitechCamCtrlDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CLogitechCamCtrlDlg, CDialog)
	//{{AFX_MSG_MAP(CLogitechCamCtrlDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_HSCROLL()
	ON_BN_CLICKED(IDC_BUTTON5, OnButton_ZoomIN)
	ON_BN_CLICKED(IDC_BUTTON_ZOUT, OnButton_ZoomOut)
	ON_BN_CLICKED(IDC_BUTTON_UP, OnButton_Up)
	ON_BN_CLICKED(IDC_BUTTON_DOWN, OnButton_Down)
	ON_BN_CLICKED(IDC_BUTTON_RIGHT, OnButton_Right)
	ON_BN_CLICKED(IDC_BUTTON_LEFT, OnButton_Left)
	ON_BN_CLICKED(IDC_CHECK_AUTO_EXPOSURE, OnCheck_AutoExposure)
	ON_BN_CLICKED(IDC_CHECK_AUTO_WB, OnCheck_AutoWB)
	ON_BN_CLICKED(IDC_CHECK_RIGHT_LIGHT, OnCheck_RightLight)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLogitechCamCtrlDlg message handlers

BOOL CLogitechCamCtrlDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	CoInitialize(NULL/*, COINIT_APARTMENTTHREADED*/);

	// List all device video capture by nam
	//int re = enum_devices(0, 0);
	ckRL = (CButton*)GetDlgItem(IDC_CHECK_RIGHT_LIGHT);
	sldEX = (CSliderCtrl*)GetDlgItem(IDC_SLIDER_EXPOSURE);
	sldGA = (CSliderCtrl*)GetDlgItem(IDC_SLIDER_GAIN);
	sldBR = (CSliderCtrl*)GetDlgItem(IDC_SLIDER_BRIGHTNESS);
	sldCO = (CSliderCtrl*)GetDlgItem(IDC_SLIDER_CONTRAST);
	sldIN = (CSliderCtrl*)GetDlgItem(IDC_SLIDER_COLOR_INTENSITY);
	sldWB = (CSliderCtrl*)GetDlgItem(IDC_SLIDER_WB);
	ckGA = (CButton*)GetDlgItem(IDC_CHECK_AUTO_EXPOSURE);
	ckWB = (CButton*)GetDlgItem(IDC_CHECK_AUTO_WB);
	cbxFL = (CComboBox*)GetDlgItem(IDC_COMBO_ANTI_FLICKER);


	bool isOpen = initController();
	initGUI(isOpen);
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CLogitechCamCtrlDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CLogitechCamCtrlDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

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
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CLogitechCamCtrlDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

bool CLogitechCamCtrlDlg::initController()
{
	return camCtrl.open("Logitech HD Pro Webcam C910");
}

void CLogitechCamCtrlDlg::initGUI(bool camctrlIsOpen)
{
	ckRL->EnableWindow(camctrlIsOpen);
	sldEX->EnableWindow(camctrlIsOpen);
	sldGA->EnableWindow(camctrlIsOpen);
	sldBR->EnableWindow(camctrlIsOpen);
	sldCO->EnableWindow(camctrlIsOpen);
	sldIN->EnableWindow(camctrlIsOpen);
	sldWB->EnableWindow(camctrlIsOpen);
	ckGA->EnableWindow(camctrlIsOpen);
	ckWB->EnableWindow(camctrlIsOpen);
	cbxFL->EnableWindow(camctrlIsOpen);

	if (!camctrlIsOpen)
		return;

	// 
	ControlInfo info;
	int tmp;

	// init slider Exposure
	loadExposure();

	// init slider Brightness
	memset(&info, 0, sizeof(ControlInfo));
	camCtrl.getControlInfo(LogitechCamCtrl::CIT_BRIGHTNESS, info);
	sldBR->SetRange(info.min, info.max);
	camCtrl.getBrightness(tmp);
	sldBR->SetPos(tmp);

	// init slider Contrast
	memset(&info, 0, sizeof(ControlInfo));
	camCtrl.getControlInfo(LogitechCamCtrl::CIT_CONTRAST, info);
	sldCO->SetRange(info.min, info.max);
	camCtrl.getContrast(tmp);
	sldCO->SetPos(tmp);

	// init slider White Balance
	memset(&info, 0, sizeof(ControlInfo));
	camCtrl.getControlInfo(LogitechCamCtrl::CIT_WB, info);
	sldWB->SetRange(info.min, info.max);
	camCtrl.getWB(tmp);
	sldWB->SetPos(tmp);

	// init slider Color Intensity(Saturation);
	memset(&info, 0, sizeof(ControlInfo));
	camCtrl.getControlInfo(LogitechCamCtrl::CIT_COLOR_INTENSITY, info);
	sldIN->SetRange(info.min, info.max);
	camCtrl.getColorIntensity(tmp);
	sldIN->SetPos(tmp);

	// if auto exposure is seted
	bool autoEx;
	camCtrl.getAutoExposure(autoEx);
	autoExposure(autoEx);

	// if auto white balance
	bool autoWb;
	camCtrl.getAutoWB(autoWb);
	ckWB->SetCheck(autoWb);
	sldWB->EnableWindow(!autoWb);

	// if rightlight is checked
	bool rili;
	camCtrl.getRightLight(rili);
	ckRL->SetCheck(rili);
}

void CLogitechCamCtrlDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	// TODO: Add your message handler code here and/or call default

	if ((void*)pScrollBar == (void*)sldEX){
		// the exposure of image icrease by following order: 1, 0, -1, -2, -3, -4, -5, -6, -7
		nPos = sldEX->GetPos();
		// Cach 1
		/**
		if ( 1 <= nPos || nPos <= 2) {
			camCtrl.setExposure(2-nPos);
		}
		else if (3 <= nPos && nPos <= 9)
			camCtrl.setExposure(-1*(nPos-2));
		*/

		// Cach 2:
		camCtrl.setExposure(nPos * EXPOSURE_TIME_10MS);
	}
	else if ((void*)pScrollBar == (void*)sldGA){
		nPos = sldGA->GetPos();
		camCtrl.setGain(nPos);
	}
	else if ((void*)pScrollBar == (void*)sldBR){
		nPos = sldBR->GetPos();
		camCtrl.setBrightness(nPos);
	}
	else if ((void*)pScrollBar == (void*)sldCO){
		nPos = sldCO->GetPos();
		camCtrl.setContrast(nPos);
	}
	else if ((void*)pScrollBar == (void*)sldWB){
		nPos = sldWB->GetPos();
		camCtrl.setWB(nPos);
	}


	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}


void CLogitechCamCtrlDlg::OnButton_ZoomIN() 
{
	int curZ;
	int hr = camCtrl.getDigitalZoom(curZ);
	curZ += ZOOM_STEP;
	if (curZ <= 400) {
		camCtrl.setDigitalZoom(curZ);
		return;
	}
}

void CLogitechCamCtrlDlg::OnButton_ZoomOut() 
{
	int curZ;
	int hr = camCtrl.getDigitalZoom(curZ);
	
	if (curZ <= 100)
		return;
	
	curZ -= ZOOM_STEP;
	camCtrl.setDigitalZoom(curZ);
}

void CLogitechCamCtrlDlg::OnButton_Up() 
{
	int curT;
	int hr = camCtrl.getDigitalTilt(curT);

	if (hr != S_OK)
		return;

//	if (curT >= 100)
//		return;

	curT -= PANTILT_STEP;
	camCtrl.setDigitalTilt(curT);
}



void CLogitechCamCtrlDlg::OnButton_Down() 
{
	int curT;
	int hr = camCtrl.getDigitalTilt(curT);

	if (hr != S_OK)
		return;

//	if (curT <= -100)
//		return;

	curT += PANTILT_STEP;
	camCtrl.setDigitalTilt(curT);	
}

void CLogitechCamCtrlDlg::OnButton_Right() 
{
	int curP;
	int hr = camCtrl.getDigitalPan(curP);

	if (hr != S_OK)
		return;

//	if (curP >= 100)
//		return;

	curP += PANTILT_STEP;
	camCtrl.setDigitalPan(curP);
}

void CLogitechCamCtrlDlg::OnButton_Left() 
{
	int curP;
	int hr = camCtrl.getDigitalPan(curP);

	if (hr != S_OK)
		return;

//	if (curP >= 100)
//		return;

	curP -= PANTILT_STEP;
	camCtrl.setDigitalPan(curP);	
}

void CLogitechCamCtrlDlg::OnCheck_AutoExposure() 
{
	// TODO: Add your control notification handler code here
	bool check = ckGA->GetCheck();
	if (camCtrl.setAutoExposure(check)==S_OK)
		autoExposure(check);
	else
		autoExposure(!check);
}

void CLogitechCamCtrlDlg::OnCheck_AutoWB() 
{
	// TODO: Add your control notification handler code here
	bool check = ckWB->GetCheck();
	if ( camCtrl.setAutoWB(check)==S_OK)
		updateUI_WB(check);
	else
		updateUI_WB(!check);
}

void CLogitechCamCtrlDlg::OnCheck_RightLight() 
{
	bool check = ckRL->GetCheck();
	camCtrl.setRightLight(check);
}

void CLogitechCamCtrlDlg::autoExposure(bool on)
{
	sldEX->EnableWindow(!on);
	sldGA->EnableWindow(!on);
	ckGA->SetCheck(on);

	if (!on)
		loadExposure();
}

void CLogitechCamCtrlDlg::updateUI_WB(bool on)
{
	sldWB->EnableWindow(!on);
	ckWB->SetCheck(on);
}

void CLogitechCamCtrlDlg::loadExposure()
{
	ControlInfo info;
	int tmp;

	memset(&info, 0, sizeof(ControlInfo));
	camCtrl.getControlInfo(LogitechCamCtrl::CIT_EXPOSURE, info);
	sldEX->SetRange(1, 10); // range: 1, 0, -1, -2, -3, -4, -5, -6, -7
	sldEX->SetTicFreq(info.step);
	camCtrl.getExposure(tmp);
	//tmp = (tmp < 0) ? (2-tmp) : ((tmp==1) ? (2) : (1));
	tmp /= EXPOSURE_TIME_10MS;
	sldEX->SetPos(tmp);

	// init slider Gain
	memset(&info, 0, sizeof(ControlInfo));
	camCtrl.getControlInfo(LogitechCamCtrl::CIT_GAIN, info);
	sldGA->SetRange(info.min, info.max);
	camCtrl.getGain(tmp);
	sldGA->SetPos(tmp);
}