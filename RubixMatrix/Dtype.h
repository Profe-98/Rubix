#pragma once
#include <typeinfo>
#include <string>
#include <memory>
#include <iostream>
#include <unordered_map>

namespace Rubix
{	
	/// <summary>
	/// 
	/// </summary>
	/// <typeparam name="T"></typeparam>
	template<typename T>
	class Dtype
	{
		std::string name_;
		uint64_t physsize_; // logical size in byte of a single value of type T / Dtype.

		public:
		__declspec(deprecated("Not Implemented"))
		Dtype()
		{
			this->name_ = typeid(T).name();
			physsize_ = sizeof(T);
		}

		__declspec(deprecated("Not Implemented"))
		std::string Name() { return this->name_;  }

		__declspec(deprecated("Not Implemented"))
		uint16_t Physicalsize() { return this->physsize_; }
	};
}