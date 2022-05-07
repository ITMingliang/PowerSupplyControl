#include "pch.h"
#include "DataHandle.h"

CDataHandle::CDataHandle(void)
{
	
}

CDataHandle::~CDataHandle(void)
{
}

CString CDataHandle::ReadDatatoString(CString App,CString Key)
{
	CString data;
	::GetPrivateProfileString(App,Key,"NULL",data.GetBuffer(1024),1024,".\\SimCardTest.ini");
	data.ReleaseBuffer();
	return data;
}

CString CDataHandle::WriteDatatoString(CString App,CString Key,CString data)
{
	WritePrivateProfileString(App,Key,data,".\\SimCardTest.ini");
	return data;
}

BOOL CDataHandle::ShellEXE(CString Cmd,int nShowCmd)
{
	::ShellExecute(NULL,"open","cmd.exe",Cmd,NULL,nShowCmd);//ShellEXE("/c devcon.exe disable USB\\Class_03",SW_HIDE);
	return TRUE;
}

CString CDataHandle::GetTime()
{
	CString mTime,strDate,strTime;
	/*CTime time=GetCurrentTime();
	mTime= time.Format("%Y-%m-%d");
	return mTime;*/
	SYSTEMTIME time;
	::GetLocalTime(&time);
	strDate.Format("%4d-%02d-%02d",time.wYear,time.wMonth,time.wDay); 
	strTime.Format("%02d:%02d:%02d",time.wHour,time.wMinute,time.wSecond);
	mTime=strDate+" "+strTime+"\t";
	return mTime;
}

CString CDataHandle::GetDate()
{
	CString mTime,strDate;
	/*CTime time=GetCurrentTime();
	mTime= time.Format("%Y-%m-%d");
	return mTime;*/
	SYSTEMTIME time;
	::GetLocalTime(&time);
	strDate.Format("%4d-%02d-%02d",time.wYear,time.wMonth,time.wDay); 
	mTime=strDate;
	return mTime;
}

bool CDataHandle::SaveLog(CString path,CString log,bool AppendWrite)
{
	CFile file;
	if(!AppendWrite)
	{
		file.Open(path,CFile::modeCreate|CFile::modeReadWrite,NULL);
	}
	else
	{
		if(_access((char *)path.GetBuffer(0),0)==-1)
		{
			file.Open(path,CFile::modeCreate|CFile::modeReadWrite,NULL);
		}
		else
		{
			file.Open(path,CFile::modeReadWrite,NULL);
		}
		file.SeekToEnd();
	}
	log+="\r\n\r\n";
	file.Write(log.GetBuffer(log.GetLength()),log.GetLength());
	log.ReleaseBuffer();
	file.Close();
	return true;
}

bool CDataHandle::CreateLog()
{
	CFile file;
	CString filename;
	::GetModuleFileName(AfxGetInstanceHandle(),filename.GetBuffer(1024),1024);
	filename.ReleaseBuffer();
	filename=filename.Left(filename.GetLength()-4);
	if(_access(filename+"log.txt",0)==-1)
	{
		file.Open(filename+"log.txt",CFile::modeCreate|CFile::modeReadWrite,NULL);
		file.Close();
	}
	else
	{
		DeleteFileA(filename+"log.txt");
		Sleep(20);
		file.Open(filename+"log.txt",CFile::modeCreate|CFile::modeReadWrite,NULL);
		file.Close();
	}
	return true;
}

bool CDataHandle::SaveResult(CString mResult)
{
	CFile file;
	CString filename,mApp;
	mApp="[Result]\r\n";
	::GetModuleFileName(AfxGetInstanceHandle(),filename.GetBuffer(1024),1024);
	filename.ReleaseBuffer();
	filename=filename.Left(filename.GetLength()-4);
	mResult=mApp+mResult+"\r\n";
	file.Open(filename+"log.txt",CFile::modeReadWrite,NULL);
	file.SeekToEnd();
	file.Write(mResult.GetBuffer(mResult.GetLength()),mResult.GetLength());
	mResult.ReleaseBuffer();
	file.Close();
	return true;
}

