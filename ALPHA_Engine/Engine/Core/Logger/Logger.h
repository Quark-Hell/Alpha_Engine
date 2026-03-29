#pragma once
#include <fstream>
#include <chrono>
#include <sstream>
#include <iostream>
#include <filesystem>
#include <list>
#include <mutex>

#define __LOGERROR__ (std::string(__FILE__ ":") + std::to_string(__LINE__))

namespace Core {
    class Logger {
    private:
        std::ofstream _logFile;
        std::vector<std::string> _logBuffer;

        std::vector<std::string> _fileLogBuffer;
        int _daysToDeleteLogFile = 7;

        std::mutex _mutex;

    private:
        Logger();

        std::string GetLogFileName();
        std::string GetCurrentTime();
        std::string GetCurrentDate();

        void WriteToFileBuffer(const std::string &message);
        void WriteToBuffer(const std::string &message);

    public:
        ~Logger();
        static Logger *GetInstance();

        const std::vector<std::string> &GetLogBuffer();



#if LOGGER_INCLUDED
        static inline void SaveLogs() {
            const auto logger = GetInstance();

            if (!logger->_logFile.is_open()) {
                logger->_logFile.open(logger->GetLogFileName(), std::ios::app);
            }

            for (auto& message : logger->_logBuffer) {
                std::cout << message << std::endl;
            }

            for (auto& message : logger->_fileLogBuffer) {
                logger->_logFile << message << std::endl;
            }

            logger->_logBuffer.clear();
            logger->_fileLogBuffer.clear();
            logger->_logFile.close();
        }

        template<typename... Data>
        static inline void LogInfo(const Data &... data) {
            const auto logger = GetInstance();

            std::ostringstream messageStream;
            messageStream << "[" << logger->GetCurrentTime() << "] INFO:";
            ((messageStream << " " << data), ...);
            const std::string message = "\033[36m" + messageStream.str() + "\033[0m";

            const std::lock_guard guard(logger->_mutex);

            logger->WriteToFileBuffer(messageStream.str());
            logger->WriteToBuffer(message);
        }

        template<typename... Data>
        static inline void LogWarning(const Data &... data) {
            const auto logger = GetInstance();

            std::ostringstream messageStream;
            messageStream << "[" << logger->GetCurrentTime() << "] WARNING:";
            ((messageStream << " " << data), ...);
            const std::string message = "\033[33m" + messageStream.str() + "\033[0m";

            const std::lock_guard guard(logger->_mutex);

            logger->WriteToFileBuffer(messageStream.str());
            logger->WriteToBuffer(message);
        }

        template<typename... Data>
        static inline void LogError(const Data &... data) {
            const auto logger = GetInstance();

            std::ostringstream messageStream;
            messageStream << "[" << logger->GetCurrentTime() << "] ERROR:";
            ((messageStream << " " << data), ...);
            const std::string message = "\033[31m" + messageStream.str() + "\033[0m";

            const std::lock_guard guard(logger->_mutex);

            logger->WriteToFileBuffer(messageStream.str());
            logger->WriteToBuffer(message);
        }

        template<typename... Data>
        static void LogCritical(const Data &... data) {
            const auto logger = GetInstance();

            std::ostringstream messageStream;
            messageStream << "[" << logger->GetCurrentTime() << "] CRITICAL:";
            ((messageStream << " " << data), ...);
            const std::string message = "\033[1;31m" + messageStream.str() + "\033[0m";

            const std::lock_guard guard(logger->_mutex);

            logger->WriteToFileBuffer(messageStream.str());
            logger->WriteToBuffer(message);
            std::cout << message << std::endl;

            logger->SaveLogs();

            abort();
        }
#else
        template<typename... Data>
        static void LogInfo(const Data &... data) {}

        template<typename... Data>
        static void LogWarning(const Data &... data) {}

        template<typename... Data>
        static void LogError(const Data &... data) {}

        template<typename... Data>
        static void LogCritical(const Data &... data) {}

        static inline void SaveLogs() {}
#endif
    };
}
