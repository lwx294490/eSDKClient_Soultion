#ifndef _TOKEN_CACHE_H_
#define _TOKEN_CACHE_H_

#include <string>
//token¿‡
class TokenCache
{
public:
	TokenCache();
	~TokenCache();
	std::string getToken(void) const;
	void setToken(const std::string &str);
private:
	std::string token;	
};

#endif
