@echo off

::��õ�ǰʱ�䣬��Ϊ���ɰ汾��Ŀ¼��
for /F "tokens=1-4 delims=-/ " %%i in ('date /t') do (
   set Year=%%i
   set Month=%%j
   set Day=%%k
   set DayOfWeek=%%l
)
for /F "tokens=1-2 delims=: " %%i in ('time /t') do (
   set Hour=%%i
   set Minute=%%j
)

::���ø�������
set DateTime=%Year%-%Month%-%Day%-%Hour%-%Minute%

::��������·����sln·���������ݸýű�����Ŀ¼�����޸�
set ProjectPath=%cd%

::���ɵ�ѹ����·��������Ҫ������޸�
set ZipPath=%ProjectPath%\..\..\..\00.Release\%DateTime%
set ZipName1=%ZipPath%\eSDKClientPlatform.zip
set ZipName2=%ZipPath%\eSDKSSO_COM.zip
set ZipName3=%ZipPath%\VersionUpdate.zip

::��������Ŀ¼
set DebugPath=%ProjectPath%\output\debug
set ReleasePath=%ProjectPath%\output\release

::--------------------------------------------------------------------------------

::����debug���ļ�
::UC���ļ�
xcopy /y ..\..\platform\HWUCSDK\windows\eSpace_Desktop_V200R001C03SPCB00B030\debug\dll\*.dll 			"%DebugPath%\SDK\UCSDK\"
xcopy /y ..\..\platform\HWUCSDK\windows\eSpace_Desktop_V200R001C03SPCB00B030\debug\dll\*.ini 			"%DebugPath%\SDK\UCSDK\"
xcopy /y ..\..\platform\HWUCSDK\windows\eSpace_Desktop_V200R001C03SPCB00B030\debug\dll\*.xml 			"%DebugPath%\SDK\UCSDK\"
xcopy /y ..\..\platform\HWUCSDK\windows\eSpace_Desktop_V200R001C03SPCB00B030\debug\dll\config\*.conf	"%DebugPath%\SDK\UCSDK\config\"
xcopy /y ..\..\platform\HWUCSDK\windows\eSpace_Desktop_V200R001C03SPCB00B030\debug\dll\log4cppd.dll 	"%DebugPath%\"
::�����ļ�
xcopy /y ..\..\platform\config\eSDKClientPlatform_config.ini											"%DebugPath%\"
xcopy /y ..\..\platform\config\eSDKSSO_config.ini														"%DebugPath%\"
xcopy /y ..\..\platform\config\ProductInfo.ini															"%DebugPath%\"
xcopy /y ..\..\platform\config\UpdateVersion_config.ini													"%DebugPath%\"
xcopy /y ..\..\platform\config\eSDKClientPlatform_config.ini											"%DebugPath%\"
xcopy /y ..\..\platform\config\UCSDK_config.ini															"%DebugPath%\SDK\UCSDK\"
xcopy /y ..\..\platform\config\setup.bat																"%DebugPath%\"
::��Դ���ļ�
xcopy /y ..\..\open_src\cpprest\release\dll\cpprest110_1_2.dll 											"%DebugPath%\"
xcopy /y ..\..\open_src\zlib\debug\dll\zlibwapi.dll			 											"%DebugPath%\"
::Visual Studio���ļ�
xcopy /y "..\..\third_party\Microsoft Visual Studio 11.0\x86\msvcp110.dll" 								"%DebugPath%\"
xcopy /y "..\..\third_party\Microsoft Visual Studio 11.0\x86\msvcr110.dll" 								"%DebugPath%\"

