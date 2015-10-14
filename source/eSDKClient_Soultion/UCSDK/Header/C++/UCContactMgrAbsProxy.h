#ifndef _UC_CONTACTMGR_ABS_PROXY_H_
#define _UC_CONTACTMGR_ABS_PROXY_H_

#include "DataType.h"


namespace eSDK {
	namespace UC {


/**
 *��ϵ�˹�����
 * 
 *����������ϵ�˹����ṩ��ϵ����ز���
 *
 *@attention	��
 *@par			��
**/
class UCSDK_API UCContactMgrAbsProxy
{
protected:
	UCContactMgrAbsProxy();
	virtual ~UCContactMgrAbsProxy();

public:
	/**
	 *��ȡ��ϵ�˹����൥ʵ��
	 * 
	 *�ú������ڻ�ȡ��ϵ�˹����൥ʵ��
	 *
	 *@return		�ɹ�����ϵ�˹����൥ʵ��ָ�룬 ʧ�ܣ�NULL
	 *@attention	��
	 *@par			��
	**/
	static UCContactMgrAbsProxy* GetInstance();

	/**
	 *�ͷ���ϵ�˹�����ʵ��
	 * 
	 *�ú��������ͷ���ϵ�˹�����ʵ��
	 *
	 *@attention	�ڵ���UCSDKAbsProxy::ReleaseInstance()ʱ�򣬻����һ���ͷ�
	 *@par			��
	**/
	static void ReleaseInstance();

public:
	/**
	 *��ȡ������ϵ���б�
	 * 
	 *�ú������ڻ�ȡ������ϵ���б�
	 *
	 *@param[out]	memberList
	 *@return		�ɹ���0		ʧ�ܣ���0,�ο�������
	 *@attention	��
	 *@par			��
	**/
	virtual int GetAllContactlist(UCSDKContactList& memberList) = 0;

	/**
	 *ͨ���˺Ż�ȡ��ϵ��
	 * 
	 *�ú�������ͨ���˺Ż�ȡ��ϵ��
	 *
	 *@param[out]	member
	 *@param[in]	strAccount
	 *@return		�ɹ���0		ʧ�ܣ���0,�ο�������
	 *@attention	�˷���ֻ�ܻ�ȡ�����Ѿ���ӵ���ϵ�ˣ���ȡ����ϵ����ID
	 *@par			��
	**/
	virtual int GetContactByAccount(UCSDKContact& member, const std::string& strAccount) = 0;

	/**
	 *ͨ��ID��ȡ��ϵ��
	 * 
	 *�ú�������ͨ��ID��ȡ��ϵ��
	 *
	 *@param[out]	member
	 *@param[in]	strID
	 *@return		�ɹ���0		ʧ�ܣ���0,�ο�������
	 *@attention	�˷���ֻ�ܻ�ȡ�����Ѿ���ӵ���ϵ��
	 *@par			��
	**/
	virtual int GetContactById(UCSDKContact& member, const std::string& strID) = 0;

	/**
	 *ͨ���绰�����ȡ��ϵ��
	 * 
	 *�ú�������ͨ���绰�����ȡ��ϵ��
	 *
	 *@param[out]	member
	 *@param[in]	strPhoneNum
	 *@return		�ɹ���0		ʧ�ܣ���0,�ο�������
	 *@attention	�˷���ֻ�ܻ�ȡ�����Ѿ���ӵ���ϵ��
	 *@par			��
	**/
	virtual int GetContactByPhoneNum(UCSDKContact& member, const std::string& strPhoneNum) = 0;

	/**
	 *ͨ��uri��ȡ��ϵ��
	 * 
	 *�ú�������ͨ��uri��ȡ��ϵ��
	 *
	 *@param[out]	member
	 *@param[in]	strPhoneNum
	 *@return		�ɹ���0		ʧ�ܣ���0,�ο�������
	 *@attention	�˷���ֻ�ܻ�ȡ�����Ѿ���ӵ���ϵ�ˣ���ȡ����ϵ����ID
	 *@par			��
	**/
	virtual int GetContactByUri(UCSDKContact& member, const std::string& strUri) = 0;

