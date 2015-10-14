#ifndef _SSO_ADAPTER_H_
#define _SSO_ADAPTER_H_

#ifdef  SSOADAPTER_EXPORTS
#define SSOADAPTER_API __declspec(dllexport)
#else
#define SSOADAPTER_API __declspec(dllimport)
#endif

#ifdef WIN32
#define __SSOADAPTER_CALL __stdcall
#else
#define __SSOADAPTER_CALL
#endif

typedef enum
{
	SSOADAPTER_SUCCESS = 0,
	SSOADAPTER_FAIL
} SSOADAPTER_ERR_CODE_E;

#ifdef __cplusplus
extern "C"
{
#endif
		
	SSOADAPTER_API int __SSOADAPTER_CALL InstanceSSO(const char *pSSOUri);
	SSOADAPTER_API int __SSOADAPTER_CALL SSOLogin(const char *pchName, const char *pchPassword);
	SSOADAPTER_API int __SSOADAPTER_CALL SSOAuthenticate(const char *token, const char *pchPDUName,char *pchName, char *pchPassword, int iBufLen);
	SSOADAPTER_API int __SSOADAPTER_CALL getToken(char *pTokenBuf, int iBufLen);
	SSOADAPTER_API int __SSOADAPTER_CALL setToken(const char *pToken);
	SSOADAPTER_API void __SSOADAPTER_CALL clearUserInfo(void);
	SSOADAPTER_API int __SSOADAPTER_CALL setHostIP(const char *pchIp);

#ifdef __cplusplus
}
#endif 

#endif 

