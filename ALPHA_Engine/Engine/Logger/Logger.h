#pragma once
#include <fstream>
#include <vector>
#include <chrono>
#include <sstream>
#include <iostream>
#include <filesystem>
#include <list>

namespace Logger {
    class Logger {
    private:
        std::ofstream _logFile;
        std::list<std::string> _logBuffer;
        int _daysToDeleteLogFile = 7;

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

        template<typename... Data>
        static void LoggerEvent(const Data &... data) {
            const auto logger = Logger::GetInstance();

            logger->_logFile.open(logger->GetLogFileName(), std::ios::app);
            std::ostringstream messageStream;
            messageStream << "INFO:\t [" << logger->GetCurrentTime() << "] ";
            ((messageStream << " " << data), ...);

            logger->WriteToFile(messageStream.str());
            logger->WriteToBuffer(messageStream.str());
            std::cout << messageStream.str() << std::endl;
            logger->_logFile.close();
        }

        template<typename... Data>
        static void LoggerWarning(const Data &... data) {
            const auto logger = Logger::GetInstance();

            logger->_logFile.open(logger->GetLogFileName(), std::ios::app);
            std::ostringstream messageStream;
            messageStream << "WARNING: [" << logger->GetCurrentTime() << "] ";
            ((messageStream << " " << data), ...);
            const std::string message = "\033[33m" + messageStream.str() + "\033[0m";

            logger->WriteToFile(messageStream.str());
            logger->WriteToBuffer(message);
            std::cout << message << std::endl;
            logger->_logFile.close();
        }

        template<typename... Data>
        static void LoggerError(const Data &... data) {
            const auto logger = Logger::GetInstance();

            logger->_logFile.open(logger->GetLogFileName(), std::ios::app);
            std::ostringstream messageStream;
            messageStream << "ERROR:\t [" << logger->GetCurrentTime() << "] ";
            ((messageStream << " " << data), ...);
            const std::string message = "\033[31m" + messageStream.str() + "\033[0m";

            logger->WriteToFile(messageStream.str());
            logger->WriteToBuffer(message);
            std::cout << message << std::endl;
            logger->_logFile.close();
        }
    };
}
