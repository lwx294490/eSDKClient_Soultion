
#include "TokenManagerExecute.h"

TokenManager::TokenManager()
{

}

TokenManager::~TokenManager()
{

}

TokenManager* TokenManager::getInstance(void)
{
	return dynamic_cast<TokenManager*>(TokenManagerExecute::Instance());
}

void TokenManager::ReleaseInstance(void)
{
	TokenManagerExecute::DestroyInstance();
}

TokenManagerExecute* TokenManagerExecute::m_pTokenMgr = NULL;

TokenManagerExecute::TokenManagerExecute()
	:m_token("")
	,m_mutex(NULL)
{

}

TokenManagerExecute::~TokenManagerExecute()
{
	try
	{
		if (NULL != m_mutex)
		{
			CloseHandle(m_mutex);
			m_mutex = NULL;
		}

		m_token = "";

	}
	catch(...)
	{
		m_mutex = NULL;
	}
}

TokenManagerExecute* TokenManagerExecute::Instance(void)
{
	if (NULL == m_pTokenMgr)
	{
		m_pTokenMgr = new TokenManagerExecute;
	}

	return m_pTokenMgr;

}

void TokenManagerExecute::DestroyInstance()
{
	if (NULL != m_pTokenMgr)
	{
		delete m_pTokenMgr;
		m_pTokenMgr = NULL;
	}
}

bool TokenManagerExecute::init()
{
	if (NULL == m_mutex)
	{
		m_mutex = CreateMutex(NULL, FALSE, NULL);
		if (NULL == m_mutex)
		{
			return false;
		}
	}
		
	return true;
}

bool TokenManagerExecute::uninit()
{
	if (NULL != m_mutex)
	{
		CloseHandle(m_mutex);
		m_mutex = NULL;
	}
	
	return true;
}

bool TokenManagerExecute::WriteToken(const std::string &Credential)
{
	if (Credential.empty())
	{
		return false;
	}

	if (NULL == m_mutex)
	{
		return false;
	}

	DWORD iRet = WaitForSingleObject(m_mutex,INFINITE);
	//lint -e835
	if (WAIT_OBJECT_0 != iRet)
	//lint +e835
	{
		return false;
	}

	m_token = Credential;

	if (!ReleaseMutex(m_mutex))
	{
		return false;
	}
	
	return true;
}

bool TokenManagerExecute::ClearToken()
{
	if (NULL == m_mutex)
	{
		return false;
	}

	DWORD iRet = WaitForSingleObject(m_mutex,INFINITE);
	//lint -e835
	if (WAIT_OBJECT_0 != iRet)
	//lint +e835
	{
		return false;
	}

	m_token = "";

	if (!ReleaseMutex(m_mutex))
	{
		return false;
	}

	return true;
}

bool TokenManagerExecute::GetToken(std::string &Token)
{
	if (NULL == m_mutex)
	{
		return false;
	}

	DWORD iRet = WaitForSingleObject(m_mutex,INFINITE);
	//lint -e835
	if (WAIT_OBJECT_0 != iRet)
	//lint +e835
	{
		return false;
	}

	if (m_token.empty())
	{
		(void)ReleaseMutex(m_mutex);
		Token = "";
		return false;
	}

	Token = m_token;

	if (!ReleaseMutex(m_mutex))
	{
		return false;
	}

	return true;
}
