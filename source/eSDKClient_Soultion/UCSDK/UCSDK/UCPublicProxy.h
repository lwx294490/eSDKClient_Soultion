#ifndef _UC_PUBLIC_PROXY_H_
#define _UC_PUBLIC_PROXY_H_

#include "UCPublicAbsProxy.h"


namespace eSDK {
	namespace UC {


class UCPublicProxy : public UCPublicAbsProxy
{
private:
	UCPublicProxy();
	~UCPublicProxy();

public:
	static UCPublicProxy* Instance();
	static void Destroy();

public:
	virtual int PublishSelfInformation(const PublishInfoMap& publishInfoMap);
	virtual int GetContactStatus(const std::string& _uri, int& _status);

public:
	int Init();
	int UnInit();

private:
	uc::model::UCClient* m_pUCClient;

private:
	static UCPublicProxy* m_pUCPublicProxy;
};

}
}

#endif
