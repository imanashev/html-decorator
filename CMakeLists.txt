cmake_minimum_required(VERSION 3.13)
project(html_decorator)

set(CMAKE_CXX_STANDARD 17)

#set(Boost_USE_STATIC_LIBS        ON) # only find static libs
#set(Boost_USE_MULTITHREADED      ON)
#set(Boost_USE_STATIC_RUNTIME    OFF)
find_package(Boost 1.69.0)

add_executable(html_decorator
    main.cpp
    html_wrapper.cpp
    html_escaper.cpp
    cpp_highlighter.cpp colors.h line_adder.cpp line_adder.h utils.cpp utils.h)

include_directories(${Boost_INCLUDE_DIRS})

target_link_libraries(html_decorator
    ${Boost_LIBRARIES})