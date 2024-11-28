#ifndef __TEXTLOG_H__
#define __TEXTLOG_H__

#include "globals.h"

class TextLog {
private:
    std::list<std::string> log;
    static const unsigned char max_len = 8;
public:
    void put_line(std::string s);
    std::string get_line(int line);
    std::string get_last_line();
    int get_num_lines();
    void dump_lines();
};

extern TextLog g_text_log;

#endif