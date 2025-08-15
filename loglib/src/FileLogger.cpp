#include "FileLogger.h"

namespace loggers 
{

FileLogger::FileLogger(const std::string& filename, Priority defaultPriority) : ALogger(defaultPriority), m_Filename(filename) 
{
    logs.open(m_Filename);
    if(!logs) std::cout << "Cannot open file.\n";
}

bool FileLogger::log(const std::string& text, Priority priority) {
    if(!logs) logs.open(m_Filename);
    if(!logs) return false;

    auto now = std::chrono::system_clock::now();
    std::time_t now_c = std::chrono::system_clock::to_time_t(now);
    std::tm* local_tm = std::localtime(&now_c);

    if (priority < m_DefaultPriority) priority = m_DefaultPriority;

    logs << std::put_time(local_tm, "%F %T") << "\t" << toString(priority) << "\t" << text << "\n";
    logs.flush();

    return true;
}

FileLogger::~FileLogger() {
    logs.close();
}

}