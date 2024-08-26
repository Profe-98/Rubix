#ifndef CL_TARGET_OPENCL_VERSION
#define CL_TARGET_OPENCL_VERSION 200
#endif // !CL_TARGET_OPENCL_VERSION // must be defined before OpenCL header files are included

#ifndef __CL_ENABLE_EXCEPTIONS
#define __CL_ENABLE_EXCEPTIONS
#endif // !__CL_ENABLE_EXCEPTIONS
#include "RubixMain.h"
#include "CLManager.h"
#include "CL/opencl.h"
#include "CL/cl.h"
namespace Rubix
{
	int RubixMain::Prepare_Library()
	{
		{
			int status_code;
			std::filesystem::path p = std::filesystem::current_path();
			std::filesystem::path rel_path = p.relative_path();
			CLManager::CreatePlatform();
			CLManager::CreateDevice();

			int errcode;
			char extensions[10000];
			errcode = clGetDeviceInfo(CLManager::device, CL_DEVICE_EXTENSIONS, sizeof(extensions), &extensions, nullptr);
			std::cout << "Errorcode: " << errcode << "\n";
			for (auto& v : extensions)
				std::cout << v;
			std::cout << "\n";

			std::size_t workgroupsizemax;
			std::size_t workitemsizesmax[3];
			cl_device_fp_config fpconfig;
			cl_uint vectorsupport;
			cl_uint maxcompunits;
			clGetDeviceInfo(CLManager::device, CL_DEVICE_MAX_WORK_GROUP_SIZE, sizeof(workgroupsizemax), &workgroupsizemax, nullptr);
			clGetDeviceInfo(CLManager::device, CL_DEVICE_MAX_WORK_ITEM_SIZES, sizeof(workitemsizesmax), workitemsizesmax, nullptr);
			clGetDeviceInfo(CLManager::device, CL_DEVICE_DOUBLE_FP_CONFIG, sizeof(fpconfig), &fpconfig, nullptr);
			clGetDeviceInfo(CLManager::device, CL_DEVICE_PREFERRED_VECTOR_WIDTH_DOUBLE, sizeof(vectorsupport), &vectorsupport, nullptr);
			clGetDeviceInfo(CLManager::device, CL_DEVICE_MAX_COMPUTE_UNITS, sizeof(maxcompunits), &maxcompunits, nullptr);
			std::cout << "CL_DEVICE_PREFERRED_VECTOR_WIDTH_DOUBLE: " << vectorsupport << "\nCL_DEVICE_DOUBLE_FP_CONFIG : " << fpconfig << "\nMAX_WORK_GROUP_SIZE: " << workgroupsizemax << "\nCL_DEVICE_MAX_COMPUTE_UNITS: " << maxcompunits << "\n";
			for(auto& v : workitemsizesmax)
				std::cout << "CL_DEVICE_MAX_WORK_ITEM_SIZE: " << v << "\n";
			CLManager::CreateContext();
			CLManager::CreateCMDQueue();
			status_code = CLManager::ReadCLFILES();
			if (status_code != RBX_SUCCESS)
			{
				return 0;
			}
			status_code = CLManager::FetchKernels();
			if (status_code != RBX_SUCCESS)
			{
				return 0;
			}
			CLManager::AddComputeObjects();
			return 1;
		}
	}
}