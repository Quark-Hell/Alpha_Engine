#include "Logger.h"

Core::Logger::Logger::Logger() {
	logFile.open(getLogFileName(), std::ios::app);
	logFile.close();
}

Core::Logger::Logger::~Logger() {
	if (logFile.is_open()) {
		logFile.close();
	}
}

void Core::Logger::Logger::writeToBuffer(const std::string& message) {
	logBuffer.emplace_back(message);
}

void Core::Logger::Logger::SetDaysToDeleteLogFile(int days) {
	daysToDeleteLogFile = days;
}

std::string Core::Logger::Logger::getCurrentDate() {
	auto now = std::chrono::system_clock::now();
	auto time = std::chrono::system_clock::to_time_t(now);
	std::ostringstream current_time;
	current_time << std::put_time(std::localtime(&time), "%Y-%m-%d");
	return current_time.str();
}

std::string Core::Logger::Logger::getCurrentTime() {
	auto now = std::chrono::system_clock::now();
	auto time = std::chrono::system_clock::to_time_t(now);
	std::ostringstream current_time;
	current_time << std::put_time(std::localtime(&time), "%Y-%m-%d %H:%M:%S");
	return current_time.str();
}

std::string Core::Logger::Logger::getLogFileName() {
	#ifdef WINDOWS
		return std::filesystem::current_path().string()+"\\Logs\\" + getCurrentDate() + ".log";
	#else
		return std::filesystem::current_path().string() + "/Logs/" + getCurrentTime() + ".log";
	#endif
}


void Core::Logger::Logger::writeToFile(const std::string& message) {
	if (logFile.is_open()) {
		logFile << message << std::endl;
	}
}

Core::Logger::Logger* Core::Logger::Logger::GetInstance() {
	static Logger logger;
	return &logger;
}

const std::vector<std::string>& Core::Logger::Logger::getLogBuffer() {
  return logBuffer;
}

void Core::Logger::Logger::CheckAndDeleteOldLogFile() {

}