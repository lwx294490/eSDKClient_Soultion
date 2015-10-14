#ifndef _CLASS_FACTORY_H_
#define _CLASS_FACTORY_H_

#include <map>
#include <string>
#include "DynamicClass.h"

//类工厂，使用反射机制实现类动态加载
class ClassFactory
{
public:
	//通过类名获取该类对象实例的生成方法
	static CreateClass GetClassByName(const std::string &className);
	//通过类名获取该类对象实例的release方法
	static ReleaseClass ReleaseClassByName(const std::string &className);
	//注册类名和该类对象实例的生成方法
	static void RegistClass(const std::string &name, CreateClass CreateMethod, ReleaseClass ReleaseMethod);
	//业务注销
	static void DestroyClass();

private:
	static std::map<std::string,CreateClass> m_classCreateMap; //类名和类对象实例的生成方法的关系映射表
	static std::map<std::string,ReleaseClass> m_classReleaseMap; //类名和类对象实例的销毁方法的关系映射表
};


#endif

