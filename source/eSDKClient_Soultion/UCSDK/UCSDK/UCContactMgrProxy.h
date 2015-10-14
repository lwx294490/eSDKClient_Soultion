#ifndef _UC_CONTACTMGR_PROXY_H_
#define _UC_CONTACTMGR_PROXY_H_

#include "UCContactMgrAbsProxy.h"


namespace eSDK {
	namespace UC {

/*lint -save -e1735*/
class UCContactMgrProxy : public UCContactMgrAbsProxy
{
private:
	UCContactMgrProxy();
	~UCContactMgrProxy();

public:
	static UCContactMgrProxy* Instance();
	static void Destroy();

public:
	virtual int GetAllContactlist(UCSDKContactList& memberList);
	virtual int GetContactByAccount(UCSDKContact& member, const std::string& strAccount);
	virtual int GetContactById(UCSDKContact& member, const std::string& strID);
	virtual int GetContactByPhoneNum(UCSDKContact& member, const std::string& strPhoneNum);
	virtual int GetContactByUri(UCSDKContact& member, const std::string& strUri);
	virtual bool HasContact(const std::string& strUri);
	virtual int RefreshContactByAccount(const std::string& strAccount, UCSDKContact& member);
	virtual int RefreshContactById(const std::string& strID, UCSDKContact& member);
	virtual int RefreshContactByUri(const std::string& strUri, UCSDKContact& member);
	virtual int RemoveContactById(const std::string& strID);
	virtual int SearchContact(UCSDKContactList& memberList, 
		const std::string& condition, const std::string& deptid,
		bool querysubdept, int offset, int count, int ordertype, int& recamount);

public:
	virtual bool Modify(const UCSDKContact& member);
	virtual std::string GetHeadImagePath(const UCSDKContact& member, bool grey = false);
	virtual bool MoveToGroup(const UCSDKContact& member, const UCSDKGroup& _src, const UCSDKGroup& _target);
	virtual bool AddToGroup(const UCSDKContact& member, const UCSDKGroup& _target);
	virtual bool RemoveFromGroup(const UCSDKContact& member, const UCSDKGroup& _target);
	virtual bool CanStartSession(const UCSDKContact& member, SESSION_TYPE_E _type);
	virtual bool CanMoveToGroup(const UCSDKContact& member, const UCSDKGroup& _src, const UCSDKGroup& _target);
	virtual int GetCustomGroups(const UCSDKContact& member, UCSDKCustomGroupList& _groups);
	virtual bool IsFavourite(const UCSDKContact& member);

public:
	int Init();
	int UnInit();
	int GetContactByUri(uc::model::Contact& contact, const std::string& uri);
	int GetContactByAccount(uc::model::Contact& contact, const std::string& account);
	
	//辅助方法
public:
	static void CopyUCSDKContactToContact(const UCSDKContact& member, Contact& contact);
	static void CopyContactToUCSDKContact(const Contact& contact, UCSDKContact& member);
	bool GetContactByUCSDKContact(const UCSDKContact& member, Contact& contact);
	bool GetGroupByUCGroup(const UCSDKGroup& ucsdkgroup, Group*& group);

private:
	uc::model::ContactMgr* m_pContactMgr;			//个人通讯录管理
	uc::model::EntAddrbookMgr* m_pEntContactMgr;	//企业通讯录管理

private:
	static UCContactMgrProxy* m_pUCContactMgrProxy;
};
/*lint -restore*/

}
}

#endif
