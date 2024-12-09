#pragma once
#include <vector>
#include <memory>
#include <cmath>
#include <iostream>
#include <string>
#include <utility>
#include "../RubixLogSys/Exceptions.h"
namespace Rubix
{
	struct MatrixStorage
	{
	private:


		// const uint64_t MAX_VALUE_ROWS_AND_COLS = 4294967295;
		bool _mutable = true;
		bool _resizable = false;
		std::vector<double> _buffer = {};
		std::pair<uint64_t, uint64_t> _strides{};
		uint64_t _size_phys = 0; // represents the physical size of the matrix.
		uint64_t _size_logic = 0;
		uint64_t _offset = 0; // Position of the matrix's first element in the buffer. default is always 0
		uint64_t _rows = 0;
		uint64_t _cols = 0;
		//uint64_t _major_Dim = 0; //default 0 = width dimension (row major order); That means one step is needed to get to the next element in that dimension

		public:

		//Default c'tor
		MatrixStorage();

		MatrixStorage(std::vector<double> buffer, std::pair<uint64_t, uint64_t> strides, uint64_t size_logic, uint64_t rows, uint64_t cols, uint64_t offset = 0, bool _resizable = false, bool _mutable = true);
		MatrixStorage(double val, std::pair<uint64_t, uint64_t> strides, uint64_t size_logic, uint64_t rows, uint64_t cols, uint64_t offset = 0, bool _resizable = false, bool _mutable = true);

		//TODO: Adhere to rule of five, before DirectX implementation
		~MatrixStorage() noexcept;
		MatrixStorage(const MatrixStorage& storage);
		MatrixStorage& operator =(const MatrixStorage& storage);
		MatrixStorage(MatrixStorage&& storage) noexcept;
		MatrixStorage& operator =(MatrixStorage&& storage) noexcept;


		std::vector<double> GetBuffer() const;

		std::pair<uint64_t, uint64_t> GetStrides() const;

		uint64_t GetSize_logic() const;

		uint64_t GetSize_phys() const;

		uint64_t GetSize_phys_b() const;

		uint64_t GetOffset() const;

		__declspec(deprecated("Not  implemented!"))
		void GetDevice() const;

		uint64_t GetRows() const;

		uint64_t GetCols() const;

		__declspec(deprecated("Not  implemented!"))
		bool Is_shared() const;

		bool Is_mutable() const;

		bool Is_resizable() const;

		__declspec(deprecated("Not  implemented!"))
		void resize();

		__declspec(deprecated("Not  implemented!"))
		void fill();

		__declspec(deprecated("Not  implemented!"))
		MatrixStorage Add_Scalar(double scalar);
		__declspec(deprecated("Not  implemented!"))
		MatrixStorage Add_Matrix(MatrixStorage other);
		__declspec(deprecated("Not  implemented!"))
		MatrixStorage Add_Eq_Scalar(double scalar);
		__declspec(deprecated("Not  implemented!"))
		MatrixStorage Add_Eq_Matrix(MatrixStorage other);
		__declspec(deprecated("Not  implemented!"))
		MatrixStorage Subtr_Scalar(double scalar);
		__declspec(deprecated("Not  implemented!"))
		MatrixStorage Subtr_Matrix(MatrixStorage other);
		__declspec(deprecated("Not  implemented!"))
		MatrixStorage Subtr_Eq_Scalar(double scalar);
		__declspec(deprecated("Not  implemented!"))
		MatrixStorage Subtr_Eq_Matrix(MatrixStorage other);
		__declspec(deprecated("Not  implemented!"))
		MatrixStorage Mult_Scalar(double scalar);
		__declspec(deprecated("Not  implemented!"))
		MatrixStorage Mult_Matrix(MatrixStorage other);
		__declspec(deprecated("Not  implemented!"))
		MatrixStorage Mult_Eq_Scalar(double scalar);
		__declspec(deprecated("Not  implemented!"))
		MatrixStorage Mult_Eq_Matrix(MatrixStorage other);
		__declspec(deprecated("Not  implemented!"))
		MatrixStorage Div_Scalar(double scalar);
		__declspec(deprecated("Not  implemented!"))
		MatrixStorage Div_Matrix(MatrixStorage other);
		__declspec(deprecated("Not  implemented!"))
		MatrixStorage Div_Eq_Scalar(double scalar);
		__declspec(deprecated("Not  implemented!"))
		MatrixStorage Div_Eq_Matrix(MatrixStorage other);

		friend std::ostream& operator<<(std::ostream& op, MatrixStorage& strg);
	};
}