#ifndef _DYNAMIC_CLASS_H_
#define _DYNAMIC_CLASS_H_

#include <string>

#ifdef ESDKTOOL_EXPORTS
#define DYNAMICCLASS_API __declspec(dllexport)
#else
#define DYNAMICCLASS_API __declspec(dllimport)
#endif

typedef void* (*CreateClass)(void);
typedef void (*ReleaseClass)(void);
//动态注册类
class DYNAMICCLASS_API DynamicClass
{
public:
	DynamicClass(const std::string &name, CreateClass CreateMethod, ReleaseClass ReleaseMethod);
};

/*定义宏,类通过包含该宏,实现动态注册*/
#define DECLARE_RUNTIME(class_name)  \
	static DynamicClass* class_name##gd;

/*宏实现,类通过实现该宏,实现动态创建*/
#define IMPLEMENT_RUNTIME(class_name, class_space)   \
	DynamicClass* class_space::class_name##gd = new DynamicClass(#class_name,(CreateClass)(class_space::CreateInstance), (ReleaseClass)(class_space::DestroyInstance));

#endif