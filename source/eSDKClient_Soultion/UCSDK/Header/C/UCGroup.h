#ifndef _UC_GROUP_HEADER_
#define _UC_GROUP_HEADER_

#include "DataDef.h"


#ifdef __cplusplus
extern "C"
{
#endif

	/**
	 *���ӹ̶�Ⱥ��
	 * 
	 *�ú����������ӹ̶�Ⱥ��
	 *
	 *@param[in/out]group
	 *@return		�ɹ���0		ʧ�ܣ���0,�ο�������
	 *@attention	��
	 *@par			��
	**/
	UCSDK_API int UCSDK_CALL AddFixedGroup(UCFixedGroup* group);

	/**
	 *ͨ��ID��ȡ�̶�Ⱥ��
	 * 
	 *�ú�������ͨ��ID��ȡ�̶�Ⱥ��
	 *
	 *@param[in]	pGId
	 *@param[out]	group
	 *@return		�ɹ���0		ʧ�ܣ���0,�ο�������
	 *@attention	��
	 *@par			��
	**/
	UCSDK_API int UCSDK_CALL GetFixedGroupByID(const char* pGId, UCFixedGroup* group);

	/**
	 *ͨ��Uri��ȡ�̶�Ⱥ��
	 * 
	 *�ú�������ͨ��Uri��ȡ�̶�Ⱥ��
	 *
	 *@param[in]	pGUri
	 *@param[out]	group
	 *@return		�ɹ���0		ʧ�ܣ���0,�ο�������
	 *@attention	��
	 *@par			��
	**/
	UCSDK_API int UCSDK_CALL GetFixedGroupByUri(const char* pGUri, UCFixedGroup* group);

	/**
	 *ɾ���̶�Ⱥ��
	 * 
	 *�ú�������ɾ���̶�Ⱥ��
	 *
	 *@param[in]	group
	 *@return		�ɹ���0		ʧ�ܣ���0,�ο�������
	 *@attention	��
	 *@par			��
	**/
	UCSDK_API int UCSDK_CALL RemoveFixedGroup(const UCFixedGroup* group);

	/**
	 *ˢ�¹̶�Ⱥ���б�
	 * 
	 *�ú�������ˢ�¹̶�Ⱥ���б�
	 *
	 *@param[in]	iFrom		��ʼindex
	 *@param[in]	iTo			����index	��Χ����[iFrom, iTo]
	 *@param[out]	groupList
	 *@return		�ɹ���0		ʧ�ܣ���0,�ο�������
	 *@attention	ȷ��iFrom��iTo��Ч����groupList�ڴ汣��һ��
	 *@par			��
	**/
	UCSDK_API int UCSDK_CALL RefreshFixedGrouplist(int iFrom, int iTo, UCFixedGroupList* groupList);

	/**
	 *��ȡ�̶�Ⱥ���б�
	 * 
	 *�ú������ڻ�ȡ�̶�Ⱥ���б�
	 *
	 *@param[in]	iFrom		��ʼindex
	 *@param[in]	iTo			����index	��Χ����[iFrom, iTo]
	 *@param[out]	groupList
	 *@return		�ɹ���0		ʧ�ܣ���0,�ο�������
	 *@attention	ȷ��iFrom��iTo��Ч����groupList�ڴ汣��һ��
	 *@par			��
	**/
	UCSDK_API int UCSDK_CALL GetFixedGrouplist(int iFrom, int iTo, UCFixedGroupList* groupList);

	/**
	 *����Ⱥ��
	 * 
	 *�ú������ڲ���Ⱥ��
	 *
	 *@param[in]	groupNo		Ⱥ���
	 *@param[in]	groupName	Ⱥ����
	 *@param[in]	offset		��ѯ��㣬һ������Ϊ1
	 *@param[in]	count		ÿ�β�ѯ���ص�������
	 *@param[out]	groupList	���ҷ��ص�Ⱥ���б�
	 *@return		�ɹ���0		ʧ�ܣ���0,�ο�������
	 *@attention	ȷ��offset��count�ڴ��groupList����һ�£����ע��offset��1��ʼ��groupList�±��0��ʼ
	 *@par			��
	**/
	UCSDK_API int UCSDK_CALL SearchFixedGroup(const char* groupNo, const char* groupName, int offset, int count,
												UCFixedGroupList* groupList);

	/**
	 *������ϵ��˽��Ⱥ��
	 * 
	 *�ú�������������ϵ��˽��Ⱥ��
	 *
	 *@param[in/out]group
	 *@return		�ɹ���0		ʧ�ܣ���0,�ο�������
	 *@attention	��
	 *@par			��
	**/
	UCSDK_API int UCSDK_CALL AddCustomGroup(UCCustomGroup* group);

	/**
	 *�����ղ�Ⱥ��
	 * 
	 *�ú������������ղ�Ⱥ��
	 *
	 *@param[in/out]group
	 *@return		�ɹ���0		ʧ�ܣ���0,�ο�������
	 *@attention	��
	 *@par			��
	**/
	UCSDK_API int UCSDK_CALL AddFavoriteGroup(UCFavoriteGroup* group);

	/**
	 *ͨ��ID����˽��Ⱥ��
	 * 
	 *�ú�������ͨ��ID����˽��Ⱥ��
	 *
	 *@param[in]	pGId
	 *@param[out]	group
	 *@return		�ɹ���0		ʧ�ܣ���0,�ο�������
	 *@attention	��
	 *@par			��
	**/
	UCSDK_API int UCSDK_CALL GetCustomGroupById(const char* pGId, UCCustomGroup* group);

	/**
	 *��ȡ˽���Զ���Ⱥ����б�
	 * 
	 *�ú������ڻ�ȡ˽���Զ���Ⱥ����б�
	 *
	 *@param[in]	iFrom		��ʼindex
	 *@param[in]	iTo			����index	��Χ����[iFrom, iTo]
	 *@param[out]	groupList
	 *@return		�ɹ���0		ʧ�ܣ���0,�ο�������
	 *@attention	ȷ��iFrom��iTo��Ч����groupList�ڴ汣��һ��
	 *@par			��
	**/
	UCSDK_API int UCSDK_CALL GetCustomGrouplist(int iFrom, int iTo, UCCustomGroupList* groupList);

	/**
	 *ɾ����ϵ��˽��Ⱥ��
	 * 
	 *�ú�������ɾ����ϵ��˽��Ⱥ��
	 *
	 *@param[in]	group
	 *@return		�ɹ���0		ʧ�ܣ���0,�ο�������
	 *@attention	��
	 *@par			��
	**/
	UCSDK_API int UCSDK_CALL RemoveCustomGroup(const UCCustomGroup* group);

	/**
	 *ɾ���ղ�Ⱥ��
	 * 
	 *�ú�������ɾ���ղ�Ⱥ��
	 *
	 *@param[in]	group
	 *@return		�ɹ���0		ʧ�ܣ���0,�ο�������
	 *@attention	��
	 *@par			��
	**/
	UCSDK_API int UCSDK_CALL RemoveFavoriteGroup(const UCFavoriteGroup* group);

	/**
	 *����ղ�Ⱥ����ϵ��
	 * 
	 *�ú�����������ղ�Ⱥ����ϵ��
	 *
	 *@param[in]	group
	 *@param[in]	_contact
	 *@return		�ɹ���0		ʧ�ܣ���0,�ο�������
	 *@attention	��
	 *@par			��
	**/
	UCSDK_API int UCSDK_CALL AddContactToFavoriteGroup(const UCFavoriteGroup* group, UCContact* _contact);

	/**
	 *ɾ���ղ�Ⱥ����ϵ��
	 * 
	 *�ú�������ɾ���ղ�Ⱥ����ϵ��
	 *
	 *@param[in]	group
	 *@param[in]	_contact
	 *@return		�ɹ���0		ʧ�ܣ���0,�ο�������
	 *@attention	��
	 *@par			��
	**/
	UCSDK_API int UCSDK_CALL RemoveContactFromFavoriteGroup(const UCFavoriteGroup* group, const UCContact* _contact);

	/**
	 *�����ղ�Ⱥ����
	 * 
	 *�ú������ڸ����ղ�Ⱥ����
	 *
	 *@param[in]	group
	 *@param[in]	_name
	 *@return		�ɹ���0		ʧ�ܣ���0,�ο�������
	 *@attention	��
	 *@par			��
	**/
	UCSDK_API int UCSDK_CALL RenameToFavoriteGroup(const UCFavoriteGroup* group, const char* _name);

	/**
	 *��ȡ�ղ�Ⱥ��Ա��Ϣ�б�
	 * 
	 *�ú������ڻ�ȡ�ղ�Ⱥ��Ա��Ϣ�б�
	 *
	 *@param[in]	group
	 *@param[in]	iFrom		��ʼindex
	 *@param[in]	iTo			����index	��Χ����[iFrom, iTo]
	 *@param[out]	_contactlist
	 *@return		�ɹ���0		ʧ�ܣ���0,�ο�������
	 *@attention	ȷ��iFrom��iTo��Ч����_contactlist�ڴ汣��һ��
	 *@par			��
	**/
	UCSDK_API int UCSDK_CALL GetContactlistFromFavoriteGroup(const UCFavoriteGroup* group, int iFrom, int iTo, UCContactList* _contactlist);

	/**
	 *�����ϵ��˽��Ⱥ����ϵ��
	 * 
	 *�ú������������ϵ��˽��Ⱥ����ϵ��
	 *
	 *@param[in]	group
	 *@param[in]	_contact
	 *@return		�ɹ���0		ʧ�ܣ���0,�ο�������
	 *@attention	��
	 *@par			��
	**/
	UCSDK_API int UCSDK_CALL AddContactToCustomGroup(const UCCustomGroup* group, UCContact* _contact);

	/**
	 *ɾ����ϵ��˽��Ⱥ����ϵ��
	 * 
	 *�ú�������ɾ����ϵ��˽��Ⱥ����ϵ��
	 *
	 *@param[in]	group
	 *@param[in]	_contact
	 *@return		�ɹ���0		ʧ�ܣ���0,�ο�������
	 *@attention	��
	 *@par			��
	**/
	UCSDK_API int UCSDK_CALL RemoveContactFromCustomGroup(const UCCustomGroup* group, const UCContact* _contact);

	/**
	 *������ϵ��˽��Ⱥ����
	 * 
	 *�ú������ڸ�����ϵ��˽��Ⱥ����
	 *
	 *@param[in]	group
	 *@param[in]	_name
	 *@return		�ɹ���0		ʧ�ܣ���0,�ο�������
	 *@attention	��
	 *@par			��
	**/
	UCSDK_API int UCSDK_CALL RenameToCustomGroup(const UCCustomGroup* group, const char* _name);

	/**
	 *��ȡ��ϵ��˽��Ⱥ��Ա��Ϣ�б�
	 * 
	 *�ú������ڻ�ȡ��ϵ��˽��Ⱥ��Ա��Ϣ�б�
	 *
	 *@param[in]	group
	 *@param[in]	iFrom		��ʼindex
	 *@param[in]	iTo			����index	��Χ����[iFrom, iTo]
	 *@param[out]	_contactlist
	 *@return		�ɹ���0		ʧ�ܣ���0,�ο�������
	 *@attention	ȷ��iFrom��iTo��Ч����_contactlist�ڴ汣��һ��
	 *@par			��
	**/
	UCSDK_API int UCSDK_CALL GetContactlistFromCustomGroup(const UCCustomGroup* group, int iFrom, int iTo, UCContactList* _contactlist);

	/**
	 *��ϵ��˽��Ⱥ������
	 * 
	 *�ú���������ϵ��˽��Ⱥ������
	 *
	 *@param[in]	group
	 *@return		�ɹ���0		ʧ�ܣ���0,�ο�������
	 *@attention	��
	 *@par			��
	**/
	UCSDK_API int UCSDK_CALL MoveUp(const UCCustomGroup* group);

	/**
	 *��ϵ��˽��Ⱥ������
	 * 
	 *�ú���������ϵ��˽��Ⱥ������
	 *
	 *@param[in]	group
	 *@return		�ɹ���0		ʧ�ܣ���0,�ο�������
	 *@attention	��
	 *@par			��
	**/
	UCSDK_API int UCSDK_CALL MoveDown(const UCCustomGroup* group);

	/**
	 *��ӹ̶�Ⱥ����ϵ��
	 * 
	 *�ú���������ӹ̶�Ⱥ����ϵ��
	 *
	 *@param[in]	group
	 *@param[in]	_contact
	 *@return		�ɹ���0		ʧ�ܣ���0,�ο�������
	 *@attention	1. Ⱥ����������		2. �û��������Ⱥ��
	 *@par			��
	**/
	UCSDK_API int UCSDK_CALL AddContactToFixedGroup(const UCFixedGroup* group, UCContact* _contact);

	/**
	 *ɾ���̶�Ⱥ����ϵ��
	 * 
	 *�ú�������ɾ���̶�Ⱥ����ϵ��
	 *
	 *@param[in]	group
	 *@param[in]	_contact
	 *@return		�ɹ���0		ʧ�ܣ���0,�ο�������
	 *@attention	��
	 *@par			��
	**/
	UCSDK_API int UCSDK_CALL RemoveContactFromFixedGroup(const UCFixedGroup* group, const UCContact* _contact);

	/**
	 *���Ĺ̶�Ⱥ����
	 * 
	 *�ú������ڸ��Ĺ̶�Ⱥ����
	 *
	 *@param[in]	group
	 *@param[in]	_name
	 *@return		�ɹ���0		ʧ�ܣ���0,�ο�������
	 *@attention	��
	 *@par			��
	**/
	UCSDK_API int UCSDK_CALL RenameToFixedGroup(const UCFixedGroup* group, const char* _name);

	/**
	 *��ȡ�̶�Ⱥ��Ա��Ϣ�б�
	 * 
	 *�ú������ڻ�ȡ�̶�Ⱥ��Ա��Ϣ�б�
	 *
	 *@param[in]	group
	 *@param[in]	iFrom		��ʼindex
	 *@param[in]	iTo			����index	��Χ����[iFrom, iTo]
	 *@param[out]	_contactlist
	 *@return		ȷ��iFrom��iTo��Ч����_contactlist�ڴ汣��һ��
	 *@attention	��
	 *@par			��
	**/
	UCSDK_API int UCSDK_CALL GetContactlistFromFixedGroup(const UCFixedGroup* group, int iFrom, int iTo, UCContactList* _contactlist);

	/**
	 *�޸Ĺ̶�Ⱥ�������Ϣ
	 * 
	 *�ú��������޸Ĺ̶�Ⱥ�������Ϣ
	 *
	 *@param[in]	group
	 *@return		�ɹ���0		ʧ�ܣ���0,�ο�������
	 *@attention	��
	 *@par			��
	**/
	UCSDK_API int UCSDK_CALL ChangeGroupInfo(const UCFixedGroup* group);

	/**
	 *�޸Ĺ̶�ȺȺ��(�����ɵ�ǰȺ���޸�)
	 * 
	 *�ú��������޸Ĺ̶�ȺȺ��
	 *
	 *@param[in]	group
	 *@param[in]	_owner
	 *@return		�ɹ���0		ʧ�ܣ���0,�ο�������
	 *@attention	�����ɵ�ǰȺ���޸ģ�_owner����Ϊ����Ⱥ��Ա
	 *@par			��
	**/
	UCSDK_API int UCSDK_CALL ChangeGroupOwner(const UCFixedGroup* group, const UCContact* _owner);

	/**
	 *��������ͬ���̶�Ⱥ���Ա��Ϣ�б�
	 * 
	 *�ú������ڸ�������ͬ���̶�Ⱥ���Ա��Ϣ�б�
	 *
	 *@param[in]	group
	 *@param[in]	iFrom		��ʼindex
	 *@param[in]	iTo			����index	��Χ����[iFrom, iTo]
	 *@param[out]	_contactlist
	 *@return		�ɹ���0		ʧ�ܣ���0,�ο�������
	 *@attention	ȷ��iFrom��iTo��Ч����_contactlist�ڴ汣��һ��
	 *@par			��
	**/
	UCSDK_API int UCSDK_CALL RefreshContactList(const UCFixedGroup* group, int iFrom, int iTo, UCContactList* _contactlist);

	/**
	 *ˢ�¹̶�Ⱥ��
	 * 
	 *�ú�������ˢ�¹̶�Ⱥ��
	 *
	 *@param[in]	group
	 *@param[in]	sync_
	 *@return		�ɹ���0		ʧ�ܣ���0,�ο�������
	 *@attention	��
	 *@par			��
	**/
	UCSDK_API int UCSDK_CALL RefreshGroup(const UCFixedGroup* group);

	/**
	 *���̶ܹ�Ⱥ������
	 * 
	 *�ú������ڽ��̶ܹ�Ⱥ������
	 *
	 *@param[in]	group
	 *@return		�ɹ���0		ʧ�ܣ���0,�ο�������
	 *@attention	��
	 *@par			��
	**/
	UCSDK_API int UCSDK_CALL AcceptInvitation(const UCFixedGroup* group);

	/**
	 *�ܾ��̶�Ⱥ������
	 * 
	 *�ú������ھܾ��̶�Ⱥ������
	 *
	 *@param[in]	group
	 *@return		�ɹ���0		ʧ�ܣ���0,�ο�������
	 *@attention	��
	 *@par			��
	**/
	UCSDK_API int UCSDK_CALL RejectInvitation(const UCFixedGroup* group);

	/**
	 *���ܼ���̶�Ⱥ������
	 * 
	 *�ú������ڽ��ܼ���̶�Ⱥ������
	 *
	 *@param[in]	group
	 *@param[in] 	_contact
	 *@return 		�ɹ���0		ʧ�ܣ���0,�ο�������
	 *@attention	��
	 *@par			��
	**/
	UCSDK_API int UCSDK_CALL AcceptJoinReq(const UCFixedGroup* group, const UCContact* _contact); 

	/**
	 *�ܾ�����̶�Ⱥ������
	 * 
	 *�ú������ھܾ�����̶�Ⱥ������
	 *
	 *@param[in]	group
	 *@param[in] 	_contact
	 *@return 		�ɹ���0		ʧ�ܣ���0,�ο�������
	 *@attention	��
	 *@par			��
	**/
	UCSDK_API int UCSDK_CALL RejectJoinReq(const UCFixedGroup* group, const UCContact* _contact);


#ifdef __cplusplus
}
#endif 


#endif