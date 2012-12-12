#ifndef ZGCHARTLIB_H
#define ZGCHARTLIB_H

//ZgChartLib Copyright 2004-2005 ZhuGang
//名  称:曲线显示库
//头文件:ZgChartLib.h
//库文件:ZgChartLib.lib
//////////////////////////////////////////////////////////////////////////
//功  能:类似mschart
//说  明1:横向坐标为时间值
//说  明2:纵向坐标为数值(float)

//功能详细说明如下
//1:时间相关联数据的显示
//2:最多10条曲线同时显示
//3:曲线信息保存到位图文件
//4:曲线信息打印：需要传入打印DC，在例子程序中我给出了详细的代码
//5:曲线显示时动态调整是否显示(左键点击曲线图例)
//6:曲线当前鼠标位置数据半透明显示(Windows2000以上支持)
//7:曲线纵向数值显示
//8:曲线动态调整颜色和线宽（右键点击曲线图例，必须保留对话框资源IDD_DIALOG_LINE_SET,否则不能使用）

//一些说明:由于这个库封装成静态Lib,对话框资源的获取出现问题，本人还没有找到方法解决，但如果使用DLL就没有问题/
//如果有人知道如何获取静态Lib中的资源方法，谢谢教教我

//////////////////////////////////////////////////////////////////////////
//大家可以随便使用本链接库，但请保留这些说明文字
//如有问题和BUG请与我联系：sonystone@tom.com, sonystone@163.com
//如有需要C++源代码，请与本人联系
//请参考例子程序
//请不要修改以下代码，否则出现错误

//////////////////////////////////////////////////////////////////////////
class CZgMemDC : public CDC 
{
	CZgMemDC(CDC* pDC, const CRect* pRect = NULL);
	~CZgMemDC();
};

//////////////////////////////////////////////////////////////////////////
class CZgBitmap : public CBitmap  
{
public:
	CZgBitmap();
	virtual ~CZgBitmap();
};

//////////////////////////////////////////////////////////////////////////
// CColourPopup messages
#define CPN_SELCHANGE        WM_USER + 1001        // Colour Picker Selection change
#define CPN_DROPDOWN         WM_USER + 1002        // Colour Picker drop down
#define CPN_CLOSEUP          WM_USER + 1003        // Colour Picker close up
#define CPN_SELENDOK         WM_USER + 1004        // Colour Picker end OK
#define CPN_SELENDCANCEL     WM_USER + 1005        // Colour Picker end (cancelled)

// forward declaration
class CColourPicker;

// To hold the colours and their names
typedef struct {
    COLORREF crColour;
    TCHAR    *szName;
} ColourTableEntry;

/////////////////////////////////////////////////////////////////////////////
// CColourPopup window

class CColourPopup : public CWnd
{
// Construction
public:
    CColourPopup();
    CColourPopup(CPoint p, COLORREF crColour, COLORREF crDefaultColour, CWnd* pParentWnd,
                 LPCTSTR szDefaultText = NULL, LPCTSTR szCustomText = NULL);
    void Initialise();

	void SetDefaultColor(COLORREF crColour) { m_crDefaultColour = crColour; }


// Attributes
public:

// Operations
public:
    BOOL Create(CPoint p, COLORREF crColour, CWnd* pParentWnd, 
                LPCTSTR szDefaultText = NULL, LPCTSTR szCustomText = NULL);

// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CColourPopup)
    public:
    virtual BOOL PreTranslateMessage(MSG* pMsg);
    //}}AFX_VIRTUAL

// Implementation
public:
	void SetDefaultColour(COLORREF crDefaultColour);
    virtual ~CColourPopup();

protected:
    BOOL GetCellRect(int nIndex, const LPRECT& rect);
    void FindCellFromColour(COLORREF crColour);
    void SetWindowSize();
    void CreateToolTips();
    void ChangeSelection(int nIndex);
    void EndSelection(int nMessage);
    void DrawCell(CDC* pDC, int nIndex);

