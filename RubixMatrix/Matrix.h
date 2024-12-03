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

		Matrix(std::string name, int rows, int cols, double elem);

		Matrix(std::string name, int rows, int cols, std::vector<double> elems, bool rowmajor = true);

		Matrix(std::string name, MatrixStorage storage);

		~Matrix() noexcept;

		
		//copy ctor
		Matrix(const Matrix& m);

		//copy assignment
		Matrix& operator =(const Matrix& m);

		//move c'tor
		Matrix(Matrix&& m) noexcept;
		
		//move assignment
		Matrix& operator =(Matrix&& m);

		bool IsEmpty();

		bool IsPacked();

		bool IsPadded();

		bool IsSquared();

		std::string Getname();

		int size_logical();
		
		int size_logical_b();

		int size_physical();

		int size_physical_b();

		int Getrows();

		int Getcols();

		std::vector<int> Getstrides();

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
		double operator() (int m, int n);
	
		/// <summary>
		/// Matrix addition with another mnatrix, according to the definition of matrix addition.
		/// </summary>
		/// <param name="other"> The right side operand</param>
		/// <returns>The - from the addition - resulting matrix packed in std::unique_ptr</returns>
		std::unique_ptr<Matrix> operator +(Matrix& other);
		
		/// <summary>
		/// Matrix addition with a scalar value, according to the definition of matrix addition.
		/// </summary>
		/// <param name="scalar">The right side operand</param>
		/// <returns>The - from the addition - resulting matrix packed in std::unique_ptr</returns>
		std::unique_ptr<Matrix> operator +(double scalar);

		/// <summary>
		/// 
		/// </summary>
		/// <param name="other"></param>
		/// <returns></returns>
		Matrix& operator +=(Matrix& other);

		/// <summary>
		/// 
		/// </summary>
		/// <param name="scalar"></param>
		/// <returns></returns>
		Matrix& operator +=(double scalar);

		/// <summary>
		/// Matrix subtraction with another matrix, according to the definition of matrix subtraction.
		/// </summary>
		/// <param name="other">The right side operand</param>
		/// <returns>The - from the subtraction - resulting matrix packed in std::unique_ptr</returns>
		std::unique_ptr<Matrix> operator -(Matrix& other);

		/// <summary>
		/// Matrix subtraction with a scalar value, according to the definition of matrix subtraction.
		/// </summary>
		/// <param name="scalar">The right side operand</param>
		/// <returns>The - from the subtraction - resulting matrix packed in std::unique_ptr</returns>
		std::unique_ptr<Matrix> operator -(double scalar);

		/// <summary>
		/// 
		/// </summary>
		/// <param name="other"></param>
		/// <returns></returns>
		Matrix& operator -=(Matrix& other);

		/// <summary>
		/// 
		/// </summary>
		/// <param name="scalar"></param>
		/// <returns></returns>
		Matrix& operator -=(double scalar);

		/// <summary>
		/// Matrix multiplication with another matrix, according to the definition of matrix multiplication.
		/// </summary>
		/// <param name="other">The right side operand</param>
		/// <returns>The - from the multiplication - resulting matrix packed in std::unique_ptr</returns>
		std::unique_ptr<Matrix> operator *(Matrix& other);

		/// <summary>
		/// Matrix multiplication with a scalar value, according to the definition of matrix multiplication.
		/// </summary>
		/// <param name="scalar">The right side operand</param>
		/// <returns>The - from the multiplication - resulting matrix packed in std::unique_ptr</returns>
		std::unique_ptr<Matrix> operator *(double scalar);

		Matrix& operator *=(Matrix& other);

		/// <summary>
		/// 
		/// </summary>
		/// <param name="scalar"></param>
		/// <returns></returns>
		Matrix& operator *=(double scalar);

		/// <summary>
		/// Inversed multiplication...
		/// </summary>
		/// <param name="other"></param>
		/// <returns></returns>
		std::unique_ptr<Matrix> operator /(Matrix& other);

		/// <summary>
		/// 
		/// </summary>
		/// <param name="scalar"></param>
		/// <returns></returns>
		std::unique_ptr<Matrix> operator /(double scalar);

		/// <summary>
		/// Inversed multiplication...
		/// </summary>
		/// <param name="other"></param>
		/// <returns></returns>
		Matrix& operator /=(Matrix& other);

		/// <summary>
		/// 
		/// </summary>
		/// <param name="scalar"></param>
		/// <returns></returns>
		Matrix& operator /=(double scalar);

		bool operator ==(Matrix& other);

		bool operator !=(Matrix& other);

		friend std::ostream& operator<<(std::ostream& os, Matrix& m)
		{
			return os;
		}


	};
}