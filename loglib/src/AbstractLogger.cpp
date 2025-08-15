#include "AbstractLogger.h"

namespace loggers 
{

ALogger::ALogger(Priority defaultPriority) : m_DefaultPriority(defaultPriority) {}

void ALogger::setDefaultPriority(Priority defaultPriority) 
{
    m_DefaultPriority = defaultPriority;
}

std::string toString(ALogger::Priority priority) {
    switch (priority)
    {
    case ALogger::Priority::Info: return "[INFO]";
    case ALogger::Priority::Warning: return "[WARNING]";
    case ALogger::Priority::Error: return "[ERROR]";
    
    default: return "[Unknown]";
    }
}

}