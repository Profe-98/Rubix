#pragma once
#define __CL_ENABLE_EXCEPTIONS // must be defined before OpenCL header files are included
#include <stdint.h>
#include <vector>
#include <memory>
#include <cmath>
#include <iostream>
#include <memory>
#include <string>
#include "Compute_Object.h"
namespace Rubix
{
	class MatrixStorage
	{
		private:

		std::vector<double> _buffer;
		std::vector<int> _strides;
		int _size_phys; // represents the physical size of the matrix.
		int _size_logic;
		int _offset; // Position of the matrix's first element in the buffer. default is always 0
		int _rows;
		int _cols;
		//int _major_Dim = 0; //default 0 = width dimension (row major order); That means one step is needed to get to the next element in that dimension

		public:

		//Default c'tor
		MatrixStorage();

		MatrixStorage(std::vector<double> buffer, std::vector<int> strides, int size_logic, int rows, int cols, int offset = 0);
		MatrixStorage(double val, std::vector<int> strides, int size_logic, int rows, int cols, int offset = 0);

		//Rule of 0
		~MatrixStorage() = default;
		MatrixStorage(const MatrixStorage&) = default;
		MatrixStorage& operator =(const MatrixStorage&) = default;
		MatrixStorage(MatrixStorage&&) = default;
		MatrixStorage& operator =(MatrixStorage&&) = default;

		std::shared_ptr<ComputeObject> GetCompObj();

		std::vector<double> GetBuffer();

		std::vector<int> GetStrides();

		int GetSize_logic();

		int GetSize_phys();

		int GetSize_phys_b();

		int GetOffset();

		void GetDevice();

		int GetRows();

		int GetCols();

		void copy();

		bool Is_shared();

		bool Is_mutable();

		void fill();

		int get_device();

		bool resizable();

		void resize();

		MatrixStorage Add_Scalar(double scalar, std::unique_ptr<ComputeObject> openclcomputeobject);
		MatrixStorage Add_Matrix(MatrixStorage other, std::unique_ptr<ComputeObject> openclcomputeobject);
		MatrixStorage Add_Eq_Scalar(double scalar, std::unique_ptr<ComputeObject> openclcomputeobject);
		MatrixStorage Add_Eq_Matrix(MatrixStorage other, std::unique_ptr<ComputeObject> openclcomputeobject);
		MatrixStorage Subtr_Scalar(double scalar, std::unique_ptr<ComputeObject> openclcomputeobject);
		MatrixStorage Subtr_Matrix(MatrixStorage other, std::unique_ptr<ComputeObject> openclcomputeobject);
		MatrixStorage Subtr_Eq_Scalar(double scalar, std::unique_ptr<ComputeObject> openclcomputeobject);
		MatrixStorage Subtr_Eq_Matrix(MatrixStorage other, std::unique_ptr<ComputeObject> openclcomputeobject);
		MatrixStorage Mult_Scalar(double scalar, std::unique_ptr<ComputeObject> openclcomputeobject);
		MatrixStorage Mult_Matrix(MatrixStorage other, std::unique_ptr<ComputeObject> openclcomputeobject);
		MatrixStorage Mult_Eq_Scalar(double scalar, std::unique_ptr<ComputeObject> openclcomputeobject);
		MatrixStorage Mult_Eq_Matrix(MatrixStorage other, std::unique_ptr<ComputeObject> openclcomputeobject);
		MatrixStorage Div_Scalar(double scalar, std::unique_ptr<ComputeObject> openclcomputeobject);
		MatrixStorage Div_Matrix(MatrixStorage other, std::unique_ptr<ComputeObject> openclcomputeobject);
		MatrixStorage Div_Eq_Scalar(double scalar, std::unique_ptr<ComputeObject> openclcomputeobject);
		MatrixStorage Div_Eq_Matrix(MatrixStorage other, std::unique_ptr<ComputeObject> openclcomputeobject);

		friend std::ostream& operator<<(std::ostream& op, MatrixStorage& strg);
	};
}