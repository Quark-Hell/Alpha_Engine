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
        std::list<std::string> _logBuffer;
        int _daysToDeleteLogFile = 7;

        std::mutex _mutex;

    private:
        Logger();

        void CheckAndDeleteOldLogFile();

        std::string GetLogFileName();
        std::string GetCurrentTime();
        std::string GetCurrentDate();

        void WriteToFile(const std::string &message);
        void WriteToBuffer(const std::string &message);

    public:
        ~Logger();
        static Logger *GetInstance();

        const std::list<std::string> &GetLogBuffer();

        //Not work now
        void SetDaysToDeleteLogFile(int days);

#if LOGGER_INCLUDED
        template<typename... Data>
        static void LogInfo(const Data &... data) {
            const auto logger = Logger::GetInstance();

            std::ostringstream messageStream;
            messageStream << "[" << logger->GetCurrentTime() << "] INFO:";
            ((messageStream << " " << data), ...);
            const std::string message = "\033[36m" + messageStream.str() + "\033[0m";

            const std::lock_guard<std::mutex> guard(logger->_mutex);
            logger->_logFile.open(logger->GetLogFileName(), std::ios::app);

            logger->WriteToFile(messageStream.str());
            logger->WriteToBuffer(message);
            std::cout << message << std::endl;
            logger->_logFile.close();
        }

        template<typename... Data>
        static void LogWarning(const Data &... data) {
            const auto logger = Logger::GetInstance();

            std::ostringstream messageStream;
            messageStream << "[" << logger->GetCurrentTime() << "] WARNING:";
            ((messageStream << " " << data), ...);
            const std::string message = "\033[33m" + messageStream.str() + "\033[0m";

            const std::lock_guard<std::mutex> guard(logger->_mutex);
            logger->_logFile.open(logger->GetLogFileName(), std::ios::app);

            logger->WriteToFile(messageStream.str());
            logger->WriteToBuffer(message);
            std::cout << message << std::endl;
            logger->_logFile.close();
        }

        template<typename... Data>
        static void LogError(const Data &... data) {
            const auto logger = Logger::GetInstance();

            std::ostringstream messageStream;
            messageStream << "[" << logger->GetCurrentTime() << "] ERROR:";
            ((messageStream << " " << data), ...);
            const std::string message = "\033[31m" + messageStream.str() + "\033[0m";

            const std::lock_guard<std::mutex> guard(logger->_mutex);
            logger->_logFile.open(logger->GetLogFileName(), std::ios::app);

            logger->WriteToFile(messageStream.str());
            logger->WriteToBuffer(message);
            std::cout << message << std::endl;
            logger->_logFile.close();
        }

        template<typename... Data>
        static void LogCritical(const Data &... data) {
            const auto logger = Logger::GetInstance();

            std::ostringstream messageStream;
            messageStream << "[" << logger->GetCurrentTime() << "] CRITICAL:";
            ((messageStream << " " << data), ...);
            const std::string message = "\033[1;31m" + messageStream.str() + "\033[0m";

            const std::lock_guard<std::mutex> guard(logger->_mutex);
            logger->_logFile.open(logger->GetLogFileName(), std::ios::app);

            logger->WriteToFile(messageStream.str());
            logger->WriteToBuffer(message);
            std::cout << message << std::endl;
            logger->_logFile.close();

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
#endif
    };
}
