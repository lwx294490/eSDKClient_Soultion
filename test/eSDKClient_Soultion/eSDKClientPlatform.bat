@echo off


echo.
echo ���������� ���� eSDKClientPlatform Debug �汾 start ��������������������������
@"%VS90COMNTOOLS%\..\IDE\devenv.com" .\eSDKClientDemo\eSDKClientDemo.vcproj /Rebuild "Debug|Win32"
@"%VS90COMNTOOLS%\..\IDE\devenv.com" .\UCDemo\UCDemo.vcproj /Rebuild "Debug|Win32"
@"%VS90COMNTOOLS%\..\IDE\devenv.com" .\testCom\testCom.vcproj /Rebuild "Debug|Win32"
echo.
echo ���������� ���� eSDKClientPlatform Debug �汾 success ��������������������������


echo.
echo ���������� ���� eSDKClientPlatform Release �汾 start ��������������������������
@"%VS90COMNTOOLS%\..\IDE\devenv.com" .\eSDKClientDemo\eSDKClientDemo.vcproj /Rebuild "Release|Win32"
@"%VS90COMNTOOLS%\..\IDE\devenv.com" .\UCDemo\UCDemo.vcproj /Rebuild "Release|Win32"
@"%VS90COMNTOOLS%\..\IDE\devenv.com" .\testCom\testCom.vcproj /Rebuild "Release|Win32"
echo.
echo ���������� ���� eSDKClientPlatform Release �汾 success ��������������������������


pause