#include "Matrix.h"

namespace Rubix
{
	Matrix::Matrix(std::string name, uint64_t rows, uint64_t cols, double elem, bool _resizable, bool _mutable) : _name(name)
	{
		std::pair<uint64_t, uint64_t> strides(0, 0);
		this->_storage = MatrixStorage(elem, strides, rows * cols, rows, cols);
	}

	Matrix::Matrix(std::string name, uint64_t rows, uint64_t cols, std::vector<double> elems, bool rowmajor, bool _resizable, bool _mutable) : _name{ name }
	{
		std::pair<uint64_t, uint64_t> strides;
		if (rowmajor)
			strides = { 1, cols };
		else
			strides = { rows, 1 };
		this->_storage = MatrixStorage(elems, strides, rows * cols, rows, cols);
	}

	Matrix::Matrix(std::string name, MatrixStorage storage, bool _resizable, bool _mutable) : _name(name), _storage(storage) { }

	Matrix::~Matrix() noexcept
	{
	}

	Matrix::Matrix(const Matrix& m) : _storage(m._storage), _name(m._name)	{}

	Matrix& Matrix::operator=(const Matrix& m)
	{
		if (this != &m)
		{
			_storage = m._storage;
			_name = m._name;
		}
		return *this;
	}

	Matrix::Matrix(Matrix&& m) noexcept : _storage(m._storage), _name(m._name) {}

	Matrix& Matrix::operator=(Matrix&& m) noexcept
	{
		if (this != &m)
		{
			_storage = m._storage;
			_name = m._name;
		}
		return *this;
	}

	bool Matrix::IsEmpty() const
	{
		return this->size_physical() == 0;
	}

	bool Matrix::IsPacked() const
	{
		return this->size_physical() == this->size_logical();
	}

	bool Matrix::IsPadded() const
	{
		return this->size_physical() > this->size_logical();
	}

	bool Matrix::IsCompressed() const
	{
		return this->size_physical() < this->size_logical();
	}

	bool Matrix::IsSquared() const
	{
		return this->Getrows() == this->Getcols();
	}

	bool Matrix::Is_mutable() const
	{
		return _storage.Is_mutable();
	}

	bool Matrix::Is_resizable() const
	{
		return _storage.Is_resizable();
	}

	void Matrix::make_mutable() const
	{
	}

	void Matrix::make_resizable() const
	{
	}

	std::string Matrix::Getname() const
	{
		return this->_name;
	}

	uint64_t Matrix::size_logical() const
	{
		return this->_storage.GetSize_logic();
	}

	uint64_t Matrix::size_logical_b() const
	{
		return this->_storage.GetSize_logic() * sizeof(double);
	}

	uint64_t Matrix::size_physical() const
	{
		return this->_storage.GetSize_phys();
	}

	uint64_t Matrix::size_physical_b() const
	{
		return this->_storage.GetSize_phys_b();
	}

	uint64_t Matrix::Getrows() const
	{
		return this->_storage.GetRows();
	}

	uint64_t Matrix::Getcols() const
	{
		return this->_storage.GetCols();
	}

	std::pair<uint64_t, uint64_t> Matrix::Getstrides() const
	{
		return this->_storage.GetStrides();
	}

	std::vector<double> Matrix::GetEntries() const
	{
		return this->_storage.GetBuffer();
	}

	std::string Matrix::GetDType() const
	{
		return "double"; // temporary
	}

	double Matrix::Trace() {
		//auto t0 = steady_clock::now();

		uint64_t r = this->Getrows();
		uint64_t c = this->Getcols();

		if (r < 2 || c < 2)
		{
			std::cerr << "\n\nERROR:\n	The matrix must atleast have 2 rows and 2 columns, so that the Trace operation can be performed!\n" << "Matrix(Name = " << this->_name << "; Rows = " << r << "; Columns = " << c << ")\n\n";
			return 0;
		}

		double res = 0;
		uint64_t iter = 0;
		uint64_t m_size = r * c;
		while (iter < m_size)
		{
			res += this->_storage.GetBuffer()[iter];
			iter += c + 1;
		}

		//auto t1 = steady_clock::now();

		//std::cout << "Time: " << nanoseconds{ t1 - t0 }.count() << "ns;\n\n";
		return res;
	}

	double Matrix::operator()(uint64_t m, uint64_t n)
	{
		if (m >= this->Getrows() || n >= this->Getcols())
			throw std::out_of_range("Matrix indices out of range!");

		return this->GetEntries()[m * this->Getcols() + n];

	}

	bool Matrix::operator==(Matrix& other)
	{
		if (this->Getrows() != other.Getrows() || this->Getcols() != other.Getcols() || this->size_physical_b() != other.size_physical_b() || this->Getstrides() != other.Getstrides())
			return false;

		uint64_t s = this->size_logical();
		for (uint64_t i = 0; i < s; ++i)
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

		for (uint64_t i = 0; i < this->size_logical(); ++i)
		{
			if (this->GetEntries()[i] != other.GetEntries()[i])
				return true;
		}

		return false;
	}

}