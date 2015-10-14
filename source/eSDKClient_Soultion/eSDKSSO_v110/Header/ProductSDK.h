#ifndef _PRODUCT_SDK_H_
#define _PRODUCT_SDK_H_

#ifdef PRODUCT_SDK_EXPORTS
#define PRODUCT_SDK_API __declspec(dllexport)
#else
#define PRODUCT_SDK_API __declspec(dllimport)
#endif

#include <string>


//业务抽象类
class PRODUCT_SDK_API ProductSDK
{
public:
	ProductSDK(void)
	{

	}
	virtual ~ProductSDK(void)
	{

	}

public:
	//业务抽象的初始化接口
	virtual int Init() = 0;
	virtual int UnInit() = 0;
	virtual int Login(const std::string& token) = 0;
	virtual int Login(const std::string& name, const std::string& password) = 0;
	virtual int Logout() = 0;
};

#endif

