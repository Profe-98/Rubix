#include "Compute_Object.h"
#include "CLManager.h"
namespace Rubix
{
	ComputeObject::ComputeObject(std::string krnlname, cl_platform_id pltfrm, cl_device_id device, std::string krnlsrc) : _krnlname(krnlname), _platform(pltfrm), _device(device)
	{
		if (_platform == NULL || _context == NULL || _device == NULL)
			std::cerr << "ERR: Computation object init failed!";
		CreateContext();
		CreateQueue();
		CreateProgramWithSrc(1, krnlsrc);
		BuildProgram(1);
		CreateKernel(krnlname);
		//log failure
	//log creation 
	}

	ComputeObject::~ComputeObject()
	{
		this->ReleaseComputation_Object();
	}

	//err handling
	void ComputeObject::CreateContext(const cl_context_properties* props, cl_uint numdevices)
	{
		_context = CLManager::Context_Available() == true ? CLManager::GetContext() : CLManager::CreateContext(props, numdevices);
		if (_context == NULL)
		{
			std::cerr << "ERR: Ctxt" << "\n";
			return;
		}
	}

	/// <summary>
    /// NOT FINAL!!!
    /// </summary>
    /// <param name="properties"></param>
	void ComputeObject::CreateQueue(cl_command_queue_properties properties)
	{
		_command = CLManager::Queue_Available() == true ? CLManager::GetCMDQueue() : CLManager::CreateCMDQueue();
	}

	/// <summary>
	/// 
	/// </summary>
	/// <param name="ctxt"></param>
	/// <param name="count"></param>
	/// <param name="kernelsrc"></param>
	/// <param name="lengths"></param>
	/// <returns></returns>
	void ComputeObject::CreateProgramWithSrc(cl_uint count, std::string kernelsrc, const std::size_t* lengths)
	{
		// for now only w/ src
		const char* src = kernelsrc.c_str();
		cl_program progr = clCreateProgramWithSource(_context, count, &src, lengths, &_errcode);
		if (_errcode != CL_SUCCESS)
		{
			std::cerr << "ERR: creation of cl_program failed! (" << _errcode << ")\n";
			return;
		}
		_pro = progr;
	}

	void ComputeObject::BuildProgram(int num_devices, const char* options)
	{
		if (_pro == NULL || _device == NULL)
		{
			std::cout << "shit\n";
		}
		_errcode = clBuildProgram(_pro, num_devices, &_device, options, NULL, NULL);
		if (_errcode != CL_SUCCESS)
		{
			std::cerr << "ERR: Failed to build the program (" << _errcode << ")\n";
			return;
		}
	}

	void ComputeObject::CompileProgram(std::size_t* param_value_size_ret, bool getbinInfo)
	{
		_errcode = clCompileProgram(_pro, 1, &_device, NULL, NULL, NULL, NULL, NULL, NULL);
		if (_errcode != CL_SUCCESS)
		{
			std::cerr << "ERR: Program Compilation(" << _errcode << ")\n";
			return;
		}

		if (getbinInfo)
		{
			std::size_t lngth;
			unsigned char* binary;
			_errcode = clGetProgramInfo(_pro, CL_PROGRAM_BINARY_SIZES, sizeof(std::size_t) * 1, &lngth, param_value_size_ret);
			if (_errcode != CL_SUCCESS)
			{
				std::cerr << "ERR: Bin sizes(" << _errcode << ")\n";
			}
			binary = (unsigned char*)malloc(lngth);
			_errcode = clGetProgramInfo(_pro, CL_PROGRAM_BINARIES, sizeof(char*), &binary, param_value_size_ret);
			if (_errcode != CL_SUCCESS)
			{
				std::cerr << "ERR: BIN(" << _errcode << ")\n";

			}
			std::cout << "Program Binary:\n" << (const char*)binary << "\nBinary_size: " << lngth << "\n\n";
		}


	}

