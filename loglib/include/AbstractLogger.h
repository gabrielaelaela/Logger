#pragma once
#include "LoggerInterface.h"
#include <algorithm>

namespace loggers
{

class ALogger : public ILogger
{
public:
    void setDefaultPriority(Priority defaultPriority) override;
    
    std::string toString(ILogger::Priority priority);
    static ILogger::Priority stringToPriority(const std::string& input);

protected:
    Priority m_DefaultPriority;
    ALogger(Priority defaultPriority);
};  

} 