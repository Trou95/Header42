#pragma once

#include "IFlag.h"
#include "IFlagValue.h"

#include <unordered_set>

class FlagSource : public IFlag, public IFlagValue<std::unordered_set<string> >  {

public:
    FlagSource(string key) : IFlag(key) { }

    void addValue(string value) {
        this->value.insert(value);
    }

};



