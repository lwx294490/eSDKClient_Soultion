@echo off

echo.
echo ���������� ���� zlib Debug �汾 start ��������������������������
@"%VS90COMNTOOLS%\..\IDE\devenv.com" .\zlib-1.2.8\contrib\vstudio\vc9\zlibvc.vcproj /Rebuild "Debug|Win32"
echo ���������� ���� zlib Debug �汾 end ��������������������������

echo.
echo ���������� ���� zlib Release �汾 start ��������������������������
@"%VS90COMNTOOLS%\..\IDE\devenv.com" .\zlib-1.2.8\contrib\vstudio\vc9\zlibvc.vcproj /Rebuild "Release|Win32"
echo ���������� ���� zlib Release �汾 end ��������������������������


::�����Ǳ���󿽱�������ע��
::xcopy /Y .\zlib-1.2.8\contrib\vstudio\vc9\x86\ZlibDllDebug\zlibwapi.dll .\debug\dll\
::xcopy /Y .\zlib-1.2.8\contrib\vstudio\vc9\x86\ZlibDllDebug\zlibwapi.lib .\debug\lib\
::xcopy /Y .\zlib-1.2.8\contrib\vstudio\vc9\x86\ZlibDllRelease\zlibwapi.dll .\release\dll\
::xcopy /Y .\zlib-1.2.8\contrib\vstudio\vc9\x86\ZlibDllRelease\zlibwapi.lib .\release\lib\

::xcopy /Y .\zlib-1.2.8\contrib\minizip\crypt.h .\include\
::xcopy /Y .\zlib-1.2.8\contrib\minizip\ioapi.c .\include\
::xcopy /Y .\zlib-1.2.8\contrib\minizip\ioapi.h .\include\
::xcopy /Y .\zlib-1.2.8\contrib\minizip\iowin32.h .\include\
::xcopy /Y .\zlib-1.2.8\contrib\minizip\mztools.h .\include\
::xcopy /Y .\zlib-1.2.8\contrib\minizip\unzip.h .\include\
::xcopy /Y .\zlib-1.2.8\contrib\minizip\zip.h .\include\
::xcopy /Y .\zlib-1.2.8\zconf.h .\include
::xcopy /Y .\zlib-1.2.8\zlib.h .\include

pause