bool CDataHandle::SaveITPMResult(CString mResult)
{
	CFile file;
	CString filename;
	::GetModuleFileName(AfxGetInstanceHandle(),filename.GetBuffer(1024),1024);
	filename.ReleaseBuffer();
	filename=filename.Left(filename.GetLength()-4);
	mResult=mResult+"\r\n";
	file.Open(filename+".txt",CFile::modeReadWrite|CFile::modeCreate,NULL);
	file.SeekToEnd();
	file.Write(mResult.GetBuffer(mResult.GetLength()),mResult.GetLength());
	mResult.ReleaseBuffer();
	file.Close();
	return true;
}

BOOL CDataHandle::SaveParams(CString szName, CString szParams)
{
	CFile file;
	CString filename,mApp,mResult;
	mApp=szName+":";
	::GetModuleFileName(AfxGetInstanceHandle(),filename.GetBuffer(1024),1024);
	filename.ReleaseBuffer();
	filename=filename.Left(filename.GetLength()-4);
	mResult=mApp+szParams+"\r\n";
	file.Open(filename+"log.txt",CFile::modeReadWrite,NULL);
	file.SeekToEnd();
	file.Write(mResult.GetBuffer(mResult.GetLength()),mResult.GetLength());
	mResult.ReleaseBuffer();
	file.Close();
	return 1;
}

CString CDataHandle::InttoStr(int iNum)
{
	CString str;
	str.Format("%d",iNum);
	return str;
}