    COLORREF GetColour(int nIndex)              { return m_crColours[nIndex].crColour; }
    LPCTSTR GetColourName(int nIndex)           { return m_crColours[nIndex].szName; }
    int  GetIndex(int row, int col) const;
    int  GetRow(int nIndex) const;
    int  GetColumn(int nIndex) const;

// protected attributes
protected:
    static ColourTableEntry m_crColours[];
    int            m_nNumColours;
    int            m_nNumColumns, m_nNumRows;
    int            m_nBoxSize, m_nMargin;
    int            m_nCurrentSel;
    int            m_nChosenColourSel;
    CString        m_strDefaultText;
    CString        m_strCustomText;
    CRect          m_CustomTextRect, m_DefaultTextRect, m_WindowRect;
    CFont          m_Font;
    CPalette       m_Palette;
    COLORREF       m_crInitialColour, m_crColour;
	COLORREF	   m_crDefaultColour;
    CToolTipCtrl   m_ToolTip;
    CWnd*          m_pParent;


    // Generated message map functions
protected:
    //{{AFX_MSG(CColourPopup)
    afx_msg void OnNcDestroy();
    afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
    afx_msg void OnPaint();
    afx_msg void OnMouseMove(UINT nFlags, CPoint point);
    afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
    afx_msg BOOL OnQueryNewPalette();
    afx_msg void OnPaletteChanged(CWnd* pFocusWnd);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnActivateApp(BOOL bActive, HTASK hTask);
	//}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};


//////////////////////////////////////////////////////////////////////////
void AFXAPI DDX_ColourPicker(CDataExchange *pDX, int nIDC, COLORREF& crColour);

/////////////////////////////////////////////////////////////////////////////
// CColourPicker window

#define CP_MODE_TEXT 1  // edit text colour
#define CP_MODE_BK   2  // edit background colour (default)

class CColourPicker : public CButton
{
// Construction
public:
    CColourPicker();
    DECLARE_DYNCREATE(CColourPicker);

// Attributes
public:
    COLORREF GetColour();
    void     SetColour(COLORREF crColour); 

    void     SetDefaultText(LPCTSTR szDefaultText);
    void     SetCustomText(LPCTSTR szCustomText);

    void     SetTrackSelection(BOOL bTracking = TRUE)  { m_bTrackSelection = bTracking; }
    BOOL     GetTrackSelection()                       { return m_bTrackSelection; }

    void     SetSelectionMode(UINT nMode)              { m_nSelectionMode = nMode; }
    UINT     GetSelectionMode()                        { return m_nSelectionMode; };

    void     SetBkColour(COLORREF crColourBk);
    COLORREF GetBkColour()                             { return m_crColourBk; }
    
    void     SetTextColour(COLORREF crColourText);
    COLORREF GetTextColour()                           { return m_crColourText;}

	//void	 SetDefaultColour(COLORREF crColour) {  m_crColourBk = m_crColourText = crColour; }
	void	 SetDefaultColour(COLORREF crColour) {  m_crDefaultBkColour = crColour; }


// Operations
public:

// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CColourPicker)
    public:
    virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
    protected:
    virtual void PreSubclassWindow();
    //}}AFX_VIRTUAL

// Implementation
public:
    virtual ~CColourPicker();

protected:
    void SetWindowSize();

// protected attributes
protected:
    BOOL     m_bActive,                // Is the dropdown active?
             m_bTrackSelection;        // track colour changes?
    COLORREF m_crColourBk;
    COLORREF m_crColourText;
    UINT     m_nSelectionMode;
    CRect    m_ArrowRect;
    CString  m_strDefaultText;
    CString  m_strCustomText;
	COLORREF m_crDefaultColour;
	COLORREF m_crDefaultBkColour;

    // Generated message map functions
protected:
    //{{AFX_MSG(CColourPicker)
    afx_msg BOOL OnClicked();
    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
    //}}AFX_MSG
    afx_msg LONG OnSelEndOK(UINT lParam, LONG wParam);
    afx_msg LONG OnSelEndCancel(UINT lParam, LONG wParam);
    afx_msg LONG OnSelChange(UINT lParam, LONG wParam);

