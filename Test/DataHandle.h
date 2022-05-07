#pragma once
#include "io.h"
#include "COMDEF.H"
#include "Wbemidl.h"
#include "pch.h"
#pragma comment(lib,"wbemuuid.lib")
class CDataHandle
{
public:
	CDataHandle(void);
	~CDataHandle(void);
	typedef struct USBINFO
	{
		CString mName[50];
		CString mCaption[50];
		CString mDeviceID[50];

	};
public:
	CString ReadDatatoString(CString App,CString Key);
	CString ReadDatatoStringEx(CString sApp,CString sKey,CString DefaultValue);
	void WriteDatatoStringEx(CString sApp,CString sKey,CString data);
	BOOL ShellEXE(CString Cmd,int nShowCmd);
	CString GetTime();
	CString GetDate();
	bool SaveLog(CString path,CString log,bool AppendWrite);
	bool SaveResult(CString mResult);
	bool SaveITPMResult(CString mResult);
	BOOL SaveParams(CString szName, CString szParams);
	bool CDataHandle::CreateLog();
	bool CheckUSBDeviceInfo(CString mCmd,USBINFO &);
	CString InttoStr(int);
	CString WriteDatatoString(CString App,CString Key,CString data);
};
