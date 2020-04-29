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

#ifndef SRC__PROCESSING__HUNSPELL_CHECKER_HPP
#define SRC__PROCESSING__HUNSPELL_CHECKER_HPP

#include "word_sink.hpp"
#include "word_source.hpp"

#include "../dictionary/dictionary.hpp"

class HunspellChecker : public WordSink, public WordSource
{
public:
    HunspellChecker(Dictionary& dict) : m_dict(dict){};
    void add(const Word& word);
    std::vector<Word>& errors()
    {
        return m_errors;
    }

protected:
    Dictionary& m_dict;
    std::vector<Word> m_errors;
};

#endif // SRC__PROCESSING__HUNSPELL_CHECKER_HPP
