#include "UCService.h"
#include "eSDKClientPlatformExecute.h"
#include "eSDKLog.h"


namespace eSDK {
	namespace UC {


UCSDKAbsProxy::UCSDKAbsProxy()
{

}
UCSDKAbsProxy::~UCSDKAbsProxy()
{

}
UCSDKAbsProxy* UCSDKAbsProxy::GetInstance()
{
	eSDKClientPlatformExecute* peSDKClientPlatformExecute = eSDKClientPlatformExecute::Instance();
	if (NULL == peSDKClientPlatformExecute)
	{
		ERROR_LOG() << "Get eSDKClientPlatformExecute instance failed.";
		return NULL;
	}

	ProductUCSDK* pProductUCSDK = dynamic_cast<ProductUCSDK*>(peSDKClientPlatformExecute->getServiceByName("UCSDK"));
	if (NULL == pProductUCSDK)
	{
		ERROR_LOG() << "getServiceByName failed.";
		return NULL;
	}
	
	return pProductUCSDK->GetUCSDKAbsProxy();
}
void UCSDKAbsProxy::ReleaseInstance()
{

}


UCContactMgrAbsProxy::UCContactMgrAbsProxy()
{

}
UCContactMgrAbsProxy::~UCContactMgrAbsProxy()
{

}
UCContactMgrAbsProxy* UCContactMgrAbsProxy::GetInstance()
{
	eSDKClientPlatformExecute* peSDKClientPlatformExecute = eSDKClientPlatformExecute::Instance();
	if (NULL == peSDKClientPlatformExecute)
	{
		ERROR_LOG() << "Get eSDKClientPlatformExecute instance failed.";
		return NULL;
	}

	ProductUCSDK* pProductUCSDK = dynamic_cast<ProductUCSDK*>(peSDKClientPlatformExecute->getServiceByName("UCSDK"));
	if (NULL == pProductUCSDK)
	{
		ERROR_LOG() << "getServiceByName failed.";
		return NULL;
	}

	return pProductUCSDK->GetUCContactMgrAbsProxy();
}
void UCContactMgrAbsProxy::ReleaseInstance()
{

}


UCGroupAbsProxy::UCGroupAbsProxy()
{

}
UCGroupAbsProxy::~UCGroupAbsProxy()
{

}
UCGroupAbsProxy* UCGroupAbsProxy::GetInstance()
{
	eSDKClientPlatformExecute* peSDKClientPlatformExecute = eSDKClientPlatformExecute::Instance();
	if (NULL == peSDKClientPlatformExecute)
	{
		ERROR_LOG() << "Get eSDKClientPlatformExecute instance failed.";
		return NULL;
	}

	ProductUCSDK* pProductUCSDK = dynamic_cast<ProductUCSDK*>(peSDKClientPlatformExecute->getServiceByName("UCSDK"));
	if (NULL == pProductUCSDK)
	{
		ERROR_LOG() << "getServiceByName failed.";
		return NULL;
	}

	return pProductUCSDK->GetUCGroupAbsProxy();
}
void UCGroupAbsProxy::ReleaseInstance()
{

}


UCIMAbsProxy::UCIMAbsProxy()
{

}
UCIMAbsProxy::~UCIMAbsProxy()
{

}
UCIMAbsProxy* UCIMAbsProxy::GetInstance()
{
	eSDKClientPlatformExecute* peSDKClientPlatformExecute = eSDKClientPlatformExecute::Instance();
	if (NULL == peSDKClientPlatformExecute)
	{
		ERROR_LOG() << "Get eSDKClientPlatformExecute instance failed.";
		return NULL;
	}

	ProductUCSDK* pProductUCSDK = dynamic_cast<ProductUCSDK*>(peSDKClientPlatformExecute->getServiceByName("UCSDK"));
	if (NULL == pProductUCSDK)
	{
		ERROR_LOG() << "getServiceByName failed.";
		return NULL;
	}

	return pProductUCSDK->GetUCIMAbsProxy();
}
void UCIMAbsProxy::ReleaseInstance()
{

}


UCMeetingAbsProxy::UCMeetingAbsProxy()
{

}
UCMeetingAbsProxy::~UCMeetingAbsProxy()
{

}
UCMeetingAbsProxy* UCMeetingAbsProxy::GetInstance()
{
	eSDKClientPlatformExecute* peSDKClientPlatformExecute = eSDKClientPlatformExecute::Instance();
	if (NULL == peSDKClientPlatformExecute)
	{
		ERROR_LOG() << "Get eSDKClientPlatformExecute instance failed.";
		return NULL;
	}

	ProductUCSDK* pProductUCSDK = dynamic_cast<ProductUCSDK*>(peSDKClientPlatformExecute->getServiceByName("UCSDK"));
	if (NULL == pProductUCSDK)
	{
		ERROR_LOG() << "getServiceByName failed.";
		return NULL;
	}

	return pProductUCSDK->GetUCMeetingAbsProxy();
}
void UCMeetingAbsProxy::ReleaseInstance()
{

}


UCPublicAbsProxy::UCPublicAbsProxy()
{

}
UCPublicAbsProxy::~UCPublicAbsProxy()
{

}
UCPublicAbsProxy* UCPublicAbsProxy::GetInstance()
{
	eSDKClientPlatformExecute* peSDKClientPlatformExecute = eSDKClientPlatformExecute::Instance();
	if (NULL == peSDKClientPlatformExecute)
	{
		ERROR_LOG() << "Get eSDKClientPlatformExecute instance failed.";
		return NULL;
	}

	ProductUCSDK* pProductUCSDK = dynamic_cast<ProductUCSDK*>(peSDKClientPlatformExecute->getServiceByName("UCSDK"));
	if (NULL == pProductUCSDK)
	{
		ERROR_LOG() << "getServiceByName failed.";
		return NULL;
	}

	return pProductUCSDK->GetUCPublicAbsProxy();
}
void UCPublicAbsProxy::ReleaseInstance()
{

}


UCVoIPAbsProxy::UCVoIPAbsProxy()
{

}
UCVoIPAbsProxy::~UCVoIPAbsProxy()
{

}
UCVoIPAbsProxy* UCVoIPAbsProxy::GetInstance()
{
	eSDKClientPlatformExecute* peSDKClientPlatformExecute = eSDKClientPlatformExecute::Instance();
	if (NULL == peSDKClientPlatformExecute)
	{
		ERROR_LOG() << "Get eSDKClientPlatformExecute instance failed.";
		return NULL;
	}

	ProductUCSDK* pProductUCSDK = dynamic_cast<ProductUCSDK*>(peSDKClientPlatformExecute->getServiceByName("UCSDK"));
	if (NULL == pProductUCSDK)
	{
		ERROR_LOG() << "getServiceByName failed.";
		return NULL;
	}

	return pProductUCSDK->GetUCVoIPAbsProxy();
}
void UCVoIPAbsProxy::ReleaseInstance()
{

}

}
}
