
#ifdef WIN32
#include <Windows.h>
#endif

#include "eSDKSSOAdapter.h"
//#include "eSDKLog.h"
#include "eSDKTool.h"
#include "eSDKHost.h"

int g_nLoginRet = ESDKSSO_ADAPTER_LOGIN_SUCCESS;
//保存token
void setToken(std::string strToken)
{
	eSDKSSOAdapter::getSharedInstance().setToken(strToken);
	return;
}
//保存用户名密码
void setUserInfo(std::string strPDUName, USER_INFO_S *pstUserInfo)
{	
	eSDKSSOAdapter::getSharedInstance().setUserInfo(strPDUName, pstUserInfo);
	return;
}

eSDKSSOAdapter& eSDKSSOAdapter::getSharedInstance(std::string ESDKServerString)
{
	std::wstring wszStr;
	wszStr = eSDKTool::StringToWString(ESDKServerString);		
	uri ESDKServerUri(wszStr);
	//配置为本地不进行校验的模式
	http_client_config config;
	config.set_validate_certificates(false);
	//建立http_client连接
	static eSDKSSOAdapter eSDKSSOClient(ESDKServerUri, config);
	
	return eSDKSSOClient;
}

eSDKSSOAdapter::eSDKSSOAdapter(uri &ESDKServerUri, http_client_config& client_config)
	:m_client(ESDKServerUri, client_config)
{
	
}

eSDKSSOAdapter::~eSDKSSOAdapter()
{

}

//用户名在eSDK SSO Server进行验证和登录 
int eSDKSSOAdapter::SSOLogin(const std::string &name, const std::string &password)
{
	//DEBUG_LOG() << "--- ENTRY";
	//INFO_PARAM1(name);
	std::wstring wstrName = eSDKTool::StringToWString(name);
	std::wstring wstrPassWord = eSDKTool::StringToWString(password);
	
	uri_builder loginUri(U(LOGIN_URI));

	http_request request(methods::POST);
	request.set_request_uri(loginUri.to_string());
	//构造http_request消息头
	request.headers().add(header_names::content_type, L"application/json;charset=UTF-8");
	request.headers().add(header_names::cache_control, L"no-cache");
	request.headers().add(header_names::connection, L"Keep_Alive");
	request.headers().add(header_names::pragma, L"no-cache");
	//构造http_request消息体
	json::value obj;
	
	std::string HostIP = eSDKHost::getHostIP();
	//DEBUG_LOG() << "Host IP = " << HostIP;
	std::wstring wstrHostIp = eSDKTool::StringToWString(HostIP);
	obj[U("clientIPAddresss")] = json::value::string(wstrHostIp);
	obj[U("authType")] = json::value::string(U("AccountAndPwd "));
	obj[U("account")] = json::value::string (wstrName);
	obj[U("pwd")] = json::value::string (wstrPassWord);
	request.set_body(obj);

	::g_nLoginRet = ESDKSSO_ADAPTER_LOGIN_FAIL;

	//发送http_request并等待响应
	task_status status = m_client.request(request).then([](http_response response) -> pplx::task<json::value>
	{
		//DEBUG_LOG() << "SSO server response status code is " << response.status_code();
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
			if (json::value() == jsObj)
			{
				return;
			}

			auto ResCode = jsObj[U("resCode")];					
			if (ResCode != json::value::string(U("0")))
			{	
				//ERROR_LOG() << "SSO login server response error, rescode = " << ::WStringToString(ResCode.as_string());
				return;
			}
			::g_nLoginRet = ESDKSSO_ADAPTER_LOGIN_SUCCESS;
			//DEBUG_LOG() << "SSO login server response ok";
			//解析json数据
			auto TokenValue = jsObj[U("credential")];
			std::string strToken = eSDKTool::WStringToString(TokenValue.as_string());
			//保存token
			::setToken(strToken);
		}
		catch (const http_exception& e)
		{
			// Print error.
			//ERROR_LOG()<<e.what();			
		}

	})
	.wait();
	//任务状态异常或登录不成功，则报错
	if ((completed != status) || (ESDKSSO_ADAPTER_LOGIN_SUCCESS != ::g_nLoginRet))
	{
		//ERROR_LOG() << "--- LEAVE";
		return ESDKSSO_ADAPTER_FAIL;
	}
	
	//DEBUG_LOG() << "--- LEAVE";
	return ESDKSSO_ADAPTER_SUCCESS;
}

