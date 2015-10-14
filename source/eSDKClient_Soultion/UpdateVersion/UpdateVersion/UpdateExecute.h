#ifndef _UPDATE_EXECUTE_H_
#define _UPDATE_EXECUTE_H_

#include <map>
#include "UpdateVersion.h"
#include "ClientVersionManage.h"
#include "DownloadVersion.h"
#include "unzip.h"

//�汾����ģ��ʵ����
class UpdateExecute : public UpdateVersion
{
private:
	UpdateExecute();
	~UpdateExecute();

public:
	//��ȡ�൥�����
	static UpdateExecute* Instance();
	//�����൥�����
	static void Destroy();

	//����ӿ�ʵ��
public:
	//��������������URL
	virtual bool SetServerUrl(const std::string& url);
	//��ȡ����������URL
	virtual std::string GetServerUrl(void);

	//����ģ���ʼ��
	virtual bool Init(const std::vector<std::string>& vecNameList, const std::vector<std::string>& vecVersionList);
	//����ģ��ȥ��ʼ��
	virtual bool UnInit(void);
	//����ģ������
	virtual bool Start(void);
	//���ð汾������ʾ��Ϣ�ص�����
	virtual bool SetMessageCallBack(MessageCallBack fpMsgCB);

	//�ڲ���������
private:
	//�����ļ�����
	bool UpdateByLocalFile(void);
	//��������汾�Աȡ���������
	bool UpdateByDownload(void);
	//ִ�����غ��������
	bool Execute(const std::string& fileName);
	//ִ�а�װ������������exe��ʽ��msi��ʽ
	bool RunMsi(const std::string& filePath)const;
	//�ļ���������ִ��bat�ļ�
	bool RunBat(const std::string& filePath)const;

	//Download�����̣߳�����з���ӿ�ȴ�
	static DWORD WINAPI UpdateThread(LPVOID);
	
	//zlib ��ѹ, begin
	bool Extract(const std::string& fileName);
	int do_extract_currentfile(unzFile uf, const char* pathDir)const;
	void change_file_date(const char *filename, uLong dosdate, const tm_unz& tmu_date)const;
	//zlib ��ѹ, end

	//��ȡreadme.txt�ļ���m_strReadMeTxt��
	bool ReadReadMeTxt(const std::string& filePath);
	//���������ļ�
	bool ClearAllTempFile();
	//ɾ���ļ������ļ���
	int DeleteDirectory(const std::string &refcstrRootDirectory, bool bDeleteSubdirectories = true);

	//��ȡProductInfo.ini, ��ȡ��ƷID��Name��ӳ���
	bool ReadProductInfo();
	//��ȡVersion.ini, ��ȡ��ǰʹ�õ������в�Ʒ�б�
	bool GetProductList(std::map<std::string, std::string>& mapProductList)const;

	//��ʼ���ǰѰ汾��Ϣд��Version.ini�ļ�
	bool WriteFile(const std::string& Name, const std::string& version);
	//������ɺ��޸�Version.ini�ļ�
	bool ChangeFile(const std::string& filePath)const;

	//��ȡ����ӿʱ������
	static bool GetAvertSurgeTime(int& iMaxTime, int& iMinTime);

private:
	//�汾������ʾ��Ϣ�ص�����ָ��
	MessageCallBack							m_fpMsgCB;
	//��ƷID��Name��ӳ��� key: Name, value: ID
	std::map<std::string, std::string>		m_mapProductInfo;
	//������ɺ󻺴�readme.txt�ļ�����
	std::string								m_strReadMeTxt;
	//Download�����߳̾��
	HANDLE									m_hThreadHandle;

private:
	//��̬��ʵ������ָ��
	static UpdateExecute					* m_pUpdateExecute;
	//�Ƚϰ汾ģ�����
	ClientVersionManage						m_ClientVersionManage;
	//����ģ�����
	DownloadVersion							m_DownloadVersion;
};

#endif