::����release���ļ�
xcopy /y ..\..\platform\HWUCSDK\windows\eSpace_Desktop_V200R001C03SPCB00B030\release\dll\*.dll 			"%ReleasePath%\SDK\UCSDK\"
xcopy /y ..\..\platform\HWUCSDK\windows\eSpace_Desktop_V200R001C03SPCB00B030\release\dll\*.ini 			"%ReleasePath%\SDK\UCSDK\"
xcopy /y ..\..\platform\HWUCSDK\windows\eSpace_Desktop_V200R001C03SPCB00B030\release\dll\*.xml 			"%ReleasePath%\SDK\UCSDK\"
xcopy /y ..\..\platform\HWUCSDK\windows\eSpace_Desktop_V200R001C03SPCB00B030\release\dll\config\*.conf	"%ReleasePath%\SDK\UCSDK\config\"
xcopy /y ..\..\platform\HWUCSDK\windows\eSpace_Desktop_V200R001C03SPCB00B030\release\dll\log4cpp.dll 	"%ReleasePath%\"
::�����ļ�
xcopy /y ..\..\platform\config\eSDKClientPlatform_config.ini											"%ReleasePath%\"
xcopy /y ..\..\platform\config\eSDKSSO_config.ini														"%ReleasePath%\"
xcopy /y ..\..\platform\config\ProductInfo.ini															"%ReleasePath%\"
xcopy /y ..\..\platform\config\UpdateVersion_config.ini													"%ReleasePath%\"
xcopy /y ..\..\platform\config\eSDKClientPlatform_config.ini											"%ReleasePath%\"
xcopy /y ..\..\platform\config\UCSDK_config.ini															"%ReleasePath%\SDK\UCSDK\"
xcopy /y ..\..\platform\config\setup.bat																"%ReleasePath%\"
::��Դ���ļ�
xcopy /y ..\..\open_src\cpprest\release\dll\cpprest110_1_2.dll 											"%ReleasePath%\"
xcopy /y ..\..\open_src\zlib\release\dll\zlibwapi.dll			 										"%ReleasePath%\"
::Visual Studio���ļ�
xcopy /y "..\..\third_party\Microsoft Visual Studio 11.0\x86\msvcp110.dll" 								"%ReleasePath%\"
xcopy /y "..\..\third_party\Microsoft Visual Studio 11.0\x86\msvcr110.dll" 								"%ReleasePath%\"

::--------------------------------------------------------------------------------

::���빤��
@"%VS110COMNTOOLS%\..\IDE\devenv.com" 	.\REST_Adapter.sln 				/Rebuild "Release|Win32"
::������debugĿ¼
xcopy /Y "%ReleasePath%\SSOAdapter.dll" 	"%DebugPath%\"
xcopy /Y "%ReleasePath%\SSOAdapter.lib" 	"%DebugPath%\"
xcopy /Y "%ReleasePath%\UpdateAdapter.dll" 	"%DebugPath%\"
xcopy /Y "%ReleasePath%\UpdateAdapter.lib" 	"%DebugPath%\"
::���빤��
@"%VS90COMNTOOLS%\..\IDE\devenv.com" 	.\eSDKClient_Soultion.sln 		/Rebuild "Debug|Win32"
@"%VS90COMNTOOLS%\..\IDE\devenv.com" 	.\eSDKClient_Soultion.sln 		/Rebuild "Release|Win32"

::--------------------------------------------------------------------------------

::���ø�������
set	WinRarRoot=C:\Program Files\WinRAR

::����Ŀ¼
mkdir "%ZipPath%\"

::--------------------------------------------------------------------------------

::����ļ� eSDKClientPlatform
(chdir %ProjectPath%\eSDKSSO\Header)
"%WinRarRoot%\Rar.exe" u -s- -m1 -ap"include\C++" 		"%ZipName1%" ProductSDK.h
(chdir %ProjectPath%\eSDKClientPlatform\Header)
"%WinRarRoot%\Rar.exe" u -s- -m1 -ap"include\C" 		"%ZipName1%" eSDKClient_Platform.h
"%WinRarRoot%\Rar.exe" u -s- -m1 -ap"include\C++" 		"%ZipName1%" eSDKClientPlatform.h
(chdir %ProjectPath%\UCSDK\Header\C)
"%WinRarRoot%\Rar.exe" u -s- -m1 -ap"include\C\UCSDK" 	"%ZipName1%" *.h
(chdir %ProjectPath%\UCSDK\Header\C++)
"%WinRarRoot%\Rar.exe" u -s- -m1 -ap"include\C++\UCSDK" "%ZipName1%" *.h

