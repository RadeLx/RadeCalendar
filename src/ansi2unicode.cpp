#include <cstring>
#include <windows.h>
#include <codecvt>
#include <fstream>
#include <string>
#include <iostream>
#include "../inc/ansi2unicode.h"

// https://blog.csdn.net/Loney_Island/article/details/98995551?spm=1001.2101.3001.6650.1&depth_1-utm_source=distribute.pc_relevant.none-task-blog-2%7Edefault%7ECTRLIST%7ERate-1-98995551-blog-115539849.235%5Ev38%5Epc_relevant_anti_vip_base&utm_relevant_index=2

std::wstring ansi2unicode::ANSI2Unicode(const std::string &str) {
    auto len = str.length();
    int unicode_len = MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, nullptr, 0);
    auto *unicode_p = new wchar_t[unicode_len + 1];
    memset(unicode_p, 0, (unicode_len) * sizeof(wchar_t));
    MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, (LPWSTR) unicode_p, unicode_len);
    std::wstring str_w;
    str_w = (wchar_t *) unicode_p;
    delete[] unicode_p;
    return str_w;
}

void ansi2unicode::saveAsUTF8(const std::string &file_name, const std::string &content, const std::string &userName) {
    std::wstring content_unicode = ANSI2Unicode(content);
    std::string userDesktop = "C:\\Users\\" + userName + "\\Desktop\\";
    std::wofstream ofs(userDesktop + file_name, std::ios::ate);
    //std::generate_header表示带BOM的UTF-8，std::little_endian表示不带BOM的UTF-8
    //ofs.imbue(std::locale(ofs.getloc(), new std::codecvt_utf8<wchar_t, 0x10ffff, std::generate_header>));
    ofs.imbue(std::locale(ofs.getloc(), new std::codecvt_utf8<wchar_t, 0x10ffff, std::little_endian>));
    ofs << content_unicode;
    ofs.close();
}
