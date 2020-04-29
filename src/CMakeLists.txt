add_executable(cspl 
	main.cpp
	cspl.hpp                           cspl.cpp
	run_config.hpp                     run_config.cpp
	processing/char_sink.hpp
	processing/char_source.hpp         processing/char_source.cpp
	processing/stdio_source.hpp        processing/stdio_source.cpp
	processing/file_source.hpp         processing/file_source.cpp
	processing/char_filter.hpp         processing/char_filter.cpp
	processing/file_sink.hpp
	processing/common.hpp		      
	processing/word_converter.hpp      processing/word_converter.cpp
	processing/word_source.hpp         processing/word_source.cpp
	processing/word_sink.hpp           
	processing/hunspell_checker.hpp    processing/hunspell_checker.cpp
	processing/hunspell_fixer.hpp      processing/hunspell_fixer.cpp
	dictionary/custom_dictionary.hpp   dictionary/custom_dictionary.cpp
	dictionary/dictionary.hpp          dictionary/dictionary.cpp
)
target_link_libraries(cspl hunspell clipp)
set_property(TARGET cspl PROPERTY CXX_STANDARD 17)
install(TARGETS cspl)