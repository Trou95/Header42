#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "../Utils/Utils.h"

class Header {

    public:
        typedef typename std::string sign;

    public:
        static size_t _sign_len;

        Header(const char* username,const char* filename,const char* create_time,const char* modify_time);
        const sign& getSign() const;
        static bool isSign(const std::string& str);


    private:
        void createSign();
        void formatLine(int start_index, const std::string& str);

        sign _sign;

        const char* _username;
        const char* _filename;
        const char* _create_time;
        const char* _modify_time;

        static const sign _default_sign;
};

std::ostream &operator<<(std::ostream &out, const Header& header);

