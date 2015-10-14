// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件
//

#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>



// TODO: 在此处引用程序需要的其他头文件
#include <Windows.h>

#ifndef CALLBACK
#define CALLBACK __stdcall
#endif

#include <fstream>
#include "cppunit/extensions/TestFactoryRegistry.h"
#include "cppunit/ui/text/TestRunner.h"
#include "cppunit/XmlOutputter.h"
#include "cppunit/extensions/HelperMacros.h"

#include "DataDef.h"
//#include "UCContactMgr.h"
//#include "UCGroup.h"
//#include "UCIM.h"
//#include "UCMeeting.h"
//#include "UCPublic.h"
//#include "UCSignalRecv.h"
//#include "UCSignIn.h"
//#include "UCVoIP.h"