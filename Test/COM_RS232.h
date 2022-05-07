// COM_RS232.h: interface for the COM_RS232 class.
//
//////////////////////////////////////////////////////////////////////
#include "pch.h"
#if !defined(AFX_OM_RS232_H__2CA43459_F9E4_4020_85CE_4B2E760C012D__INCLUDED_)
#define AFX_OM_RS232_H__2CA43459_F9E4_4020_85CE_4B2E760C012D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class COM_RS232  
{
public:                 //liushui_lin  define
	CString m_sResult;

	COM_RS232();
	virtual ~COM_RS232();
	bool COM_OpenDev(CString sComPort);
	bool COM_InitDev(UINT rate,DWORD inbuffer,DWORD outbuffer);
	bool COM_SetTimeout(UINT interval_read,
		                UINT speed_read,
		                UINT constant_read, 
						UINT speed_write,
						UINT constant_write );
	bool COM_Write(CString strCmd);
	CString COM_Read(void);
	CString COM_QueryEx(CString strCmd);
	CString COM_Query(CString strCmd);
	bool COM_Close(void);

	CString m_sComPortNum;
    HANDLE m_hDev;
	DCB m_dcb;
    COMMTIMEOUTS m_ComTimeOut;
    COMSTAT	m_ComState;
	CString m_ComPortName;

private:

};

#endif // !defined(AFX_OM_RS232_H__2CA43459_F9E4_4020_85CE_4B2E760C012D__INCLUDED_)
