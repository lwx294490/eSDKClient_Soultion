#ifndef _UC_GROUP_PROXY_H_
#define _UC_GROUP_PROXY_H_

#include "UCGroupAbsProxy.h"


namespace eSDK {
	namespace UC {

/*lint -save -e1735*/
class UCGroupProxy : public UCGroupAbsProxy
{
private:
	UCGroupProxy();
	~UCGroupProxy();

public:
	static UCGroupProxy* Instance();
	static void Destroy();

public:
	virtual int AddFixedGroup(UCSDKFixedGroup& group);
	virtual int GetFixedGroupByID(UCSDKFixedGroup& group, const std::string& strGroupID);
	virtual int GetFixedGroupByUri(UCSDKFixedGroup& group, const std::string& strGroupUri);
	virtual int RemoveFixedGroup(const UCSDKFixedGroup& group);
	virtual int RefreshFixedGrouplist(UCSDKFixedGroupList& groupList);
	virtual int GetFixedGrouplist(UCSDKFixedGroupList& groupList);
	virtual int SearchFixedGroup(UCSDKFixedGroupList& groupList, 
		const std::string& groupNo, const std::string& groupName, int offset, int count);
	virtual int AddCustomGroup(UCSDKCustomGroup& group);
	virtual int AddFavoriteGroup(UCSDKFavoriteGroup& group);
	virtual int GetCustomGroupById(UCSDKCustomGroup& group, const std::string& strGroupID);
	virtual int GetCustomGrouplist(UCSDKCustomGroupList& groupList);
	virtual int RemoveCustomGroup(const UCSDKCustomGroup& group);
	virtual int RemoveFavoriteGroup(const UCSDKFavoriteGroup& group);

public:
	//FavoriteGroup
	virtual int AddContact(const UCSDKFavoriteGroup& group, UCSDKContact& _contact);
	virtual int RemoveContact(const UCSDKFavoriteGroup& group, const UCSDKContact& _contact) const;
	virtual int Rename(const UCSDKFavoriteGroup& group, const std::string& _name);
	virtual int GetContactlist(const UCSDKFavoriteGroup& group, UCSDKContactList& _contactlist);

	//CustomGroup
	virtual int AddContact(const UCSDKCustomGroup& group, UCSDKContact& _contact);
	virtual int RemoveContact(const UCSDKCustomGroup& group, const UCSDKContact& _contact) const;
	virtual int Rename(const UCSDKCustomGroup& group, const std::string& _name);
	virtual int GetContactlist(const UCSDKCustomGroup& group, UCSDKContactList& _contactlist);
	virtual int MoveUp(const UCSDKCustomGroup& group);
	virtual int MoveDown(const UCSDKCustomGroup& group);

	//FixedGroup
	virtual int AddContact(const UCSDKFixedGroup& group, UCSDKContact& _contact);
	virtual int RemoveContact(const UCSDKFixedGroup& group, const UCSDKContact& _contact) const;
	virtual int Rename(const UCSDKFixedGroup& group, const std::string& _name);
	virtual int GetContactlist(const UCSDKFixedGroup& group, UCSDKContactList& _contactlist);
	virtual int ChangeGroupInfo(const UCSDKFixedGroup& group);
	virtual int ChangeGroupOwner(const UCSDKFixedGroup& group, const UCSDKContact& _owner);
	virtual int Refresh(const UCSDKFixedGroup& group, UCSDKContactList& _contactlist);
	virtual int Refresh(const UCSDKFixedGroup& group, bool sync_ = true);
	virtual int AcceptInvitation(const UCSDKFixedGroup& group) const;
	virtual int RejectInvitation(const UCSDKFixedGroup& group) const;
	virtual int AcceptJoinReq(const UCSDKFixedGroup& group, const UCSDKContact& _contact) const; 
	virtual int RejectJoinReq(const UCSDKFixedGroup& group, const UCSDKContact& _contact) const;

public:
	int Init();
	int UnInit();

	//¸¨Öúº¯Êý
public:
	int GetFixedGroup(const UCSDKFixedGroup& group, uc::model::FixedGroup& fixedGroup) const;
	int SearchFixedGroup(const UCSDKFixedGroup& group, uc::model::FixedGroup& fixedGroup) const;
	static void CopyUCSDKFixedGroupToFixedGroup(const UCSDKFixedGroup& group, uc::model::FixedGroup& fixedGroup);
	static void CopyFixedGroupToUCSDKFixedGroup(const uc::model::FixedGroup& fixedGroup, UCSDKFixedGroup& group);
	static void CopyUCSDKCustomGroupToCustomGroup(const UCSDKCustomGroup& group, uc::model::CustomGroup& customGroup);
	static void CopyCustomGroupToUCSDKCustomGroup(const uc::model::CustomGroup& customGroup, UCSDKCustomGroup& group);
	static void CopyUCSDKFavoriteGroupToFavoriteGroup(const UCSDKFavoriteGroup& group, uc::model::FavoriteGroup& favoriteGroup);
	static void CopyFavoriteGroupToUCSDKFavoriteGroup(const uc::model::FavoriteGroup& favoriteGroup, UCSDKFavoriteGroup& group);

private:
	uc::model::UCClient* m_pUCClient;
	uc::model::ContactMgr* m_pContactMgr;

private:
	static UCGroupProxy* m_pUCGroupProxy;
};
/*lint -restore*/

}
}

#endif
