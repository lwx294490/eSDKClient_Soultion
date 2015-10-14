#include <string>

//#include "ClientVersionManage.h"
//#include "casablanca120.h"
//#include "Common.h"
#include "eSDKLog.h"
#include "eSDKTool.h"
#include "UpdateServerConfig.h"
#include "ClientVersionManage.h"
#include "UpdateAdapter.h"

#pragma comment(lib, "UpdateAdapter.lib")
//PRODUCT_VERSION_S g_PduInfo; //存储版本服务器传回来的产品版本信息

ClientVersionManage::ClientVersionManage()
{

}

ClientVersionManage::~ClientVersionManage()
{

}

bool ClientVersionManage::CompareVersion(const std::string& PduId, const std::string& LocalVer, std::string& DownloadUrl, std::string& ForceUpdate)const
{
	if ((0 == PduId.size()) || (0 == LocalVer.size()))
	{
		ERROR_LOG() << "Invalid parameter, string is empty!!!";
		return false;
	}
	
	std::string ServerUrl = UpdateServerConfig::GetServerUrl();

	const int LENGTH = 128;
	char acServer[LENGTH] = {0};
	char acDownloadUrl[LENGTH] = {0};
	char acForceUpdate[LENGTH] = {0};
	
	int iRet = GetLatestVersion(PduId.c_str(), ServerUrl.c_str(), acServer, acDownloadUrl, acForceUpdate, LENGTH);	
	if (UPDATEADAPTER_SUCCESS != iRet)
	{
		ERROR_LOG() << "Not have the update job for product Id = " << PduId;
		return false;
	}

	std::string ServerVer = acServer;
	DownloadUrl = acDownloadUrl;
	ForceUpdate = acForceUpdate;

	bool bRet = CheckVersion(LocalVer, ServerVer);
	
	return bRet;
}


bool ClientVersionManage::CheckVersion(const std::string &LocalVer, const std::string &ServerVer)const
{
	std::vector<std::string> vecLocalVersion;
	std::vector<std::string> vecServerVersion;

	char separator = '.';
	eSDKTool::SplitString(LocalVer,separator, vecLocalVersion);
	eSDKTool::SplitString(ServerVer, separator, vecServerVersion);

	std::vector<std::string>::size_type LocalVerSize = vecLocalVersion.size();
	std::vector<std::string>::size_type ServerVerSize = vecServerVersion.size();
	std::vector<std::string>::size_type size = 0;
	std::string zero = "0";

	int sizeGap = (int)ServerVerSize - (int)LocalVerSize;
	if (sizeGap < 0)
	{
		size = LocalVerSize;
		int len = 0 - sizeGap;
		for (int index = 0; index < len; index++)
		{
			vecServerVersion.push_back(zero);
		}
	}
	else if (sizeGap > 0)
	{
		size = ServerVerSize;
		for (int index = 0; index < sizeGap; index++)
		{
			vecLocalVersion.push_back(zero);
		}
	}
	else
	{
		size = ServerVerSize;
	}

	std::vector<std::string>::size_type num = 0;
	while (num < size)
	{
		int nLocal = 0;
		int nServer = 0;
		try
		{
			std::stringstream sstreamLocal(vecLocalVersion[num]);
			sstreamLocal >> nLocal;
			std::stringstream sstreamServer(vecServerVersion[num]);
			sstreamServer >> nServer;
		}
		catch (...)
		{
			ERROR_LOG() << "Check version fail";
			return false;
		}
		
		if (nLocal > nServer)
		{
			return false;
		}
		else if (nLocal < nServer)
		{
			return true;
		}
		else
		{
			num++;
		}
	}

	return false;
}






