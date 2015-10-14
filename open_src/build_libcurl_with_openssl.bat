::libcurl自身不支持https，需要依赖openssl一起编译，生成的库才支持https
::执行之前需修改libcurl与openssl路径，且保证目录结构为开源软件包原始结构

@echo off

set LIBCURL_PATH=%cd%\curl\source\src
set OPENSSL_PATH=%cd%\openssl-1.0.1m\source
set VCVARS32="%VS100COMNTOOLS%\..\..\VC\bin\vcvars32.bat"

@echo .
@echo －－－－－－－－－－－－－－－－编译openssl－－－－－－－－－－－－－－－－
@echo .
cd %OPENSSL_PATH%
perl Configure VC-WIN32
call "ms/do_ms.bat"
call %VCVARS32%
nmake -f ms/ntdll.mak

@echo .
@echo －－－－－－－－－－－－－－－－编译libcurl－－－－－－－－－－－－－－－－
@echo .
cd %LIBCURL_PATH%\lib
call %VCVARS32%
set CFG=debug-dll-ssl-dll
nmake -f Makefile.vc10
set CFG=release-dll-ssl-dll
nmake -f Makefile.vc10

pause