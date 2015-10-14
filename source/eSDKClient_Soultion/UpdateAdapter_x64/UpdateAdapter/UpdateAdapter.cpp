
#include "UpdateAdapter.h"
#include "GetVersion.h"
#include "eSDKTool.h"
#include "casablanca120.h"

#ifdef _DEBUG
#pragma comment(lib, "cpprest110d_1_2.lib")
#else
#pragma comment(lib, "cpprest110_1_2.lib")
#endif

//#pragma comment(linker, "/EXPORT:GetLatestVersion=_GetLatestVersion@48")

bool CheckUriValid(const std::wstring& wszUri)
{
	if (wszUri.empty())
	{
		return false;
	}

	uri tUri(wszUri);

	if (tUri.scheme().empty() || (tUri.scheme() != L"http" && tUri.scheme() != L"https"))
	{
		return false;
	}
	if (tUri.host().empty())
	{
		return false;
	}

	return true;
}

int __UPDATEADAPTER_CALL GetLatestVersion(const char *pchPduID, const char *pchUpdateServer, char *pchServerVer, char *pchDownloadUrl, char *pchForceUpdate, int iBufLen)
{
	if ((NULL == pchPduID) || (NULL == pchUpdateServer) || (NULL == pchServerVer) || (NULL == pchDownloadUrl) || (NULL == pchForceUpdate) || (0 == strlen(pchPduID)) || (0 == strlen(pchUpdateServer)))
	{
		return UPDATEADAPTER_FAIL;
	}

	std::string strPduID = pchPduID;
	std::string strServerUrl = pchUpdateServer;
	std::string strServerVer("");
	std::string strDownloadUrl("");
	std::string strForceUpdate("");

	std::wstring wszStr;
	wszStr = eSDKTool::StringToWString(strServerUrl);
	if (!uri::validate(wszStr))
	{
		return UPDATEADAPTER_FAIL;
	}

	if (!CheckUriValid(wszStr))
	{
		return UPDATEADAPTER_FAIL;
	}

	GetVersion(strPduID, strServerUrl, strServerVer, strDownloadUrl, strForceUpdate);
	if ("" == strServerVer
		|| "" == strDownloadUrl
		|| "" == strForceUpdate)
	{
		return UPDATEADAPTER_FAIL;
	}

	int iLen = strServerVer.size();
	if (iLen >= iBufLen)
	{
		return UPDATEADAPTER_FAIL;
	}

	memcpy(pchServerVer, strServerVer.c_str(), iLen);
	pchServerVer[iLen] = '\0';

	iLen = strDownloadUrl.size();
	if (iLen >= iBufLen)
	{
		return UPDATEADAPTER_FAIL;
	}

	memcpy(pchDownloadUrl, strDownloadUrl.c_str(), iLen);
	pchDownloadUrl[iLen] = '\0';

	iLen = strForceUpdate.size();
	if (iLen >= iBufLen)
	{
		return UPDATEADAPTER_FAIL;
	}

	memcpy(pchForceUpdate, strForceUpdate.c_str(), iLen);
	pchForceUpdate[iLen] = '\0';

	return UPDATEADAPTER_SUCCESS;

}