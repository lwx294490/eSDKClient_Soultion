@echo off

echo.
echo ���������� ���� Log4cpp Debug �汾 start ��������������������������
@"%VS90COMNTOOLS%\..\IDE\devenv.com" .\log4cpp\msvc9\msvc9.sln /Rebuild "Debug|Win32" /out builddebug.log
echo.
echo ���������� ���� Log4cpp Debug �汾 success ��������������������������


echo.
echo ���������� ���� Log4cpp Release �汾 start ��������������������������
@"%VS90COMNTOOLS%\..\IDE\devenv.com" .\log4cpp\msvc9\msvc9.sln /Rebuild "Release|Win32" /out buildrelease.log
echo.
echo ���������� ���� Log4cpp Release �汾 success ��������������������������

pause