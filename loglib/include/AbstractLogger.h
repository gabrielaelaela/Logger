#pragma once
#include "LoggerInterface.h"

namespace loggers
{

class ALogger : public ILogger
{
public:
    void setDefaultPriority(Priority defaultPriority) override;
    
    std::string toString(ALogger::Priority priority);

protected:
    Priority m_DefaultPriority;
    ALogger(Priority defaultPriority);
};  

} 