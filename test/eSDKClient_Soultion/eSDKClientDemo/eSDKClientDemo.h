
// eSDKClientDemo.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CeSDKClientDemoApp:
// �йش����ʵ�֣������ eSDKClientDemo.cpp
//

class CeSDKClientDemoApp : public CWinAppEx
{
public:
	CeSDKClientDemoApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CeSDKClientDemoApp theApp;