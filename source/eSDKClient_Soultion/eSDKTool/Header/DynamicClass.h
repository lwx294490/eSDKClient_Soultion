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
//��̬ע����
class DYNAMICCLASS_API DynamicClass
{
public:
	DynamicClass(const std::string &name, CreateClass CreateMethod, ReleaseClass ReleaseMethod);
};

/*�����,��ͨ�������ú�,ʵ�ֶ�̬ע��*/
#define DECLARE_RUNTIME(class_name)  \
	static DynamicClass* class_name##gd;

/*��ʵ��,��ͨ��ʵ�ָú�,ʵ�ֶ�̬����*/
#define IMPLEMENT_RUNTIME(class_name, class_space)   \
	DynamicClass* class_space::class_name##gd = new DynamicClass(#class_name,(CreateClass)(class_space::CreateInstance), (ReleaseClass)(class_space::DestroyInstance));

#endif