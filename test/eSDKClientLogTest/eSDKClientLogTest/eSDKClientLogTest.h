
// eSDKClientLogTest.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CeSDKClientLogTestApp:
// �йش����ʵ�֣������ eSDKClientLogTest.cpp
//

class CeSDKClientLogTestApp : public CWinApp
{
public:
	CeSDKClientLogTestApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CeSDKClientLogTestApp theApp;