// COM_RS232.cpp: implementation of the COM_RS232 class.
//
//////////////////////////////////////////////////////////////////////

//#include "WWANDlg.h"
//#include "WWAN.h"
#include "pch.h"
#include "COM_RS232.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
//======================================================================================//
//======================================================================================//


COM_RS232::COM_RS232()
{
	m_ComPortName="";
}
//======================================================================================//
COM_RS232::~COM_RS232()
{

}

//=====================Open the specified port=========================================//
bool COM_RS232::COM_OpenDev(CString sComPort)
{
	if(sComPort.Find("\\\\.\\")<0)
	{
		sComPort="\\\\.\\"+sComPort;
	}
    m_hDev=CreateFile(sComPort,GENERIC_READ|GENERIC_WRITE,0,NULL, OPEN_EXISTING, 0, NULL);
	if (m_hDev==INVALID_HANDLE_VALUE)
	{
		//AfxMessageBox("x1");
		return false;	
	}
    else	 
	{
		return true;
	}
}

//===================Set the band rate and Input/output buffer size====================//
bool COM_RS232::COM_InitDev(UINT rate,DWORD inbuffer,DWORD outbuffer)
{
    if(!SetupComm(m_hDev,inbuffer,outbuffer))
	{
		//AfxMessageBox("x2");
		return false;	
	}
	if(!GetCommState(m_hDev,&m_dcb))
   {
	  // AfxMessageBox("x3");
		return false;  
   }
   switch (rate)
   {
        case 1200 :
            m_dcb.BaudRate = CBR_1200;
            break ;
        case 2400 :
            m_dcb.BaudRate = CBR_2400;
            break ;
        case 4800 :
            m_dcb.BaudRate = CBR_4800;
            break ;
        case 9600 :
            m_dcb.BaudRate = CBR_9600;
            break ;
        case 19200 :
            m_dcb.BaudRate = CBR_19200;
            break ;
        case 38400 :
            m_dcb.BaudRate = CBR_38400;
            break ;
        case 57600 :
            m_dcb.BaudRate = CBR_57600;
            break ;
        case 115200 :
            m_dcb.BaudRate = CBR_115200;
            break ; 
		default:
			m_dcb.BaudRate = CBR_9600;
   }
   
    m_dcb.ByteSize = 8;
    m_dcb.Parity = NOPARITY;
    m_dcb.StopBits = ONESTOPBIT;
    if( !SetCommState(m_hDev, &m_dcb))
	{
		//AfxMessageBox("x4");
		return false;
    }
    else
	{
	   PurgeComm(m_hDev, PURGE_TXCLEAR); 
       return true ;
	}
}
//=================Set timeout for read/write operation=================================//
bool COM_RS232::COM_SetTimeout(UINT interval_read,
							   UINT speed_read,
							   UINT constant_read, 
						       UINT speed_write,
						       UINT constant_write)
{
   if(!GetCommTimeouts(m_hDev,&m_ComTimeOut))
   {
	   return false;   
   }
   m_ComTimeOut.ReadIntervalTimeout				= interval_read;
   m_ComTimeOut.ReadTotalTimeoutConstant		= constant_read;
   m_ComTimeOut.ReadTotalTimeoutMultiplier		= speed_read;
   m_ComTimeOut.WriteTotalTimeoutConstant		= constant_write;
   m_ComTimeOut.WriteTotalTimeoutMultiplier		= speed_write;
    if(!SetCommTimeouts(m_hDev,&m_ComTimeOut))
	{ 
		return false;	
	}
    else 
	 { 
	     return true;
	 }
}
//======================================================================================//
bool COM_RS232::COM_Write(CString cmd)
{
    DWORD hLength;
	cmd=cmd+'\r';
	if(!WriteFile(m_hDev,cmd,cmd.GetLength(),&hLength,NULL))
	{		
			if(!WriteFile(m_hDev,cmd,cmd.GetLength(),&hLength,NULL))
			{
				return	false;
			}
		return false;		
	}
	else
	{
	    return	true;
	}
}
//======================================================================================//
CString COM_RS232::COM_Read(void)
{
	Sleep(20);
	DWORD error,len;
	char buffer[1024]={0x00};
	int i=10;
	while(i--)
	{
		ClearCommError(m_hDev,&error,&m_ComState);
		ReadFile(m_hDev,buffer,m_ComState.cbInQue,&len,NULL);
		m_sResult = (CString) buffer;
		if(m_sResult.IsEmpty() == 0){
			break;
		}else{
			Sleep(50);
		}
	}
	return m_sResult;
}

//=====================================================================================//
CString COM_RS232::COM_Query(CString strCmd)
{
	if(COM_Write(strCmd) == true)  
	{
		Sleep(500);
		return COM_Read();
	}
	else 
		return _T(""); 
}
//=====================================================================================//
CString COM_RS232::COM_QueryEx(CString strCmd)
{
	COM_Close();
	if(COM_OpenDev(m_ComPortName))
	{
		if(COM_Write(strCmd) == true)  
		{
			Sleep(500);
			return COM_Read();
		}
		else 
			return _T(""); 
	}
	else
	{
		COM_Close();
		return _T("");
	}

}
//======================================================================================//
bool COM_RS232::COM_Close(void)
{
 if(m_hDev != INVALID_HANDLE_VALUE)
    {
      CloseHandle(m_hDev);
      m_hDev = INVALID_HANDLE_VALUE;
      return true;
    }else{ 
	 //AfxMessageBox("x6");
    return false;
 }
}