	/**
	 *�鿴�Ƿ񱾵��Ѿ����ڴ���ϵ��
	 * 
	 *�ú������ڲ鿴�Ƿ񱾵��Ѿ����ڴ���ϵ��
	 *
	 *@param[in]	strUri
	 *@return		�ɹ���true	ʧ�ܣ�false
	 *@attention	��
	 *@par			��
	**/
	virtual bool HasContact(const std::string& strUri) = 0;

	/**
	 *ͨ��accountˢ����ϵ��
	 * 
	 *�ú�������ͨ��accountˢ����ϵ��
	 *
	 *@param[in]	strAccount
	 *@param[out]	member
	 *@return		�ɹ���0		ʧ�ܣ���0,�ο�������
	 *@attention	��
	 *@par			��
	**/
	virtual int RefreshContactByAccount(const std::string& strAccount, UCSDKContact& member) = 0;

	/**
	 *ͨ��IDˢ����ϵ��
	 * 
	 *�ú�������ͨ��IDˢ����ϵ��
	 *
	 *@param[in]	strID
	 *@param[out]	member
	 *@return		�ɹ���0		ʧ�ܣ���0,�ο�������
	 *@attention	��
	 *@par			��
	**/
	virtual int RefreshContactById(const std::string& strID, UCSDKContact& member) = 0;

	/**
	 *ͨ��Uriˢ����ϵ��
	 * 
	 *�ú�������ͨ��Uriˢ����ϵ��
	 *
	 *@param[in]	strUri
	 *@param[out]	member
	 *@return		�ɹ���0		ʧ�ܣ���0,�ο�������
	 *@attention	��
	 *@par			��
	**/
	virtual int RefreshContactByUri(const std::string& strUri, UCSDKContact& member) = 0;

	/**
	 *ɾ���ض�ID����ϵ��
	 * 
	 *�ú�������ɾ���ض�ID����ϵ��
	 *
	 *@param[in]	strID
	 *@return		�ɹ���0		ʧ�ܣ���0,�ο�������
	 *@attention	��
	 *@par			��
	**/
	virtual int RemoveContactById(const std::string& strID) = 0;

	/**
	 *����ҵͨѶ¼�������ϵ��
	 * 
	 *�ú������ڴ���ҵͨѶ¼�������ϵ��
	 *
	 *@param[out]	memberList		���ص���ϵ���б�
	 *@param[in]	condition		��ѯ�������磺��ϵ��account����account�ؼ���
	 *@param[in]	deptid			��ѯ���ŵ�ID����Ĭ���ÿ�Ϊ����
	 *@param[in]	querysubdept	�Ƿ���Ҫ���Ӳ��Ų�ѯ
	 *@param[in]	offset			��ѯ��㣬һ������Ϊ0
	 *@param[in]	count			ÿ�β�ѯ���ص�������
	 *@param[in]	ordertype		��ѯ���ͣ�һ������Ϊ0
	 *@param[out]	recamount		��ѯ�������
	 *@return		�ɹ���0		ʧ�ܣ���0,�ο�������
	 *@attention	��
	 *@par			��
	**/
	virtual int SearchContact(UCSDKContactList& memberList, 
		const std::string& condition, const std::string& deptid,
		bool querysubdept, int offset, int count, int ordertype, int& recamount) = 0;

public:
	/**
	 *�жϵ�ǰ��ϵ����Ϣ�ܷ��޸�
	 * 
	 *�ú��������жϵ�ǰ��ϵ����Ϣ�ܷ��޸�
	 *
	 *@param[in]	member
	 *@return		�ɹ���true	ʧ�ܣ�false
	 *@attention	��
	 *@par			��
	**/
	virtual bool Modify(const UCSDKContact& member) = 0;

