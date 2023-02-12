#include "Header.h"

const Header::sign Header::_default_sign = "/* ************************************************************************** */\n"
                                           "/*                                                                            */\n"
                                           "/*   .c                                                   :::      ::::::::   */\n"
                                           "/*                                                      :+:      :+:    :+:   */\n"
                                           "/*                                                    +:+ +:+         +:+     */\n"
                                           "/*   By:                                            +#+  +:+       +#+        */\n"
                                           "/*                                                +#+#+#+#+#+   +#+           */\n"
                                           "/*   Created:                                          #+#    #+#             */\n"
                                           "/*   Updated:                                         ###   ########.fr       */\n"
                                           "/*                                                                            */\n"
                                           "/* ************************************************************************** */";

size_t Header::_sign_len = Header::_default_sign.length();



Header::Header(const char* username, const char* filename, const char* create_time, const char* modify_time, const char* campus) :
                _username(username), _filename(filename), _create_time(create_time), _modify_time(modify_time), _campus(campus)
{
    createSign();
}

const Header::sign& Header::getSign() const
{
    return this->_sign;
}

bool Header::isSign(const std::string& str)
{

    if(str[0] != '/' || str.length() < Header::_sign_len)
        return false;

    int count = 0;
    for(int i = 0; str[i] && Header::_default_sign[i]; i++)
        if(Header::_default_sign[i] == str[i])
            count++;
    return Header::_sign_len - count < 350;
}

void Header::createSign()
{
    _sign = Header::_default_sign;

    size_t index = _sign.find(".c");
    formatLine(index, _filename);

    index = _sign.find("By:");
    std::string user = str_format(string("%s <%s@student.42." + string(_campus) + ">").c_str(),_username,_username);
    formatLine(index + 4, user);

    index = _sign.find("Created:");
    std::string create_time = str_format("%s by %s",_create_time,_username);
    formatLine(index + 9, create_time);

    index = _sign.find("Updated:");
    std::string modify_time = str_format("%s by %s",_modify_time,_username);
    formatLine(index + 9, modify_time);

    index = _sign.find("fr");
    formatLine(index,_campus);
}

void Header::formatLine(int start_index, const std::string& str)
{
    int i = 0;
    for(; _sign[start_index + i] && str[i]; i++)
        _sign[start_index + i] = str[i];
}

std::ostream& operator<<(std::ostream &out, const Header& header)
{
    out << header.getSign();
    return (out);
}
