#ifndef _CLASS_FACTORY_H_
#define _CLASS_FACTORY_H_

#include <map>
#include <string>
#include "DynamicClass.h"

//�๤����ʹ�÷������ʵ���ද̬����
class ClassFactory
{
public:
	//ͨ��������ȡ�������ʵ�������ɷ���
	static CreateClass GetClassByName(const std::string &className);
	//ͨ��������ȡ�������ʵ����release����
	static ReleaseClass ReleaseClassByName(const std::string &className);
	//ע�������͸������ʵ�������ɷ���
	static void RegistClass(const std::string &name, CreateClass CreateMethod, ReleaseClass ReleaseMethod);
	//ҵ��ע��
	static void DestroyClass();

private:
	static std::map<std::string,CreateClass> m_classCreateMap; //�����������ʵ�������ɷ����Ĺ�ϵӳ���
	static std::map<std::string,ReleaseClass> m_classReleaseMap; //�����������ʵ�������ٷ����Ĺ�ϵӳ���
};


#endif

