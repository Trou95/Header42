#pragma once

template<class T>
class IFlagValue {

    public:

        const T& getValue() { return this->value; }

    protected:

        explicit IFlagValue() { }
        explicit IFlagValue(const T& value) { this->value = value; }

        T value;


};