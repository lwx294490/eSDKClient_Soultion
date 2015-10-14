
#include <Windows.h>
#include <string>
#include "casablanca120.h"
#include "GetVersion.h"
#include "eSDKTool.h"


PRODUCT_VERSION_S g_PduInfo; //存储版本服务器传回来的产品版本信息

#define DLL_FILE_NAME U("UpdateAdapter.dll")
#define SECTION_URI U("UpdateURL")
#define KEYNAME_URI U("UrlPostfix")
#define CONF_FILE_NAME U("UpdateVersion_config.ini")

std::wstring GetVerionUriPostfix()
{
	WCHAR path[MAX_PATH] = {0};	
	GetModuleFileNameW(GetModuleHandleW(DLL_FILE_NAME), path, MAX_PATH);
	std::wstring wsPath(path);
	wsPath = wsPath.substr(0, wsPath.rfind(U("\\"))+1);
	wsPath.append(CONF_FILE_NAME);

	const int LENGTH_URI = 256;
	WCHAR value[LENGTH_URI] = {0};

	int iRet = GetPrivateProfileStringW(SECTION_URI, KEYNAME_URI, U(""), value, LENGTH_URI, wsPath.c_str());
	if (0 >= iRet)
	{
		std::wstring uriPostfix = U(VERSION_URI);
		return uriPostfix;
	}

	std::wstring uriPostfix(value);
	return uriPostfix;
}

void GetVersion(const std::string& PduId, const std::string &ServerUrl, std::string &ServerVer, std::string &DownloadUrl, std::string &ForceUpdate)
{
	::g_PduInfo.ServiceId = "";
	::g_PduInfo.ServiceVersion = "";
	::g_PduInfo.ServiceDownLoadUrl = "";
	::g_PduInfo.IsForceUpgrade = "";

	if ((0 == PduId.size()) || (0 == ServerUrl.size()))
	{
		ServerVer = ::g_PduInfo.ServiceVersion;
		DownloadUrl = ::g_PduInfo.ServiceDownLoadUrl;
		ForceUpdate = ::g_PduInfo.IsForceUpgrade;
		return;
	}

	std::wstring wstrPduId = eSDKTool::StringToWString(PduId);
	
	//uri_builder VersionUri(U(VERSION_URI));
	uri_builder VersionUri(GetVerionUriPostfix().c_str());
	VersionUri.append_query(U("productID"), wstrPduId);
	
	http_request request(methods::GET);
	request.set_request_uri(VersionUri.to_string());
	//构造http_request消息头
	request.headers().add(header_names::content_type, L"application/json;charset=UTF-8");
	request.headers().add(header_names::cache_control, L"no-cache");
	request.headers().add(header_names::connection, L"Keep_Alive");
	request.headers().add(header_names::pragma, L"no-cache");
	
	std::wstring wszStr;
	wszStr = eSDKTool::StringToWString(ServerUrl);
	uri ESDKServerUri(wszStr);
	//建立http_client连接
	http_client_config config;
	config.set_validate_certificates(false);
	http_client client(ESDKServerUri, config);
	//http_client client(ESDKServerUri);
	
	//发送http_request并等待响应
	task_status status = client.request(request).then([](http_response response) -> pplx::task<json::value>
	{
		//DEBUG_LOG() << "Version server response status code is " << response.status_code();
		if(response.status_code() == status_codes::OK)
		{
			return response.extract_json();
		}

		// Handle error cases, for now return empty json value...
		return pplx::task_from_result(json::value());
	})
	.then([](pplx::task<json::value> previousTask)
	{
		try
		{
			const json::value& jsObj = previousTask.get();
			if(json::value() == jsObj)
			{
				return;
			}
			auto ResCode = jsObj[U("resCode")];	
			if (ResCode != json::value::string(U("0")))
			{	
				//ERROR_LOG() << "Update version server response error, rescode = " << WStringToString(ResCode.as_string());
				return;
			}
			//DEBUG_LOG() << "Update version server response ok";
			//解析json数组数据
			auto jsPDUInfo = jsObj[U("productInfo")];
			if (jsPDUInfo.is_array())
			{
				int iNumber = jsPDUInfo.size();
				for (int i = 0; i < iNumber; i++)
				{
					auto jsPduId = jsPDUInfo[i][U("ID")];
					if (!jsPduId.is_null())
					{
						g_PduInfo.ServiceId = eSDKTool::WStringToString(jsPduId.as_string());	
					}					

					auto jsVersion = jsPDUInfo[i][U("version")];
					if (!jsVersion.is_null())
					{
						g_PduInfo.ServiceVersion = eSDKTool::WStringToString(jsVersion.as_string());
					}					

					auto jsForceUpdate = jsPDUInfo[i][U("isForceUpgrade")];
					if (!jsForceUpdate.is_null())
					{
						g_PduInfo.IsForceUpgrade = eSDKTool::WStringToString(jsForceUpdate.as_string());
					}				

					auto jsDownloadUrl = jsPDUInfo[i][U("downloadUrl")];
					if (!jsDownloadUrl.is_null())
					{
						g_PduInfo.ServiceDownLoadUrl = eSDKTool::WStringToString(jsDownloadUrl.as_string());
					}
				}
			}						
		}
		catch (const http_exception& e)
		{
			//ERROR_LOG()<<e.what();			
		}
	})
	.wait();	
	
	ServerVer = ::g_PduInfo.ServiceVersion;
	DownloadUrl = ::g_PduInfo.ServiceDownLoadUrl;
	ForceUpdate = ::g_PduInfo.IsForceUpgrade;
	return;
}