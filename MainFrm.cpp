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
	//����������ʾ����
	if (!m_wndZgChart.CreateChartView(this, CRect(0,0,0,0)))
		return -1;

	CTime tStart(2004, 3, 21, 0, 0, 0);
	CTime tStop(2004, 3, 25, 0, 0, 0);
	//���ú���Ŀ�ʼʱ��ͽ���ʱ��
	m_wndZgChart.SetXDate(tStart.GetTime(), tStop.GetTime());

	//����
	m_wndZgChart.SetTitleText(CString("����·��ѹ�� - ��������"));

	//�������
	COLORREF l_cr1 = 0x80dd00;
	COLORREF l_cr2 = 0x0080ff;
	COLORREF l_cr3 = 0xff8000;
	m_wndZgChart.AddChartCutline("A�����(A)", l_cr1, 1, TRUE);
	m_wndZgChart.AddChartCutline("B�����(A)", l_cr2, 1);
	m_wndZgChart.AddChartCutline("C�����(A)", l_cr3, 1);

	//������������ķ�Χ
	m_wndZgChart.SetYValue(5, 6);

	//���ò������ݵ�ʱ����
	int nTimeSpin = 60*60;
	m_wndZgChart.SetTimeSpin(nTimeSpin);
	
	//��������
	//����ʹ����������Ƚ�������
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

	//�����OnSize�е�����С
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

//��������
void CMainFrame::OnOutputFile() 
{
	// TODO: Add your command handler code here
	//���������ʾ���ڣ�ǿ������
	if (m_wndZgChart.GetSafeHwnd())
		m_wndZgChart.HideTips();
	
	CString	strFileName;	
	TCHAR szFilters[]=_T("λͼ�ļ�(*.bmp)|*.bmp|");
	CString strText;
	strText = "����·��ѹ�� - ��������";
	CFileDialog dlg(FALSE, _T("*.bmp"), strText, OFN_HIDEREADONLY, szFilters);
	dlg.m_ofn.lpstrTitle="����Ϊλͼ";
	
	if( dlg.DoModal() == IDCANCEL )
		return ;
	strFileName = dlg.GetPathName();

	if (m_wndZgChart.SaveChartToFile(strFileName))
		AfxMessageBox("����Ϊλͼ�ļ��ɹ���");
	else
		AfxMessageBox("����Ϊλͼ�ļ�ʧ�ܣ�");
}

//��ӡ����
void CMainFrame::OnPrintChart() 
{
	// TODO: Add your command handler code here
	//���������ʾ���ڣ�ǿ������
	if (m_wndZgChart.GetSafeHwnd())
		m_wndZgChart.HideTips();

	//�������ô�ӡ��ҳ��Ϊ����
	CPrintDialog l_pdFirst(TRUE);
	l_pdFirst.GetDefaults();

	HGLOBAL hDevMode=NULL;
	hDevMode = l_pdFirst.m_pd.hDevMode;

	if (NULL == hDevMode)
	{
		AfxMessageBox("���Ȱ�װ��ӡ����");
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
		dc.Attach(dlg.GetPrinterDC());//�Ѵ�ӡ�豸�������ӵ�DC����

		DOCINFO di; 
		di.cbSize = sizeof(DOCINFO);

		di.lpszDocName = "����·��ѹ�� - ��������";
		di.lpszOutput = NULL;
		di.lpszDatatype = NULL;
		di.fwType = 0;

		dc.StartDoc(&di); //֪ͨ��ӡ����������ִ��һ�µĴ�ӡ����
		dc.StartPage();//֪ͨ��ӡ�����������ӡ��ҳ
	
		m_wndZgChart.PrintChart(&dc);

		dc.EndPage(); //֪ͨ��ӡ����������ҳ����
		dc.EndDoc();//֪ͨ��ӡ�����������ӡ���
		DeleteDC(dc.Detach()); 
	}
}

void CMainFrame::OnActivateApp(BOOL bActive, HTASK hTask) 
{
	CFrameWnd::OnActivateApp(bActive, hTask);
	
	// TODO: Add your message handler code here
	if (bActive == FALSE)
	{
		//��û�м�����ǿ��������ʾ����
		m_wndZgChart.HideTips();
	}
}
