#pragma once
#include <string>
//class ILogger
//{
//public:
//	virtual ~ILogger() {};
//	virtual void log(std::string logMessage) = 0;
//};
//
//class stdOutLogger : public ILogger
//{
//public:
//	stdOutLogger();
//	void log(std::string logMessage);
//};
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