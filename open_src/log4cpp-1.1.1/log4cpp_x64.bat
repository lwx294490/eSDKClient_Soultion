@echo off

echo.
echo гнгнгнгнгн ▒р╥ы log4cpp_x64 Debug ░ц▒╛ start гнгнгнгнгнгнгнгнгнгнгнгнгн
@"%VS90COMNTOOLS%\..\IDE\devenv.com" .\log4cpp\msvc9\log4cpp\log4cpp.vcproj /Rebuild "Debug|x64"
echo гнгнгнгнгн ▒р╥ы zlib Debug ░ц▒╛ end гнгнгнгнгнгнгнгнгнгнгнгнгн

echo.
echo гнгнгнгнгн ▒р╥ы log4cpp_x64 Release ░ц▒╛ start гнгнгнгнгнгнгнгнгнгнгнгнгн
@"%VS90COMNTOOLS%\..\IDE\devenv.com" .\log4cpp\msvc9\log4cpp\log4cpp.vcproj /Rebuild "Release|x64"
echo гнгнгнгнгн ▒р╥ы zlib Release ░ц▒╛ end гнгнгнгнгнгнгнгнгнгнгнгнгн


::╥╘╧┬╩╟▒р╥ы║є┐╜▒┤гм╘▌╧╚╫в╩═
xcopy /Y .\log4cpp\msvc9\log4cpp\x64\Debug\log4cppd.lib .\debug_x64\
xcopy /Y .\log4cpp\msvc9\log4cpp\x64\Release\log4cpp.lib .\release_x64\

pause
