#ifndef _TOKEN_MANAGER_H_
#define _TOKEN_MANAGER_H_

#include <string>

#ifdef ESDKSSO_EXPORTS
#define ESDKTOKEN_API __declspec(dllexport)
#else
#define ESDKTOKEN_API __declspec(dllimport)
#endif

/**
 *token������
 * 
 *��������token��д�롢��ȡ������Ȳ���
 *
 *@attention	��
 *@par			��
**/
class ESDKTOKEN_API TokenManager
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
	static TokenManager* getInstance(void);
	/**
	 *�ͷ�token������ʵ��
	 * 
	 *�ú��������ͷ�token������ʵ��
	 *
	 *@attention	��
	 *@par			��
	**/
	static void ReleaseInstance(void);

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
	virtual bool init(void) = 0;

	/**
	 *ȥ��ʼ��
	 * 
	 *�ú�������ȥ��ʼ��token������
	 *
	 *@return 		�ɹ���true		ʧ�ܣ�false
	 *@attention	��
	 *@par 			��
	**/
	virtual bool uninit(void) = 0;

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
	virtual bool WriteToken(const std::string &Credential) = 0;
	/**
	 *��ձ����token
	 * 
	 *�ú���������ձ����token
	 *	
	 *@return		�ɹ���true		ʧ�ܣ�false
	 *@attention	��
	 *@par			��
	**/
	virtual bool ClearToken(void) = 0;
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
	virtual bool GetToken(std::string &Token) = 0;

protected:
	TokenManager();
	virtual ~TokenManager();	
};

#endif
