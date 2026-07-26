#include "SocketLogger.h"

namespace loggers 
{
SocketLogger::SocketLogger(const std::string& ip, int port, Priority defaultPriority) : ALogger(defaultPriority) 
{
    m_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (m_sock < 0) return;

    sockaddr_in server_addr{};
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    
    if (inet_pton(AF_INET, ip.c_str(), &server_addr.sin_addr) <= 0) {
        close(m_sock);
        m_sock = -1;
        return;
    } 
    if (connect(m_sock, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        close(m_sock);
        m_sock = -1;
        return;
    } 
}

bool SocketLogger::log(const std::string& text, Priority priority) 
{
    if (m_sock < 0) return false; 

    auto now = std::chrono::system_clock::now();
    std::time_t now_c = std::chrono::system_clock::to_time_t(now);
    std::tm local_tm{};
    localtime_r(&now_c, &local_tm);

    if (priority < m_DefaultPriority) return true;

    std::ostringstream ss;
    ss << std::put_time(&local_tm, "%F %T") 
    << '\t' << toString(priority) 
    << '\t' << text 
    << '\n';

    std::string msg = ss.str();
    ssize_t bytes_sent = send(m_sock, msg.c_str(), msg.size(), 0);

    if (bytes_sent < 0) {
        close(m_sock);
        m_sock = -1;
        return false;
    }

    return true;
}

bool SocketLogger::isValid() const 
{
    return m_sock != -1;
}

SocketLogger::~SocketLogger() 
{
    if (m_sock >= 0) close(m_sock);
}
}