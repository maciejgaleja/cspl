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

#include <iostream>

#include "cspl.hpp"

#include "processing/char_filter.hpp"
#include "processing/file_sink.hpp"
#include "processing/file_source.hpp"
#include "processing/hunspell_checker.hpp"
#include "processing/hunspell_fixer.hpp"
#include "processing/item_iterator.hpp"
#include "processing/stdio_source.hpp"
#include "processing/word_converter.hpp"

#include "dictionary/dictionary.hpp"

#include "log.hpp"

#include <hunspell.hxx>

using std::make_shared;
using std::shared_ptr;
using std::vector;

int cspl_check(RunConfig& cfg, Dictionary& dict)
{
    shared_ptr<ItemIterator<Char>> source;
    if(cfg.file.size() > 0)
    {
        source = make_shared<FileSource>(cfg.file);
    }
    else
    {
        source = make_shared<StdioSource>();
    }

    shared_ptr<WordConverter> conv = make_shared<WordConverter>();

    shared_ptr<FileSink> sink;
    if(cfg.interactive && (cfg.file.size() > 0))
    {
        sink = make_shared<FileSink>(cfg.file);
        conv->add_char_sink(sink);
    }

    vector<shared_ptr<CharFilter>> filters;
    if(cfg.filter.size() == 0)
    {
        source->add_sink(conv);
    }
    else
    {
        shared_ptr<CharFilter> src;
        for(auto it = cfg.filter.begin(); it != cfg.filter.end(); ++it)
        {
            auto spec = *it;
            auto filter =
                make_shared<CharFilter>(spec.begin, spec.end, spec.inverted);
            filters.push_back(filter);
            if(src)
            {
                src->add_unmatch_sink(filter);
            }
            else
            {
                source->add_sink(filter);
            }
            filter->add_match_sink(conv);
            src = filter;
        }
        if(sink)
        {
            log << "Last filter will write to sink\n";
            filters.back()->add_unmatch_sink(sink);
        }
    }

    shared_ptr<HunspellChecker> checker;
    if(cfg.interactive)
    {
        checker = make_shared<HunspellFixer>(dict);
    }
    else
    {
        checker = make_shared<HunspellChecker>(dict);
    }
    if(sink)
    {
        checker->add_sink(sink);
    }
    conv->add_word_sink(checker);

    while(source->next())
    {
    }
    source.reset();

    if(sink)
    {
        sink->flush();
    }

    int ret = checker->errors().size() > 0;
    if(cfg.interactive)
    {
        ret = 0;
    }
    else
    {
        for(const auto& w : checker->errors())
        {
            std::cout << w << "\n";
        }
    }
    return ret;
}

int cspl_add(RunConfig& cfg, Dictionary& dict)
{
    int ret = 0;

    for(const Word& w : cfg.words_to_add)
    {
        dict.add(w);
    }

    return ret;
}

int cspl(RunConfig& cfg)
{
    int ret = 0;
    Hunspell hs("C:\\Hunspell\\en_US.aff", "C:\\Hunspell\\en_US.dic");
    Dictionary dict(hs, cfg.language, ".");

    switch(cfg.mode)
    {
    case RunConfig::OpMode::CHECK:
        ret = cspl_check(cfg, dict);
        break;
    case RunConfig::OpMode::CREATE:
        break;
    case RunConfig::OpMode::ADD:
        ret = cspl_add(cfg, dict);
        break;
    default:
        break;
    }
    return ret;
}