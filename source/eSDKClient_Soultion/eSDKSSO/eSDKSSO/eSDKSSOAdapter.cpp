
#ifdef WIN32
#include <Windows.h>
#endif

#include "eSDKSSOAdapter.h"
//#include "eSDKLog.h"
#include "eSDKTool.h"
#include "eSDKHost.h"

int g_nLoginRet = ESDKSSO_ADAPTER_LOGIN_SUCCESS;
//����token
void setToken(std::string strToken)
{
	eSDKSSOAdapter::getSharedInstance().setToken(strToken);
	return;
}
//�����û�������
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
	//����Ϊ���ز�����У���ģʽ
	http_client_config config;
	config.set_validate_certificates(false);
	//����http_client����
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

//�û�����eSDK SSO Server������֤�͵�¼ 
int eSDKSSOAdapter::SSOLogin(const std::string &name, const std::string &password)
{
	//DEBUG_LOG() << "--- ENTRY";
	//INFO_PARAM1(name);
	std::wstring wstrName = eSDKTool::StringToWString(name);
	std::wstring wstrPassWord = eSDKTool::StringToWString(password);
	
	uri_builder loginUri(U(LOGIN_URI));

	http_request request(methods::POST);
	request.set_request_uri(loginUri.to_string());
	//����http_request��Ϣͷ
	request.headers().add(header_names::content_type, L"application/json;charset=UTF-8");
	request.headers().add(header_names::cache_control, L"no-cache");
	request.headers().add(header_names::connection, L"Keep_Alive");
	request.headers().add(header_names::pragma, L"no-cache");
	//����http_request��Ϣ��
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

	//����http_request���ȴ���Ӧ
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
			//����json����
			auto TokenValue = jsObj[U("credential")];
			std::string strToken = eSDKTool::WStringToString(TokenValue.as_string());
			//����token
			::setToken(strToken);
		}
		catch (const http_exception& e)
		{
			// Print error.
			//ERROR_LOG()<<e.what();			
		}

	})
	.wait();
	//����״̬�쳣���¼���ɹ����򱨴�
	if ((completed != status) || (ESDKSSO_ADAPTER_LOGIN_SUCCESS != ::g_nLoginRet))
	{
		//ERROR_LOG() << "--- LEAVE";
		return ESDKSSO_ADAPTER_FAIL;
	}
	
	//DEBUG_LOG() << "--- LEAVE";
	return ESDKSSO_ADAPTER_SUCCESS;
}

//token��֤����ȡ�û�������
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
	
	//����http_request������Ϣ
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
	
	//����http_request���ȴ���Ӧ
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
			//����json��������
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
					//�����û�������
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

	//����״̬�쳣��û�ж�Ӧ��Ʒ���û���Ϣ���򱨴�
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
//��ȡtoken
std::string eSDKSSOAdapter::getToken(void)
{
	return m_token.getToken();
}
//����token
void eSDKSSOAdapter::setToken(std::string strToken)
{
	m_token.setToken(strToken);
}
//�����û�������
void eSDKSSOAdapter::setUserInfo(std::string strPDUName, USER_INFO_S *pstUserInfo)
{
	if (NULL == pstUserInfo)
	{
		return;
	}

	m_vecPDUInfo.insert(std::pair<std::string, USER_INFO_S>(strPDUName, (*pstUserInfo)));	
}
//����û�������
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