#ifndef _ESDK_CLIENT_PLATFORM_H_
#define _ESDK_CLIENT_PLATFORM_H_

#include <string>

#ifdef ESDKCLIENTPLATFORM_EXPORTS
#define ESDKCLIENT_PLATFORM_API __declspec(dllexport)
#else
#define ESDKCLIENT_PLATFORM_API __declspec(dllimport)
#endif

#ifndef ESDKCLIENT_PLATFORM_DEPEND
#define ESDKCLIENT_PLATFORM_DEPEND
#endif

typedef enum
{
	ESDKCLIENT_PLATFORM_SUCCESS = 0,
	ESDKCLIENT_PLATFORM_FAIL,
	ESDKCLIENT_PLATFORM_INTERNAL_ERROR
} ESDKCLINET_PLATFORM_ERR_CODE_E;

#ifndef CALLBACK
#define CALLBACK				__stdcall
#endif

typedef enum
{
	ESDKCLIENTPLATFORM_UPDATE_ASK = 0,			//����ѯ��
	ESDKCLIENTPLATFORM_UPDATE_START,			//������ʼ
	ESDKCLIENTPLATFORM_UPDATE_FINISHED			//�������
} ESDK_MESSAGE_CODE_E;

typedef bool (CALLBACK *eSDKMessageCallBack)(int iMsgID, std::string strDescription);

//�ͻ���ƽ̨���⿪�ŵĽӿ���
class ESDKCLIENT_PLATFORM_API eSDKClientPlatform
{
protected:
	eSDKClientPlatform();
	virtual ~eSDKClientPlatform();
public:
	//��ȡ�ͻ���ƽ̨��ʵ������
	static eSDKClientPlatform* getInstance(void);
	//���ٿͻ���ƽ̨��ʵ������
	static void ReleaseInstance(void);

public:
	//�ͻ���ƽ̨��ʼ��
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
	//��������������
	virtual int setUpdateServer(const std::string &UpdateServer) = 0;
	//����������Ϣ�ص�����
	virtual bool SetMessageCallBack(eSDKMessageCallBack fpMsgCB) = 0;
};

#endif
