#pragma once
#include "AbstractLogger.h"
#include <iostream>
#include <fstream>
#include <filesystem>
#include <ctime>

namespace loggers
{

class FileLogger : public ALogger
{
public:
    FileLogger() = delete;
    FileLogger(const std::string& filename, Priority defaultPriority);
    ~FileLogger();
    
    bool log(const std::string& text, Priority priority) override;

private:
    std::filesystem::path m_Filename;
    std::ofstream logs;
};

}