bool CDataHandle::CheckUSBDeviceInfo(CString mCmd,USBINFO &usbinfo)
{
	HRESULT hres;
	// Initialize COM.
	int cycles=0;
	hres =  CoInitializeEx(0, COINIT_MULTITHREADED); 
	if (FAILED(hres))
	{
		AfxMessageBox("Failed to initialize COM library. ");
		/*cout << "Failed to initialize COM library. " 
			<< "Error code = 0x" 
			<< hex << hres << endl;*/
		return 1;              // Program has failed.
	}

	// Initialize 
	hres =  CoInitializeSecurity(
		NULL,     
		-1,      // COM negotiates service                  
		NULL,    // Authentication services
		NULL,    // Reserved
		RPC_C_AUTHN_LEVEL_DEFAULT,    // authentication
		RPC_C_IMP_LEVEL_IMPERSONATE,  // Impersonation
		NULL,             // Authentication info 
		EOAC_NONE,        // Additional capabilities
		NULL              // Reserved
		);


	if (FAILED(hres))
	{
		AfxMessageBox("Failed to initialize security. " );
		/*cout << "Failed to initialize security. " 
			<< "Error code = 0x" 
			<< hex << hres << endl;*/
		CoUninitialize();
		return 1;          // Program has failed.
	}

	// Obtain the initial locator to Windows Management
	// on a particular host computer.
	IWbemLocator *pLoc = 0;

	hres = CoCreateInstance(
		CLSID_WbemLocator,             
		0, 
		CLSCTX_INPROC_SERVER, 
		IID_IWbemLocator, (LPVOID *) &pLoc);

	if (FAILED(hres))
	{
		AfxMessageBox("Failed to create IWbemLocator object. ");
		/*cout << "Failed to create IWbemLocator object. "
			<< "Error code = 0x"
			<< hex << hres << endl;*/
		CoUninitialize();
		return 1;       // Program has failed.
	}

	IWbemServices *pSvc = 0;

	// Connect to the root\cimv2 namespace with the
	// current user and obtain pointer pSvc
	// to make IWbemServices calls.

	hres = pLoc->ConnectServer(

		_bstr_t("ROOT\\CIMV2"), // WMI namespace
		NULL,                    // User name
		NULL,                    // User password
		0,                       // Locale
		NULL,                    // Security flags                 
		0,                       // Authority       
		0,                       // Context object
		&pSvc                    // IWbemServices proxy
		);                              

	if (FAILED(hres))
	{
		AfxMessageBox("Could not connect. Error code = 0x");
		/*cout << "Could not connect. Error code = 0x" 
			<< hex << hres << endl;*/
		pLoc->Release();     
		CoUninitialize();
		return 1;                // Program has failed.
	}

	// cout << "Connected to ROOT\\CIMV2 WMI namespace" << endl;

	// Set the IWbemServices proxy so that impersonation
	// of the user (client) occurs.
	hres = CoSetProxyBlanket(

		pSvc,                         // the proxy to set
		RPC_C_AUTHN_WINNT,            // authentication service
		RPC_C_AUTHZ_NONE,             // authorization service
		NULL,                         // Server principal name
		RPC_C_AUTHN_LEVEL_CALL,       // authentication level
		RPC_C_IMP_LEVEL_IMPERSONATE,  // impersonation level
		NULL,                         // client identity 
		EOAC_NONE                     // proxy capabilities     
		);

	if (FAILED(hres))
	{
		AfxMessageBox("Could not set proxy blanket. Error code = 0x");
		/*cout << "Could not set proxy blanket. Error code = 0x" 
			<< hex << hres << endl;*/
		pSvc->Release();
		pLoc->Release();     
		CoUninitialize();
		return 1;               // Program has failed.
	}


	// Use the IWbemServices pointer to make requests of WMI. 
	// Make requests here:

	// For example, query for all the running processes
	IEnumWbemClassObject* pEnumerator = NULL;
	hres = pSvc->ExecQuery(
		bstr_t("WQL"), 
		bstr_t("SELECT * FROM "+mCmd),
		WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY, 
		NULL,
		&pEnumerator);

	if (FAILED(hres))
	{
		AfxMessageBox("Query for processes failed. ");
		/*cout << "Query for processes failed. "
			<< "Error code = 0x" 
			<< hex << hres << endl;*/
		pSvc->Release();
		pLoc->Release();     
		CoUninitialize();
		return 1;               // Program has failed.
	}
	else
	{ 
		IWbemClassObject *pclsObj;
		ULONG uReturn = 0;


		/*cout<< "========test start=========== "<<endl;*/
		
		while (pEnumerator)
		{
			CString temp;
			hres = pEnumerator->Next(WBEM_INFINITE, 1, 
				&pclsObj, &uReturn);

			if(0 == uReturn)
			{
				break;
			}

			VARIANT vtProp;
			__int64 num=0;
			hres = pclsObj->Get(L"Caption", 0, &vtProp, 0, 0);
			temp=vtProp.bstrVal;
			usbinfo.mCaption[cycles]=temp;

			hres = pclsObj->Get(L"Name", 0, &vtProp, 0, 0);
			temp=vtProp.bstrVal;
			usbinfo.mName[cycles]=temp;

			hres = pclsObj->Get(L"DeviceID", 0, &vtProp, 0, 0);
			temp=vtProp.bstrVal;
			usbinfo.mDeviceID[cycles]=temp;
			VariantClear(&vtProp);
			
			cycles++;
			//AfxMessageBox(str,0,0);
		}
	}

	// Cleanup
	// ========
	pSvc->Release();
	pLoc->Release();     
	CoUninitialize();
	return true;
}

