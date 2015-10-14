#ifndef _UC_GROUP_HEADER_
#define _UC_GROUP_HEADER_

#include "DataDef.h"


#ifdef __cplusplus
extern "C"
{
#endif

	/**
	 *增加固定群组
	 * 
	 *该函数用于增加固定群组
	 *
	 *@param[in/out]group
	 *@return		成功：0		失败：非0,参考返回码
	 *@attention	无
	 *@par			无
	**/
	UCSDK_API int UCSDK_CALL AddFixedGroup(UCFixedGroup* group);

	/**
	 *通过ID获取固定群组
	 * 
	 *该函数用于通过ID获取固定群组
	 *
	 *@param[in]	pGId
	 *@param[out]	group
	 *@return		成功：0		失败：非0,参考返回码
	 *@attention	无
	 *@par			无
	**/
	UCSDK_API int UCSDK_CALL GetFixedGroupByID(const char* pGId, UCFixedGroup* group);

	/**
	 *通过Uri获取固定群组
	 * 
	 *该函数用于通过Uri获取固定群组
	 *
	 *@param[in]	pGUri
	 *@param[out]	group
	 *@return		成功：0		失败：非0,参考返回码
	 *@attention	无
	 *@par			无
	**/
	UCSDK_API int UCSDK_CALL GetFixedGroupByUri(const char* pGUri, UCFixedGroup* group);

	/**
	 *删除固定群组
	 * 
	 *该函数用于删除固定群组
	 *
	 *@param[in]	group
	 *@return		成功：0		失败：非0,参考返回码
	 *@attention	无
	 *@par			无
	**/
	UCSDK_API int UCSDK_CALL RemoveFixedGroup(const UCFixedGroup* group);

	/**
	 *刷新固定群组列表
	 * 
	 *该函数用于刷新固定群组列表
	 *
	 *@param[in]	iFrom		起始index
	 *@param[in]	iTo			结束index	范围区间[iFrom, iTo]
	 *@param[out]	groupList
	 *@return		成功：0		失败：非0,参考返回码
	 *@attention	确保iFrom和iTo有效，与groupList内存保持一致
	 *@par			无
	**/
	UCSDK_API int UCSDK_CALL RefreshFixedGrouplist(int iFrom, int iTo, UCFixedGroupList* groupList);

	/**
	 *获取固定群组列表
	 * 
	 *该函数用于获取固定群组列表
	 *
	 *@param[in]	iFrom		起始index
	 *@param[in]	iTo			结束index	范围区间[iFrom, iTo]
	 *@param[out]	groupList
	 *@return		成功：0		失败：非0,参考返回码
	 *@attention	确保iFrom和iTo有效，与groupList内存保持一致
	 *@par			无
	**/
	UCSDK_API int UCSDK_CALL GetFixedGrouplist(int iFrom, int iTo, UCFixedGroupList* groupList);

	/**
	 *查找群组
	 * 
	 *该函数用于查找群组
	 *
	 *@param[in]	groupNo		群组号
	 *@param[in]	groupName	群组名
	 *@param[in]	offset		查询起点，一般设置为1
	 *@param[in]	count		每次查询返回的最大个数
	 *@param[out]	groupList	查找返回的群组列表
	 *@return		成功：0		失败：非0,参考返回码
	 *@attention	确保offset和count内存和groupList保持一致，如果注意offset从1开始，groupList下标从0开始
	 *@par			无
	**/
	UCSDK_API int UCSDK_CALL SearchFixedGroup(const char* groupNo, const char* groupName, int offset, int count,
												UCFixedGroupList* groupList);

	/**
	 *增加联系人私人群组
	 * 
	 *该函数用于增加联系人私人群组
	 *
	 *@param[in/out]group
	 *@return		成功：0		失败：非0,参考返回码
	 *@attention	无
	 *@par			无
	**/
	UCSDK_API int UCSDK_CALL AddCustomGroup(UCCustomGroup* group);

	/**
	 *增加收藏群组
	 * 
	 *该函数用于增加收藏群组
	 *
	 *@param[in/out]group
	 *@return		成功：0		失败：非0,参考返回码
	 *@attention	无
	 *@par			无
	**/
	UCSDK_API int UCSDK_CALL AddFavoriteGroup(UCFavoriteGroup* group);

	/**
	 *通过ID查找私有群组
	 * 
	 *该函数用于通过ID查找私有群组
	 *
	 *@param[in]	pGId
	 *@param[out]	group
	 *@return		成功：0		失败：非0,参考返回码
	 *@attention	无
	 *@par			无
	**/
	UCSDK_API int UCSDK_CALL GetCustomGroupById(const char* pGId, UCCustomGroup* group);

	/**
	 *获取私人自定义群组的列表
	 * 
	 *该函数用于获取私人自定义群组的列表
	 *
	 *@param[in]	iFrom		起始index
	 *@param[in]	iTo			结束index	范围区间[iFrom, iTo]
	 *@param[out]	groupList
	 *@return		成功：0		失败：非0,参考返回码
	 *@attention	确保iFrom和iTo有效，与groupList内存保持一致
	 *@par			无
	**/
	UCSDK_API int UCSDK_CALL GetCustomGrouplist(int iFrom, int iTo, UCCustomGroupList* groupList);

	/**
	 *删除联系人私人群组
	 * 
	 *该函数用于删除联系人私人群组
	 *
	 *@param[in]	group
	 *@return		成功：0		失败：非0,参考返回码
	 *@attention	无
	 *@par			无
	**/
	UCSDK_API int UCSDK_CALL RemoveCustomGroup(const UCCustomGroup* group);

	/**
	 *删除收藏群组
	 * 
	 *该函数用于删除收藏群组
	 *
	 *@param[in]	group
	 *@return		成功：0		失败：非0,参考返回码
	 *@attention	无
	 *@par			无
	**/
	UCSDK_API int UCSDK_CALL RemoveFavoriteGroup(const UCFavoriteGroup* group);

	/**
	 *添加收藏群组联系人
	 * 
	 *该函数用于添加收藏群组联系人
	 *
	 *@param[in]	group
	 *@param[in]	_contact
	 *@return		成功：0		失败：非0,参考返回码
	 *@attention	无
	 *@par			无
	**/
	UCSDK_API int UCSDK_CALL AddContactToFavoriteGroup(const UCFavoriteGroup* group, UCContact* _contact);

	/**
	 *删除收藏群组联系人
	 * 
	 *该函数用于删除收藏群组联系人
	 *
	 *@param[in]	group
	 *@param[in]	_contact
	 *@return		成功：0		失败：非0,参考返回码
	 *@attention	无
	 *@par			无
	**/
	UCSDK_API int UCSDK_CALL RemoveContactFromFavoriteGroup(const UCFavoriteGroup* group, const UCContact* _contact);

	/**
	 *更改收藏群组名
	 * 
	 *该函数用于更改收藏群组名
	 *
	 *@param[in]	group
	 *@param[in]	_name
	 *@return		成功：0		失败：非0,参考返回码
	 *@attention	无
	 *@par			无
	**/
	UCSDK_API int UCSDK_CALL RenameToFavoriteGroup(const UCFavoriteGroup* group, const char* _name);

	/**
	 *获取收藏群成员信息列表
	 * 
	 *该函数用于获取收藏群成员信息列表
	 *
	 *@param[in]	group
	 *@param[in]	iFrom		起始index
	 *@param[in]	iTo			结束index	范围区间[iFrom, iTo]
	 *@param[out]	_contactlist
	 *@return		成功：0		失败：非0,参考返回码
	 *@attention	确保iFrom和iTo有效，与_contactlist内存保持一致
	 *@par			无
	**/
	UCSDK_API int UCSDK_CALL GetContactlistFromFavoriteGroup(const UCFavoriteGroup* group, int iFrom, int iTo, UCContactList* _contactlist);

	/**
	 *添加联系人私人群组联系人
	 * 
	 *该函数用于添加联系人私人群组联系人
	 *
	 *@param[in]	group
	 *@param[in]	_contact
	 *@return		成功：0		失败：非0,参考返回码
	 *@attention	无
	 *@par			无
	**/
	UCSDK_API int UCSDK_CALL AddContactToCustomGroup(const UCCustomGroup* group, UCContact* _contact);

	/**
	 *删除联系人私人群组联系人
	 * 
	 *该函数用于删除联系人私人群组联系人
	 *
	 *@param[in]	group
	 *@param[in]	_contact
	 *@return		成功：0		失败：非0,参考返回码
	 *@attention	无
	 *@par			无
	**/
	UCSDK_API int UCSDK_CALL RemoveContactFromCustomGroup(const UCCustomGroup* group, const UCContact* _contact);

	/**
	 *更改联系人私人群组名
	 * 
	 *该函数用于更改联系人私人群组名
	 *
	 *@param[in]	group
	 *@param[in]	_name
	 *@return		成功：0		失败：非0,参考返回码
	 *@attention	无
	 *@par			无
	**/
	UCSDK_API int UCSDK_CALL RenameToCustomGroup(const UCCustomGroup* group, const char* _name);

	/**
	 *获取联系人私人群成员信息列表
	 * 
	 *该函数用于获取联系人私人群成员信息列表
	 *
	 *@param[in]	group
	 *@param[in]	iFrom		起始index
	 *@param[in]	iTo			结束index	范围区间[iFrom, iTo]
	 *@param[out]	_contactlist
	 *@return		成功：0		失败：非0,参考返回码
	 *@attention	确保iFrom和iTo有效，与_contactlist内存保持一致
	 *@par			无
	**/
	UCSDK_API int UCSDK_CALL GetContactlistFromCustomGroup(const UCCustomGroup* group, int iFrom, int iTo, UCContactList* _contactlist);

	/**
	 *联系人私人群组上移
	 * 
	 *该函数用于联系人私人群组上移
	 *
	 *@param[in]	group
	 *@return		成功：0		失败：非0,参考返回码
	 *@attention	无
	 *@par			无
	**/
	UCSDK_API int UCSDK_CALL MoveUp(const UCCustomGroup* group);

	/**
	 *联系人私人群组下移
	 * 
	 *该函数用于联系人私人群组下移
	 *
	 *@param[in]	group
	 *@return		成功：0		失败：非0,参考返回码
	 *@attention	无
	 *@par			无
	**/
	UCSDK_API int UCSDK_CALL MoveDown(const UCCustomGroup* group);

	/**
	 *添加固定群组联系人
	 * 
	 *该函数用于添加固定群组联系人
	 *
	 *@param[in]	group
	 *@param[in]	_contact
	 *@return		成功：0		失败：非0,参考返回码
	 *@attention	1. 群主主动加人		2. 用户申请加人群组
	 *@par			无
	**/
	UCSDK_API int UCSDK_CALL AddContactToFixedGroup(const UCFixedGroup* group, UCContact* _contact);

	/**
	 *删除固定群组联系人
	 * 
	 *该函数用于删除固定群组联系人
	 *
	 *@param[in]	group
	 *@param[in]	_contact
	 *@return		成功：0		失败：非0,参考返回码
	 *@attention	无
	 *@par			无
	**/
	UCSDK_API int UCSDK_CALL RemoveContactFromFixedGroup(const UCFixedGroup* group, const UCContact* _contact);

	/**
	 *更改固定群组名
	 * 
	 *该函数用于更改固定群组名
	 *
	 *@param[in]	group
	 *@param[in]	_name
	 *@return		成功：0		失败：非0,参考返回码
	 *@attention	无
	 *@par			无
	**/
	UCSDK_API int UCSDK_CALL RenameToFixedGroup(const UCFixedGroup* group, const char* _name);

	/**
	 *获取固定群成员信息列表
	 * 
	 *该函数用于获取固定群成员信息列表
	 *
	 *@param[in]	group
	 *@param[in]	iFrom		起始index
	 *@param[in]	iTo			结束index	范围区间[iFrom, iTo]
	 *@param[out]	_contactlist
	 *@return		确保iFrom和iTo有效，与_contactlist内存保持一致
	 *@attention	无
	 *@par			无
	**/
	UCSDK_API int UCSDK_CALL GetContactlistFromFixedGroup(const UCFixedGroup* group, int iFrom, int iTo, UCContactList* _contactlist);

	/**
	 *修改固定群组基本信息
	 * 
	 *该函数用于修改固定群组基本信息
	 *
	 *@param[in]	group
	 *@return		成功：0		失败：非0,参考返回码
	 *@attention	无
	 *@par			无
	**/
	UCSDK_API int UCSDK_CALL ChangeGroupInfo(const UCFixedGroup* group);

	/**
	 *修改固定群群主(仅能由当前群主修改)
	 * 
	 *该函数用于修改固定群群主
	 *
	 *@param[in]	group
	 *@param[in]	_owner
	 *@return		成功：0		失败：非0,参考返回码
	 *@attention	仅能由当前群主修改，_owner必须为已有群成员
	 *@par			无
	**/
	UCSDK_API int UCSDK_CALL ChangeGroupOwner(const UCFixedGroup* group, const UCContact* _owner);

	/**
	 *跟服务器同步固定群组成员信息列表
	 * 
	 *该函数用于跟服务器同步固定群组成员信息列表
	 *
	 *@param[in]	group
	 *@param[in]	iFrom		起始index
	 *@param[in]	iTo			结束index	范围区间[iFrom, iTo]
	 *@param[out]	_contactlist
	 *@return		成功：0		失败：非0,参考返回码
	 *@attention	确保iFrom和iTo有效，与_contactlist内存保持一致
	 *@par			无
	**/
	UCSDK_API int UCSDK_CALL RefreshContactList(const UCFixedGroup* group, int iFrom, int iTo, UCContactList* _contactlist);

	/**
	 *刷新固定群组
	 * 
	 *该函数用于刷新固定群组
	 *
	 *@param[in]	group
	 *@param[in]	sync_
	 *@return		成功：0		失败：非0,参考返回码
	 *@attention	无
	 *@par			无
	**/
	UCSDK_API int UCSDK_CALL RefreshGroup(const UCFixedGroup* group);

	/**
	 *接受固定群组邀请
	 * 
	 *该函数用于接受固定群组邀请
	 *
	 *@param[in]	group
	 *@return		成功：0		失败：非0,参考返回码
	 *@attention	无
	 *@par			无
	**/
	UCSDK_API int UCSDK_CALL AcceptInvitation(const UCFixedGroup* group);

	/**
	 *拒绝固定群组邀请
	 * 
	 *该函数用于拒绝固定群组邀请
	 *
	 *@param[in]	group
	 *@return		成功：0		失败：非0,参考返回码
	 *@attention	无
	 *@par			无
	**/
	UCSDK_API int UCSDK_CALL RejectInvitation(const UCFixedGroup* group);

	/**
	 *接受加入固定群组请求
	 * 
	 *该函数用于接受加入固定群组请求
	 *
	 *@param[in]	group
	 *@param[in] 	_contact
	 *@return 		成功：0		失败：非0,参考返回码
	 *@attention	无
	 *@par			无
	**/
	UCSDK_API int UCSDK_CALL AcceptJoinReq(const UCFixedGroup* group, const UCContact* _contact); 

	/**
	 *拒绝加入固定群组请求
	 * 
	 *该函数用于拒绝加入固定群组请求
	 *
	 *@param[in]	group
	 *@param[in] 	_contact
	 *@return 		成功：0		失败：非0,参考返回码
	 *@attention	无
	 *@par			无
	**/
	UCSDK_API int UCSDK_CALL RejectJoinReq(const UCFixedGroup* group, const UCContact* _contact);


#ifdef __cplusplus
}
#endif 


#endif