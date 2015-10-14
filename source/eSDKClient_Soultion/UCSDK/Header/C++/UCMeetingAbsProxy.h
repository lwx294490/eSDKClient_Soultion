#ifndef _UC_MEETING_ABS_PROXY_H_
#define _UC_MEETING_ABS_PROXY_H_

#include "DataType.h"


namespace eSDK {
	namespace UC {


/**
 *���������
 * 
 *�������ڻ������
 *
 *@attention	��
 *@par			��
**/
class UCSDK_API UCMeetingAbsProxy
{
protected:
	UCMeetingAbsProxy();
	virtual ~UCMeetingAbsProxy();

public:
	/**
	 *��ȡ��������൥ʵ��
	 * 
	 *�ú������ڻ�ȡ��������൥ʵ��
	 *
	 *@return 		�ɹ�����������൥ʵ��ָ�룬 ʧ�ܣ�NULL
	 *@attention	��
	 *@par 			��
	**/
	static UCMeetingAbsProxy* GetInstance();

	/**
	 *�ͷŻ�������൥ʵ��
	 * 
	 *�ú��������ͷŻ�������൥ʵ��
	 *
	 *@attention	�ڵ���UCSDKAbsProxy::ReleaseInstance()ʱ�򣬻����һ���ͷ�
	 *@par 			��
	**/
	static void ReleaseInstance();

public:
	/**
	 *����������ʱȺ��
	 * 
	 *�ú������ڴ���������ʱȺ�飬�ɷ��ͼ�ʱ��Ϣ�Ļ���
	 *
	 *@param[in] 	memberlist	����Ա�б�
	 *@param[out] 	convId		����ỰconversationID
	 *@return 		�ɹ���0		ʧ�ܣ���0,�ο�������
	 *@attention	������������ʱ����MakeMeetingGroup()��Ȼ��StartMeeting()
	 *@par 			��
	**/
	virtual int MakeMeetingGroup(const UCSDKContactList& memberlist, std::string& convId) = 0;

	/**
	 *��ʼ��������
	 * 
	 *�ú������ڿ�ʼ��������
	 *
	 *@param[in] 	convId		����ỰconversationID
	 *@return 		�ɹ���0		ʧ�ܣ���0,�ο�������
	 *@attention	��ʹ��MakeMeetingGroup��ȡconvId
	 *@par 			��
	**/
	virtual int StartMeeting(const std::string& convId) = 0;

	/**
	 *���ջ�������
	 * 
	 *�ú������ڽ��ջ�������
	 *
	 *@param[in] 	convId
	 *@return 		�ɹ���0		ʧ�ܣ���0,�ο�������
	 *@attention	Ҳ����ʹ��UCVoIPAbsProxy::Accept();
	 *@par 			��
	**/
	virtual int AcceptMeeting(const std::string& convId) = 0;

	/**
	 *��������Ա
	 * 
	 *�ú���������������Ա
	 *
	 *@param[in] 	member
	 *@param[in] 	convId
	 *@return 		�ɹ���0		ʧ�ܣ���0,�ο�������
	 *@attention	��
	 *@par 			��
	**/
	virtual int AddParticipant(const UCSDKContact& member, const std::string& convId) = 0;

	/**
	 *��������Ա
	 * 
	 *�ú���������������Ա
	 *
	 *@param[in] 	member
	 *@param[in] 	convId
	 *@return 		�ɹ���0		ʧ�ܣ���0,�ο�������
	 *@attention	��
	 *@par 			��
	**/
	virtual int ConnectParticipant(const UCSDKContact& member, const std::string& convId) = 0;

	/**
	 *ɾ������Ա
	 * 
	 *�ú�������ɾ������Ա
	 *
	 *@param[in] 	member
	 *@param[in] 	convId
	 *@return 		�ɹ���0		ʧ�ܣ���0,�ο�������
	 *@attention	��
	 *@par 			��
	**/
	virtual int RemoveParticipant(const UCSDKContact& member, const std::string& convId) = 0;

	/**
	 *ǿ������Ա�ǳ�
	 * 
	 *�ú�������ǿ������Ա�ǳ�
	 *
	 *@param[in] 	member
	 *@param[in] 	convId
	 *@return 		�ɹ���0		ʧ�ܣ���0,�ο�������
	 *@attention	��
	 *@par 			��
	**/
	virtual int KickParticipant(const UCSDKContact& member, const std::string& convId) = 0;

	/**
	 *������Ա����
	 * 
	 *�ú������ڶ�����Ա����
	 *
	 *@param[in] 	member
	 *@param[in] 	convId
	 *@return 		�ɹ���0		ʧ�ܣ���0,�ο�������
	 *@attention	��
	 *@par 			��
	**/
	virtual int Mute(const UCSDKContact& member, const std::string& convId) = 0;

	/**
	 *������Աȡ������
	 * 
	 *�ú������ڶ�����Աȡ������
	 *
	 *@param[in] 	member
	 *@param[in] 	convId
	 *@return 		�ɹ���0		ʧ�ܣ���0,�ο�������
	 *@attention	��
	 *@par 			��
	**/
	virtual int UnMute(const UCSDKContact& member, const std::string& convId) = 0;

	/**
	 *��ȡԤԼ�����б�
	 * 
	 *�ú������ڻ�ȡԤԼ�����б�
	 *
	 *@param[in] 	bookConfList
	 *@return 		�ɹ���0		ʧ�ܣ���0,�ο�������
	 *@attention	��
	 *@par 			��
	**/
	virtual int GetBookConfList(UCSDKBookConfList& bookConfList) = 0;

	/**
	 *����ԤԼ����
	 * 
	 *�ú������ڼ���ԤԼ����
	 *
	 *@param[out] 	convId
	 *@param[in] 	meetingInfo
	 *@return 		�ɹ���0		ʧ�ܣ���0,�ο�������
	 *@attention	��
	 *@par 			��
	**/
	virtual int JoinMeeting(std::string& convId, const UCSDKBookConfInfo& meetingInfo) = 0;

	/**
	 *�뿪����
	 * 
	 *�ú��������뿪����
	 *
	 *@param[in] 	convId
	 *@return 		�ɹ���0		ʧ�ܣ���0,�ο�������
	 *@attention	��
	 *@par 			��
	**/
	virtual int LeaveMeeting(const std::string& convId) = 0;
};

}
}

#endif