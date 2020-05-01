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

#ifndef SRC__RUN_CONFIG_HPP
#define SRC__RUN_CONFIG_HPP

#include <string>
#include <vector>

struct FilterSpecification
{
    std::string begin = "";
    std::string end   = "";
    bool inverted     = false;
};

class RunConfig
{
public:
    enum class OpMode
    {
        CHECK,
        CREATE,
        ADD
    };

	OpMode mode;
    std::string language = "en_US";
    std::string file = "";
    bool interactive = false;
    std::vector<std::string> words_to_add;

	std::vector<FilterSpecification> filter;

    bool validate();
    bool add_filter(const std::vector<std::string> &filters);
};

#endif // SRC__RUN_CONFIG_HPP
