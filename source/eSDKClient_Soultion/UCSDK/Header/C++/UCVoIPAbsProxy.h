#ifndef _UC_VOIP_ABS_PROXY_H_
#define _UC_VOIP_ABS_PROXY_H_

#include "DataType.h"


namespace eSDK {
	namespace UC {


/**
 *VoIP������
 * 
 *��������VoIPͨ�Ų������������С��������ܾ����Ҷϡ��ָ������ֵȵ�
 *
 *@attention	��
 *@par 			��
**/
class UCSDK_API UCVoIPAbsProxy
{
protected:
	UCVoIPAbsProxy();
	virtual ~UCVoIPAbsProxy();

public:
	/**
	 *��ȡVoIP�����൥ʵ��
	 * 
	 *�ú������ڻ�ȡVoIP�����൥ʵ��
	 *
	 *@return 		�ɹ���VoIP�����൥ʵ��ָ�룬 ʧ�ܣ�NULL
	 *@attention	��
	 *@par 			��
	**/
	static UCVoIPAbsProxy* GetInstance();

	/**
	 *�ͷ�VoIP�����൥ʵ��
	 * 
	 *�ú��������ͷ�VoIP�����൥ʵ��
	 *
	 *@attention	�ڵ���UCSDKAbsProxy::ReleaseInstance()ʱ�򣬻����һ���ͷ�
	 *@par 			��
	**/
	static void ReleaseInstance();

public:
	/**
	 *����VoIP����Ƶ����
	 * 
	 *�ú������ڴ���VoIP����Ƶ����
	 *
	 *@param[out] 	strConvID	VoIP���лỰID
	 *@param[in] 	member		���г�Ա
	 *@param[in] 	iType		�������ͣ��ο�CALL_TYPE_E
	 *@param[in] 	localWnd	������Ƶ����
	 *@param[in] 	remoteWnd	Զ����Ƶ����
	 *@return 		�ɹ���0		ʧ�ܣ���0,�ο�������
	 *@attention	���iType��Call_Audio���������У�ʱ����ʹ��localWnd��remoteWnd����
	 *@par 			��
	**/
	virtual int MakeCall(std::string& strConvID, const UCSDKContact& member, int iType,
		const STVideoWindow& localWnd, const STVideoWindow& remoteWnd) = 0;

	/**
	 *����Ӧ��
	 * 
	 *�ú������ں���Ӧ��
	 *
	 *@param[in] 	strConvID	VoIP���лỰID
	 *@param[in] 	iType		�������ͣ��ο�CALL_TYPE_E
	 *@param[in] 	localWnd	������Ƶ����
	 *@param[in] 	remoteWnd	Զ����Ƶ����
	 *@return 		�ɹ���0		ʧ�ܣ���0,�ο�������
	 *@attention	���iType��Call_Audio���������У�ʱ����ʹ��localWnd��remoteWnd����
	 *@par 			��
	**/
	virtual int Accept(const std::string& strConvID, int iType, const STVideoWindow& localWnd, const STVideoWindow& remoteWnd) = 0;

	/**
	 *�ܾ�����
	 * 
	 *�ú������ھܾ�����
	 *
	 *@param[in] 	strConvID	VoIP���лỰID
	 *@param[in] 	iType		�������ͣ��ο�CALL_TYPE_E
	 *@return 		�ɹ���0		ʧ�ܣ���0,�ο�������
	 *@attention	�ܾ���Ƶ�����������Ƕ�ʹ��iType=Call_Audio���������У���Call_Video����Ƶ���У���ʱ����
	 *@par 			��
	**/
	virtual int Reject(const std::string& strConvID, int iType) = 0;

	/**
	 *�Ͽ�ͨ��
	 * 
	 *�ú������ڶϿ�ͨ��
	 *
	 *@param[in] 	strConvID	VoIP���лỰID
	 *@param[in] 	iType		�������ͣ��ο�CALL_TYPE_E
	 *@return 		�ɹ���0		ʧ�ܣ���0,�ο�������
	 *@attention	���iType=Call_Video����Ƶ���У����ر���Ƶ��������Ƶͨ��ת����ͨ��
	 *@par 			��
	**/
	virtual int Hangup(const std::string& strConvID, int iType) = 0;

	/**
	 *ͨ������
	 * 
	 *�ú�������ͨ������
	 *
	 *@param[in] 	strConvID	VoIP���лỰID
	 *@return 		�ɹ���0		ʧ�ܣ���0,�ο�������
	 *@attention	��
	 *@par 			��
	**/
	virtual int Hold(const std::string& strConvID) = 0;

	/**
	 *�ָ�ͨ��
	 * 
	 *�ú������ڻָ�ͨ��
	 *
	 *@param[in] 	strConvID	VoIP���лỰID
	 *@return 		�ɹ���0		ʧ�ܣ���0,�ο�������
	 *@attention	��
	 *@par 			��
	**/
	virtual int Resume(const std::string& strConvID) = 0;

	/**
	 *����ǰת
	 * 
	 *�ú������ں���ǰת
	 *
	 *@param[in] 	strConvID	VoIP���лỰID
	 *@param[in] 	strAccount	ǰת�û�
	 *@return 		�ɹ���0		ʧ�ܣ���0,�ο�������
	 *@attention	��
	 *@par 			��
	**/
	virtual int Forward(const std::string& strConvID, const std::string& strAccount) = 0;

	/**
	 *��ʼ¼��
	 * 
	 *�ú������ڿ�ʼ¼��
	 *
	 *@param[in] 	strConvID	VoIP���лỰID
	 *@param[in] 	strFilePath	¼���ļ������·��
	 *@return 		�ɹ���0		ʧ�ܣ���0,�ο�������
	 *@attention	��
	 *@par 			��
	**/
	virtual int StartRecord(const std::string& strConvID, const std::string& strFilePath) = 0;

	/**
	 *ֹͣ¼��
	 * 
	 *�ú�������ֹͣ¼��
	 *
	 *@param[in] 	strConvID	VoIP���лỰID
	 *@return 		�ɹ���0		ʧ�ܣ���0,�ο�������
	 *@attention	��
	 *@par 			��
	**/
	virtual int StopRecord(const std::string& strConvID) = 0;

	/**
	 *����
	 * 
	 *�ú������ھ���
	 *
	 *@param[in] 	iType		�������ͣ��ο�MUTE_DEVICE_E
	 *@return 		�ɹ���0		ʧ�ܣ���0,�ο�������
	 *@attention	��
	 *@par 			��
	**/
	virtual int Mute(const int iType) = 0;

	/**
	 *ȡ������
	 * 
	 *�ú�������ȡ������
	 *
	 *@param[in] 	iType		ȡ���������ͣ��ο�MUTE_DEVICE_E
	 *@return 		�ɹ���0		ʧ�ܣ���0,�ο�������
	 *@attention	��
	 *@par 			��
	**/
	virtual int UnMute(const int iType) = 0;
};

}
}

#endif