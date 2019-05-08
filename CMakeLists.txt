cmake_minimum_required(VERSION 3.13)
project(html_decorator)

set(CMAKE_CXX_STANDARD 17)

add_executable(html_decorator
    main.cpp
    html_wrapper.cpp
    html_escaper.cpp
    cpp_highlighter.cpp
    line_adder.cpp
    utils.cpp)
