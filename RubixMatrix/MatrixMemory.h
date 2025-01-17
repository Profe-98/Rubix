#pragma once
#include "../RubixDXGIManger/DXGIMngr.h"
#include "../RubixLogSys/Exceptions.h"
#include "../RubixDXCompute/DirectCompute_Manager.h"

#ifndef _WIN32_WINNT
	#define _WIN32_WINNT 0x600
#endif // !_WIN32_WINNT


#ifdef DX11
	#include <d3d11.h>
#elif defined DX12
	#include <d3d12.h>
#endif // DX11

#include <d3dcompiler.h>
#include <libloaderapi.h>
#include <vector>
#include <memory>
#include <cmath>
#include <iostream>
#include <string>
#include <utility>


namespace Rubix
{
	struct MatrixMemory
	{

	private:

		//TODO: CheckFeatureSupport()

	    //const uint64_t MAX_VALUE_ROWS_AND_COLS = UINT64_MAX;

		#pragma region Fields/Properties

		bool _mutable = true;
		bool _resizable = false;
		int layer = 0;
		std::string _active_compute_shader_src = "";
		std::vector<double> _buffer = {};
		std::pair<uint64_t, uint64_t> _strides{};

		#if defined DX12
			std::map<int, ID3D12Device*> _dx12Devices = {};
		#elif defined DX11
			std::pair<ID3D11Device*, ID3D11DeviceContext*> _dx11Device = {nullptr, nullptr};
			ID3D11ComputeShader* _dx11shader = nullptr;
			std::vector<ID3D11Buffer*> _dx11buffers_input;
			std::vector<ID3D11Buffer*> _dx11buffers_output;
			std::vector<ID3D11Buffer*> _dx11buffers_staging;
			std::vector<ID3D11UnorderedAccessView*> _dx11_unordered_access_views = {};
		#endif

		uint64_t _size_phys = 0; // represents the physical size of the matrix.
		uint64_t _size_logic = 0;
		uint64_t _offset = 0; // Position of the matrix's first element in the buffer. default is always 0
		uint64_t _rows = 0;
		uint64_t _cols = 0;
		//uint64_t _major_Dim = 0; //default 0 = width dimension (row major order); That means one step is needed to get to the next element in that dimension

		#pragma endregion

		#pragma region HELPER_METHODS
		
		HRESULT Handle_Fail(std::string logmsg);

		#ifdef DX12

		HRESULT CheckAdapterDX12support(std::set<IDXGIAdapter*> adapters, D3D_FEATURE_LEVEL lvl = D3D_FEATURE_LEVEL_11_0);
		HRESULT CreateDX12Devices(std::set<IDXGIAdapter*> adapters, D3D_FEATURE_LEVEL minimumfeaturelevel);
		
		#endif

		#pragma endregion

		public:

		#pragma region C tors and rule of 5

		//Default c'tor
		MatrixMemory();

		MatrixMemory(std::vector<double> buffer, std::pair<uint64_t, uint64_t> strides, uint64_t size_logic, uint64_t rows, uint64_t cols, uint64_t offset = 0, bool _resizable = false, bool _mutable = true);
		MatrixMemory(double val, std::pair<uint64_t, uint64_t> strides, uint64_t size_logic, uint64_t rows, uint64_t cols, uint64_t offset = 0, bool _resizable = false, bool _mutable = true);

		~MatrixMemory() noexcept;
		MatrixMemory(const MatrixMemory& memory);
		MatrixMemory& operator =(const MatrixMemory& memory);
		MatrixMemory(MatrixMemory&& memory) noexcept;
		MatrixMemory& operator =(MatrixMemory&& memory) noexcept;

		#pragma endregion


		#pragma region DIRECTX(Machine learning) 

		HRESULT CreateDevice(std::set<IDXGIAdapter*> adapters, int id = 0, D3D_FEATURE_LEVEL featurelevel, D3D_DRIVER_TYPE drivertype = D3D_DRIVER_TYPE::D3D_DRIVER_TYPE_HARDWARE, HMODULE software = 0, UINT flags = D3D11_CREATE_DEVICE_DEBUG, UINT sdkversion = D3D11_SDK_VERSION);

		#if defined DX11

		HRESULT LoadComputeShaderDX11(int id, std::string mainfunctionname = "main", UINT flags1 = D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION, UINT flags2 = 0, UINT contextflags = 0, std::string shadermodel = "5_0");