(chdir %DebugPath%\)
"%WinRarRoot%\Rar.exe" u -s- -m1 -ap"debug" 			"%ZipName1%" eSDKClientPlatform.dll
"%WinRarRoot%\Rar.exe" u -s- -m1 -ap"debug" 			"%ZipName1%" eSDKClientPlatform.lib
"%WinRarRoot%\Rar.exe" u -s- -m1 -ap"debug" 			"%ZipName1%" eSDKSSO.dll
"%WinRarRoot%\Rar.exe" u -s- -m1 -ap"debug" 			"%ZipName1%" eSDKSSO.lib
"%WinRarRoot%\Rar.exe" u -s- -m1 -ap"debug" 			"%ZipName1%" eSDKTool.dll
"%WinRarRoot%\Rar.exe" u -s- -m1 -ap"debug" 			"%ZipName1%" eSDKTool.lib
"%WinRarRoot%\Rar.exe" u -s- -m1 -ap"debug" 			"%ZipName1%" SSOAdapter.dll
"%WinRarRoot%\Rar.exe" u -s- -m1 -ap"debug" 			"%ZipName1%" SSOAdapter.lib
"%WinRarRoot%\Rar.exe" u -s- -m1 -ap"debug" 			"%ZipName1%" UpdateAdapter.dll
"%WinRarRoot%\Rar.exe" u -s- -m1 -ap"debug" 			"%ZipName1%" UpdateAdapter.lib
"%WinRarRoot%\Rar.exe" u -s- -m1 -ap"debug" 			"%ZipName1%" UpdateVersion.dll
"%WinRarRoot%\Rar.exe" u -s- -m1 -ap"debug" 			"%ZipName1%" UpdateVersion.lib
"%WinRarRoot%\Rar.exe" u -s- -m1 -ap"debug" 			"%ZipName1%" log4cppd.dll
"%WinRarRoot%\Rar.exe" u -s- -m1 -ap"debug" 			"%ZipName1%" cpprest110_1_2.dll
"%WinRarRoot%\Rar.exe" u -s- -m1 -ap"debug" 			"%ZipName1%" zlibwapi.dll
"%WinRarRoot%\Rar.exe" u -s- -m1 -ap"debug" 			"%ZipName1%" msvcp110.dll
"%WinRarRoot%\Rar.exe" u -s- -m1 -ap"debug" 			"%ZipName1%" msvcr110.dll
"%WinRarRoot%\Rar.exe" u -s- -m1 -ap"debug" 			"%ZipName1%" eSDKClientPlatform_config.ini
"%WinRarRoot%\Rar.exe" u -s- -m1 -ap"debug" 			"%ZipName1%" eSDKSSO_config.ini
"%WinRarRoot%\Rar.exe" u -s- -m1 -ap"debug" 			"%ZipName1%" ProductInfo.ini
"%WinRarRoot%\Rar.exe" u -s- -m1 -ap"debug" 			"%ZipName1%" UpdateVersion_config.ini
"%WinRarRoot%\Rar.exe" u -s- -m1 -ap"debug" 			"%ZipName1%" .\SDK\UCSDK\*.dll
"%WinRarRoot%\Rar.exe" u -s- -m1 -ap"debug" 			"%ZipName1%" .\SDK\UCSDK\*.lib
"%WinRarRoot%\Rar.exe" u -s- -m1 -ap"debug" 			"%ZipName1%" .\SDK\UCSDK\*.ini
"%WinRarRoot%\Rar.exe" u -s- -m1 -ap"debug" 			"%ZipName1%" .\SDK\UCSDK\*.xml
"%WinRarRoot%\Rar.exe" u -s- -m1 -ap"debug" 			"%ZipName1%" .\SDK\UCSDK\config\*.conf

