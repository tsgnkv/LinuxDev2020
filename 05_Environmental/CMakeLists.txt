cmake_minimum_required(VERSION 3.1)

project(regexp)

find_library(CURSES ncursesw)
find_library(PCRE2-8 pcre2-8)

add_executable(regexp main.c)
target_link_libraries(regexp ${CURSES} ${PCRE2-8})

option(WITHOUT_UTF "Disable UTF in regexp" OFF)
configure_file(config.h.in config.h)

set(GENERATES regexp config.h CMakeCache.txt CMakeFiles cmake_install.cmake Makefile)

add_custom_target(allclean)
add_custom_command(
	TARGET    allclean
	COMMAND   rm -rf ${GENERATES}
)
