#include "stdafx.h"
#include "Logger.h"
#include <iostream>

stdOutLogger::stdOutLogger()
{
}

void stdOutLogger::log(std::string logMessage)
{
	std::cout << logMessage << std::endl;
}

Logger & Logger::instance()
{
	//change logger implementation if needed
	static Logger* instance_ = new stdOutLogger;
	return *instance_;
}
