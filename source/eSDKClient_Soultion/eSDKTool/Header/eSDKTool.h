#ifndef _ESDKTOOL_H
#define _ESDKTOOL_H

#ifdef ESDKTOOL_EXPORTS
#define ESDKTOOL_API __declspec(dllexport)
#else
#define ESDKTOOL_API __declspec(dllimport)
#endif

#ifndef ESDKTOOL_CALL
#define ESDKTOOL_CALL  __stdcall
#endif

#include <string>
#include <vector>
#include <map>

#define HOST_NAME_MAX_LENGTH 128

//������
class ESDKTOOL_API eSDKTool
{
protected:
	eSDKTool(void);
	~eSDKTool(void);
public:
	//��ȡ��̬��·��
	static void ESDKTOOL_CALL getModulePath(const std::string& strModuleName, std::string& cstrPath);
	//��ȡ����IP
	static std::string ESDKTOOL_CALL getHostIP();
	//stringת����wstring
	static std::wstring ESDKTOOL_CALL StringToWString(std::string str);
	//wstringת����string
	static std::string ESDKTOOL_CALL WStringToString(std::wstring wstr);
	//���ַ���������ָ���ķָ����
	static void ESDKTOOL_CALL AddSplitToString(std::string &src, char separator);
	//����ָ���ķָ����Ų���ַ���
	static void ESDKTOOL_CALL SplitString(const std::string &src, char separator, std::vector<std::string>& vect);
	//����ָ��Ŀ¼�µ�ini�ļ���dll�ļ�
	static void ESDKTOOL_CALL FindFiles(std::map<std::string, std::string> &sIniFiles,std::vector<std::string> &sDllFiles, const std::string& sPath);
	//���URL�ĺϷ���,��Ч��URL������"http://"��"https://"��ͷ
	static bool ESDKTOOL_CALL CheckUrlValid(const std::string &url);
	//���IP�ĺϷ���
	static bool ESDKTOOL_CALL CheckIPValid(const std::string &ip);
};

#endif