	void ComputeObject::LinkProgram()
	{
		_pro = clLinkProgram(_context, 1, &_device, NULL, 1, &_pro, NULL, NULL, &_errcode);
		if (_errcode != CL_SUCCESS)
		{
			std::cerr << "ERR: LINK(" << _errcode << ")\n";
			return;
		}
	}

	void ComputeObject::ReleaseProgram()
	{
		_errcode = clReleaseProgram(_pro);
		if (_errcode != CL_SUCCESS)
		{
			std::cerr << "ERR: could not release program(" << _errcode << ")\n";
			return;
		}
	}


	void ComputeObject::CreateKernel(std::string kernelname)
	{
		cl_kernel kernel = clCreateKernel(_pro, kernelname.c_str(), &_errcode);
		if (_errcode != CL_SUCCESS)
		{
			std::cerr << "ERR: creation of cl_kernel failed!";
			return;
		}
		_kernel = kernel;
	}

	void ComputeObject::ReleaseKernel()
	{
		_errcode = clReleaseKernel(_kernel);
		if (_errcode != CL_SUCCESS)
		{
			std::cerr << "ERR: could not release kernel(" << _errcode << ")\n";
			return;
		}
	}

	//Í hope this works
	/// <summary>
	/// 
	/// </summary>
	/// <param name="krnl_idx"></param>
	/// <param name="arg_idx"></param>
	/// <param name="val"></param>
	void ComputeObject::SetKernelArg(int arg_idx, double val)
	{
		_errcode = clSetKernelArg(_kernel, arg_idx, sizeof(val), &val);
		if (_errcode != CL_SUCCESS)
		{
			std::cerr << "ERR: setting the kernel arg failed!(" << _errcode << ")\n";
			ReleaseBuffers();
			ReleaseKernel();
			ReleaseProgram();
			return;
		}
	}

	void ComputeObject::SetKernelArg(int arg_idx, int val)
	{
		_errcode = clSetKernelArg(_kernel, arg_idx, sizeof(val), &val);
		if (_errcode != CL_SUCCESS)
		{
			std::cerr << "ERR: setting the kernel arg failed!(" << _errcode << ")\n";
			ReleaseBuffers();
			ReleaseKernel();
			ReleaseProgram();
			return;
		}
	}

	//not final
	void ComputeObject::SetKernelArgs()
	{
		int j = _buffers.size();
		for (int i = 0; i < j; ++i) //maybe j - 1
		{
			std::cout << "buffer(" << i << ")\n\n";
			_errcode = clSetKernelArg(_kernel, i, sizeof(cl_mem), &_buffers[i]);
			if (_errcode != CL_SUCCESS)
			{
				std::cerr << "ERR: setting the kernel args failed!(" << _errcode << ")\n";
				ReleaseBuffers();
				ReleaseKernel();
				ReleaseProgram();
				return;
			}
		}
	}

	/// <summary>
	/// Not Finished
	/// </summary>
	/// <param name="work_dim"></param>
	/// <param name="num_events_in_wait_list"></param>
	/// <param name="event_wait_list"></param>
	/// <param name="evt"></param>
	void ComputeObject::EnqueueNDRangeKernel(int work_dim, int num_events_in_wait_list, const cl_event* event_wait_list, cl_event* evt)
	{
		_errcode = clEnqueueNDRangeKernel(_command, _kernel, work_dim, NULL, &_global_work_size, NULL, num_events_in_wait_list, event_wait_list, evt);
		if (_errcode != CL_SUCCESS)
		{
			std::cerr << "ERR: Could not enqueue NDRangeKernel " << _errcode << "\n";
			return;
		}
	}

	void ComputeObject::CreateBufferMisc(cl_mem_flags flags, std::size_t size, void* hostptr)
	{
		cl_mem buffer = clCreateBuffer(_context, flags, size, hostptr, &_errcode);
		if (_errcode != CL_SUCCESS)
		{
			std::cerr << "ERR: CreateBufferMisc (code: " << _errcode << ")\n";
			return;
		}
		_buffers.emplace_back(buffer);
	}

