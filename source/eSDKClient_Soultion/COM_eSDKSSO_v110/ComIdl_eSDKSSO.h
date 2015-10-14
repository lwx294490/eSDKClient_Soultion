// ComIdl_eSDKSSO.h : CComIdl_eSDKSSO ������

#pragma once
#include "resource.h"       // ������

#include "COM_eSDKSSO_i.h"


#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Windows CE ƽ̨(�粻�ṩ��ȫ DCOM ֧�ֵ� Windows Mobile ƽ̨)���޷���ȷ֧�ֵ��߳� COM ���󡣶��� _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA ��ǿ�� ATL ֧�ִ������߳� COM ����ʵ�ֲ�����ʹ���䵥�߳� COM ����ʵ�֡�rgs �ļ��е��߳�ģ���ѱ�����Ϊ��Free����ԭ���Ǹ�ģ���Ƿ� DCOM Windows CE ƽ̨֧�ֵ�Ψһ�߳�ģ�͡�"
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
