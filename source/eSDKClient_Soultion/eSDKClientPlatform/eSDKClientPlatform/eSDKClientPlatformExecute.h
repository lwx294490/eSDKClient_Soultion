#ifndef _ESDK_CLIENT_PLATFORM_EXECUTE_H_
#define _ESDK_CLIENT_PLATFORM_EXECUTE_H_

#ifdef WIN32
#include <Windows.h>
#endif

#include <string>
#include <vector>
#include <map>
#include "eSDKClientPlatform.h"
#include "UpdateVersion.h"
#include "ProductSDK.h"

#define ESDKSSO_INI_FILE "eSDKSSO_config.ini"
#define ESDKSSO_DLL_FILE "eSDKSSO.dll"

class eSDKSSO;

class eSDKClientPlatformExecute : public eSDKClientPlatform
{
public:
	//生成客户端平台的单实例
	static eSDKClientPlatformExecute* Instance(void);
	//销毁客户端平台的单实例
	static void Destroy(void);

public:
	//客户端平台初始化
	virtual int init(void);
	//使用token进行登录
	virtual int login(const std::string &token);
	//使用用户名密码进行登录
	virtual int login(const std::string &name, const std::string &password, int type);
	//登出
	virtual int logout(void);
	//设置eSDK SSO Sever URL
	virtual int setConfig(const std::string &param);
	//去初始化
	virtual int uninit(void);
	//设置主机IP地址
	virtual int setHostIP(const std::string &ip);
	//设置升级服务器
	virtual int setUpdateServer(const std::string &UpdateServer);
	//设置升级消息回调函数
	virtual bool SetMessageCallBack(eSDKMessageCallBack fpMsgCB);

public:
	ProductSDK* getServiceByName(const std::string& strServiceName);
	HINSTANCE getServiceHandleByName(const std::string& strServiceName);
	
private:
	eSDKClientPlatformExecute();
	~eSDKClientPlatformExecute();
	int UpdateService(void);

private:
	eSDKSSO* m_eSDKSSO; //客户端单实例
	UpdateVersion *m_UpdateVersion; //升级单实例

	std::vector<std::string> m_vecClassName;
	std::vector<std::string> m_vecVersion;
	std::vector<std::string> m_vecServiceName;

	typedef std::map<std::string, ProductSDK*> ClassInstanceMap;
	ClassInstanceMap m_vecClassInstance;  //业务名和实例化的对象指针的映射关系表

	HINSTANCE hDll;
	eSDKMessageCallBack m_pMsgCallBack;
private:
	static eSDKClientPlatformExecute* m_eSDKClientPlatform; //单实例对象指针
};

#endif
