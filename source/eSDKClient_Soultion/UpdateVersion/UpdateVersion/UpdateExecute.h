#ifndef _UPDATE_EXECUTE_H_
#define _UPDATE_EXECUTE_H_

#include <map>
#include "UpdateVersion.h"
#include "ClientVersionManage.h"
#include "DownloadVersion.h"
#include "unzip.h"

//版本升级模块实现类
class UpdateExecute : public UpdateVersion
{
private:
	UpdateExecute();
	~UpdateExecute();

public:
	//获取类单体对象
	static UpdateExecute* Instance();
	//销毁类单体对象
	static void Destroy();

	//对外接口实现
public:
	//设置升级服务器URL
	virtual bool SetServerUrl(const std::string& url);
	//获取升级服务器URL
	virtual std::string GetServerUrl(void);

	//升级模块初始化
	virtual bool Init(const std::vector<std::string>& vecNameList, const std::vector<std::string>& vecVersionList);
	//升级模块去初始化
	virtual bool UnInit(void);
	//升级模块启动
	virtual bool Start(void);
	//设置版本升级提示消息回调函数
	virtual bool SetMessageCallBack(MessageCallBack fpMsgCB);

	//内部辅助函数
private:
	//本地文件升级
	bool UpdateByLocalFile(void);
	//与服务器版本对比、下载升级
	bool UpdateByDownload(void);
	//执行下载后的升级包
	bool Execute(const std::string& fileName);
	//执行安装程序升级包括exe格式和msi格式
	bool RunMsi(const std::string& filePath)const;
	//文件覆盖升级执行bat文件
	bool RunBat(const std::string& filePath)const;

	//Download升级线程，会进行防浪涌等待
	static DWORD WINAPI UpdateThread(LPVOID);
	
	//zlib 解压, begin
	bool Extract(const std::string& fileName);
	int do_extract_currentfile(unzFile uf, const char* pathDir)const;
	void change_file_date(const char *filename, uLong dosdate, const tm_unz& tmu_date)const;
	//zlib 解压, end

	//读取readme.txt文件到m_strReadMeTxt中
	bool ReadReadMeTxt(const std::string& filePath);
	//清理升级文件
	bool ClearAllTempFile();
	//删除文件或者文件夹
	int DeleteDirectory(const std::string &refcstrRootDirectory, bool bDeleteSubdirectories = true);

	//读取ProductInfo.ini, 获取产品ID、Name的映射表
	bool ReadProductInfo();
	//读取Version.ini, 获取当前使用到的所有产品列表
	bool GetProductList(std::map<std::string, std::string>& mapProductList)const;

	//初始化是把版本信息写入Version.ini文件
	bool WriteFile(const std::string& Name, const std::string& version);
	//升级完成后修改Version.ini文件
	bool ChangeFile(const std::string& filePath)const;

	//获取防浪涌时间配置
	static bool GetAvertSurgeTime(int& iMaxTime, int& iMinTime);

private:
	//版本升级提示消息回调函数指针
	MessageCallBack							m_fpMsgCB;
	//产品ID、Name的映射表 key: Name, value: ID
	std::map<std::string, std::string>		m_mapProductInfo;
	//升级完成后缓存readme.txt文件内容
	std::string								m_strReadMeTxt;
	//Download升级线程句柄
	HANDLE									m_hThreadHandle;

private:
	//静态单实例对象指针
	static UpdateExecute					* m_pUpdateExecute;
	//比较版本模块对象
	ClientVersionManage						m_ClientVersionManage;
	//下载模块对象
	DownloadVersion							m_DownloadVersion;
};

#endif
