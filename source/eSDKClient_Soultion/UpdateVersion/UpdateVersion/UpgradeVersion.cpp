#include <string>
#include <vector>
#include "UpgradeVersion.h"
#include "UpdateVersion.h"
#include "eSDKLog.h"

#pragma comment(linker, "/EXPORT:Upgrade_Init=_Upgrade_Init@8")
#pragma comment(linker, "/EXPORT:Upgrade_Uninit=_Upgrade_Uninit@0")
#pragma comment(linker, "/EXPORT:Upgrade_SetServerUrl=_Upgrade_SetServerUrl@4")
#pragma comment(linker, "/EXPORT:Upgrade_GetServerUrl=_Upgrade_GetServerUrl@8")
#pragma comment(linker, "/EXPORT:Upgrade_Start=_Upgrade_Start@0")
#pragma comment(linker, "/EXPORT:Upgrade_SetMessageCallBack=_Upgrade_SetMessageCallBack@4")

bool __UPGRADE_VERSION_CALL Upgrade_Init(const UPGRADE_VERSION_INFO_S* pstVersionArray, const int iArrayNum)
{
	if ((NULL == pstVersionArray) || (0 >= iArrayNum))
	{
		return false;
	}
	//获取升级模块实例
	UpdateVersion *pUpdateVersion = UpdateVersion::GetUpdateVersion();
	if (NULL == pUpdateVersion)
	{
		return false;
	}
	//将模块名和版本号分别存放在vector中
	int i = 0;
	std::vector<std::string> vecNameList;
	std::vector<std::string> vecVersionList;	
	for (; i < iArrayNum; i++)
	{
		vecNameList.push_back(pstVersionArray[i].acName);
		vecVersionList.push_back(pstVersionArray[i].acVersion);
	}
	//升级初始化
	bool bRet = pUpdateVersion->Init(vecNameList, vecVersionList);

	return bRet;
}

bool __UPGRADE_VERSION_CALL Upgrade_Uninit(void)
{
	DEBUG_LOG() << "--- ENTER";
	//获取升级模块实例
	UpdateVersion *pUpdateVersion = UpdateVersion::GetUpdateVersion();
	if (NULL == pUpdateVersion)
	{
		ERROR_LOG() << "pUpdateVersion is NULL pointer.";
		return false;
	}
	//升级去初始化
	bool bRet = pUpdateVersion->UnInit();
	if (!bRet)
	{
		ERROR_LOG() << "UpdateVersion uninit fail.";
		return bRet;
	}

	//销毁升级模块实例
	UpdateVersion::ReleaseUpdateVersion();
	return bRet;
}

bool __UPGRADE_VERSION_CALL Upgrade_SetServerUrl(const char* pchServerUrl)
{
	DEBUG_LOG() << "--- ENTER";
	INFO_PARAM1(pchServerUrl);

	if (NULL == pchServerUrl)
	{
		ERROR_LOG() << "pchServerUrl is NULL pointer.";
		return false;
	}
	//获取升级模块实例
	UpdateVersion *pUpdateVersion = UpdateVersion::GetUpdateVersion();
	if (NULL == pUpdateVersion)
	{
		ERROR_LOG() << "pUpdateVersion is NULL pointer.";
		return false;
	}
	//设置server url
	std::string strUrl = pchServerUrl;
	bool bRet = pUpdateVersion->SetServerUrl(strUrl);
	if (!bRet)
	{
		ERROR_LOG() << "Set server url fail.";
	}
	else
	{
		DEBUG_LOG() << "Set server url success.";
	}
	
	DEBUG_LOG() << "--- LEAVE";
	return bRet;
}

