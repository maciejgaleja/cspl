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

#ifndef SRC__PROCESSING__WORD_CONVERTER_HPP
#define SRC__PROCESSING__WORD_CONVERTER_HPP

#include "char_sink.hpp"
#include "word_sink.hpp"
#include "word_source.hpp"

#include <sstream>

class WordConverter : public CharSink, public WordSource
{
private:
    std::vector<std::shared_ptr<WordSink>> m_word_sinks;
    std::vector<std::shared_ptr<CharSink>> m_char_sinks;
    std::stringstream m_buffer;

    void notify_all_words(Word word);
    void notify_all_chars(Char c);

    bool is_separator(Char c);

public:
    void add(Char c);

    void add_word_sink(std::shared_ptr<WordSink> sink);
    void add_char_sink(std::shared_ptr<CharSink> sink);
};

#endif // SRC__PROCESSING__WORD_CONVERTER_HPP
