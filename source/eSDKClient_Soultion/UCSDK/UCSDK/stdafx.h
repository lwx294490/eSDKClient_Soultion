// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#ifndef _UCSDK_STDAFX_H_
#define _UCSDK_STDAFX_H_


#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files:
//#include <windows.h>



// TODO: reference additional headers your program requires here
#include "ctk/ctk.h"
#include "hwuc/HWUC.h"
#include "history/history.h"
using namespace uc::model; 
using namespace uc::model::conversation;
using namespace uc::model::device;
using namespace uc::model::historydata;
using namespace sigslot;

#endif
