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
set ZipName=%ZipPath%\eSDKSSO_COM_v110.zip

::��������Ŀ¼
set ReleasePath=%ProjectPath%\output\release_v110

::--------------------------------------------------------------------------------

::�����ļ�
xcopy /y ..\..\platform\config\eSDKSSO_config.ini 							"%ReleasePath%\"
xcopy /y ..\..\platform\config\setup.bat									"%ReleasePath%\"
xcopy /y ..\..\open_src\log4cpp\release_vc11\log4cpp.dll					"%ReleasePath%\"
xcopy /y ..\..\open_src\cpprest\release\dll\cpprest110_1_2.dll 				"%ReleasePath%\"
xcopy /y "..\..\third_party\Microsoft Visual Studio 11.0\x86\msvcp110.dll" 	"%ReleasePath%\"
xcopy /y "..\..\third_party\Microsoft Visual Studio 11.0\x86\msvcr110.dll" 	"%ReleasePath%\"
xcopy /y "..\..\third_party\Microsoft Visual Studio 11.0\x86\atl110.dll" 	"%ReleasePath%\"

::--------------------------------------------------------------------------------

::���빤��
@"%VS110COMNTOOLS%\..\IDE\devenv.com" 	.\SSOAdapter\SSOAdapter.vcxproj /Rebuild "Release|Win32"
@"%VS110COMNTOOLS%\..\IDE\devenv.com" 	.\eSDKSSO_COM_v110.sln 			/Rebuild "Release|Win32"

::--------------------------------------------------------------------------------

::���ø�������
set	WinRarRoot=C:\Program Files\WinRAR

::����Ŀ¼
mkdir "%ZipPath%\"

::����ļ�
(chdir .\COM_eSDKSSO_v110)
"%WinRarRoot%\Rar.exe" u -s- -m1 -ap"include" 	"%ZipName%" COM_eSDKSSO_i.c
"%WinRarRoot%\Rar.exe" u -s- -m1 -ap"include" 	"%ZipName%" COM_eSDKSSO_i.h

(chdir %ReleasePath%\)
"%WinRarRoot%\Rar.exe" u -s- -m1 -ap"release" 	"%ZipName%" "*.dll"
"%WinRarRoot%\Rar.exe" u -s- -m1 -ap"release" 	"%ZipName%" "*.lib"
"%WinRarRoot%\Rar.exe" u -s- -m1 -ap"release" 	"%ZipName%" "*.ini"
"%WinRarRoot%\Rar.exe" u -s- -m1 -ap"release" 	"%ZipName%" "*.bat"

pause
