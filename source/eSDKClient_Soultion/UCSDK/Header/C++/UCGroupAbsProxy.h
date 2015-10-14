#ifndef _UC_GROUP_ABS_PROXY_H_
#define _UC_GROUP_ABS_PROXY_H_

#include "DataType.h"


namespace eSDK {
	namespace UC {


/**
 *Ⱥ�������
 * 
 *��������Ⱥ������ṩȺ����ز����������Ⱥ�������ϵ�˷���(CustomGroup)���̶�Ⱥ��(FixedGroup)���ղ�Ⱥ��(FavoriteGroup)
 *
 *@attention	��
 *@par			��
**/
class UCSDK_API UCGroupAbsProxy
{
protected:
	UCGroupAbsProxy();
	virtual ~UCGroupAbsProxy();

public:
	/**
	 *��ȡȺ������൥ʵ��
	 * 
	 *�ú������ڻ�ȡȺ������൥ʵ��
	 *
	 *@return		�ɹ���Ⱥ������൥ʵ��ָ�룬 ʧ�ܣ�NULL
	 *@attention	��
	 *@par			��
	**/
	static UCGroupAbsProxy* GetInstance();

	/**
	 *�ͷ�Ⱥ������൥ʵ��
	 * 
	 *�ú��������ͷ�Ⱥ������൥ʵ��
	 *
	 *@attention	�ڵ���UCSDKAbsProxy::ReleaseInstance()ʱ�򣬻����һ���ͷ�
	 *@par			��
	**/
	static void ReleaseInstance();

public:
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
	virtual int AddFixedGroup(UCSDKFixedGroup& group) = 0;

	/**
	 *ͨ��ID��ȡ�̶�Ⱥ��
	 * 
	 *�ú�������ͨ��ID��ȡ�̶�Ⱥ��
	 *
	 *@param[out]	group
	 *@param[in]	strGroupID
	 *@return		�ɹ���0		ʧ�ܣ���0,�ο�������
	 *@attention	��
	 *@par			��
	**/
	virtual int GetFixedGroupByID(UCSDKFixedGroup& group, const std::string& strGroupID) = 0;

	/**
	 *ͨ��Uri��ȡ�̶�Ⱥ��
	 * 
	 *�ú�������ͨ��Uri��ȡ�̶�Ⱥ��
	 *
	 *@param[out]	group
	 *@param[in]	strGroupUri
	 *@return		�ɹ���0		ʧ�ܣ���0,�ο�������
	 *@attention	��
	 *@par			��
	**/
	virtual int GetFixedGroupByUri(UCSDKFixedGroup& group, const std::string& strGroupUri) = 0;

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
	virtual int RemoveFixedGroup(const UCSDKFixedGroup& group) = 0;

	/**
	 *ˢ�¹̶�Ⱥ���б�
	 * 
	 *�ú�������ˢ�¹̶�Ⱥ���б�
	 *
	 *@param[out]	groupList
	 *@return		�ɹ���0		ʧ�ܣ���0,�ο�������
	 *@attention	��
	 *@par			��
	**/
	virtual int RefreshFixedGrouplist(UCSDKFixedGroupList& groupList) = 0;

	/**
	 *��ȡ�̶�Ⱥ���б�
	 * 
	 *�ú������ڻ�ȡ�̶�Ⱥ���б�
	 *
	 *@param[out]	groupList
	 *@return		�ɹ���0		ʧ�ܣ���0,�ο�������
	 *@attention	��
	 *@par			��
	**/
	virtual int GetFixedGrouplist(UCSDKFixedGroupList& groupList) = 0;

	/**
	 *����Ⱥ��
	 * 
	 *�ú������ڲ���Ⱥ��
	 *
	 *@param[out]	groupList	���ҷ��ص�Ⱥ���б�
	 *@param[in]	groupNo		Ⱥ���
	 *@param[in]	groupName	Ⱥ����
	 *@param[in]	offset		��ѯ��㣬һ������Ϊ1
	 *@param[in]	count		ÿ�β�ѯ���ص�������
	 *@return		�ɹ���0		ʧ�ܣ���0,�ο�������
	 *@attention	��
	 *@par			��
	**/
	virtual int SearchFixedGroup(UCSDKFixedGroupList& groupList, 
		const std::string& groupNo, const std::string& groupName, int offset, int count) = 0;

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
	virtual int AddCustomGroup(UCSDKCustomGroup& group) = 0;

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
	virtual int AddFavoriteGroup(UCSDKFavoriteGroup& group) = 0;

	/**
	 *ͨ��ID����˽��Ⱥ��
	 * 
	 *�ú�������ͨ��ID����˽��Ⱥ��
	 *
	 *@param[out]	group
	 *@param[in]	strGroupID
	 *@return		�ɹ���0		ʧ�ܣ���0,�ο�������
	 *@attention	��
	 *@par			��
	**/
	virtual int GetCustomGroupById(UCSDKCustomGroup& group, const std::string& strGroupID) = 0;

