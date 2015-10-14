
#include "eSDKHost.h"
#include "eSDKTool.h"

std::string eSDKHost::m_strHostIp = eSDKTool::getHostIP();

eSDKHost::eSDKHost()
{

}

eSDKHost::~eSDKHost()
{

}

std::string eSDKHost::getHostIP()
{
	return m_strHostIp;
}

void eSDKHost::setHostIP(const std::string &ip)
{
	m_strHostIp = ip;
}