		HRESULT AddBuffer_Input(int id, std::vector<double> matrixmembuffer = {}, D3D11_USAGE bufferusage = D3D11_USAGE::D3D11_USAGE_DEFAULT, UINT bindflags = 8 | 128, UINT miscflags = 64);

		HRESULT AddBuffer_Output(int id, D3D11_USAGE bufferusage = D3D11_USAGE::D3D11_USAGE_DEFAULT, UINT bindflags = 8 | 128, UINT miscflags = 64);

		HRESULT CreateUAVsDX11(int id, const D3D11_UNORDERED_ACCESS_VIEW_DESC* uavdescription);

		void Bind_UAVDX11(MatrixMemory& other, int startslot, int index);

		void Unbind_UAVDX11(int startslot);

		ID3D11UnorderedAccessView* GetUAV(int startslot);
		
		void DispatchComputeShader_DX11(int id, int threadgroupsizex = 1, int threadgroupsizey = 1, int threadgroupsizez = 1);

		HRESULT RetrieveOutputDataDX11(int id, std::vector<double> buffer_destination, int outputindexer);

		void ReleaseBuffersInput();
		void ReleaseBuffersOutput();
		void ReleaseBuffersStaging();
		void ReleaseUAVs();
		void ReleaseDevice();

		//TODO Check if multiple devices can be used for multiple matrices
		std::pair<ID3D11Device*, ID3D11DeviceContext*> GetDeviceAndContextDX11(int id); // for the case that 2+ matrices have to be stored on one gpu...  

		#endif

		void SetActiveComputeShaderSrc(std::string name, DirectCompute_Manager::SHADER_SOURCE_TYPE type = DirectCompute_Manager::SHADER_SOURCE_TYPE::RUBIX_SHADER);

		std::string GetActiveComputeShaderSrc();

		#pragma endregion


		#pragma region Misc

		std::vector<double> GetBuffer() const;

		std::pair<uint64_t, uint64_t> GetStrides() const;

		uint64_t GetSize_logic() const;

		uint64_t GetSize_phys() const;

		uint64_t GetSize_phys_b() const;

		uint64_t GetOffset() const;

		uint64_t GetRows() const;

		uint64_t GetCols() const;

		__declspec(deprecated("Not  implemented!"))
		bool Is_shared() const;

		bool Is_mutable() const;

		bool Is_resizable() const;

		__declspec(deprecated("Not  implemented!"))
		void resize();

		__declspec(deprecated("Not  implemented!"))
		void fill();

		#pragma endregion

		#pragma region Single Matrix Operations

		__declspec(deprecated("Not  implemented!"))
		MatrixMemory Add_Scalar(double scalar);
		__declspec(deprecated("Not  implemented!"))
		MatrixMemory Add_Matrix(MatrixMemory other);
		__declspec(deprecated("Not  implemented!"))
		MatrixMemory Add_Eq_Scalar(double scalar);
		__declspec(deprecated("Not  implemented!"))
		MatrixMemory Add_Eq_Matrix(MatrixMemory other);
		__declspec(deprecated("Not  implemented!"))
		MatrixMemory Subtr_Scalar(double scalar);
		__declspec(deprecated("Not  implemented!"))
		MatrixMemory Subtr_Matrix(MatrixMemory other);
		__declspec(deprecated("Not  implemented!"))
		MatrixMemory Subtr_Eq_Scalar(double scalar);
		__declspec(deprecated("Not  implemented!"))
		MatrixMemory Subtr_Eq_Matrix(MatrixMemory other);
		__declspec(deprecated("Not  implemented!"))
		MatrixMemory Mult_Scalar(double scalar);
		__declspec(deprecated("Not  implemented!"))
		MatrixMemory Mult_Matrix(MatrixMemory other);
		__declspec(deprecated("Not  implemented!"))
		MatrixMemory Mult_Eq_Scalar(double scalar);
		__declspec(deprecated("Not  implemented!"))
		MatrixMemory Mult_Eq_Matrix(MatrixMemory other);
		__declspec(deprecated("Not  implemented!"))
		MatrixMemory Div_Scalar(double scalar);
		__declspec(deprecated("Not  implemented!"))
		MatrixMemory Div_Matrix(MatrixMemory other);
		__declspec(deprecated("Not  implemented!"))
		MatrixMemory Div_Eq_Scalar(double scalar);
		__declspec(deprecated("Not  implemented!"))
		MatrixMemory Div_Eq_Matrix(MatrixMemory other);

		#pragma endregion

		friend std::ostream& operator<<(std::ostream& op, MatrixMemory& strg);
	};
}