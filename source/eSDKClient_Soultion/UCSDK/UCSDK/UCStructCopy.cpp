//lint -e830
//lint -e850
#include "stdafx.h"
#include "UCStructCopy.h"


void UCStructCopy::Copy_UCIMMessage(UCIMMessage& ucIM, const IMMessage& IM)
{
	UCMemCopy(ucIM.origin, IM.origin, sizeof(ucIM.origin));
	UCMemCopy(ucIM.target, IM.target, sizeof(ucIM.target));
	UCMemCopy(ucIM.content, IM.content, sizeof(ucIM.content));
	UCMemCopy(ucIM.rcv_time, IM.rcv_time, sizeof(ucIM.rcv_time));
	UCMemCopy(ucIM.name, IM.name, sizeof(ucIM.name));
	UCMemCopy(ucIM.msgid, IM.msgid, sizeof(ucIM.msgid));
	ucIM.chatType = IM.chatType;
}
void UCStructCopy::Copy_UCContact(UCContact& ucContact, const UCSDKContact& contact)
{
	UCMemCopy(ucContact.id_, contact.id_, sizeof(ucContact.id_));
	UCMemCopy(ucContact.uri_, contact.uri_, sizeof(ucContact.uri_));
	UCMemCopy(ucContact.ucAcc_, contact.ucAcc_, sizeof(ucContact.ucAcc_));
	UCMemCopy(ucContact.staffNo_, contact.staffNo_, sizeof(ucContact.staffNo_));
	UCMemCopy(ucContact.name_, contact.name_, sizeof(ucContact.name_));
	UCMemCopy(ucContact.nickName_, contact.nickName_, sizeof(ucContact.nickName_));
	UCMemCopy(ucContact.qpinyin_, contact.qpinyin_, sizeof(ucContact.qpinyin_));
	UCMemCopy(ucContact.spinyin_, contact.spinyin_, sizeof(ucContact.spinyin_));
	UCMemCopy(ucContact.homePhone_, contact.homePhone_, sizeof(ucContact.homePhone_));
	UCMemCopy(ucContact.officePhone_, contact.officePhone_, sizeof(ucContact.officePhone_));
	UCMemCopy(ucContact.mobile_, contact.mobile_, sizeof(ucContact.mobile_));
	UCMemCopy(ucContact.otherPhone_, contact.otherPhone_, sizeof(ucContact.otherPhone_));
	UCMemCopy(ucContact.address_, contact.address_, sizeof(ucContact.address_));
	UCMemCopy(ucContact.email_, contact.email_, sizeof(ucContact.email_));
	UCMemCopy(ucContact.fax_, contact.fax_, sizeof(ucContact.fax_));
	UCMemCopy(ucContact.corpName_, contact.corpName_, sizeof(ucContact.corpName_));
	UCMemCopy(ucContact.deptName_, contact.deptName_, sizeof(ucContact.deptName_));
	UCMemCopy(ucContact.webSite_, contact.webSite_, sizeof(ucContact.webSite_));
	UCMemCopy(ucContact.desc_, contact.desc_, sizeof(ucContact.desc_));
	UCMemCopy(ucContact.zip_, contact.zip_, sizeof(ucContact.zip_));
	UCMemCopy(ucContact.signature_, contact.signature_, sizeof(ucContact.signature_));
	UCMemCopy(ucContact.imageID_, contact.imageID_, sizeof(ucContact.imageID_));
	UCMemCopy(ucContact.position_, contact.position_, sizeof(ucContact.position_));
	UCMemCopy(ucContact.location_, contact.location_, sizeof(ucContact.location_));
	UCMemCopy(ucContact.tzone_, contact.tzone_, sizeof(ucContact.tzone_));
	UCMemCopy(ucContact.avtool_, contact.avtool_, sizeof(ucContact.avtool_));
	UCMemCopy(ucContact.device_, contact.device_, sizeof(ucContact.device_));
	UCMemCopy(ucContact.terminalType_, contact.terminalType_, sizeof(ucContact.terminalType_));
}
void UCStructCopy::Copy_UCBookConf(UCBookConf& ucBookConf, const UCSDKBookConfInfo& bookConf)
{
	UCMemCopy(ucBookConf.topic, bookConf.topic, sizeof(ucBookConf.topic));
	UCMemCopy(ucBookConf.meetingtime, bookConf.meetingtime, sizeof(ucBookConf.meetingtime));
	UCMemCopy(ucBookConf.convener, bookConf.convener, sizeof(ucBookConf.convener));
	UCMemCopy(ucBookConf.convenername, bookConf.convenername, sizeof(ucBookConf.convenername));
	UCMemCopy(ucBookConf.accessnum, bookConf.accessnum, sizeof(ucBookConf.accessnum));
	UCMemCopy(ucBookConf.securitycode, bookConf.securitycode, sizeof(ucBookConf.securitycode));
	UCMemCopy(ucBookConf.iscycle, bookConf.iscycle, sizeof(ucBookConf.iscycle));
	UCMemCopy(ucBookConf.startdate, bookConf.startdate, sizeof(ucBookConf.startdate));
	UCMemCopy(ucBookConf.validityperiod, bookConf.validityperiod, sizeof(ucBookConf.validityperiod));
	UCMemCopy(ucBookConf.content, bookConf.content, sizeof(ucBookConf.content));
	UCMemCopy(ucBookConf.chairmanpwd, bookConf.chairmanpwd, sizeof(ucBookConf.chairmanpwd));
	UCMemCopy(ucBookConf.partmanpwd, bookConf.partmanpwd, sizeof(ucBookConf.partmanpwd));
	UCMemCopy(ucBookConf.recordcode, bookConf.recordcode, sizeof(ucBookConf.recordcode));
	UCMemCopy(ucBookConf.funcbits, bookConf.funcbits, sizeof(ucBookConf.funcbits));
	UCMemCopy(ucBookConf.mediaBits, bookConf.mediaBits, sizeof(ucBookConf.mediaBits));
	UCMemCopy(ucBookConf.confid, bookConf.confid, sizeof(ucBookConf.confid));
	UCMemCopy(ucBookConf.confStyle, bookConf.confStyle, sizeof(ucBookConf.confStyle));
	ucBookConf.confType = bookConf.confType;
	//ucBookConf.attendeelist字段无效
	ucBookConf.attendeelist = NULL;
}
void UCStructCopy::Copy_UCGroup(UCGroup& ucGroup, const UCSDKGroup& group)
{
	UCMemCopy(ucGroup.name_, group.name_, sizeof(ucGroup.name_));
	UCMemCopy(ucGroup.id_, group.id_, sizeof(ucGroup.id_));
	ucGroup.type_ = group.type_;
	ucGroup.readonly_ = group.readonly_;
}
void UCStructCopy::Copy_UCCustomGroup(UCCustomGroup& ucGroup, const UCSDKCustomGroup& group)
{
	UCMemCopy(ucGroup.name_, group.name_, sizeof(ucGroup.name_));
	UCMemCopy(ucGroup.id_, group.id_, sizeof(ucGroup.id_));
	ucGroup.type_ = group.type_;
	ucGroup.readonly_ = group.readonly_;
	ucGroup.indexno_ = group.indexno_;
}
void UCStructCopy::Copy_UCFavoriteGroup(UCFavoriteGroup& ucGroup, const UCSDKFavoriteGroup& group)
{
	UCMemCopy(ucGroup.name_, group.name_, sizeof(ucGroup.name_));
	UCMemCopy(ucGroup.id_, group.id_, sizeof(ucGroup.id_));
	ucGroup.type_ = group.type_;
	ucGroup.readonly_ = group.readonly_;
}
void UCStructCopy::Copy_UCFixedGroup(UCFixedGroup& ucGroup, const UCSDKFixedGroup& group)
{
	UCMemCopy(ucGroup.name_, group.name_, sizeof(ucGroup.name_));
	UCMemCopy(ucGroup.id_, group.id_, sizeof(ucGroup.id_));
	UCMemCopy(ucGroup.creator_, group.creator_, sizeof(ucGroup.creator_));
	UCMemCopy(ucGroup.uri_, group.uri_, sizeof(ucGroup.uri_));
	UCMemCopy(ucGroup.groupno_, group.groupno_, sizeof(ucGroup.groupno_));
	UCMemCopy(ucGroup.desc_, group.desc_, sizeof(ucGroup.desc_));
	UCMemCopy(ucGroup.bulletin_, group.bulletin_, sizeof(ucGroup.bulletin_));
	UCMemCopy(ucGroup.owneruri_, group.owneruri_, sizeof(ucGroup.owneruri_));
	UCMemCopy(ucGroup.needpermit_, group.needpermit_, sizeof(ucGroup.needpermit_));
	ucGroup.type_ = group.type_;
	ucGroup.readonly_ = group.readonly_;
	ucGroup.capacity_ = group.capacity_;
}
void UCStructCopy::Copy_UCVideoWindow(UCVideoWindow& ucWnd, const STVideoWindow& wnd)
{
	ucWnd.hWnd = wnd.hWnd;
	ucWnd.left = wnd.left;
	ucWnd.top = wnd.top;
	ucWnd.width = wnd.width;
	ucWnd.height = wnd.height;
}
void UCStructCopy::Copy_UCAudioVideoParam(UCAudioVideoParam& ucParam, const STAudioVideoParam& param)
{
	UCMemCopy(ucParam.caller_, param.caller_, sizeof(ucParam.caller_));
	UCMemCopy(ucParam.callername_, param.callername_, sizeof(ucParam.callername_));
	UCMemCopy(ucParam.lineindex_, param.lineindex_, sizeof(ucParam.lineindex_));
	ucParam.callalertinfo_ = param.callalertinfo_;
	ucParam.autoanswerdelay = param.autoanswerdelay;
	ucParam.isvideo_ = param.isvideo_;
	ucParam.callmode_ = param.callmode_;
	ucParam.isdataconf_ = param.isdataconf_;
}
void UCStructCopy::Copy_UCAccountList(UCAccountList& ucList, const AccountList& list)
{
	size_t size = list.size();
	if (0 == size)
	{
		if (NULL != ucList.account)
		{
			free(ucList.account);
			ucList.account = NULL;
		}

		ucList.iFrom = 0;
		ucList.iTo = -1;
		ucList.iTotal = 0;
		return;
	}

	ucList.iFrom = 0;
	ucList.iTo = (int)size - 1;
	ucList.iTotal = (int)size;

	if (NULL != ucList.account)
	{
		free(ucList.account);
		ucList.account = NULL;
	}
	ucList.account = (UCAccount*)malloc(sizeof(UCAccount)*size);
	if (NULL == ucList.account)
	{
		ucList.iFrom = 0;
		ucList.iTo = -1;
		ucList.iTotal = 0;
		return;
	}
	for (size_t i=0; i<size; i++)
	{
		UCMemCopy(ucList.account[i].str, list[i], sizeof(ucList.account[i].str));		
	}
}
void UCStructCopy::Copy_UCPublishInfoMap(UCPublishInfoMap& ucMap, const PublishInfoMap& map)
{
	ctk::MemSet(ucMap.publish, 0, sizeof(ucMap.publish));

	PublishInfoMap::const_iterator it = map.begin();
	for (; it != map.end(); it++)
	{
		if (!it->second.empty())
		{
			int index = it->first;
			UCMemCopy(ucMap.publish[index], it->second, sizeof(char)*PUB_INFO_LENGTH);
		}
	}
}
void UCStructCopy::Copy_UCBookConfList(UCBookConfList& ucList, const UCSDKBookConfList& list)
{
	size_t size = list.size();
	if (0 == size)
	{
		ucList.bookConf = NULL;
		ucList.iFrom = 0;
		ucList.iTo = -1;
		ucList.iTotal = 0;
		return;
	}

	ucList.iFrom = 0;
	ucList.iTo = (int)size-1;
	ucList.iTotal = (int)size;

	ucList.bookConf = (UCBookConf*)malloc(sizeof(UCBookConf)*size);
	if (NULL == ucList.bookConf)
	{
		ucList.iFrom = 0;
		ucList.iTo = -1;
		ucList.iTotal = 0;
		return;
	}
	for (size_t i=0; i<size; i++)
	{
		Copy_UCBookConf(ucList.bookConf[i], list[i]);
	}
}
void UCStructCopy::Copy_UCContactList(UCContactList& ucList, const UCSDKContactList& list)
{
	size_t size = list.size();
	if (0 == size)
	{
		ucList.contact = NULL;
		ucList.iFrom = 0;
		ucList.iTo = -1;
		ucList.iTotal = 0;
		return;
	}

	ucList.iFrom = 0;
	ucList.iTo = (int)size-1;
	ucList.iTotal = (int)size;

	ucList.contact = (UCContact*)malloc(sizeof(UCContact)*size);
	if (NULL == ucList.contact)
	{
		ucList.iFrom = 0;
		ucList.iTo = -1;
		ucList.iTotal = 0;
		return;
	}
	for (size_t i=0; i<size; i++)
	{
		Copy_UCContact(ucList.contact[i], list[i]);
	}
}
void UCStructCopy::Copy_UCFixedGroupList(UCFixedGroupList& ucList, const UCSDKFixedGroupList& list)
{
	size_t size = list.size();
	if (0 == size)
	{
		ucList.group = NULL;
		ucList.iFrom = 0;
		ucList.iTo = -1;
		ucList.iTotal = 0;
		return;
	}

	ucList.iFrom = 0;
	ucList.iTo = (int)size-1;
	ucList.iTotal = (int)size;

	ucList.group = (UCFixedGroup*)malloc(sizeof(UCFixedGroup)*size);
	if (NULL == ucList.group)
	{
		ucList.iFrom = 0;
		ucList.iTo = -1;
		ucList.iTotal = 0;
		return;
	}
	for (size_t i=0; i<size; i++)
	{
		Copy_UCFixedGroup(ucList.group[i], list[i]);
	}
}
void UCStructCopy::Copy_UCCustomGroupList(UCCustomGroupList& ucList, const UCSDKCustomGroupList& list)
{
	size_t size = list.size();
	if (0 == size)
	{
		ucList.group = NULL;
		ucList.iFrom = 0;
		ucList.iTo = -1;
		ucList.iTotal = 0;
		return;
	}

	ucList.iFrom = 0;
	ucList.iTo = (int)size-1;
	ucList.iTotal = (int)size;

	ucList.group = (UCCustomGroup*)malloc(sizeof(UCCustomGroup)*size);
	if (NULL == ucList.group)
	{
		ucList.iFrom = 0;
		ucList.iTo = -1;
		ucList.iTotal = 0;
		return;
	}
	for (size_t i=0; i<size; i++)
	{
		Copy_UCCustomGroup(ucList.group[i], list[i]);
	}
}
void UCStructCopy::Copy_UCConversationPropMap(UCConversationPropMap& ucMap, const ConversationPropMap& map)
{
	ctk::MemSet(ucMap.prop, 0, sizeof(ucMap.prop));

	ConversationPropMap::const_iterator it = map.begin();
	for (; it != map.end(); it++)
	{
		if (!it->second.empty())
		{
			UCMemCopy(ucMap.prop[it->first], it->second, sizeof(char)*PROP_INFO_LENGTH);
		}
	}
}


