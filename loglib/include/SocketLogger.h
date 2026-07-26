#pragma once
#include "AbstractLogger.h"
#include <cstring>
#include <sstream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <ctime>
#include <iomanip>
#include <chrono>

namespace loggers
{

//! Логгер, записывающий сообщения в сокет 
class SocketLogger : public ALogger
{
public:
    SocketLogger() = delete;

    //! Создание сокет логгера 
    //! @param ip Адрес сокета
    //! @param port Порт сокета 
    //! @param defaultPriority Уровень важности по умолчанию 
    SocketLogger(const std::string& ip, int port, Priority defaultPriority);

    //! Закрытие сокета
    ~SocketLogger() override;
    
    //! Запись сообщений в лог 
    //! @param text Текст сообщения
    //! @param priority Уровень важности сообщения
    //! @return true в случае успешной записи, иначе false
    bool log(const std::string& text, Priority priority) override;

    //! Проверка создания логгера
    //! @return true в случае успешного создания, иначе false
    bool isValid() const override;

private:
    //! Сокет
    int m_sock = -1;
};

}