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
#include "MatrixLayout.h"
namespace Rubix
{
	using namespace std::chrono;

	class Matrix
	{
	private:
		std::unique_ptr<MatrixLayout> _layout;
		MatrixStorage _storage;
		std::string _name;
		bool _mutable = true;
		

	public:

		Matrix(std::string name, int rows, int cols, double elem) : _name(name)
		{
			this->_layout =  std::make_unique<MatrixLayout>(rows, cols);
			std::vector<int> strides(2, 0);
			this->_storage = MatrixStorage(elem, strides, rows * cols, rows, cols);
		}

		Matrix(std::string name, int rows, int cols, std::vector<double> elems, bool rowmajor = true) : _name{ name }
		{
			this->_layout = std::make_unique<MatrixLayout>(rows, cols);
			std::vector<int> strides;
			if (rowmajor)
				strides = { 1, cols };
			else
				strides = { rows, 1 };
			this->_storage = MatrixStorage(elems, strides, rows * cols, rows, cols);
		}

		Matrix(std::string name, MatrixStorage storage) : _name(name), _storage(storage)
		{

		}

		~Matrix() noexcept
		{
			_layout = nullptr;
			std::cout << _name << ": Matrix d'tor called.\n";
		}

		
		//copy ctor
		Matrix(const Matrix& m) : _layout(std::make_unique<MatrixLayout>(*m._layout)), _storage(m._storage), _name(m._name), _mutable(m._mutable)
		{

		}

		//copy assignment
		Matrix& operator =(const Matrix& m)
		{
			if(this != &m)
			{
				_layout = nullptr;
				_layout = std::make_unique<MatrixLayout>(*m._layout);
				_storage = m._storage;
				_name = m._name;
				_mutable = m._mutable;
			}
			return *this;
		}

		//move c'tor
		Matrix(Matrix&& m) noexcept : _layout(std::make_unique<MatrixLayout>(*m._layout)), _storage(m._storage), _name(m._name), _mutable(m._mutable)
		{
			m._layout = nullptr;
		}
		
		//move assignment
		Matrix& operator =(Matrix&& m)
		{
			if (this != &m)
			{
				_layout = nullptr;
				_layout = std::make_unique<MatrixLayout>(*m._layout);
				_storage = m._storage;
				_name = m._name;
				_mutable = m._mutable;
			}
			return *this;
		}

		bool IsEmpty()
		{
			return this->size_physical() == 0;
		}

		bool IsPacked()
		{
			return this->size_physical() == this->size_logical();
		}

		bool IsPadded()
		{
			return this->size_physical() > this->size_logical();
		}

		bool IsSquared()
		{
			return this->Getrows() == this->Getcols();
		}

		std::string Getname()
		{
			return this->_name;
		}

		int size_logical()
		{
			return this->_layout->size_logic();
		}
		
		int size_logical_b()
		{
			return this->_layout->size_logic() * _layout->DType_size();
		}

		int size_physical()
		{
			return this->_storage.GetSize_phys(); 
		}

		int size_physical_b()
		{
			return this->_storage.GetSize_phys_b();
		}

		int Getrows()
		{
			return this->_layout->GetRows();
		}

		int Getcols()
		{
			return this->_layout->GetCols();
		}

		std::vector<int> Getstrides()
		{
			return this->_storage.GetStrides();
		}

		std::vector<double> GetEntries()
		{
			return this->_storage.GetBuffer();
		}

		std::string GetDType()
		{
			return this->_layout->GetDType();
		}

		/// <summary>
		/// Adds all values on the main diagonal (where the row index = the column index) of the matrix up and returns the result
		/// </summary>
		/// <returns>Value of type T</returns>
		double Trace()
		{
			//auto t0 = steady_clock::now();

			int r = this->Getrows();
			int c = this->Getcols();

			if (r < 2 || c < 2)
			{
				std::cerr << "\n\nERROR:\n	The matrix must atleast have 2 rows and 2 columns, so that the Trace operation can be performed!\n" << "Matrix(Name = " << this->_name << "; Rows = " << r << "; Columns = " << c << ")\n\n";
				return 0 ;
			}

			double res = 0;
			int iter = 0;
			int m_size = r * c;
			while (iter < m_size)
			{
				res += this->_storage.GetBuffer()[iter];
				iter += c + 1;
			}

			//auto t1 = steady_clock::now();

			//std::cout << "Time: " << nanoseconds{ t1 - t0 }.count() << "ns;\n\n";
			return res;
		}

