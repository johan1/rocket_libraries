#include "Log.h"

#ifdef ANDROID
#include <android/log.h>
#else
#include <iostream>
#endif

using namespace boost::chrono;

namespace rocket {

Logger& Logger::getLogger() {
	static Logger instance;
	return instance;
}

#ifndef ANDROID
Logger::Logger() : messagePool{1}, defaultTag{"Rocket2d"} {}
#else
Logger::Logger() : defaultTag{"Rocket2d"} {}
#endif

void Logger::log(LogLevel const& level, std::string const& tag, std::string const& msg) {
	LoggerTask loggerTask(level, tag, msg);
#ifndef ANDROID
	messagePool.submit(loggerTask);
#else
	loggerTask();
#endif
}

void Logger::log(LogLevel const& level, std::string const& msg) {
	log(level, defaultTag, msg);
	if (level == LogLevel::ERROR) {
		flush();
	}
}

void Logger::flush() {
#ifndef ANDROID
	auto result = messagePool.submit([](){}); // Hack, empty lambda, we're only interested in waiting for the last message to be processed :)
	result.wait();
#endif
	// On android we're not able to handle the queued log message.
}

#ifdef ANDROID
Logger::LoggerTask::LoggerTask(LogLevel const& level, std::string const& tag,
		std::string const& message) : level(level), tag(tag), message(message) {}
#else
Logger::LoggerTask::LoggerTask(LogLevel const& level, std::string const& tag,
		std::string const& message) : level(level), tag(tag), message(message), timePoint(system_clock::now()) {}
#endif

void Logger::LoggerTask::operator()() {
#ifndef ANDROID
	milliseconds ms = duration_cast<milliseconds>(timePoint.time_since_epoch());
	seconds s = duration_cast<seconds>(ms);

	std::time_t t = s.count();
	static char timeString[40];

	std::strftime(timeString, 200, "%H:%M:%S", std::localtime(&t));
	auto msString = (boost::format("%03d") % (ms.count() % 1000)).str();

	std::cout << timeString << "." << msString << " " << tag << " ";
	if (level == LogLevel::DEBUG) {
		std::cout << "DEBUG ";
	} else if (level == LogLevel::WARNING) {
		std::cout << "WARNING ";
	} else if (level == LogLevel::ERROR) {
		std::cout << "ERROR ";
	}

	std::cout << message << std::endl;
#else
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wformat-security"
	if (level == LogLevel::DEBUG) {
		__android_log_print(ANDROID_LOG_DEBUG, tag.c_str(), message.c_str());
	} else if (level == LogLevel::WARNING) {
		__android_log_print(ANDROID_LOG_WARN, tag.c_str(), message.c_str());
	} else if (level == LogLevel::ERROR) {
		__android_log_print(ANDROID_LOG_ERROR, tag.c_str(), message.c_str());
	}
#pragma clang diagnostic pop
#endif
}

}
