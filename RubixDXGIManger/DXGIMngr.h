#pragma once

#define _WIN32_WINNT 0x600

#include "../../RubixCfg.h"
#include <map>
#ifdef DX11
#include <dxgi1_4.h>
#elif defined DX12
#include <dxgi1_5.h>
#include <dxgi1_6.h>
#endif

#include <dxgidebug.h> //TODO: play around with this(?)
#include <d3d11.h>
#include <d3d12.h>
#include <d3dcompiler.h>

#include <libloaderapi.h>

#include <winerror.h>
#include <set>
#include <iostream>
#include <cstdio>

#include "../RubixDefinitions.h"
#include "../RubixError.h"
#include "../RubixLogSys/LogHandler.h"

// Link necessary D3D libraries
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")

namespace Rubix::DirectX
{
	class DXGIMngr
	{
		public:

			static inline std::set<IDXGIAdapter*> _available_adapters = { nullptr };
			static inline std::map<int, std::pair<ID3D11Device*, ID3D11DeviceContext*>> _dx11Devices = {};
			static HRESULT AddAdapter(IDXGIFactory* pfactory, IDXGIAdapter* adap);

			static HRESULT ListAvailableAdapters(Rubix::Definitions::RBXDEF::DXGI_VERSION dxgi_ver, UINT flags = 0);

			static void ReleaseDX11Devices();

			static HRESULT CreateDX11Devices(D3D_FEATURE_LEVEL featurelevel, D3D_DRIVER_TYPE drivertype, HMODULE software, UINT flags, UINT sdkversion);

	};

}