	/**
	 *��ȡ�û�����ͷ��·��
	 * 
	 *�ú������ڻ�ȡ�û�����ͷ��·��
	 *
	 *@param[in]	member
	 *@param[in]	grey
	 *@return		�ɹ���ͷ��·��	ʧ�ܣ����ַ���
	 *@attention	���ʧ�ܣ����member��ȷ��member.uri_
	 *@par			��
	**/
	virtual std::string GetHeadImagePath(const UCSDKContact& member, bool grey = false) = 0;

	/**
	 *��һ��Ⱥ���Ƶ�����һ��Ⱥ��
	 * 
	 *�ú������ڴ�һ��Ⱥ���Ƶ�����һ��Ⱥ��
	 *
	 *@param[in]	member
	 *@param[in]	_src
	 *@param[in]	_target
	 *@return		�ɹ���true	ʧ�ܣ�false
	 *@attention	���ʧ�ܣ����member��ȷ��member.uri_
	 *@par			��
	**/
	virtual bool MoveToGroup(const UCSDKContact& member, const UCSDKGroup& _src, const UCSDKGroup& _target) = 0;

	/**
	 *��ӵ�Ⱥ��
	 * 
	 *�ú���������ӵ�Ⱥ��
	 *
	 *@param[in]	member
	 *@param[in]	_target
	 *@return		�ɹ���true	ʧ�ܣ�false
	 *@attention	���ʧ�ܣ����member��ȷ��member.uri_
	 *@par			��
	**/
	virtual bool AddToGroup(const UCSDKContact& member, const UCSDKGroup& _target) = 0;

	/**
	 *��Ⱥ�����Ƴ�
	 * 
	 *�ú������ڴ�Ⱥ�����Ƴ�
	 *
	 *@param[in]	member
	 *@param[in]	_target
	 *@return		�ɹ���true	ʧ�ܣ�false
	 *@attention	���ʧ�ܣ����member��ȷ��member.uri_
	 *@par			��
	**/
	virtual bool RemoveFromGroup(const UCSDKContact& member, const UCSDKGroup& _target) = 0;

	/**
	 *�ж��ܷ���Ự
	 * 
	 *�ú��������ж��ܷ���Ự
	 *
	 *@param[in]	member
	 *@param[in]	_type
	 *@return		�ɹ���true	ʧ�ܣ�false
	 *@attention	��
	 *@par			��
	**/
	virtual bool CanStartSession(const UCSDKContact& member, SESSION_TYPE_E _type) = 0;

	/**
	 *�ж��ܷ�����ĳ��Ⱥ��
	 * 
	 *�ú��������ж��ܷ�����ĳ��Ⱥ��
	 *
	 *@param[in]	member
	 *@param[in]	_src
	 *@param[in]	_target
	 *@return		�ɹ���true	ʧ�ܣ�false
	 *@attention	��
	 *@par			��
	**/
	virtual bool CanMoveToGroup(const UCSDKContact& member, const UCSDKGroup& _src, const UCSDKGroup& _target) = 0;

	/**
	 *��ȡ���м����Ⱥ��
	 * 
	 *�ú������ڻ�ȡ���м����Ⱥ��
	 *
	 *@param[in]	member
	 *@param[out]	_groups
	 *@return		�ɹ���true	ʧ�ܣ�false
	 *@attention	���ʧ�ܣ����member��ȷ��member.uri_
	 *@par			��
	**/
	virtual int GetCustomGroups(const UCSDKContact& member, UCSDKCustomGroupList& _groups) = 0;

	/**
	 *�Ƿ�����ղ�
	 * 
	 *�ú��������Ƿ�����ղ�
	 *
	 *@param[in]	member
	 *@return		�ɹ���true	ʧ�ܣ�false
	 *@attention	��
	 *@par			��
	**/
	virtual bool IsFavourite(const UCSDKContact& member) = 0;
};

}
}

#endif