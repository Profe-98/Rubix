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
		

	public:

		Matrix(std::string name, uint64_t rows, uint64_t cols, double elem, bool _resizable = false, bool _mutable = true);

		Matrix(std::string name, uint64_t rows, uint64_t cols, std::vector<double> elems, bool rowmajor = true, bool _resizable = false, bool _mutable = true);

		Matrix(std::string name, MatrixStorage storage, bool _resizable = false, bool _mutable = true);

		~Matrix() noexcept;

		
		//copy ctor
		Matrix(const Matrix& m);

		//copy assignment
		Matrix& operator =(const Matrix& m);

		//move c'tor
		Matrix(Matrix&& m) noexcept;
		
		//move assignment
		Matrix& operator =(Matrix&& m) noexcept;

		bool IsEmpty() const;

		bool IsPacked() const;

		bool IsPadded() const;

		bool IsCompressed() const;

		bool IsSquared() const;

		bool Is_mutable() const;

		bool Is_resizable() const;

		__declspec(deprecated("Not  implemented!"))
		void make_mutable() const;

		__declspec(deprecated("Not  implemented!"))
		void make_resizable() const;

		std::string Getname() const;

		uint64_t size_logical() const;
		
		uint64_t size_logical_b() const;

		uint64_t size_physical() const;

		uint64_t size_physical_b() const;

		uint64_t Getrows() const;

		uint64_t Getcols() const;

		std::pair<uint64_t, uint64_t> Getstrides() const;

		std::vector<double> GetEntries() const;

		std::string GetDType() const;


		__declspec(deprecated("Not fully implemented/experimental. Will lead to fatal error!"))
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

		__declspec(deprecated("Not fully implemented!"))
		friend std::ostream& operator<<(std::ostream& os, Matrix& m)
		{
			return os;
		}


	};
}