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

#include "hunspell_fixer.hpp"

#include <iostream>

using std::cin;
using std::cout;

void HunspellFixer::add(const Word& word)
{
    bool ok = m_dict.hunspell().spell(word.c_str());
    if(!ok)
    {
        ++m_error_count;
        auto alternatives = m_dict.hunspell().suggest(word);
        auto choice       = ask_user(word, alternatives);
        if(choice.choice == UserDecision::Choice::IGNORE)
        {
            notify_all_words(word);
        }
        else if(choice.choice == UserDecision::Choice::ADD)
        {
            m_dict.add(word);
            notify_all_words(word);
        }
        else
        {
            notify_all_words(alternatives[choice.chosen_word]);
        }
    }
    else
    {
        notify_all_words(word);
    }
}

UserDecision HunspellFixer::ask_user(std::string error_word,
                                     std::vector<std::string>& options)
{
    UserDecision ret;
    ret.choice      = UserDecision::Choice::IGNORE;
    ret.chosen_word = -1;

    cout << "----> " << error_word << " <----\n";
    int n = 1;
    for(const auto& s : options)
    {
        cout << n << ": " << s << "\n";
        ++n;
    }
    cout << "i: ignore\n";
    cout << "a: add to dictionary\n";

    std::string decision_str;
    cin >> decision_str;

    try
    {
        ret.chosen_word = std::stoi(decision_str) - 1;
        ret.choice      = UserDecision::Choice::REPLACE;
    }
    catch(const std::invalid_argument& e)
    {
        if(decision_str == "i")
            ret.choice = UserDecision::Choice::IGNORE;
        else if(decision_str == "a")
            ret.choice = UserDecision::Choice::ADD;
        else
        {
            cout << "Invalid option";
            ret = ask_user(error_word, options);
        }
    }

    return ret;
}