    DECLARE_MESSAGE_MAP()
};



//////////////////////////////////////////////////////////////////////////
typedef struct STRU_TIPSHOW_DATA
{
	CString		strTipsText;			//提示文本
	COLORREF	crTipsColor;			//提示文本颜色
}TipShowData;
//////////////////////////////////////////////////////////////////////////
class CZgChartTips  
{
public:
	CZgChartTips();
	virtual ~CZgChartTips();

protected:
	void DrawTips(CDC *pDC, CRect &rcDraw, TipShowData *pData);
	void DrawAllTips(CDC *pDC, CRect &rcDraw);
	BOOL MakeChartTips(CDC *pDC);
	CZgBitmap m_BitmapTips;
	CSize m_szMaxText;
	CPtrList m_TipsList;
	CSize m_szBitmap;
	CFont m_FontText;
};

//////////////////////////////////////////////////////////////////////////
class CZgChartTipsWnd : public CWnd
{
	DECLARE_DYNAMIC(CZgChartTipsWnd);
// Construction
public:
	CZgChartTipsWnd();

// Attributes
public:
	CZgChartTips *mp_ChartTips;
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CZgChartTipsWnd)
	protected:
	//}}AFX_VIRTUAL

// Implementation
public:
	BOOL CreateTipsWnd(CRect rect, CWnd *pParent);
	virtual ~CZgChartTipsWnd();

	// Generated message map functions
protected:
	CWnd *mp_Parent;
	BOOL SetTransparent(HWND hWnd, COLORREF crKey, BYTE bAlpha, DWORD dwFlags);
	HMODULE	m_hUserDll ;		//DLL
	//{{AFX_MSG(CZgChartTipsWnd)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnPaint();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

typedef struct STRU_CUTLINE_DATA
{
	char		szCutlineName[40];		//图例名称
	COLORREF	crCutlineColor;			//图例颜色
	UINT		nLineWidth;				//曲线宽度
	CRect		rcPos;					//图例位置
	BOOL		bStatus;				//图例状态
}CutlineData;

//////////////////////////////////////////////////////////////////////////
class CZgChartCutline
{
// Construction
public:
	CZgChartCutline();

public:
	void UpdateCutlinePara(COLORREF crColor, UINT nLineWidth, int nIndex);
	BOOL GetCutlineStatusByIndex(int nIndex);
	void ReverseStatus(int nIndex);
	BOOL GetCutlineRectByIndex(CRect &rcPos, int nIndex);
	BOOL GetCutlineColorInfoByIndex(COLORREF &crColor, UINT &nLineWidth, int nIndex);
	BOOL GetCutlineInfoByIndex(CString &strName, COLORREF &crColor, int nIndex);
	void ShowChartCutline(CDC *pDC, CRect &rcDraw);
	BOOL AddChartCutline(char szName[], COLORREF crColor, UINT nLineWidth=2, BOOL bClearData=FALSE);
	void EmptyData();
	virtual ~CZgChartCutline();

protected:
	void DrawCutline(CDC *pDC, CRect &rcDraw, CutlineData *pData);
	void DrawAllCutline(CDC *pDC, CRect &rcClient);
	CPtrList m_CutlineList;
};


//////////////////////////////////////////////////////////////////////////
#define IDD_DIALOG_LINE_SET             101
#define IDC_COMBO_LINEWIDTH             1038
#define IDC_BUTTON_LINECOLOR            1039

class CZgChartLineSetDlg : public CDialog
{
// Construction
public:
	CZgChartLineSetDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CZgChartLineSetDlg)
	enum { IDD = IDD_DIALOG_LINE_SET };
	CColourPicker	m_LineColor;
	int		mi_LineWidth;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CZgChartLineSetDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CZgChartLineSetDlg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


//////////////////////////////////////////////////////////////////////////
#define MAX_CURVE_COUNT	10		//最大曲线条数
typedef struct STRU_CHART_DATA
{
	int			nValueTime;		//时间点
	float		fValue;			//值
	BOOL		bValid;			//是否有效
}ChartData;


class CZgChartView : public CWnd
{
// Construction
public:
	CZgChartView();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CZgChartView)
	public:
	//}}AFX_VIRTUAL

// Implementation
public:
	//设置时间间隔，可以不设置，但在获取数值会出现一些小问题
	void SetTimeSpin(int nTimeSpin);

	//保存当前曲线到指定位图文件
	BOOL SaveChartToFile(CString &strFileName);

	//打印当前曲线
	void PrintChart(CDC *pDC);

	//强制隐藏当前提示窗体
	void HideTips();

	//设置曲线标题文本
	void SetTitleText(CString &strTitle);

	//添加曲线数据信息
	BOOL AddChartData(int nIndex, int nTime, float fValue, BOOL bValid=TRUE);

