#ifndef _UC_GROUP_ABS_PROXY_H_
#define _UC_GROUP_ABS_PROXY_H_

#include "DataType.h"


namespace eSDK {
	namespace UC {


/**
 *群组管理类
 * 
 *该类用于群组管理，提供群组相关操作，这里的群组包括联系人分组(CustomGroup)，固定群组(FixedGroup)，收藏群组(FavoriteGroup)
 *
 *@attention	无
 *@par			无
**/
class UCSDK_API UCGroupAbsProxy
{
protected:
	UCGroupAbsProxy();
	virtual ~UCGroupAbsProxy();

public:
	/**
	 *获取群组管理类单实例
	 * 
	 *该函数用于获取群组管理类单实例
	 *
	 *@return		成功：群组管理类单实例指针， 失败：NULL
	 *@attention	无
	 *@par			无
	**/
	static UCGroupAbsProxy* GetInstance();

	/**
	 *释放群组管理类单实例
	 * 
	 *该函数用于释放群组管理类单实例
	 *
	 *@attention	在调用UCSDKAbsProxy::ReleaseInstance()时候，会跟着一起释放
	 *@par			无
	**/
	static void ReleaseInstance();

public:
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
	virtual int AddFixedGroup(UCSDKFixedGroup& group) = 0;

	/**
	 *通过ID获取固定群组
	 * 
	 *该函数用于通过ID获取固定群组
	 *
	 *@param[out]	group
	 *@param[in]	strGroupID
	 *@return		成功：0		失败：非0,参考返回码
	 *@attention	无
	 *@par			无
	**/
	virtual int GetFixedGroupByID(UCSDKFixedGroup& group, const std::string& strGroupID) = 0;

	/**
	 *通过Uri获取固定群组
	 * 
	 *该函数用于通过Uri获取固定群组
	 *
	 *@param[out]	group
	 *@param[in]	strGroupUri
	 *@return		成功：0		失败：非0,参考返回码
	 *@attention	无
	 *@par			无
	**/
	virtual int GetFixedGroupByUri(UCSDKFixedGroup& group, const std::string& strGroupUri) = 0;

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
	virtual int RemoveFixedGroup(const UCSDKFixedGroup& group) = 0;

	/**
	 *刷新固定群组列表
	 * 
	 *该函数用于刷新固定群组列表
	 *
	 *@param[out]	groupList
	 *@return		成功：0		失败：非0,参考返回码
	 *@attention	无
	 *@par			无
	**/
	virtual int RefreshFixedGrouplist(UCSDKFixedGroupList& groupList) = 0;

	/**
	 *获取固定群组列表
	 * 
	 *该函数用于获取固定群组列表
	 *
	 *@param[out]	groupList
	 *@return		成功：0		失败：非0,参考返回码
	 *@attention	无
	 *@par			无
	**/
	virtual int GetFixedGrouplist(UCSDKFixedGroupList& groupList) = 0;

	/**
	 *查找群组
	 * 
	 *该函数用于查找群组
	 *
	 *@param[out]	groupList	查找返回的群组列表
	 *@param[in]	groupNo		群组号
	 *@param[in]	groupName	群组名
	 *@param[in]	offset		查询起点，一般设置为1
	 *@param[in]	count		每次查询返回的最大个数
	 *@return		成功：0		失败：非0,参考返回码
	 *@attention	无
	 *@par			无
	**/
	virtual int SearchFixedGroup(UCSDKFixedGroupList& groupList, 
		const std::string& groupNo, const std::string& groupName, int offset, int count) = 0;

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
	virtual int AddCustomGroup(UCSDKCustomGroup& group) = 0;

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
	virtual int AddFavoriteGroup(UCSDKFavoriteGroup& group) = 0;

	/**
	 *通过ID查找私有群组
	 * 
	 *该函数用于通过ID查找私有群组
	 *
	 *@param[out]	group
	 *@param[in]	strGroupID
	 *@return		成功：0		失败：非0,参考返回码
	 *@attention	无
	 *@par			无
	**/
	virtual int GetCustomGroupById(UCSDKCustomGroup& group, const std::string& strGroupID) = 0;

