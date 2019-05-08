#include "line_adder.h"
#include <iostream>
#include <sstream>
#include <iomanip>
#include "utils.h"
#include "colors.h"

LineAdder::LineAdder(IHTMLDecorator *inner) :
    wrapper(inner)
{};

std::string &LineAdder::process(std::string &str)
{
    std::cout << "LineAdder process" << std::endl;

    int i = 0;
    size_t start_pos = 0;
    std::string from {"\n"};
    std::string to;
    std::stringstream buffer;

    auto generateBuffer = [&] () {
        buffer << std::right << std::setw(6) <<  std::to_string(++i)+ '|';
    };

    auto clearBuffer = [&] () {
        std::stringstream().swap(buffer);
    };

    // first line
    generateBuffer();
    to = paint(buffer.str(), color::lines);
    clearBuffer();
    str.insert(0, to);

    while((start_pos = str.find(from, start_pos)) != std::string::npos) {
        generateBuffer();
        to = '\n' + paint(buffer.str(), color::lines);
        clearBuffer();

        str.replace(start_pos, from.length(), to);
        start_pos += to.length();
    }

    return wrapper->process(str);
}
