#pragma once
#include <string>

class Logger
{
public:
	static Logger& instance();
	virtual void log(std::string logMessage) = 0;
protected:
	Logger() {};
};

class stdOutLogger : public Logger
{
public:
	stdOutLogger();
	void log(std::string logMessage);
};

#define LOG(message) \
	Logger::instance().log(message)