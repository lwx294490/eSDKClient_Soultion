#ifndef _UC_SDK_ABS_PROXY_H_
#define _UC_SDK_ABS_PROXY_H_

#include "DataType.h"
#include "UCSignalRecvAbsProxy.h"

#ifdef ESDKCLIENT_PLATFORM_DEPEND
#include "ProductSDK.h"
#endif


namespace eSDK {
	namespace UC {


/**
 *��Ȩ�����࣬��ƽ̨��ʹ��ʱ��UCSDKҵ���ܹ�����
 * 
 *�������ڵ�½�ǳ���Ȩ����UCSDK�������
 *
 *@attention	��
 *@par 			��
**/
#ifdef ESDKCLIENT_PLATFORM_DEPEND
class UCSDK_API UCSDKAbsProxy : public ProductSDK
#else
class UCSDK_API UCSDKAbsProxy
#endif
{
protected:
	UCSDKAbsProxy();
	virtual ~UCSDKAbsProxy();

public:
	/**
	 *��ȡ��Ȩ�����൥ʵ��
	 * 
	 *�ú������ڻ�ȡ��Ȩ�����൥ʵ��
	 *
	 *@return 		�ɹ���Ȩ�����൥ʵ��ָ�룬 ʧ�ܣ�NULL
	 *@attention	��
	 *@par 			��
	**/
	static UCSDKAbsProxy* GetInstance();

	/**
	 *�ͷż�Ȩ�����൥ʵ��
	 * 
	 *�ú��������ͷż�Ȩ�����൥ʵ��
	 *
	 *@attention	ͬʱ�ͷ�UCSDK����ҵ����ʵ��
	 *@par 			��
	**/
	static void ReleaseInstance();

public:
	/**
	 *��ʼ��
	 * 
	 *�ú������ڳ�ʼ��UCSDK����ҵ�񣬴�������ҵ��ʵ��
	 *
	 *@return 		�ɹ���0		ʧ�ܣ���0,�ο�������
	 *@attention	��
	 *@par 			��
	**/
	virtual int Init() = 0;

	/**
	 *ȥ��ʼ��
	 * 
	 *�ú�������ȥ��ʼ��UCSDK����ҵ��
	 *
	 *@return 		�ɹ���0		ʧ�ܣ���0,�ο�������
	 *@attention	��
	 *@par 			��
	**/
	virtual int UnInit() = 0;

	/**
	 *��½
	 * 
	 *�ú�������ʹ��token���е����½
	 *
	 *@param[in] 	strToken	�����½token
	 *@return 		�ɹ���0		ʧ�ܣ���0,�ο�������
	 *@attention	��
	 *@par 			��
	**/
	virtual int Login(const std::string& strToken) = 0;

	/**
	 *��½
	 * 
	 *�ú�������ʹ���˺�������е�½
	 *
	 *@param[in] 	strName		��½�˻�
	 *@param[in] 	strPassword	��½����
	 *@return 		�ɹ���0		ʧ�ܣ���0,�ο�������
	 *@attention	��
	 *@par 			��
	**/
	virtual int Login(const std::string& strName, const std::string& strPassword) = 0;

	/**
	 *�ǳ�
	 * 
	 *�ú������ڵǳ�
	 *
	 *@return 		�ɹ���0		ʧ�ܣ���0,�ο�������
	 *@attention	��
	 *@par 			��
	**/
	virtual int Logout() = 0;

	/**
	 *���õ�½������Url
	 * 
	 *�ú����������õ�½������Url
	 *
	 *@param[in] 	strSrvUrl	������Url
	 *@return 		�ɹ���0		ʧ�ܣ���0,�ο�������
	 *@attention	��
	 *@par 			��
	**/
	virtual int Config(const std::string& strSrvUrl) = 0;

	/**
	 *���õ�½����
	 * 
	 *�ú����������õ�½����
	 *
	 *@param[in] 	strLang		����
	 *@return 		�ɹ���0		ʧ�ܣ���0,�ο�������
	 *@attention	��
	 *@par 			��
	**/
	virtual int SetLang(const std::string& strLang) = 0;

	/**
	 *�����źŻص�ʵ��ָ��
	 * 
	 *�ú������������źŻص�ʵ��ָ��
	 *
	 *@param[in] 	pUCSignalRecvAbsProxy	�ź�ʵ��ָ��
	 *@return 		�ɹ���0		ʧ�ܣ���0,�ο�������
	 *@attention	UCSignalRecvAbsProxy��ISVʵ�֣������ź�ʵ���󣬴���ʵ��ָ��
	 *@par 			ʾ������
	**/
	virtual int SetUCSignalRecvAbsProxy(UCSignalRecvAbsProxy* pUCSignalRecvAbsProxy) = 0;
};

}
}

#endif