#pragma once
#include <stdint.h>
#include <cmath>
#include <vector>
#include <iostream>
#include <memory>
#include <string>
#include "Dtype.h"
#include "MatrixStorage.h"
//using namespace std;

namespace Rubix
{
	/// <summary>
	/// Blueprint for TensorLayout
	/// </summary>
	class MatrixLayout
	{
		private:
		
			int rows_, cols_;
			Dtype<double> type;
		
		public: 

			/// <summary>
			/// 
			/// </summary>
			/// <param name="rows"></param>s
			/// <param name="cols"></param>
			/// <param name="elems"></param>
			/// <param name="strides"></param>
			MatrixLayout(int rows, int cols)
			{
				if (rows == 0 && cols == 0)
					throw std::invalid_argument("The rows and cols can't = 0 at the same time!");
				this->rows_ = rows;
				this->cols_ = cols;
				this->type = Dtype<double>();
			}

			/// <summary>
			/// The logical size of the matrix
			/// </summary>
			/// <returns>size(int)</returns>
			int size_logic()
			{
				return this->rows_ * this->cols_;
			}

			/// <summary>
			/// The physical size of the dtype in that matrix
			/// </summary>
			/// <returns>size in bytes(int)</returns>
			int DType_size()
			{
				return this->type.Physicalsize();
			}

			/// <summary>
			/// 
			/// </summary>
			int GetRows()
			{
				return this->rows_;
			}

			/// <summary>
			/// 
			/// </summary>
			int GetCols()
			{
				return this->cols_;
			}

			/// <summary>
			/// 
			/// </summary>
			/// <returns></returns>
			std::string GetDType()
			{
				return this->type.Name();
			}

			//Rule of 0
			~MatrixLayout() = default;
			MatrixLayout(const MatrixLayout&) = default;
			MatrixLayout& operator =(const MatrixLayout&) = default;
			MatrixLayout(MatrixLayout&&) = default;
			MatrixLayout& operator =(MatrixLayout&&) = default;
	};
}