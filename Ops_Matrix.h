#pragma once
#include <stdint.h>
#include <string>
#include <ctime>
#include <regex>
#include <cmath>
#include <fstream>
#include <vector>
#include <typeinfo>
#include <random>
#include <memory>
#include <initializer_list>
#include <map>
#include "Matrix.h"
#include "Dtype.h"
//#include "Rubix_Main.h" 
namespace Rubix
{
	/// <summary>
	/// This static class is used to store the OpenCL kernels for every corresponding Matrix Operation
	/// </summary>
	class Ops_Matrix
	{
	private:
		//I should consider the creation of a static helper class for the whole project...   
		//enthropy() for random device
		inline static std::string CL_Content;
		inline static std::map<std::string, std::string> opkrnls;
	public:
		inline static const std::vector<std::vector<std::string>> cl_file_paths =
		{
			{ "D:/Projekte/Machine Learning/MLLibProjects/Rubix/Matrix_Add_Kernels.cl", "D:/Projekte/Machine Learning/MLLibProjects/Rubix/Matrix_Subtr_Kernels.cl", "D:/Projekte/Machine Learning/MLLibProjects/Rubix/Matrix_Mult_Kernels.cl", "D:/Projekte/Machine Learning/MLLibProjects/Rubix/Matrix_Div_Kernels.cl" },
			{}
		}; // Make it changeble in the future so that kernels can be added by devs before and at runtime + relative paths must work. we go with this for know, because it's sufficient for testing and we haven't
		// all default operations/kernels, yet.
		inline static const std::vector<std::vector<std::string>> Kernel_Names =
		{
			{ "matrix_add_scalar", "matrix_add_matrix", "vadd", "matrix_subtr_scalar", "matrix_subtr_matrix", "matrix_mult_scalar", "matrix_mult_matrix", "matrix_div_scalar", "matrix_div_matrix"},
			{}
		}; // Make it changeble in the future so that kernels can be added by devs before and at runtime
		static int ReadCLFILES()
		{
			//std::vector<std::string
			int s = cl_file_paths[0].size();
			for (int i = 0; i < s; ++i)
			{
				std::string rawdata;
				std::ifstream file(cl_file_paths[0][i]);
				if (file.is_open())
				{
					std::string line;
					while (std::getline(file, line))
					{
						rawdata.append(line + "\n");
					}

				}
				else
				{
					std::cout << "ERR: Unable to open the file(" << cl_file_paths[0][i] << ")\n";
					return 0;
				}
				CL_Content += rawdata;
				file.close();
			}
			return 1;

		}

		//maybe return std::map<std::string, const char*>?
		static int FetchKernels()
		{
			std::regex rgx("\n\n\n");
			std::vector<std::string> v_krnls;
			std::sregex_token_iterator iter(CL_Content.begin(), 
				CL_Content.end(),
				rgx,
				-1);
			std::sregex_token_iterator end;
			for (; iter != end; ++iter)
				v_krnls.emplace_back(*iter);
			int vs = v_krnls.size();
			int ks = Kernel_Names[0].size();
			if (vs != ks)
			{
				//create log class
				std::cerr << "ERR: Fetchkernels ";
				return 0;
			}
			for (int i = 0; i < ks; ++i)
				opkrnls[Kernel_Names[0][i]] = v_krnls[i];
			return 1;
		}

		static std::string GetKernelSrc(std::string& krnl_name)
		{
			return opkrnls[krnl_name];
		}

		/*STILL IMPORTANT
		//-------Matrix Operations-------

		/// <summary>
		///
		/// </summary>
		/// <param name="name"></param>
		/// <param name="rowsandcols"></param>
		/// <returns></returns>
		static std::unique_ptr<Matrix<T>> Create_Identity_Matrix(const std::string& name, int rowsandcols = 2)
		{
			if (rowsandcols < 2)
				throw std::invalid_argument("Only quadratic matrices can be identity matrices!"); // maybe use cerr instead...

			std::vector<T> vc_res;
			int logical_size = rowsandcols * rowsandcols;
			int last_one = 0;
			for (int i = 0; i < logical_size; ++i)
			{

				i == last_one + rowsandcols + 1 || i == 0 ? vc_res.emplace_back(1.0) : vc_res.emplace_back(0.0);
				i == last_one + rowsandcols + 1 ? last_one = i : last_one = last_one;
			}

			std::unique_ptr<Matrix<T>> res = std::make_unique<Matrix<T>>(name, rowsandcols, rowsandcols, vc_res, rowsandcols);
			return res;
		}

		/// <summary>
		///
		/// </summary>
		/// <param name="name"></param>
		/// <param name="rows"></param>
		/// <param name="cols"></param>
		/// <param name="strides"></param>
		/// <param name="start"></param>
		/// <param name="end"></param>
		/// <param name="pseudo"></param>
		/// <param name="usetime"></param>
		/// <returns></returns>
		static std::unique_ptr<Matrix<T>> Create_Rndm_Matrix(const std::string& name, int rows, int cols, int strides, T start, T end)
		{

			if (rows <= 1 && cols <= 1)
			{
				std::cerr << "It isn't necessary, or useful, to create a 1 x 1 matrix, because this can be represented as scalar value.";
				return nullptr;
			}

			std::vector<T> vc_res;
			int logical_size = rows * cols;

			for (int i = 0; i < logical_size; ++i)
			{
				vc_res.emplace_back((T)Gen_Rndm_in_Range(start, end));
			}
			std::unique_ptr<Matrix<T>> res = std::make_unique<Matrix<T>>(name, rows, cols, vc_res, strides);
			return res;
		}

		/// <summary>
		///
		/// </summary>
		/// <param name="name"></param>
		/// <param name="rows"></param>
		/// <param name="cols"></param>
		/// <returns></returns>
		static std::unique_ptr<Matrix<T>> Create_Zero_Matrix(const std::string& name, int rows, int cols)
		{
			if (rows <= 1 && cols <= 1)
			{
				std::cerr << "Err message";
			}

			std::vector<T> vc_res = { 0.0 };

			std::unique_ptr<Matrix<T>> res = std::make_unique<Matrix<T>>(name, rows, cols, vc_res, 0);
			return res;
		}*/
	};


}