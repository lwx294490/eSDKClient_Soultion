// dllmain.cpp : DllMain ��ʵ�֡�

#include "stdafx.h"
#include "resource.h"
#include "COM_eSDKSSO_i.h"
#include "dllmain.h"

CCOM_eSDKSSOModule _AtlModule;

// DLL ��ڵ�
extern "C" BOOL WINAPI DllMain(HINSTANCE , DWORD dwReason, LPVOID lpReserved)
{
	return _AtlModule.DllMain(dwReason, lpReserved); 
}
