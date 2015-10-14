// authimpl.cpp : ���� DLL Ӧ�ó���ĵ���������
//

#include "stdafx.h"
#include "authimpl.h"

#pragma comment(lib,"comsuppw")


namespace uc {
	namespace model {
		namespace auth {

			const char* AUTH_IMPL_DLL			= "auth.dll";
			const char* SERVER_INI_FILE			= "server.ini";
			const char* NODE_STRING				= "ServerConfig";
			const char* IP_STRING				= "SSOServerIP";
			const char* PORT_STRING				= "SSOServerPort";
			const char* SERVER1IP_STRING		= "Server1IP";
			const char* SERVER1PORT_STRING		= "Server1Port";
			const char* SERVER1IPBAK_STRING		= "Server1IPBak";
			const char* SERVER1PORTBAK_STRING	= "Server1PortBak";
			const char* SERVER2IP_STRING		= "Server2IP";
			const char* SERVER2PORT_STRING		= "Server2Port";
			const char* SERVER2IPBAK_STRING		= "Server2IPBak";
			const char* SERVER2PORTBAK_STRING	= "Server2PortBak";
			const char* SERVER_STRING			= "Server";

			AuthManagerImpl* AuthManagerImpl::m_pInstance = NULL;
			
			AuthManager* AuthManager::Instance()
			{
				if (NULL == AuthManagerImpl::m_pInstance)
				{
					AuthManagerImpl::m_pInstance = new AuthManagerImpl;
				}

				if (NULL != AuthManagerImpl::m_pInstance)
				{
					bool bRet = AuthManagerImpl::m_pInstance->init();
					if (!bRet)
					{
						try
						{
							delete AuthManagerImpl::m_pInstance;
							AuthManagerImpl::m_pInstance = NULL;
						}
						catch(...){}
					}

					return AuthManagerImpl::m_pInstance;
				}

				return NULL;
			}

			void AuthManager::Destroy()
			{
				if (NULL == AuthManagerImpl::m_pInstance)
				{
					return;
				}

				AuthManagerImpl::m_pInstance->uninit();
				try
				{
					delete AuthManagerImpl::m_pInstance;
					AuthManagerImpl::m_pInstance = NULL;
				}
				catch(...){}
			}

			AuthType AuthManagerImpl::GetTicket(std::string &_ticket)
			{
				if (NULL == m_pIntf)
				{
					return AUTH_TYPE_AA;
				}

				//�����
				_ticket.clear();

				BSTR bsToken = NULL;
				//����COM�ӿڣ���ȡtoken
				HRESULT hr = m_pIntf->GetToken(&bsToken);
				if (S_OK == hr)
				{
					//ת����string����
					if (NULL != bsToken)
					{
						char *pcTicket = _com_util::ConvertBSTRToString(bsToken);
						if (NULL != pcTicket)
						{
							_ticket = pcTicket;
							delete[] pcTicket;
						}
					}					
				}

				if (NULL != bsToken)
				{
					SysFreeString(bsToken);
					bsToken = NULL;
				}

				if(_ticket.empty())
				{
					return AUTH_TYPE_AA;
				}

				return AUTH_TYPE_Ticket;
			}

