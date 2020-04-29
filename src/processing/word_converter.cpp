/**
 * Copyright (c) 2020 Maciej Galeja
 * 
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
**/

#include "word_converter.hpp"

#include <algorithm>
#include <iostream>

using std::any_of;

void WordConverter::add(Char c)
{
    if(is_separator(c))
    {
        std::string word = m_buffer.str();
        m_buffer.str("");
        if(word.length() > 0)
        {
            notify_all_words(word);
        }
        notify_all_chars(c);
    }
    else
    {
        m_buffer << c;
    }
}

void WordConverter::add_word_sink(std::shared_ptr<WordSink> sink)
{
    m_word_sinks.push_back(sink);
}

void WordConverter::notify_all_words(Word word)
{
    for(auto& sink : m_word_sinks)
    {
        sink->add(word);
    }
}

void WordConverter::add_char_sink(std::shared_ptr<CharSink> sink)
{
    m_char_sinks.push_back(sink);
}

void WordConverter::notify_all_chars(Char c)
{
    for(auto& sink : m_char_sinks)
    {
        sink->add(c);
    }
}

bool WordConverter::is_separator(Char c)
{
    const std::vector<Char> separators = {'\0', ' ', ',', '\n', '\r','"','\'', '(',')','{','}','[',']','.',':',';'};
    bool ret                           = any_of(
        separators.begin(), separators.end(), [c](Char s) { return s == c; });
    return ret;
}
