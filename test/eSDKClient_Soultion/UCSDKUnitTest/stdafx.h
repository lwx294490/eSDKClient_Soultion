// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件
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



// TODO: 在此处引用程序需要的其他头文件
