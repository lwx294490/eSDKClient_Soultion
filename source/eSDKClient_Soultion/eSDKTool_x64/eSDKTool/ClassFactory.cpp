
#include "ServiceFactory.h"
#include "ClassFactory.h"

CreateClass ServiceFactory::GetClassByName(const std::string &className)
{
	return ClassFactory::GetClassByName(className);
}

ReleaseClass ServiceFactory::ReleaseClassByName(const std::string &className)
{
	return ClassFactory::ReleaseClassByName(className);
}

void ServiceFactory::RegistClass(const std::string &name, CreateClass CreateMethod, ReleaseClass ReleaseMethod)
{
	ClassFactory::RegistClass(name, CreateMethod, ReleaseMethod);
}

void ServiceFactory::DestroyClass()
{
	ClassFactory::DestroyClass();
}

std::map<std::string,CreateClass> ClassFactory::m_classCreateMap;
std::map<std::string,ReleaseClass> ClassFactory::m_classReleaseMap;

CreateClass ClassFactory::GetClassByName(const std::string &className)
{
	std::map<std::string,CreateClass>::iterator iter;
	iter = m_classCreateMap.find(className);
	if(iter == m_classCreateMap.end())
	{
		return NULL;
	}
	else
	{
		return iter->second;
	}
}

ReleaseClass ClassFactory::ReleaseClassByName(const std::string &className)
{
	std::map<std::string,ReleaseClass>::iterator iter;
	iter = m_classReleaseMap.find(className);
	if(iter == m_classReleaseMap.end())
	{
		return NULL;
	}
	else
	{
		return iter->second;
	}
}

void ClassFactory::RegistClass(const std::string &name, CreateClass CreateMethod, ReleaseClass ReleaseMethod)
{
	(void)m_classCreateMap.insert(std::pair<std::string, CreateClass>(name,CreateMethod));
	(void)m_classReleaseMap.insert(std::pair<std::string, ReleaseClass>(name,ReleaseMethod));
}

void ClassFactory::DestroyClass()
{
	m_classCreateMap.clear();
	m_classReleaseMap.clear();
}

