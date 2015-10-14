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

//工具类
class ESDKTOOL_API eSDKTool
{
protected:
	eSDKTool(void);
	~eSDKTool(void);
public:
	//获取动态库路径
	static void ESDKTOOL_CALL getModulePath(const std::string& strModuleName, std::string& cstrPath);
	//获取主机IP
	static std::string ESDKTOOL_CALL getHostIP();
	//string转换成wstring
	static std::wstring ESDKTOOL_CALL StringToWString(std::string str);
	//wstring转换成string
	static std::string ESDKTOOL_CALL WStringToString(std::wstring wstr);
	//在字符串中增加指定的分割符号
	static void ESDKTOOL_CALL AddSplitToString(std::string &src, char separator);
	//根据指定的分隔符号拆分字符串
	static void ESDKTOOL_CALL SplitString(const std::string &src, char separator, std::vector<std::string>& vect);
	//查找指定目录下得ini文件和dll文件
	static void ESDKTOOL_CALL FindFiles(std::map<std::string, std::string> &sIniFiles,std::vector<std::string> &sDllFiles, const std::string& sPath);
	//检查URL的合法性,有效的URL必须以"http://"或"https://"开头
	static bool ESDKTOOL_CALL CheckUrlValid(const std::string &url);
	//检查IP的合法性
	static bool ESDKTOOL_CALL CheckIPValid(const std::string &ip);
};

#endif

