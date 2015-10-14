#ifndef _SERVICE_FACTORY_H_
#define _SERVICE_FACTORY_H_

#include <map>
#include <string>
#include "DynamicClass.h"

#ifdef ESDKTOOL_EXPORTS
#define SERVICEFACTORY_API __declspec(dllexport)
#else
#define SERVICEFACTORY_API __declspec(dllimport)
#endif

//类工厂，使用反射机制实现类动态加载
class SERVICEFACTORY_API ServiceFactory
{
public:
	//通过类名获取该类对象实例的生成方法
	static CreateClass GetClassByName(const std::string &className);
	//通过类名获取该类对象实例的release方法
	static ReleaseClass ReleaseClassByName(const std::string &className);
	//注册类名和该类对象实例的生成方法
	static void RegistClass(const std::string &name, CreateClass CreateMethod, ReleaseClass ReleaseMethod);
	//注销业务
	static void DestroyClass();
};


#endif