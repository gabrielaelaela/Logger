#include "FileLogger.h"

namespace loggers 
{

FileLogger::FileLogger(const std::string& filename, Priority defaultPriority) : ALogger(defaultPriority), m_Filename(filename) 
{
    logs.open(m_Filename, std::ios::app);
}

bool FileLogger::log(const std::string& text, Priority priority) 
{
    if(!logs) logs.open(m_Filename);
    if(!logs) return false;

    auto now = std::chrono::system_clock::now();
    std::time_t now_c = std::chrono::system_clock::to_time_t(now);
    std::tm local_tm{};
    localtime_r(&now_c, &local_tm);

    if (priority < m_DefaultPriority) return true;

    logs << std::put_time(&local_tm, "%F %T") 
    << "\t" << toString(priority) 
    << "\t" << text 
    << "\n";

    logs.flush();

    return static_cast<bool>(logs);
}

bool FileLogger::isValid() const 
{
    return static_cast<bool>(logs);
}

FileLogger::~FileLogger() 
{
    logs.close();
}

}