(chdir %ReleasePath%\)
"%WinRarRoot%\Rar.exe" u -s- -m1 -ap"release" 			"%ZipName1%" eSDKClientPlatform.dll
"%WinRarRoot%\Rar.exe" u -s- -m1 -ap"release" 			"%ZipName1%" eSDKClientPlatform.lib
"%WinRarRoot%\Rar.exe" u -s- -m1 -ap"release" 			"%ZipName1%" eSDKSSO.dll
"%WinRarRoot%\Rar.exe" u -s- -m1 -ap"release" 			"%ZipName1%" eSDKSSO.lib
"%WinRarRoot%\Rar.exe" u -s- -m1 -ap"release" 			"%ZipName1%" eSDKTool.dll
"%WinRarRoot%\Rar.exe" u -s- -m1 -ap"release" 			"%ZipName1%" eSDKTool.lib
"%WinRarRoot%\Rar.exe" u -s- -m1 -ap"release" 			"%ZipName1%" SSOAdapter.dll
"%WinRarRoot%\Rar.exe" u -s- -m1 -ap"release" 			"%ZipName1%" SSOAdapter.lib
"%WinRarRoot%\Rar.exe" u -s- -m1 -ap"release" 			"%ZipName1%" UpdateAdapter.dll
"%WinRarRoot%\Rar.exe" u -s- -m1 -ap"release" 			"%ZipName1%" UpdateAdapter.lib
"%WinRarRoot%\Rar.exe" u -s- -m1 -ap"release" 			"%ZipName1%" UpdateVersion.dll
"%WinRarRoot%\Rar.exe" u -s- -m1 -ap"release" 			"%ZipName1%" UpdateVersion.lib
"%WinRarRoot%\Rar.exe" u -s- -m1 -ap"release" 			"%ZipName1%" log4cpp.dll
"%WinRarRoot%\Rar.exe" u -s- -m1 -ap"release" 			"%ZipName1%" cpprest110_1_2.dll
"%WinRarRoot%\Rar.exe" u -s- -m1 -ap"release" 			"%ZipName1%" zlibwapi.dll
"%WinRarRoot%\Rar.exe" u -s- -m1 -ap"release" 			"%ZipName1%" msvcp110.dll
"%WinRarRoot%\Rar.exe" u -s- -m1 -ap"release" 			"%ZipName1%" msvcr110.dll
"%WinRarRoot%\Rar.exe" u -s- -m1 -ap"release" 			"%ZipName1%" eSDKClientPlatform_config.ini
"%WinRarRoot%\Rar.exe" u -s- -m1 -ap"release" 			"%ZipName1%" eSDKSSO_config.ini
"%WinRarRoot%\Rar.exe" u -s- -m1 -ap"release" 			"%ZipName1%" ProductInfo.ini
"%WinRarRoot%\Rar.exe" u -s- -m1 -ap"release" 			"%ZipName1%" UpdateVersion_config.ini
"%WinRarRoot%\Rar.exe" u -s- -m1 -ap"release" 			"%ZipName1%" .\SDK\UCSDK\*.dll
"%WinRarRoot%\Rar.exe" u -s- -m1 -ap"release" 			"%ZipName1%" .\SDK\UCSDK\*.lib
"%WinRarRoot%\Rar.exe" u -s- -m1 -ap"release" 			"%ZipName1%" .\SDK\UCSDK\*.ini
"%WinRarRoot%\Rar.exe" u -s- -m1 -ap"release" 			"%ZipName1%" .\SDK\UCSDK\*.xml
"%WinRarRoot%\Rar.exe" u -s- -m1 -ap"release" 			"%ZipName1%" .\SDK\UCSDK\config\*.conf

::--------------------------------------------------------------------------------

::����ļ� eSDKSSO_COM
(chdir %ProjectPath%\COM_eSDKSSO)
"%WinRarRoot%\Rar.exe" u -s- -m1 -ap"include" 			"%ZipName2%" COM_eSDKSSO_i.c
"%WinRarRoot%\Rar.exe" u -s- -m1 -ap"include" 			"%ZipName2%" COM_eSDKSSO_i.h

(chdir %ReleasePath%\)
"%WinRarRoot%\Rar.exe" u -s- -m1 -ap"release" 			"%ZipName2%" auth.dll
"%WinRarRoot%\Rar.exe" u -s- -m1 -ap"release" 			"%ZipName2%" auth.lib
"%WinRarRoot%\Rar.exe" u -s- -m1 -ap"release" 			"%ZipName2%" COM_eSDKSSO.dll
"%WinRarRoot%\Rar.exe" u -s- -m1 -ap"release" 			"%ZipName2%" COM_eSDKSSO.lib
"%WinRarRoot%\Rar.exe" u -s- -m1 -ap"release" 			"%ZipName2%" eSDKSSO.dll
"%WinRarRoot%\Rar.exe" u -s- -m1 -ap"release" 			"%ZipName2%" eSDKSSO.lib
"%WinRarRoot%\Rar.exe" u -s- -m1 -ap"release" 			"%ZipName2%" eSDKTool.dll
"%WinRarRoot%\Rar.exe" u -s- -m1 -ap"release" 			"%ZipName2%" eSDKTool.lib
"%WinRarRoot%\Rar.exe" u -s- -m1 -ap"release" 			"%ZipName2%" SSOAdapter.dll
"%WinRarRoot%\Rar.exe" u -s- -m1 -ap"release" 			"%ZipName2%" SSOAdapter.lib
"%WinRarRoot%\Rar.exe" u -s- -m1 -ap"release" 			"%ZipName2%" log4cpp.dll
"%WinRarRoot%\Rar.exe" u -s- -m1 -ap"release" 			"%ZipName2%" cpprest110_1_2.dll
"%WinRarRoot%\Rar.exe" u -s- -m1 -ap"release" 			"%ZipName2%" msvcp110.dll
"%WinRarRoot%\Rar.exe" u -s- -m1 -ap"release" 			"%ZipName2%" msvcr110.dll
"%WinRarRoot%\Rar.exe" u -s- -m1 -ap"release" 			"%ZipName2%" eSDKSSO_config.ini
"%WinRarRoot%\Rar.exe" u -s- -m1 -ap"release" 			"%ZipName2%" setup.bat

