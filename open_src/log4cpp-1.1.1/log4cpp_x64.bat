@echo off

echo.
echo ���������� ���� log4cpp_x64 Debug �汾 start ��������������������������
@"%VS90COMNTOOLS%\..\IDE\devenv.com" .\log4cpp\msvc9\log4cpp\log4cpp.vcproj /Rebuild "Debug|x64"
echo ���������� ���� zlib Debug �汾 end ��������������������������

echo.
echo ���������� ���� log4cpp_x64 Release �汾 start ��������������������������
@"%VS90COMNTOOLS%\..\IDE\devenv.com" .\log4cpp\msvc9\log4cpp\log4cpp.vcproj /Rebuild "Release|x64"
echo ���������� ���� zlib Release �汾 end ��������������������������


::�����Ǳ���󿽱�������ע��
xcopy /Y .\log4cpp\msvc9\log4cpp\x64\Debug\log4cppd.lib .\debug_x64\
xcopy /Y .\log4cpp\msvc9\log4cpp\x64\Release\log4cpp.lib .\release_x64\

pause