	/**
	 *获取私人自定义群组的列表
	 * 
	 *该函数用于获取私人自定义群组的列表
	 *
	 *@param[out]	groupList
	 *@return		成功：0		失败：非0,参考返回码
	 *@attention	无
	 *@par			无
	**/
	virtual int GetCustomGrouplist(UCSDKCustomGroupList& groupList) = 0;

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
	virtual int RemoveCustomGroup(const UCSDKCustomGroup& group) = 0;

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
	virtual int RemoveFavoriteGroup(const UCSDKFavoriteGroup& group) = 0;

public:
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
	virtual int AddContact(const UCSDKFavoriteGroup& group, UCSDKContact& _contact) = 0;

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
	virtual int RemoveContact(const UCSDKFavoriteGroup& group, const UCSDKContact& _contact) const = 0;

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
	virtual int Rename(const UCSDKFavoriteGroup& group, const std::string& _name) = 0;

	/**
	 *获取收藏群成员信息列表
	 * 
	 *该函数用于获取收藏群成员信息列表
	 *
	 *@param[in]	group
	 *@param[out]	_contactlist
	 *@return		成功：0		失败：非0,参考返回码
	 *@attention	无
	 *@par			无
	**/
	virtual int GetContactlist(const UCSDKFavoriteGroup& group, UCSDKContactList& _contactlist) = 0;

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
	virtual int AddContact(const UCSDKCustomGroup& group, UCSDKContact& _contact) = 0;

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
	virtual int RemoveContact(const UCSDKCustomGroup& group, const UCSDKContact& _contact) const = 0;

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
	virtual int Rename(const UCSDKCustomGroup& group, const std::string& _name) = 0;

	/**
	 *获取联系人私人群成员信息列表
	 * 
	 *该函数用于获取联系人私人群成员信息列表
	 *
	 *@param[in]	group
	 *@param[out]	_contactlist
	 *@return		成功：0		失败：非0,参考返回码
	 *@attention	无
	 *@par			无
	**/
	virtual int GetContactlist(const UCSDKCustomGroup& group, UCSDKContactList& _contactlist) = 0;

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
	virtual int MoveUp(const UCSDKCustomGroup& group) = 0;

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
	virtual int MoveDown(const UCSDKCustomGroup& group) = 0;

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
	virtual int AddContact(const UCSDKFixedGroup& group, UCSDKContact& _contact) = 0;

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
	virtual int RemoveContact(const UCSDKFixedGroup& group, const UCSDKContact& _contact) const = 0;

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
	virtual int Rename(const UCSDKFixedGroup& group, const std::string& _name) = 0;

	/**
	 *获取固定群成员信息列表
	 * 
	 *该函数用于获取固定群成员信息列表
	 *
	 *@param[in]	group
	 *@param[out]	_contactlist
	 *@return		成功：0		失败：非0,参考返回码
	 *@attention	无
	 *@par			无
	**/
	virtual int GetContactlist(const UCSDKFixedGroup& group, UCSDKContactList& _contactlist) = 0;

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
	virtual int ChangeGroupInfo(const UCSDKFixedGroup& group) = 0;

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
	virtual int ChangeGroupOwner(const UCSDKFixedGroup& group, const UCSDKContact& _owner) = 0;

	/**
	 *跟服务器同步固定群组成员信息列表
	 * 
	 *该函数用于跟服务器同步固定群组成员信息列表
	 *
	 *@param[in]	group
	 *@param[out]	_contactlist
	 *@return		成功：0		失败：非0,参考返回码
	 *@attention	无
	 *@par			无
	**/
	virtual int Refresh(const UCSDKFixedGroup& group, UCSDKContactList& _contactlist) = 0;

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
	virtual int Refresh(const UCSDKFixedGroup& group, bool sync_ = true) = 0;

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
	virtual int AcceptInvitation(const UCSDKFixedGroup& group) const = 0;

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
	virtual int RejectInvitation(const UCSDKFixedGroup& group) const = 0;

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
	virtual int AcceptJoinReq(const UCSDKFixedGroup& group, const UCSDKContact& _contact) const = 0; 

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
	virtual int RejectJoinReq(const UCSDKFixedGroup& group, const UCSDKContact& _contact) const = 0;
};

}
}

#endif