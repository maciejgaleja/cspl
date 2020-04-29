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

#ifndef SRC__PROCESSING__HUNSPELL_FIXER_HPP
#define SRC__PROCESSING__HUNSPELL_FIXER_HPP

#include "hunspell_checker.hpp"

struct UserDecision
{
    enum class Choice
    {
        REPLACE,
        IGNORE,
        ADD
    };
    Choice choice;
    int chosen_word = -1;
};

class HunspellFixer : public HunspellChecker
{
public:
    HunspellFixer(Dictionary& dict) : HunspellChecker(dict){};
    void add(const Word& word);

private:
    UserDecision ask_user(std::string error_word,
                          std::vector<std::string>& options);
};

#endif // SRC__PROCESSING__HUNSPELL_FIXER_HPP
