#include "MatrixStorage.h"
namespace Rubix 
{

	//Default c'tor
	MatrixStorage::MatrixStorage()
	{

	}

	MatrixStorage::MatrixStorage(std::vector<double> buffer, std::pair<uint64_t, uint64_t> strides, uint64_t size_logic, uint64_t rows, uint64_t cols, uint64_t offset) : _buffer(buffer), _strides(strides), _size_logic(size_logic), _rows(rows), _cols(cols), _offset(offset)
	{
		this->_size_phys = this->_buffer.size();
	}

	MatrixStorage::MatrixStorage(double val, std::pair<uint64_t, uint64_t> strides, uint64_t size_logic, uint64_t rows, uint64_t cols, uint64_t offset) : _strides(strides), _size_logic(size_logic), _rows(rows), _cols(cols), _offset(offset)
	{
		this->_buffer = std::vector<double>(1, val);
		this->_size_phys = this->_buffer.size();
	}

	std::vector<double> MatrixStorage::GetBuffer()
	{
		return this->_buffer;
	}

	std::pair<uint64_t, uint64_t> MatrixStorage::GetStrides()
	{
		return this->_strides;
	}

	uint64_t MatrixStorage::GetSize_logic()
	{
		return this->_size_logic;
	}

	uint64_t MatrixStorage::GetSize_phys()
	{
		return this->_size_phys;
	}

	uint64_t MatrixStorage::GetSize_phys_b()
	{
		return sizeof(double) * this->_size_phys;
	}

	uint64_t MatrixStorage::GetOffset()
	{
		return this->_offset;
	}

	void MatrixStorage::GetDevice()
	{

	}

	uint64_t MatrixStorage::GetRows()
	{
		return this->_rows;
	}

	uint64_t MatrixStorage::GetCols()
	{
		return this->_cols;
	}

	bool MatrixStorage::Is_shared()
	{
		return false;
	}

	bool MatrixStorage::Is_mutable()
	{
		return false;
	}

	void MatrixStorage::fill()
	{

	}

	uint64_t MatrixStorage::get_device()
	{
		return 0;
	}

	bool MatrixStorage::resizable()
	{
		return false;
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
		// TODO: hier return-Anweisung eingeben
		throw NotImplementedException("The method isn't implented yet!");
		return op;
	}

}
