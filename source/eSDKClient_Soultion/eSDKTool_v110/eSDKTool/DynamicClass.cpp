
#include "DynamicClass.h"
#include "ServiceFactory.h"

DynamicClass::DynamicClass(const std::string &name, CreateClass CreateMethod, ReleaseClass ReleaseMethod)
{
	ServiceFactory::RegistClass(name, CreateMethod, ReleaseMethod);
}

