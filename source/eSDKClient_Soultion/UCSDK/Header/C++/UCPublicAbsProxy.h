#ifndef _UC_PUBLIC_ABS_PROXY_H_
#define _UC_PUBLIC_ABS_PROXY_H_

#include "DataType.h"


namespace eSDK {
	namespace UC {


/**
 *�����ӿڹ�����
 * 
 *�������ڹ����ӿڹ���
 *
 *@attention	��
 *@par 			��
**/
class UCSDK_API UCPublicAbsProxy
{
protected:
	UCPublicAbsProxy();
	virtual ~UCPublicAbsProxy();

public:
	/**
	 *��ȡ�����ӿڹ����൥ʵ��
	 * 
	 *�ú������ڻ�ȡ�����ӿڹ����൥ʵ��
	 *
	 *@return 		�ɹ��������ӿڹ����൥ʵ��ָ�룬 ʧ�ܣ�NULL
	 *@attention	��
	 *@par 			��
	**/
	static UCPublicAbsProxy* GetInstance();

	/**
	 *�ͷŹ����ӿڹ����൥ʵ��
	 * 
	 *�ú��������ͷŹ����ӿڹ����൥ʵ��
	 *
	 *@attention	�ڵ���UCSDKAbsProxy::ReleaseInstance()ʱ�򣬻����һ���ͷ�
	 *@par 			ʾ������
	**/
	static void ReleaseInstance();

public:
	/**
	 *����������Ϣ
	 * 
	 *�ú������ڷ���������Ϣ
	 *
	 *@param[in] 	publishInfoMap
	 *@return 		�ɹ���0		ʧ�ܣ���0,�ο�������
	 *@attention	��
	 *@par 			��
	**/
	virtual int PublishSelfInformation(const PublishInfoMap& publishInfoMap) = 0;

	/**
	 *ͨ����ϵ��uri��ȡ��ϵ״̬
	 * 
	 *�ú�������ͨ����ϵ��uri��ȡ��ϵ״̬
	 *
	 *@param[in] 	_uri		��ϵ��uri
	 *@param[out] 	_status		��ϵ��״̬
	 *@return 		�ɹ���0		ʧ�ܣ���0,�ο�������
	 *@attention	��
	 *@par 			��
	**/
	virtual int GetContactStatus(const std::string& _uri, int& _status) = 0;
};

}
}

#endif