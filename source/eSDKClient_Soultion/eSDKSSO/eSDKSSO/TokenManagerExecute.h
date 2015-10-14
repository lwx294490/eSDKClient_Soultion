#ifndef _TOKEN_MANAGER_EXECUTE_H_
#define _TOKEN_MANAGER_EXECUTE_H_

#ifdef WIN32
#include <Windows.h>
#endif

#include "TokenManager.h"

class TokenManagerExecute : public TokenManager
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
	static TokenManagerExecute* Instance();
	/**
	 *释放token管理类实例
	 * 
	 *该函数用于释放token管理类实例
	 *
	 *@attention	无
	 *@par			无
	**/
	static void DestroyInstance(void);

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
	virtual bool init(void);
	/**
	 *去初始化
	 * 
	 *该函数用于去初始化token管理类
	 *
	 *@return 		成功：true		失败：false
	 *@attention	无
	 *@par 			无
	**/
	virtual bool uninit(void);
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
	virtual bool WriteToken(const std::string &Credential);
	/**
	 *清空保存的token
	 * 
	 *该函数用于清空保存的token
	 *	
	 *@return		成功：true		失败：false
	 *@attention	无
	 *@par			无
	**/
	virtual bool ClearToken(void);
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
	virtual bool GetToken(std::string &Token);

private:
	TokenManagerExecute();
	~TokenManagerExecute();

private:
	std::string m_token;
	HANDLE m_mutex;

private:
	static TokenManagerExecute* m_pTokenMgr; //单实例对象指针

};

#endif
