
#include<iostream>
#include<windows.h>
#include <Tlhelp32.h>
#include<winternl.h>
#include<QMessageBox>
BOOL anti1()
{
  return IsDebuggerPresent();
}

BOOL anti2()
{
  BOOL ret;
  CheckRemoteDebuggerPresent(GetCurrentProcess(), &ret);
  return ret;
}

BOOL anti3()
{
  //检查PEB  BeingDebugged标志位
  char result = 0;
  __asm
  {
    // fs:[30h],进程的PEB基地址存放在此位置上
    mov eax, fs: [30h]
      // fs:[30h]偏移2个位置的地方即为BeingDebugged标志位
      mov al, BYTE PTR[eax + 2]
      // 查询后将结果返回
      mov result, al
  }
    return result != 0;
  }

  typedef NTSTATUS(*NtSetInformationThreadPtr)(HANDLE threadHandle,  // 声明NtSetInformationThread函数指针
                                               THREADINFOCLASS threadInformationClass,
                                               PVOID threadInformation,
                                               ULONG threadInformationLength);

  void NtSetInformationThread()   //你可以在当前线程里调用NtSetInformationThread，调用这个函数时，如果在第二个参数里指定0x11这个值（意思是ThreadHideFromDebugger，即取消所有附加的调试器）
  {
    HMODULE hModule = LoadLibrary(TEXT("Ntdll.dll"));
    NtSetInformationThreadPtr NtSetInformationThread = (NtSetInformationThreadPtr)GetProcAddress(hModule, "NtSetInformationThread");
    NtSetInformationThread(GetCurrentThread(), (THREADINFOCLASS)0x11, 0, 0);
  }

  BOOL anti4()
  {
    //查询HeapFlags标志位
    int result = 0;
    __asm
    {
      // 进程的PEB基地址
      mov eax, fs: [30h]
        // 进程的ProcessHeap基地址
        mov eax, [eax + 18h]
        // ForceFlags标志位
        mov eax, [eax + 44h]  //win10
        mov result, eax
    }
      return result != 0;

    }
/*
    BOOL anti5()
    {

      DWORD ExplorerId = 0;
      PROCESSENTRY32 pe32 = { 0 };
      // 获取当前进程ID
      DWORD ProcessId = GetCurrentProcessId();
      // 获取父进程ID
      GetWindowThreadProcessId(FindWindow(L"Progman", NULL), &ExplorerId);
      HANDLE hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
      if (hProcessSnap != INVALID_HANDLE_VALUE)
        {
          pe32.dwSize = sizeof(PROCESSENTRY32);
          Process32First(hProcessSnap, &pe32);
          do
            {	// 判断是否本进程的PID
              if (ProcessId == pe32.th32ProcessID)
                {	// 判断父进程是否是 Explorer.exe
                  if (pe32.th32ParentProcessID != ExplorerId)
                    {	// 若程序已被调试器附加，则返回1
                      return 1;
                    }
                }
            } while (Process32Next(hProcessSnap, &pe32));
        }
      return 0;
    }
*/

    // 进程自主注册的未处理异常处理程序
    LONG WINAPI MyUnhandledExceptionFilter(struct _EXCEPTION_POINTERS* pei)
    {
      SetUnhandledExceptionFilter((LPTOP_LEVEL_EXCEPTION_FILTER)
                                  pei->ContextRecord->Eax);
      // 修改寄存器eip的值
      pei->ContextRecord->Eip += 2;
      // 告诉操作系统，继续执行进程剩余的指令（指令保存在eip里），而不是关闭进程
      return EXCEPTION_CONTINUE_EXECUTION;
    }

    BOOL anti6()
    {
      SetUnhandledExceptionFilter(MyUnhandledExceptionFilter);
      __asm
      {
        // 将eax清零
        xor eax, eax
            // 触发一个除零异常
            div eax
      }
      return false;
    }


    void test1()
    {
      if (anti1() != 0)
        {
          QMessageBox::warning(NULL, "信息", "IsDebuggerPresent检测到调试器", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);

        }
    }

    void test2()
    {
      if (anti2() != 0)
        {
          QMessageBox::warning(NULL, "信息","CheckremoteDebuggerPresent检测到调试器",  QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
        }
    }

    void test3()
    {
      if (anti3() != 0)
        {

          QMessageBox::warning(NULL, "信息","PEB BeingDebugged标志检测到调试器",  QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
        }
    }

    void test4()
    {
      if (anti4() != 0)
        {
          QMessageBox::warning(NULL, "信息","PEB HeapFlags标志检测到调试器",  QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
          QMessageBox::warning(NULL, "信息", "若程序被调试，程序将终止",  QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
          exit(0);

        }
    }
/*
    void test5()
    {
      if (anti5() != 0)
        {
          QMessageBox::warning(NULL, "父进程检测为调试器", "信息", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
        }
    }
*/
    void test6()
    {
      QMessageBox::warning(NULL, "信息", "若程序被调试，程序将终止",  QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);

      NtSetInformationThread();
    }

//    void test7()
//    {
//      QMessageBox::warning(NULL, "信息", "若程序被调试，程序将终止",  QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
//      anti6();
//    }


