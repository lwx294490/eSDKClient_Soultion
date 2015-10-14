/*****************************************************************
 filename    :    CodeTools.h
 author      :    yWX200189
 created     :    2014/05/14
 description :    �ַ���ת������������ANSI��Unicode��UTF_8���ַ���֮����໥ת��
 copyright   :    Copyright (c) 2012-2016 Huawei Tech.Co.,Ltd
 history     :    2014/05/14 ��ʼ�汾
*****************************************************************/

#ifndef __CODE_TOOLS_HEADER__
#define __CODE_TOOLS_HEADER__

typedef unsigned int UINT32;

//�ַ���ת��
wchar_t* ANSIToUnicode(const char* str);	//ANSIת��ΪUnicode
wchar_t* UTF8ToUnicode(const char* str);	//UTF_8ת��ΪUnicode
char* UnicodeToUTF8(const wchar_t* str);	//Unicodeת��ΪUTF_8
char* UnicodeToANSI(const wchar_t* str);	//Unicodeת��ΪANSI
char* UTF8ToANSI(const char* str);			//UTF_8ת��ΪANSI
char* ANSIToUTF8(const char* str);			//ANSIת��ΪUTF_8


#endif