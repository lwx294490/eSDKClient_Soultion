#ifndef _ESDK_HOST_H_
#define _ESDK_HOST_H_

#include <string>
//����������
class eSDKHost
{
public:
	eSDKHost();
	~eSDKHost();
	//��ȡ����IP
	static std::string getHostIP();
	//��������IP
	static void setHostIP(const std::string &ip);

private:
	static std::string m_strHostIp;
};

#endif
