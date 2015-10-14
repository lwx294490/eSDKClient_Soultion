#ifndef _UPGRADE_VERSION_H_
#define _UPGRADE_VERSION_H_

#ifdef UPDATEVERSION_EXPORTS
#define UPGRADE_VERSION_API __declspec(dllexport)
#else
#define UPGRADE_VERSION_API __declspec(dllimport)
#endif

#ifdef WIN32
#define __UPGRADE_VERSION_CALL __stdcall
#else
#define __UPGRADE_VERSION_CALL
#endif

#define UPGRADE_MAX_BUFFER_SIZE 128

//�汾������ʾ��Ϣ�ص�����iMsgID����
typedef enum
{
	UPGRADE_ASK = 0,			//����ѯ��
	UPGRADE_START,			    //������ʼ
	UPGRADE_FINISHED			//�������
} UPGRADE_MESSAGE_CODE_E;

typedef struct  
{
	char acName[UPGRADE_MAX_BUFFER_SIZE];
	char acVersion[UPGRADE_MAX_BUFFER_SIZE];
} UPGRADE_VERSION_INFO_S;

/**
 *�汾������ʾ��Ϣ�ص�����
 * 
 *�ú����������ð汾������ʾ��Ϣ�ص�����
 *
 *@param[in] iMsgID				��ϢID,�ο�MESSAGE_CODE_E����
 *@param[in] pchDescription		��Ϣ���ݣ�����UPDATE_FINISHED��������ɣ�ʱ�����ݣ���readme.txt��ȡ��������Ϊ��
 *@return						UPDATE_ASK������ѯ�ʣ��������������������true������������false����UPDATE_ASK����true��
 *@attention					��UPDATE_ASK������ѯ�ʣ�ʱҪ�������������磺�ڸú�����ʹ��MessageBox��ʾ�û��Ƿ��������û�ѡ��YES����true��NO����false��
 *@par							��
**/
typedef bool (__UPGRADE_VERSION_CALL *UpgradeMessageCallBack)(int iMsgID, char* pchDescription);

#ifdef __cplusplus
extern "C"
{
#endif
	/**
	 *����ģ���ʼ��
	 * 
	 *�ú�����������ģ���ʼ��
	 *
	 *@param[in] pstVersionArray		��Ʒ�汾�б�
	 *@param[in] iArrayNum		        ��Ʒ�汾�б����
	 *@return						    true:  Success ; false: Failed
	 *@attention					    ��
	 *@par							    ��
	**/
	UPGRADE_VERSION_API bool __UPGRADE_VERSION_CALL Upgrade_Init(const UPGRADE_VERSION_INFO_S* pstVersionArray, const int iArrayNum);

	/**
	 *����ģ��ȥ��ʼ��
	 * 
	 *�ú�����������ģ��ȥ��ʼ��
	 *
	 *@return						true:  Success ; false: Failed
	 *@attention					��
	 *@par							��
	**/
	UPGRADE_VERSION_API bool __UPGRADE_VERSION_CALL Upgrade_Uninit(void);

	/**
	 *��������������URL
	 * 
	 *�ú���������������������URL
	 *
	 *@param[in] pchServerUrl	����������URL
	 *@return			        true:  Success ; false: Failed
	 *@attention		        ��
	 *@par				        URL����"http://10.135.43.43:8080/"
	**/
	UPGRADE_VERSION_API bool __UPGRADE_VERSION_CALL Upgrade_SetServerUrl(const char* pchServerUrl);

	/**
	 *��ȡ����������URL
	 * 
	 *�ú������ڻ�ȡ����������URL
	 *
	 *@param[in]  pchServerUrl	�洢����������URL���ڴ�ָ��
	 *@param[in]  iBufferLen	�ڴ泤��
	 *@param[out] pchServerUrl	����������URL
	 *@return			true:  Success ; false: Failed
	 *@attention		��
	 *@par				URL����"http://10.135.43.43:8080/"
	**/
	UPGRADE_VERSION_API bool __UPGRADE_VERSION_CALL Upgrade_GetServerUrl(char* pchServerUrl, int iBufferLen);

	/**
	 *����ģ������
	 * 
	 *�ú�����������ģ������
	 *
	 *@return						true:  Success ; false: Failed
	 *@attention					ʹ��ʱ��Ҫ�½��̣߳��ڱ����ļ�����ʱStart��������ֱ�������������������Զ������߳̽�������������
	 *@par							��
	**/
	UPGRADE_VERSION_API bool __UPGRADE_VERSION_CALL Upgrade_Start(void);

	/**
	 *���ð汾������ʾ��Ϣ�ص�����
	 * 
	 *�ú����������ð汾������ʾ��Ϣ�ص�����
	 *
	 *@param[in] fpMsgCB			�汾������ʾ��Ϣ�ص�����ָ��
	 *@return						true:  Success ; false: Failed
	 *@attention					�ο�����ָ��UpgradeMessageCallBack����
	 *@par							��
	**/
	UPGRADE_VERSION_API bool __UPGRADE_VERSION_CALL Upgrade_SetMessageCallBack(UpgradeMessageCallBack fpMsgCB);

#ifdef __cplusplus
}
#endif 

#endif

