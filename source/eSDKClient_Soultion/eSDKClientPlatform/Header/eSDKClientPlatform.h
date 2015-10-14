#ifndef _ESDK_CLIENT_PLATFORM_H_
#define _ESDK_CLIENT_PLATFORM_H_

#include <string>

#ifdef ESDKCLIENTPLATFORM_EXPORTS
#define ESDKCLIENT_PLATFORM_API __declspec(dllexport)
#else
#define ESDKCLIENT_PLATFORM_API __declspec(dllimport)
#endif

#ifndef ESDKCLIENT_PLATFORM_DEPEND
#define ESDKCLIENT_PLATFORM_DEPEND
#endif

typedef enum
{
	ESDKCLIENT_PLATFORM_SUCCESS = 0,
	ESDKCLIENT_PLATFORM_FAIL,
	ESDKCLIENT_PLATFORM_INTERNAL_ERROR
} ESDKCLINET_PLATFORM_ERR_CODE_E;

#ifndef CALLBACK
#define CALLBACK				__stdcall
#endif

typedef enum
{
	ESDKCLIENTPLATFORM_UPDATE_ASK = 0,			//升级询问
	ESDKCLIENTPLATFORM_UPDATE_START,			//升级开始
	ESDKCLIENTPLATFORM_UPDATE_FINISHED			//升级完成
} ESDK_MESSAGE_CODE_E;

typedef bool (CALLBACK *eSDKMessageCallBack)(int iMsgID, std::string strDescription);

//客户端平台对外开放的接口类
class ESDKCLIENT_PLATFORM_API eSDKClientPlatform
{
protected:
	eSDKClientPlatform();
	virtual ~eSDKClientPlatform();
public:
	//获取客户端平台单实例对象
	static eSDKClientPlatform* getInstance(void);
	//销毁客户端平台单实例对象
	static void ReleaseInstance(void);

public:
	//客户端平台初始化
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
	//设置升级服务器
	virtual int setUpdateServer(const std::string &UpdateServer) = 0;
	//设置升级消息回调函数
	virtual bool SetMessageCallBack(eSDKMessageCallBack fpMsgCB) = 0;
};

#endif
