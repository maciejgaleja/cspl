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
#define SRC__PROCESSING__CHAR_FILTER_HPP

#include "common.hpp"
#include "filter_buffer.hpp"
#include "item_sink.hpp"
#include "item_source.hpp"

class CharFilter : public ItemSink<Char>
{
public:
    CharFilter(const std::string& start, const std::string& end);
    ~CharFilter() {}
    void add(const Char& c);

    void add_match_sink(std::shared_ptr<ItemSink<Char>> sink)
    {
        m_match_sinks.push_back(sink);
    }
    void add_unmatch_sink(std::shared_ptr<ItemSink<Char>> sink)
    {
        m_unmatch_sinks.push_back(sink);
    }

private:
    std::vector<std::shared_ptr<ItemSink<Char>>> m_match_sinks;
    std::vector<std::shared_ptr<ItemSink<Char>>> m_unmatch_sinks;

    FilterBuffer m_buf_begin;
    FilterBuffer m_buf_end;

    bool m_active = false;
    int m_delay;

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
};

#endif // SRC__PROCESSING__CHAR_FILTER_HPP
