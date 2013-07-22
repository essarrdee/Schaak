#pragma once
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

// Singleton, logs messages for debugging
class Logger
{
public:
	//Logger(void);
	//~Logger(void);
	static void init(std::string filename)
	{
		write.open(filename);
		write << "Beginning log";
	}
	template<typename T>
	static void logError(const T& t) {log(t,  "\nERROR:   ");}

	template<typename T>
	static void logWarning(const T& t) {log(t,"\nWARNING: ");}

	template<typename T>
	static void logInfo(const T& t) {log(t,   "\nINFO:    ");}

	template<typename T>
	static void logAppend(const T& t) { log(t, ""); }
private:
	static std::ofstream write;
	template<typename T>
	static void log(const T& t, const std::string logType)
	{
		if(write.is_open())
		{
			write << logType << t;
			write.flush();
		}
	}
};

template<typename T>
static void LERR(const T& t)
{
	Logger::logError(t);
}

template<typename T>
static void LWARN(const T& t)
{
	Logger::logWarning(t);
}

template<typename T>
static void LINFO(const T& t)
{
	Logger::logInfo(t);
}

template<typename T>
static void LAPPEND(const T& t)
{
	Logger::logAppend(t);
}