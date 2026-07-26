#pragma once
#include "LoggerInterface.h"
#include <algorithm>

namespace loggers
{


//! Базовый класс для реализации логгеров
class ALogger : public ILogger
{
public:
    //! Установка уровня важности по умолчанию 
    //! @param defaultPriority Уровень важность по умолчанию 
    void setDefaultPriority(Priority defaultPriority) override;
    
    //! Преобразование уровня важности в строковое представление
    //! @param priority Уровень важности
    //! @return Строковое представление уровня важности
    std::string toString(ILogger::Priority priority);

    //! Преобразование строкового предаставления в уровень важности
    //! @param input Строковое представление уровня важности 
    //! @return Уровень важности 
    static ILogger::Priority stringToPriority(const std::string& input);

protected:
    //! Создание логгера с заданным уровнем важности по умолчанию 
    //! @param defaultPriority Уровень важности по умолчанию
    ALogger(Priority defaultPriority);

    //! Уровень важности по умолчанию
    Priority m_DefaultPriority;
};  

} 