#pragma once

#include <string>

class IFlag
{
    public:

        IFlag() { }

        const std::string& getKey() const { return this->key; }

    private:

        std::string key;

    protected:

        IFlag(std::string key) { this->key = key; }

};
