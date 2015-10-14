#ifndef _CLIENT_VERSION_MANAGE_H_
#define _CLIENT_VERSION_MANAGE_H_
/*
typedef struct  
{
	std::string ServiceId;
	std::string ServiceVersion;
	std::string IsForceUpgrade;
	std::string ServiceDownLoadUrl;	
} PRODUCT_VERSION_S;
*/
class ClientVersionManage
{
public:
	ClientVersionManage();
	~ClientVersionManage();

public:
	bool CompareVersion(const std::string& PduId, const std::string& LocalVer, std::string& DownloadUrl, std::string& ForceUpdate)const;	//ForceUpdate = "true" or "false"

private:
	bool CheckVersion(const std::string &LocalVer, const std::string &ServerVer)const;
};

#endif

