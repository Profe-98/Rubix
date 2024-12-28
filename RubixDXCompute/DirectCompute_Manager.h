#pragma once

#define _WIN32_WINNT 0x600

#include <d3d11.h>
#include <d3d12.h>
#include <d3dcompiler.h>
#include <libloaderapi.h>
#include <iostream>
#include <stdint.h>
#include <winerror.h>
#include <string>
#include <ctime>
#include <regex>
#include <cmath>
#include <fstream>
#include <vector>
#include <utility>
#include <typeinfo>
#include <sstream>
#include <random>
#include <thread>
#include <memory>
#include <initializer_list>
#include <map>
#include <filesystem>


// Link necessary D3D libraries
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")

namespace fs = std::filesystem;

namespace Rubix
{

	class DirectCompute_Manager
	{
		private:
			inline static std::map<std::string, std::string> _sources_rbxShader;
			inline static std::map<std::string, std::string> _sources_rbxAnalytics;
			inline static std::map<std::string, std::string> _sources_rbxInterim;
			inline static std::map<std::string, std::string> _sources_CustomShader;
			inline static std::map<std::string, std::pair<ID3D11Device*, ID3D11DeviceContext*>> _devices_dx11;
			inline static std::map<std::string, D3D_FEATURE_LEVEL> _devices_dx11_feature_lvls;
			inline static std::map<std::string, ID3D12Device*> _devices_dx12; // TODO: implement this properly...

		public:

			enum SHADER_SOURCE_TYPE : int
			{
				RUBIX_SHADER = 0,
				RUBIX_ANALYTICS = 1,
				RUBIX_INTERIM = 2,
				CUSTOM = 3
			};

			static HRESULT LoadSources(std::vector<fs::path> paths, std::vector<std::string> names, SHADER_SOURCE_TYPE srctype = SHADER_SOURCE_TYPE::RUBIX_SHADER);
			static HRESULT AddD3D11Device(std::string devicvename, IDXGIAdapter* adapter, D3D_DRIVER_TYPE drivertype, HMODULE software, UINT flags, UINT sdkversion);

			static std::pair<ID3D11Device*, ID3D11DeviceContext*> Get_Device_And_Context(std::string name);

			static std::string Get_Source_Rbx_Shader(std::string name);
			static std::string Get_Source_Rbx_Analytics(std::string name);
			static std::string Get_Source_Rbx_Interim(std::string name);
			static std::string Get_Source_Custom_Shader(std::string name);

			static std::string ChangeNumThreads(std::string shadername, int dim_x, int dim_y, int dim_z, SHADER_SOURCE_TYPE shadertype = SHADER_SOURCE_TYPE::RUBIX_SHADER);
	};
}