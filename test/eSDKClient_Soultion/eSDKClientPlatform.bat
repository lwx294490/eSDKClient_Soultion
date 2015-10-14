@echo off


echo.
echo гнгнгнгнгн ▒р╥ы eSDKClientPlatform Debug ░ц▒╛ start гнгнгнгнгнгнгнгнгнгнгнгнгн
@"%VS90COMNTOOLS%\..\IDE\devenv.com" .\eSDKClientDemo\eSDKClientDemo.vcproj /Rebuild "Debug|Win32"
@"%VS90COMNTOOLS%\..\IDE\devenv.com" .\UCDemo\UCDemo.vcproj /Rebuild "Debug|Win32"
@"%VS90COMNTOOLS%\..\IDE\devenv.com" .\testCom\testCom.vcproj /Rebuild "Debug|Win32"
echo.
echo гнгнгнгнгн ▒р╥ы eSDKClientPlatform Debug ░ц▒╛ success гнгнгнгнгнгнгнгнгнгнгнгнгн


echo.
echo гнгнгнгнгн ▒р╥ы eSDKClientPlatform Release ░ц▒╛ start гнгнгнгнгнгнгнгнгнгнгнгнгн
@"%VS90COMNTOOLS%\..\IDE\devenv.com" .\eSDKClientDemo\eSDKClientDemo.vcproj /Rebuild "Release|Win32"
@"%VS90COMNTOOLS%\..\IDE\devenv.com" .\UCDemo\UCDemo.vcproj /Rebuild "Release|Win32"
@"%VS90COMNTOOLS%\..\IDE\devenv.com" .\testCom\testCom.vcproj /Rebuild "Release|Win32"
echo.
echo гнгнгнгнгн ▒р╥ы eSDKClientPlatform Release ░ц▒╛ success гнгнгнгнгнгнгнгнгнгнгнгнгн


pause