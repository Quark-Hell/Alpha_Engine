#include "Logger.h"

Core::Logger::Logger() {
	_logFile.open(GetLogFileName(), std::ios::app);
	_logFile.close();
}

Core::Logger::~Logger() {
	if (_logFile.is_open()) {
		_logFile.close();
	}
}

void Core::Logger::WriteToBuffer(const std::string& message) {
	_logBuffer.emplace_back(message);
}

void Core::Logger::SetDaysToDeleteLogFile(const int days) {
	_daysToDeleteLogFile = days;
}

std::string Core::Logger::GetCurrentDate() {
	const auto now = std::chrono::system_clock::now();
	const auto time = std::chrono::system_clock::to_time_t(now);
	std::ostringstream current_time;
	current_time << std::put_time(std::localtime(&time), "%Y-%m-%d");
	return current_time.str();
}

std::string Core::Logger::GetCurrentTime() {
	const auto now = std::chrono::system_clock::now();
	const auto time = std::chrono::system_clock::to_time_t(now);
	std::ostringstream current_time;
	current_time << std::put_time(std::localtime(&time), "%Y-%m-%d %H:%M:%S");
	return current_time.str();
}

std::string Core::Logger::GetLogFileName() {
	#ifdef WINDOWS
		return std::filesystem::current_path().string()+"\\Logs\\" + GetCurrentDate() + ".log";
	#else
		return std::filesystem::current_path().string() + "/Logs/" + GetCurrentDate() + ".log";
	#endif
}


void Core::Logger::WriteToFile(const std::string& message) {
	if (_logFile.is_open()) {
		_logFile << message << std::endl;
	}
}

Core::Logger* Core::Logger::GetInstance() {
	static Logger logger;
	return &logger;
}

const std::list<std::string>& Core::Logger::GetLogBuffer() {
  return _logBuffer;
}

void Core::Logger::CheckAndDeleteOldLogFile() {

}