CString CDataHandle::ReadDatatoStringEx(CString sApp,CString sKey,CString DefaultValue)
{
	CFileFind filefind;
	CFile file;
	char cPlan[100000]={0} ;
	memset(cPlan,0,100000);
	CString str,buff,buffer,m_Value;
	int length=0;
	if(filefind.FindFile(".\\..\\INI\\AudioSpec.ini"))
	{
		int iCnt=20;
		while(!file.Open(".\\..\\INI\\AudioSpec.ini",CFile::modeRead| CFile::typeBinary))
		{
			 Sleep(100);	
			 if(file.Open(".\\..\\INI\\AudioSpec.ini",CFile::modeRead| CFile::typeBinary))
				break;
		     iCnt--;
		     if(iCnt <= 0)
		     {
			    file.Close();
				file.Open(".\\..\\INI\\AudioSpec.ini",CFile::modeRead| CFile::typeBinary);
		     } 
	    }
		length=(int) file.GetLength();
		file.Read(cPlan,length);
		file.Close();
		str=cPlan;
		//pInfo1(str);
	}else{
		::AfxMessageBox("No Test Spec!");
		PostQuitMessage(0);
	
	}

	if(str.Find(sApp)>=0 && str.Find(sKey)>=0)
	{
		buffer=str.Mid(str.Find("["+sApp+"]"));
		buffer=buffer.Mid(buffer.Find("]")+1);
		if(buffer.Find(sKey)<0)
		{
			::AfxMessageBox("No ["+sApp+"]"+"  "+sKey+". Pls Add!");
		}
		buffer=buffer.Mid(buffer.Find(sKey+"="));
		buffer=buffer.Mid(buffer.Find("=")+1);
		if(buffer.Find("\r\n")>=0)
		{
			m_Value=buffer.Mid(0,buffer.Find("\r\n"));
		}
		else
		{
			m_Value=buffer;//last line
		}
     //   m_Value=buffer.Left(buffer.Find(";"));
	
	}else{
	     m_Value=DefaultValue;
		::AfxMessageBox("No ["+sApp+"]"+"  "+sKey+". Pls Add!");
	}

	//::AfxMessageBox("["+sApp+"]"+sKey+"="+m_Value);
	return m_Value;

}

void CDataHandle::WriteDatatoStringEx(CString App,CString Key,CString data)
{
	CFileFind filefind;
	CFile file;
	char cPlan[100000]={0} ;
	memset(cPlan,0,100000);
	CString str,buff,m_strNewPlan,buffer,buffer_P1,buffer_P2,buffer_P,buffer_N,str1;
	int length=0;
	if(filefind.FindFile(".\\..\\INI\\AudioSpec.ini"))
	{
		file.Open(".\\..\\INI\\AudioSpec.ini",CFile::modeRead| CFile::typeBinary);
		length=(int) file.GetLength();
		file.Read(cPlan,length);
		file.Close();
		str=cPlan;
		//pInfo1(str);
	}else{
		::AfxMessageBox("No Test Spec!");
		PostQuitMessage(0);
	
	}

	if(str.Find(App)>=0 && str.Find(Key)>=0)
	{
		buffer=str.Mid(str.Find("["+App+"]"));
		buffer=buffer.Mid(buffer.Find("]")+1);
		buffer=buffer.Mid(buffer.Find(Key+"="));
		buffer=buffer.Mid(buffer.Find("=")+1);
        buffer_N=buffer.Mid(buffer.Find("\r\n")+1);
		buffer=str.Mid(str.Find("["+App+"]"));
		buffer_P1=str.Left(str.Find("["+App+"]"));
        buffer_P2=buffer.Left(buffer.Find(Key));
		buffer_P=buffer_P1+buffer_P2;
		m_strNewPlan=buffer_P+Key+"="+data+"\r\n"+buffer_N;

	}else{
		 ::AfxMessageBox("No ["+App+"]"+"  "+Key+". Pls Add!");
	}

	
	CString pathName = ".\\..\\INI\\AudioSpec.ini";
	file.Open(pathName,CFile::modeCreate | CFile::modeReadWrite| CFile::typeBinary);
	//pInfo(m_strNewPlan);
	file.Write(m_strNewPlan,m_strNewPlan.GetLength());
	file.Close();

}

