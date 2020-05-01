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

#include <clipp.h>

#include <iostream>

#include "cspl.hpp"

using clipp::command;
using clipp::make_man_page;
using clipp::option;
using clipp::parse;
using clipp::repeatable;
using clipp::usage_lines;
using clipp::value;
using clipp::values;
using clipp::opt_values;

using std::cout;

enum class OpMode
{
	CHECK, CREATE
};

int main(int argc, char** argv)
{
    int ret = -1;
    std::vector<std::string> filter_strings;
    
	OpMode mode;

    RunConfig cfg;
    auto cli_check =
        (option("-i", "--interactive")
             .doc("fix errors interactively")
             .set(cfg.interactive),
         repeatable(
             option("-x", "--filter")
                 .doc("filter only words matching filter specification") &
             opt_values("spec", filter_strings)),
         (option("-f", "--file") &value("file", cfg.file).doc("input file")));

	auto cli_create = (command("create")
                           .doc("create dictionary")
                           .set(mode, OpMode::CREATE))&
         (option("-l", "--language").doc("select language") & value("language").set(cfg.language));
    

    auto cli = (command("check").doc("check spelling").set(mode, OpMode::CHECK) & cli_check) |
       cli_create;

    if(parse(argc, argv, cli))
    {
        switch(mode)
        {
        case OpMode::CHECK:
            if(cfg.add_filter(filter_strings) && cfg.validate())
            {
                ret = cspl(cfg);
            }
            break;
        case OpMode::CREATE:
            cout << "Will create dictionary here\n";
            break;
        default:
            break;
        }
    }
    else
    {
        cout << make_man_page(cli, argv[0]) << '\n';
    }
    return ret;
}
