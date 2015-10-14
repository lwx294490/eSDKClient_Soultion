@echo off

echo.
echo гнгнгнгнгн ▒р╥ы Log4cpp Debug ░ц▒╛ start гнгнгнгнгнгнгнгнгнгнгнгнгн
@"%VS90COMNTOOLS%\..\IDE\devenv.com" .\log4cpp\msvc9\msvc9.sln /Rebuild "Debug|Win32" /out builddebug.log
echo.
echo гнгнгнгнгн ▒р╥ы Log4cpp Debug ░ц▒╛ success гнгнгнгнгнгнгнгнгнгнгнгнгн


echo.
echo гнгнгнгнгн ▒р╥ы Log4cpp Release ░ц▒╛ start гнгнгнгнгнгнгнгнгнгнгнгнгн
@"%VS90COMNTOOLS%\..\IDE\devenv.com" .\log4cpp\msvc9\msvc9.sln /Rebuild "Release|Win32" /out buildrelease.log
echo.
echo гнгнгнгнгн ▒р╥ы Log4cpp Release ░ц▒╛ success гнгнгнгнгнгнгнгнгнгнгнгнгн

pause