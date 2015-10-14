#ifndef _UPDATE_SERVER_CONFIG_H_
#define _UPDATE_SERVER_CONFIG_H_

#include <string>
//#include "casablanca120.h"

class UpdateServerConfig
{
public:
	UpdateServerConfig();
	~UpdateServerConfig();

public:
	static void SetServerUrl(const std::string& ServerUrl);
	static std::string GetServerUrl(void);
	//static http_client GetHttpClient(void);

private:
	static std::string m_ServerUrl;
		
};

#endif
