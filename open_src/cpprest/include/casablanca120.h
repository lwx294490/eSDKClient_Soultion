#ifndef _CASABLANCA_100_H_
#define _CASABLANCA_100_H_

#include "./casablanca120/cpprest/http_client.h"
#include "./casablanca120/cpprest/json.h"

using namespace pplx;
using namespace web;
using namespace web::http;
using namespace web::http::client;

#ifdef _DEBUG
#define CASABLANCA120_LIB_NAME "cpprest110d_1_2.lib"
#else
#define CASABLANCA120_LIB_NAME "cpprest110_1_2.lib"
#endif

#pragma message("casablanca120 : Auto Linking to "CASABLANCA120_LIB_NAME)
#pragma comment(lib, CASABLANCA120_LIB_NAME)

#endif