	void ComputeObject::CreateBufferInput(std::size_t size, void* hostptr)
	{
		cl_mem buffer = clCreateBuffer(_context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, sizeof(double) * size, hostptr, &_errcode);
		if (_errcode != CL_SUCCESS)
		{
			std::cerr << "ERR: CreateBufferInput (code: " << _errcode << ")\n";
			return;
		}
		std::cout << _errcode << "\n";
		_buffers.emplace_back(buffer);
	}

	void ComputeObject::CreateBufferOutput(std::size_t size, void* hostptr)
	{
		cl_mem buffer = clCreateBuffer(_context, CL_MEM_WRITE_ONLY, sizeof(double) * size, hostptr, &_errcode);
		if (_errcode != CL_SUCCESS)
		{
			std::cerr << "ERR: CreateBufferOutput (code: " << _errcode << ")\n";
			return;
		}
		_buffers.emplace_back(buffer);
	}

	void ComputeObject::EnqueueReadBuffer(int idx_mem, cl_bool blocking_read, std::size_t offset, std::size_t size, void* ptr, int num_events_in_wait_list, const cl_event* event_wait_list, cl_event* evt)
	{
		_errcode = clEnqueueReadBuffer(_command, _buffers[idx_mem], blocking_read, offset, sizeof(double) * size, ptr, num_events_in_wait_list, event_wait_list, evt);
		if (_errcode != CL_SUCCESS)
		{
			std::cerr << "ERR: Couldn't read buffer! " << _errcode << "\n";
			return;
		}
	}

	void ComputeObject::ReleaseBuffers()
	{
		for (int i = 0; i < _buffers.size(); ++i)
		{
			_errcode = clReleaseMemObject(_buffers[i]);
			if (_errcode != CL_SUCCESS)
			{
				std::cerr << "ERR: could not release buffer(" << i << ")\n";
				return;
			}
			_buffers.pop_front();
		}		
		_buffers.pop_front();
	}


	void ComputeObject::SetWorkSize_global(int size)
	{
		_global_work_size = size;
	}

	int ComputeObject::GetWorkSize_global()
	{
		return _global_work_size;
	}

	void ComputeObject::CreatePipemem(cl_mem_flags flags, cl_uint packet_size, cl_uint max_packets, const cl_pipe_properties* properties)
	{
		cl_mem pipe = clCreatePipe(this->_context, flags, packet_size, max_packets, properties, &_errcode);
		if (_errcode != CL_SUCCESS)
		{
			std::cerr << "ERR: Failed to create memory pipe! " << _errcode << "\n";
			return;
		}
		_pipes.emplace_back(pipe);
		return;
	}


	void ComputeObject::Flush()
	{
		_errcode = clFlush(_command);
		if (_errcode != CL_SUCCESS)
		{
			std::cerr << "ERR: Failed to flush command! " << _errcode << "\n";
			return;
		}
	}

	void ComputeObject::Finish()
	{
		_errcode = clFinish(_command);
		if (_errcode != CL_SUCCESS)
		{
			std::cerr << "ERR: Failed to finish command! " << _errcode << "\n";
			return;
		}
	}

	void ComputeObject::ReleaseComputation_Object()
	{
		ReleaseBuffers();
		ReleaseKernel();
		ReleaseProgram();
		_platform = NULL;
	}

	int ComputeObject::GetId()
	{
		return this->_id;
	}
	/*
	int GetAmountofExisting(CL_OBJ_TYPE_ type = CL_OBJ_TYPE_::DEVICE)
	{
		switch (type)
		{
		case Rubix::DEVICE:
			return _devices.size();
		case Rubix::CONTEXT:
			return _contexts.size();
		case Rubix::PROGRAM:
			return _pros.size();
		case Rubix::KERNEL:
			return _kernels.size();
		case Rubix::COMMAND:
			return _commands.size();
		case Rubix::PIPE:
			return _pipes.size();
		case Rubix::MEMORY:
			break; // we still have to implement cl_mem properly...
		}
	}*/
	//this class'll be used to manage the opencl kernels, device and programs,
	// so that 1 Computation object is able to contain and manage multiple kernels, programs and/or devices and make them perform calculations as wished by the user 
}