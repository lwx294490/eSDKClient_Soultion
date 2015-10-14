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

//字符码转换
wchar_t* ANSIToUnicode(const char* str);	//ANSI转换为Unicode
wchar_t* UTF8ToUnicode(const char* str);	//UTF_8转换为Unicode
char* UnicodeToUTF8(const wchar_t* str);	//Unicode转换为UTF_8
char* UnicodeToANSI(const wchar_t* str);	//Unicode转换为ANSI
char* UTF8ToANSI(const char* str);			//UTF_8转换为ANSI
char* ANSIToUTF8(const char* str);			//ANSI转换为UTF_8


#endif