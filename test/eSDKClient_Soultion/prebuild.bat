@echo off

::¿½±´debug
xcopy /Y ..\..\source\eSDKClient_Soultion\output\debug\*.dll .\output\debug\
xcopy /Y ..\..\source\eSDKClient_Soultion\output\debug\*.lib .\output\debug\
xcopy /Y ..\..\source\eSDKClient_Soultion\output\debug\*.pdb .\output\debug\

xcopy /Y ..\..\source\eSDKClient_Soultion\output\debug\SDK\UCSDK\*.dll .\output\debug\SDK\UCSDK\
xcopy /Y ..\..\source\eSDKClient_Soultion\output\debug\SDK\UCSDK\*.lib .\output\debug\SDK\UCSDK\
xcopy /Y ..\..\source\eSDKClient_Soultion\output\debug\SDK\UCSDK\*.pdb .\output\debug\SDK\UCSDK\

xcopy /Y ..\..\platform\HWUCSDK\windows\eSpace_Desktop_V200R001C03SPCB00B030\debug\dll\*.dll .\output\debug\SDK\UCSDK\
xcopy /Y ..\..\platform\HWUCSDK\windows\eSpace_Desktop_V200R001C03SPCB00B030\debug\dll\*.ini .\output\debug\SDK\UCSDK\
xcopy /Y ..\..\platform\HWUCSDK\windows\eSpace_Desktop_V200R001C03SPCB00B030\debug\dll\*.xml .\output\debug\SDK\UCSDK\
xcopy /Y ..\..\platform\HWUCSDK\windows\eSpace_Desktop_V200R001C03SPCB00B030\debug\dll\config\*.conf .\output\debug\SDK\UCSDK\config\

xcopy /Y ..\..\platform\config\eSDKClientPlatform_config.ini .\output\debug\
xcopy /Y ..\..\platform\config\eSDKSSO_config.ini .\output\debug\
xcopy /Y ..\..\platform\config\ProductInfo.ini .\output\debug\
xcopy /Y ..\..\platform\config\UpdateVersion_config.ini .\output\debug\
xcopy /Y ..\..\platform\config\UCSDK_config.ini .\output\debug\SDK\UCSDK\

xcopy /Y ..\..\open_src\zlib\release\dll\*.dll .\output\debug\


::¿½±´release
xcopy /Y ..\..\source\eSDKClient_Soultion\output\release\*.dll .\output\release\
xcopy /Y ..\..\source\eSDKClient_Soultion\output\release\*.lib .\output\release\
xcopy /Y ..\..\source\eSDKClient_Soultion\output\release\*.pdb .\output\release\

xcopy /Y ..\..\source\eSDKClient_Soultion\output\release\SDK\UCSDK\*.dll .\output\release\SDK\UCSDK\
xcopy /Y ..\..\source\eSDKClient_Soultion\output\release\SDK\UCSDK\*.lib .\output\release\SDK\UCSDK\
xcopy /Y ..\..\source\eSDKClient_Soultion\output\release\SDK\UCSDK\*.pdb .\output\release\SDK\UCSDK\

xcopy /Y ..\..\platform\HWUCSDK\windows\eSpace_Desktop_V200R001C03SPCB00B030\release\dll\*.dll .\output\release\SDK\UCSDK\
xcopy /Y ..\..\platform\HWUCSDK\windows\eSpace_Desktop_V200R001C03SPCB00B030\release\dll\*.ini .\output\release\SDK\UCSDK\
xcopy /Y ..\..\platform\HWUCSDK\windows\eSpace_Desktop_V200R001C03SPCB00B030\release\dll\*.xml .\output\release\SDK\UCSDK\
xcopy /Y ..\..\platform\HWUCSDK\windows\eSpace_Desktop_V200R001C03SPCB00B030\release\dll\config\*.conf .\output\release\SDK\UCSDK\config\

xcopy /Y ..\..\platform\config\eSDKClientPlatform_config.ini .\output\release\
xcopy /Y ..\..\platform\config\eSDKSSO_config.ini .\output\release\
xcopy /Y ..\..\platform\config\ProductInfo.ini .\output\release\
xcopy /Y ..\..\platform\config\UpdateVersion_config.ini .\output\release\
xcopy /Y ..\..\platform\config\UCSDK_config.ini .\output\release\SDK\UCSDK\

xcopy /Y ..\..\open_src\zlib\release\dll\*.dll .\output\release\