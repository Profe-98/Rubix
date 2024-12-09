#include "MatrixMemory.h"
namespace Rubix 
{

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

	MatrixMemory::MatrixMemory(const MatrixMemory& storage) :  _mutable(storage._mutable), _resizable(storage._resizable), _buffer(storage._buffer), _strides(storage._strides), _size_phys(storage._size_phys), _size_logic(storage._size_logic), _offset(storage._offset), _rows(storage._rows), _cols(storage._cols) //copy c'tor
	{
	}

	MatrixMemory& MatrixMemory::operator= (const MatrixMemory& storage) //copy assignment
	{
		if (this != &storage)
		{
			_mutable = storage._mutable;
			_resizable = storage._resizable;
			_buffer = storage._buffer;
			_strides = storage._strides;
			_size_phys = storage._size_phys;
			_size_logic = storage._size_logic;
			_offset = storage._offset;
			_rows = storage._rows;
			_cols = storage._cols;
		}
		return *this;
	}

	MatrixMemory::MatrixMemory(MatrixMemory&& storage) noexcept : _mutable(storage._mutable), _resizable(storage._resizable), _buffer(storage._buffer), _strides(storage._strides), _size_phys(storage._size_phys), _size_logic(storage._size_logic), _offset(storage._offset), _rows(storage._rows), _cols(storage._cols) //move c'tor 	
	{

	}

	MatrixMemory& MatrixMemory::operator=(MatrixMemory&& storage) noexcept //move assignment
	{
		if (this != &storage)
		{
			_mutable = storage._mutable;
			_resizable = storage._resizable;
			_buffer = storage._buffer;
			_strides = storage._strides;
			_size_phys = storage._size_phys;
			_size_logic = storage._size_logic;
			_offset = storage._offset;
			_rows = storage._rows;
			_cols = storage._cols;
		}

		return *this;
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

	void MatrixMemory::GetDevice() const
	{

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

	void MatrixMemory::fill()
	{

	}

	void MatrixMemory::resize()
	{

	}

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
