::libcurl����֧��https����Ҫ����opensslһ����룬���ɵĿ��֧��https
::ִ��֮ǰ���޸�libcurl��openssl·�����ұ�֤Ŀ¼�ṹΪ��Դ�����ԭʼ�ṹ

@echo off

set LIBCURL_PATH=%cd%\curl\source\src
set OPENSSL_PATH=%cd%\openssl-1.0.1m\source
set VCVARS32="%VS100COMNTOOLS%\..\..\VC\bin\vcvars32.bat"

@echo .
@echo ������������������������������������openssl��������������������������������
@echo .
cd %OPENSSL_PATH%
perl Configure VC-WIN32
call "ms/do_ms.bat"
call %VCVARS32%
nmake -f ms/ntdll.mak

@echo .
@echo ������������������������������������libcurl��������������������������������
@echo .
cd %LIBCURL_PATH%\lib
call %VCVARS32%
set CFG=debug-dll-ssl-dll
nmake -f Makefile.vc10
set CFG=release-dll-ssl-dll
nmake -f Makefile.vc10

pause