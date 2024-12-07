#pragma once
#include <stdint.h>
#include <chrono>
#include <vector>
#include <iostream>
#include <cmath>
#include <memory>
#include <string>
#include <map>
#include <set>
#include "MatrixStorage.h"
namespace Rubix
{
	using namespace std::chrono;

	class Matrix
	{
	private:
		MatrixStorage _storage;
		std::string _name;
		bool _mutable = true;
		

	public:

		Matrix(std::string name, uint64_t rows, uint64_t cols, double elem);

		Matrix(std::string name, uint64_t rows, uint64_t cols, std::vector<double> elems, bool rowmajor = true);

		Matrix(std::string name, MatrixStorage storage);

		~Matrix() noexcept;

		
		//copy ctor
		Matrix(const Matrix& m);

		//copy assignment
		Matrix& operator =(const Matrix& m);

		//move c'tor
		Matrix(Matrix&& m) noexcept;
		
		//move assignment
		Matrix& operator =(Matrix&& m) noexcept;

		bool IsEmpty();

		bool IsPacked();

		bool IsPadded();

		bool IsCompressed();

		bool IsSquared();

		std::string Getname();

		uint64_t size_logical();
		
		uint64_t size_logical_b();

		uint64_t size_physical();

		uint64_t size_physical_b();

		uint64_t Getrows();

		uint64_t Getcols();

		std::pair<uint64_t, uint64_t> Getstrides();

		std::vector<double> GetEntries();

		std::string GetDType();

		/// <summary>
		/// Adds all values on the main diagonal (where the row index = the column index) of the matrix up and returns the result
		/// </summary>
		/// <returns>Value of type T</returns>
		double Trace();

		/// <summary>
		/// This operator is used to access a single element / entry in the matrix 
		/// </summary>
		/// <param name="m"> The index for the row in which our target is stored.</param>
		/// <param name="n"> The index for the column in which our target is stored.</param>
		/// <returns>The entry - of type T - that is stored at position (m * columns + n) in the matrix.</returns>
		double operator() (uint64_t m, uint64_t n);
	
		bool operator ==(Matrix& other);

		bool operator !=(Matrix& other);

		friend std::ostream& operator<<(std::ostream& os, Matrix& m)
		{
			return os;
		}


	};
}