#ifndef _DOWNLOAD_VERSION_H_
#define _DOWNLOAD_VERSION_H_

#include <string>
#include <wininet.h>

class DownloadVersion
{
public:
	DownloadVersion();
	~DownloadVersion();

public:
	bool Download(const std::string& strDownloadPath, const std::string& strDownloadUrl);

	void CloseResourceWhenThreadTerminate(void);

private:
	// http обть
	bool HttpDownload(const std::string& strDownloadPath, const std::string& strDownloadUrl);
	// https обть
	bool HttpsDownload(const std::string& strDownloadPath, const std::string& strDownloadUrl);

private:
	std::string m_strFileName;
	FILE *m_fout;
	HINTERNET m_hOpen;
	HINTERNET m_hOpenUrl;
	HINTERNET m_hConnect;
	HINTERNET m_hRequest;
};


#endif
