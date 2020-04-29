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

#ifndef SRC__DICTIONARY__DICTIONARY_HPP
#define SRC__DICTIONARY__DICTIONARY_HPP

#include <filesystem>
#include <vector>

#include <hunspell.hxx>

#include "custom_dictionary.hpp"

class Dictionary
{
public:
    Dictionary(Hunspell& hs,
               const std::string& language,
               const std::string& root_path);
    ~Dictionary();
    Hunspell& hunspell()
    {
        return m_hs;
    }

    void add(Word word);

private:
    Hunspell& m_hs;
    std::vector<CustomDictionary> m_custom;
    std::vector<Word> m_added_words;

    std::vector<std::filesystem::path>
    get_parent_paths(const std::string& root_path);

    int ask_where_to_add_word(const Word& word);
};

#endif // SRC__DICTIONARY__DICTIONARY_HPP
