#pragma once
#include <string>

namespace loggers
{

class ILogger
{
public:
    enum class Priority 
    {
        Info = 0, 
        Warning = 1, 
        Error = 2
    };

    virtual ~ILogger() = default;

    virtual bool log(const std::string& text, Priority priority) = 0;
    virtual void setDefaultPriority(Priority defaultPriority) = 0;
};  

} 