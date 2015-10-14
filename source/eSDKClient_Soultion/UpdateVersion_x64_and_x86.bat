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
set ZipName=%ZipPath%\UpdateVersion_x64_and_x86.zip

::��������Ŀ¼
set DebugPath64=%ProjectPath%\output\debug_x64
set ReleasePath64=%ProjectPath%\output\release_x64
set DebugPath86=%ProjectPath%\output\debug
set ReleasePath86=%ProjectPath%\output\release

::--------------------------------------------------------------------------------

::�����ļ�
xcopy /y ..\..\platform\config\ProductInfo.ini 								"%DebugPath64%\"
xcopy /y ..\..\platform\config\UpdateVersion_config.ini 					"%DebugPath64%\"
xcopy /y ..\..\open_src\cpprest\release_x64\dll\cpprest110_1_2.dll 			"%DebugPath64%\"
xcopy /y ..\..\open_src\zlib\debug_x64\dll\zlibwapi.dll 					"%DebugPath64%\"
xcopy /y "..\..\third_party\Microsoft Visual Studio 9.0\x64\msvcp90.dll" 	"%DebugPath64%\"
xcopy /y "..\..\third_party\Microsoft Visual Studio 9.0\x64\msvcr90.dll" 	"%DebugPath64%\"
xcopy /y "..\..\third_party\Microsoft Visual Studio 11.0\x64\msvcp110.dll" 	"%DebugPath64%\"
xcopy /y "..\..\third_party\Microsoft Visual Studio 11.0\x64\msvcr110.dll" 	"%DebugPath64%\"

xcopy /y ..\..\platform\config\ProductInfo.ini 								"%ReleasePath64%\"
xcopy /y ..\..\platform\config\UpdateVersion_config.ini 					"%ReleasePath64%\"
xcopy /y ..\..\open_src\cpprest\release_x64\dll\cpprest110_1_2.dll 			"%ReleasePath64%\"
xcopy /y ..\..\open_src\zlib\release_x64\dll\zlibwapi.dll 					"%ReleasePath64%\"
xcopy /y "..\..\third_party\Microsoft Visual Studio 9.0\x64\msvcp90.dll" 	"%ReleasePath64%\"
xcopy /y "..\..\third_party\Microsoft Visual Studio 9.0\x64\msvcr90.dll" 	"%ReleasePath64%\"
xcopy /y "..\..\third_party\Microsoft Visual Studio 11.0\x64\msvcp110.dll" 	"%ReleasePath64%\"
xcopy /y "..\..\third_party\Microsoft Visual Studio 11.0\x64\msvcr110.dll" 	"%ReleasePath64%\"

::�����ļ�
xcopy /y ..\..\platform\HWUCSDK\windows\eSpace_Desktop_V200R001C03SPCB00B030\debug\dll\log4cppd.dll 	"%DebugPath86%\"
xcopy /y ..\..\platform\config\ProductInfo.ini															"%DebugPath86%\"
xcopy /y ..\..\platform\config\UpdateVersion_config.ini													"%DebugPath86%\"
xcopy /y ..\..\open_src\cpprest\release\dll\cpprest110_1_2.dll 											"%DebugPath86%\"
xcopy /y ..\..\open_src\zlib\debug\dll\zlibwapi.dll			 											"%DebugPath86%\"
xcopy /y "..\..\third_party\Microsoft Visual Studio 11.0\x86\msvcp110.dll" 								"%DebugPath86%\"
xcopy /y "..\..\third_party\Microsoft Visual Studio 11.0\x86\msvcr110.dll" 								"%DebugPath86%\"

xcopy /y ..\..\platform\HWUCSDK\windows\eSpace_Desktop_V200R001C03SPCB00B030\release\dll\log4cpp.dll 	"%ReleasePath86%\"
xcopy /y ..\..\platform\config\ProductInfo.ini															"%ReleasePath86%\"
xcopy /y ..\..\platform\config\UpdateVersion_config.ini													"%ReleasePath86%\"
xcopy /y ..\..\open_src\cpprest\release\dll\cpprest110_1_2.dll 											"%ReleasePath86%\"
xcopy /y ..\..\open_src\zlib\release\dll\zlibwapi.dll			 										"%ReleasePath86%\"
xcopy /y "..\..\third_party\Microsoft Visual Studio 11.0\x86\msvcp110.dll" 								"%ReleasePath86%\"
xcopy /y "..\..\third_party\Microsoft Visual Studio 11.0\x86\msvcr110.dll" 								"%ReleasePath86%\"

