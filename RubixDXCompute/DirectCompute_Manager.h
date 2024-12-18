#pragma once
#include <iostream>
#include <stdint.h>
#include <winerror.h>
#include <string>
#include <ctime>
#include <regex>
#include <cmath>
#include <fstream>
#include <vector>
#include <utility>
#include <typeinfo>
#include <sstream>
#include <random>
#include <thread>
#include <memory>
#include <initializer_list>
#include <map>
#include <filesystem>


namespace fs = std::filesystem;

namespace Rubix
{

	class DirectCompute_Manager
	{
		private:
			inline static std::map<std::string, std::string> _sources_rbxShader;
			inline static std::map<std::string, std::string> _sources_rbxAnalytics;
			inline static std::map<std::string, std::string> _sources_rbxInterim;
			inline static std::map<std::string, std::string> _sources_CustomShader;

		public:

			enum SHADER_SOURCE_TYPE : int
			{
				RUBIX_SHADER = 0,
				RUBIX_ANALYTICS = 1,
				RUBIX_INTERIM = 2,
				CUSTOM = 3
			};

			static HRESULT LoadSources(std::vector<fs::path> paths, std::vector<std::string> names, SHADER_SOURCE_TYPE srctype = SHADER_SOURCE_TYPE::RUBIX_SHADER);

			static std::string Get_Source_Rbx_Shader(std::string name);
			static std::string Get_Source_Rbx_Analytics(std::string name);
			static std::string Get_Source_Rbx_Interim(std::string name);
			static std::string Get_Source_Custom_Shader(std::string name);

			static std::string ChangeNumThreads(std::string shadername, int dim_x, int dim_y, int dim_z, SHADER_SOURCE_TYPE shadertype = SHADER_SOURCE_TYPE::RUBIX_SHADER);
	};
}