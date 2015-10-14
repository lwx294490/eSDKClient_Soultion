#ifdef WIN32
#include <Windows.h>
#include <WinSock.h>
#pragma comment(lib,"wsock32.lib")
#endif

#include <string>
#include "eSDKTool.h"

eSDKTool::eSDKTool(void)
{
}

eSDKTool::~eSDKTool(void)
{
}
//��ȡָ�����ļ���path
void eSDKTool::getModulePath(const std::string& strModuleFile, std::string& cstrPath)
{
	TCHAR pBuf[MAX_PATH] = {0};
	std::string strTemp;
	GetModuleFileName(::GetModuleHandle(strModuleFile.c_str()), pBuf, MAX_PATH-sizeof(TCHAR));
	strTemp.append(pBuf);	
	cstrPath = strTemp.substr(0,strTemp.rfind('\\')+1);	
}

//��ȡ����IP
std::string eSDKTool::getHostIP(void)
{
	char hostName[HOST_NAME_MAX_LENGTH] = {0};
	struct hostent *ph = NULL;
	std::string strHostIP = "";
	WSADATA wsadata;
	if (0 != WSAStartup(MAKEWORD(1, 1), &wsadata))
	{
		return strHostIP;
	}
	//��ȡ������
	if (0 != gethostname(hostName, HOST_NAME_MAX_LENGTH))
	{
		return strHostIP;
	}
	//ͨ����������ȡ����IP
	if ((ph = gethostbyname(hostName)) == NULL)//lint !e838
	{
		return strHostIP;
	}
	
	char *pcIP = inet_ntoa(*((struct in_addr *)ph->h_addr));//lint !e826
	strHostIP = pcIP;
	WSACleanup();
	return strHostIP;	
}

std::wstring eSDKTool::StringToWString(std::string str)
{
	std::wstring wszStr; 
	int nLength = MultiByteToWideChar( CP_ACP, 0, str.c_str(), -1, NULL, NULL );
	wszStr.resize((unsigned int)nLength);
	LPWSTR lpwszStr = new wchar_t[(unsigned int)nLength];
	MultiByteToWideChar( CP_ACP, 0, str.c_str(), -1, lpwszStr, nLength );
	wszStr = lpwszStr;
	delete [] lpwszStr;

	return wszStr;
}

std::string eSDKTool::WStringToString(std::wstring wstr)
{
	std::string szStr; 
	int nLength = WideCharToMultiByte( CP_ACP, 0, wstr.c_str(), -1, NULL, 0, NULL, NULL );
	szStr.resize((unsigned int)nLength);
	LPSTR lpszStr = new char[(unsigned int)nLength];
	WideCharToMultiByte( CP_ACP, 0, wstr.c_str(), -1, lpszStr, nLength, NULL, NULL);
	szStr = lpszStr;
	delete [] lpszStr;

	return szStr;
}

void eSDKTool::AddSplitToString(std::string &src, char separator)
{
	unsigned int size = src.size();
	for (unsigned int i = 0; i < size; i++)
	{
		if ((('a'<= src[i]) && ('z' >= src[i])) || (('A'<= src[i]) && ('Z' >= src[i])))
		{
			src[i] = separator;
		}
	}

	return;
}

void eSDKTool::SplitString(const std::string &src, char separator, std::vector<std::string>& vect)
{	
	std::string strTemp = src;

	AddSplitToString(strTemp, separator);
	
	size_t nBegin = 0;
	size_t nEnd = 0;

	while(std::string::npos != nEnd)
	{
		nEnd = strTemp.find_first_of(separator, nBegin);
		if (std::string::npos == nEnd)
		{
			vect.push_back(strTemp.substr(0, strTemp.length()));
		}
		else if (nBegin == nEnd)
		{
			strTemp = strTemp.substr(nBegin + 1, strTemp.length() - 1);
			if ("" == strTemp)
			{
				break;
			}
		}
		else
		{
			vect.push_back(strTemp.substr(nBegin, nEnd));
			strTemp = strTemp.substr(nEnd + 1, (strTemp.length()- nEnd) -1);
		}
	}

	return;
}

void eSDKTool::FindFiles(std::map<std::string, std::string> &sIniFiles,std::vector<std::string> &sDllFiles, const std::string& sPath)
{
	WIN32_FIND_DATAA data = {0};
	std::string sFileRule = sPath + "*.*";
	HANDLE hFile = FindFirstFile(sFileRule.c_str(), &data);
	if(INVALID_HANDLE_VALUE == hFile)
	{
		sIniFiles.clear();
		sDllFiles.clear();
		FindClose(hFile);
		return;
	}
	//��ȡָ��Ŀ¼�µ�*.ini��*.dll�ļ�
	do
	{
		if ((data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) && ('.' != data.cFileName[0]))
		{
			WIN32_FIND_DATAA IniData;
			std::string sSubDirect = sPath + data.cFileName + "\\";
			std::string sIniFileRule = sSubDirect + "*.ini";
			HANDLE hIniFile =  FindFirstFile(sIniFileRule.c_str(), &IniData);
			if (INVALID_HANDLE_VALUE == hIniFile)
			{
				FindClose(hIniFile);
				continue;
			}

			do 
			{
				(void)sIniFiles.insert(std::pair<std::string, std::string>((sSubDirect + IniData.cFileName), sSubDirect));

			} while (FindNextFile(hIniFile, &IniData));

			WIN32_FIND_DATAA DllData;
			std::string sDllFileRule = sSubDirect + "*.dll";
			HANDLE hDllFile = FindFirstFile(sDllFileRule.c_str(), &DllData);
			if (INVALID_HANDLE_VALUE == hDllFile)
			{
				FindClose(hDllFile);
				FindClose(hIniFile);
				continue;
			}

			do 
			{
				sDllFiles.push_back((sSubDirect + DllData.cFileName));
			} while (FindNextFile(hDllFile, &DllData));

			FindClose(hDllFile);
			FindClose(hIniFile);
		}
	}while(FindNextFile(hFile,&data));

	FindClose(hFile);
}

bool eSDKTool::CheckUrlValid(const std::string &url)
{
	//�ж�url�Ƿ�Ϊ��
	if (url.empty())
	{
		return false;
	}
	//��Ч��url����Ϊ"https://"��"http://"��ʼ���ַ���
	const std::string strHttps = "https://";
	const std::string strHttp = "http://";
	//��Ч��url���ȱ������"http://",������Ч
	size_t iLen = url.size();
	if (iLen <= strHttp.size())
	{
		return false;
	}
	//�ж��Ƿ���"http://"��ͷ
	if (0 == url.compare(0, strHttp.size(), strHttp))
	{
		return true;
	}
	//�ж��Ƿ���"https://"��ͷ
	else if (0 == url.compare(0, strHttps.size(), strHttps))
	{
		//��Ч��url���ȱ������"https://"��������Ч
		if (iLen > strHttps.size())
		{
			return true;
		}		
	}

	return false;	
}

bool eSDKTool::CheckIPValid(const std::string &ip)
{
	if (ip.empty())
	{
		return false;
	}

	const unsigned int DOT_NUM = 3;
	const unsigned int MAX_IP = 255;
	unsigned int auIpTemp[4] = {0};
	unsigned int iNum = 0;				
	int iValue = 0;
	bool bFlag = false;
	unsigned int iIndex = 0;
	for (;;)
	{
		iValue = ip[iIndex];
		iIndex++;
		if ((iValue >= '0') && (iValue <= '9'))
		{
			bFlag = true;
			auIpTemp[iNum] = auIpTemp[iNum] * 10 + (unsigned int)iValue - '0';
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

	return true;
}
