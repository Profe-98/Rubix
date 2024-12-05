#include "Exceptions.h"

namespace Rubix
{
	NotImplementedException::NotImplementedException(const char* msg)
	{
		this->_msg = msg;
	}

	const char* NotImplementedException::what()
	{
		return this->_msg; 
	}

}