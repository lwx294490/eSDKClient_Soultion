#ifndef _GET_VERSION_H_
#define _GET_VERSION_H_

#include <string>

#define VERSION_URI			"esdk_platform_om/upgrade/version"

typedef struct  
{
	std::string ServiceId;
	std::string ServiceVersion;
	std::string IsForceUpgrade;
	std::string ServiceDownLoadUrl;	
} PRODUCT_VERSION_S;

extern void GetVersion(const std::string& PduId, const std::string &ServerUrl, std::string &ServerVer, std::string &DownloadUrl, std::string &ForceUpdate);


#endif 