//token验证，获取用户名密码
int eSDKSSOAdapter::SSOAuthenticate(const std::string &token, const std::string &strPDUName, std::string &strName, std::string &strPassword)
{
	//DEBUG_LOG() << "--- ENTRY";
	//INFO_PARAM2(token, strPDUName);
	std::map<std::string,USER_INFO_S>::iterator iter = m_vecPDUInfo.find(strPDUName);
	if (iter != m_vecPDUInfo.end())
	{
		strName = iter->second.name;
		strPassword = iter->second.password;
		//DEBUG_LOG() << "--- LEAVE";
		return ESDKSSO_ADAPTER_SUCCESS;
	}

	uri_builder authenticateUri(U(AUTHENTICATE_URI));
	
	//构造http_request请求消息
	http_request request(methods::POST);
	request.set_request_uri(authenticateUri.to_string());
	request.headers().add(header_names::content_type, L"application/json;charset=UTF-8");
	request.headers().add(header_names::cache_control, L"no-cache");
	request.headers().add(header_names::connection, L"Keep_Alive");
	request.headers().add(header_names::pragma, L"no-cache");
	
	std::wstring wstrToken = eSDKTool::StringToWString(token);
	json::value obj;
	obj[U("credential")] = json::value::string(wstrToken);
	request.set_body(obj);
	
	//发送http_request并等待响应
	task_status status = m_client.request(request).then([](http_response response) -> pplx::task<json::value>
	{
		//DEBUG_LOG() << "SSO server response status code is " << response.status_code();
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
			if (json::value() == jsObj)
			{
				return;
			}

			auto ResCode = jsObj[U("resCode")];					
			if (ResCode != json::value::string(U("0")))
			{	
				//ERROR_LOG() << "SSO authenticate server response error, rescode = " << ::WStringToString(ResCode.as_string());
				return;
			}
			//DEBUG_LOG() << "SSO authenticate server response ok";
			//解析json数组数据
			auto jsPDUInfo = jsObj[U("userinfo")];
			if (jsPDUInfo.is_array())
			{
				int iNumber = jsPDUInfo.size();
				for (int i = 0; i < iNumber; i++)
				{					
					auto jsPDUName = jsPDUInfo[i][U("product")];
					std::string strTmpPDU = eSDKTool::WStringToString(jsPDUName.as_string());
					
					USER_INFO_S stUserInfo;
					auto jsUserName = jsPDUInfo[i][U("name")];
					stUserInfo.name = eSDKTool::WStringToString(jsUserName.as_string());

					auto jsPassword = jsPDUInfo[i][U("password")];
					stUserInfo.password = eSDKTool::WStringToString(jsPassword.as_string());
					//保存用户名密码
					::setUserInfo(strTmpPDU, &stUserInfo);
				}
			}						
		}
		catch (const http_exception& e)
		{
			// Print error.
			//ERROR_LOG()<<e.what();			
		}
	})
	.wait();

	//任务状态异常或没有对应产品的用户信息，则报错
	iter = m_vecPDUInfo.find(strPDUName);
	if ((completed != status) || (iter == m_vecPDUInfo.end()))
	{
		//ERROR_LOG() << "--- LEAVE";
		return ESDKSSO_ADAPTER_FAIL;
	}	

	strName = iter->second.name;
	strPassword = iter->second.password;
	//DEBUG_LOG() << "--- LEAVE";
	return ESDKSSO_ADAPTER_SUCCESS;
}
//获取token
std::string eSDKSSOAdapter::getToken(void)
{
	return m_token.getToken();
}
//保存token
void eSDKSSOAdapter::setToken(std::string strToken)
{
	m_token.setToken(strToken);
}
//保存用户名密码
void eSDKSSOAdapter::setUserInfo(std::string strPDUName, USER_INFO_S *pstUserInfo)
{
	if (NULL == pstUserInfo)
	{
		return;
	}

	m_vecPDUInfo.insert(std::pair<std::string, USER_INFO_S>(strPDUName, (*pstUserInfo)));	
}
//清除用户名密码
void eSDKSSOAdapter::clearUserInfo(void)
{
	m_vecPDUInfo.clear();
}

bool eSDKSSOAdapter::CheckUriValid(const std::wstring& wszUri)
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