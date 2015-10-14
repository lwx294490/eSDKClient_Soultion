#ifndef _UCSERVICE_HEAD_FILE_
#define _UCSERVICE_HEAD_FILE_

#include "UCSDKAbsProxy.h"
#include "UCContactMgrAbsProxy.h"
#include "UCGroupAbsProxy.h"
#include "UCIMAbsProxy.h"
#include "UCMeetingAbsProxy.h"
#include "UCPublicAbsProxy.h"
#include "UCSignalRecvAbsProxy.h"
#include "UCVoIPAbsProxy.h"


namespace eSDK {
	namespace UC {


class ProductUCSDK
{
public:
	virtual UCSDKAbsProxy* GetUCSDKAbsProxy() = 0;
	virtual UCContactMgrAbsProxy* GetUCContactMgrAbsProxy() = 0;
	virtual UCGroupAbsProxy* GetUCGroupAbsProxy() = 0;
	virtual UCIMAbsProxy* GetUCIMAbsProxy() = 0;
	virtual UCMeetingAbsProxy* GetUCMeetingAbsProxy() = 0;
	virtual UCPublicAbsProxy* GetUCPublicAbsProxy() = 0;
	virtual UCVoIPAbsProxy* GetUCVoIPAbsProxy() = 0;
};

}
}

#endif
