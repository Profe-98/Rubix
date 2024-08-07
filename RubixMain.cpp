#define __CL_ENABLE_EXCEPTIONS // must be defined before OpenCL header files are included
#include "RubixMain.h"
#include "CLManager.h"
#define CL_TARGET_OPENCL_VERSION 200
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