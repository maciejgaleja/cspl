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

#include "char_filter.hpp"

#include <iomanip>
#include "..//log.hpp"
#include <iostream>

using std::cout;

CharFilter::CharFilter(const std::string& start,
                       const std::string& end,
                       bool inverted)
    : m_buf_begin(start), m_buf_end(end), m_invert(inverted)
{
    if(inverted)
    {
        m_on_match   = [this](char c) { notify_unmatch(c); };
        m_on_unmatch = [this](char c) { notify_match(c); };
    }
    else
    {
        m_on_match   = [this](char c) { notify_match(c); };
        m_on_unmatch = [this](char c) { notify_unmatch(c); };
    }
}


void CharFilter::add(const Char& c)
{
    m_delay          = --m_delay < -1 ? -1 : m_delay;
    auto match_begin = m_buf_begin.add(c);
    auto match_end   = m_buf_end.add(c);
    if(match_begin.first)
    {
        m_active = true;
        m_delay  = m_buf_end.size();
    }
    Char c_fwd = match_end.second;
    if(c_fwd != '\0')
    {
        if(m_active && (m_delay < 0))
        {
            m_on_match(c_fwd);
        }
        else
        {
            m_on_unmatch(c_fwd);
        }
    }
    if(match_end.first)
    {
        m_active = false;
    }
}
