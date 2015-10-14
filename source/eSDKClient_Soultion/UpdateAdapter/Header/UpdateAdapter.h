#ifndef _UPDATE_ADAPTER_H_
#define _UPDATE_ADAPTER_H_

#ifdef  UPDATEADAPTER_EXPORTS
#define UPDATEADAPTER_API __declspec(dllexport)
#else
#define UPDATEADAPTER_API __declspec(dllimport)
#endif

#ifdef WIN32
#define __UPDATEADAPTER_CALL __stdcall
#else
#define __UPDATEADAPTER_CALL
#endif

typedef enum
{
	UPDATEADAPTER_SUCCESS = 0,
	UPDATEADAPTER_FAIL
} UPDATEADAPTER_ERR_CODE_E;

#ifdef __cplusplus
extern "C"
{
#endif
		
	UPDATEADAPTER_API int __UPDATEADAPTER_CALL GetLatestVersion(const char *pchPduID, const char *pchUpdateServer, char *pchServerVer, char *pchDownloadUrl, char *pchForceUpdate, int iBufLen);

#ifdef __cplusplus
}
#endif 

#endif 

