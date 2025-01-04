#include "DXGIMngr.h"

using namespace Rubix::DirectX;

HRESULT Rubix::DirectX::DXGIMngr::AddAdapter(IDXGIFactory* pfactory, IDXGIAdapter* adap)
{
	if (pfactory == nullptr || adap == nullptr)
	{
		//logging
		return E_FAIL;
	}

	UINT idx = 0;
	int adaptersavailable_before = _available_adapters.size();
	while (pfactory->EnumAdapters(idx, &adap) != DXGI_ERROR_NOT_FOUND) 
	{
		_available_adapters.insert(adap);	
		++idx;
	}
	return _available_adapters.size() > adaptersavailable_before ? S_OK : E_FAIL;
}

HRESULT DXGIMngr::ListAvailableAdapters(Rubix::Definitions::RBXDEF::DXGI_VERSION dxgi_ver, UINT flags)
{
	HRESULT hr = 0;

	#ifdef DX11
		IDXGIFactory4* pfactory = nullptr;
		IDXGIAdapter3* adap = nullptr;
		hr = CreateDXGIFactory2(flags, __uuidof(IDXGIFactory4), (void**)(&pfactory));
		if (FAILED(hr)) { /*logging*/ return E_FAIL; }
		hr = AddAdapter(pfactory, adap);
		if (FAILED(hr)) { /*logging*/ return E_FAIL; }
	#elif defined(DX12) 
		IDXGIFactory5* pfactory = nullptr;
		IDXGIAdapter3* adap = nullptr;
		hr = CreateDXGIFactory2(flags, __uuidof(IDXGIFactory5), (void**)(&pfactory));
		if (FAILED(hr)) { /*logging*/ return E_FAIL; }
		hr = AddAdapter(pfactory, adap);
		if (FAILED(hr)) { /*logging*/ return E_FAIL; }
	#elif defined(DX12_x)
		IDXGIFactory7* pfactory = nullptr;
		IDXGIAdapter4* adap = nullptr;
		hr = CreateDXGIFactory2(flags, __uuidof(IDXGIFactory7), (void**)(&pfactory));
		if (FAILED(hr)) { /*logging*/ return hr; }
		hr = AddAdapter(pfactory, adap);
		if (FAILED(hr)) { /*logging*/ return hr; }
	#endif // DX11, 12 or 12_x?

	/*/

	/**/
	
	return S_OK;

}
