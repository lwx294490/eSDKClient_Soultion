#include <io.h>
#include <direct.h>
#include "eSDKLogExecute.h"
#include "eSDKTool.h"

eSDKLogExecute* eSDKLogExecute::m_eSDKLog = NULL;
int eSDKLogExecute::m_index = 0;
std::map<int, eSDKLogExecute*> eSDKLogExecute::m_InstanceMap;

eSDKLog::eSDKLog(void)
{
}

eSDKLog::~eSDKLog(void)
{
	
}

eSDKLog* eSDKLog::getInstance()
{
	return dynamic_cast<eSDKLog*>(eSDKLogExecute::Instance());
}

void eSDKLog::destroyInstance()
{
	eSDKLogExecute::Destroy();
}

eSDKLogExecute::eSDKLogExecute()
	:m_LogLevel(INFO_LEVEL)
{

}

eSDKLogExecute::~eSDKLogExecute(void)
{
	try{
		m_ModuleName.clear();
		m_ModuleFile.clear();
		m_CategoryName.clear();
		m_LogConfigFileName.clear();
		m_LogFile.clear();
	}
	catch(...)
	{
	}
}

eSDKLogExecute* eSDKLogExecute::Instance()
{	
	if (NULL == m_eSDKLog)
	{
		m_eSDKLog = new eSDKLogExecute;
	}

	return m_eSDKLog;
}

void eSDKLogExecute::Destroy()
{
	eSDKLogExecute::m_index--;
	if (0 != eSDKLogExecute::m_index)
	{
		return;
	}

	std::map<int, eSDKLogExecute*>::iterator iter_b = m_InstanceMap.begin();
	std::map<int, eSDKLogExecute*>::iterator iter_e = m_InstanceMap.end();
	for (; iter_b != iter_e; iter_b++)
	{
		log4cpp::Category& root = log4cpp::Category::getRoot().getInstance(iter_b->second->m_CategoryName);//lint !e1705
		root.critStream() << "==============log end==============";
		delete iter_b->second;
	}

	log4cpp::Category::shutdown();
	m_InstanceMap.clear();

	if (NULL != m_eSDKLog)
	{
		delete m_eSDKLog;
		m_eSDKLog = NULL;
	}
}

log4cpp::Category& eSDKLogExecute::getCategoryInstance(const int& iInstanceIndex)
{
	std::map<int, eSDKLogExecute*>::iterator iter_b = m_InstanceMap.find(iInstanceIndex);
	std::map<int, eSDKLogExecute*>::iterator iter_e = m_InstanceMap.end();
	if (iter_b == iter_e)
	{
		log4cpp::Category& root = log4cpp::Category::getRoot();
		return root;
	}

	log4cpp::Category& root = log4cpp::Category::getRoot().getInstance(iter_b->second->m_CategoryName);//lint !e1705
	return root;
}

int eSDKLogExecute::init(const std::string &strModuleName, int& iInstanceIndex)
{	
	if (strModuleName.empty())
	{
		return ESDKLOG_FAIL; 
	}

	eSDKLogExecute *pInstance = new eSDKLogExecute;	
	pInstance->m_ModuleName = strModuleName;
	pInstance->m_ModuleFile = strModuleName + ".dll";
	pInstance->m_CategoryName = strModuleName + "_Category";
	pInstance->m_LogConfigFileName = strModuleName + "_config.ini";
	pInstance->m_LogFile = "log\\" + strModuleName + ".log";
	
	(void)(pInstance->loadConfig());
	(void)(pInstance->loadLog4cpp());
	(void)(pInstance->setLog4CppLevel());
	log4cpp::Category& root = log4cpp::Category::getRoot().getInstance(pInstance->m_CategoryName);//lint !e1705
	root.critStream() << "==============log start============";
	(void)m_InstanceMap.insert(std::pair<int, eSDKLogExecute*>(eSDKLogExecute::m_index, pInstance));
	iInstanceIndex = eSDKLogExecute::m_index;
	eSDKLogExecute::m_index++;
	return ESDKLOG_SUCCESS;//lint !e429
}

int eSDKLogExecute::loadLog4cpp() const
{
	/*lint -save -e429*/
	log4cpp::PatternLayout* pLayout = new log4cpp::PatternLayout();
	pLayout->setConversionPattern("[%d][%5p]-%m%n");//%d日期 %p优先级 %m消息 %n换行符
	std::string logPath;
	eSDKTool::getModulePath(m_ModuleFile, logPath);
	logPath.append("\\");
	logPath.append(m_LogFile);	
	std::string logDirect = logPath.substr(0,logPath.rfind('\\')+1);
	if (!logDirect.empty())
	{
		(void)_mkdir(logDirect.c_str());
	}

	log4cpp::RollingFileAppender* rollfileAppender = new log4cpp::RollingFileAppender("rollfileAppender",logPath);//logPath必须使用绝对路径
	rollfileAppender->setLayout(pLayout);
	log4cpp::Category& root = log4cpp::Category::getRoot().getInstance(m_CategoryName);//lint !e1705
	root.addAppender(rollfileAppender);
	return ESDKLOG_SUCCESS;
	/*lint -restore*/
}//lint !e429
int eSDKLogExecute::setLog4CppLevel() const
{
	log4cpp::Category& root = log4cpp::Category::getRoot();
	switch (m_LogLevel)
	{
	case INFO_LEVEL:
		{
			root.setPriority(log4cpp::Priority::INFO);
			break;
		}
	case DEBUG_LEVEL:
		{
			root.setPriority(log4cpp::Priority::DEBUG);
			break;
		}
	case WARN_LEVEL:
		{
			root.setPriority(log4cpp::Priority::WARN);
			break;
		}
	case ERROR_LEVEL:
		{
			root.setPriority(log4cpp::Priority::ERROR);
			break;
		}
	default:
		{
			root.setPriority(log4cpp::Priority::INFO);
		}
	}

	return ESDKLOG_SUCCESS;
}

int eSDKLogExecute::loadConfig()
{
	std::string logConfigPath;	
	eSDKTool::getModulePath(m_ModuleFile, logConfigPath); 
	logConfigPath.append("\\");
	logConfigPath.append(m_LogConfigFileName);

	const int LENGTH = 10;
	char tchValue[LENGTH] = {0};
	(void)::GetPrivateProfileStringA(m_ModuleName.c_str(),"loglevel","",tchValue,LENGTH-1,logConfigPath.c_str());
	
	std::string strLogLevel(tchValue);
	if(0 == strLogLevel.compare("info"))
	{
		m_LogLevel = INFO_LEVEL;
	}
	else if(0 == strLogLevel.compare("warning"))
	{
		m_LogLevel = WARN_LEVEL;
	}
	else if(0 == strLogLevel.compare("error"))
	{
		m_LogLevel = ERROR_LEVEL;
	}
	else if(0 == strLogLevel.compare("debug"))
	{
		m_LogLevel = DEBUG_LEVEL;
	}
	else
	{
		m_LogLevel = INFO_LEVEL;
	}

	return m_LogLevel;
}