::--------------------------------------------------------------------------------

::����ļ� VersionUpdate
(chdir %ProjectPath%\UpdateVersion\Header)
"%WinRarRoot%\Rar.exe" u -s- -m1 -ap"include" 			"%ZipName3%" UpdateVersion.h
"%WinRarRoot%\Rar.exe" u -s- -m1 -ap"include" 			"%ZipName3%" UpgradeVersion.h

(chdir %DebugPath%\)
"%WinRarRoot%\Rar.exe" u -s- -m1 -ap"debug" 			"%ZipName3%" UpdateAdapter.dll
"%WinRarRoot%\Rar.exe" u -s- -m1 -ap"debug" 			"%ZipName3%" UpdateAdapter.lib
"%WinRarRoot%\Rar.exe" u -s- -m1 -ap"debug" 			"%ZipName3%" UpdateVersion.dll
"%WinRarRoot%\Rar.exe" u -s- -m1 -ap"debug" 			"%ZipName3%" UpdateVersion.lib
"%WinRarRoot%\Rar.exe" u -s- -m1 -ap"debug" 			"%ZipName3%" eSDKTool.dll
"%WinRarRoot%\Rar.exe" u -s- -m1 -ap"debug" 			"%ZipName3%" eSDKTool.lib
"%WinRarRoot%\Rar.exe" u -s- -m1 -ap"debug" 			"%ZipName3%" log4cppd.dll
"%WinRarRoot%\Rar.exe" u -s- -m1 -ap"debug" 			"%ZipName3%" cpprest110_1_2.dll
"%WinRarRoot%\Rar.exe" u -s- -m1 -ap"debug" 			"%ZipName3%" zlibwapi.dll
"%WinRarRoot%\Rar.exe" u -s- -m1 -ap"debug" 			"%ZipName3%" msvcp110.dll
"%WinRarRoot%\Rar.exe" u -s- -m1 -ap"debug" 			"%ZipName3%" msvcr110.dll
"%WinRarRoot%\Rar.exe" u -s- -m1 -ap"debug" 			"%ZipName3%" ProductInfo.ini
"%WinRarRoot%\Rar.exe" u -s- -m1 -ap"debug" 			"%ZipName3%" UpdateVersion_config.ini

(chdir %ReleasePath%\)
"%WinRarRoot%\Rar.exe" u -s- -m1 -ap"release" 			"%ZipName3%" UpdateAdapter.dll
"%WinRarRoot%\Rar.exe" u -s- -m1 -ap"release" 			"%ZipName3%" UpdateAdapter.lib
"%WinRarRoot%\Rar.exe" u -s- -m1 -ap"release" 			"%ZipName3%" UpdateVersion.dll
"%WinRarRoot%\Rar.exe" u -s- -m1 -ap"release" 			"%ZipName3%" UpdateVersion.lib
"%WinRarRoot%\Rar.exe" u -s- -m1 -ap"release" 			"%ZipName3%" eSDKTool.dll
"%WinRarRoot%\Rar.exe" u -s- -m1 -ap"release" 			"%ZipName3%" eSDKTool.lib
"%WinRarRoot%\Rar.exe" u -s- -m1 -ap"release" 			"%ZipName3%" log4cpp.dll
"%WinRarRoot%\Rar.exe" u -s- -m1 -ap"release" 			"%ZipName3%" cpprest110_1_2.dll
"%WinRarRoot%\Rar.exe" u -s- -m1 -ap"release" 			"%ZipName3%" zlibwapi.dll
"%WinRarRoot%\Rar.exe" u -s- -m1 -ap"release" 			"%ZipName3%" msvcp110.dll
"%WinRarRoot%\Rar.exe" u -s- -m1 -ap"release" 			"%ZipName3%" msvcr110.dll
"%WinRarRoot%\Rar.exe" u -s- -m1 -ap"release" 			"%ZipName3%" ProductInfo.ini
"%WinRarRoot%\Rar.exe" u -s- -m1 -ap"release" 			"%ZipName3%" UpdateVersion_config.ini

::--------------------------------------------------------------------------------

pause
