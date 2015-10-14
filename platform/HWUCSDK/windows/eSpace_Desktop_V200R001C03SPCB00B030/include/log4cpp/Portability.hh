/*
 * Portability.hh
 *
 * Copyright 2001, LifeLine Networks BV (www.lifeline.nl). All rights reserved.
 * Copyright 2001, Bastiaan Bakker. All rights reserved.
 *
 * See the COPYING file for the terms of usage and distribution.
 */

#ifndef _LOG4CPP_PORTABILITY_HH
#define _LOG4CPP_PORTABILITY_HH

#define _WINSOCKAPI_

#if defined (_MSC_VER) || defined(__BORLANDC__)
#    if defined (LOG4CPP_STLPORT_AND_BOOST_BUILD)
#        include <log4cpp/config-win32-stlport-boost.h>
#    else
#        include <log4cpp/config-win32.h>
#    endif
#else
#if defined(__OPENVMS__)
#    include <log4cpp/config-openvms.h>
#else
#   if defined(__MINGW32__)
#       include <log4cpp/config-MinGW32.h>
#   else
#       include <log4cpp/config.h>
#   endif
#endif
#endif

#include <log4cpp/Export.hh>

#if defined(_MSC_VER)
#    pragma warning( disable : 4786 ) // 255 char debug symbol limit
#    pragma warning( disable : 4290 ) // throw specifier not implemented
#    pragma warning( disable : 4251 ) // "class XXX should be exported"
#endif

#ifndef LOG4CPP_HAVE_SSTREAM
#include <strstream>
namespace std {
    class LOG4CPP_EXPORT ostringstream : public ostrstream {
        public:
        std::string str();
    };
}
#endif

#include <string>
#include <memory>
#include <windows.h>

#define MTK_CP_GBK      936
#define MTK_CP_DEFAULT  MTK_CP_GBK

namespace log4cpp
{
inline std::auto_ptr<wchar_t>
to_wstr(const char* _p)
{
    if (!_p)
        return std::auto_ptr<wchar_t>(0);
    size_t slen = std::strlen(_p);
    size_t wlen = slen+1;
    wchar_t* wbuf = new wchar_t(wlen);
    std::memset(wbuf, 0, wlen*sizeof(wchar_t));
	wlen = MultiByteToWideChar(MTK_CP_DEFAULT, 0, _p, slen, wbuf, wlen);

    std::auto_ptr<wchar_t> ret(wbuf);
    return ret;
}

inline  std::auto_ptr<char>
to_str(const wchar_t* _p)
{
    if (!_p)
        return std::auto_ptr<char>(0);
    size_t wlen = std::wcslen(_p);
    size_t slen = wlen*3*sizeof(wchar_t)/2+1;
    char* sbuf = new char(slen);
    std::memset(sbuf, 0, slen);
    slen = WideCharToMultiByte(MTK_CP_DEFAULT, 0, _p, wlen, sbuf, slen, 0, 0);
    std::auto_ptr<char> ret(sbuf);
    return ret;
}
}

#endif
