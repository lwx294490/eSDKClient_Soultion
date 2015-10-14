#ifndef _UC_CONTACTMGR_HEADER_
#define _UC_CONTACTMGR_HEADER_

#include "DataDef.h"


#ifdef __cplusplus
extern "C"
{
#endif

	/**
	 *��ȡ������ϵ���б�
	 * 
	 *�ú������ڻ�ȡ������ϵ���б�
	 *
	 *@param[in]	iFrom		��ʼindex
	 *@param[in]	iTo			����index	��Χ����[iFrom, iTo]
	 *@param[out]	memberList
	 *@return		�ɹ���0		ʧ�ܣ���0,�ο�������
	 *@attention	ȷ��iFrom��iTo��Ч����memberList�ڴ汣��һ��
	 *@par			��
	**/
	UCSDK_API int UCSDK_CALL GetAllContactlist(int iFrom, int iTo, UCContactList* memberList);

	/**
	 *ͨ���˺Ż�ȡ��ϵ��
	 * 
	 *�ú�������ͨ���˺Ż�ȡ��ϵ��
	 *
	 *@param[in]	pAcc
	 *@param[out]	member
	 *@return		�ɹ���0		ʧ�ܣ���0,�ο�������
	 *@attention	�˷���ֻ�ܻ�ȡ�����Ѿ���ӵ���ϵ�ˣ���ȡ����ϵ����ID
	 *@par			��
	**/
	UCSDK_API int UCSDK_CALL GetContactByAccount(const char* pAcc, UCContact* member);

	/**
	 *ͨ��ID��ȡ��ϵ��
	 * 
	 *�ú�������ͨ��ID��ȡ��ϵ��
	 *
	 *@param[in]	pId
	 *@param[out]	member	 
	 *@return		�ɹ���0		ʧ�ܣ���0,�ο�������
	 *@attention	�˷���ֻ�ܻ�ȡ�����Ѿ���ӵ���ϵ��
	 *@par			��
	**/
	UCSDK_API int UCSDK_CALL GetContactById(const char* pId, UCContact* member);

	/**
	 *ͨ���绰�����ȡ��ϵ��
	 * 
	 *�ú�������ͨ���绰�����ȡ��ϵ��
	 *
	 *@param[in]	pPhoneNum
	 *@param[out]	member
	 *@return		�ɹ���0		ʧ�ܣ���0,�ο�������
	 *@attention	�˷���ֻ�ܻ�ȡ�����Ѿ���ӵ���ϵ��
	 *@par			��
	**/
	UCSDK_API int UCSDK_CALL GetContactByPhoneNum(const char* pPhoneNum, UCContact* member);

	/**
	 *ͨ��uri��ȡ��ϵ��
	 * 
	 *�ú�������ͨ��uri��ȡ��ϵ��
	 *
	 *@param[in]	pUri
	 *@param[out]	member
	 *@return		�ɹ���0		ʧ�ܣ���0,�ο�������
	 *@attention	�˷���ֻ�ܻ�ȡ�����Ѿ���ӵ���ϵ�ˣ���ȡ����ϵ����ID
	 *@par			��
	**/
	UCSDK_API int UCSDK_CALL GetContactByUri(const char* pUri, UCContact* member);

	/**
	 *�鿴�Ƿ񱾵��Ѿ����ڴ���ϵ��
	 * 
	 *�ú������ڲ鿴�Ƿ񱾵��Ѿ����ڴ���ϵ��
	 *
	 *@param[in]	pUri
	 *@return		�ɹ���0	ʧ�ܣ�1
	 *@attention	��
	 *@par			��
	**/
	UCSDK_API int UCSDK_CALL HasContact(const char* pUri);

	/**
	 *ͨ��accountˢ����ϵ��
	 * 
	 *�ú�������ͨ��accountˢ����ϵ��
	 *
	 *@param[in]	pAcc
	 *@param[out]	member
	 *@return		�ɹ���0		ʧ�ܣ���0,�ο�������
	 *@attention	��
	 *@par			��
	**/
	UCSDK_API int UCSDK_CALL RefreshContactByAccount(const char* pAcc, UCContact* member);

	/**
	 *ͨ��IDˢ����ϵ��
	 * 
	 *�ú�������ͨ��IDˢ����ϵ��
	 *
	 *@param[in]	pId
	 *@param[out]	member
	 *@return		�ɹ���0		ʧ�ܣ���0,�ο�������
	 *@attention	��
	 *@par			��
	**/
	UCSDK_API int UCSDK_CALL RefreshContactById(const char* pId, UCContact* member);

	/**
	 *ͨ��Uriˢ����ϵ��
	 * 
	 *�ú�������ͨ��Uriˢ����ϵ��
	 *
	 *@param[in]	pUri
	 *@param[out]	member
	 *@return		�ɹ���0		ʧ�ܣ���0,�ο�������
	 *@attention	��
	 *@par			��
	**/
	UCSDK_API int UCSDK_CALL RefreshContactByUri(const char* pUri, UCContact* member);

	/**
	 *ɾ���ض�ID����ϵ��
	 * 
	 *�ú�������ɾ���ض�ID����ϵ��
	 *
	 *@param[in]	pId
	 *@return		�ɹ���0		ʧ�ܣ���0,�ο�������
	 *@attention	��
	 *@par			��
	**/
	UCSDK_API int UCSDK_CALL RemoveContactById(const char* pId);

	/**
	 *����ҵͨѶ¼�������ϵ��
	 * 
	 *�ú������ڴ���ҵͨѶ¼�������ϵ��
	 *
	 *@param[in]	condition		��ѯ�������磺��ϵ��account����account�ؼ���
	 *@param[in]	deptid			��ѯ���ŵ�ID����Ĭ���ÿ�Ϊ����
	 *@param[in]	querysubdept	�Ƿ���Ҫ���Ӳ��Ų�ѯ
	 *@param[in]	offset			��ѯ��㣬һ������Ϊ0
	 *@param[in]	count			ÿ�β�ѯ���ص�������
	 *@param[in]	ordertype		��ѯ���ͣ�һ������Ϊ0
	 *@param[out]	recamount		��ѯ�������
	 *@param[out]	memberList		���ص���ϵ���б�
	 *@return		�ɹ���0		ʧ�ܣ���0,�ο�������
	 *@attention	ȷ��offset��count��memberList�ڴ汣��һ��
	 *@par			��
	**/
	UCSDK_API int UCSDK_CALL SearchContact(const char* condition, const char* deptid,
		int querysubdept, int offset, int count, int ordertype, 
		int* recamount, UCContactList* memberList);

	/**
	 *�жϵ�ǰ��ϵ����Ϣ�ܷ��޸�
	 * 
	 *�ú��������жϵ�ǰ��ϵ����Ϣ�ܷ��޸�
	 *
	 *@param[in]	member
	 *@return		�ɹ���0	ʧ�ܣ�1
	 *@attention	��
	 *@par			��
	**/
	UCSDK_API int UCSDK_CALL Modify(const UCContact* member);

	/**
	 *��ȡ�û�����ͷ��·��
	 * 
	 *�ú������ڻ�ȡ�û�����ͷ��·��
	 *
	 *@param[in]	member
	 *@param[out]	path
	 *@return		�ɹ���0		ʧ�ܣ���0,�ο�������
	 *@attention	���ʧ�ܣ����member��ȷ��member.uri_
	 *@par			��
	**/
	UCSDK_API int UCSDK_CALL GetHeadImagePath(const UCContact* member, char path[IMAGE_LENGTH]);

	/**
	 *��һ��Ⱥ���Ƶ�����һ��Ⱥ��
	 * 
	 *�ú������ڴ�һ��Ⱥ���Ƶ�����һ��Ⱥ��
	 *
	 *@param[in]	member
	 *@param[in]	_src
	 *@param[in]	_target
	 *@return		�ɹ���0		ʧ�ܣ���0,�ο�������
	 *@attention	���ʧ�ܣ����member��ȷ��member.uri_
	 *@par			��
	**/
	UCSDK_API int UCSDK_CALL MoveToGroup(const UCContact* member, const UCGroup* _src, const UCGroup* _target);

	/**
	 *��ӵ�Ⱥ��
	 * 
	 *�ú���������ӵ�Ⱥ��
	 *
	 *@param[in]	member
	 *@param[in]	_target
	 *@return		�ɹ���0		ʧ�ܣ���0,�ο�������
	 *@attention	���ʧ�ܣ����member��ȷ��member.uri_
	 *@par			��
	**/
	UCSDK_API int UCSDK_CALL AddToGroup(const UCContact* member, const UCGroup* _target);

	/**
	 *��Ⱥ�����Ƴ�
	 * 
	 *�ú������ڴ�Ⱥ�����Ƴ�
	 *
	 *@param[in]	member
	 *@param[in]	_target
	 *@return		�ɹ���0		ʧ�ܣ���0,�ο�������
	 *@attention	���ʧ�ܣ����member��ȷ��member.uri_
	 *@par			��
	**/
	UCSDK_API int UCSDK_CALL RemoveFromGroup(const UCContact* member, const UCGroup* _target);

	/**
	 *�ж��ܷ���Ự
	 * 
	 *�ú��������ж��ܷ���Ự
	 *
	 *@param[in]	member
	 *@param[in]	_type
	 *@return		�ɹ���0	ʧ�ܣ�1
	 *@attention	��
	 *@par			��
	**/
	UCSDK_API int UCSDK_CALL CanStartSession(const UCContact* member, int _type);

	/**
	 *�ж��ܷ�����ĳ��Ⱥ��
	 * 
	 *�ú��������ж��ܷ�����ĳ��Ⱥ��
	 *
	 *@param[in]	member
	 *@param[in]	_src
	 *@param[in]	_target
	 *@return		�ɹ���0	ʧ�ܣ�1
	 *@attention	��
	 *@par			��
	**/
	UCSDK_API int UCSDK_CALL CanMoveToGroup(const UCContact* member, const UCGroup* _src, const UCGroup* _target);

	/**
	 *��ȡ���м����Ⱥ��
	 * 
	 *�ú������ڻ�ȡ���м����Ⱥ��
	 *
	 *@param[in]	member
	 *@param[in]	iFrom		��ʼindex
	 *@param[in]	iTo			����index	��Χ����[iFrom, iTo]
	 *@param[out]	_groups
	 *@return		�ɹ���0		ʧ�ܣ���0,�ο�������
	 *@attention	���ʧ�ܣ����member��ȷ��member.uri_��ȷ��iFrom��iTo��Ч����_groups�ڴ汣��һ��
	 *@par			��
	**/
	UCSDK_API int UCSDK_CALL GetCustomGroups(const UCContact* member, int iFrom, int iTo, UCCustomGroupList* _groups);

	/**
	 *�Ƿ�����ղ�
	 * 
	 *�ú��������Ƿ�����ղ�
	 *
	 *@param[in]	member
	 *@return		�ɹ���0	ʧ�ܣ�1
	 *@attention	��
	 *@par			��
	**/
	UCSDK_API int UCSDK_CALL IsFavourite(const UCContact* member);


#ifdef __cplusplus
}
#endif 


#endif