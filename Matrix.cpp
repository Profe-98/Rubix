#include "Matrix.h"
#include "Exceptions.h"

namespace Rubix
{
	Matrix::Matrix(std::string name, int rows, int cols, double elem) : _name(name)
	{
		std::vector<int> strides(2, 0);
		this->_storage = MatrixStorage(elem, strides, rows * cols, rows, cols);
	}

	Matrix::Matrix(std::string name, int rows, int cols, std::vector<double> elems, bool rowmajor = true) : _name{ name }
	{
		std::vector<int> strides;
		if (rowmajor)
			strides = { 1, cols };
		else
			strides = { rows, 1 };
		this->_storage = MatrixStorage(elems, strides, rows * cols, rows, cols);
	}

	Matrix::Matrix(std::string name, MatrixStorage storage) : _name(name), _storage(storage)
	{

	}

	Matrix::~Matrix() noexcept
	{
		std::cout << _name << ": Matrix d'tor called.\n";
	}


	//copy ctor
	Matrix::Matrix(const Matrix& m) : _storage(m._storage), _name(m._name), _mutable(m._mutable)
	{

	}

	//copy assignment
	Matrix& Matrix::operator =(const Matrix& m)
	{
		if (this != &m)
		{
			_storage = m._storage;
			_name = m._name;
			_mutable = m._mutable;
		}
		return *this;
	}

	//move c'tor
	Matrix::Matrix(Matrix&& m) noexcept : _storage(m._storage), _name(m._name), _mutable(m._mutable)
	{

	}

	//move assignment
	Matrix& Matrix::operator =(Matrix&& m) noexcept
	{
		if (this != &m)
		{
			_storage = m._storage;
			_name = m._name;
			_mutable = m._mutable;
		}
		return *this;
	}

	bool Matrix::IsEmpty()
	{
		return this->size_physical() == 0;
	}

	bool Matrix::IsPacked()
	{
		return this->size_physical() == this->size_logical();
	}

	bool Matrix::IsPadded()
	{
		return this->size_physical() > this->size_logical();
	}

	bool Matrix::IsSquared()
	{
		return this->Getrows() == this->Getcols();
	}

	std::string Matrix::Getname()
	{
		return this->_name;
	}

	int Matrix::size_logical()
	{
		return this->_storage.GetSize_logic();
	}

	int Matrix::size_logical_b()
	{
		return this->_storage.GetSize_logic() * sizeof(double);
	}

	int Matrix::size_physical()
	{
		return this->_storage.GetSize_phys();
	}

	int Matrix::size_physical_b()
	{
		return this->_storage.GetSize_phys_b();
	}

	int Matrix::Getrows()
	{
		return this->_storage.GetRows();
	}

	int Matrix::Getcols()
	{
		return this->_storage.GetCols();
	}

	std::vector<int> Matrix::Getstrides()
	{
		return this->_storage.GetStrides();
	}

	std::vector<double> Matrix::GetEntries()
	{
		return this->_storage.GetBuffer();
	}

	std::string Matrix::GetDType()
	{
		return "double"; // temporary
	}

	/// <summary>
	/// Adds all values on the main diagonal (where the row index = the column index) of the matrix up and returns the result
	/// </summary>
	/// <returns>Value of type T</returns>
	double Matrix::Trace()
	{
		//auto t0 = steady_clock::now();

		int r = this->Getrows();
		int c = this->Getcols();

		if (r < 2 || c < 2)
		{
			std::cerr << "\n\nERROR:\n	The matrix must atleast have 2 rows and 2 columns, so that the Trace operation can be performed!\n" << "Matrix(Name = " << this->_name << "; Rows = " << r << "; Columns = " << c << ")\n\n";
			return 0;
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

	std::unique_ptr<Matrix> Matrix::Add_Scalar()
	{
		throw NotImplementedException("The method isn't implented yet!");
		return std::unique_ptr<Matrix>();
	}

	std::unique_ptr<Matrix> Matrix::Add_Matrix()
	{
		throw NotImplementedException("The method isn't implented yet!");
		return std::unique_ptr<Matrix>();
	}

	void Matrix::Add_Eq_Scalar()
	{
		throw NotImplementedException("The method isn't implented yet!");

	}

	void Matrix::Add_Eq_Matrix()
	{
		throw NotImplementedException("The method isn't implented yet!");
	}


	std::unique_ptr<Matrix> Matrix::Subtr_Scalar()
	{
		throw NotImplementedException("The method isn't implented yet!");
		return std::unique_ptr<Matrix>();
	}

	std::unique_ptr<Matrix> Matrix::Subtr_Matrix()
	{
		throw NotImplementedException("The method isn't implented yet!");
		return std::unique_ptr<Matrix>();
	}

	void Matrix::Subtr_Eq_Scalar()
	{
		throw NotImplementedException("The method isn't implented yet!");
	}

	void Matrix::Subtr_Eq_Matrix()
	{
		throw NotImplementedException("The method isn't implented yet!");
	}

	std::unique_ptr<Matrix> Matrix::Mult_Scalar()
	{
		throw NotImplementedException("The method isn't implented yet!");
		return std::unique_ptr<Matrix>();
	}

	std::unique_ptr<Matrix> Matrix::Mult_Matrix()
	{
		throw NotImplementedException("The method isn't implented yet!");
		return std::unique_ptr<Matrix>();
	}

	void Matrix::Mult_Eq_Scalar()
	{
		throw NotImplementedException("The method isn't implented yet!");
	}

	void Matrix::Mult_Eq_Matrix()
	{
		throw NotImplementedException("The method isn't implented yet!");
	}

	std::unique_ptr<Matrix> Matrix::Div_Scalar()
	{
		throw NotImplementedException("The method isn't implented yet!");
		return std::unique_ptr<Matrix>();
	}

	std::unique_ptr<Matrix> Matrix::Div_Matrix()
	{
		throw NotImplementedException("The method isn't implented yet!");
		return std::unique_ptr<Matrix>();
	}

	void Matrix::Div_Eq_Scalar()
	{
		throw NotImplementedException("The method isn't implented yet!");
	}

	void Matrix::Div_Eq_Matrix()
	{
		throw NotImplementedException("The method isn't implented yet!");
	}

}