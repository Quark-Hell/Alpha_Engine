#pragma once
#include <fstream>
#include <vector>
#include <chrono>
#include <sstream>
#include <iostream>
#include <filesystem>

namespace Core::Logger {
	class Logger {
		private:
			Logger();
			std::ofstream logFile;
			std::vector<std::string> logBuffer;
			void CheckAndDeleteOldLogFile();
			std::string getLogFileName();
			std::string getCurrentTime();
			std::string getCurrentDate();
			int daysToDeleteLogFile;
			void writeToFile(const std::string& message);
			void writeToBuffer(const std::string& message);
		public:
			~Logger();
			static Logger* GetInstance();
			const std::vector<std::string>& getLogBuffer();
			void SetDaysToDeleteLogFile(int days);

			template <typename... Data>
			void LoggerEvent(const Data&... data) {
				logFile.open(getLogFileName(), std::ios::app);
				std::ostringstream messageStream;
				messageStream << "INFO:\t [" << getCurrentTime() << "] ";
				((messageStream << " " << data), ...);

				writeToFile(messageStream.str());
				writeToBuffer(messageStream.str());
				logFile.close();
			}

			template <typename... Data>
			void LoggerWarning(const Data&... data) {
				logFile.open(getLogFileName(), std::ios::app);
				std::ostringstream messageStream;
				messageStream << "WARNING: [" << getCurrentTime() << "] ";
				((messageStream << " " << data), ...);
				std::string message = "\033[33m" + messageStream.str() + "\033[0m";

				writeToFile(messageStream.str());
				writeToBuffer(message);
				logFile.close();
			}

			template <typename... Data>
			void LoggerError(const Data&... data) {
				logFile.open(getLogFileName(), std::ios::app);
				std::ostringstream messageStream;
				messageStream << "ERROR:\t [" << getCurrentTime() << "] ";
				((messageStream << " " << data), ...);
				std::string message = "\033[31m" + messageStream.str() + "\033[0m";

				writeToFile(messageStream.str());
				writeToBuffer(message);
				logFile.close();
			}
	};
}