		void* operator new(std::size_t s)
		{
			void* p = malloc(s);
			return p;
		}

		void operator delete(void* p)
		{
			free(p);
		}

		/// <summary>
		/// This operatur is used to access a single element / entry in the matrix 
		/// </summary>
		/// <param name="m"> The index for the row in which our target is stored.</param>
		/// <param name="n"> The index for the column in which our target is stored.</param>
		/// <returns>The entry - of type T - that is stored at position (m * columns + n) in the matrix.</returns>
		double operator() (int m, int n)
		{
			if (m >= this->Getrows() || n >= this->Getcols())
				throw std::out_of_range("Matrix indices out of range!");

			return this->GetEntries()[m * this->Getcols() + n];

		}
	
		/// <summary>
		/// Matrix addition with another mnatrix, according to the definition of matrix addition.
		/// </summary>
		/// <param name="other"> The right side operand</param>
		/// <returns>The - from the addition - resulting matrix packed in std::unique_ptr</returns>
		std::unique_ptr<Matrix> operator +(Matrix& other)
		{
			std::string resname = this->_name + "_Add_" + other._name;
			MatrixStorage res_strg = this->_storage + other._storage;
			return std::make_unique<Matrix>(resname, res_strg);


			return nullptr;//std::make_unique(name, this->Getrows(), this->Getcols(), v);
		}
		
		/// <summary>
		/// Matrix addition with a scalar value, according to the definition of matrix addition.
		/// </summary>
		/// <param name="scalar">The right side operand</param>
		/// <returns>The - from the addition - resulting matrix packed in std::unique_ptr</returns>
		std::unique_ptr<Matrix> operator +(double scalar)
		{
			int s = this->size_physical();
			if (s == 0)
				throw std::invalid_argument("The given matrix is empty!");
			std::string resname = this->_name + "_Add(s)_" + std::to_string(scalar);
			MatrixStorage res_strg = this->_storage + scalar;
			return std::make_unique<Matrix>(resname, res_strg);
		}

		/// <summary>
		/// 
		/// </summary>
		/// <param name="other"></param>
		/// <returns></returns>
		Matrix& operator +=(Matrix& other)
		{
			if (this->Getrows() != other.Getrows() || this->Getcols() != other.Getcols())
				throw std::invalid_argument("The two matrices are not additive conformable!");

			return *this;
		}

		/// <summary>
		/// 
		/// </summary>
		/// <param name="scalar"></param>
		/// <returns></returns>
		Matrix& operator +=(double scalar)
		{
			return *this;
		}

		/// <summary>
		/// Matrix subtraction with another matrix, according to the definition of matrix subtraction.
		/// </summary>
		/// <param name="other">The right side operand</param>
		/// <returns>The - from the subtraction - resulting matrix packed in std::unique_ptr</returns>
		std::unique_ptr<Matrix> operator -(Matrix& other)
		{
			int s = this->size_logical();
			int s1 = other.size_logical();
			if (s == 0 || s1 == 0)
				throw std::invalid_argument("One of the given matrices is empty!");

			return nullptr;//std::make_unique<Matrix<T>>(name, this->Getrows(), this->Getcols(), v, this->Getstrides());
		}

		/// <summary>
		/// Matrix subtraction with a scalar value, according to the definition of matrix subtraction.
		/// </summary>
		/// <param name="scalar">The right side operand</param>
		/// <returns>The - from the subtraction - resulting matrix packed in std::unique_ptr</returns>
		std::unique_ptr<Matrix> operator -(double scalar)
		{
			int s = this->size_logical();
			if (s == 0)
				throw std::invalid_argument("The given matrix is empty!");

			return nullptr;//std::make_unique<Matrix<T>>(name, this->Getrows(), this->Getcols(), v, this->Getstrides());
		}

