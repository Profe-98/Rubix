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
		//_global_work_offset;
		//_local_work_size;
		

		public:
		#define RUBIX_COMPUTE_OBJECT_MAXDIMS 3

	};
}