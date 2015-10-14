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

//版本升级提示消息回调函数iMsgID定义
typedef enum
{
	UPGRADE_ASK = 0,			//升级询问
	UPGRADE_START,			    //升级开始
	UPGRADE_FINISHED			//升级完成
} UPGRADE_MESSAGE_CODE_E;

typedef struct  
{
	char acName[UPGRADE_MAX_BUFFER_SIZE];
	char acVersion[UPGRADE_MAX_BUFFER_SIZE];
} UPGRADE_VERSION_INFO_S;

/**
 *版本升级提示消息回调函数
 * 
 *该函数用于设置版本升级提示消息回调函数
 *
 *@param[in] iMsgID				消息ID,参考MESSAGE_CODE_E定义
 *@param[in] pchDescription		消息内容，仅在UPDATE_FINISHED（升级完成）时有内容（从readme.txt读取），其他为空
 *@return						UPDATE_ASK（升级询问）会进行阻塞，升级返回true，不升级返回false。非UPDATE_ASK返回true。
 *@attention					在UPDATE_ASK（升级询问）时要进行阻塞，比如：在该函数内使用MessageBox提示用户是否升级，用户选择YES返回true，NO返回false。
 *@par							无
**/
typedef bool (__UPGRADE_VERSION_CALL *UpgradeMessageCallBack)(int iMsgID, char* pchDescription);

#ifdef __cplusplus
extern "C"
{
#endif
	/**
	 *升级模块初始化
	 * 
	 *该函数用于升级模块初始化
	 *
	 *@param[in] pstVersionArray		产品版本列表
	 *@param[in] iArrayNum		        产品版本列表个数
	 *@return						    true:  Success ; false: Failed
	 *@attention					    无
	 *@par							    无
	**/
	UPGRADE_VERSION_API bool __UPGRADE_VERSION_CALL Upgrade_Init(const UPGRADE_VERSION_INFO_S* pstVersionArray, const int iArrayNum);

	/**
	 *升级模块去初始化
	 * 
	 *该函数用于升级模块去初始化
	 *
	 *@return						true:  Success ; false: Failed
	 *@attention					无
	 *@par							无
	**/
	UPGRADE_VERSION_API bool __UPGRADE_VERSION_CALL Upgrade_Uninit(void);

	/**
	 *设置升级服务器URL
	 * 
	 *该函数用于设置升级服务器URL
	 *
	 *@param[in] pchServerUrl	升级服务器URL
	 *@return			        true:  Success ; false: Failed
	 *@attention		        无
	 *@par				        URL例："http://10.135.43.43:8080/"
	**/
	UPGRADE_VERSION_API bool __UPGRADE_VERSION_CALL Upgrade_SetServerUrl(const char* pchServerUrl);

	/**
	 *获取升级服务器URL
	 * 
	 *该函数用于获取升级服务器URL
	 *
	 *@param[in]  pchServerUrl	存储升级服务器URL的内存指针
	 *@param[in]  iBufferLen	内存长度
	 *@param[out] pchServerUrl	升级服务器URL
	 *@return			true:  Success ; false: Failed
	 *@attention		无
	 *@par				URL例："http://10.135.43.43:8080/"
	**/
	UPGRADE_VERSION_API bool __UPGRADE_VERSION_CALL Upgrade_GetServerUrl(char* pchServerUrl, int iBufferLen);

	/**
	 *升级模块启动
	 * 
	 *该函数用于升级模块启动
	 *
	 *@return						true:  Success ; false: Failed
	 *@attention					使用时不要新建线程（在本地文件升级时Start会阻塞，直到本地升级结束，会自动创建线程进行下载升级）
	 *@par							无
	**/
	UPGRADE_VERSION_API bool __UPGRADE_VERSION_CALL Upgrade_Start(void);

	/**
	 *设置版本升级提示消息回调函数
	 * 
	 *该函数用于设置版本升级提示消息回调函数
	 *
	 *@param[in] fpMsgCB			版本升级提示消息回调函数指针
	 *@return						true:  Success ; false: Failed
	 *@attention					参考函数指针UpgradeMessageCallBack定义
	 *@par							无
	**/
	UPGRADE_VERSION_API bool __UPGRADE_VERSION_CALL Upgrade_SetMessageCallBack(UpgradeMessageCallBack fpMsgCB);

#ifdef __cplusplus
}
#endif 

#endif

