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

#include "run_config.hpp"
#include "log.hpp"

#include <iterator>
#include <sstream>

bool RunConfig::validate()
{
    bool ret = true;

    if(interactive && (file.size() == 0))
    {
        ret = false;
    }

    return ret;
}

bool RunConfig::add_filter(const std::vector<std::string>& filters)
{
    bool ret = true;
    for(const std::string& s : filters)
    {
        FilterSpecification spec;
        std::istringstream iss(s);
        std::vector<std::string> tokens(
            (std::istream_iterator<std::string>(iss)),
            std::istream_iterator<std::string>());
        for(std::string& t : tokens)
        {
            if(t == "\\n")
            {
                t = "\n";
			}
        }
        if(tokens.size() >= 2)
        {
            spec.begin = tokens[0];
            spec.end   = tokens[1];
            if(tokens.size() >= 3)
            {
                if(tokens[2] == "!")
                {
                    spec.inverted = true;
                }
            }
        }
        else
        {
            ret = false;
            break;
        }
        filter.push_back(spec);
    }
    return ret;
}
