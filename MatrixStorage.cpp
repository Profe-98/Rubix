#define __CL_ENABLE_EXCEPTIONS // must be defined before OpenCL header files are included
#include "MatrixStorage.h"
#include "CLManager.h"
#include "Compute_Object.h"

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

	std::shared_ptr<ComputeObject> MatrixStorage::GetCompObj()
	{
		return this->_comp_obj;
	}

	/// <summary>
	/// 
	/// </summary>
	/// <param name="id"></param>
	void MatrixStorage::SetCompObj(std::string name)
	{
		 this->_comp_obj = CLManager::_compobj_map[name];
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

	MatrixStorage MatrixStorage::operator+(double scalar)
	{
		if (this->_buffer.empty() || this->_buffer.size() == 0)
			throw std::invalid_argument("The given matrix is empty");
		if (scalar == 0.0)
			return MatrixStorage(this->_buffer, this->_strides, this->_size_logic, this->_rows, this->_cols, this->_offset);
		std::vector<double> res_buffer(this->_size_phys);
		
		SetCompObj("matrix_add_scalar");
		
		this->_comp_obj->CreateBufferInput(this->_size_phys, this->_buffer.data());
		this->_comp_obj->CreateBufferOutput(res_buffer.size(), NULL);
		
		this->_comp_obj->SetKernelArgs();
		this->_comp_obj->SetKernelArg(2, scalar);
		this->_comp_obj->SetKernelArg(3, this->_size_phys);
		
		std::size_t global_work_size[1] = {(std::size_t)this->_size_phys};
		std::size_t local_work_size[1] = {(std::size_t)2 };

		this->_comp_obj->EnqueueNDRangeKernel(local_work_size, global_work_size, 1, NULL);
		this->_comp_obj->Finish();
		this->_comp_obj->EnqueueReadBuffer(1, CL_TRUE, 0, res_buffer.size(), res_buffer.data(), 0, NULL, NULL);
		this->_comp_obj->ReleaseBuffers();
		this->_comp_obj = nullptr;
		return MatrixStorage(res_buffer, this->_strides, this->_size_logic, this->_rows, this->_cols, this->_offset);
	}

	MatrixStorage MatrixStorage::operator +(MatrixStorage rhs)
	{
		int rhs_size_logic = rhs.GetSize_logic();
		int rhs_size_phys = rhs.GetSize_phys();
		if(this->_buffer.empty() || rhs.GetBuffer().empty())
			throw std::invalid_argument("To be additive conformable, both matrices must contain elements!");
		if(this->_size_logic != rhs_size_logic)
			throw std::invalid_argument("To be additive conformable, both matrices must've the same size!");
		if(this->_rows != rhs.GetRows() || this->_cols != rhs.GetCols())
			throw std::invalid_argument("To be additive conformable, both matrices must've equal amound of rows and columns!");
		
		std::vector<double> res_buffer(this->_size_phys);
		//(this->_size_phys < rhs._size_phys) ? res_buffer.resize(rhs._size_phys) : res_buffer.resize(this->_size_phys);
	
		SetCompObj("matrix_add_matrix");
		this->_comp_obj->CreateBufferInput(this->_size_phys, this->_buffer.data());
		this->_comp_obj->CreateBufferInput(rhs_size_phys, rhs._buffer.data());
		this->_comp_obj->CreateBufferOutput(res_buffer.size(), NULL);
		
		this->_comp_obj->SetKernelArgs();
		this->_comp_obj->SetKernelArg(3, this->_rows);
		this->_comp_obj->SetKernelArg(4, this->_cols);
		this->_comp_obj->SetKernelArg(5, this->_strides[0]);
		this->_comp_obj->SetKernelArg(6, this->_strides[1]);
		this->_comp_obj->SetKernelArg(7, rhs.GetStrides()[0]);
		this->_comp_obj->SetKernelArg(8, rhs.GetStrides()[1]);
		this->_comp_obj->SetKernelArg(9, this->_size_phys);
		this->_comp_obj->SetKernelArg(10, rhs_size_phys);

		std::size_t global_work_size[1] = { (std::size_t)this->_size_logic}; // std::size_t global_work_size[2] = { (std::size_t)this->_rows, (std::size_t)this->_cols };
		std::size_t local_work_size[1] = { (std::size_t)2};

		this->_comp_obj->EnqueueNDRangeKernel(local_work_size, global_work_size, 1, NULL);
		this->_comp_obj->Finish();
		this->_comp_obj->EnqueueReadBuffer(1, CL_TRUE, 0, res_buffer.size(), res_buffer.data(), 0, NULL, NULL);
		this->_comp_obj->ReleaseBuffers();
		this->_comp_obj = nullptr;
		for (auto& r : res_buffer)
			std::cout << r << "\n";
		std::cout << "\n";
		return MatrixStorage(res_buffer, this->_strides, this->_size_logic, this->_rows, this->_cols, this->_offset);
	}

	MatrixStorage MatrixStorage::operator+=(double scalar)
	{
		return MatrixStorage();
	}

	MatrixStorage MatrixStorage::operator+=(MatrixStorage rhs)
	{
		return MatrixStorage();
	}

	MatrixStorage MatrixStorage::operator-(double scalar)
	{
		return MatrixStorage();
	}

	MatrixStorage MatrixStorage::operator-(MatrixStorage rhs)
	{
		return MatrixStorage();
	}

	MatrixStorage MatrixStorage::operator-=(double scalar)
	{
		return MatrixStorage();
	}

	MatrixStorage MatrixStorage::operator-=(MatrixStorage rhs)
	{
		return MatrixStorage();
	}

	MatrixStorage MatrixStorage::operator*(double scalar)
	{
		return MatrixStorage();
	}

	MatrixStorage MatrixStorage::operator*(MatrixStorage rhs)
	{
		return MatrixStorage();
	}

	MatrixStorage MatrixStorage::operator*=(double scalar)
	{
		return MatrixStorage();
	}

	MatrixStorage MatrixStorage::operator*=(MatrixStorage rhs)
	{
		return MatrixStorage();
	}

	MatrixStorage MatrixStorage::operator/(double scalar)
	{
		return MatrixStorage();
	}

	MatrixStorage MatrixStorage::operator/(MatrixStorage rhs)
	{
		return MatrixStorage();
	}

	MatrixStorage MatrixStorage::operator/=(double scalar)
	{
		return MatrixStorage();
	}

	MatrixStorage MatrixStorage::operator/=(MatrixStorage rhs)
	{
		return MatrixStorage();
	}

	std::ostream& operator<<(std::ostream& op, MatrixStorage& strg)
	{
		return op;
	}
}
