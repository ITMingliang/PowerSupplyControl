
// TestDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "Test.h"
#include "TestDlg.h"
#include "afxdialogex.h"
#include "COM_RS232.h"
#include "GPIB.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CTestDlg 对话框



CTestDlg::CTestDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_TEST_DIALOG, pParent)
	
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//  DDX_CBString(pDX, IDC_COMBO1, Bitter);
	DDX_Control(pDX, IDC_COMBO1, ComboBit);
	DDX_Control(pDX, RADIO_USB, RadioUsb);
	DDX_Control(pDX, RADIO_GPIB, RadioGpib);
	DDX_Control(pDX, RADIO_RS232, RadioRs232);
}

BEGIN_MESSAGE_MAP(CTestDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(BtnInit, &CTestDlg::OnBnClickedBtninit)
	ON_BN_CLICKED(IDC_BUTTON5, &CTestDlg::OnBnClickedButton5)
	ON_BN_CLICKED(BtnV, &CTestDlg::OnBnClickedBtnv)
	ON_BN_CLICKED(BtnA, &CTestDlg::OnBnClickedBtna)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CTestDlg::OnCbnSelchangeCombo1)
	ON_BN_CLICKED(IDC_BUTTON1, &CTestDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CTestDlg::OnBnClickedButton2)
	ON_BN_CLICKED(RADIO_POWER1, &CTestDlg::OnBnClickedPower1)
	ON_BN_CLICKED(RADIO_POWER2, &CTestDlg::OnBnClickedPower2)
	ON_BN_CLICKED(RADIO_USB, &CTestDlg::OnBnClickedUsb)
	ON_BN_CLICKED(RADIO_RS232, &CTestDlg::OnBnClickedRs232)
	ON_BN_CLICKED(RADIO_GPIB, &CTestDlg::OnBnClickedGpib)
	ON_BN_CLICKED(SetV, &CTestDlg::OnBnClickedSetv)
	ON_BN_CLICKED(SetV2, &CTestDlg::OnBnClickedSetv2)
	ON_BN_CLICKED(IDC_BUTTON3, &CTestDlg::OnBnClickedButton3)
END_MESSAGE_MAP()


// CTestDlg 消息处理程序

BOOL CTestDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标
	// TODO: 在此添加额外的初始化代码
	ComboBit.SetCurSel(3);
	GetDlgItem(IDC_EDIT2)->SetWindowText("USB0::0xFFFF::0x6800::800445020737430017::INSTR");
	GetDlgItem(IDC_EDIT2)->EnableWindow(FALSE);
	SetDlgItemText(IDC_EDIT1, "3");
	SetDlgItemText(IDC_EDIT3, "3");
	ModifyStyle(WS_THICKFRAME, 0, NULL);
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CTestDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CTestDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CTestDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}
 

//初始化
void CTestDlg::OnBnClickedBtninit()
{
	int usb = RadioUsb.GetCheck();
	int gpib = RadioGpib.GetCheck();
	int RS232 = RadioRs232.GetCheck();
	if (usb) {
		GetDlgItem(IDC_EDIT2)->GetWindowText(strInit);
	}
	if (gpib) {
		ComboBit.GetWindowTextA(strInit);
	}
	if (RS232) {
		ComboBit.GetWindowTextA(strInit);
	}
	bool a = myGpib.Initial(strInit);
	if (!a) {
		MessageBoxA("初始化错误！");
	}
	else
	{
		myGpib.WriteCmd("*IDN?\n");
		Sleep(100);
		CString str = myGpib.ReadCmd();
		Sleep(1500);
		myGpib.WriteCmd("SYSTem:REMote\n");
		MessageBoxA(str);
		str.ReleaseBuffer();
	}
	
}

//开机
void CTestDlg::OnBnClickedButton5()
{
	myGpib.WriteCmd("OUTP ON\n");
	MessageBoxA("开机完成");
}


//读电压
void CTestDlg::OnBnClickedBtnv()
{
	CString str = " "; 
	str = myGpib.QueryCmd("VOLTage?\n");
	int a = str.GetLength();
	str = str.Left(str.GetLength() - 1);
	str = "电压为" + str + "V";
	MessageBoxA(str);
}