void UCStructCopy::Copy_IMMessage(IMMessage& IM, const UCIMMessage& ucIM)
{
	IM.origin						= ucIM.origin;
	IM.target						= ucIM.target;
	IM.content						= ucIM.content;
	IM.rcv_time						= ucIM.rcv_time;
	IM.name							= ucIM.name;
	IM.msgid						= ucIM.msgid;
	IM.chatType						= (INSTANT_MSG_TYPE_E)ucIM.chatType;
}
void UCStructCopy::Copy_UCSDKContact(UCSDKContact& contact, const UCContact& ucContact)
{
	contact.id_						= ucContact.id_;
	contact.uri_					= ucContact.uri_;
	contact.ucAcc_					= ucContact.ucAcc_;
	contact.staffNo_				= ucContact.staffNo_;
	contact.name_					= ucContact.name_;
	contact.nickName_				= ucContact.nickName_;
	contact.qpinyin_				= ucContact.qpinyin_;
	contact.spinyin_				= ucContact.spinyin_;
	contact.homePhone_				= ucContact.homePhone_;
	contact.officePhone_			= ucContact.officePhone_;
	contact.mobile_					= ucContact.mobile_;
	contact.otherPhone_				= ucContact.otherPhone_;
	contact.address_				= ucContact.address_;
	contact.email_					= ucContact.email_;
	contact.fax_					= ucContact.fax_;
	contact.corpName_				= ucContact.corpName_;
	contact.deptName_				= ucContact.deptName_;
	contact.webSite_				= ucContact.webSite_;
	contact.desc_					= ucContact.desc_;
	contact.zip_					= ucContact.zip_;
	contact.signature_				= ucContact.signature_;
	contact.imageID_				= ucContact.imageID_;
	contact.position_				= ucContact.position_;
	contact.location_				= ucContact.location_;
	contact.tzone_					= ucContact.tzone_;
	contact.avtool_					= ucContact.avtool_;
	contact.device_					= ucContact.device_;
	contact.terminalType_			= ucContact.terminalType_;
}
void UCStructCopy::Copy_UCSDKBookConfInfo(UCSDKBookConfInfo& bookConf, const UCBookConf& ucBookConf)
{
	bookConf.topic					= ucBookConf.topic;
	bookConf.meetingtime			= ucBookConf.meetingtime;
	bookConf.convener				= ucBookConf.convener;
	bookConf.convenername			= ucBookConf.convenername;

	//bookConf.attendeelist无效
	bookConf.attendeelist.clear();

	bookConf.accessnum				= ucBookConf.accessnum;
	bookConf.securitycode			= ucBookConf.securitycode;
	bookConf.iscycle				= ucBookConf.iscycle;
	bookConf.startdate				= ucBookConf.startdate;
	bookConf.validityperiod			= ucBookConf.validityperiod;
	bookConf.content				= ucBookConf.content;
	bookConf.chairmanpwd			= ucBookConf.chairmanpwd;
	bookConf.partmanpwd				= ucBookConf.partmanpwd;
	bookConf.recordcode				= ucBookConf.recordcode;
	bookConf.funcbits				= ucBookConf.funcbits;
	bookConf.mediaBits				= ucBookConf.mediaBits;
	bookConf.confType				= ucBookConf.confType;
	bookConf.confid					= ucBookConf.confid;
	bookConf.confStyle				= ucBookConf.confStyle;
}
void UCStructCopy::Copy_UCSDKGroup(UCSDKGroup& group, const UCGroup& ucGroup)
{
	group.name_						= ucGroup.name_;
	group.id_						= ucGroup.id_;
	group.type_						= ucGroup.type_;
	if (0 == ucGroup.readonly_)
	{
		group.readonly_				= false;
	}
	else
	{
		group.readonly_				= true;
	}
}
void UCStructCopy::Copy_UCSDKCustomGroup(UCSDKCustomGroup& group, const UCCustomGroup& ucGroup)
{
	group.name_						= ucGroup.name_;
	group.id_						= ucGroup.id_;
	group.type_						= ucGroup.type_;
	group.indexno_					= ucGroup.indexno_;
	if (0 == ucGroup.readonly_)
	{
		group.readonly_				= false;
	}
	else
	{
		group.readonly_				= true;
	}
}
void UCStructCopy::Copy_UCSDKFavoriteGroup(UCSDKFavoriteGroup& group, const UCFavoriteGroup& ucGroup)
{
	group.name_						= ucGroup.name_;
	group.id_						= ucGroup.id_;
	group.type_						= ucGroup.type_;
	if (0 == ucGroup.readonly_)
	{
		group.readonly_				= false;
	}
	else
	{
		group.readonly_				= true;
	}
}
void UCStructCopy::Copy_UCSDKFixedGroup(UCSDKFixedGroup& group, const UCFixedGroup& ucGroup)
{
	group.name_						= ucGroup.name_;
	group.id_						= ucGroup.id_;
	group.type_						= ucGroup.type_;
	if (0 == ucGroup.readonly_)
	{
		group.readonly_				= false;
	}
	else
	{
		group.readonly_				= true;
	}
	group.creator_					= ucGroup.creator_;
	group.uri_						= ucGroup.uri_;
	group.groupno_					= ucGroup.groupno_;
	group.desc_						= ucGroup.desc_;
	group.bulletin_					= ucGroup.bulletin_;
	group.owneruri_					= ucGroup.owneruri_;
	group.capacity_					= ucGroup.capacity_;
	group.needpermit_				= ucGroup.needpermit_;
}
void UCStructCopy::Copy_STVideoWindow(STVideoWindow& wnd, const UCVideoWindow& ucWnd)
{
	wnd.hWnd						= ucWnd.hWnd;
	wnd.left						= ucWnd.left;
	wnd.top							= ucWnd.top;
	wnd.width						= ucWnd.width;
	wnd.height						= ucWnd.height;
}
void UCStructCopy::Copy_STAudioVideoParam(STAudioVideoParam& param, const UCAudioVideoParam& ucParam)
{
	param.caller_					= ucParam.caller_;
	param.callername_				= ucParam.callername_;
	param.callalertinfo_			= ucParam.callalertinfo_;
	param.autoanswerdelay			= ucParam.autoanswerdelay;
	param.lineindex_				= ucParam.lineindex_;
	if (0 == ucParam.isvideo_)
	{
		param.isvideo_				= false;
	}
	else
	{
		param.isvideo_				= true;
	}
	if (0 == ucParam.callmode_)
	{
		param.callmode_				= false;
	}
	else
	{
		param.callmode_				= true;
	}
	if (0 == ucParam.isdataconf_)
	{
		param.isdataconf_			= false;
	}
	else
	{
		param.isdataconf_			= true;
	}
}
void UCStructCopy::Copy_AccountList(AccountList& list, const UCAccountList& ucList)
{
	int iBufNum = ucList.iTo + 1 - ucList.iFrom;
	if (0 >= iBufNum)
	{
		return;
	}

	if (NULL == ucList.account)
	{
		return;
	}

	for (int i=0; i<iBufNum; i++)
	{
		std::string strAcc = ucList.account[i].str;
		list.push_back(strAcc);
	}
}
void UCStructCopy::Copy_PublishInfoMap(PublishInfoMap& map, const UCPublishInfoMap& ucMap)
{
	for (int i=0; i<PUB_LENGTH; i++)
	{
		if (0 != ucMap.publish[i][0])
		{
			std::string strPub = ucMap.publish[i];
			(void)map.insert(std::make_pair((PUB_CONTACT_INFO_TYPE_E)i, strPub));
		}
	}
}
//lint !e830
//lint !e850
void UCStructCopy::Copy_UCSDKBookConfList(UCSDKBookConfList& list, const UCBookConfList& ucList)
{
	int iBufNum = ucList.iTo + 1 - ucList.iFrom;
	if (0 >= iBufNum)
	{
		return;
	}

	if (NULL == ucList.bookConf)
	{
		return;
	}

	for (int i=0; i<iBufNum; i++)
	{
		UCSDKBookConfInfo bookinfo;
		Copy_UCSDKBookConfInfo(bookinfo, ucList.bookConf[i]);
		list.push_back(bookinfo);
	}
}
void UCStructCopy::Copy_UCSDKContactList(UCSDKContactList& list, const UCContactList& ucList)
{
	int iBufNum = ucList.iTo + 1 - ucList.iFrom;
	if (0 >= iBufNum)
	{
		return;
	}

	if (NULL == ucList.contact)
	{
		return;
	}

	for (int i=0; i<iBufNum; i++)
	{
		UCSDKContact contact;
		Copy_UCSDKContact(contact, ucList.contact[i]);
		list.push_back(contact);
	}
}
void UCStructCopy::Copy_UCSDKFixedGroupList(UCSDKFixedGroupList& list, const UCFixedGroupList& ucList)
{
	int iBufNum = ucList.iTo + 1 - ucList.iFrom;
	if (0 >= iBufNum)
	{
		return;
	}

	if (NULL == ucList.group)
	{
		return;
	}

	for (int i=0; i<iBufNum; i++)
	{
		UCSDKFixedGroup group;
		Copy_UCSDKFixedGroup(group, ucList.group[i]);
		list.push_back(group);
	}
}
void UCStructCopy::Copy_UCSDKCustomGroupList(UCSDKCustomGroupList& list, const UCCustomGroupList& ucList)
{
	int iBufNum = ucList.iTo + 1 - ucList.iFrom;
	if (0 >= iBufNum)
	{
		return;
	}

	if (NULL == ucList.group)
	{
		return;
	}

	for (int i=0; i<iBufNum; i++)
	{
		UCSDKCustomGroup group;
		Copy_UCSDKCustomGroup(group, ucList.group[i]);
		list.push_back(group);
	}
}
void UCStructCopy::Copy_ConversationPropMap(ConversationPropMap& map, const UCConversationPropMap& ucMap)
{
	for (int i=0; i<PROP_LENGTH; i++)
	{
		if (0 != ucMap.prop[i][0])
		{
			std::string strProp = ucMap.prop[i];
			(void)map.insert(std::make_pair((CONVERSATION_PROPERTY_E)i, strProp));
		}
	}
}
//lint !e830
//lint !e850

