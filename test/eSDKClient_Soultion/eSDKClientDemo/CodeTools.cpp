#include "stdafx.h"
#include "CodeTools.h"


wchar_t* ANSIToUnicode(const char* str)
{
	unsigned int textlen = 0;
	wchar_t * result = NULL;
	textlen = static_cast<UINT32>(MultiByteToWideChar( CP_ACP, 0, str,-1, NULL,0 ));
	try
	{
		result = (wchar_t *)malloc((textlen+1)*sizeof(wchar_t));
		if (NULL == result)
		{
			//BP_RUN_LOG_ERR(IVS_ALLOC_MEMORY_ERROR, "memory is not enough", "NA");
			return NULL;
		}
	}
	catch (...)
	{
		//BP_RUN_LOG_ERR(IVS_ALLOC_MEMORY_ERROR, "memory is not enough", "NA");
		//result = NULL;
		return NULL;
	}

	memset(result,0,(textlen+1)*sizeof(wchar_t));
	MultiByteToWideChar(CP_ACP, 0,str,-1,(LPWSTR)result,textlen );//lint !e713
	return result;
}

char* UnicodeToUTF8( const wchar_t* str )
{
	char* result = NULL;
	unsigned int textlen = 0;
	textlen = static_cast<UINT32>(WideCharToMultiByte( CP_UTF8, 0, str, -1, NULL, 0, NULL, NULL ));
	try
	{
		result =(char *)malloc((textlen+1)*sizeof(char));
		if (NULL == result)
		{
			//BP_RUN_LOG_ERR(IVS_ALLOC_MEMORY_ERROR, "memory is not enough", "NA");
			return NULL;
		}
	}
	catch (...)
	{
		//BP_RUN_LOG_ERR(IVS_ALLOC_MEMORY_ERROR, "memory is not enough", "NA");
		//result = NULL;
		return NULL;
	}

	memset(result, 0, sizeof(char) * ( textlen + 1 ) );
	WideCharToMultiByte( CP_UTF8, 0, str, -1, result, textlen, NULL, NULL );//lint !e713
	return result;
}

char* UnicodeToANSI( const wchar_t* str )
{
	char* result = NULL;
	unsigned int textlen = 0;
	textlen = static_cast<UINT32>(WideCharToMultiByte( CP_ACP, 0, str, -1, NULL, 0, NULL, NULL ));
	try
	{
		result =(char *)malloc((textlen+1)*sizeof(char));
		if (NULL == result)
		{
			//BP_RUN_LOG_ERR(IVS_ALLOC_MEMORY_ERROR, "memory is not enough", "NA");
			return NULL;
		}
	}
	catch (...)
	{
		//BP_RUN_LOG_ERR(IVS_ALLOC_MEMORY_ERROR, "memory is not enough", "NA");
		//result = NULL;
		return NULL;
	}

	memset( result, 0, sizeof(char) * ( textlen + 1 ) );
	WideCharToMultiByte( CP_ACP, 0, str, -1, result, textlen, NULL, NULL );//lint !e713
	return result;
}

wchar_t* UTF8ToUnicode( const char* str )
{
	unsigned int textlen = 0;
	wchar_t * result = NULL;
	textlen = static_cast<UINT32>(MultiByteToWideChar( CP_UTF8, 0, str,-1, NULL,0 ));
	try
	{
		result = (wchar_t *)malloc((textlen+1)*sizeof(wchar_t));
		if (NULL == result)
		{
			//BP_RUN_LOG_ERR(IVS_ALLOC_MEMORY_ERROR, "memory is not enough", "NA");
			return NULL;
		}
	}
	catch (...)
	{
		//BP_RUN_LOG_ERR(IVS_ALLOC_MEMORY_ERROR, "memory is not enough", "NA");
		//result = NULL;
		return NULL;
	}

	memset(result,0,(textlen+1)*sizeof(wchar_t));
	MultiByteToWideChar(CP_UTF8, 0,str,-1,(LPWSTR)result,textlen );//lint !e713
	return result;
}

char* UTF8ToANSI(const char* str)
{
	wchar_t* unicode = UTF8ToUnicode(str);
	if (NULL == unicode)
	{
		//BP_RUN_LOG_ERR(IVS_FAIL, "UTF8 To Unicode error", "NA");
		return NULL;
	}
	char* ansi = UnicodeToANSI(unicode);
	free(unicode);
	unicode = NULL;
	return ansi;
}

char* ANSIToUTF8(const char* str)
{
	wchar_t* unicode = ANSIToUnicode(str);
	if (NULL == unicode)
	{
		//BP_RUN_LOG_ERR(IVS_FAIL, "ANSI To Unicode error", "NA");
		return NULL;
	}
	char* utf8 = UnicodeToUTF8(unicode);
	free(unicode);
	unicode = NULL;
	return utf8;
}