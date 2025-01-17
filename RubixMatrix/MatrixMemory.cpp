#include "MatrixMemory.h"
namespace Rubix 
{

#pragma region HELPER_METHODS

	HRESULT MatrixMemory::Handle_Fail(std::string logmsg)
	{
		//TODO
		/*logging*/
		return E_FAIL;
	}

	#ifdef DX12

	HRESULT MatrixMemory::CheckAdapterDX12support(std::set<IDXGIAdapter*> adapters, D3D_FEATURE_LEVEL lvl)
	{
		for (IDXGIAdapter* adap : adapters)
		{
			if (FAILED(D3D12CreateDevice(adap, lvl, __uuidof(ID3D12Device), nullptr)))
				adapters.erase(adap);
		}
		return adapters.size() > 0 ? S_OK : E_FAIL;
	}

	HRESULT MatrixMemory::CreateDX12Devices(std::set<IDXGIAdapter*> adapters, D3D_FEATURE_LEVEL minimumfeaturelevel)
	{
		if (adapters.size() == 0)
			return E_FAIL;
		HRESULT hr = 0;
		ID3D12Device* device = nullptr;
		int id = 0;
		for (IDXGIAdapter* adap : adapters)
		{
			hr = D3D12CreateDevice(adap, minimumfeaturelevel, IID_PPV_ARGS(&device));
			if (SUCCEEDED(hr))
			{
				_dx12Devices[id] = device;
				++id;
				/*logging*/
			}
			else
			{
				/*logging*/
			}
		}
		return S_OK;
	}
	#endif // DX12

#pragma endregion


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

#pragma region DIRECTX(Machine learning) 

	HRESULT MatrixMemory::CreateDevice(std::set<IDXGIAdapter*> adapters, int id, D3D_FEATURE_LEVEL featurelevel, D3D_DRIVER_TYPE drivertype, HMODULE software, UINT flags, UINT sdkversion)
	{
		HRESULT hr = 0;
		//TODO: finish this
		#if defined DX12
			if (FAILED(CheckAdapterDX12support(adapters, featurelevel))) {/*logging*/ return E_FAIL; }
			if (FAILED(CreateDX12Devices(adapters, featurelevel))) { /*logging*/ return E_FAIL; }
			hr = _dx12Devices.size() == 0 ? E_FAIL : S_OK;
		#endif		
		#if defined DX11
			_dx11Device = DirectX::DXGIMngr::_dx11Devices[id];
			hr = _dx11Device.first != nullptr && _dx11Device.second != nullptr ? S_OK : E_FAIL;
		#endif
		return hr;
	}

	#ifdef  DX11

	HRESULT MatrixMemory::LoadComputeShaderDX11(int id, std::string mainfunctionname, UINT flags1, UINT flags2, UINT contextflags, std::string shadermodel)
	{

		HRESULT hr = 0;
		ID3DBlob* shaderblob;
		ID3DBlob* errorblob;
		ID3D11Device* device_ptr_cpy = _dx11Device.first;

		hr = D3DCompile(_active_compute_shader_src.c_str(), _active_compute_shader_src.size(), nullptr, nullptr, nullptr, mainfunctionname.c_str(), shadermodel.c_str(), 0, 0, &shaderblob, &errorblob);

		if (FAILED(hr))
		{
			/*TODO logging*/
			if (errorblob)
			{
				OutputDebugStringA((char*)errorblob->GetBufferPointer());
				errorblob->Release();
			}
			if (shaderblob)	shaderblob->Release();
			return E_FAIL;
		}

		hr = device_ptr_cpy->CreateComputeShader(shaderblob->GetBufferPointer(), shaderblob->GetBufferSize(), nullptr, &_dx11shader);
		if (FAILED(hr)) { /*TODO: logging*/ shaderblob->Release(); _dx11shader->Release(); }

		return _dx11shader != nullptr ? S_OK : E_FAIL;
	}


