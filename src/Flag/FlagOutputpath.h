#pragma once

#include "IFlag.h"
#include "IFlagValue.h"

class FlagOutputpath : public IFlag, IFlagValue<string> {

public:
    FlagOutputpath(std::string key) : IFlag(key) { }

};



