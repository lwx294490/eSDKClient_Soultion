#ifndef _ESDK_SSO_ADAPTER_H_
#define _ESDK_SSO_ADAPTER_H_

#include <string>
#include "casablanca120.h"
#include "TokenCache.h"
//��ȨURL
#define AUTHENTICATE_URI "esdksso/authenticate" 
//��¼URL
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
//�����¼��
class eSDKSSOAdapter
{
public:
	static eSDKSSOAdapter& getSharedInstance(std::string ESDKServerString = "");
	//ʹ���û��������¼eSDK SSO Server
	int SSOLogin(const std::string &name, const std::string &password);
	//ʹ��tokenί�м�Ȩ����ȡ��Ӧҵ����û�������
	int SSOAuthenticate(const std::string &token, const std::string &strPDUName, std::string &strName, std::string &strPassword);
	//��ȡtoken
	std::string getToken(void);
	//����token
	void setToken(std::string strToken);
	//�����û���Ϣ
	void setUserInfo(std::string strPDUName, USER_INFO_S *pstUserInfo);
	//����û���Ϣ
	void clearUserInfo(void);
private:
	eSDKSSOAdapter(uri &ESDKServerUri, http_client_config& client_config);
	~eSDKSSOAdapter();

public:
	static bool CheckUriValid(const std::wstring& wszUri);

private:
	http_client m_client; //http_client����
	TokenCache m_token;
	std::map<std::string, USER_INFO_S> m_vecPDUInfo; //�û�����ҵ���ӳ���ϵ��
};

#endif
