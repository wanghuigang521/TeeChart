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
	m_ctrlComm.SetCommPort (3);//ѡ��COM3


	m_ctrlComm.SetInputMode (1);//����ͨ�����ݷ�ʽΪ1���������Ʒ�ʽ


	m_ctrlComm.SetInBufferSize (1024);//���ô������뻺������СΪ1024�ֽ�
	m_ctrlComm.SetOutBufferSize (512);//���ô��������������СΪ512�ֽ�
	m_ctrlComm.SetSettings ("9600,N,8,1");


	//������Ϊ9600bps,NΪ��У��(EΪżУ�飬OΪ��У��)��8λ����λ��1λֹͣλ
	m_ctrlComm.SetPortOpen (TRUE);//�򿪴���


	m_ctrlComm.SetRThreshold (1);//���ý����¼��������ż���1��ʾÿ�����յ�һ����
    //һ�������ֽ�ʱ����һ�������¼�
	m_ctrlComm.SetInputLen (0);//���ö�ȡ�������ݳ���Ϊ0����ʾ�޳������ƣ�ÿ�ζ�
	//ȡʱһ���Զ�ȡ���ջ������е�ȫ������



	m_ctrlComm.SetInBufferCount (0);//��ս��ջ���������������ջ������еĲ�������
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
	BYTE rxdata[2048]; //����BYTE������
	CString strtemp;
	if(m_ctrlComm.GetCommEvent()==2) //�¼�ֵΪ2��ʾ���������¼�
	{
		variant_inp=m_ctrlComm.GetInput(); //�����ջ�����
		safearray_inp=variant_inp;  //VARIANT��ת��ΪColeSafeArray��
		len=safearray_inp.GetOneDimSize(); //�õ���Ч���ݳ���
		for(k=0;k<len;k++)
			safearray_inp.GetElement(&k,rxdata+k);//ת��ΪBYTE������
		for(k=0;k<len;k++)             //������ת��ΪCstring�ͱ���
		{
			BYTE bt=*(char*)(rxdata+k);    //�ַ���
			strtemp.Format("%c",bt);    //���ַ�������ʱ����strtemp���
			//strtemp.Format("%02x ",bt);    //���ַ���ʮ�����������strtemp
			m_strEditRXData+=strtemp;  //������ձ༭���Ӧ�ַ���������    
		}
	}
	UpdateData(FALSE);  //���±༭�����ݣ����ڽ�����ʾ������ʾ��������	
}

void CMSCommTestDlg::OnButtonManualsend() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE); //��ȡ�༭�����ݣ���÷�������
	m_ctrlComm.SetOutput(COleVariant(m_strEditTXData));//��������
/*
unsigned char chdata[10];
chdata[0]='A'; chdata[1]='B'; chdata[2]='C';
chdata[3]='\0';chdata[4]=0;
chdata[5]=0xB9; chdata[6]=0xFA; chdata[7]=136;
CByteArray binData;//����CByteArray�����-binData
binData.RemoveAll();//���binData
for(int i=0;i<8;i++) binData.Add(chdata[i]);//�ֽ����ݴ���binData������
COleVariant  var(binData);//��binDataת��ΪCOleVariant����
m_ctrlComm.SetOutput(var);//����
*/
  }


void CMSCommTestDlg::OnEnChangeEditTxdata()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialog::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void CMSCommTestDlg::OnCbnSelchangeCombo1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}