//读电流
void CTestDlg::OnBnClickedBtna()
{
	// TODO: 在此添加控件通知处理程序代码
	CString str = " ";
	str = myGpib.QueryCmd("CURR?\n");
	int a = str.GetLength();
	str = str.Left(str.GetLength() - 1);
	str = "电流为" + str + "A";
	MessageBoxA(str);
}

void CTestDlg::OnCbnSelchangeCombo1()
{
	// TODO: 在此添加控件通知处理程序代码

}


//关机
void CTestDlg::OnBnClickedButton1()
{
	myGpib.WriteCmd("OUTP OFF\n");
	MessageBoxA("关机完成");
	
}


//重置
void CTestDlg::OnBnClickedButton2()
{
	bool a = myGpib.WriteCmd("*CLS;*RST;\n");
	if (a==true) {
		MessageBoxA("初始化成功！");
	}
	else {
		MessageBoxA("初始化失败！请检查连接！");
	}
}


//IT6872A
void CTestDlg::OnBnClickedPower1()
{
	// TODO: 在此添加控件通知处理程序代码
	GetDlgItem(RADIO_GPIB)->EnableWindow(FALSE);
	GetDlgItem(RADIO_USB)->EnableWindow(TRUE); 
	GetDlgItem(RADIO_RS232)->EnableWindow(TRUE);
	RadioUsb.SetCheck(0); 
	RadioGpib.SetCheck(0);
	RadioRs232.SetCheck(0);
}


//程控电源
void CTestDlg::OnBnClickedPower2()
{
	// TODO: 在此添加控件通知处理程序代码
	GetDlgItem(RADIO_GPIB)->EnableWindow(TRUE);
	GetDlgItem(RADIO_USB)->EnableWindow(FALSE);
	GetDlgItem(RADIO_RS232)->EnableWindow(FALSE);
	ComboBit.ResetContent();
	RadioUsb.SetCheck(0);
	RadioGpib.SetCheck(1);
	OnBnClickedGpib();
	RadioRs232.SetCheck(0);
}



void CTestDlg::OnBnClickedUsb()
{
	// TODO: 在此添加控件通知处理程序代码
	ComboBit.ResetContent();
	GetDlgItem(IDC_COMBO1)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT2)->EnableWindow(TRUE);
}


void CTestDlg::OnBnClickedRs232()
{
	// TODO: 在此添加控件通知处理程序代码
	GetDlgItem(IDC_COMBO1)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDIT2)->EnableWindow(FALSE);
	ComboBit.ResetContent();
	ComboBit.AddString("COM1");
	ComboBit.AddString("COM2");
	ComboBit.AddString("COM3");
	ComboBit.AddString("COM6");
}


void CTestDlg::OnBnClickedGpib()
{
	// TODO: 在此添加控件通知处理程序代码
	GetDlgItem(IDC_COMBO1)->EnableWindow(TRUE);
	ComboBit.ResetContent();
	ComboBit.AddString("GPIB0::16::INSTR");
	ComboBit.AddString("GPIB::15::INSTR");
	ComboBit.AddString("GPIB::14::INSTR");
	ComboBit.AddString("GPIB::13::INSTR");
}


//设置电压
void CTestDlg::OnBnClickedSetv()
{
	// TODO: 在此添加控件通知处理程序代码
	CString str_V = "";
	float fV = 0.0f;
	GetDlgItemText(IDC_EDIT1, str_V);
	fV = atof(str_V);
	str_V.Format("VOLT %0.1f\n", fV);
	myGpib.WriteCmd(str_V);
	GetDlgItemText(IDC_EDIT1, str_V);
	CString a = "已经设置电压为" + str_V + "V";
	MessageBoxA(a);
}



//设置电流
void CTestDlg::OnBnClickedSetv2()
{
	// TODO: 在此添加控件通知处理程序代码
	CString str_V = "";
	float fV = 0.0f;
	GetDlgItemText(IDC_EDIT3, str_V);
	fV = atof(str_V);
	str_V.Format("CURR %0.1f\n", fV);
	myGpib.WriteCmd(str_V);
	GetDlgItemText(IDC_EDIT3, str_V);
	CString a = "已经设置电流为" + str_V + "A";
	MessageBoxA(a);
}

//断开连接
void CTestDlg::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	myGpib.UnInitial();
	Sleep(1000);
	CDialogEx::DestroyWindow();
}
