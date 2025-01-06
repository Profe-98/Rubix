#include "MatrixMemory.h"
namespace Rubix 
{

#pragma region Ctors and RULE OF 5

	//Default c'tor
	MatrixMemory::MatrixMemory()
	{

	}

	MatrixMemory::MatrixMemory(std::vector<double> buffer, std::pair<uint64_t, uint64_t> strides, uint64_t size_logic, uint64_t rows, uint64_t cols, uint64_t offset, bool _resizable, bool _mutable) : _buffer(buffer), _strides(strides), _size_logic(size_logic), _rows(rows), _cols(cols), _offset(offset), _resizable(_resizable), _mutable(_mutable)
	{
		this->_size_phys = this->_buffer.size();
	}

	MatrixMemory::MatrixMemory(double val, std::pair<uint64_t, uint64_t> strides, uint64_t size_logic, uint64_t rows, uint64_t cols, uint64_t offset, bool _resizable, bool _mutable) : _strides(strides), _size_logic(size_logic), _rows(rows), _cols(cols), _offset(offset), _resizable(_resizable), _mutable(_mutable)
	{
		this->_buffer = std::vector<double>(1, val);
		this->_size_phys = this->_buffer.size();
	}

	MatrixMemory::~MatrixMemory() noexcept
	{
	}

	MatrixMemory::MatrixMemory(const MatrixMemory& memory) :  _mutable(memory._mutable), _resizable(memory._resizable), _buffer(memory._buffer), _strides(memory._strides), _size_phys(memory._size_phys), _size_logic(memory._size_logic), _offset(memory._offset), _rows(memory._rows), _cols(memory._cols) //copy c'tor
	{
	}

	MatrixMemory& MatrixMemory::operator= (const MatrixMemory& memory) //copy assignment
	{
		if (this != &memory)
		{
			_mutable = memory._mutable;
			_resizable = memory._resizable;
			_buffer = memory._buffer;
			_strides = memory._strides;
			_size_phys = memory._size_phys;
			_size_logic = memory._size_logic;
			_offset = memory._offset;
			_rows = memory._rows;
			_cols = memory._cols;
		}
		return *this;
	}

	MatrixMemory::MatrixMemory(MatrixMemory&& memory) noexcept : _mutable(memory._mutable), _resizable(memory._resizable), _buffer(memory._buffer), _strides(memory._strides), _size_phys(memory._size_phys), _size_logic(memory._size_logic), _offset(memory._offset), _rows(memory._rows), _cols(memory._cols) //move c'tor 	
	{

	}

	MatrixMemory& MatrixMemory::operator=(MatrixMemory&& memory) noexcept //move assignment
	{
		if (this != &memory)
		{
			_mutable = memory._mutable;
			_resizable = memory._resizable;
			_buffer = memory._buffer;
			_strides = memory._strides;
			_size_phys = memory._size_phys;
			_size_logic = memory._size_logic;
			_offset = memory._offset;
			_rows = memory._rows;
			_cols = memory._cols;
		}

		return *this;
	}

#pragma endregion

	HRESULT MatrixMemory::CreateDevice(std::set<IDXGIAdapter*> adapters, D3D_FEATURE_LEVEL featurelevel, D3D_DRIVER_TYPE drivertype, HMODULE software, UINT flags, UINT sdkversion)
	{
		HRESULT hr = 0;

		#if defined DX12 || defined DX12_x
		ID3D12Device* device = nullptr;
			//if(SUCCEEDED()) { } TODO: continue with check of adapter being able to use DX12 	
			//hr = D3D12CreateDevice(, featurelevel, IID_PPV_ARGS(&device));
			if (FAILED(hr)) { /*logging*/ return hr; }
			_dx12Devices.insert(device);
		#elif defined(DX11)
			ID3D11Device* device = nullptr;
			ID3D11DeviceContext* context = nullptr;
			hr = D3D11CreateDevice(adapter, drivertype, software, flags, nullptr, 0, sdkversion, &device, &featurelevel, &context);
			if (FAILED(hr)) { /*logging*/ return hr; }
			_dx11Devices.insert(device);
		#endif
		return S_OK;
	}

