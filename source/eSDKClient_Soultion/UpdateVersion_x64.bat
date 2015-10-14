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
set ZipName=%ZipPath%\UpdateVersion_x64.zip

::编译生成目录
set DebugPath=%ProjectPath%\output\debug_x64
set ReleasePath=%ProjectPath%\output\release_x64

::--------------------------------------------------------------------------------

::拷贝文件
xcopy /y ..\..\platform\config\ProductInfo.ini 								"%DebugPath%\"
xcopy /y ..\..\platform\config\UpdateVersion_config.ini 					"%DebugPath%\"
xcopy /y ..\..\open_src\cpprest\release_x64\dll\cpprest110_1_2.dll 			"%DebugPath%\"
xcopy /y ..\..\open_src\zlib\debug_x64\dll\zlibwapi.dll 					"%DebugPath%\"
xcopy /y "..\..\third_party\Microsoft Visual Studio 9.0\x64\msvcp90.dll" 	"%DebugPath%\"
xcopy /y "..\..\third_party\Microsoft Visual Studio 9.0\x64\msvcr90.dll" 	"%DebugPath%\"
xcopy /y "..\..\third_party\Microsoft Visual Studio 11.0\x64\msvcp110.dll" 	"%DebugPath%\"
xcopy /y "..\..\third_party\Microsoft Visual Studio 11.0\x64\msvcr110.dll" 	"%DebugPath%\"

xcopy /y ..\..\platform\config\ProductInfo.ini 								"%ReleasePath%\"
xcopy /y ..\..\platform\config\UpdateVersion_config.ini 					"%ReleasePath%\"
xcopy /y ..\..\open_src\cpprest\release_x64\dll\cpprest110_1_2.dll 			"%ReleasePath%\"
xcopy /y ..\..\open_src\zlib\release_x64\dll\zlibwapi.dll 					"%ReleasePath%\"
xcopy /y "..\..\third_party\Microsoft Visual Studio 9.0\x64\msvcp90.dll" 	"%ReleasePath%\"
xcopy /y "..\..\third_party\Microsoft Visual Studio 9.0\x64\msvcr90.dll" 	"%ReleasePath%\"
xcopy /y "..\..\third_party\Microsoft Visual Studio 11.0\x64\msvcp110.dll" 	"%ReleasePath%\"
xcopy /y "..\..\third_party\Microsoft Visual Studio 11.0\x64\msvcr110.dll" 	"%ReleasePath%\"

::--------------------------------------------------------------------------------

::编译工程
@"%VS110COMNTOOLS%\..\IDE\devenv.com" 	.\UpdateAdapter_x64.sln /Rebuild 	"Release|x64"
::拷贝到debug目录
xcopy /Y "%ReleasePath%\UpdateAdapter.dll" 	"%DebugPath%\"
xcopy /Y "%ReleasePath%\UpdateAdapter.lib" 	"%DebugPath%\"
::编译工程
@"%VS90COMNTOOLS%\..\IDE\devenv.com" 	.\UpdateVersion_x64.sln /Rebuild 	"Debug|x64"
@"%VS90COMNTOOLS%\..\IDE\devenv.com" 	.\UpdateVersion_x64.sln /Rebuild 	"Release|x64"

::--------------------------------------------------------------------------------

::设置各变量名
set	WinRarRoot=C:\Program Files\WinRAR

::创建目录
mkdir "%ZipPath%\"

::打包文件
(chdir .\UpdateVersion_x64\Header\)
"%WinRarRoot%\Rar.exe" u -s- -m1 -ap"include\C" 	"%ZipName%" UpgradeVersion.h
"%WinRarRoot%\Rar.exe" u -s- -m1 -ap"include\C++" 	"%ZipName%" UpdateVersion.h

(chdir %DebugPath%\)
"%WinRarRoot%\Rar.exe" u -s- -m1 -ap"debug_x64" 	"%ZipName%" "*.dll"
"%WinRarRoot%\Rar.exe" u -s- -m1 -ap"debug_x64" 	"%ZipName%" "*.lib"
"%WinRarRoot%\Rar.exe" u -s- -m1 -ap"debug_x64" 	"%ZipName%" "*.ini"

(chdir %ReleasePath%\)
"%WinRarRoot%\Rar.exe" u -s- -m1 -ap"release_x64" 	"%ZipName%" "*.dll"
"%WinRarRoot%\Rar.exe" u -s- -m1 -ap"release_x64" 	"%ZipName%" "*.lib"
"%WinRarRoot%\Rar.exe" u -s- -m1 -ap"release_x64" 	"%ZipName%" "*.ini"

pause
