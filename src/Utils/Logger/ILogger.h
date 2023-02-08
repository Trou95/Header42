#pragma once

class ILogger
{
    public:
        virtual void log(const char* str) = 0;
        virtual ~ILogger() { };
};