	HRESULT MatrixMemory::AddBuffer_Input(int id, std::vector<double> matrixmembuffer, D3D11_USAGE bufferusage, UINT bindflags, UINT miscflags)
	{

		D3D11_BUFFER_DESC bufferdescription = {};

		bufferdescription.Usage = bufferusage;
		bufferdescription.ByteWidth = sizeof(double) * _size_phys;
		bufferdescription.BindFlags = bindflags;
		bufferdescription.MiscFlags = miscflags;
		bufferdescription.StructureByteStride = sizeof(double);

		if (&bufferdescription == nullptr)
		{
			return Handle_Fail("");
		}

		D3D11_SUBRESOURCE_DATA initdata = {};

		initdata.pSysMem = _buffer.data();
		ID3D11Buffer* _dx11buffer = nullptr;
		if (FAILED(_dx11Device.first->CreateBuffer(&bufferdescription, &initdata, &_dx11buffer))) { /*logging*/ return Handle_Fail(""); }
		_dx11buffers_input.emplace_back(_dx11buffer);
		return S_OK;
	}

	/// <summary>
	/// Also Interesting for Rubix Interim and Rubix Analytics 
	/// </summary>
	/// <param name="id"></param>
	/// <param name="useRubixDescriptions"></param>
	/// <param name="bufferusage"></param>
	/// <param name="bindflags"></param>
	/// <param name="miscflags"></param>
	/// <returns></returns>
	HRESULT MatrixMemory::AddBuffer_Output(int id, D3D11_USAGE bufferusage, UINT bindflags, UINT miscflags)
	{
		D3D11_BUFFER_DESC bufferdescription = {};

		bufferdescription.Usage = bufferusage;
		bufferdescription.ByteWidth = sizeof(double) * _size_phys;
		bufferdescription.BindFlags = bindflags;
		bufferdescription.MiscFlags = miscflags;
		bufferdescription.StructureByteStride = sizeof(double);

		if (&bufferdescription == nullptr)
		{
			return Handle_Fail("");
		}

		ID3D11Buffer* _dx11buffer;
		if (FAILED(_dx11Device.first->CreateBuffer(&bufferdescription, nullptr, &_dx11buffer))) { /*logging*/ return Handle_Fail(""); }
		_dx11buffers_output.emplace_back(_dx11buffer);
		return S_OK;
	}


	HRESULT MatrixMemory::CreateUAVsDX11(int id, const D3D11_UNORDERED_ACCESS_VIEW_DESC* uavdesc)
	{
		if (uavdesc == nullptr) {/*logging*/ return E_FAIL; }

		ID3D11Device* device = _dx11Device.first;
		ID3D11DeviceContext* ctxt = _dx11Device.second;

		ID3D11UnorderedAccessView* _dx11uav = nullptr;

		for (auto& buffer : _dx11buffers_input)
		{
			HRESULT hr = _dx11Device.first->CreateUnorderedAccessView(buffer, uavdesc, &_dx11uav);
			if (FAILED(hr)) { ReleaseBuffersInput(); ReleaseBuffersOutput(); ReleaseBuffersStaging(); ReleaseUAVs();  /*logging*/ return E_FAIL; }
			_dx11_unordered_access_views.emplace_back(_dx11uav);
		}

		for (auto& buffer : _dx11buffers_output)
		{
			HRESULT hr = _dx11Device.first->CreateUnorderedAccessView(buffer, uavdesc, &_dx11uav);
			if (FAILED(hr)) { ReleaseBuffersInput(); ReleaseBuffersOutput(); ReleaseBuffersStaging(); ReleaseUAVs();  /*logging*/ return E_FAIL; }
			_dx11_unordered_access_views.emplace_back(_dx11uav);
		}

		_dx11Device.second->CSSetUnorderedAccessViews(0, _dx11_unordered_access_views.size(), _dx11_unordered_access_views.data(), nullptr); // Binds the UAVs to the compute shader
		return S_OK;
	}

	void MatrixMemory::Bind_UAVDX11(MatrixMemory& other, int startslot, int index)
	{
		ID3D11UnorderedAccessView* uav[] = { other.GetUAV(index) };
		_dx11Device.second->CSSetUnorderedAccessViews(startslot, 1, uav, nullptr);
	}

