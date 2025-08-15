#include "FileLogger.h"
#include <iostream>
#include <string>
#include <thread>
#include <atomic>
#include <queue>
#include <mutex>
#include <condition_variable>

struct LogMessage 
{
    std::string message = "";
    loggers::ILogger::Priority priority = loggers::ILogger::Priority::Info;
};

std::queue<LogMessage> logQueue;
std::mutex queueMutex;
std::condition_variable cv;
bool finished = false;

void loggerThread(loggers::FileLogger& fileLog) {
    while (!finished || !logQueue.empty()) {
        std::unique_lock<std::mutex> lock(queueMutex);
        cv.wait(lock, [] { return finished || !logQueue.empty(); });

        while (!logQueue.empty()) {
            LogMessage entry = logQueue.front();
            logQueue.pop();
            lock.unlock();
            fileLog.log(entry.message, entry.priority);
            lock.lock();
        }
    }
}

int main(int argc, char* argv[])
{
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <log_file> [default_level]\nExample: " << argv[0] << " log.txt Info\n";
        return 1;
    }

    std::string filename = argv[1];
    loggers::ILogger::Priority priority = loggers::ALogger::stringToPriority(argv[2]);

    loggers::FileLogger fileLog(filename, priority);

    std::thread logThread(loggerThread, std::ref(fileLog));

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