void UCStructCopy::Free_UCBookConf(UCBookConf& ucBookConf)
{
	if (NULL != ucBookConf.attendeelist)
	{
		free(ucBookConf.attendeelist);
		ucBookConf.attendeelist = NULL;
	}
}
void UCStructCopy::Free_UCAccountList(UCAccountList& ucList)
{
	if (NULL != ucList.account)
	{
		free(ucList.account);
		ucList.account = NULL;
	}
}
void UCStructCopy::Free_UCBookConfList(UCBookConfList& ucList)
{
	if (NULL != ucList.bookConf)
	{
		free(ucList.bookConf);
		ucList.bookConf = NULL;
	}
}
void UCStructCopy::Free_UCContactList(UCContactList& ucList)
{
	if (NULL != ucList.contact)
	{
		free(ucList.contact);
		ucList.contact = NULL;
	}
}
void UCStructCopy::Free_UCFixedGroupList(UCFixedGroupList& ucList)
{
	if (NULL != ucList.group)
	{
		free(ucList.group);
		ucList.group = NULL;
	}
}
void UCStructCopy::Free_UCCustomGroupList(UCCustomGroupList& ucList)
{
	if (NULL != ucList.group)
	{
		free(ucList.group);
		ucList.group = NULL;
	}
}


void UCStructCopy::UCMemCopy(char* dest, const std::string& str, size_t size)
{
	if (NULL == dest || size == 0)
	{
		return;
	}

	ctk::MemSet(dest, 0, size);
	ctk::MemCopy(dest, str.c_str(), (str.size()<size) ? (str.size()) : (size-1));
}