	/**
	 *��ȡ˽���Զ���Ⱥ����б�
	 * 
	 *�ú������ڻ�ȡ˽���Զ���Ⱥ����б�
	 *
	 *@param[out]	groupList
	 *@return		�ɹ���0		ʧ�ܣ���0,�ο�������
	 *@attention	��
	 *@par			��
	**/
	virtual int GetCustomGrouplist(UCSDKCustomGroupList& groupList) = 0;

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
	virtual int RemoveCustomGroup(const UCSDKCustomGroup& group) = 0;

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
	virtual int RemoveFavoriteGroup(const UCSDKFavoriteGroup& group) = 0;

public:
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
	virtual int AddContact(const UCSDKFavoriteGroup& group, UCSDKContact& _contact) = 0;

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
	virtual int RemoveContact(const UCSDKFavoriteGroup& group, const UCSDKContact& _contact) const = 0;

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
	virtual int Rename(const UCSDKFavoriteGroup& group, const std::string& _name) = 0;

	/**
	 *��ȡ�ղ�Ⱥ��Ա��Ϣ�б�
	 * 
	 *�ú������ڻ�ȡ�ղ�Ⱥ��Ա��Ϣ�б�
	 *
	 *@param[in]	group
	 *@param[out]	_contactlist
	 *@return		�ɹ���0		ʧ�ܣ���0,�ο�������
	 *@attention	��
	 *@par			��
	**/
	virtual int GetContactlist(const UCSDKFavoriteGroup& group, UCSDKContactList& _contactlist) = 0;

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
	virtual int AddContact(const UCSDKCustomGroup& group, UCSDKContact& _contact) = 0;

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
	virtual int RemoveContact(const UCSDKCustomGroup& group, const UCSDKContact& _contact) const = 0;

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
	virtual int Rename(const UCSDKCustomGroup& group, const std::string& _name) = 0;

	/**
	 *��ȡ��ϵ��˽��Ⱥ��Ա��Ϣ�б�
	 * 
	 *�ú������ڻ�ȡ��ϵ��˽��Ⱥ��Ա��Ϣ�б�
	 *
	 *@param[in]	group
	 *@param[out]	_contactlist
	 *@return		�ɹ���0		ʧ�ܣ���0,�ο�������
	 *@attention	��
	 *@par			��
	**/
	virtual int GetContactlist(const UCSDKCustomGroup& group, UCSDKContactList& _contactlist) = 0;

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
	virtual int MoveUp(const UCSDKCustomGroup& group) = 0;

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
	virtual int MoveDown(const UCSDKCustomGroup& group) = 0;

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
	virtual int AddContact(const UCSDKFixedGroup& group, UCSDKContact& _contact) = 0;

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
	virtual int RemoveContact(const UCSDKFixedGroup& group, const UCSDKContact& _contact) const = 0;

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
	virtual int Rename(const UCSDKFixedGroup& group, const std::string& _name) = 0;

	/**
	 *��ȡ�̶�Ⱥ��Ա��Ϣ�б�
	 * 
	 *�ú������ڻ�ȡ�̶�Ⱥ��Ա��Ϣ�б�
	 *
	 *@param[in]	group
	 *@param[out]	_contactlist
	 *@return		�ɹ���0		ʧ�ܣ���0,�ο�������
	 *@attention	��
	 *@par			��
	**/
	virtual int GetContactlist(const UCSDKFixedGroup& group, UCSDKContactList& _contactlist) = 0;

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
	virtual int ChangeGroupInfo(const UCSDKFixedGroup& group) = 0;

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
	virtual int ChangeGroupOwner(const UCSDKFixedGroup& group, const UCSDKContact& _owner) = 0;

	/**
	 *��������ͬ���̶�Ⱥ���Ա��Ϣ�б�
	 * 
	 *�ú������ڸ�������ͬ���̶�Ⱥ���Ա��Ϣ�б�
	 *
	 *@param[in]	group
	 *@param[out]	_contactlist
	 *@return		�ɹ���0		ʧ�ܣ���0,�ο�������
	 *@attention	��
	 *@par			��
	**/
	virtual int Refresh(const UCSDKFixedGroup& group, UCSDKContactList& _contactlist) = 0;

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
	virtual int Refresh(const UCSDKFixedGroup& group, bool sync_ = true) = 0;

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
	virtual int AcceptInvitation(const UCSDKFixedGroup& group) const = 0;

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
	virtual int RejectInvitation(const UCSDKFixedGroup& group) const = 0;

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
	virtual int AcceptJoinReq(const UCSDKFixedGroup& group, const UCSDKContact& _contact) const = 0; 

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
	virtual int RejectJoinReq(const UCSDKFixedGroup& group, const UCSDKContact& _contact) const = 0;
};

}
}

#endif