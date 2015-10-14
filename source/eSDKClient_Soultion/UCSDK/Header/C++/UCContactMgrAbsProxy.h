#ifndef _UC_CONTACTMGR_ABS_PROXY_H_
#define _UC_CONTACTMGR_ABS_PROXY_H_

#include "DataType.h"


namespace eSDK {
	namespace UC {


/**
 *联系人管理类
 * 
 *该类用于联系人管理，提供联系人相关操作
 *
 *@attention	无
 *@par			无
**/
class UCSDK_API UCContactMgrAbsProxy
{
protected:
	UCContactMgrAbsProxy();
	virtual ~UCContactMgrAbsProxy();

public:
	/**
	 *获取联系人管理类单实例
	 * 
	 *该函数用于获取联系人管理类单实例
	 *
	 *@return		成功：联系人管理类单实例指针， 失败：NULL
	 *@attention	无
	 *@par			无
	**/
	static UCContactMgrAbsProxy* GetInstance();

	/**
	 *释放联系人管理类实例
	 * 
	 *该函数用于释放联系人管理类实例
	 *
	 *@attention	在调用UCSDKAbsProxy::ReleaseInstance()时候，会跟着一起释放
	 *@par			无
	**/
	static void ReleaseInstance();

public:
	/**
	 *获取所有联系人列表
	 * 
	 *该函数用于获取所有联系人列表
	 *
	 *@param[out]	memberList
	 *@return		成功：0		失败：非0,参考返回码
	 *@attention	无
	 *@par			无
	**/
	virtual int GetAllContactlist(UCSDKContactList& memberList) = 0;

	/**
	 *通过账号获取联系人
	 * 
	 *该函数用于通过账号获取联系人
	 *
	 *@param[out]	member
	 *@param[in]	strAccount
	 *@return		成功：0		失败：非0,参考返回码
	 *@attention	此方法只能获取本地已经添加的联系人，获取的联系人无ID
	 *@par			无
	**/
	virtual int GetContactByAccount(UCSDKContact& member, const std::string& strAccount) = 0;

	/**
	 *通过ID获取联系人
	 * 
	 *该函数用于通过ID获取联系人
	 *
	 *@param[out]	member
	 *@param[in]	strID
	 *@return		成功：0		失败：非0,参考返回码
	 *@attention	此方法只能获取本地已经添加的联系人
	 *@par			无
	**/
	virtual int GetContactById(UCSDKContact& member, const std::string& strID) = 0;

	/**
	 *通过电话号码获取联系人
	 * 
	 *该函数用于通过电话号码获取联系人
	 *
	 *@param[out]	member
	 *@param[in]	strPhoneNum
	 *@return		成功：0		失败：非0,参考返回码
	 *@attention	此方法只能获取本地已经添加的联系人
	 *@par			无
	**/
	virtual int GetContactByPhoneNum(UCSDKContact& member, const std::string& strPhoneNum) = 0;

	/**
	 *通过uri获取联系人
	 * 
	 *该函数用于通过uri获取联系人
	 *
	 *@param[out]	member
	 *@param[in]	strPhoneNum
	 *@return		成功：0		失败：非0,参考返回码
	 *@attention	此方法只能获取本地已经添加的联系人，获取的联系人有ID
	 *@par			无
	**/
	virtual int GetContactByUri(UCSDKContact& member, const std::string& strUri) = 0;

	/**
	 *查看是否本地已经存在此联系人
	 * 
	 *该函数用于查看是否本地已经存在此联系人
	 *
	 *@param[in]	strUri
	 *@return		成功：true	失败：false
	 *@attention	无
	 *@par			无
	**/
	virtual bool HasContact(const std::string& strUri) = 0;

	/**
	 *通过account刷新联系人
	 * 
	 *该函数用于通过account刷新联系人
	 *
	 *@param[in]	strAccount
	 *@param[out]	member
	 *@return		成功：0		失败：非0,参考返回码
	 *@attention	无
	 *@par			无
	**/
	virtual int RefreshContactByAccount(const std::string& strAccount, UCSDKContact& member) = 0;

	/**
	 *通过ID刷新联系人
	 * 
	 *该函数用于通过ID刷新联系人
	 *
	 *@param[in]	strID
	 *@param[out]	member
	 *@return		成功：0		失败：非0,参考返回码
	 *@attention	无
	 *@par			无
	**/
	virtual int RefreshContactById(const std::string& strID, UCSDKContact& member) = 0;

	/**
	 *通过Uri刷新联系人
	 * 
	 *该函数用于通过Uri刷新联系人
	 *
	 *@param[in]	strUri
	 *@param[out]	member
	 *@return		成功：0		失败：非0,参考返回码
	 *@attention	无
	 *@par			无
	**/
	virtual int RefreshContactByUri(const std::string& strUri, UCSDKContact& member) = 0;

