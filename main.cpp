#include <iostream>
#include <fstream>
#include "html_wrapper.h"
#include "html_escaper.h"
#include "cpp_highlighter.h"
#include "line_adder.h"

int main() {
    CPPHighlighter obj(new LineAdder(new HTMLWrapper()));

    std::ifstream input;
    input.open ("../main.cpp");
    std::string cpp_code;
    std::string buffer;

    while(!input.eof()) {
        getline(input, buffer);
        cpp_code += buffer + '\n';
    }
    input.close();

    // std::string cpp_code{"If Boost was built using the boost-cmake project it provides a package configuration file"};

    /*
     * Multiline
     * comment
     */

    int a = 50 + 4000.3;
    srand(time(nullptr));

    std::string html_code = obj.process(cpp_code);

    std:: cout << "\nWrapped code:\n" << html_code << std::endl;

    std::ofstream output;
    output.open ("example.html");
    output << html_code;
    output.close();

    return 0;
}
