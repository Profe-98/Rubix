#pragma once

#include <string>
#include <fstream>
#include <iostream>
#include <Windows.h>
namespace Rubix
{
	enum LOG_LVL : int
	{
		INFO,// green
		WARNING, // yellow
		ERR, // orange
		FATAL_ERROR, // red
		EXCEPTION
	};

	static class LogHandler
	{
	private:
		inline static std::string _path = "";
		inline static bool _devmode = true;

		//we will  refactor this, but that's ok for now.
		static std::string PrepLogMSG(std::string& description, std::string& srcfile, std::string& class_, std::string& method, int line, LOG_LVL lvl = LOG_LVL::INFO);

		//Won't be called at Exceptions and therefore won't log Exceptions.
		static std::string PrepLogMSG(std::string& description, std::string& srcfile, int line, LOG_LVL lvl = LOG_LVL::INFO);

		static int setConsole_Color(LOG_LVL lvl);

	public:
		static void LogToFile(std::string& description, std::string srcfile, std::string& class_, std::string& method, int line, LOG_LVL lvl = LOG_LVL::INFO);

		static void LogToConsole(std::string& description, std::string srcfile, std::string& class_, std::string& method, int line, LOG_LVL lvl = LOG_LVL::INFO);

		static std::string EchoLog(std::string& description, std::string srcfile, std::string& class_, std::string& method, int line, LOG_LVL lvl = LOG_LVL::INFO);

		static void SetDevmodeTo(bool devmode);
		
		static bool GetDevmode();

		static void SetLogFilePath(std::string path);

		static std::string GetLogFilePath();
	};
}


