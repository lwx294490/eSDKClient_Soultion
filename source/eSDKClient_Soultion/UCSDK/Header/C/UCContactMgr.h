#ifndef _UC_CONTACTMGR_HEADER_
#define _UC_CONTACTMGR_HEADER_

#include "DataDef.h"


#ifdef __cplusplus
extern "C"
{
#endif

	/**
	 *获取所有联系人列表
	 * 
	 *该函数用于获取所有联系人列表
	 *
	 *@param[in]	iFrom		起始index
	 *@param[in]	iTo			结束index	范围区间[iFrom, iTo]
	 *@param[out]	memberList
	 *@return		成功：0		失败：非0,参考返回码
	 *@attention	确保iFrom和iTo有效，与memberList内存保持一致
	 *@par			无
	**/
	UCSDK_API int UCSDK_CALL GetAllContactlist(int iFrom, int iTo, UCContactList* memberList);

	/**
	 *通过账号获取联系人
	 * 
	 *该函数用于通过账号获取联系人
	 *
	 *@param[in]	pAcc
	 *@param[out]	member
	 *@return		成功：0		失败：非0,参考返回码
	 *@attention	此方法只能获取本地已经添加的联系人，获取的联系人无ID
	 *@par			无
	**/
	UCSDK_API int UCSDK_CALL GetContactByAccount(const char* pAcc, UCContact* member);

	/**
	 *通过ID获取联系人
	 * 
	 *该函数用于通过ID获取联系人
	 *
	 *@param[in]	pId
	 *@param[out]	member	 
	 *@return		成功：0		失败：非0,参考返回码
	 *@attention	此方法只能获取本地已经添加的联系人
	 *@par			无
	**/
	UCSDK_API int UCSDK_CALL GetContactById(const char* pId, UCContact* member);

	/**
	 *通过电话号码获取联系人
	 * 
	 *该函数用于通过电话号码获取联系人
	 *
	 *@param[in]	pPhoneNum
	 *@param[out]	member
	 *@return		成功：0		失败：非0,参考返回码
	 *@attention	此方法只能获取本地已经添加的联系人
	 *@par			无
	**/
	UCSDK_API int UCSDK_CALL GetContactByPhoneNum(const char* pPhoneNum, UCContact* member);

	/**
	 *通过uri获取联系人
	 * 
	 *该函数用于通过uri获取联系人
	 *
	 *@param[in]	pUri
	 *@param[out]	member
	 *@return		成功：0		失败：非0,参考返回码
	 *@attention	此方法只能获取本地已经添加的联系人，获取的联系人有ID
	 *@par			无
	**/
	UCSDK_API int UCSDK_CALL GetContactByUri(const char* pUri, UCContact* member);

	/**
	 *查看是否本地已经存在此联系人
	 * 
	 *该函数用于查看是否本地已经存在此联系人
	 *
	 *@param[in]	pUri
	 *@return		成功：0	失败：1
	 *@attention	无
	 *@par			无
	**/
	UCSDK_API int UCSDK_CALL HasContact(const char* pUri);

	/**
	 *通过account刷新联系人
	 * 
	 *该函数用于通过account刷新联系人
	 *
	 *@param[in]	pAcc
	 *@param[out]	member
	 *@return		成功：0		失败：非0,参考返回码
	 *@attention	无
	 *@par			无
	**/
	UCSDK_API int UCSDK_CALL RefreshContactByAccount(const char* pAcc, UCContact* member);

	/**
	 *通过ID刷新联系人
	 * 
	 *该函数用于通过ID刷新联系人
	 *
	 *@param[in]	pId
	 *@param[out]	member
	 *@return		成功：0		失败：非0,参考返回码
	 *@attention	无
	 *@par			无
	**/
	UCSDK_API int UCSDK_CALL RefreshContactById(const char* pId, UCContact* member);

	/**
	 *通过Uri刷新联系人
	 * 
	 *该函数用于通过Uri刷新联系人
	 *
	 *@param[in]	pUri
	 *@param[out]	member
	 *@return		成功：0		失败：非0,参考返回码
	 *@attention	无
	 *@par			无
	**/
	UCSDK_API int UCSDK_CALL RefreshContactByUri(const char* pUri, UCContact* member);

	/**
	 *删除特定ID的联系人
	 * 
	 *该函数用于删除特定ID的联系人
	 *
	 *@param[in]	pId
	 *@return		成功：0		失败：非0,参考返回码
	 *@attention	无
	 *@par			无
	**/
	UCSDK_API int UCSDK_CALL RemoveContactById(const char* pId);

	/**
	 *从企业通讯录里查找联系人
	 * 
	 *该函数用于从企业通讯录里查找联系人
	 *
	 *@param[in]	condition		查询条件，如：联系人account，或account关键字
	 *@param[in]	deptid			查询部门的ID，可默认置空为“”
	 *@param[in]	querysubdept	是否需要对子部门查询
	 *@param[in]	offset			查询起点，一般设置为0
	 *@param[in]	count			每次查询返回的最大个数
	 *@param[in]	ordertype		查询类型，一般设置为0
	 *@param[out]	recamount		查询结果总数
	 *@param[out]	memberList		返回的联系人列表
	 *@return		成功：0		失败：非0,参考返回码
	 *@attention	确保offset和count和memberList内存保持一致
	 *@par			无
	**/
	UCSDK_API int UCSDK_CALL SearchContact(const char* condition, const char* deptid,
		int querysubdept, int offset, int count, int ordertype, 
		int* recamount, UCContactList* memberList);

	/**
	 *判断当前联系人信息能否被修改
	 * 
	 *该函数用于判断当前联系人信息能否被修改
	 *
	 *@param[in]	member
	 *@return		成功：0	失败：1
	 *@attention	无
	 *@par			无
	**/
	UCSDK_API int UCSDK_CALL Modify(const UCContact* member);

	/**
	 *获取用户自身头像路径
	 * 
	 *该函数用于获取用户自身头像路径
	 *
	 *@param[in]	member
	 *@param[out]	path
	 *@return		成功：0		失败：非0,参考返回码
	 *@attention	如果失败，入参member请确保member.uri_
	 *@par			无
	**/
	UCSDK_API int UCSDK_CALL GetHeadImagePath(const UCContact* member, char path[IMAGE_LENGTH]);

	/**
	 *从一个群组移到另外一个群组
	 * 
	 *该函数用于从一个群组移到另外一个群组
	 *
	 *@param[in]	member
	 *@param[in]	_src
	 *@param[in]	_target
	 *@return		成功：0		失败：非0,参考返回码
	 *@attention	如果失败，入参member请确保member.uri_
	 *@par			无
	**/
	UCSDK_API int UCSDK_CALL MoveToGroup(const UCContact* member, const UCGroup* _src, const UCGroup* _target);

	/**
	 *添加到群组
	 * 
	 *该函数用于添加到群组
	 *
	 *@param[in]	member
	 *@param[in]	_target
	 *@return		成功：0		失败：非0,参考返回码
	 *@attention	如果失败，入参member请确保member.uri_
	 *@par			无
	**/
	UCSDK_API int UCSDK_CALL AddToGroup(const UCContact* member, const UCGroup* _target);

	/**
	 *从群组中移除
	 * 
	 *该函数用于从群组中移除
	 *
	 *@param[in]	member
	 *@param[in]	_target
	 *@return		成功：0		失败：非0,参考返回码
	 *@attention	如果失败，入参member请确保member.uri_
	 *@par			无
	**/
	UCSDK_API int UCSDK_CALL RemoveFromGroup(const UCContact* member, const UCGroup* _target);

	/**
	 *判断能否发起会话
	 * 
	 *该函数用于判断能否发起会话
	 *
	 *@param[in]	member
	 *@param[in]	_type
	 *@return		成功：0	失败：1
	 *@attention	无
	 *@par			无
	**/
	UCSDK_API int UCSDK_CALL CanStartSession(const UCContact* member, int _type);

	/**
	 *判断能否移入某个群组
	 * 
	 *该函数用于判断能否移入某个群组
	 *
	 *@param[in]	member
	 *@param[in]	_src
	 *@param[in]	_target
	 *@return		成功：0	失败：1
	 *@attention	无
	 *@par			无
	**/
	UCSDK_API int UCSDK_CALL CanMoveToGroup(const UCContact* member, const UCGroup* _src, const UCGroup* _target);

	/**
	 *获取所有加入的群组
	 * 
	 *该函数用于获取所有加入的群组
	 *
	 *@param[in]	member
	 *@param[in]	iFrom		起始index
	 *@param[in]	iTo			结束index	范围区间[iFrom, iTo]
	 *@param[out]	_groups
	 *@return		成功：0		失败：非0,参考返回码
	 *@attention	如果失败，入参member请确保member.uri_，确保iFrom和iTo有效，与_groups内存保持一致
	 *@par			无
	**/
	UCSDK_API int UCSDK_CALL GetCustomGroups(const UCContact* member, int iFrom, int iTo, UCCustomGroupList* _groups);

	/**
	 *是否加入收藏
	 * 
	 *该函数用于是否加入收藏
	 *
	 *@param[in]	member
	 *@return		成功：0	失败：1
	 *@attention	无
	 *@par			无
	**/
	UCSDK_API int UCSDK_CALL IsFavourite(const UCContact* member);


#ifdef __cplusplus
}
#endif 


#endif