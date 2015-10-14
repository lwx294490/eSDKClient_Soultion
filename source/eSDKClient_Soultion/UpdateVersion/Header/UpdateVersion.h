#ifndef _UPDATE_VERSION_H_
#define _UPDATE_VERSION_H_

#ifdef UPDATEVERSION_EXPORTS
#define UPDATE_VERSION_API __declspec(dllexport)
#else
#define UPDATE_VERSION_API __declspec(dllimport)
#endif

#ifndef CALLBACK
#define CALLBACK				__stdcall
#endif

#include <string>
#include <vector>

//�汾������ʾ��Ϣ�ص�����iMsgID����
typedef enum
{
	UPDATE_ASK = 0,			//����ѯ��
	UPDATE_START,			//������ʼ
	UPDATE_FINISHED			//�������
} MESSAGE_CODE_E;

/**
 *�汾������ʾ��Ϣ�ص�����
 * 
 *�ú����������ð汾������ʾ��Ϣ�ص�����
 *
 *@param[in] iMsgID				��ϢID,�ο�MESSAGE_CODE_E����
 *@param[in] strDescription		��Ϣ���ݣ�����UPDATE_FINISHED��������ɣ�ʱ�����ݣ���readme.txt��ȡ��������Ϊ��
 *@return						UPDATE_ASK������ѯ�ʣ��������������������true������������false����UPDATE_ASK����true��
 *@attention					��UPDATE_ASK������ѯ�ʣ�ʱҪ�������������磺�ڸú�����ʹ��MessageBox��ʾ�û��Ƿ��������û�ѡ��YES����true��NO����false��
 *@par							��
**/
typedef bool (CALLBACK *MessageCallBack)(int iMsgID, std::string strDescription);


//�汾����������
class UPDATE_VERSION_API UpdateVersion
{
protected:
	UpdateVersion();
	virtual ~UpdateVersion();

public:
	/**
	 *��ȡUpdateVersion�����ʵ��
	 * 
	 *�ú������ڻ�ȡUpdateVersion�����ʵ��
	 *
	 *@return		UpdateVersion�����ʵ����ָ��
	 *@attention	��
	 *@par			��
	**/
	static UpdateVersion* GetUpdateVersion();

	/**
	 *�ͷ�UpdateVersion�����ʵ��
	 * 
	 *�ú�������UpdateVersion�����ʵ��
	 *
	 *@return		��
	 *@attention	��
	 *@par			��
	**/
	static void ReleaseUpdateVersion();

public:
	/**
	 *��������������URL
	 * 
	 *�ú���������������������URL
	 *
	 *@param[in] url	����������URL
	 *@return			true:  Success ; false: Failed
	 *@attention		��
	 *@par				URL����http://10.135.43.43:8080/
	**/
	virtual bool SetServerUrl(const std::string& url) = 0;

	/**
	 *��ȡ����������URL
	 * 
	 *�ú������ڻ�ȡ����������URL
	 *
	 *@return			true:  Success ; false: Failed
	 *@attention		��
	 *@par				URL����http://10.135.43.43:8080/
	**/
	virtual std::string GetServerUrl(void) = 0;

	/**
	 *����ģ���ʼ��
	 * 
	 *�ú�����������ģ���ʼ��
	 *
	 *@param[in] vecNameList		��Ʒ�����б�
	 *@param[in] vecVersionList		��Ʒ�汾�б�
	 *@return						true:  Success ; false: Failed
	 *@attention					��Ʒ���ƺͲ�Ʒ�汾�����Ӧ
	 *@par							��
	**/
	virtual bool Init(const std::vector<std::string>& vecNameList, const std::vector<std::string>& vecVersionList) = 0;

	/**
	 *����ģ��ȥ��ʼ��
	 * 
	 *�ú�����������ģ��ȥ��ʼ��
	 *
	 *@return						true:  Success ; false: Failed
	 *@attention					��
	 *@par							��
	**/
	virtual bool UnInit(void) = 0;

	/**
	 *����ģ������
	 * 
	 *�ú�����������ģ������
	 *
	 *@return						true:  Success ; false: Failed
	 *@attention					ʹ��ʱ��Ҫ�½��̣߳��ڱ����ļ�����ʱStart��������ֱ�������������������Զ������߳̽�������������
	 *@par							��
	**/
	virtual bool Start(void) = 0;

	/**
	 *���ð汾������ʾ��Ϣ�ص�����
	 * 
	 *�ú����������ð汾������ʾ��Ϣ�ص�����
	 *
	 *@param[in] fpMsgCB			�汾������ʾ��Ϣ�ص�����ָ��
	 *@return						true:  Success ; false: Failed
	 *@attention					�ο�����ָ��MessageCallBack����
	 *@par							��
	**/
	virtual bool SetMessageCallBack(MessageCallBack fpMsgCB) = 0;
};

#endif