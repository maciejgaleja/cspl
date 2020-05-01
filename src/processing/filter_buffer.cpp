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

#include "filter_buffer.hpp"
#include <algorithm>
#include <iostream>

FilterBuffer::FilterBuffer(const std::string& pattern)
{
    for(char c : pattern)
    {
        m_pattern.push_back(c);
        m_buffer.push_back('\0');
    }
}

size_t FilterBuffer::size() const
{
    return m_pattern.size();
}

std::pair<bool, Char> FilterBuffer::add(Char c)
{
    Char ret_c = m_buffer[0];
    m_buffer.pop_front();
    m_buffer.push_back(c);

    bool ret = std::equal(m_pattern.begin(), m_pattern.end(), m_buffer.begin());
    //std::cout << debugToString(m_buffer) << " " << ret << "\n";

    return {ret, ret_c};
}

std::string FilterBuffer::debugToString(const std::deque<Char>& buffer)
{
    std::string ret = "[";
    for(char c : buffer)
    {
        ret += c;
    }
    ret += "]";
    return ret;
}
