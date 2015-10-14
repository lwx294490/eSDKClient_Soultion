#ifndef _UC_OBSERVER_H_
#define _UC_OBSERVER_H_


namespace eSDK {
	namespace UC {


//m_ObTest为界面实现类，实现SDK抛到上层的消息在单线程处理
class UCObserver : public ConversationUiObserver
{
public:
	UCObserver();
	
public:
	virtual bool OnNotification(void* _item);
};

}
}

#endif


