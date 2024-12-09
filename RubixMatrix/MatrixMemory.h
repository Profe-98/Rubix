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
	struct MatrixMemory
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
		MatrixMemory();

		MatrixMemory(std::vector<double> buffer, std::pair<uint64_t, uint64_t> strides, uint64_t size_logic, uint64_t rows, uint64_t cols, uint64_t offset = 0, bool _resizable = false, bool _mutable = true);
		MatrixMemory(double val, std::pair<uint64_t, uint64_t> strides, uint64_t size_logic, uint64_t rows, uint64_t cols, uint64_t offset = 0, bool _resizable = false, bool _mutable = true);

		//TODO: Adhere to rule of five, before DirectX implementation
		~MatrixMemory() noexcept;
		MatrixMemory(const MatrixMemory& storage);
		MatrixMemory& operator =(const MatrixMemory& storage);
		MatrixMemory(MatrixMemory&& storage) noexcept;
		MatrixMemory& operator =(MatrixMemory&& storage) noexcept;


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
		MatrixMemory Add_Scalar(double scalar);
		__declspec(deprecated("Not  implemented!"))
		MatrixMemory Add_Matrix(MatrixMemory other);
		__declspec(deprecated("Not  implemented!"))
		MatrixMemory Add_Eq_Scalar(double scalar);
		__declspec(deprecated("Not  implemented!"))
		MatrixMemory Add_Eq_Matrix(MatrixMemory other);
		__declspec(deprecated("Not  implemented!"))
		MatrixMemory Subtr_Scalar(double scalar);
		__declspec(deprecated("Not  implemented!"))
		MatrixMemory Subtr_Matrix(MatrixMemory other);
		__declspec(deprecated("Not  implemented!"))
		MatrixMemory Subtr_Eq_Scalar(double scalar);
		__declspec(deprecated("Not  implemented!"))
		MatrixMemory Subtr_Eq_Matrix(MatrixMemory other);
		__declspec(deprecated("Not  implemented!"))
		MatrixMemory Mult_Scalar(double scalar);
		__declspec(deprecated("Not  implemented!"))
		MatrixMemory Mult_Matrix(MatrixMemory other);
		__declspec(deprecated("Not  implemented!"))
		MatrixMemory Mult_Eq_Scalar(double scalar);
		__declspec(deprecated("Not  implemented!"))
		MatrixMemory Mult_Eq_Matrix(MatrixMemory other);
		__declspec(deprecated("Not  implemented!"))
		MatrixMemory Div_Scalar(double scalar);
		__declspec(deprecated("Not  implemented!"))
		MatrixMemory Div_Matrix(MatrixMemory other);
		__declspec(deprecated("Not  implemented!"))
		MatrixMemory Div_Eq_Scalar(double scalar);
		__declspec(deprecated("Not  implemented!"))
		MatrixMemory Div_Eq_Matrix(MatrixMemory other);

		friend std::ostream& operator<<(std::ostream& op, MatrixMemory& strg);
	};
}