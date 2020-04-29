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


#ifndef SRC__PROCESSING__CHAR_FILTER_HPP

#endif // SRC__PROCESSING__CHAR_FILTER_HPP
#define SRC__PROCESSING__CHAR_FILTER_HPP
#include "char_sink.hpp"
#include "char_source.hpp"
#include "common.hpp"
#include "word_source.hpp"

class CharFilter : public CharSink
{
private:
    std::vector<std::shared_ptr<CharSink>> m_match_sinks;
    std::vector<std::shared_ptr<CharSink>> m_unmatch_sinks;
    void notify_match(Char c)
    {
        for(auto& sink : m_match_sinks)
        {
            sink->add(c);
        }
    }
    void notify_unmatch(Char c)
    {
        for(auto& sink : m_unmatch_sinks)
        {
            sink->add(c);
        }
    }

public:
    ~CharFilter() {}
    void add(Char c);

    void add_match_sink(std::shared_ptr<CharSink> sink)
    {
        m_match_sinks.push_back(sink);
    }
    void add_unmatch_sink(std::shared_ptr<CharSink> sink)
    {
        m_unmatch_sinks.push_back(sink);
    }
};
