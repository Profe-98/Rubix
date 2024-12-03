#pragma once
#include <cstdio>
#include <iostream>
#include <exception>

namespace Rubix
{
	class NotImplementedException : public std::exception
	{
		private:
			const char* _msg;
		public:
			NotImplementedException(const char* msg);
			const char* what();
	};
}