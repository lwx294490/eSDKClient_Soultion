
#include "TokenCache.h"

TokenCache::TokenCache()
	:token("")
{

}

TokenCache::~TokenCache()
{

}

std::string TokenCache::getToken() const
{
	return token;
}

void TokenCache::setToken(const std::string &strToken)
{
	token = strToken;
}
