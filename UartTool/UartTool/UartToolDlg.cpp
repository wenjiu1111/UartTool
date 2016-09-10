
// UartToolDlg.cpp : implementation file
//

#include "stdafx.h"
#include "UartTool.h"
#include "UartToolDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CUartToolDlg dialog




CUartToolDlg::CUartToolDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CUartToolDlg::IDD, pParent)
	, m_EditRxData(_T(""))
	, m_EditTxData(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CUartToolDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EditRxData, m_EditRxData);
	DDX_Text(pDX, IDC_EditTxData, m_EditTxData);
	DDX_Control(pDX, IDC_ComboPortNumber, m_ComboPortNumber);
	DDX_Control(pDX, IDC_ComboBaud, m_ComboBaud);
	DDX_Control(pDX, IDC_BtnOpen, m_BtnOpen);
	DDX_Control(pDX, IDC_BtnClose, m_BtnClose);
	DDX_Control(pDX, IDC_BtnSend, m_BtnSend);
	DDX_Control(pDX, IDC_BtnClear, m_BtnClear);
	DDX_Control(pDX, IDC_ComMscomm, m_ComMscomm);
	DDX_Control(pDX, IDC_ChkTimeStamp, m_ChkTimeStamp);
}

BEGIN_MESSAGE_MAP(CUartToolDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BtnOpen, &CUartToolDlg::OnBnClickedBtnopen)
	ON_BN_CLICKED(IDC_BtnClose, &CUartToolDlg::OnBnClickedBtnclose)
	ON_BN_CLICKED(IDC_BtnSend, &CUartToolDlg::OnBnClickedBtnsend)
	ON_BN_CLICKED(IDC_BtnClear, &CUartToolDlg::OnBnClickedBtnclear)
	ON_BN_CLICKED(IDC_BtnQuit, &CUartToolDlg::OnBnClickedBtnQuit)
END_MESSAGE_MAP()


// CUartToolDlg message handlers

BOOL CUartToolDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
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

	// Initialize the port number combobox
	CString strPortNumber;
	for ( int i=0; i<10; i++ )
	{
		strPortNumber.Format( _T("COM %d"), i + 1 );
		m_ComboPortNumber.InsertString( i, strPortNumber );
	}
	m_ComboPortNumber.SetCurSel( 1 );		// Default port: com 2


	// Initialize the baudrate combobox
	CString strBaud[] =
	{
		_T("300"),		_T("600"),		_T("1200"),		_T("2400"),		
		_T("4800"),		_T("9600"),		_T("19200"),	_T("38400"),
		_T("43000"),	_T("56000"),	_T("57600"),	_T("115200"),

	};

	for ( int i=0; i<12; i++ )
	{
		m_ComboBaud.InsertString( i, strBaud[i] );
	}
	m_ComboBaud.SetCurSel( 5 );		// Default baud: 19200

	// Initialize the check box of timestamp
	m_ChkTimeStamp.SetCheck( BST_CHECKED );


	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CUartToolDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CUartToolDlg::OnPaint()
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
HCURSOR CUartToolDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CUartToolDlg::OnBnClickedBtnopen()
{
	// TODO: 在此添加控件通知处理程序代码

	if ( m_ComMscomm.get_PortOpen() )
	{
		m_ComMscomm.put_PortOpen( FALSE );
	}

	if ( !m_ComMscomm.get_PortOpen() )
	{
		CString strPortConfig;
		m_ComboBaud.GetLBText( m_ComboBaud.GetCurSel(), strPortConfig );
		strPortConfig = strPortConfig + ',' + 'n' + ',' + '8' + ','	+ '1';

		m_ComMscomm.put_CommPort( m_ComboPortNumber.GetCurSel() + 1 );
		m_ComMscomm.put_InputMode( 1 );
		m_ComMscomm.put_Settings( strPortConfig );
		m_ComMscomm.put_InputLen( 1024 );
		m_ComMscomm.put_RThreshold( 1 );
		m_ComMscomm.put_RTSEnable( TRUE );

		m_ComMscomm.put_PortOpen( TRUE );

		if ( m_ComMscomm.get_PortOpen() )
		{
			m_BtnOpen.EnableWindow( FALSE );
		}
		else
		{
			m_BtnOpen.EnableWindow( TRUE );
		}


	}

}


void CUartToolDlg::OnBnClickedBtnclose()
{
	// TODO: 在此添加控件通知处理程序代码

	if ( m_ComMscomm.get_PortOpen() )
	{
		m_ComMscomm.put_PortOpen( FALSE );
	}
	
	m_BtnOpen.EnableWindow( TRUE );

}


void CUartToolDlg::OnBnClickedBtnsend()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData( TRUE );
	m_ComMscomm.put_Output( COleVariant( m_EditTxData ) );

}
BEGIN_EVENTSINK_MAP(CUartToolDlg, CDialogEx)
	ON_EVENT(CUartToolDlg, IDC_ComMscomm, 1, CUartToolDlg::OnCommCommscomm, VTS_NONE)
END_EVENTSINK_MAP()


void CUartToolDlg::OnCommCommscomm()
{
	// TODO: 在此处添加消息处理程序代码

	if ( COM_EVT_RECEIVE == m_ComMscomm.get_CommEvent() )
	{
		long i;
		char strRxData[1024] = { 0 };

		// Get the system time
		SYSTEMTIME sysTime;
		GetLocalTime(&sysTime);

		CString strTime;
		strTime.Format( _T("%2d:%2d:%2d:%3d: "), 
			sysTime.wHour, 
			sysTime.wMinute, 
			sysTime.wSecond, 
			sysTime.wMilliseconds );

		// Process the input data
		COleSafeArray InputData = m_ComMscomm.get_Input();

		for ( i=0; i<InputData.GetOneDimSize(); i++ )
		{
			InputData.GetElement( &i, strRxData + i );
		}

		strRxData[i++] = '\r';
		strRxData[i] = '\n';

		if ( BST_UNCHECKED == m_ChkTimeStamp.GetCheck() )
		{
			strTime.Empty();
		}

		m_EditRxData += strTime;
		m_EditRxData += strRxData;

		UpdateData( FALSE );

		//CEdit *pEditControl = (CEdit *)::GetDlgItem( m_hWnd, IDC_EditRxData );
		//pEditControl->LineScroll( pEditControl->GetLineCount() - 1, 0 );
		//UpdateData( FALSE );

	}

}


void CUartToolDlg::OnBnClickedBtnclear()
{
	// TODO: 在此添加控件通知处理程序代码

	m_EditRxData.Empty();

	UpdateData( FALSE );

}


void CUartToolDlg::OnBnClickedBtnQuit()
{
	// TODO: 在此添加控件通知处理程序代码
	if ( m_ComMscomm.get_PortOpen() )
	{
		m_ComMscomm.put_PortOpen( FALSE );
	}

	EndDialog( IDCANCEL );
}