			bool AuthManagerImpl::GetServer(std::string &_ipAddress, std::string &_port)
			{
				//��ȡserver.ini����·��
				char path[MAX_PATH] = {0};
				GetModuleFileNameA(GetModuleHandleA(AUTH_IMPL_DLL), path, MAX_PATH);

				std::string sPath(path);
				sPath = sPath.substr(0, sPath.rfind("\\")+1);
				sPath.append(SERVER_INI_FILE);

				//�����
				_ipAddress.clear();
				_port.clear();

				const int IP_LENGTH = 16;
				char acIPAddr[IP_LENGTH] = {0};

				const int PORT_LENGTH = 8;
				char acPort[PORT_LENGTH] = {0};				

				//��ȡserver.ini�ļ��е�SSO Server IP�Ͷ˿ں�
				DWORD dwNum = ::GetPrivateProfileStringA(NODE_STRING,IP_STRING,"",acIPAddr,IP_LENGTH,sPath.c_str());
				DWORD dwNum1 = ::GetPrivateProfileStringA(NODE_STRING,PORT_STRING,"",acPort,PORT_LENGTH,sPath.c_str());
				if ((0 == dwNum) || (0 == dwNum1))
				{
					//��ȡeSpace��ǰʹ�õķ�������server1 or server2
					const int SERVER_LENGTH = 16;
					char acServer[SERVER_LENGTH] = {0};
					dwNum = ::GetPrivateProfileStringA(NODE_STRING,SERVER_STRING,"",acServer,SERVER_LENGTH,sPath.c_str());
					if (0 == dwNum)
					{
						return false;
					}

					//�жϵ�ǰʹ�õķ�������server1����server2
					if (0 == _stricmp(acServer, "server1"))
					{
						//��ȡserver1��IP�Ͷ˿ں�
						dwNum = ::GetPrivateProfileStringA(NODE_STRING,SERVER1IP_STRING,"",acIPAddr,IP_LENGTH,sPath.c_str());
						dwNum1 = ::GetPrivateProfileStringA(NODE_STRING,SERVER1PORT_STRING,"",acPort,PORT_LENGTH,sPath.c_str());
						if ((0 == dwNum) || (0 == dwNum1))
						{
							//��ȡserver1���õ�IP�Ͷ˿ں�
							dwNum = ::GetPrivateProfileStringA(NODE_STRING,SERVER1IPBAK_STRING,"",acIPAddr,IP_LENGTH,sPath.c_str());
							dwNum1 = ::GetPrivateProfileStringA(NODE_STRING,SERVER1PORTBAK_STRING,"",acPort,PORT_LENGTH,sPath.c_str());
							if ((0 == dwNum) || (0 == dwNum1))
							{
								return false;
							}
						}
					}
					else if (0 == _stricmp(acServer, "server2"))
					{
						//��ȡserver2��IP�Ͷ˿ں�
						dwNum = ::GetPrivateProfileStringA(NODE_STRING,SERVER2IP_STRING,"",acIPAddr,IP_LENGTH,sPath.c_str());
						dwNum1 = ::GetPrivateProfileStringA(NODE_STRING,SERVER2PORT_STRING,"",acPort,PORT_LENGTH,sPath.c_str());
						if ((0 == dwNum) || (0 == dwNum1))
						{
							//��ȡserver2���õ�IP�Ͷ˿ں�
							dwNum = ::GetPrivateProfileStringA(NODE_STRING,SERVER2IPBAK_STRING,"",acIPAddr,IP_LENGTH,sPath.c_str());
							dwNum1 = ::GetPrivateProfileStringA(NODE_STRING,SERVER2PORTBAK_STRING,"",acPort,PORT_LENGTH,sPath.c_str());
							if ((0 == dwNum) || (0 == dwNum1))
							{
								return false;
							}
						}

					}
					else
					{
						return false;
					}					
				}

				//���IP��ַ�Ͷ˿ڵĺϷ���
				bool bRet = CheckIpAndPort(acIPAddr, acPort);
				if (!bRet)
				{
					return false;
				}

				_ipAddress = acIPAddr;
				_port = acPort;
				return true;
			}

			bool AuthManagerImpl::init()
			{
				//��ʼ��COM�����
				CoInitializeEx(NULL, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);
				HRESULT hr;
				hr = CoCreateInstance(CLSID_ComIdl_eSDKSSO,
					NULL,CLSCTX_LOCAL_SERVER,
					IID_IComIdl_eSDKSSO,
					(void **)& m_pIntf);
				if (S_OK != hr)
				{
					return false;
				}

				return true;
			}

			void AuthManagerImpl::uninit()
			{
				//ȥ��ʼ��COM�����
				if (NULL != m_pIntf)
				{
					m_pIntf->Release();
					m_pIntf = NULL;
				}

				CoUninitialize();
			}

			bool AuthManagerImpl::CheckIpAndPort(const char *ip, const char *port)
			{
				if ((NULL == ip) || (NULL == port))
				{
					return false;
				}

				const int DOT_NUM = 3;
				const int MAX_IP = 255;
				unsigned int auIpTemp[4] = {0};
				int iNum = 0;				
				int iValue = 0;
				bool bFlag = false;
				//���IP��ַ�ĺϷ���
				for (;;)
				{
					iValue = *(ip++);
					if ((iValue >= '0') && (iValue <= '9'))
					{
						bFlag = true;
						auIpTemp[iNum] = auIpTemp[iNum] * 10 + iValue - '0';
						if (auIpTemp[iNum] > MAX_IP)
						{
							return false;
						}
					}
					else if ('.' == iValue)
					{
						if (!bFlag)
						{
							return false;
						}

						if (DOT_NUM == iNum)
						{
							return false;
						}

						iNum++;
						bFlag = false;
					}
					else if (('\0' == iValue) && (DOT_NUM == iNum) && bFlag)
					{
						break;
					}
					else
					{
						return false;
					}					
				}

				const int MIN_PORT = 1;
				const int MAX_PORT = 65535;
				//���˿ڵĺϷ���
				unsigned int uPortTemp = 0;
				for (;;)
				{
					iValue = *(port++);
					if ((iValue >= '0') && (iValue <= '9'))
					{
						uPortTemp = uPortTemp * 10 + iValue - '0';
						if (MAX_PORT < uPortTemp)
						{
							return false;
						}
					}
					else if ('\0' == iValue)
					{
						break;
					}
					else
					{
						return false;
					}
				}

				if (MIN_PORT > uPortTemp)
				{
					return false;
				}

				return true;
			}

		} // namespace auth
	} // namespace model
} // namespace uc
