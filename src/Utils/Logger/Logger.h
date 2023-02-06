#pragma once

#include <iostream>
#include "ILogger.h"

class Logger : public ILogger {

    public:
        void log(const char* str);

};
