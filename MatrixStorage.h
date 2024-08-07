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
		std::shared_ptr<ComputeObject> _comp_obj = nullptr;
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

		/// <summary>
		/// 
		/// </summary>
		/// <param name="id"></param>
		void SetCompObj(std::string name);

		/// <summary>
		/// 
		/// </summary>
		/// <param name="obj"></param>
		void SetCompObj(std::shared_ptr<ComputeObject> obj);

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

		MatrixStorage operator +(double scalar);
		MatrixStorage operator +(MatrixStorage rhs);
		MatrixStorage operator +=(double scalar);
		MatrixStorage operator +=(MatrixStorage rhs);
		MatrixStorage operator -(double scalar);
		MatrixStorage operator -(MatrixStorage rhs);
		MatrixStorage operator -=(double scalar);
		MatrixStorage operator -=(MatrixStorage rhs);
		MatrixStorage operator *(double scalar);
		MatrixStorage operator *(MatrixStorage rhs);
		MatrixStorage operator *=(double scalar);
		MatrixStorage operator *=(MatrixStorage rhs);
		MatrixStorage operator /(double scalar);
		MatrixStorage operator /(MatrixStorage rhs);
		MatrixStorage operator /=(double scalar);
		MatrixStorage operator /=(MatrixStorage rhs);

		friend std::ostream& operator<<(std::ostream& op, MatrixStorage& strg);
	};
}