		/// <summary>
		/// 
		/// </summary>
		/// <param name="other"></param>
		/// <returns></returns>
		Matrix& operator -=(Matrix& other)
		{
			if (this->Getrows() != other.Getrows() || this->Getcols() != other.Getcols())
				throw std::invalid_argument("The two matrices are not additive conformable!");

			return *this;
		}

		/// <summary>
		/// 
		/// </summary>
		/// <param name="scalar"></param>
		/// <returns></returns>
		Matrix& operator -=(double scalar)
		{
			return *this;
		}

		/// <summary>
		/// Matrix multiplication with another matrix, according to the definition of matrix multiplication.
		/// </summary>
		/// <param name="other">The right side operand</param>
		/// <returns>The - from the multiplication - resulting matrix packed in std::unique_ptr</returns>
		std::unique_ptr<Matrix> operator *(Matrix& other)
		{
			//checks if both matrices are multiplicative conformable
			if (this->Getcols() != other.Getrows())
				throw std::invalid_argument("The two matrices are not multiplicative conformable!");

			return nullptr;
		}

		/// <summary>
		/// Matrix multiplication with a scalar value, according to the definition of matrix multiplication.
		/// </summary>
		/// <param name="scalar">The right side operand</param>
		/// <returns>The - from the multiplication - resulting matrix packed in std::unique_ptr</returns>
		std::unique_ptr<Matrix> operator *(double scalar)
		{
			return nullptr;//std::make_unique<Matrix<T>>(name, this->Getrows(), this->Getcols(), v, this->Getstrides());
		}

		Matrix& operator *=(Matrix& other)
		{
			//checks if both matrices are multiplicative conformable
			if (this->Getcols() != other.Getrows())
				throw std::invalid_argument("The two matrices are not multiplicative conformable!");

			return *this;
		}

		/// <summary>
		/// 
		/// </summary>
		/// <param name="scalar"></param>
		/// <returns></returns>
		Matrix& operator *=(double scalar)
		{
			return *this;
		}

		/// <summary>
		/// Inversed multiplication...
		/// </summary>
		/// <param name="other"></param>
		/// <returns></returns>
		std::unique_ptr<Matrix> operator /(Matrix& other)
		{
			return nullptr;//std::make_unique<Matrix<T>>(name, this->Getrows(), this->Getcols(), v, this->Getstrides());
		}

		/// <summary>
		/// 
		/// </summary>
		/// <param name="scalar"></param>
		/// <returns></returns>
		std::unique_ptr<Matrix> operator /(double scalar)
		{
			return nullptr;//std::make_unique<Matrix<T>>(name, this->Getrows(), this->Getcols(), v, this->Getstrides());
		}

		/// <summary>
		/// Inversed multiplication...
		/// </summary>
		/// <param name="other"></param>
		/// <returns></returns>
		Matrix& operator /=(Matrix& other)
		{
			return *this;
		}

		/// <summary>
		/// 
		/// </summary>
		/// <param name="scalar"></param>
		/// <returns></returns>
		Matrix& operator /=(double scalar)
		{
			return *this;
		}

		bool operator ==(Matrix& other)
		{
			if (this->Getrows() != other.Getrows() || this->Getcols() != other.Getcols() || this->size_physical_b() != other.size_physical_b() || this->Getstrides() != other.Getstrides())
				return false;

            int s = this->size_logical();
			for (int i = 0; i < s; ++i)
			{
				if (this->GetEntries()[i] != other.GetEntries()[i])
					return false;
			}

			return true;
		}

		bool operator !=(Matrix& other)
		{
			if (this->Getrows() != other.Getrows() || this->Getcols() != other.Getcols() || this->size_physical_b() != other.size_physical_b() || this->Getstrides() != other.Getstrides())
				return true;

			for (int i = 0; i < this->size_logical(); ++i)
			{
				if (this->GetEntries()[i] != other.GetEntries()[i])
					return true;
			}

			return false;
		}

		friend std::ostream& operator<<(std::ostream& os, Matrix& m)
		{
			return os;
		}


	};
}