	void MatrixMemory::Unbind_UAVDX11(int startslot)
	{
		ID3D11UnorderedAccessView* nullp_uav[] = { nullptr };
		_dx11Device.second->CSSetUnorderedAccessViews(startslot, 1, nullp_uav, nullptr);
	}

	ID3D11UnorderedAccessView* MatrixMemory::GetUAV(int startslot)
	{
		ID3D11UnorderedAccessView* uav[1] = { nullptr };
		_dx11Device.second->CSGetUnorderedAccessViews(startslot, 1, uav);
		return uav[0];
	}

	//TODO: Not really finished. Only good for the beginning(regarding the threadgroupsizes)
	void MatrixMemory::DispatchComputeShader_DX11(int id, int threadgroupsizex, int threadgroupsizey, int threadgroupsizez)
	{
		_dx11Device.second->Dispatch(sizeof(_buffer) / threadgroupsizex, 1 / threadgroupsizey, 1 / threadgroupsizez);
	}

	HRESULT MatrixMemory::RetrieveOutputDataDX11(int id, std::vector<double> buffer_destination, int outputindexer)
	{
		if (_dx11Device.first == nullptr || _dx11Device.second == nullptr) {/*logging*/ return E_FAIL; }

		HRESULT hr = 0;

		D3D11_BUFFER_DESC stagingdesc = {};
		stagingdesc.Usage = D3D11_USAGE_STAGING;
		stagingdesc.ByteWidth = sizeof(double) * _buffer.size();
		stagingdesc.CPUAccessFlags = D3D11_CPU_ACCESS_READ;
		stagingdesc.BindFlags = 0;
		stagingdesc.MiscFlags = D3D11_RESOURCE_MISC_BUFFER_STRUCTURED;
		stagingdesc.StructureByteStride = sizeof(double);

		ID3D11Buffer* buffer_staging = nullptr;
		hr = _dx11Device.first->CreateBuffer(&stagingdesc, nullptr, &buffer_staging);
		if (FAILED(hr)) {/*logging*/ return E_FAIL; }

		_dx11Device.second->CopyResource(buffer_staging, _dx11buffers_output[outputindexer]);

		D3D11_MAPPED_SUBRESOURCE mappedressource;
		hr = _dx11Device.second->Map(buffer_staging, 0, D3D11_MAP_READ, 0, &mappedressource);
		if (FAILED(hr)) {/*logging*/ return E_FAIL; }

		memcpy(buffer_destination.data(), mappedressource.pData, sizeof(double) * _size_phys);
		_dx11Device.second->Unmap(buffer_staging, 0);
		buffer_staging->Release();
		return S_OK;
	}

	std::pair<ID3D11Device*, ID3D11DeviceContext*> MatrixMemory::GetDeviceAndContextDX11(int id)
	{
		return _dx11Device;
	}

	#endif //  DX11


	#if defined(DX12) || defined(DX12_x)

	#endif

	void MatrixMemory::SetActiveComputeShaderSrc(std::string name, DirectCompute_Manager::SHADER_SOURCE_TYPE type)
	{
		switch (type)
		{
			case Rubix::DirectCompute_Manager::RUBIX_SHADER:
				_active_compute_shader_src = DirectCompute_Manager::Get_Source_Rbx_Shader(name);
				break;
			case Rubix::DirectCompute_Manager::RUBIX_ANALYTICS:
				_active_compute_shader_src = DirectCompute_Manager::Get_Source_Rbx_Analytics(name);
				break;
			case Rubix::DirectCompute_Manager::RUBIX_INTERIM:
				_active_compute_shader_src = DirectCompute_Manager::Get_Source_Rbx_Interim(name);
				break;
			case Rubix::DirectCompute_Manager::CUSTOM:
				_active_compute_shader_src = DirectCompute_Manager::Get_Source_Custom_Shader(name);
				break;
		}
	}

	std::string MatrixMemory::GetActiveComputeShaderSrc()
	{
		return _active_compute_shader_src;
	}

#pragma endregion

#pragma region Misc

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

#pragma endregion

#pragma region Single Matrix Operations


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

#pragma endregion

	std::ostream& operator<<(std::ostream& op, MatrixMemory& strg)
	{
		return op;
	}

}
