#pragma once

#include "IFlag.h"
#include "IFlagValue.h"

class FlagUsername : public IFlag, public IFlagValue<string> {

    public:

        FlagUsername(string key) : IFlag(key) { }




};



