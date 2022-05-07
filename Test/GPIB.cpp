// GPIB.cpp: 实现文件
//

#include "pch.h"
#include "Test.h"
#include "GPIB.h"

#define READ_BUFFER_SIZE 4096
// GPIB

IMPLEMENT_DYNAMIC(GPIB, CWnd)

GPIB::GPIB()
{

}

GPIB::~GPIB()
{
}


BEGIN_MESSAGE_MAP(GPIB, CWnd)
END_MESSAGE_MAP()

bool GPIB::Initial(CString strCom)
{
    status = viOpenDefaultRM(&defaultRM);
    if (status < VI_SUCCESS)
    {
        printf("Could not open a session to the VISA Resource Manager!\n");
        //exit(EXIT_FAILURE);
        return false;
    }
    status = viOpen(defaultRM, strCom, VI_NULL, VI_NULL, &inst);
    if (status < VI_SUCCESS)
  {
      printf("Could not open a session to the VISA Resource Manager!\n");
      //exit(EXIT_FAILURE);
      return false;
  }
    return true;
}
bool GPIB::WriteCmd(CString strCmd)
{
    char buff[255] = "";
    int i = 0;
    for (i = 0; i < strCmd.GetLength(); i++)
    {
        buff[i] = strCmd[i];
    }
    buff[i + 1] = '\0';
    ViPUInt32 rcount = 0;
    status = viWrite(inst, (ViBuf)buff, i, rcount);
    if (status < VI_SUCCESS)
    {
        return false;
    }
    return true;
}

CString GPIB::ReadCmd()
{
    ViJobId job;
    static unsigned char data[READ_BUFFER_SIZE]="";
    memset(data, NULL, sizeof data);
    status = viRead(inst, data, READ_BUFFER_SIZE - 1, &job);
    CString str = "";
    for (int i = 0; i < READ_BUFFER_SIZE; i++)
    {
        if (data[i] != '\0')
        {
            char ch = data[i];
            str = str + ch;
        }
    }
    return str;
}

CString GPIB::QueryCmd(CString strCmd)
{
    WriteCmd(strCmd);
    Sleep(300);
    CString str = ReadCmd();
    return str;
}
bool GPIB::UnInitial()
{
    viClose(inst);
    viClear(defaultRM);
    return true;
}
// GPIB 消息处理程序


