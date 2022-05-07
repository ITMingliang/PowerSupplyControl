
// TestDlg.h: 头文件
//

#pragma once

#include "COM_RS232.h"
#include "GPIB.h"
// CTestDlg 对话框
class CTestDlg : public CDialogEx
{
// 构造
public:
	CTestDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TEST_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数

	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtninit();
	COM_RS232 pCom;
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedBtnv();
	afx_msg void OnBnClickedBtna();
	afx_msg void OnCbnSelchangeCombo1();
	// 波特率控件// 波特率控件
	CComboBox ComboBit;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedPower1();
	afx_msg void OnBnClickedPower2();
	// USB
	CButton RadioUsb;
	// Gpib选项
	CButton RadioGpib;
	CButton RadioRs232;
	afx_msg void OnBnClickedUsb();
	afx_msg void OnBnClickedRs232();
	afx_msg void OnBnClickedGpib();
	GPIB myGpib;
	CString strInit;
	afx_msg void OnBnClickedSetv();
	afx_msg void OnBnClickedSetv2();
	afx_msg void OnBnClickedButton3();
};
