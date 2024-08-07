#pragma once
#define __CL_ENABLE_EXCEPTIONS // must be defined before OpenCL header files are included
//#include "CL/opencl.h"
#include <iostream>
#include <stdint.h>
#include <string>
#include <ctime>
#include <regex>
#include <cmath>
#include <fstream>
#include <vector>
#include <utility>
#include <typeinfo>
#include <random>
#include <memory>
#include <initializer_list>
#include <map>
#include "Matrix.h"
#include "Dtype.h"
namespace Rubix
{

	class CLManager
	{
		private:
		inline static std::string CL_Content;
		inline static std::map<std::string, std::string> opkrnls;
		inline static int errcode;
		inline static cl_context context;
		inline static cl_command_queue cmmd;
		inline static bool ctxt_available = false;
		inline static bool cmmd_available = false;

		public:
		inline static cl_platform_id pltfrm;
		inline static cl_device_id device;
		inline static std::map<std::string, std::shared_ptr<ComputeObject>> _compobj_map;
		inline static std::map<std::string, std::string> _krnl_descs;
		inline static std::map<std::string, std::string> opkrnls_custom; // l8r
		inline static const std::vector<std::vector<std::string>> cl_file_paths =
		{
			{ "D:/Projekte/Machine Learning/MLLibProjects/Rubix/Matrix_Add_Kernels.cl", "D:/Projekte/Machine Learning/MLLibProjects/Rubix/Matrix_Subtr_Kernels.cl", "D:/Projekte/Machine Learning/MLLibProjects/Rubix/Matrix_Mult_Kernels.cl", "D:/Projekte/Machine Learning/MLLibProjects/Rubix/Matrix_Div_Kernels.cl" },
			{}
		}; // Make it changeble in the future so that kernels can be added by devs before and at runtime + relative paths must work. we go with this for know, because it's sufficient for testing and we haven't
		// all default operations/kernels, yet.
		inline static const std::vector<std::vector<std::string>> Kernel_Names =
		{
			{ "matrix_add_scalar", "matrix_add_matrix", "matrix_subtr_scalar", "matrix_subtr_matrix", "matrix_mult_scalar", "matrix_mult_matrix", "matrix_div_scalar", "matrix_div_matrix"},
			{}
		}; // Make it changeble in the future so that kernels can be added by devs before and at runtime

		static void CreatePlatform(cl_uint num_entries = 1, cl_uint* num_platforms = nullptr);


		static void CreateDevice(cl_device_type type = CL_DEVICE_TYPE_GPU, cl_uint num_entries = 1, cl_uint* num_devices = nullptr);

		static void ReleaseDevice();

		static cl_context CreateContext(const cl_context_properties* props = NULL, cl_uint numdevices = 1);

		static void ReleaseContext();

		static cl_command_queue CreateCMDQueue(cl_command_queue_properties* properties = nullptr);

		static void ReleaseCMDQueue();

		static int ReadCLFILES();

		static int FetchKernels();

		static std::string GetKernelSrc(std::string& krnl_name);

		static std::string ListKernelswithDescr();

		static void AddComputeObjects();

		static void AddComputeObject();

		static void RemoveComputeObject(std::string name);

		static void AddCustomKernel(std::string name, std::string cl_code, std::string desc);

		static bool Context_Available();

		static bool Queue_Available();

		static cl_context GetContext();

		static cl_command_queue GetCMDQueue();
	};

	/*
	/// <summary>
	///
	/// </summary>
	/// <param name="start"></param>
	/// <param name="end"></param>
	/// <returns></returns>
	static T Gen_Rndm_in_Range(T start, T end)
	{
		std::random_device rd;
		std::mt19937 gen(rd());
		T res;
		if (typeid(T).name() == typeid(double).name())
		{
			std::uniform_real_distribution<double> distr(start, end);
			res = distr(gen);
			return res;
		}
		else
		{
			std::uniform_int_distribution<int> distr(start, end);
			res = distr(gen);
			return res;
		}
	}
*/
}