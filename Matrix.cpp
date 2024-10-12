#include "Matrix.h"

namespace Rubix
{
	Matrix::Matrix(std::string name, int rows, int cols, double elem) : _name(name)
	{
		std::vector<int> strides(2, 0);
		this->_storage = MatrixStorage(elem, strides, rows * cols, rows, cols);
	}

	Matrix::Matrix(std::string name, int rows, int cols, std::vector<double> elems, bool rowmajor) : _name{ name }
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

	Matrix::Matrix(const Matrix& m) : _storage(m._storage), _name(m._name), _mutable(m._mutable)
	{

	}

	Matrix& Matrix::operator=(const Matrix& m)
	{
		if (this != &m)
		{
			_storage = m._storage;
			_name = m._name;
			_mutable = m._mutable;
		}
		return *this;
	}

	Matrix::Matrix(Matrix&& m) noexcept : _storage(m._storage), _name(m._name), _mutable(m._mutable)
	{

	}

	Matrix& Matrix::operator=(Matrix&& m) noexcept
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

	double Matrix::Trace() {
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

	double Matrix::operator()(int m, int n)
	{
		if (m >= this->Getrows() || n >= this->Getcols())
			throw std::out_of_range("Matrix indices out of range!");

		return this->GetEntries()[m * this->Getcols() + n];

	}

	std::unique_ptr<Matrix> Matrix::operator+(Matrix& other)
	{
		return std::unique_ptr<Matrix>();
	}

	std::unique_ptr<Matrix> Matrix::operator+(double scalar)
	{
		return std::unique_ptr<Matrix>();
	}

	Matrix& Matrix::operator+=(Matrix& other)
	{
		// TODO: hier return-Anweisung eingeben
	}

	Matrix& Matrix::operator+=(double scalar)
	{
		// TODO: hier return-Anweisung eingeben
	}

	std::unique_ptr<Matrix> Matrix::operator-(Matrix& other)
	{
		return std::unique_ptr<Matrix>();
	}

	std::unique_ptr<Matrix> Matrix::operator-(double scalar)
	{
		return std::unique_ptr<Matrix>();
	}

	Matrix& Matrix::operator-=(Matrix& other)
	{
		// TODO: hier return-Anweisung eingeben
	}

	Matrix& Matrix::operator-=(double scalar)
	{
		// TODO: hier return-Anweisung eingeben
	}

	std::unique_ptr<Matrix> Matrix::operator*(Matrix& other)
	{
		return std::unique_ptr<Matrix>();
	}

	std::unique_ptr<Matrix> Matrix::operator*(double scalar)
	{
		return std::unique_ptr<Matrix>();
	}

	Matrix& Matrix::operator*=(Matrix& other)
	{
		// TODO: hier return-Anweisung eingeben
	}

	Matrix& Matrix::operator*=(double scalar)
	{
		// TODO: hier return-Anweisung eingeben
	}

	std::unique_ptr<Matrix> Matrix::operator/(Matrix& other)
	{
		return std::unique_ptr<Matrix>();
	}

	std::unique_ptr<Matrix> Matrix::operator/(double scalar)
	{
		return std::unique_ptr<Matrix>();
	}

	Matrix& Matrix::operator/=(Matrix& other)
	{
		// TODO: hier return-Anweisung eingeben
	}

	Matrix& Matrix::operator/=(double scalar)
	{
		// TODO: hier return-Anweisung eingeben
	}

	bool Matrix::operator==(Matrix& other)
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

	bool Matrix::operator!=(Matrix& other)
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

}