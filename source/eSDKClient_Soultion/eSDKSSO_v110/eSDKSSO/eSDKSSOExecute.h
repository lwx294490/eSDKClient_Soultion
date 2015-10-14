#ifndef _ESDK_SSO_EXECUTE_H_
#define _ESDK_SSO_EXECUTE_H_

#ifdef WIN32
#include <Windows.h>
#endif

#include <string>
#include <vector>
#include <map>
#include "eSDKSSO.h"
#include "DynamicClass.h"

#pragma warning( disable: 4251 )

class ProductSDK;

class eSDKSSOExecute : public eSDKSSO
{
public:
	//生成客户端平台的单实例
	static eSDKSSOExecute* CreateInstance();
	//销毁客户端平台的单实例
	static void DestroyInstance(void);

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

	virtual unsigned long getServiceHandleByName(const std::string& strServiceName);

private:
	eSDKSSOExecute();
	~eSDKSSOExecute();
	void loadPDUSDK(void);
	int setWorkDirctoryByClassName(const std::string &className);

private:
	std::map<std::string, HINSTANCE> m_vecDllHandle; //存储dll文件句柄
	std::vector<std::string> m_vecClassName; //存储反射加载的业务类名字
	
	typedef std::map<std::string, ProductSDK*> ClassInstanceMap;
	ClassInstanceMap m_vecClassInstance;  //业务名和实例化的对象指针的映射关系表

	typedef std::map<std::string, ESDKSSO_PDU_LOGIN_TYPE_E> LoginTypeMap;
	LoginTypeMap m_vecPDULoginType; //业务名和业务登录方式的映射关系表

	std::map<std::string, std::string> m_ServiceWorkDirectMap; //产品SDK运行目录的映射关系表
	std::string m_CurrentDirect; //存储ISV APP的运行目录

	bool bInitFlag;
private:
	static eSDKSSOExecute* m_eSDKSSO; //单实例对象指针

private:
	DECLARE_RUNTIME(eSDKSSOExecute)

};

#endif
