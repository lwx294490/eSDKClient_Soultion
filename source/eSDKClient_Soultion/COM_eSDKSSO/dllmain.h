// dllmain.h : 模块类的声明。
#ifndef _SSO_HEADER_
#define _SSO_HEADER_

class CCOM_eSDKSSOModule : public CAtlDllModuleT< CCOM_eSDKSSOModule >
{
public :
	DECLARE_LIBID(LIBID_COM_eSDKSSOLib)
	DECLARE_REGISTRY_APPID_RESOURCEID(IDR_COM_ESDKSSO, "{1EB40D69-5361-41EC-9425-6958F424C35A}")
};

extern class CCOM_eSDKSSOModule _AtlModule;

#endif
