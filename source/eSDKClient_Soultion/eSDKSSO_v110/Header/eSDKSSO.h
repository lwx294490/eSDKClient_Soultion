#ifndef _ESDK_SSO_H_
#define _ESDK_SSO_H_

#include <string>

#ifdef ESDKSSO_EXPORTS
#define ESDKSSO_API __declspec(dllexport)
#else
#define ESDKSSO_API __declspec(dllimport)
#endif

typedef enum
{
	ESDKSSO_SUCCESS = 0,
	ESDKSSO_FAIL,
	ESDKSSO_INTERNAL_ERROR
} ESDKSSO_ERR_CODE_E;

typedef enum
{
	ESDKSSO_LOGIN_SSO = 0,
	ESDKSSO_LOGIN_SERVICE
} ESDKSSO_LOGIN_TYPE_E;

typedef enum
{
	ESDKSSO_SERVICE_PASSWORD_LOGIN = 0,
	ESDKSSO_SERVICE_TOKEN_LOGIN
} ESDKSSO_PDU_LOGIN_TYPE_E;

//�����¼������⿪�ŵĽӿ���
class ESDKSSO_API eSDKSSO
{
public:
	//��ȡ�����¼�����ʵ������
	static eSDKSSO* getInstance(void);
	//���ٵ����¼�����ʵ������
	static void ReleaseInstance(void);

public:
	//�����¼�����ʼ��
	virtual int init(void) = 0;
	//ʹ��token���е�¼
	virtual int login(const std::string &token) = 0;
	//ʹ���û���������е�¼
	virtual int login(const std::string &name, const std::string &password, int type) = 0;
	//�ǳ�
	virtual int logout(void) = 0;
	//����eSDK SSO Sever URL
	virtual int setConfig(const std::string &param) = 0;
	//ȥ��ʼ��
	virtual int uninit(void) = 0;
	//��������IP
	virtual int setHostIP(const std::string &ip) = 0;
	//����ҵ������ȡ���ص�ҵ����
	virtual unsigned long getServiceHandleByName(const std::string& strServiceName) = 0;

protected:
	eSDKSSO();
	virtual ~eSDKSSO();
};

#endif
