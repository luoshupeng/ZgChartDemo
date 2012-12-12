// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "ZgChartDemo.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
	ON_COMMAND(ID_OUTPUT_FILE, OnOutputFile)
	ON_COMMAND(ID_PRINT_CHART, OnPrintChart)
	ON_WM_ACTIVATEAPP()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here
	
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	//////////////////////////////////////////////////////////////////////////
	//创建曲线显示窗体
	if (!m_wndZgChart.CreateChartView(this, CRect(0,0,0,0)))
		return -1;

	CTime tStart(2004, 3, 21, 0, 0, 0);
	CTime tStop(2004, 3, 25, 0, 0, 0);
	//设置横轴的开始时间和结束时间
	m_wndZgChart.SetXDate(tStart.GetTime(), tStop.GetTime());

	//标题
	m_wndZgChart.SetTitleText(CString("汉中路变压器 - 电流曲线"));

	//添加曲线
	COLORREF l_cr1 = 0x80dd00;
	COLORREF l_cr2 = 0x0080ff;
	COLORREF l_cr3 = 0xff8000;
	m_wndZgChart.AddChartCutline("A相电流(A)", l_cr1, 1, TRUE);
	m_wndZgChart.AddChartCutline("B相电流(A)", l_cr2, 1);
	m_wndZgChart.AddChartCutline("C相电流(A)", l_cr3, 1);

	//设置曲线纵轴的范围
	m_wndZgChart.SetYValue(5, 6);

	//设置插入数据的时间间隔
	int nTimeSpin = 60*60;
	m_wndZgChart.SetTimeSpin(nTimeSpin);
	
	//插入数据
	//我们使用随机数，先建立种子
	srand((unsigned)time(NULL));
	float fValue[3];
	for(int i=tStart.GetTime(); i<tStop.GetTime(); i+=nTimeSpin)
	{
		fValue[0] = float(rand()%10)/100;
		fValue[1] = float(rand()%20)/100;
		fValue[2] = float(rand()%30)/100;
		if (rand()%2)
		{
			fValue[0] *= -1;
			fValue[0] *= -1;
			fValue[0] *= -1;
		}

		m_wndZgChart.AddChartData(0, i, float(5.2+fValue[0]), TRUE);
		m_wndZgChart.AddChartData(1, i, float(5.4+fValue[1]), TRUE);
		m_wndZgChart.AddChartData(2, i, float(5.6+fValue[2]), TRUE);
	}

	//最后在OnSize中调整大小
	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	cs.dwExStyle &= ~WS_EX_CLIENTEDGE;
	cs.lpszClass = AfxRegisterWndClass(0);
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers


void CMainFrame::OnSize(UINT nType, int cx, int cy) 
{
	CFrameWnd::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	if (m_wndZgChart.GetSafeHwnd())
	{
		CRect rcClient;
		GetClientRect(&rcClient);
		m_wndZgChart.MoveWindow(rcClient);
	}
}

BOOL CMainFrame::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default
	return TRUE;
	return CFrameWnd::OnEraseBkgnd(pDC);
}

//保存曲线
void CMainFrame::OnOutputFile() 
{
	// TODO: Add your command handler code here
	//如果曲线提示存在，强制隐藏
	if (m_wndZgChart.GetSafeHwnd())
		m_wndZgChart.HideTips();
	
	CString	strFileName;	
	TCHAR szFilters[]=_T("位图文件(*.bmp)|*.bmp|");
	CString strText;
	strText = "汉中路变压器 - 电流曲线";
	CFileDialog dlg(FALSE, _T("*.bmp"), strText, OFN_HIDEREADONLY, szFilters);
	dlg.m_ofn.lpstrTitle="保存为位图";
	
	if( dlg.DoModal() == IDCANCEL )
		return ;
	strFileName = dlg.GetPathName();

	if (m_wndZgChart.SaveChartToFile(strFileName))
		AfxMessageBox("保存为位图文件成功！");
	else
		AfxMessageBox("保存为位图文件失败！");
}

//打印曲线
void CMainFrame::OnPrintChart() 
{
	// TODO: Add your command handler code here
	//如果曲线提示存在，强制隐藏
	if (m_wndZgChart.GetSafeHwnd())
		m_wndZgChart.HideTips();

	//首先设置打印机页面为横向
	CPrintDialog l_pdFirst(TRUE);
	l_pdFirst.GetDefaults();

	HGLOBAL hDevMode=NULL;
	hDevMode = l_pdFirst.m_pd.hDevMode;

	if (NULL == hDevMode)
	{
		AfxMessageBox("请先安装打印机！");
		return;
	}

	LPDEVMODE lp_Mode = (LPDEVMODE) ::GlobalLock(hDevMode);
	ASSERT(lp_Mode);
	lp_Mode->dmOrientation = DMORIENT_LANDSCAPE;
	::GlobalUnlock(hDevMode);

	CPrintDialog dlg(FALSE, PD_NOPAGENUMS|PD_NOSELECTION|PD_HIDEPRINTTOFILE , this);
	dlg.m_pd.hDevMode = hDevMode;

	if(dlg.DoModal() == IDOK)
	{
		if (hDevMode != NULL)
		::GlobalFree(hDevMode);

		CDC dc;
		dc.Attach(dlg.GetPrinterDC());//把打印设备环境附加到DC对象

		DOCINFO di; 
		di.cbSize = sizeof(DOCINFO);

		di.lpszDocName = "汉中路变压器 - 电流曲线";
		di.lpszOutput = NULL;
		di.lpszDatatype = NULL;
		di.fwType = 0;

		dc.StartDoc(&di); //通知打印机驱动程序执行一新的打印任务
		dc.StartPage();//通知打印机驱动程序打印新页
	
		m_wndZgChart.PrintChart(&dc);

		dc.EndPage(); //通知打印机驱动程序页结束
		dc.EndDoc();//通知打印机驱动程序打印完毕
		DeleteDC(dc.Detach()); 
	}
}

void CMainFrame::OnActivateApp(BOOL bActive, HTASK hTask) 
{
	CFrameWnd::OnActivateApp(bActive, hTask);
	
	// TODO: Add your message handler code here
	if (bActive == FALSE)
	{
		//当没有激活是强制隐藏提示窗体
		m_wndZgChart.HideTips();
	}
}
