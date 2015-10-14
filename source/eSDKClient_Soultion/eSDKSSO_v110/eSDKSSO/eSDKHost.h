#ifndef _ESDK_HOST_H_
#define _ESDK_HOST_H_

#include <string>
//主机配置类
class eSDKHost
{
public:
	eSDKHost();
	~eSDKHost();
	//获取主机IP
	static std::string getHostIP();
	//设置主机IP
	static void setHostIP(const std::string &ip);

private:
	static std::string m_strHostIp;
};

#endif
