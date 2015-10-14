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
	 *��ȡtoken�����൥ʵ��
	 * 
	 *�ú������ڻ�ȡtoken�����൥ʵ��
	 *
	 *@return		�ɹ���token�����൥ʵ��ָ�룬 ʧ�ܣ�NULL
	 *@attention	��
	 *@par			��
	**/
	static TokenManagerExecute* Instance();
	/**
	 *�ͷ�token������ʵ��
	 * 
	 *�ú��������ͷ�token������ʵ��
	 *
	 *@attention	��
	 *@par			��
	**/
	static void DestroyInstance(void);

public:
	/**
	 *��ʼ��
	 * 
	 *�ú������ڳ�ʼ��token������
	 *
	 *@return 		�ɹ���true		ʧ�ܣ�false
	 *@attention	��
	 *@par 			��
	**/
	virtual bool init(void);
	/**
	 *ȥ��ʼ��
	 * 
	 *�ú�������ȥ��ʼ��token������
	 *
	 *@return 		�ɹ���true		ʧ�ܣ�false
	 *@attention	��
	 *@par 			��
	**/
	virtual bool uninit(void);
	/**
	 *д��token������
	 * 
	 *�ú�������д��token
	 *
	 *@param[in]	Credential
	 *@return		�ɹ���true		ʧ�ܣ�false
	 *@attention	��
	 *@par			��
	**/
	virtual bool WriteToken(const std::string &Credential);
	/**
	 *��ձ����token
	 * 
	 *�ú���������ձ����token
	 *	
	 *@return		�ɹ���true		ʧ�ܣ�false
	 *@attention	��
	 *@par			��
	**/
	virtual bool ClearToken(void);
	/**
	 *��ȡ�����token
	 * 
	 *�ú������ڶ�ȡ�����token
	 *
	 *@param[out]	Token
	 *@return		�ɹ���true		ʧ�ܣ�false
	 *@attention	��
	 *@par			��
	**/
	virtual bool GetToken(std::string &Token);

private:
	TokenManagerExecute();
	~TokenManagerExecute();

private:
	std::string m_token;
	HANDLE m_mutex;

private:
	static TokenManagerExecute* m_pTokenMgr; //��ʵ������ָ��

};

#endif
