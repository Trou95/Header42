#include "LogService.h"

LogService::LogService()
{
    this->sleep_time = SLEEP_TIME;
}

LogService::LogService(std::unique_ptr<ILogger> logger) : _logger(std::move(logger)) {
    this->sleep_time = SLEEP_TIME;
}

void LogService::disable()
{
    this->_logger.release();
}

void LogService::log(const char *str, int sleep_time) const
{
    if(this->_logger)
        this->_logger->log(str);
    sleep(sleep_time ? sleep_time : this->sleep_time);
}

void LogService::logFormat(const char *format, ...) const
{
    if(this->_logger == nullptr)
        return;

    char buffer[256];
    va_list args;

    va_start (args, format);
    vsprintf (buffer,format, args);
    this->_logger->log(buffer);
    va_end (args);
}

void LogService::logFormat(E_MESSAGE_TYPE message_type, const char *format, ...) const
{
    if(this->_logger == nullptr)
        return;

    char buffer[256];
    char str[1000];
    va_list args;

    va_start (args, format);
    vsprintf (buffer,format, args);
    if(message_type == MESSAGE_INFO)
        sprintf(str,"\x1B[32mINFO:\x1B[0m %s",buffer);
    else
        sprintf(str, "\x1B[34mERROR:\x1B[0m %s",buffer);
    this->log(str);
    va_end (args);
}

void LogService::logFormat(E_MESSAGE_TYPE message_type, int sleep_time, const char *format, ...) const
{
    if(this->_logger == nullptr)
        return;

    char buffer[256];
    char str[1000];
    va_list args;

    va_start (args, format);
    vsprintf (buffer,format, args);
    if(message_type == MESSAGE_INFO)
        sprintf(str,"\x1B[32mINFO:\x1B[0m %s",buffer);
    else if(message_type == MESSAGE_ERROR)
        sprintf(str, "\x1B[34mERROR:\x1B[0m %s",buffer);
    else
        strcpy(str,buffer);
    this->log(str,sleep_time);
    va_end (args);
}
