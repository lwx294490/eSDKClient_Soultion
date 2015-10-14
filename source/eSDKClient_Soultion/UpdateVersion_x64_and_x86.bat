@echo off

::获得当前时间，作为生成版本的目录名
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

::设置各变量名
set DateTime=%Year%-%Month%-%Day%-%Hour%-%Minute%

::工程所在路径（sln路径），根据该脚本所在目录进行修改
set ProjectPath=%cd%

::生成的压缩包路径，根据要求进行修改
set ZipPath=%ProjectPath%\..\..\..\00.Release\%DateTime%
set ZipName=%ZipPath%\UpdateVersion_x64_and_x86.zip

::编译生成目录
set DebugPath64=%ProjectPath%\output\debug_x64
set ReleasePath64=%ProjectPath%\output\release_x64
set DebugPath86=%ProjectPath%\output\debug
set ReleasePath86=%ProjectPath%\output\release

::--------------------------------------------------------------------------------

::拷贝文件
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

::拷贝文件
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

::编译工程 x64
@"%VS110COMNTOOLS%\..\IDE\devenv.com" 	.\UpdateAdapter_x64.sln 				/Rebuild "Release|x64"
::拷贝到debug目录
xcopy /Y "%ReleasePath64%\UpdateAdapter.dll" 	"%DebugPath64%\"
xcopy /Y "%ReleasePath64%\UpdateAdapter.lib" 	"%DebugPath64%\"
::编译工程
@"%VS90COMNTOOLS%\..\IDE\devenv.com" 	.\UpdateVersion_x64.sln 				/Rebuild "Debug|x64"
@"%VS90COMNTOOLS%\..\IDE\devenv.com" 	.\UpdateVersion_x64.sln 				/Rebuild "Release|x64"


::编译工程 x86
@"%VS110COMNTOOLS%\..\IDE\devenv.com" 	.\UpdateAdapter\UpdateAdapter.vcxproj 	/Rebuild "Release|Win32"
::拷贝到debug目录
xcopy /Y "%ReleasePath86%\UpdateAdapter.dll" 	"%DebugPath86%\"
xcopy /Y "%ReleasePath86%\UpdateAdapter.lib" 	"%DebugPath86%\"
::编译工程
@"%VS90COMNTOOLS%\..\IDE\devenv.com" 	.\eSDKTool\eSDKTool.vcproj 				/Rebuild "Debug|Win32"
@"%VS90COMNTOOLS%\..\IDE\devenv.com" 	.\eSDKTool\eSDKTool.vcproj 				/Rebuild "Release|Win32"
@"%VS90COMNTOOLS%\..\IDE\devenv.com" 	.\UpdateVersion\UpdateVersion.vcproj 	/Rebuild "Debug|Win32"
@"%VS90COMNTOOLS%\..\IDE\devenv.com" 	.\UpdateVersion\UpdateVersion.vcproj 	/Rebuild "Release|Win32"

::--------------------------------------------------------------------------------

::设置各变量名
set	WinRarRoot=C:\Program Files\WinRAR

::创建目录
mkdir "%ZipPath%\"

::打包文件 VersionUpdate_x64
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

::打包文件 VersionUpdate_x86
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
