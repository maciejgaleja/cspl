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

#include "processing/char_filter.hpp"
#include "processing/file_source.hpp"
#include "processing/hunspell_checker.hpp"
#include "processing/hunspell_fixer.hpp"
#include "processing/stdio_sink.hpp"
#include "processing/word_converter.hpp"

#include "dictionary/dictionary.hpp"

#include <hunspell.hxx>

    using std::make_shared;
using std::shared_ptr;

int main(int argc, char** argv)
{
    Hunspell hs("C:\\Hunspell\\en_US.aff", "C:\\Hunspell\\en_US.dic");
    Dictionary dict(hs, "en_US", ".");

    FileSource source(argv[1]);
    shared_ptr<CharFilter> filter = make_shared<CharFilter>();
    source.add_sink(filter);
    shared_ptr<WordConverter> conv = make_shared<WordConverter>();
    filter->add_match_sink(conv);
    shared_ptr<StdioSink> sink = make_shared<StdioSink>();
    conv->add_char_sink(sink);
    shared_ptr<HunspellFixer> h_fix = make_shared<HunspellFixer>(dict);
    conv->add_word_sink(h_fix);
    h_fix->add_word_sink(sink);
    while(source.next())
    {
    }
    sink->flush();
}
