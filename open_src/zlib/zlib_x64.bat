@echo off

set VCVARSALL="D:\Program Files\Microsoft Visual Studio 10.0\VC\vcvarsall.bat"
set ZLIB_PATH=.\zlib-1.2.8\contrib\masmx64

::����
cd %ZLIB_PATH%
call %VCVARSALL% x86_amd64
call bld_ml64.bat
cd ..\..\..\

echo.
echo ���������� ���� zlib Debug �汾 start ��������������������������
@"%VS90COMNTOOLS%\..\IDE\devenv.com" .\zlib-1.2.8\contrib\vstudio\vc9\zlibvc.vcproj /Rebuild "Debug|x64"
echo ���������� ���� zlib Debug �汾 end ��������������������������

echo.
echo ���������� ���� zlib Release �汾 start ��������������������������
@"%VS90COMNTOOLS%\..\IDE\devenv.com" .\zlib-1.2.8\contrib\vstudio\vc9\zlibvc.vcproj /Rebuild "Release|x64"
echo ���������� ���� zlib Release �汾 end ��������������������������


::�����Ǳ���󿽱�������ע��
xcopy /Y .\zlib-1.2.8\contrib\vstudio\vc9\x64\ZlibDllDebug\zlibwapi.dll .\debug_x64\dll\
xcopy /Y .\zlib-1.2.8\contrib\vstudio\vc9\x64\ZlibDllDebug\zlibwapi.lib .\debug_x64\lib\
xcopy /Y .\zlib-1.2.8\contrib\vstudio\vc9\x64\ZlibDllRelease\zlibwapi.dll .\release_x64\dll\
xcopy /Y .\zlib-1.2.8\contrib\vstudio\vc9\x64\ZlibDllRelease\zlibwapi.lib .\release_x64\lib\

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