	/**
	 *删除特定ID的联系人
	 * 
	 *该函数用于删除特定ID的联系人
	 *
	 *@param[in]	strID
	 *@return		成功：0		失败：非0,参考返回码
	 *@attention	无
	 *@par			无
	**/
	virtual int RemoveContactById(const std::string& strID) = 0;

	/**
	 *从企业通讯录里查找联系人
	 * 
	 *该函数用于从企业通讯录里查找联系人
	 *
	 *@param[out]	memberList		返回的联系人列表
	 *@param[in]	condition		查询条件，如：联系人account，或account关键字
	 *@param[in]	deptid			查询部门的ID，可默认置空为“”
	 *@param[in]	querysubdept	是否需要对子部门查询
	 *@param[in]	offset			查询起点，一般设置为0
	 *@param[in]	count			每次查询返回的最大个数
	 *@param[in]	ordertype		查询类型，一般设置为0
	 *@param[out]	recamount		查询结果总数
	 *@return		成功：0		失败：非0,参考返回码
	 *@attention	无
	 *@par			无
	**/
	virtual int SearchContact(UCSDKContactList& memberList, 
		const std::string& condition, const std::string& deptid,
		bool querysubdept, int offset, int count, int ordertype, int& recamount) = 0;

public:
	/**
	 *判断当前联系人信息能否被修改
	 * 
	 *该函数用于判断当前联系人信息能否被修改
	 *
	 *@param[in]	member
	 *@return		成功：true	失败：false
	 *@attention	无
	 *@par			无
	**/
	virtual bool Modify(const UCSDKContact& member) = 0;

	/**
	 *获取用户自身头像路径
	 * 
	 *该函数用于获取用户自身头像路径
	 *
	 *@param[in]	member
	 *@param[in]	grey
	 *@return		成功：头像路径	失败：空字符串
	 *@attention	如果失败，入参member请确保member.uri_
	 *@par			无
	**/
	virtual std::string GetHeadImagePath(const UCSDKContact& member, bool grey = false) = 0;

	/**
	 *从一个群组移到另外一个群组
	 * 
	 *该函数用于从一个群组移到另外一个群组
	 *
	 *@param[in]	member
	 *@param[in]	_src
	 *@param[in]	_target
	 *@return		成功：true	失败：false
	 *@attention	如果失败，入参member请确保member.uri_
	 *@par			无
	**/
	virtual bool MoveToGroup(const UCSDKContact& member, const UCSDKGroup& _src, const UCSDKGroup& _target) = 0;

	/**
	 *添加到群组
	 * 
	 *该函数用于添加到群组
	 *
	 *@param[in]	member
	 *@param[in]	_target
	 *@return		成功：true	失败：false
	 *@attention	如果失败，入参member请确保member.uri_
	 *@par			无
	**/
	virtual bool AddToGroup(const UCSDKContact& member, const UCSDKGroup& _target) = 0;

	/**
	 *从群组中移除
	 * 
	 *该函数用于从群组中移除
	 *
	 *@param[in]	member
	 *@param[in]	_target
	 *@return		成功：true	失败：false
	 *@attention	如果失败，入参member请确保member.uri_
	 *@par			无
	**/
	virtual bool RemoveFromGroup(const UCSDKContact& member, const UCSDKGroup& _target) = 0;

	/**
	 *判断能否发起会话
	 * 
	 *该函数用于判断能否发起会话
	 *
	 *@param[in]	member
	 *@param[in]	_type
	 *@return		成功：true	失败：false
	 *@attention	无
	 *@par			无
	**/
	virtual bool CanStartSession(const UCSDKContact& member, SESSION_TYPE_E _type) = 0;

	/**
	 *判断能否移入某个群组
	 * 
	 *该函数用于判断能否移入某个群组
	 *
	 *@param[in]	member
	 *@param[in]	_src
	 *@param[in]	_target
	 *@return		成功：true	失败：false
	 *@attention	无
	 *@par			无
	**/
	virtual bool CanMoveToGroup(const UCSDKContact& member, const UCSDKGroup& _src, const UCSDKGroup& _target) = 0;

	/**
	 *获取所有加入的群组
	 * 
	 *该函数用于获取所有加入的群组
	 *
	 *@param[in]	member
	 *@param[out]	_groups
	 *@return		成功：true	失败：false
	 *@attention	如果失败，入参member请确保member.uri_
	 *@par			无
	**/
	virtual int GetCustomGroups(const UCSDKContact& member, UCSDKCustomGroupList& _groups) = 0;

	/**
	 *是否加入收藏
	 * 
	 *该函数用于是否加入收藏
	 *
	 *@param[in]	member
	 *@return		成功：true	失败：false
	 *@attention	无
	 *@par			无
	**/
	virtual bool IsFavourite(const UCSDKContact& member) = 0;
};

}
}

#endif