	//设置纵向坐标的范围
	void SetYValue(int nMin, int nMax);

	//添加曲线类型
	BOOL AddChartCutline(char szName[], COLORREF crColor, UINT nLineWidth=2, BOOL bClearData=FALSE);
	
	//日期设置,间隔时天的倍数，最好能够被24整除
	void SetXDate(int nStart, int nStop);

	//创建曲线显示窗体
	BOOL CreateChartView(CWnd *pParentWnd, CRect &rect);
	virtual ~CZgChartView();

	// Generated message map functions
protected:
	CZgChartCutline m_ChartCutline;		//曲线图例
	CZgChartTips	m_ChartTips;		//曲线提示
	
	int mi_SpinX;			//X轴等分大小
	int mi_SpinY;			//Y轴等分大小

	int mi_MarginTop;		//曲线顶部间隔	
	int mi_MarginBottom;	//曲线底部间隔
	int mi_MarginLeft;		//曲线左边间隔
	int mi_MarginRight;		//曲线右边间隔

	int mi_SpinWidth;		//X轴宽度
	int mi_SpinHeight;		//Y轴高度

	COLORREF m_crTitleText;	//标题文本颜色
	CString m_strTitleText;	//标题文本
	UINT	mi_TitleAlign;	//标题文本对齐类型：左，中，右

	COLORREF m_crDate;		//显示提示中时间的颜色
	COLORREF m_crBackground;//曲线背景颜色
	COLORREF m_crScaleText;	//刻度文本颜色
	COLORREF m_crLinePoint;	//点线颜色

	UINT mi_TimerMove;		//定时器

	CPoint m_ptSave;		//坐标保存点

	int	mi_MinX;			//X轴最小值
	int mi_MaxX;			//X轴最大值

	int mi_MinY;			//Y轴最小值
	int mi_MaxY;			//Y轴最大值

	int mi_DayCount;		//天数

	CFont m_FontText;		//文本字体
	CFont m_FontTitle;		//标题文字字体

	CPen m_PenCoordinate;	//坐标轴
	CPen m_PenArrow;		//坐标轴箭头
	CPen m_PenSpinLine;		//坐标轴分割线
	CPen m_PenPosLine;		//鼠标在曲线中的定位线

	CRect m_rcClient;		//整个客户，在ONSIZE事件中更新
	CRect m_rcCurve;		//曲线

	int	mi_CurveCount;		//曲线条数

	BOOL mi_DrawLineSmooth;	//是否使用Bezier来平滑画线
	BOOL mi_TipsWithMouse;	//显示提示是否跟随光标
	BOOL mi_DrawLineVertical;//非Bezier来平滑画线时候是否采用直方图方式

	CPtrList m_DataList[MAX_CURVE_COUNT];		//最多十条曲线的数据保存点

	int mi_TimeSpin;		//数据时间间隔

protected:
	int mi_CurDataIndexSave;
	CZgChartTipsWnd m_ChartTipsWnd;
	BOOL SaveBitmapToFile(HBITMAP hBitmap , CString &strFileName);
	void DrawYFloatTextFromValue(CDC *pDC, CPoint ptText, float fValue);
	void DrawCutline(CDC* pDC, CRect &rcClient);
	void DrawCrossLine(CDC *pDC);
	void DrawChartTips(CDC *pDC);
	int GetDateStringByX(CString &strDate, int nChartIndex);
	void DatePointToChartPoint(CPoint &ptChart, int nTime, float fValue);
	void DrawSingleCurveSmooth(CDC *pDC, int nIndex, CRect &rcDraw);
	void DrawSingleCurveNoSmooth(CDC *pDC, int nIndex, CRect &rcDraw);
	void GetXStringByPos(CString &strText);
	float GetYValueByPos();
	void DrawFloatTextFromValue(CDC *pDC, CPoint ptText, float fValue);
	void DrawDateTextFromValue(CDC *pDC, CPoint ptText, int nValue);
	void DrawFloatTextFromValue(CDC *pDC, CPoint ptText, int nValue);
	void DrawChartTitle(CDC *pDC, CRect &rcDraw, BOOL bPrint=FALSE);
	void DrawCurve(CDC *pDC, CRect &rcDraw);
	void DrawCoordinate(CDC *pDC, CRect &rcDraw);
	//{{AFX_MSG(CZgChartView)
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#endif

