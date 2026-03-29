#include "Logger.h"

namespace Core {
	Logger::Logger() {
		_logBuffer.reserve(100);
		_fileLogBuffer.reserve(100);

		_logFile.open(GetLogFileName(), std::ios::app);
		_logFile.close();
	}

	Logger::~Logger() {
		if (_logFile.is_open()) {
			_logFile.close();
		}
	}

	void Logger::WriteToBuffer(const std::string& message) {
		_logBuffer.emplace_back(message);
	}

	std::string Logger::GetCurrentDate() {
		const auto now = std::chrono::system_clock::now();
		const auto time = std::chrono::system_clock::to_time_t(now);
		std::ostringstream current_time;
		current_time << std::put_time(std::localtime(&time), "%Y-%m-%d");
		return current_time.str();
	}

	std::string Logger::GetCurrentTime() {
		const auto now = std::chrono::system_clock::now();
		const auto time = std::chrono::system_clock::to_time_t(now);
		std::ostringstream current_time;
		current_time << std::put_time(std::localtime(&time), "%Y-%m-%d %H:%M:%S");
		return current_time.str();
	}

	std::string Logger::GetLogFileName() {
#ifdef WINDOWS
		return std::filesystem::current_path().string() + "\\Logs\\" + GetCurrentDate() + ".log";
#else
		return std::filesystem::current_path().string() + "/Logs/" + GetCurrentDate() + ".log";
#endif
	}


	void Logger::WriteToFileBuffer(const std::string& message) {
		_fileLogBuffer.emplace_back(message);
	}

	Logger* Logger::GetInstance() {
		static Logger logger;
		return &logger;
	}

	const std::vector<std::string>& Logger::GetLogBuffer() {
		return _logBuffer;
	}
}