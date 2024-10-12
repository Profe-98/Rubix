#include "LogHandler.h"

namespace Rubix
{
	std::string LogHandler::PrepLogMSG(std::string& description, std::string& srcfile, std::string& class_, std::string& method, int line, LOG_LVL lvl)
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

	std::string LogHandler::PrepLogMSG(std::string& description, std::string& srcfile, int line, LOG_LVL lvl)
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

	int LogHandler::setConsole_Color(LOG_LVL lvl)
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

	void LogHandler::LogToFile(std::string& description, std::string srcfile, std::string& class_, std::string& method, int line, LOG_LVL lvl)
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

	void LogHandler::LogToConsole(std::string& description, std::string srcfile, std::string& class_, std::string& method, int line, LOG_LVL lvl)
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

	std::string LogHandler::EchoLog(std::string& description, std::string srcfile, std::string& class_, std::string& method, int line, LOG_LVL lvl)
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

	void LogHandler::SetDevmodeTo(bool devmode)
	{
		_devmode = devmode;
	}

	bool LogHandler::GetDevmode()
	{
		return _devmode;
	}

	void LogHandler::SetLogFilePath(std::string path)
	{
		_path = path;
	}

	std::string LogHandler::GetLogFilePath()
	{
		return _path;
	}


}