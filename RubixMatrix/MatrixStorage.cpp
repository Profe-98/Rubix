#include "MatrixStorage.h"
namespace Rubix 
{

	//Default c'tor
	MatrixStorage::MatrixStorage()
	{

	}

	MatrixStorage::MatrixStorage(std::vector<double> buffer, std::vector<int> strides, int size_logic, int rows, int cols, int offset) : _buffer(buffer), _strides(strides), _size_logic(size_logic), _rows(rows), _cols(cols), _offset(offset)
	{
		this->_size_phys = this->_buffer.size();
	}

	MatrixStorage::MatrixStorage(double val, std::vector<int> strides, int size_logic, int rows, int cols, int offset) : _strides(strides), _size_logic(size_logic), _rows(rows), _cols(cols), _offset(offset)
	{
		this->_buffer = std::vector<double>(1, val);
		this->_size_phys = this->_buffer.size();
	}

	std::vector<double> MatrixStorage::GetBuffer()
	{
		return this->_buffer;
	}

	std::vector<int> MatrixStorage::GetStrides()
	{
		return this->_strides;
	}

	int MatrixStorage::GetSize_logic()
	{
		return this->_size_logic;
	}

	int MatrixStorage::GetSize_phys()
	{
		return this->_size_phys;
	}

	int MatrixStorage::GetSize_phys_b()
	{
		return sizeof(double) * this->_size_phys;
	}

	int MatrixStorage::GetOffset()
	{
		return this->_offset;
	}

	void MatrixStorage::GetDevice()
	{

	}

	int MatrixStorage::GetRows()
	{
		return this->_rows;
	}

	int MatrixStorage::GetCols()
	{
		return this->_cols;
	}

	void MatrixStorage::copy()
	{

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

	int MatrixStorage::get_device()
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

	MatrixStorage MatrixStorage::Add_Scalar(double scalar, std::unique_ptr<ComputeObject> openclcomputeobject)
	{
		throw NotImplementedException("The method isn't implented yet!");
		return MatrixStorage();
	}

	MatrixStorage MatrixStorage::Add_Matrix(MatrixStorage other, std::unique_ptr<ComputeObject> openclcomputeobject)
	{
		throw NotImplementedException("The method isn't implented yet!");
		return MatrixStorage();
	}

	MatrixStorage MatrixStorage::Add_Eq_Scalar(double scalar, std::unique_ptr<ComputeObject> openclcomputeobject)
	{
		throw NotImplementedException("The method isn't implented yet!");
		return MatrixStorage();
	}

	MatrixStorage MatrixStorage::Add_Eq_Matrix(MatrixStorage other, std::unique_ptr<ComputeObject> openclcomputeobject)
	{
		throw NotImplementedException("The method isn't implented yet!");
		return MatrixStorage();
	}

	MatrixStorage MatrixStorage::Subtr_Scalar(double scalar, std::unique_ptr<ComputeObject> openclcomputeobject)
	{
		throw NotImplementedException("The method isn't implented yet!");
		return MatrixStorage();
	}

	MatrixStorage MatrixStorage::Subtr_Matrix(MatrixStorage other, std::unique_ptr<ComputeObject> openclcomputeobject)
	{
		throw NotImplementedException("The method isn't implented yet!");
		return MatrixStorage();
	}

	MatrixStorage MatrixStorage::Subtr_Eq_Scalar(double scalar, std::unique_ptr<ComputeObject> openclcomputeobject)
	{
		throw NotImplementedException("The method isn't implented yet!");
		return MatrixStorage();
	}

	MatrixStorage MatrixStorage::Subtr_Eq_Matrix(MatrixStorage other, std::unique_ptr<ComputeObject> openclcomputeobject)
	{
		throw NotImplementedException("The method isn't implented yet!");
		return MatrixStorage();
	}

	MatrixStorage MatrixStorage::Mult_Scalar(double scalar, std::unique_ptr<ComputeObject> openclcomputeobject)
	{
		throw NotImplementedException("The method isn't implented yet!");
		return MatrixStorage();
	}

	MatrixStorage MatrixStorage::Mult_Matrix(MatrixStorage other, std::unique_ptr<ComputeObject> openclcomputeobject)
	{
		throw NotImplementedException("The method isn't implented yet!");
		return MatrixStorage();
	}

	MatrixStorage MatrixStorage::Mult_Eq_Scalar(double scalar, std::unique_ptr<ComputeObject> openclcomputeobject)
	{
		throw NotImplementedException("The method isn't implented yet!");
		return MatrixStorage();
	}

	MatrixStorage MatrixStorage::Mult_Eq_Matrix(MatrixStorage other, std::unique_ptr<ComputeObject> openclcomputeobject)
	{
		throw NotImplementedException("The method isn't implented yet!");
		return MatrixStorage();
	}

	MatrixStorage MatrixStorage::Div_Scalar(double scalar, std::unique_ptr<ComputeObject> openclcomputeobject)
	{
		throw NotImplementedException("The method isn't implented yet!");
		return MatrixStorage();
	}

	MatrixStorage MatrixStorage::Div_Matrix(MatrixStorage other, std::unique_ptr<ComputeObject> openclcomputeobject)
	{
		throw NotImplementedException("The method isn't implented yet!");
		return MatrixStorage();
	}

	MatrixStorage MatrixStorage::Div_Eq_Scalar(double scalar, std::unique_ptr<ComputeObject> openclcomputeobject)
	{
		throw NotImplementedException("The method isn't implented yet!");
		return MatrixStorage();
	}

	MatrixStorage MatrixStorage::Div_Eq_Matrix(MatrixStorage other, std::unique_ptr<ComputeObject> openclcomputeobject)
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
