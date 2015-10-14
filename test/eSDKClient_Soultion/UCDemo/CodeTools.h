/*****************************************************************
 filename    :    CodeTools.h
 author      :    yWX200189
 created     :    2014/05/14
 description :    字符码转换方法，包含ANSI、Unicode、UTF_8等字符码之间的相互转换
 copyright   :    Copyright (c) 2012-2016 Huawei Tech.Co.,Ltd
 history     :    2014/05/14 初始版本
*****************************************************************/

#ifndef __CODE_TOOLS_HEADER__
#define __CODE_TOOLS_HEADER__

typedef unsigned int UINT32;

wchar_t* ANSIToUnicode(const char* str);
wchar_t* UTF8ToUnicode(const char* str);
char* UnicodeToUTF8(const wchar_t* str);
char* UnicodeToANSI(const wchar_t* str);
char* UTF8ToANSI(const char* str);
char* ANSIToUTF8(const char* str);


#endif