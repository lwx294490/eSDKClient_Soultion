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

//版本升级提示消息回调函数iMsgID定义
typedef enum
{
	UPDATE_ASK = 0,			//升级询问
	UPDATE_START,			//升级开始
	UPDATE_FINISHED			//升级完成
} MESSAGE_CODE_E;

/**
 *版本升级提示消息回调函数
 * 
 *该函数用于设置版本升级提示消息回调函数
 *
 *@param[in] iMsgID				消息ID,参考MESSAGE_CODE_E定义
 *@param[in] strDescription		消息内容，仅在UPDATE_FINISHED（升级完成）时有内容（从readme.txt读取），其他为空
 *@return						UPDATE_ASK（升级询问）会进行阻塞，升级返回true，不升级返回false。非UPDATE_ASK返回true。
 *@attention					在UPDATE_ASK（升级询问）时要进行阻塞，比如：在该函数内使用MessageBox提示用户是否升级，用户选择YES返回true，NO返回false。
 *@par							无
**/
typedef bool (CALLBACK *MessageCallBack)(int iMsgID, std::string strDescription);


//版本升级导出类
class UPDATE_VERSION_API UpdateVersion
{
protected:
	UpdateVersion();
	virtual ~UpdateVersion();

public:
	/**
	 *获取UpdateVersion类对象实例
	 * 
	 *该函数用于获取UpdateVersion类对象实例
	 *
	 *@return		UpdateVersion类对象实例的指针
	 *@attention	无
	 *@par			无
	**/
	static UpdateVersion* GetUpdateVersion();

	/**
	 *释放UpdateVersion类对象实例
	 * 
	 *该函数用于UpdateVersion类对象实例
	 *
	 *@return		无
	 *@attention	无
	 *@par			无
	**/
	static void ReleaseUpdateVersion();

public:
	/**
	 *设置升级服务器URL
	 * 
	 *该函数用于设置升级服务器URL
	 *
	 *@param[in] url	升级服务器URL
	 *@return			true:  Success ; false: Failed
	 *@attention		无
	 *@par				URL例：http://10.135.43.43:8080/
	**/
	virtual bool SetServerUrl(const std::string& url) = 0;

	/**
	 *获取升级服务器URL
	 * 
	 *该函数用于获取升级服务器URL
	 *
	 *@return			true:  Success ; false: Failed
	 *@attention		无
	 *@par				URL例：http://10.135.43.43:8080/
	**/
	virtual std::string GetServerUrl(void) = 0;

	/**
	 *升级模块初始化
	 * 
	 *该函数用于升级模块初始化
	 *
	 *@param[in] vecNameList		产品名称列表
	 *@param[in] vecVersionList		产品版本列表
	 *@return						true:  Success ; false: Failed
	 *@attention					产品名称和产品版本必须对应
	 *@par							无
	**/
	virtual bool Init(const std::vector<std::string>& vecNameList, const std::vector<std::string>& vecVersionList) = 0;

	/**
	 *升级模块去初始化
	 * 
	 *该函数用于升级模块去初始化
	 *
	 *@return						true:  Success ; false: Failed
	 *@attention					无
	 *@par							无
	**/
	virtual bool UnInit(void) = 0;

	/**
	 *升级模块启动
	 * 
	 *该函数用于升级模块启动
	 *
	 *@return						true:  Success ; false: Failed
	 *@attention					使用时不要新建线程（在本地文件升级时Start会阻塞，直到本地升级结束，会自动创建线程进行下载升级）
	 *@par							无
	**/
	virtual bool Start(void) = 0;

	/**
	 *设置版本升级提示消息回调函数
	 * 
	 *该函数用于设置版本升级提示消息回调函数
	 *
	 *@param[in] fpMsgCB			版本升级提示消息回调函数指针
	 *@return						true:  Success ; false: Failed
	 *@attention					参考函数指针MessageCallBack定义
	 *@par							无
	**/
	virtual bool SetMessageCallBack(MessageCallBack fpMsgCB) = 0;
};

#endif