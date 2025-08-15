#include "AbstractLogger.h"

namespace loggers 
{

ALogger::ALogger(Priority defaultPriority) : m_DefaultPriority(defaultPriority) {}

void ALogger::setDefaultPriority(Priority defaultPriority) 
{
    m_DefaultPriority = defaultPriority;
}

std::string ALogger::toString(ILogger::Priority priority) {
    switch (priority)
    {
    case ILogger::Priority::Info: return "[INFO]\t";
    case ILogger::Priority::Warning: return "[WARNING]";
    case ILogger::Priority::Error: return "[ERROR]\t";
    
    default: return "[Unknown]";
    }
}

ILogger::Priority ALogger::stringToPriority(const std::string& input) {
    std::string lowerInput = input; // создаём копию
    std::transform(lowerInput.begin(), lowerInput.end(), lowerInput.begin(),
                   [](unsigned char c){ return std::tolower(c); });
    if (lowerInput == "warning") return ILogger::Priority::Warning;
    if (lowerInput == "error") return ILogger::Priority::Error;
    return ILogger::Priority::Info;
}


}