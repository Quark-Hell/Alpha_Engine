#pragma once
#include <fstream>
#include <vector>

namespace Core::Logger {
	class Logger {
		private:
			Logger();
			std::ofstream logFile;
			std::vector<std::string> logBuffer;
			void CheckAndDeleteOldLogFile();
			std::string getLogFileName();
			std::string getCurrentTime();
			int daysToDeleteLogFile;
			void writeToFile(const std::string& message);
			void writeToBuffer(const std::string& message);
		public:
			~Logger();
			static Logger* GetInstance();
			const std::vector<std::string>& getLogBuffer();
			void SetDaysToDeleteLogFile(int days);
			template <typename... Data>
			void LoggerEvent(const Data&... data);
			template <typename... Data>
			void LoggerWarning(const Data&... data);
			template <typename... Data>
			void LoggerError(const Data&... data);
	};
}

