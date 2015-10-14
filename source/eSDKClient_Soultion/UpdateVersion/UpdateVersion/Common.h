#ifndef _UPDATE_COMMON_H_
#define _UPDATE_COMMON_H_


//∑¿¿À”ø ±º‰(300 - 3600)
#define DLL_FILE_NAME "UpdateVersion.dll"
#define CONF_FILE_NAME "UpdateVersion_config.ini"

#define AVERT_SURGE_CONFIG_SECTION "AvertSurgeTime"
#define AVERT_SURGE_CONFIG_KEYMINT "timeMin"
#define AVERT_SURGE_CONFIG_KEYMAXT "timeMax"

#define AVERT_SURGE_TIME_MIN		5//300
#define AVERT_SURGE_TIME_MAX		10//1800

#define PRODUCT_INFO_FILE			("ProductInfo.ini")
#define PDU_INI_KEY_NAME			("Name")
#define PDU_INI_KEY_ID				("Id")

#define VERSION_FILE_NAME			("Version.ini")
#define VER_INI_SECTION				("Name")
#define VER_INI_KEY_ID				("Id")
#define VER_INI_KEY_VERSION			("Version")

#define README_TXT_FILE				("readme.txt")

#define DOWNLOAD_DIR_NAME			("temp")

#define VERSION_INFO_FILE			("version.txt")
#define VERSION_NAME_FIELD			("Name=")
#define VERSION_ID_FIELD			("Id=")
#define VERSION_VERSION_FIELD		("Version=")
#define VERSION_DATE_FIELD			("Date=")
#define VERSION_FORCE_FIELD			("IsforceUpdate=")
#define VERSION_INSTALL_FIELD		("IsInstallPackage=")

#define VERSION_READ_LENGTH			100
#define SHELL_EXECUTE_HANDLE		32

//#define VERSION_URI					"esdk_platform_upgrade/upgrade/version"



typedef enum
{
	THREAD_EXIT_ERR = -1,
	THREAD_EXIT_SUCC = 0
} UPDATE_THREAD_E;

#endif
