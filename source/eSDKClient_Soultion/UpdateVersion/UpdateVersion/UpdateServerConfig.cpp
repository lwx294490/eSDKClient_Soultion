
#include "UpdateServerConfig.h"
#include "eSDKTool.h"

std::string UpdateServerConfig::m_ServerUrl = "https://127.0.0.1:8089/";

UpdateServerConfig::UpdateServerConfig()
{

}

UpdateServerConfig::~UpdateServerConfig()
{

}

void UpdateServerConfig::SetServerUrl(const std::string& ServerUrl)
{
	m_ServerUrl = ServerUrl;
}

std::string UpdateServerConfig::GetServerUrl()
{
	return m_ServerUrl;
}
/*
http_client UpdateServerConfig::GetHttpClient()
{
	std::wstring wszStr;
	wszStr = eSDKTool::StringToWString(m_ServerUrl);
	uri ESDKServerUri(wszStr);
	//建立http_client连接
	http_client_config config;
	config.set_validate_certificates(false);
	//http_client client(ESDKServerUri, config);
	http_client client(ESDKServerUri);
	return client;
}*/

