// ComIdl_eSDKSSO.h : CComIdl_eSDKSSO 的声明

#pragma once
#include "resource.h"       // 主符号

#include "COM_eSDKSSO_i.h"


#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Windows CE 平台(如不提供完全 DCOM 支持的 Windows Mobile 平台)上无法正确支持单线程 COM 对象。定义 _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA 可强制 ATL 支持创建单线程 COM 对象实现并允许使用其单线程 COM 对象实现。rgs 文件中的线程模型已被设置为“Free”，原因是该模型是非 DCOM Windows CE 平台支持的唯一线程模型。"
#endif



// CComIdl_eSDKSSO

class ATL_NO_VTABLE CComIdl_eSDKSSO :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CComIdl_eSDKSSO, &CLSID_ComIdl_eSDKSSO>,
	public IDispatchImpl<IComIdl_eSDKSSO, &IID_IComIdl_eSDKSSO, &LIBID_COM_eSDKSSOLib, /*wMajor =*/ 1, /*wMinor =*/ 0>
{
public:
	CComIdl_eSDKSSO()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_COMIDL_ESDKSSO)
DECLARE_CLASSFACTORY_SINGLETON(CComIdl_eSDKSSO)

BEGIN_COM_MAP(CComIdl_eSDKSSO)
	COM_INTERFACE_ENTRY(IComIdl_eSDKSSO)
	COM_INTERFACE_ENTRY(IDispatch)
END_COM_MAP()



	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
		return S_OK;
	}

	void FinalRelease()
	{
	}

public:

	STDMETHOD(WriteToken)(BSTR Credential);
	STDMETHOD(ClearToken)(void);
	STDMETHOD(GetToken)(BSTR* Token);
	STDMETHOD(SSOLogin)(BSTR name, BSTR password, BSTR SSOuri);
};

OBJECT_ENTRY_AUTO(__uuidof(ComIdl_eSDKSSO), CComIdl_eSDKSSO)
