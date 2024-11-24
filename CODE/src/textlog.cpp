//==========================================================================================
//   Secret Legacy of the Ancient Caves (SLAC)
//
//   Copyright (c) 2020-2024 Shaun Brandt / Holy Meatgoat Software
//
//   Permission is hereby granted, free of charge, to any person obtaining a copy
//   of this software and associated documentation files (the "Software"), to deal
//   in the Software without restriction, including without limitation the rights
//   to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//   copies of the Software, and to permit persons to whom the Software is
//   furnished to do so, subject to the following conditions:
//
//   The above copyright notice and this permission notice shall be included in all
//   copies or substantial portions of the Software.
//
//   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//   AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//   OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
//   SOFTWARE.
//==========================================================================================
#include "textlog.h"

TextLog g_text_log;

void TextLog::put_line(std::string s) {

    // if we have more than the maximum number of lines,
    // pop them until we have one fewer than the maximum
    if (get_num_lines() >= max_len) {
        while (get_num_lines() > max_len - 1)
            log.pop_front();
    }
    // add the line
    log.push_back(s);
}

std::string TextLog::get_line(int line) {
    int counter = 0;

    // If the range is invalid, return a blank line
    if (line > max_len || line < 0) {
        return "";
    }

    // Use an iterator to find the 'line'th item of the list and return it
    for (std::list<std::string>::iterator it = log.begin(); it != log.end(); ++it) {
        if (line == counter) {
            return *it;
        }
        counter++;
    }
}

std::string TextLog::get_last_line() {
    return log.back();
}

int TextLog::get_num_lines() {
    return log.size();
}

void TextLog::dump_lines() {
    int line = 0;

    for (std::list<std::string>:: iterator it = log.begin(); it != log.end(); ++it) {
        ++line;
        std::cout << "Line " << line <<  ": " << *it << std::endl;
    }
}