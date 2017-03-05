// LogitechCamCtrl.h : main header file for the LOGITECHCAMCTRL application
//

#if !defined(AFX_LOGITECHCAMCTRL_H__BB467D6F_58DE_4133_8ACE_1766379C22EA__INCLUDED_)
#define AFX_LOGITECHCAMCTRL_H__BB467D6F_58DE_4133_8ACE_1766379C22EA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CLogitechCamCtrlApp:
// See LogitechCamCtrl.cpp for the implementation of this class
//

class CLogitechCamCtrlApp : public CWinApp
{
public:
	CLogitechCamCtrlApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLogitechCamCtrlApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CLogitechCamCtrlApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LOGITECHCAMCTRL_H__BB467D6F_58DE_4133_8ACE_1766379C22EA__INCLUDED_)