::--------------------------------------------------------------------------------

::���빤�� x64
@"%VS110COMNTOOLS%\..\IDE\devenv.com" 	.\UpdateAdapter_x64.sln 				/Rebuild "Release|x64"
::������debugĿ¼
xcopy /Y "%ReleasePath64%\UpdateAdapter.dll" 	"%DebugPath64%\"
xcopy /Y "%ReleasePath64%\UpdateAdapter.lib" 	"%DebugPath64%\"
::���빤��
@"%VS90COMNTOOLS%\..\IDE\devenv.com" 	.\UpdateVersion_x64.sln 				/Rebuild "Debug|x64"
@"%VS90COMNTOOLS%\..\IDE\devenv.com" 	.\UpdateVersion_x64.sln 				/Rebuild "Release|x64"


::���빤�� x86
@"%VS110COMNTOOLS%\..\IDE\devenv.com" 	.\UpdateAdapter\UpdateAdapter.vcxproj 	/Rebuild "Release|Win32"
::������debugĿ¼
xcopy /Y "%ReleasePath86%\UpdateAdapter.dll" 	"%DebugPath86%\"
xcopy /Y "%ReleasePath86%\UpdateAdapter.lib" 	"%DebugPath86%\"
::���빤��
@"%VS90COMNTOOLS%\..\IDE\devenv.com" 	.\eSDKTool\eSDKTool.vcproj 				/Rebuild "Debug|Win32"
@"%VS90COMNTOOLS%\..\IDE\devenv.com" 	.\eSDKTool\eSDKTool.vcproj 				/Rebuild "Release|Win32"
@"%VS90COMNTOOLS%\..\IDE\devenv.com" 	.\UpdateVersion\UpdateVersion.vcproj 	/Rebuild "Debug|Win32"
@"%VS90COMNTOOLS%\..\IDE\devenv.com" 	.\UpdateVersion\UpdateVersion.vcproj 	/Rebuild "Release|Win32"

::--------------------------------------------------------------------------------

::���ø�������
set	WinRarRoot=C:\Program Files\WinRAR

::����Ŀ¼
mkdir "%ZipPath%\"

::����ļ� VersionUpdate_x64
(chdir %ProjectPath%\UpdateVersion_x64\Header\)
"%WinRarRoot%\Rar.exe" u -s- -m1 -ap"x64\include\C" 	"%ZipName%" UpgradeVersion.h
"%WinRarRoot%\Rar.exe" u -s- -m1 -ap"x64\include\C++" 	"%ZipName%" UpdateVersion.h

(chdir %DebugPath64%\)
"%WinRarRoot%\Rar.exe" u -s- -m1 -ap"x64\debug_x64" 	"%ZipName%" "*.dll"
"%WinRarRoot%\Rar.exe" u -s- -m1 -ap"x64\debug_x64" 	"%ZipName%" "*.lib"
"%WinRarRoot%\Rar.exe" u -s- -m1 -ap"x64\debug_x64" 	"%ZipName%" "*.ini"

(chdir %ReleasePath64%\)
"%WinRarRoot%\Rar.exe" u -s- -m1 -ap"x64\release_x64" 	"%ZipName%" "*.dll"
"%WinRarRoot%\Rar.exe" u -s- -m1 -ap"x64\release_x64" 	"%ZipName%" "*.lib"
"%WinRarRoot%\Rar.exe" u -s- -m1 -ap"x64\release_x64" 	"%ZipName%" "*.ini"

::--------------------------------------------------------------------------------

