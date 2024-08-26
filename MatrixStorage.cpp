#define __CL_ENABLE_EXCEPTIONS // must be defined before OpenCL header files are included
#include "MatrixStorage.h"
#include "CLManager.h"
#include "Compute_Object.h"
#include "Exceptions.h"
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
		if (this->_buffer.empty() || this->_buffer.size() == 0)
			throw std::invalid_argument("The given matrix is empty");
		if (scalar == 0.0)
			return MatrixStorage(this->_buffer, this->_strides, this->_size_logic, this->_rows, this->_cols, this->_offset);
		std::vector<double> res_buffer(this->_size_phys);


		openclcomputeobject->CreateBufferInput(this->_size_phys, this->_buffer.data());
		openclcomputeobject->CreateBufferOutput(res_buffer.size(), NULL);

		openclcomputeobject->SetKernelArgs();
		openclcomputeobject->SetKernelArg(2, scalar);
		openclcomputeobject->SetKernelArg(3, this->_size_phys);

		std::size_t global_work_size[1] = { (std::size_t)this->_size_phys };
		std::size_t local_work_size[1] = { (std::size_t)2 };

		openclcomputeobject->EnqueueNDRangeKernel(local_work_size, global_work_size, 1, NULL);
		openclcomputeobject->Finish();
		openclcomputeobject->EnqueueReadBuffer(1, CL_TRUE, 0, res_buffer.size(), res_buffer.data(), 0, NULL, NULL);
		openclcomputeobject->ReleaseBuffers();
		return MatrixStorage(res_buffer, this->_strides, this->_size_logic, this->_rows, this->_cols, this->_offset);

	}

	MatrixStorage MatrixStorage::Add_Matrix(MatrixStorage other, std::unique_ptr<ComputeObject> openclcomputeobject)
	{
		int other_size_logic = other.GetSize_logic();
		int other_size_phys = other.GetSize_phys();
		if (this->_buffer.empty() || other.GetBuffer().empty())
			throw std::invalid_argument("To be additive conformable, both matrices must contain elements!");
		if (this->_size_logic != other_size_logic)
			throw std::invalid_argument("To be additive conformable, both matrices must've the same size!");
		if (this->_rows != other.GetRows() || this->_cols != other.GetCols())
			throw std::invalid_argument("To be additive conformable, both matrices must've equal amound of rows and columns!");

		std::vector<double> res_buffer(this->_size_phys);
		//(this->_size_phys < other._size_phys) ? res_buffer.resize(other._size_phys) : res_buffer.resize(this->_size_phys);

		openclcomputeobject->CreateBufferInput(this->_size_phys, this->_buffer.data());
		openclcomputeobject->CreateBufferInput(other_size_phys, other._buffer.data());
		openclcomputeobject->CreateBufferOutput(res_buffer.size(), NULL);

		openclcomputeobject->SetKernelArgs();
		openclcomputeobject->SetKernelArg(3, this->_rows);
		openclcomputeobject->SetKernelArg(4, this->_cols);
		openclcomputeobject->SetKernelArg(5, this->_strides[0]);
		openclcomputeobject->SetKernelArg(6, this->_strides[1]);
		openclcomputeobject->SetKernelArg(7, other.GetStrides()[0]);
		openclcomputeobject->SetKernelArg(8, other.GetStrides()[1]);
		openclcomputeobject->SetKernelArg(9, this->_size_phys);
		openclcomputeobject->SetKernelArg(10, other_size_phys);

		std::size_t global_work_size[1] = { (std::size_t)this->_size_logic }; // std::size_t global_work_size[2] = { (std::size_t)this->_rows, (std::size_t)this->_cols };
		std::size_t local_work_size[1] = { (std::size_t)2 };

		openclcomputeobject->EnqueueNDRangeKernel(local_work_size, global_work_size, 1, NULL);
		openclcomputeobject->Finish();
		openclcomputeobject->EnqueueReadBuffer(1, CL_TRUE, 0, res_buffer.size(), res_buffer.data(), 0, NULL, NULL);
		openclcomputeobject->ReleaseBuffers();
		for (auto& r : res_buffer)
			std::cout << r << "\n";
		std::cout << "\n";
		return MatrixStorage(res_buffer, this->_strides, this->_size_logic, this->_rows, this->_cols, this->_offset);

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
