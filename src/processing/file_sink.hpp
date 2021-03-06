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

#ifndef SRC__PROCESSING__FILE_SINK_HPP
#define SRC__PROCESSING__FILE_SINK_HPP


#include "item_sink.hpp"

#include <sstream>

#include <fstream>
#include <iostream>

class FileSink : public ItemSink<Char>, public ItemSink<Word>
{
public:
    FileSink(const std::string& filename) : m_file(filename) {}

    void add(const Char& c)
    {
        if(c != '\0')
        {
            m_buffer << c;
        }
    }

    void add(const Word& word)
    {
        m_buffer << word;
    }

    void flush()
    {
        std::ofstream outFile;
        outFile.open(m_file);
        outFile << m_buffer.str();
        outFile.close();
        m_buffer.str("");
    }

private:
    std::stringstream m_buffer;
    std::string m_file;
};


#endif // SRC__PROCESSING__FILE_SINK_HPP
