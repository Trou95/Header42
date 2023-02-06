#pragma once

#include <stdarg.h>
#include <cstring>

#include <memory>
#include "Logger.h"

#ifdef WIN32
    #include <windows.h>
    #define sleep Sleep
#else
    #include <unistd.h>
    #define sleep(time) usleep(time * 1000)
#endif

enum E_MESSAGE_TYPE {
    MESSAGE_INFO,
    MESSAGE_ERROR,
    MESSAGE_NONE,
};

constexpr int SLEEP_TIME = 1000;

class LogService {

    public:
        LogService();
        LogService(std::unique_ptr<ILogger> logger);

        void disable();
        void log(const char* str, int sleep_time = 0) const;
        void logFormat(const char* format, ...) const;
        void logFormat(E_MESSAGE_TYPE message_type, const char* format, ...) const;
        void logFormat(E_MESSAGE_TYPE message_type, int sleep_time, const char* format, ...) const;

    private:
        int sleep_time;
        std::unique_ptr<ILogger> _logger;

};

