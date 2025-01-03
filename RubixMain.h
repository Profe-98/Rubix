#pragma once
#include <winerror.h>
#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <filesystem>
#include <memory>

#include "RubixDefinitions.h"



namespace Rubix
{
	using namespace Definitions;
	class RubixMain
	{
		public:	

			static HRESULT Prepare_Library();
	};
}

