#ifndef _ESDK_SSO_ADAPTER_H_
#define _ESDK_SSO_ADAPTER_H_

#include <string>
#include "casablanca120.h"
#include "TokenCache.h"
//鉴权URL
#define AUTHENTICATE_URI "esdksso/authenticate" 
//登录URL
#define LOGIN_URI "esdksso/entrustedAuthProxy.action"

typedef enum
{
	ESDKSSO_ADAPTER_SUCCESS = 0,
	ESDKSSO_ADAPTER_FAIL
} ESDKSSO_ADAPTER_ERR_CODE_E;

typedef enum
{
	ESDKSSO_ADAPTER_LOGIN_SUCCESS = 0,
	ESDKSSO_ADAPTER_LOGIN_FAIL
} ESDKSSO_ADAPTER_LOGIN_ERR_CODE_E;

typedef struct 
{
	std::string name;
	std::string password;
} USER_INFO_S;
//单点登录类
class eSDKSSOAdapter
{
public:
	static eSDKSSOAdapter& getSharedInstance(std::string ESDKServerString = "");
	//使用用户名密码登录eSDK SSO Server
	int SSOLogin(const std::string &name, const std::string &password);
	//使用token委托鉴权，获取相应业务的用户名密码
	int SSOAuthenticate(const std::string &token, const std::string &strPDUName, std::string &strName, std::string &strPassword);
	//获取token
	std::string getToken(void);
	//保存token
	void setToken(std::string strToken);
	//保存用户信息
	void setUserInfo(std::string strPDUName, USER_INFO_S *pstUserInfo);
	//清除用户信息
	void clearUserInfo(void);
private:
	eSDKSSOAdapter(uri &ESDKServerUri, http_client_config& client_config);
	~eSDKSSOAdapter();

public:
	static bool CheckUriValid(const std::wstring& wszUri);

private:
	http_client m_client; //http_client连接
	TokenCache m_token;
	std::map<std::string, USER_INFO_S> m_vecPDUInfo; //用户所属业务的映射关系表
};

#endif
