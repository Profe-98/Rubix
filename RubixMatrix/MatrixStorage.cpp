#include "MatrixStorage.h"
namespace Rubix 
{

	//Default c'tor
	MatrixStorage::MatrixStorage()
	{

	}

	MatrixStorage::MatrixStorage(std::vector<double> buffer, std::pair<uint64_t, uint64_t> strides, uint64_t size_logic, uint64_t rows, uint64_t cols, uint64_t offset, bool _resizable, bool _mutable) : _buffer(buffer), _strides(strides), _size_logic(size_logic), _rows(rows), _cols(cols), _offset(offset), _resizable(_resizable), _mutable(_mutable)
	{
		this->_size_phys = this->_buffer.size();
	}

	MatrixStorage::MatrixStorage(double val, std::pair<uint64_t, uint64_t> strides, uint64_t size_logic, uint64_t rows, uint64_t cols, uint64_t offset, bool _resizable, bool _mutable) : _strides(strides), _size_logic(size_logic), _rows(rows), _cols(cols), _offset(offset), _resizable(_resizable), _mutable(_mutable)
	{
		this->_buffer = std::vector<double>(1, val);
		this->_size_phys = this->_buffer.size();
	}

	std::vector<double> MatrixStorage::GetBuffer() const
	{
		return this->_buffer;
	}

	std::pair<uint64_t, uint64_t> MatrixStorage::GetStrides() const
	{
		return this->_strides;
	}

	uint64_t MatrixStorage::GetSize_logic() const
	{
		return this->_size_logic;
	}

	uint64_t MatrixStorage::GetSize_phys() const
	{
		return this->_size_phys;
	}

	uint64_t MatrixStorage::GetSize_phys_b() const
	{
		return sizeof(double) * this->_size_phys;
	}

	uint64_t MatrixStorage::GetOffset() const
	{
		return this->_offset;
	}

	void MatrixStorage::GetDevice() const
	{

	}

	uint64_t MatrixStorage::GetRows() const
	{
		return this->_rows;
	}

	uint64_t MatrixStorage::GetCols() const
	{
		return this->_cols;
	}

	bool MatrixStorage::Is_shared() const
	{
		return false;
	}

	bool MatrixStorage::Is_mutable() const
	{
		return _mutable;
	}

	bool MatrixStorage::Is_resizable() const
	{
		return _resizable;
	}

	void MatrixStorage::fill()
	{

	}

	void MatrixStorage::resize()
	{

	}

	MatrixStorage MatrixStorage::Add_Scalar(double scalar)
	{
		throw NotImplementedException("The method isn't implented yet!");
		return MatrixStorage();
	}

	MatrixStorage MatrixStorage::Add_Matrix(MatrixStorage other)
	{
		throw NotImplementedException("The method isn't implented yet!");
		return MatrixStorage();
	}

	MatrixStorage MatrixStorage::Add_Eq_Scalar(double scalar)
	{
		throw NotImplementedException("The method isn't implented yet!");
		return MatrixStorage();
	}

	MatrixStorage MatrixStorage::Add_Eq_Matrix(MatrixStorage other)
	{
		throw NotImplementedException("The method isn't implented yet!");
		return MatrixStorage();
	}

	MatrixStorage MatrixStorage::Subtr_Scalar(double scalar)
	{
		throw NotImplementedException("The method isn't implented yet!");
		return MatrixStorage();
	}

	MatrixStorage MatrixStorage::Subtr_Matrix(MatrixStorage other)
	{
		throw NotImplementedException("The method isn't implented yet!");
		return MatrixStorage();
	}

	MatrixStorage MatrixStorage::Subtr_Eq_Scalar(double scalar)
	{
		throw NotImplementedException("The method isn't implented yet!");
		return MatrixStorage();
	}

	MatrixStorage MatrixStorage::Subtr_Eq_Matrix(MatrixStorage other)
	{
		throw NotImplementedException("The method isn't implented yet!");
		return MatrixStorage();
	}

	MatrixStorage MatrixStorage::Mult_Scalar(double scalar)
	{
		throw NotImplementedException("The method isn't implented yet!");
		return MatrixStorage();
	}

	MatrixStorage MatrixStorage::Mult_Matrix(MatrixStorage other)
	{
		throw NotImplementedException("The method isn't implented yet!");
		return MatrixStorage();
	}

	MatrixStorage MatrixStorage::Mult_Eq_Scalar(double scalar)
	{
		throw NotImplementedException("The method isn't implented yet!");
		return MatrixStorage();
	}

	MatrixStorage MatrixStorage::Mult_Eq_Matrix(MatrixStorage other)
	{
		throw NotImplementedException("The method isn't implented yet!");
		return MatrixStorage();
	}

	MatrixStorage MatrixStorage::Div_Scalar(double scalar)
	{
		throw NotImplementedException("The method isn't implented yet!");
		return MatrixStorage();
	}

	MatrixStorage MatrixStorage::Div_Matrix(MatrixStorage other)
	{
		throw NotImplementedException("The method isn't implented yet!");
		return MatrixStorage();
	}

	MatrixStorage MatrixStorage::Div_Eq_Scalar(double scalar)
	{
		throw NotImplementedException("The method isn't implented yet!");
		return MatrixStorage();
	}

	MatrixStorage MatrixStorage::Div_Eq_Matrix(MatrixStorage other)
	{
		throw NotImplementedException("The method isn't implented yet!");
		return MatrixStorage();
	}

	std::ostream& operator<<(std::ostream& op, MatrixStorage& strg)
	{
		return op;
	}

}
