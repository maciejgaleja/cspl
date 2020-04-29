add_executable(cspl cspl.cpp)
target_link_libraries(cspl hunspell)
install(TARGETS cspl)