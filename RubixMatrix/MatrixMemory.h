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
		bool _mutable = true;
		bool _resizable = false;
		std::string _active_compute_shader = "";
		std::vector<double> _buffer = {};
		std::pair<uint64_t, uint64_t> _strides{};

		#if defined DX12
			std::set<ID3D12Device*> _dx12Devices = {};
		#elif defined DX11
			std::set<ID3D11Device*> _dx11Devices = {};
		#endif

		uint64_t _size_phys = 0; // represents the physical size of the matrix.
		uint64_t _size_logic = 0;
		uint64_t _offset = 0; // Position of the matrix's first element in the buffer. default is always 0
		uint64_t _rows = 0;
		uint64_t _cols = 0;
		//uint64_t _major_Dim = 0; //default 0 = width dimension (row major order); That means one step is needed to get to the next element in that dimension

		public:

		//Default c'tor
		MatrixMemory();

		MatrixMemory(std::vector<double> buffer, std::pair<uint64_t, uint64_t> strides, uint64_t size_logic, uint64_t rows, uint64_t cols, uint64_t offset = 0, bool _resizable = false, bool _mutable = true);
		MatrixMemory(double val, std::pair<uint64_t, uint64_t> strides, uint64_t size_logic, uint64_t rows, uint64_t cols, uint64_t offset = 0, bool _resizable = false, bool _mutable = true);

		~MatrixMemory() noexcept;
		MatrixMemory(const MatrixMemory& memory);
		MatrixMemory& operator =(const MatrixMemory& memory);
		MatrixMemory(MatrixMemory&& memory) noexcept;
		MatrixMemory& operator =(MatrixMemory&& memory) noexcept;

		HRESULT CreateDevice(std::set<IDXGIAdapter*> adapters, D3D_FEATURE_LEVEL featurelevel, D3D_DRIVER_TYPE drivertype, HMODULE software, UINT flags, UINT sdkversion);

		void SetActiveComputeShader(std::string name, DirectCompute_Manager::SHADER_SOURCE_TYPE type = DirectCompute_Manager::SHADER_SOURCE_TYPE::RUBIX_SHADER);

		std::string GetActiveComputeShader();

		std::vector<double> GetBuffer() const;

		std::pair<uint64_t, uint64_t> GetStrides() const;

		uint64_t GetSize_logic() const;

		uint64_t GetSize_phys() const;

		uint64_t GetSize_phys_b() const;

		uint64_t GetOffset() const;

		__declspec(deprecated("Not  implemented!"))
		void GetDevice() const;

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

		#if defined DX12

		#endif

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

		friend std::ostream& operator<<(std::ostream& op, MatrixMemory& strg);
	};
}