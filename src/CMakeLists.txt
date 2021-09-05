add_executable(cspl
	main.cpp
	cspl.hpp                           cspl.cpp
	run_config.hpp                     run_config.cpp
	processing/stdio_source.hpp        processing/stdio_source.cpp
	processing/file_source.hpp         processing/file_source.cpp
	processing/char_filter.hpp         processing/char_filter.cpp
	processing/file_sink.hpp
	processing/filter_buffer.hpp       processing/filter_buffer.cpp
	processing/common.hpp
	processing/word_converter.hpp      processing/word_converter.cpp
	processing/hunspell_checker.hpp    processing/hunspell_checker.cpp
	processing/hunspell_fixer.hpp      processing/hunspell_fixer.cpp
	dictionary/custom_dictionary.hpp   dictionary/custom_dictionary.cpp
	dictionary/dictionary.hpp          dictionary/dictionary.cpp
)
set_property(TARGET cspl PROPERTY CXX_STANDARD 17)
target_link_libraries(cspl hunspell clipp)
if (NOT CMAKE_CXX_COMPILER_VERSION VERSION_GREATER 8.0)
	target_link_libraries(cspl -lstdc++fs)
endif()
install(TARGETS cspl RUNTIME DESTINATION /usr/bin)