::����ļ� VersionUpdate_x86
(chdir %ProjectPath%\UpdateVersion\Header)
"%WinRarRoot%\Rar.exe" u -s- -m1 -ap"x86\include\C" 	"%ZipName%" UpgradeVersion.h
"%WinRarRoot%\Rar.exe" u -s- -m1 -ap"x86\include\C++" 	"%ZipName%" UpdateVersion.h

(chdir %DebugPath86%\)
"%WinRarRoot%\Rar.exe" u -s- -m1 -ap"x86\debug" 		"%ZipName%" UpdateAdapter.dll
"%WinRarRoot%\Rar.exe" u -s- -m1 -ap"x86\debug" 		"%ZipName%" UpdateAdapter.lib
"%WinRarRoot%\Rar.exe" u -s- -m1 -ap"x86\debug" 		"%ZipName%" UpdateVersion.dll
"%WinRarRoot%\Rar.exe" u -s- -m1 -ap"x86\debug" 		"%ZipName%" UpdateVersion.lib
"%WinRarRoot%\Rar.exe" u -s- -m1 -ap"x86\debug" 		"%ZipName%" eSDKTool.dll
"%WinRarRoot%\Rar.exe" u -s- -m1 -ap"x86\debug" 		"%ZipName%" eSDKTool.lib
"%WinRarRoot%\Rar.exe" u -s- -m1 -ap"x86\debug" 		"%ZipName%" log4cppd.dll
"%WinRarRoot%\Rar.exe" u -s- -m1 -ap"x86\debug" 		"%ZipName%" cpprest110_1_2.dll
"%WinRarRoot%\Rar.exe" u -s- -m1 -ap"x86\debug" 		"%ZipName%" zlibwapi.dll
"%WinRarRoot%\Rar.exe" u -s- -m1 -ap"x86\debug" 		"%ZipName%" msvcp110.dll
"%WinRarRoot%\Rar.exe" u -s- -m1 -ap"x86\debug" 		"%ZipName%" msvcr110.dll
"%WinRarRoot%\Rar.exe" u -s- -m1 -ap"x86\debug" 		"%ZipName%" ProductInfo.ini
"%WinRarRoot%\Rar.exe" u -s- -m1 -ap"x86\debug" 		"%ZipName%" UpdateVersion_config.ini

(chdir %ReleasePath86%\)
"%WinRarRoot%\Rar.exe" u -s- -m1 -ap"x86\release" 		"%ZipName%" UpdateAdapter.dll
"%WinRarRoot%\Rar.exe" u -s- -m1 -ap"x86\release" 		"%ZipName%" UpdateAdapter.lib
"%WinRarRoot%\Rar.exe" u -s- -m1 -ap"x86\release" 		"%ZipName%" UpdateVersion.dll
"%WinRarRoot%\Rar.exe" u -s- -m1 -ap"x86\release" 		"%ZipName%" UpdateVersion.lib
"%WinRarRoot%\Rar.exe" u -s- -m1 -ap"x86\release" 		"%ZipName%" eSDKTool.dll
"%WinRarRoot%\Rar.exe" u -s- -m1 -ap"x86\release" 		"%ZipName%" eSDKTool.lib
"%WinRarRoot%\Rar.exe" u -s- -m1 -ap"x86\release" 		"%ZipName%" log4cpp.dll
"%WinRarRoot%\Rar.exe" u -s- -m1 -ap"x86\release" 		"%ZipName%" cpprest110_1_2.dll
"%WinRarRoot%\Rar.exe" u -s- -m1 -ap"x86\release" 		"%ZipName%" zlibwapi.dll
"%WinRarRoot%\Rar.exe" u -s- -m1 -ap"x86\release" 		"%ZipName%" msvcp110.dll
"%WinRarRoot%\Rar.exe" u -s- -m1 -ap"x86\release" 		"%ZipName%" msvcr110.dll
"%WinRarRoot%\Rar.exe" u -s- -m1 -ap"x86\release" 		"%ZipName%" ProductInfo.ini
"%WinRarRoot%\Rar.exe" u -s- -m1 -ap"x86\release" 		"%ZipName%" UpdateVersion_config.ini

::--------------------------------------------------------------------------------

pause
