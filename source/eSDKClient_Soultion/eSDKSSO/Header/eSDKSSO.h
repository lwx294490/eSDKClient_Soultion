#ifndef _ESDK_SSO_H_
#define _ESDK_SSO_H_

#include <string>

#ifdef ESDKSSO_EXPORTS
#define ESDKSSO_API __declspec(dllexport)
#else
#define ESDKSSO_API __declspec(dllimport)
#endif

typedef enum
{
	ESDKSSO_SUCCESS = 0,
	ESDKSSO_FAIL,
	ESDKSSO_INTERNAL_ERROR
} ESDKSSO_ERR_CODE_E;

typedef enum
{
	ESDKSSO_LOGIN_SSO = 0,
	ESDKSSO_LOGIN_SERVICE
} ESDKSSO_LOGIN_TYPE_E;

typedef enum
{
	ESDKSSO_SERVICE_PASSWORD_LOGIN = 0,
	ESDKSSO_SERVICE_TOKEN_LOGIN
} ESDKSSO_PDU_LOGIN_TYPE_E;

//单点登录组件对外开放的接口类
class ESDKSSO_API eSDKSSO
{
public:
	//获取单点登录组件单实例对象
	static eSDKSSO* getInstance(void);
	//销毁单点登录组件单实例对象
	static void ReleaseInstance(void);

public:
	//单点登录组件初始化
	virtual int init(void) = 0;
	//使用token进行登录
	virtual int login(const std::string &token) = 0;
	//使用用户名密码进行登录
	virtual int login(const std::string &name, const std::string &password, int type) = 0;
	//登出
	virtual int logout(void) = 0;
	//设置eSDK SSO Sever URL
	virtual int setConfig(const std::string &param) = 0;
	//去初始化
	virtual int uninit(void) = 0;
	//设置主机IP
	virtual int setHostIP(const std::string &ip) = 0;
	//根据业务名获取加载的业务句柄
	virtual unsigned long getServiceHandleByName(const std::string& strServiceName) = 0;

protected:
	eSDKSSO();
	virtual ~eSDKSSO();
};

#endif
