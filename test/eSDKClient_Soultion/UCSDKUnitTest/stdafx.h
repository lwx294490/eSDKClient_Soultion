// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���Ǿ���ʹ�õ��������ĵ�
// �ض�����Ŀ�İ����ļ�
//

#pragma once

#include "targetver.h"

//#include <Windows.h>
#include <stdio.h>
//#include <tchar.h>

#include <string>

#ifndef CALLBACK
#define CALLBACK __stdcall
#endif

//#include "ctk/ctk.h"
#include "DataType.h"
#include "UCSDKAbsProxy.h"
#include "UCContactMgrAbsProxy.h"
#include "UCSignalRecvAbsProxy.h"
#include "UCGroupAbsProxy.h"
#include "UCIMAbsProxy.h"
#include "UCVoIPAbsProxy.h"
#pragma comment(lib, "UCSDK.lib")

#ifdef _DEBUG
#pragma comment(lib, "ctkd.lib")
#else
#pragma comment(lib, "ctk.lib")
#endif



using namespace eSDK::UC;



// TODO: �ڴ˴����ó�����Ҫ������ͷ�ļ�
