#ifndef _ESDKLOG_H
#define _ESDKLOG_H

#ifdef ESDKTOOL_EXPORTS
#define ESDKLOG_API __declspec(dllexport)
#else
#define ESDKLOG_API __declspec(dllimport)
#endif

#include "log4cpp.h"

extern int g_iLogInstanceIndex;

//lint -e773
//四种日志级别，打印简短描述
#define DEBUG_LOG() eSDKLog::getInstance()->getCategoryInstance(g_iLogInstanceIndex).debugStream()  << "{" << __FUNCTION__ << "} "
#define INFO_LOG()  eSDKLog::getInstance()->getCategoryInstance(g_iLogInstanceIndex).infoStream()   << "{" << __FUNCTION__ << "} "
#define WARN_LOG()  eSDKLog::getInstance()->getCategoryInstance(g_iLogInstanceIndex).warnStream()   << "{" << __FUNCTION__ << "} "
#define ERROR_LOG() eSDKLog::getInstance()->getCategoryInstance(g_iLogInstanceIndex).errorStream()  << "{" << __FUNCTION__ << "} "

#define EXP1(param1) #param1 << " = " << (param1)
#define EXP2(param1, param2) \
	EXP1(param1) << ", " << EXP1(param2)
#define EXP3(param1, param2, param3) \
	EXP2(param1, param2) << ", " << EXP1(param3)
#define EXP4(param1, param2, param3, param4) \
	EXP3(param1, param2, param3) << ", " << EXP1(param4)
#define EXP5(param1, param2, param3, param4, param5) \
	EXP4(param1, param2, param3, param4) << ", " << EXP1(param5)
#define EXP6(param1, param2, param3, param4, param5, param6) \
	EXP5(param1, param2, param3, param4, param5) << ", " << EXP1(param6)

//带参数打印info级别日志，最多6个参数
#define INFO_PARAM0() INFO_LOG()
#define INFO_PARAM1(param1) \
	INFO_PARAM0() << EXP1(param1)
#define INFO_PARAM2(param1, param2) \
	INFO_PARAM0() << EXP2(param1, param2)
#define INFO_PARAM3(param1, param2, param3) \
	INFO_PARAM0() << EXP3(param1, param2, param3)
#define INFO_PARAM4(param1, param2, param3, param4) \
	INFO_PARAM0() << EXP4(param1, param2, param3, param4)
#define INFO_PARAM5(param1, param2, param3, param4, param5) \
	INFO_PARAM0() << EXP5(param1, param2, param3, param4, param5)
#define INFO_PARAM6(param1, param2, param3, param4, param5, param6) \
	INFO_PARAM0() << EXP6(param1, param2, param3, param4, param5, param6)

//带参数打印debug级别日志，最多6个参数
#define DEBUG_PARAM0() DEBUG_LOG()
#define DEBUG_PARAM1(param1) \
	DEBUG_PARAM0() << EXP1(param1)
#define DEBUG_PARAM2(param1, param2) \
	DEBUG_PARAM0() << EXP2(param1, param2)
#define DEBUG_PARAM3(param1, param2, param3) \
	DEBUG_PARAM0() << EXP3(param1, param2, param3)
#define DEBUG_PARAM4(param1, param2, param3, param4) \
	DEBUG_PARAM0() << EXP4(param1, param2, param3, param4)
#define DEBUG_PARAM5(param1, param2, param3, param4, param5) \
	DEBUG_PARAM0() << EXP5(param1, param2, param3, param4, param5)
#define DEBUG_PARAM6(param1, param2, param3, param4, param5, param6) \
	DEBUG_PARAM0() << EXP6(param1, param2, param3, param4, param5, param6)

//带参数打印warn级别日志，最多6个参数
#define WARN_PARAM0() WARN_LOG()
#define WARN_PARAM1(param1) \
	WARN_PARAM0() << EXP1(param1)
#define WARN_PARAM2(param1, param2) \
	WARN_PARAM0() << EXP2(param1, param2)
#define WARN_PARAM3(param1, param2, param3) \
	WARN_PARAM0() << EXP3(param1, param2, param3)
#define WARN_PARAM4(param1, param2, param3, param4) \
	WARN_PARAM0() << EXP4(param1, param2, param3, param4)
#define WARN_PARAM5(param1, param2, param3, param4, param5) \
	WARN_PARAM0() << EXP5(param1, param2, param3, param4, param5)
#define WARN_PARAM6(param1, param2, param3, param4, param5, param6) \
	WARN_PARAM0() << EXP6(param1, param2, param3, param4, param5, param6)

//带参数打印error级别日志，最多6个参数
#define ERROR_PARAM0() ERROR_LOG()
#define ERROR_PARAM1(param1) \
	ERROR_PARAM0() << EXP1(param1)
#define ERROR_PARAM2(param1, param2) \
	ERROR_PARAM0() << EXP2(param1, param2)
#define ERROR_PARAM3(param1, param2, param3) \
	ERROR_PARAM0() << EXP3(param1, param2, param3)
#define ERROR_PARAM4(param1, param2, param3, param4) \
	ERROR_PARAM0() << EXP4(param1, param2, param3, param4)
#define ERROR_PARAM5(param1, param2, param3, param4, param5) \
	ERROR_PARAM0() << EXP5(param1, param2, param3, param4, param5)
#define ERROR_PARAM6(param1, param2, param3, param4, param5, param6) \
	ERROR_PARAM0() << EXP6(param1, param2, param3, param4, param5, param6)
//lint +e773

enum LOGLEVEL
{
	DEBUG_LEVEL = 0,
	INFO_LEVEL,
	WARN_LEVEL,
	ERROR_LEVEL
};

typedef enum
{
	ESDKLOG_SUCCESS = 0,
	ESDKLOG_FAIL
} ESDKLOG_ERR_CODE_E;

//日志类
class ESDKLOG_API eSDKLog
{
public:	
	static eSDKLog* getInstance(void);
	static void destroyInstance();	

public:
	virtual int init(const std::string &strModuleName, int& iInstanceIndex) = 0;	
	virtual log4cpp::Category& getCategoryInstance(const int& iInstanceIndex) = 0;

protected:
	eSDKLog(void);
	virtual ~eSDKLog(void);
};


#endif
