#ifndef _LOG_H_
#define _LOG_H_

#ifndef ANDROID
#include "ThreadPool.h"
#endif

#include <string>
#include <boost/chrono.hpp>
#include <boost/format.hpp>

#include <sstream>

namespace rocket {
	enum class LogLevel {
		DEBUG,
		WARNING,
		ERROR
	};

	class Logger {
	public:
		~Logger() = default;
		void log(LogLevel const& level, std::string const& tag, std::string const& message);
		void log(LogLevel const& level, std::string const& message);

		void flush();
		void setDefaultTag(std::string const& defaultTag);

		static Logger& getLogger();
	private:
		class LoggerTask {
		public:
			LoggerTask(LogLevel const& level, std::string const& tag, std::string const& message);
			void operator()();
		private:
			LogLevel level;
			std::string tag;
			std::string message;
#ifndef ANDROID
			boost::chrono::system_clock::time_point timePoint;
#endif
		};

		Logger();
		Logger(Logger const& logger) = delete;
		Logger& operator=(Logger const& logger) = delete;

#ifndef ANDROID
		ThreadPool messagePool;
#endif
		std::string defaultTag;
	};

	inline void Logger::setDefaultTag(std::string const& defaultTag) {
		this->defaultTag = defaultTag;
	}

	inline void logd(std::string const& tag, std::string const& message) {
		Logger::getLogger().log(LogLevel::DEBUG, tag, message);
	}

	inline void logw(std::string const& tag, std::string const& message) {
		Logger::getLogger().log(LogLevel::WARNING, tag, message);
	}

	inline void loge(std::string const& tag, std::string const& message) {
		Logger::getLogger().log(LogLevel::ERROR, tag, message);
	}

	inline void logd(std::string const& message) {
		Logger::getLogger().log(LogLevel::DEBUG, message);
	}

	inline void logw(std::string const& message) {
		Logger::getLogger().log(LogLevel::WARNING, message);
	}

	inline void loge(std::string const& message) {
		Logger::getLogger().log(LogLevel::ERROR, message);
	}
}

// And finally some horrible horrible macros...
#ifndef LOG_DISABLED

inline std::string log_file_info(std::string file, int line) {
	std::string::size_type offset = 0;

	std::string::size_type new_offset = 0;
	while ((new_offset = file.find("/", offset)) != std::string::npos) {
		offset = new_offset + 1;
	}

	std::ostringstream oss;
	oss << file.substr(offset, file.length() - offset) << ":" << line << " | ";

	return oss.str();
}

	#define LOGD(MESSAGE) { std::ostringstream oss; oss << log_file_info(__FILE__, __LINE__) << MESSAGE; rocket::logd(oss.str()); }
	#define LOGW(MESSAGE) { std::ostringstream oss; oss << log_file_info(__FILE__, __LINE__) << MESSAGE; rocket::logw(oss.str()); }
	#define LOGE(MESSAGE) { std::ostringstream oss; oss << log_file_info(__FILE__, __LINE__) << MESSAGE; rocket::loge(oss.str()); }
	#define LOGDT(TAG, MESSAGE) { std::ostringstream oss; oss << log_file_info(__FILE__, __LINE__) << MESSAGE; rocket::logd((TAG), oss.str()); }
	#define LOGWT(TAG, MESSAGE) { std::ostringstream oss; oss << log_file_info(__FILE__, __LINE__) << MESSAGE; rocket::logw((TAG), oss.str()); }
	#define LOGET(TAG, MESSAGE) { std::ostringstream oss; oss << log_file_info(__FILE__, __LINE__) << MESSAGE; rocket::loge((TAG), oss.str()); }

#else
	#define LOGD(MESSAGE)
	#define LOGW(MESSAGE)
	#define LOGE(MESSAGE)
	#define LOGDT(TAG, MESSAGE)
	#define LOGWT(TAG, MESSAGE)
	#define LOGET(TAG, MESSAGE)
#endif // Horrible horrible macros

#endif // _LOGGER_H_
