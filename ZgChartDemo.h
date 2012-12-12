// ZgChartDemo.h : main header file for the ZGCHARTDEMO application
//

#if !defined(AFX_ZGCHARTDEMO_H__F1BC61CF_85F6_4714_90D0_70D4FE6384DC__INCLUDED_)
#define AFX_ZGCHARTDEMO_H__F1BC61CF_85F6_4714_90D0_70D4FE6384DC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CZgChartDemoApp:
// See ZgChartDemo.cpp for the implementation of this class
//

class CZgChartDemoApp : public CWinApp
{
public:
	CZgChartDemoApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CZgChartDemoApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

public:
	//{{AFX_MSG(CZgChartDemoApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ZGCHARTDEMO_H__F1BC61CF_85F6_4714_90D0_70D4FE6384DC__INCLUDED_)