bool __UPGRADE_VERSION_CALL Upgrade_GetServerUrl(char* pchServerUrl, int iBufferLen)
{
	DEBUG_LOG() << "--- ENTER";
	INFO_PARAM2(pchServerUrl, iBufferLen);

	if (NULL == pchServerUrl)
	{
		ERROR_LOG() << "pchServerUrl is NULL pointer.";
		return false;
	}
	//判断buffer长度是否合法
	if (0 >= iBufferLen)
	{
		ERROR_LOG() << "Buffer length is less than 0.";
		return false;
	}

	//获取升级模块实例
	UpdateVersion *pUpdateVersion = UpdateVersion::GetUpdateVersion();
	if (NULL == pUpdateVersion)
	{
		ERROR_LOG() << "pUpdateVersion is NULL pointer.";
		return false;
	}
	//获取server url
	std::string strUrl;
	strUrl = pUpdateVersion->GetServerUrl();
	DEBUG_LOG() << "Get server url success.";
	//判断获取到的server url的长度是否超出实际buffer的长度，若超出，则出错
	unsigned int iLen = strUrl.size();
	if (iLen >= (unsigned int)iBufferLen)
	{
		ERROR_LOG() << "URL length is more than buffer length.";
		return false;
	}
	
	memcpy(pchServerUrl, strUrl.c_str(), iLen);
	pchServerUrl[iLen] = '\0';

	DEBUG_LOG() << "--- LEAVE";
	return true;
}

bool __UPGRADE_VERSION_CALL Upgrade_Start(void)
{
	DEBUG_LOG() << "--- ENTER";	
	//获取升级模块实例
	UpdateVersion *pUpdateVersion = UpdateVersion::GetUpdateVersion();
	if (NULL == pUpdateVersion)
	{
		ERROR_LOG() << "pUpdateVersion is NULL pointer.";
		return false;
	}
	//启动升级
	bool bRet = pUpdateVersion->Start();
	if (!bRet)
	{
		ERROR_LOG() << "Start upgrade fail.";
	}
	else
	{
		DEBUG_LOG() << "Start upgrade success.";
	}

	DEBUG_LOG() << "--- LEAVE";
	return bRet;
}

//存储用户传入的回调函数指针
UpgradeMessageCallBack g_fpMsgCallback = NULL;

//消息回调函数桩，将此桩函数设置到升级组件中，在调用用户设定的回调函数之前，先将参数转换成C的数据类型，然后再调用
bool __UPGRADE_VERSION_CALL MessageCallBackStub(int iMsgID, std::string strDescription)
{
	if (NULL == g_fpMsgCallback)
	{
		return false;
	}
	//string类型转换成char类型
	unsigned int iLen = strDescription.size();
	char *pchDescription = (char *)malloc(sizeof(char) * (iLen + 1));
	if (NULL == pchDescription)
	{
		return false;
	}

	memcpy(pchDescription, strDescription.c_str(), iLen);
	pchDescription[iLen] = '\0';
	//调用用户传入的回调函数
	bool bRet = (*g_fpMsgCallback)(iMsgID, pchDescription);
	
	free(pchDescription);
	pchDescription = NULL;

	return bRet;//lint !e438
}

bool __UPGRADE_VERSION_CALL Upgrade_SetMessageCallBack(UpgradeMessageCallBack fpMsgCB)
{
	DEBUG_LOG() << "--- ENTER";	
	
	if (NULL == fpMsgCB)
	{
		ERROR_LOG() << "fpMsgCB is NULL pointer.";
		return false;
	}
	//存储用户传入的回调函数指针
	g_fpMsgCallback = fpMsgCB;

	//获取升级模块实例
	UpdateVersion *pUpdateVersion = UpdateVersion::GetUpdateVersion();
	if (NULL == pUpdateVersion)
	{
		ERROR_LOG() << "pUpdateVersion is NULL pointer.";
		return false;
	}
	//设置消息回调桩函数为回调函数
	bool bRet = pUpdateVersion->SetMessageCallBack(MessageCallBackStub);
	if (!bRet)
	{
		ERROR_LOG() << "Set MessageCallBack fail.";
	}
	else
	{
		DEBUG_LOG() << "Set MessageCallBack success.";
	}

	DEBUG_LOG() << "--- LEAVE";
	return bRet;
}

