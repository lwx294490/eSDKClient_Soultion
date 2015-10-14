#ifndef _ESDK_CLIENT_PLATFORM_EXECUTE_H_
#define _ESDK_CLIENT_PLATFORM_EXECUTE_H_

#ifdef WIN32
#include <Windows.h>
#endif

#include <string>
#include <vector>
#include <map>
#include "eSDKClientPlatform.h"
#include "UpdateVersion.h"
#include "ProductSDK.h"

#define ESDKSSO_INI_FILE "eSDKSSO_config.ini"
#define ESDKSSO_DLL_FILE "eSDKSSO.dll"

class eSDKSSO;

class eSDKClientPlatformExecute : public eSDKClientPlatform
{
public:
	//���ɿͻ���ƽ̨�ĵ�ʵ��
	static eSDKClientPlatformExecute* Instance(void);
	//���ٿͻ���ƽ̨�ĵ�ʵ��
	static void Destroy(void);

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
	//��������������
	virtual int setUpdateServer(const std::string &UpdateServer);
	//����������Ϣ�ص�����
	virtual bool SetMessageCallBack(eSDKMessageCallBack fpMsgCB);

public:
	ProductSDK* getServiceByName(const std::string& strServiceName);
	HINSTANCE getServiceHandleByName(const std::string& strServiceName);
	
private:
	eSDKClientPlatformExecute();
	~eSDKClientPlatformExecute();
	int UpdateService(void);

private:
	eSDKSSO* m_eSDKSSO; //�ͻ��˵�ʵ��
	UpdateVersion *m_UpdateVersion; //������ʵ��

	std::vector<std::string> m_vecClassName;
	std::vector<std::string> m_vecVersion;
	std::vector<std::string> m_vecServiceName;

	typedef std::map<std::string, ProductSDK*> ClassInstanceMap;
	ClassInstanceMap m_vecClassInstance;  //ҵ������ʵ�����Ķ���ָ���ӳ���ϵ��

	HINSTANCE hDll;
	eSDKMessageCallBack m_pMsgCallBack;
private:
	static eSDKClientPlatformExecute* m_eSDKClientPlatform; //��ʵ������ָ��
};

#endif
