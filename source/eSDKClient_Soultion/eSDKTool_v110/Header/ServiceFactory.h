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

//�๤����ʹ�÷������ʵ���ද̬����
class SERVICEFACTORY_API ServiceFactory
{
public:
	//ͨ��������ȡ�������ʵ�������ɷ���
	static CreateClass GetClassByName(const std::string &className);
	//ͨ��������ȡ�������ʵ����release����
	static ReleaseClass ReleaseClassByName(const std::string &className);
	//ע�������͸������ʵ�������ɷ���
	static void RegistClass(const std::string &name, CreateClass CreateMethod, ReleaseClass ReleaseMethod);
	//ע��ҵ��
	static void DestroyClass();
};


#endif