#ifndef _UC_OBSERVER_H_
#define _UC_OBSERVER_H_


namespace eSDK {
	namespace UC {


//m_ObTestΪ����ʵ���࣬ʵ��SDK�׵��ϲ����Ϣ�ڵ��̴߳���
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


