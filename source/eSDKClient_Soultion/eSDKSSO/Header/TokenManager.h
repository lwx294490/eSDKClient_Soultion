#ifndef _TOKEN_MANAGER_H_
#define _TOKEN_MANAGER_H_

#include <string>

#ifdef ESDKSSO_EXPORTS
#define ESDKTOKEN_API __declspec(dllexport)
#else
#define ESDKTOKEN_API __declspec(dllimport)
#endif

/**
 *token管理类
 * 
 *该类用于token的写入、读取、清除等操作
 *
 *@attention	无
 *@par			无
**/
class ESDKTOKEN_API TokenManager
{
public:
	/**
	 *获取token管理类单实例
	 * 
	 *该函数用于获取token管理类单实例
	 *
	 *@return		成功：token管理类单实例指针， 失败：NULL
	 *@attention	无
	 *@par			无
	**/
	static TokenManager* getInstance(void);
	/**
	 *释放token管理类实例
	 * 
	 *该函数用于释放token管理类实例
	 *
	 *@attention	无
	 *@par			无
	**/
	static void ReleaseInstance(void);

public:
	/**
	 *初始化
	 * 
	 *该函数用于初始化token管理类
	 *
	 *@return 		成功：true		失败：false
	 *@attention	无
	 *@par 			无
	**/
	virtual bool init(void) = 0;

	/**
	 *去初始化
	 * 
	 *该函数用于去初始化token管理类
	 *
	 *@return 		成功：true		失败：false
	 *@attention	无
	 *@par 			无
	**/
	virtual bool uninit(void) = 0;

	/**
	 *写入token、保存
	 * 
	 *该函数用于写入token
	 *
	 *@param[in]	Credential
	 *@return		成功：true		失败：false
	 *@attention	无
	 *@par			无
	**/
	virtual bool WriteToken(const std::string &Credential) = 0;
	/**
	 *清空保存的token
	 * 
	 *该函数用于清空保存的token
	 *	
	 *@return		成功：true		失败：false
	 *@attention	无
	 *@par			无
	**/
	virtual bool ClearToken(void) = 0;
	/**
	 *读取保存的token
	 * 
	 *该函数用于读取保存的token
	 *
	 *@param[out]	Token
	 *@return		成功：true		失败：false
	 *@attention	无
	 *@par			无
	**/
	virtual bool GetToken(std::string &Token) = 0;

protected:
	TokenManager();
	virtual ~TokenManager();	
};

#endif
