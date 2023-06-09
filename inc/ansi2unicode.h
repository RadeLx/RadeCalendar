#ifndef RADECALENDAR_ANSI2UNICODE_H
#define RADECALENDAR_ANSI2UNICODE_H

#include "string"

class ansi2unicode {
public:
    static std::wstring ANSI2Unicode(const std::string &str);

    static void saveAsUTF8(const std::string &file_name, const std::string &content, const std::string &userName);
};


#endif //RADECALENDAR_ANSI2UNICODE_H
