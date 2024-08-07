#include "CLManager.h"
#include "CLManager.h"
#define __CL_ENABLE_EXCEPTIONS // must be defined before OpenCL header files are included
#define CL_TARGET_OPENCL_VERSION 200
#include "CL/opencl.h"
#include "CL/cl.h"
#include "CLManager.h"
#include <vector>
#include <memory>
#include <string>
#include <iostream>
#include <deque>
#include <thread>
#include <stdint.h>
#include <ctime>
#include <regex>
#include <cmath>
#include <fstream>
#include <typeinfo>
#include <random>
#include <initializer_list>
#include <map>
#include "Matrix.h"
#include "Dtype.h"
#include "Compute_Object.h"
namespace Rubix
{
	//Write Compute_Object_Handler class to handle computeobjects from init - over lifetime - to destr. 
	void CLManager::CreatePlatform(cl_uint num_entries, cl_uint* num_platforms)
	{
		cl_platform_id platform;
		errcode = clGetPlatformIDs(num_entries, &platform, num_platforms);
		if (errcode != CL_SUCCESS)
		{
			//log
			std::cerr << "ERR: creation of cl_platform failed";
			return;
		}
		pltfrm = platform;
	}

	void CLManager::CreateDevice(cl_device_type type, cl_uint num_entries, cl_uint* num_devices)
	{
		cl_device_id dvc;
		errcode = clGetDeviceIDs(pltfrm, type, 1, &dvc, num_devices);
		if (errcode != CL_SUCCESS)
		{
			//log
			std::cerr << "ERR: creation of device failed!";
			return;
		}
		device = dvc;
	}

	void CLManager::ReleaseDevice()
	{
		errcode = clReleaseDevice(device);
		if (errcode != CL_SUCCESS)
		{
			std::cerr << "ERR: release of device failed!";
		}
	}

	cl_context CLManager::CreateContext(const cl_context_properties* props, cl_uint numdevices)
	{
		cl_context ctxt = clCreateContext(props, numdevices, &device, NULL, NULL, &errcode);
		if (errcode != CL_SUCCESS)
		{
			std::cerr << "ERR: creation of cl_context failed! (" << errcode << ")\n";
		}
		context = ctxt;
		ctxt_available = true;
		return ctxt;
	}

	void CLManager::ReleaseContext()
	{
		errcode = clReleaseContext(context);
		if (errcode != CL_SUCCESS)
		{
			std::cerr << "ERR: release of context failed!";
		}
	}

	cl_command_queue CLManager::CreateCMDQueue(cl_command_queue_properties* properties)
	{
		cl_command_queue queue = clCreateCommandQueueWithProperties(context, device, properties, &errcode);
		if (errcode != CL_SUCCESS)
		{
			std::cerr << "ERR: Commandqueue creation Failed!(" << errcode << ")\n";
			return NULL;
		}
		cmmd = queue;
		cmmd_available = true;
		return queue;
	}

	void CLManager::ReleaseCMDQueue()
	{
		errcode = clReleaseCommandQueue(cmmd);
		if (errcode != CL_SUCCESS)
		{
			std::cerr << "ERR: release of command queue failed!";
		}
	}


	int CLManager::ReadCLFILES()
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

	int CLManager::FetchKernels()
	{
		std::regex rgx("\n\n//==\n");
		std::vector<std::string> v_krnls;
		std::sregex_token_iterator iter(CL_Content.begin(),
			CL_Content.end(),
			rgx,
			-1);
		std::sregex_token_iterator end;

		for (; iter != end; ++iter)
			v_krnls.emplace_back(*iter); //std::cout << i << ":\n" << *iter << "\n";

		int vs = v_krnls.size();
		int ks = Kernel_Names[0].size();
		if (vs != ks)
		{
			//create log class
			std::cerr << "ERR: Fetchkernels(" << "vs = " << vs << "; ks = " << ks << ")\n";
			return 0;
		}
		for (int i = 0; i < ks; ++i)
			opkrnls[Kernel_Names[0][i]] = v_krnls[i];
		return 1;
	}

	std::string CLManager::GetKernelSrc(std::string& krnl_name)
	{
		return opkrnls[krnl_name];
	}

	std::string CLManager::ListKernelswithDescr()
	{
		std::ostringstream oss;
		int x = 1;
		for (int i = 0; i < x; ++i)
		{
			int y = Kernel_Names[i].size();
			for (int j = 0; j < y; ++i)
			{
				oss << "Name: " << Kernel_Names[i][j] << "\n\nDescription:\n" << _krnl_descs[Kernel_Names[i][j]] << "\n\n";
			}
		}
		return oss.str();
	}


	/// <summary>
	/// Only Adds predefined ComputeObjects(For Custom ComputeObjects, made by you, use AddComputeObjects) 
	/// </summary>
	void CLManager::AddComputeObjects()
	{
		int s_kn = Kernel_Names[0].size();
		std::cout << "Initialising ComputeObjects...\n";
		std::cout << "Size = " << s_kn << "\n";
		for (int i = 0; i < s_kn; ++i)
		{
			std::shared_ptr<ComputeObject> obj = std::make_shared<ComputeObject>(Kernel_Names[0][i], pltfrm, device, opkrnls[Kernel_Names[0][i]]);
			std::cout << i + 1 << ": ComputeObject Initialised!\n";
			_compobj_map[Kernel_Names[0][i]] = obj;
		}
	}

	void CLManager::AddComputeObject()
	{

	}

	void CLManager::RemoveComputeObject(std::string name)
	{
		_compobj_map.erase(name);
	}

	void CLManager::AddCustomKernel(std::string name, std::string cl_code, std::string desc)
	{

	}

	bool CLManager::Context_Available()
	{
		return ctxt_available;
	}

	bool CLManager::Queue_Available()
	{
		return cmmd_available;
	}

	cl_context CLManager::GetContext()
	{
		return context;
	}
	cl_command_queue CLManager::GetCMDQueue()
	{
		return cmmd;
	}
}
