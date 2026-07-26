#pragma once
#include "AbstractLogger.h"
#include <iostream>
#include <fstream>
#include <filesystem>
#include <ctime>

namespace loggers
{

//! Логгер, записывающий сообщения в файл
class FileLogger : public ALogger
{
public:
    FileLogger() = delete;

    //! Создание файлового логгера 
    //! @param filename Путь к файлу с логами
    //! @param defaultPriority Уровень важности по умолчанию 
    FileLogger(const std::string& filename, Priority defaultPriority);

    //! Закрытие файла журнала
    ~FileLogger();
    
    //! Запись сообщений в лог 
    //! @param text Текст сообщения
    //! @param priority Уровень важности сообщения
    //! @return true в случае успешной записи, иначе false
    bool log(const std::string& text, Priority priority) override;

private:
    //! Путь к файлу журнала
    std::filesystem::path m_Filename;

    //! Поток для записи в журнал
    std::ofstream logs;
};

}