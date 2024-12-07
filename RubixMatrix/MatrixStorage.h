#pragma once
#include <vector>
#include <memory>
#include <cmath>
#include <iostream>
#include <memory>
#include <string>
#include "../RubixLogSys/Exceptions.h"
namespace Rubix
{
	struct MatrixStorage
	{
		private:

		bool _mutable = true;
		bool _resizable = false;
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

		MatrixStorage(std::vector<double> buffer, std::pair<uint64_t, uint64_t> strides, uint64_t size_logic, uint64_t rows, uint64_t cols, uint64_t offset = 0, bool _resizable = false, bool _mutable = true);
		MatrixStorage(double val, std::pair<uint64_t, uint64_t> strides, uint64_t size_logic, uint64_t rows, uint64_t cols, uint64_t offset = 0, bool _resizable = false, bool _mutable = true);

		//Rule of 0
		~MatrixStorage() = default;
		MatrixStorage(const MatrixStorage&) = default;
		MatrixStorage& operator =(const MatrixStorage&) = default;
		MatrixStorage(MatrixStorage&&) = default;
		MatrixStorage& operator =(MatrixStorage&&) = default;


		std::vector<double> GetBuffer() const;

		std::pair<uint64_t, uint64_t> GetStrides() const;

		uint64_t GetSize_logic() const;

		uint64_t GetSize_phys() const;

		uint64_t GetSize_phys_b() const;

		uint64_t GetOffset() const;

		void GetDevice() const;

		uint64_t GetRows() const;

		uint64_t GetCols() const;

		bool Is_shared() const;

		bool Is_mutable() const;

		bool Is_resizable() const;

		void resize();

		void fill();

		void get_device() const;


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