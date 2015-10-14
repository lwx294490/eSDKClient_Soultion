#include <iostream>
#include <string.h>

#include "eSDKLogAPI.h"

using namespace std;

int main()
{
//	std::string strPath = "/gongjianming/new/eSDKLogAPI";
	std::string strPath = "";
	cout << strPath << endl;
	const char* str = "123";
	int i1 = 1;
	init(strPath.c_str());
	while(1)
	{
				char *str="123";
		int i = 100;
		Log_Interface_Info("UC","1","ParlayX","createGroup","10.68.160.1","10.68.160.112","ID12345678","2012/11/15 15:45:01 06","2012/11/15 15:45:01 345","0","name=%d,str=%s",i,str);
		Log_Interface_Error("IVS","2","native","interfaceName","127.0.0.3","127.0.0.4","ID12345678","2012/11/15 15:45:01 06","2012/11/15 15:45:01 345","0","i=%d,str=%s",i,str);
		Log_Operate_Debug("moduleName","username","clientFlag","resultCode","keyInfo","i=%d,str=%s",i,str);
		Log_Operate_Info("moduleName","username","clientFlag","resultCode","keyInfo","i=%d,str=%s",i,str);
		Log_Operate_Warn("moduleName","username","clientFlag","resultCode","keyInfo","i=%d,str=%s",i,str);
		Log_Operate_Error("moduleName","username","clientFlag","resultCode","keyInfo","i=%d,str=%s",i,str);
				Log_Run_Debug("param");
				Log_Run_Info("param");
				Log_Run_Warn("param");
				Log_Run_Error("param");
				sleep(1);
	}
	fini();
}
