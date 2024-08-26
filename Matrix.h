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

		double Trace();

		std::unique_ptr<Matrix> Add_Scalar();
		std::unique_ptr<Matrix> Add_Matrix();
		void Add_Eq_Scalar();
		void Add_Eq_Matrix();
		std::unique_ptr<Matrix> Subtr_Scalar();
		std::unique_ptr<Matrix> Subtr_Matrix();
		void Subtr_Eq_Scalar();
		void Subtr_Eq_Matrix();
		std::unique_ptr<Matrix> Mult_Scalar();
		std::unique_ptr<Matrix> Mult_Matrix();
		void Mult_Eq_Scalar();
		void Mult_Eq_Matrix();
		std::unique_ptr<Matrix> Div_Scalar();
		std::unique_ptr<Matrix> Div_Matrix();
		void Div_Eq_Scalar();
		void Div_Eq_Matrix();

		void* operator new(std::size_t s)
		{
			void* p = malloc(s);
			return p;
		}

		void operator delete(void* p)
		{
			free(p);
		}

		friend std::ostream& operator<<(std::ostream& os, Matrix& m)
		{
			return os;
		}


	};
}