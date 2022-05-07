#pragma once
#include "visa.h"
#pragma comment(lib,"visa64.lib")


// GPIB

class GPIB : public CWnd
{
	DECLARE_DYNAMIC(GPIB)

public:
	GPIB();
	virtual ~GPIB();
	
	bool Initial(CString strCom);
	bool WriteCmd(CString strCmd);
	CString ReadCmd();
	CString QueryCmd(CString strCmd);
	bool UnInitial();

	ViSession defaultRM;
	ViStatus status, StatusSession;
	ViSession inst, Sessionparam;


protected:
	DECLARE_MESSAGE_MAP()
};


