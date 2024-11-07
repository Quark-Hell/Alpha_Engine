#include "Logger.h"
#include "Core/Tag.h"

Core::Logger::Logger::Logger() {
	logFile.open(getLogFileName(), std::ios::app);
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

std::string Core::Logger::Logger::getCurrentTime() {
	auto now = std::chrono::system_clock::now();
	auto time = std::chrono::system_clock::to_time_t(now);
	std::ostringstream current_time;
	current_time << std::put_time(std::localtime(&time), "%Y-%m-%d");
	return current_time.str();
}

std::string Core::Logger::Logger::getLogFileName() {
	return std::filesystem::current_path().string()+"\\Logs\\" + getCurrentTime() + ".log";
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

template <typename... Data>
void Core::Logger::Logger::LoggerEvent(const Data&... data) {
	std::ostringstream messageStream;
	messageStream << "[" << getCurrentTime() << "] ";
	((messageStream << " " << data), ...);

	writeToFile(messageStream.str());
	writeToBuffer(messageStream.str());
}

template <typename... Data>
void Core::Logger::Logger::LoggerWarning(const Data&... data) {
	std::ostringstream messageStream;
	messageStream << "WARNING [" << getCurrentTime() << "] ";
	((messageStream << " " << data), ...);
	std::string message = "\033[33m" + messageStream.str() + "\033[0m";

	writeToFile(messageStream.str());
	writeToBuffer(message);
}

template <typename... Data>
void Core::Logger::Logger::LoggerError(const Data&... data) {
	std::ostringstream messageStream;
	messageStream << "ERROR [" << getCurrentTime() << "] ";
	((messageStream << " " << data), ...);
	std::string message = "\033[31m" + messageStream.str() + "\033[0m";

	writeToFile(messageStream.str());
	writeToBuffer(message);
}

const std::vector<std::string>& Core::Logger::Logger::getLogBuffer() {
  return logBuffer;
}

void Core::Logger::Logger::CheckAndDeleteOldLogFile() {

}