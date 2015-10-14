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
set ZipName=%ZipPath%\eSDKSSO_COM_v110.zip

::编译生成目录
set ReleasePath=%ProjectPath%\output\release_v110

::--------------------------------------------------------------------------------

::拷贝文件
xcopy /y ..\..\platform\config\eSDKSSO_config.ini 							"%ReleasePath%\"
xcopy /y ..\..\platform\config\setup.bat									"%ReleasePath%\"
xcopy /y ..\..\open_src\log4cpp\release_vc11\log4cpp.dll					"%ReleasePath%\"
xcopy /y ..\..\open_src\cpprest\release\dll\cpprest110_1_2.dll 				"%ReleasePath%\"
xcopy /y "..\..\third_party\Microsoft Visual Studio 11.0\x86\msvcp110.dll" 	"%ReleasePath%\"
xcopy /y "..\..\third_party\Microsoft Visual Studio 11.0\x86\msvcr110.dll" 	"%ReleasePath%\"
xcopy /y "..\..\third_party\Microsoft Visual Studio 11.0\x86\atl110.dll" 	"%ReleasePath%\"

::--------------------------------------------------------------------------------

::编译工程
@"%VS110COMNTOOLS%\..\IDE\devenv.com" 	.\SSOAdapter\SSOAdapter.vcxproj /Rebuild "Release|Win32"
@"%VS110COMNTOOLS%\..\IDE\devenv.com" 	.\eSDKSSO_COM_v110.sln 			/Rebuild "Release|Win32"

::--------------------------------------------------------------------------------

::设置各变量名
set	WinRarRoot=C:\Program Files\WinRAR

::创建目录
mkdir "%ZipPath%\"

::打包文件
(chdir .\COM_eSDKSSO_v110)
"%WinRarRoot%\Rar.exe" u -s- -m1 -ap"include" 	"%ZipName%" COM_eSDKSSO_i.c
"%WinRarRoot%\Rar.exe" u -s- -m1 -ap"include" 	"%ZipName%" COM_eSDKSSO_i.h

(chdir %ReleasePath%\)
"%WinRarRoot%\Rar.exe" u -s- -m1 -ap"release" 	"%ZipName%" "*.dll"
"%WinRarRoot%\Rar.exe" u -s- -m1 -ap"release" 	"%ZipName%" "*.lib"
"%WinRarRoot%\Rar.exe" u -s- -m1 -ap"release" 	"%ZipName%" "*.ini"
"%WinRarRoot%\Rar.exe" u -s- -m1 -ap"release" 	"%ZipName%" "*.bat"

pause
