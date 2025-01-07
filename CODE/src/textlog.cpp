//==========================================================================================
//   Secret Legacy of the Ancient Caves (SLAC)
//
//   Copyright (c) 2020-2025 Shaun Brandt / Holy Meatgoat Software
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

//----------------------------------------------------------------------------
// Adds a line to the log, removing the oldest one if the log is full
//
// Arguments:
//   s - the line to add
//
// Returns:
//   Nothing
//----------------------------------------------------------------------------
void TextLog::put_line(std::string s) {

    // if we have more than the maximum number of lines,
    // pop them until we have one fewer than the maximum
    if (get_num_lines() >= max_len) {
        while (get_num_lines() > max_len - 1)
            log.pop_front();
    }
    // add the line
    log.push_back(s);

    // Since adding a line is always going to trigger a new render, just do it
    // here
    g_state_flags.update_text_dialog = true;
    g_state_flags.update_display = true;
}

//----------------------------------------------------------------------------
// Gets a line from the log, where 0 is the oldest line
//
// Arguments:
//   line - the line number to retreive.  
//
// Returns:
//   The string at that line, or a blank line if the index is invalid
//----------------------------------------------------------------------------
std::string TextLog::get_line(int line) {
    int counter = 0;

    // If the range is invalid, return a blank line
    if (line >= get_num_lines() || line < 0) {
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

//----------------------------------------------------------------------------
// Gets the newest entry in the log
//
// Arguments:
//   None
//
// Returns:
//   A string containing the last line in the log
//----------------------------------------------------------------------------
std::string TextLog::get_last_line() {
    return log.back();
}

//----------------------------------------------------------------------------
// Gets the number of entries in the log
//
// Arguments:
//   None
//
// Returns:
//   The number of lines in the log
//----------------------------------------------------------------------------
int TextLog::get_num_lines() {
    return log.size();
}

//----------------------------------------------------------------------------
// Empties the text log
//
// Arguments:
//   None
//
// Returns:
//   Nothing
//----------------------------------------------------------------------------
void TextLog::clear() {
    log.clear();
}

//----------------------------------------------------------------------------
// Debug function that prints the log
//
// Arguments:
//   None
//
// Returns:
//   Nothing
//----------------------------------------------------------------------------
void TextLog::dump_lines() {
    int line = 0;

    for (std::list<std::string>:: iterator it = log.begin(); it != log.end(); ++it) {
        ++line;
        std::cout << "Line " << line <<  ": " << *it << std::endl;
    }
}

