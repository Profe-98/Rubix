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
		static std::string PrepLogMSG(std::string& description, std::string& srcfile, std::string& class_, std::string& method, int line, LOG_LVL lvl = LOG_LVL::INFO)
		{
			std::string res;
			std::string descrpt = "Description: ";
			std::string src = "Source file: ";
			std::string clss = "Class: ";
			std::string mthd = "Method: ";
			std::string ln = "Line: ";
			switch (lvl)
			{
			case LOG_LVL::INFO:
				res = "INFO:\n" + descrpt + description + src + srcfile + clss + class_ + mthd + method + ln + std::to_string(line);
				return res;
			case LOG_LVL::WARNING:
				res = "WARNING:\n" + descrpt + description + src + srcfile + clss + class_ + mthd + method + ln + std::to_string(line);
				return res;
			case LOG_LVL::ERR:
				res = "ERROR:\n" + descrpt + description + src + srcfile + clss + class_ + mthd + method + ln + std::to_string(line);
				return res;
			case LOG_LVL::FATAL_ERROR:
				res = "FATAL ERROR:\n" + descrpt + description + src + srcfile + clss + class_ + mthd + method + ln + std::to_string(line);
				return res;
			case LOG_LVL::EXCEPTION:
				res = "EXCEPTION:\n" + descrpt + description + src + srcfile + clss + class_ + mthd + method + ln + std::to_string(line);
				return res;
			}
		}

		//Won't be calles at Exceptions and therefore won't log Exceptions.
		static std::string PrepLogMSG(std::string& description, std::string& srcfile, int line, LOG_LVL lvl = LOG_LVL::INFO)
		{
			std::string res;
			std::string descrpt = "Description: ";
			std::string src = "Source file: ";
			std::string ln = "Line: ";
			switch (lvl)
			{
			case LOG_LVL::INFO:
				res = "INFO:\n" + descrpt + description + src + srcfile + ln + std::to_string(line);
				return res;
			case LOG_LVL::WARNING:
				res = "WARNING:\n" + descrpt + description + src + srcfile + ln + std::to_string(line);
				return res;
			case LOG_LVL::ERR:
				res = "ERROR:\n" + descrpt + description + src + srcfile + ln + std::to_string(line);
				return res;
			case LOG_LVL::FATAL_ERROR:
				res = "FATAL ERROR:\n" + descrpt + description + src + srcfile + ln + std::to_string(line);
				return res;
			}
		}

		static int setConsole_Color(LOG_LVL lvl)
		{
			if (lvl == LOG_LVL::INFO)
				return 10;
			if (lvl == LOG_LVL::WARNING)
				return 14;
			if (lvl == LOG_LVL::ERR)
				return 22;
			if (lvl == LOG_LVL::FATAL_ERROR)
				return 20;
			if (lvl == LOG_LVL::EXCEPTION)
				return 4;
		}

	public:
		static void LogToFile(std::string& description, std::string srcfile, std::string& class_, std::string& method, int line, LOG_LVL lvl = LOG_LVL::INFO)
		{
			std::string msg;
			std::ofstream strm(_path);
			if (_devmode == false && lvl != LOG_LVL::EXCEPTION)
			{
				msg = PrepLogMSG(description, srcfile, line, lvl);
				strm << msg;
				return;
			}
			msg = PrepLogMSG(description, srcfile, class_, method, line, lvl);
			strm << msg;
		}

		static void LogToConsole(std::string& description, std::string srcfile, std::string& class_, std::string& method, int line, LOG_LVL lvl = LOG_LVL::INFO)
		{
			HANDLE console;
			console = GetStdHandle(STD_OUTPUT_HANDLE);
			int col = setConsole_Color(lvl);
			std::string msg;
			SetConsoleTextAttribute(console, col);
			if (_devmode == false && lvl != LOG_LVL::EXCEPTION)
			{
				msg = PrepLogMSG(description, srcfile, line, lvl);
				std::cout << msg;
				return;
			}
			msg = PrepLogMSG(description, srcfile, class_, method, line, lvl);
			std::cout << msg;
			return;
		}

		static std::string EchoLog(std::string& description, std::string srcfile, std::string& class_, std::string& method, int line, LOG_LVL lvl = LOG_LVL::INFO)
		{
			std::string msg;
			if (_devmode == false && lvl != LOG_LVL::EXCEPTION)
			{
				msg = PrepLogMSG(description, srcfile, line, lvl);
				return msg;

			}
			msg = PrepLogMSG(description, srcfile, class_, method, line, lvl);
			return msg;
		}

		static void SetDevmodeTo(bool devmode)
		{
			_devmode = devmode;
		}
		
		static bool GetDevmode()
		{
			return _devmode;
		}

		static void SetLogFilePath(std::string path)
		{
			_path = path;
		}

		static std::string GetLogFilePath()
		{
			return _path;
		}
	};
}


