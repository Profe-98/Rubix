#include "DirectCompute_Manager.h"

namespace Rubix
{
	HRESULT DirectCompute_Manager::LoadSources(std::vector<fs::path> paths, std::vector<std::string> names, DirectCompute_Manager::SHADER_SOURCE_TYPE srctype)
	{
		int sourcecount = paths.size();

		if (sourcecount == 0 || names.size() == 0)
			return E_FAIL;

		for (int i = 0; i < sourcecount; ++i)
		{
			fs::file_status fstatus = fs::file_status{};
			fs::path path = paths[i];
			if (!(fs::status_known(fstatus) ? fs::exists(fstatus) : fs::exists(path)))
			{
				//TODO: logging
				return E_FAIL;
			}

			std::ifstream srcfile(path);

			std::ostringstream oss;
			if (srcfile.is_open())
			{
				std::string line;
				while (srcfile)
				{
					std::getline(srcfile, line);
					oss << line << "\n";
				}
			}

			std::string srccode = oss.str();

			srccode.erase(srccode.end()-2);
			switch (srctype)
			{
				case Rubix::DirectCompute_Manager::RUBIX_SHADER:
					_sources_rbxShader[names[i]] = srccode;
					break;
				case Rubix::DirectCompute_Manager::RUBIX_ANALYTICS:
					_sources_rbxAnalytics[names[i]] = srccode;
					break;
				case Rubix::DirectCompute_Manager::RUBIX_INTERIM:
					_sources_rbxInterim[names[i]] = srccode;
					break;
				case Rubix::DirectCompute_Manager::CUSTOM:
					_sources_CustomShader[names[i]] = srccode;
					break;
			}
		}
		return S_OK;
	}

	std::string DirectCompute_Manager::Get_Source_Rbx_Shader(std::string name)
	{
		return _sources_rbxShader[name];
	}
	std::string DirectCompute_Manager::Get_Source_Rbx_Analytics(std::string name)
	{
		return _sources_rbxAnalytics[name];
	}
	std::string DirectCompute_Manager::Get_Source_Rbx_Interim(std::string name)
	{
		return _sources_rbxInterim[name];
	}
	std::string DirectCompute_Manager::Get_Source_Custom_Shader(std::string name)
	{
		return _sources_CustomShader[name];
	}

	std::string DirectCompute_Manager::ChangeNumThreads(std::string shadername, int dim_x, int dim_y, int dim_z, SHADER_SOURCE_TYPE shadertype)
	{
		std::ostringstream newthreads_stream;
		newthreads_stream << "[numthreads(" << dim_x << ", " << dim_y << ", " << dim_z << ")]";

		std::string newthreads = newthreads_stream.str();
		std::string shader = "";

		switch (shadertype)
		{
		case Rubix::DirectCompute_Manager::RUBIX_SHADER:
			shader = _sources_rbxShader[shadername];
			break;
		case Rubix::DirectCompute_Manager::RUBIX_ANALYTICS:
			shader = _sources_rbxAnalytics[shadername];
			break;
		case Rubix::DirectCompute_Manager::RUBIX_INTERIM:
			shader = _sources_rbxInterim[shadername];
			break;
		case Rubix::DirectCompute_Manager::CUSTOM:
			shader = _sources_CustomShader[shadername];
			break;
		}

		if (shader == "")
			return "";

		std::regex exp(".numthreads.1, 1, 1..");

		shader = std::regex_replace(shader, exp, newthreads.c_str());

		return shader;
	}
}
