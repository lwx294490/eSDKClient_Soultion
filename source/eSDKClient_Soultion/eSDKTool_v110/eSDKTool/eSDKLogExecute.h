#ifndef _ESDKLOG_EXECUTE_H
#define _ESDKLOG_EXECUTE_H

//#include "log4cpp.h"
#include <string>
#include <map>
#include "eSDKLog.h"

// class eSDKLogCategoryExec : public eSDKLogCategory
// class eSDKLogCategoryExec
// {
// public:
// 	eSDKLogCategoryExec()
// 	{
// 
// 	}
// 
// 	~eSDKLogCategoryExec()
// 	{
// 		if (NULL != m_pStream)
// 		{
// 			m_pStream = NULL;
// 		}
// 	}
// 
// public:
// 	template<typename T> eSDKLogCategoryExec& operator<<(const T& t)
// 	{
// 		if (NULL != m_pStream)
// 		{
// 			m_pStream->operator <<(t);
// 		}		
// 		return *this;
// 	}
// 
// public:
// 	log4cpp::CategoryStream* m_pStream;
// };


class eSDKLogExecute : public eSDKLog
{
public:
	static eSDKLogExecute* Instance(void);
	static void Destroy(void);	

private:
	eSDKLogExecute();
	~eSDKLogExecute();

public:
	virtual int init(const std::string &strModuleName, int& iInstanceIndex);	
	virtual log4cpp::Category& getCategoryInstance(const int& iInstanceIndex);

private:
	int loadConfig();			//加载日志配置
	int loadLog4cpp() const;	//加载Log4cpp
	int setLog4CppLevel() const;//设置Log4cpp的日志级别
	
private:
	std::string m_ModuleName;
	std::string m_ModuleFile;
	std::string m_CategoryName;
	std::string m_LogConfigFileName;
	std::string m_LogFile;
	int m_LogLevel;

private:
	static int m_index;
	static std::map<int, eSDKLogExecute*> m_InstanceMap;

private:
	static eSDKLogExecute* m_eSDKLog;

};

#endif
