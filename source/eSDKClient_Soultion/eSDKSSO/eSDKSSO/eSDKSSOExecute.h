#ifndef _ESDK_SSO_EXECUTE_H_
#define _ESDK_SSO_EXECUTE_H_

#ifdef WIN32
#include <Windows.h>
#endif

#include <string>
#include <vector>
#include <map>
#include "eSDKSSO.h"
#include "DynamicClass.h"

#pragma warning( disable: 4251 )

class ProductSDK;

class eSDKSSOExecute : public eSDKSSO
{
public:
	//���ɿͻ���ƽ̨�ĵ�ʵ��
	static eSDKSSOExecute* CreateInstance();
	//���ٿͻ���ƽ̨�ĵ�ʵ��
	static void DestroyInstance(void);

public:
	//�ͻ���ƽ̨��ʼ��
	virtual int init(void);
	//ʹ��token���е�¼
	virtual int login(const std::string &token);
	//ʹ���û���������е�¼
	virtual int login(const std::string &name, const std::string &password, int type);
	//�ǳ�
	virtual int logout(void);
	//����eSDK SSO Sever URL
	virtual int setConfig(const std::string &param);
	//ȥ��ʼ��
	virtual int uninit(void);
	//��������IP��ַ
	virtual int setHostIP(const std::string &ip);

	virtual unsigned long getServiceHandleByName(const std::string& strServiceName);

private:
	eSDKSSOExecute();
	~eSDKSSOExecute();
	void loadPDUSDK(void);
	int setWorkDirctoryByClassName(const std::string &className);

private:
	std::map<std::string, HINSTANCE> m_vecDllHandle; //�洢dll�ļ����
	std::vector<std::string> m_vecClassName; //�洢������ص�ҵ��������
	
	typedef std::map<std::string, ProductSDK*> ClassInstanceMap;
	ClassInstanceMap m_vecClassInstance;  //ҵ������ʵ�����Ķ���ָ���ӳ���ϵ��

	typedef std::map<std::string, ESDKSSO_PDU_LOGIN_TYPE_E> LoginTypeMap;
	LoginTypeMap m_vecPDULoginType; //ҵ������ҵ���¼��ʽ��ӳ���ϵ��

	std::map<std::string, std::string> m_ServiceWorkDirectMap; //��ƷSDK����Ŀ¼��ӳ���ϵ��
	std::string m_CurrentDirect; //�洢ISV APP������Ŀ¼

	bool bInitFlag;
private:
	static eSDKSSOExecute* m_eSDKSSO; //��ʵ������ָ��

private:
	DECLARE_RUNTIME(eSDKSSOExecute)

};

#endif
