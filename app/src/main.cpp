#include "FileLogger.h"
#include "SocketLogger.h"
#include <iostream>
#include <string>
#include <thread>
#include <atomic>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <cctype>
#include <limits>

struct LogMessage 
{
    std::string message = "";
    loggers::ILogger::Priority priority = loggers::ILogger::Priority::Info;
};

std::queue<LogMessage> logQueue;
std::mutex queueMutex;
std::condition_variable cv;
std::atomic<bool> finished = false;

void loggerThread(loggers::ILogger& logger) {
    while (true) {
        std::unique_lock<std::mutex> lock(queueMutex);

        cv.wait(lock, [] {
            return finished || !logQueue.empty();
        });

        if (finished && logQueue.empty())
            break;

        LogMessage entry = logQueue.front();
        logQueue.pop();

        lock.unlock();

        logger.log(entry.message, entry.priority);
    }
}

int main(int argc, char* argv[])
{
    std::cout << "Choose default priority (Enter I for Info, W for Warning or E for Error): ";
    char defPriority;
    std::cin >> defPriority;
    defPriority = std::toupper(static_cast<unsigned char>(defPriority));
    loggers::ILogger::Priority priority;
    switch (defPriority)
    {
    case 'I':
        priority = loggers::ILogger::Priority::Info;
        break;
    
    case 'W':
    priority = loggers::ILogger::Priority::Warning;
        break;

    case 'E':
        priority = loggers::ILogger::Priority::Error;
        break;

    default:
        std::cout << "Invalid priority.\n";
        return 1;
    }

    std::unique_ptr<loggers::ILogger> logger;

    std::cout << "\nChoose logger type (enter F for File or S for Socket): ";
    char loggerType;
    std::cin >> loggerType;
    loggerType = std::toupper(static_cast<unsigned char>(loggerType));
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    switch (loggerType)
    {
    case 'F':
    {
        std::cout << "Enter filename: ";
        std::string filename;
        std::getline(std::cin, filename);

        logger = std::make_unique<loggers::FileLogger>(filename, priority);
        break;
    }
    
    case 'S':
    {
        std::cout << "Enter ip address: ";
        std::string ip;
        std::getline(std::cin, ip);

        std::cout << "\nEnter port: ";
        int port = 0;
        std::cin >> port;

        logger = std::make_unique<loggers::SocketLogger>(ip, port, priority);
        break;
    }

    default:
        std::cout << "Invalid logger type.\n";
        return 1;
    }

    if (!logger->isValid()) {
        std::cerr << "Logger initialization failed.\n";
        return 1;
    }

    std::thread logThread(loggerThread, std::ref(*logger));

    while (true)
    {
        std::string message, pr;

        std::cout << "Enter the log message (or 'end'): ";
        std::getline(std::cin, message);

        if (message == "end") break;

        std::cout << "Enter the priority level (Info, Warning, Error): ";
        std::getline(std::cin, pr);

        loggers::ILogger::Priority priority = pr.empty() ? loggers::ILogger::Priority::Info
                                                           : loggers::ALogger::stringToPriority(pr);

        std::lock_guard<std::mutex> lock(queueMutex);
        logQueue.push({message, priority});
        cv.notify_one();
    }
    
    finished = true;
    cv.notify_one();
    logThread.join();

    std::cout << "End of the program\n";

    return 0;
}