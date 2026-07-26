#pragma once
#include <string>

namespace loggers
{

//! Интерфейс логгера
class ILogger
{
public:
    //! Перечисление уровней важности логов
    enum class Priority 
    {
        Info = 0,    //!< Информационное сообщение
        Warning = 1, //!< Предупреждение
        Error = 2    //!< Ошибка
    };

    //! Виртуальный деструктор
    virtual ~ILogger() = default;

    //! Запись сообщений в лог 
    //! @param text Текст сообщения
    //! @param priority Уровень важности сообщения
    //! @return true в случае успешной записи, иначе false
    virtual bool log(const std::string& text, Priority priority) = 0;

    //! Установка уровня важности по умолчанию 
    //! @param defaultPriority Уровень важности по умолчанию 
    virtual void setDefaultPriority(Priority defaultPriority) = 0;
};  

} 