	void MatrixMemory::SetActiveComputeShader(std::string name, DirectCompute_Manager::SHADER_SOURCE_TYPE type)
	{
		switch (type)
		{
			case Rubix::DirectCompute_Manager::RUBIX_SHADER:
				_active_compute_shader = DirectCompute_Manager::Get_Source_Rbx_Shader(name);
				break;
			case Rubix::DirectCompute_Manager::RUBIX_ANALYTICS:
				_active_compute_shader = DirectCompute_Manager::Get_Source_Rbx_Analytics(name);
				break;
			case Rubix::DirectCompute_Manager::RUBIX_INTERIM:
				_active_compute_shader = DirectCompute_Manager::Get_Source_Rbx_Interim(name);
				break;
			case Rubix::DirectCompute_Manager::CUSTOM:
				_active_compute_shader = DirectCompute_Manager::Get_Source_Custom_Shader(name);
				break;
		}
	}

	std::string MatrixMemory::GetActiveComputeShader()
	{
		return _active_compute_shader;
	}

	std::vector<double> MatrixMemory::GetBuffer() const
	{
		return this->_buffer;
	}

	std::pair<uint64_t, uint64_t> MatrixMemory::GetStrides() const
	{
		return this->_strides;
	}

	uint64_t MatrixMemory::GetSize_logic() const
	{
		return this->_size_logic;
	}

	uint64_t MatrixMemory::GetSize_phys() const
	{
		return this->_size_phys;
	}

	uint64_t MatrixMemory::GetSize_phys_b() const
	{
		return sizeof(double) * this->_size_phys;
	}

	uint64_t MatrixMemory::GetOffset() const
	{
		return this->_offset;
	}


	uint64_t MatrixMemory::GetRows() const
	{
		return this->_rows;
	}

	uint64_t MatrixMemory::GetCols() const
	{
		return this->_cols;
	}

	bool MatrixMemory::Is_shared() const
	{
		return false;
	}

	bool MatrixMemory::Is_mutable() const
	{
		return _mutable;
	}

	bool MatrixMemory::Is_resizable() const
	{
		return _resizable;
	}

	void MatrixMemory::resize()
	{

	}

	void MatrixMemory::fill()
	{

	}

	#if defined(DX12) || defined(DX12_x)
	
	#endif


	MatrixMemory MatrixMemory::Add_Scalar(double scalar)
	{
		return MatrixMemory();
	}

	MatrixMemory MatrixMemory::Add_Matrix(MatrixMemory other)
	{
		return MatrixMemory();
	}

	MatrixMemory MatrixMemory::Add_Eq_Scalar(double scalar)
	{
		return MatrixMemory();
	}

	MatrixMemory MatrixMemory::Add_Eq_Matrix(MatrixMemory other)
	{
		return MatrixMemory();
	}

	MatrixMemory MatrixMemory::Subtr_Scalar(double scalar)
	{
		return MatrixMemory();
	}

	MatrixMemory MatrixMemory::Subtr_Matrix(MatrixMemory other)
	{
		return MatrixMemory();
	}

	MatrixMemory MatrixMemory::Subtr_Eq_Scalar(double scalar)
	{
		return MatrixMemory();
	}

	MatrixMemory MatrixMemory::Subtr_Eq_Matrix(MatrixMemory other)
	{
		return MatrixMemory();
	}

	MatrixMemory MatrixMemory::Mult_Scalar(double scalar)
	{
		return MatrixMemory();
	}

	MatrixMemory MatrixMemory::Mult_Matrix(MatrixMemory other)
	{
		return MatrixMemory();
	}

	MatrixMemory MatrixMemory::Mult_Eq_Scalar(double scalar)
	{
		return MatrixMemory();
	}

	MatrixMemory MatrixMemory::Mult_Eq_Matrix(MatrixMemory other)
	{
		return MatrixMemory();
	}

	MatrixMemory MatrixMemory::Div_Scalar(double scalar)
	{
		return MatrixMemory();
	}

	MatrixMemory MatrixMemory::Div_Matrix(MatrixMemory other)
	{
		return MatrixMemory();
	}

	MatrixMemory MatrixMemory::Div_Eq_Scalar(double scalar)
	{
		return MatrixMemory();
	}

	MatrixMemory MatrixMemory::Div_Eq_Matrix(MatrixMemory other)
	{
		return MatrixMemory();
	}

	std::ostream& operator<<(std::ostream& op, MatrixMemory& strg)
	{
		return op;
	}

}
