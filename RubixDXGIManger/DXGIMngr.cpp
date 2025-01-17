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
	#elif defined DX12
		IDXGIFactory5* pfactory = nullptr;
		IDXGIAdapter3* adap = nullptr;
		hr = CreateDXGIFactory2(flags, __uuidof(IDXGIFactory5), (void**)(&pfactory));
		if (FAILED(hr)) { /*logging*/ return E_FAIL; }
		hr = AddAdapter(pfactory, adap);
		if (FAILED(hr)) { /*logging*/ return E_FAIL; }
	#endif // DX11, 12 or 12_x?
	return S_OK;

}

void Rubix::DirectX::DXGIMngr::ReleaseDX11Devices()
{
	for (int i = 0; i < _dx11Devices.size(); ++i)
	{
		ID3D11Device* device = _dx11Devices[i].first;
		ID3D11DeviceContext* context = _dx11Devices[i].second;
		_dx11Devices.erase(i);
		device->Release();
		context->Release();
	}
}


HRESULT Rubix::DirectX::DXGIMngr::CreateDX11Devices(D3D_FEATURE_LEVEL featurelevel, D3D_DRIVER_TYPE drivertype, HMODULE software, UINT flags, UINT sdkversion)
{
	int id = 0;
	
	for (auto& adap : _available_adapters)
	{
		ID3D11Device* device = nullptr;
		ID3D11DeviceContext* context = nullptr;
		if (FAILED(D3D11CreateDevice(adap, drivertype, software, flags, nullptr, 0, sdkversion, &device, &featurelevel, &context))) {/*logging*/ ReleaseDX11Devices(); return E_FAIL; }
		_dx11Devices[id] = { device, context };
		++id;
	}

	return S_OK;
}
