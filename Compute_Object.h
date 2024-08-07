#pragma once
#define __CL_ENABLE_EXCEPTIONS // must be defined before OpenCL header files are included
#define CL_TARGET_OPENCL_VERSION 200
#include "CL/opencl.h"
#include "CL/cl.h"
#include <vector>
#include <memory>
#include <string>
#include <iostream>
#include <deque>
#include <thread>
namespace Rubix
{
	//SIMD anschauen
	//1300 lines of code alone in rubix 
	/// <summary>
	/// A Class that creates Objects to manage the opencl platform, context, device, program(s), kernels and therefore also the computations, commandqueues, memory buffers, and memory pipes on the given device. Multiple matrices/tensors can share one Computation_Object
	/// </summary>
	class ComputeObject
	{
		private:
		int _id;
		std::string _krnlname;
		cl_int _errcode = 1;
		cl_platform_id _platform;
		cl_context _context;
		cl_device_id _device;
		cl_program _pro;
		cl_kernel _kernel;
		cl_command_queue _command;
		std::deque<cl_mem> _buffers;
		std::deque<cl_mem> _pipes;
		//_global_work_offset;
		std::size_t _global_work_size = 0;
		//_local_work_size;
		
		//addevice();
		//those methods are not the last methods to be implemented here, but are a good fundament to build up on. There's more to come! Dont forget INIT
		public:
		ComputeObject(std::string krnlname, cl_platform_id pltfrm, cl_device_id device, std::string krnlsrc);

		~ComputeObject();

		void CreateContext(const cl_context_properties* props = NULL, cl_uint numdevices = 1);

		/// <summary>
		/// 
		/// </summary>
		/// <param name="count"></param>
		/// <param name="ctxt"></param>
		/// <param name="kernelsrc"></param>
		/// <param name="lengths"></param>
		/// <returns></returns>
		void CreateProgramWithSrc(cl_uint count, std::string kernelsrc, const std::size_t* lengths = NULL);

		void BuildProgram(int num_devices, const char* options = NULL);

		void CompileProgram(std::size_t* param_value_size_ret = nullptr, bool getbinInfo = false);

		void LinkProgram();

		void ReleaseProgram();


		void CreateKernel(std::string kernelname);

		void ReleaseKernel();

		//Í hope this works
		/// <summary>
		/// 
		/// </summary>
		/// <param name="krnl_idx"></param>
		/// <param name="arg_idx"></param>
		/// <param name="val"></param>
		void SetKernelArg(int arg_idx, double val);

		//Í hope this works
		/// <summary>
		/// 
		/// </summary>
		/// <param name="krnl_idx"></param>
		/// <param name="arg_idx"></param>
		/// <param name="val"></param>
		void SetKernelArg(int arg_idx, int val);

		//not final
		void SetKernelArgs();

		/// <summary>
		/// Not Finished
		/// </summary>
		/// <param name="work_dim"></param>
		/// <param name="num_events_in_wait_list"></param>
		/// <param name="event_wait_list"></param>
		/// <param name="evt"></param>
		void EnqueueNDRangeKernel(int work_dim = 1, int num_events_in_wait_list = 0, const cl_event* event_wait_list = nullptr, cl_event* evt = nullptr);


		void CreateQueue(cl_command_queue_properties properties = 0);
		
		void CreateBufferMisc(cl_mem_flags flags, std::size_t size, void* hostptr = NULL);
				
		void CreateBufferInput(std::size_t size, void* hostptr = NULL);

		void CreateBufferOutput(std::size_t size, void* hostptr = NULL);
		
		void EnqueueReadBuffer(int idx_mem, cl_bool blocking_read, std::size_t offset, std::size_t size, void* ptr, int num_events_in_wait_list = 0, const cl_event* event_wait_list = nullptr, cl_event* evt = nullptr);

		void ReleaseBuffers();


		void SetWorkSize_global(int size);

		int GetWorkSize_global();

		void CreatePipemem(cl_mem_flags flags, cl_uint packet_size, cl_uint max_packets, const cl_pipe_properties* properties);


		void Flush();

		void Finish();

		void ReleaseComputation_Object();

		int GetId();
	};
}