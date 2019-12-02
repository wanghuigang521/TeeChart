// MSCommTestDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MSCommTest.h"
#include "MSCommTestDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

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
// CMSCommTestDlg dialog

CMSCommTestDlg::CMSCommTestDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMSCommTestDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMSCommTestDlg)
	m_strEditRXData = _T("");
	m_strEditTXData = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMSCommTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMSCommTestDlg)
	DDX_Text(pDX, IDC_EDIT_RXDATA, m_strEditRXData);
	DDX_Text(pDX, IDC_EDIT_TXDATA, m_strEditTXData);
	DDX_Control(pDX, IDC_MSCOMM1, m_ctrlComm);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CMSCommTestDlg, CDialog)
	//{{AFX_MSG_MAP(CMSCommTestDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_MANUALSEND, OnButtonManualsend)
	//}}AFX_MSG_MAP
	ON_EN_CHANGE(IDC_EDIT_TXDATA, &CMSCommTestDlg::OnEnChangeEditTxdata)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CMSCommTestDlg::OnCbnSelchangeCombo1)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMSCommTestDlg message handlers

BOOL CMSCommTestDlg::OnInitDialog()
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
	m_ctrlComm.SetCommPort (3);//选择COM3


	m_ctrlComm.SetInputMode (1);//设置通信数据方式为1，即二进制方式


	m_ctrlComm.SetInBufferSize (1024);//设置串口输入缓冲区大小为1024字节
	m_ctrlComm.SetOutBufferSize (512);//设置串口输出缓冲区大小为512字节
	m_ctrlComm.SetSettings ("9600,N,8,1");


	//波特率为9600bps,N为无校验(E为偶校验，O为奇校验)，8位数据位，1位停止位
	m_ctrlComm.SetPortOpen (TRUE);//打开串口


	m_ctrlComm.SetRThreshold (1);//设置接收事件触发的门槛，1表示每当接收到一个及
    //一个以上字节时引发一个接收事件
	m_ctrlComm.SetInputLen (0);//设置读取接收数据长度为0，表示无长度限制，每次读
	//取时一次性读取接收缓冲区中的全部数据



	m_ctrlComm.SetInBufferCount (0);//清空接收缓冲区，即清除接收缓冲区中的残留数据
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMSCommTestDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMSCommTestDlg::OnPaint() 
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
HCURSOR CMSCommTestDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

BEGIN_EVENTSINK_MAP(CMSCommTestDlg, CDialog)
    //{{AFX_EVENTSINK_MAP(CMSCommTestDlg)
	ON_EVENT(CMSCommTestDlg, IDC_MSCOMM1, 1 /* OnComm */, OnComm, VTS_NONE)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

void CMSCommTestDlg::OnComm() 
{
	// TODO: Add your control notification handler code here
	VARIANT variant_inp;
	COleSafeArray safearray_inp;
	LONG len,k;
	BYTE rxdata[2048]; //设置BYTE型数组
	CString strtemp;
	if(m_ctrlComm.GetCommEvent()==2) //事件值为2表示接收数据事件
	{
		variant_inp=m_ctrlComm.GetInput(); //读接收缓冲区
		safearray_inp=variant_inp;  //VARIANT型转换为ColeSafeArray型
		len=safearray_inp.GetOneDimSize(); //得到有效数据长度
		for(k=0;k<len;k++)
			safearray_inp.GetElement(&k,rxdata+k);//转换为BYTE型数组
		for(k=0;k<len;k++)             //将数组转换为Cstring型变量
		{
			BYTE bt=*(char*)(rxdata+k);    //字符型
			strtemp.Format("%c",bt);    //将字符送入临时变量strtemp存放
			//strtemp.Format("%02x ",bt);    //将字符的十六进制码存入strtemp
			m_strEditRXData+=strtemp;  //加入接收编辑框对应字符串变量中    
		}
	}
	UpdateData(FALSE);  //更新编辑框内容，即在接收显示框中显示接收数据	
}

void CMSCommTestDlg::OnButtonManualsend() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE); //读取编辑框内容，获得发送数据
	m_ctrlComm.SetOutput(COleVariant(m_strEditTXData));//发送数据
/*
unsigned char chdata[10];
chdata[0]='A'; chdata[1]='B'; chdata[2]='C';
chdata[3]='\0';chdata[4]=0;
chdata[5]=0xB9; chdata[6]=0xFA; chdata[7]=136;
CByteArray binData;//定义CByteArray类对象-binData
binData.RemoveAll();//清空binData
for(int i=0;i<8;i++) binData.Add(chdata[i]);//字节数据存入binData对象中
COleVariant  var(binData);//将binData转换为COleVariant类型
m_ctrlComm.SetOutput(var);//发送
*/
  }


void CMSCommTestDlg::OnEnChangeEditTxdata()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


void CMSCommTestDlg::OnCbnSelchangeCombo1()
{
	// TODO: 在此添加控件通知处理程序代码
}
