#ifndef _UC_STRUCT_COPY_HEADER_
#define _UC_STRUCT_COPY_HEADER_

#include "DataType.h"
#include "DataDef.h"

using namespace eSDK::UC;


class UCStructCopy
{
public:
	static void Copy_UCIMMessage(UCIMMessage& ucIM, const IMMessage& IM);
	static void Copy_UCContact(UCContact& ucContact, const UCSDKContact& contact);
	static void Copy_UCBookConf(UCBookConf& ucBookConf, const UCSDKBookConfInfo& bookConf);
	static void Copy_UCGroup(UCGroup& ucGroup, const UCSDKGroup& group);
	static void Copy_UCCustomGroup(UCCustomGroup& ucGroup, const UCSDKCustomGroup& group);
	static void Copy_UCFavoriteGroup(UCFavoriteGroup& ucGroup, const UCSDKFavoriteGroup& group);
	static void Copy_UCFixedGroup(UCFixedGroup& ucGroup, const UCSDKFixedGroup& group);
	static void Copy_UCVideoWindow(UCVideoWindow& ucWnd, const STVideoWindow& wnd);
	static void Copy_UCAudioVideoParam(UCAudioVideoParam& ucParam, const STAudioVideoParam& param);
	static void Copy_UCAccountList(UCAccountList& ucList, const AccountList& list);
	static void Copy_UCPublishInfoMap(UCPublishInfoMap& ucMap, const PublishInfoMap& map);
	static void Copy_UCBookConfList(UCBookConfList& ucList, const UCSDKBookConfList& list);
	static void Copy_UCContactList(UCContactList& ucList, const UCSDKContactList& list);
	static void Copy_UCFixedGroupList(UCFixedGroupList& ucList, const UCSDKFixedGroupList& list);
	static void Copy_UCCustomGroupList(UCCustomGroupList& ucList, const UCSDKCustomGroupList& list);
	static void Copy_UCConversationPropMap(UCConversationPropMap& ucMap, const ConversationPropMap& map);

public:
	static void Copy_IMMessage(IMMessage& IM, const UCIMMessage& ucIM);
	static void Copy_UCSDKContact(UCSDKContact& contact, const UCContact& ucContact);
	static void Copy_UCSDKBookConfInfo(UCSDKBookConfInfo& bookConf, const UCBookConf& ucBookConf);
	static void Copy_UCSDKGroup(UCSDKGroup& group, const UCGroup& ucGroup);
	static void Copy_UCSDKCustomGroup(UCSDKCustomGroup& group, const UCCustomGroup& ucGroup);
	static void Copy_UCSDKFavoriteGroup(UCSDKFavoriteGroup& group, const UCFavoriteGroup& ucGroup);
	static void Copy_UCSDKFixedGroup(UCSDKFixedGroup& group, const UCFixedGroup& ucGroup);
	static void Copy_STVideoWindow(STVideoWindow& wnd, const UCVideoWindow& ucWnd);
	static void Copy_STAudioVideoParam(STAudioVideoParam& param, const UCAudioVideoParam& ucParam);
	static void Copy_AccountList(AccountList& list, const UCAccountList& ucList);
	static void Copy_PublishInfoMap(PublishInfoMap& map, const UCPublishInfoMap& ucMap);
	static void Copy_UCSDKBookConfList(UCSDKBookConfList& list, const UCBookConfList& ucList);
	static void Copy_UCSDKContactList(UCSDKContactList& list, const UCContactList& ucList);
	static void Copy_UCSDKFixedGroupList(UCSDKFixedGroupList& list, const UCFixedGroupList& ucList);
	static void Copy_UCSDKCustomGroupList(UCSDKCustomGroupList& list, const UCCustomGroupList& ucList);
	static void Copy_ConversationPropMap(ConversationPropMap& map, const UCConversationPropMap& ucMap);

public:
	static void Free_UCBookConf(UCBookConf& ucBookConf);
	static void Free_UCAccountList(UCAccountList& ucList);
	static void Free_UCBookConfList(UCBookConfList& ucList);
	static void Free_UCContactList(UCContactList& ucList);
	static void Free_UCFixedGroupList(UCFixedGroupList& ucList);
	static void Free_UCCustomGroupList(UCCustomGroupList& ucList);

public:
	static void UCMemCopy(char* c, const std::string& str, size_t size);
};

#endif
