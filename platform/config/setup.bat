@echo off

set PATH=%CD%;%PATH%
regsvr32  /s COM_eSDKSSO.dll

@echo on