#pragma once
#define __CL_ENABLE_EXCEPTIONS // must be defined before OpenCL header files are included
#include <vector>
#include <memory>
#include <cmath>
#include <iostream>
#include <memory>
#include <string>
#include "../RubixLogSys/Exceptions.h"
namespace Rubix
{
	class MatrixStorage
	{
		private:

		std::vector<double> _buffer;
		std::pair<uint64_t, uint64_t> _strides;
		uint64_t _size_phys; // represents the physical size of the matrix.
		uint64_t _size_logic;
		uint64_t _offset; // Position of the matrix's first element in the buffer. default is always 0
		uint64_t _rows;
		uint64_t _cols;
		//uint64_t _major_Dim = 0; //default 0 = width dimension (row major order); That means one step is needed to get to the next element in that dimension

		public:

		//Default c'tor
		MatrixStorage();

		MatrixStorage(std::vector<double> buffer, std::pair<uint64_t, uint64_t> strides, uint64_t size_logic, uint64_t rows, uint64_t cols, uint64_t offset = 0);
		MatrixStorage(double val, std::pair<uint64_t, uint64_t> strides, uint64_t size_logic, uint64_t rows, uint64_t cols, uint64_t offset = 0);

		//Rule of 0
		~MatrixStorage() = default;
		MatrixStorage(const MatrixStorage&) = default;
		MatrixStorage& operator =(const MatrixStorage&) = default;
		MatrixStorage(MatrixStorage&&) = default;
		MatrixStorage& operator =(MatrixStorage&&) = default;


		std::vector<double> GetBuffer();

		std::pair<uint64_t, uint64_t> GetStrides();

		uint64_t GetSize_logic();

		uint64_t GetSize_phys();

		uint64_t GetSize_phys_b();

		uint64_t GetOffset();

		void GetDevice();

		uint64_t GetRows();

		uint64_t GetCols();

		bool Is_shared();

		bool Is_mutable();

		void fill();

		uint64_t get_device();

		bool resizable();

		void resize();

		MatrixStorage Add_Scalar(double scalar);
		MatrixStorage Add_Matrix(MatrixStorage other);
		MatrixStorage Add_Eq_Scalar(double scalar);
		MatrixStorage Add_Eq_Matrix(MatrixStorage other);
		MatrixStorage Subtr_Scalar(double scalar);
		MatrixStorage Subtr_Matrix(MatrixStorage other);
		MatrixStorage Subtr_Eq_Scalar(double scalar);
		MatrixStorage Subtr_Eq_Matrix(MatrixStorage other);
		MatrixStorage Mult_Scalar(double scalar);
		MatrixStorage Mult_Matrix(MatrixStorage other);
		MatrixStorage Mult_Eq_Scalar(double scalar);
		MatrixStorage Mult_Eq_Matrix(MatrixStorage other);
		MatrixStorage Div_Scalar(double scalar);
		MatrixStorage Div_Matrix(MatrixStorage other);
		MatrixStorage Div_Eq_Scalar(double scalar);
		MatrixStorage Div_Eq_Matrix(MatrixStorage other);

		friend std::ostream& operator<<(std::ostream& op, MatrixStorage& strg);
	};
}