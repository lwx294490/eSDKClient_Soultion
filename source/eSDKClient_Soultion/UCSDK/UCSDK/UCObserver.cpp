#include "stdAfx.h"
#include "UCObserver.h"
#include "UCVoIPProxy.h"


namespace eSDK {
	namespace UC {


UCObserver::UCObserver()
{

}

bool UCObserver::OnNotification(void* _item)
{
	if(NULL == _item)
	{
		return false;
	}

	if (NULL == UCVoIPProxy::Instance())
	{
		return false;
	}
	ConversationMgr* pConvMgr = UCVoIPProxy::Instance()->GetConvMgr();
	if(NULL == pConvMgr)
	{
		return false;
	}

	if(pConvMgr->HandleConversationNotify(_item))
	{
		return true;
	}
	else
	{
		return false;
	}	
}

}
}
