#include <iostream>
#include <regex>
#include <fstream>
#include "html_wrapper.h"
#include "html_escaper.h"
#include "cpp_highlighter.h"
#include "line_adder.h"

int main() {
#include "utils.h"
    srand(time(nullptr));

    std::cout << randColor() << std::endl;

//    HTMLEscaper obj(new CPPHighlighter(new LineAdder(new HTMLWrapper())));
    CPPHighlighter obj(new LineAdder(new HTMLWrapper()));


//    std::string cpp_code{R"***(
//#pragma once
//#include "html_wrapper.h"
//#include <iostream>
//
//class HTMLEscaper: public IHTMLDecorator {
//public:
//    HTMLEscaper(IHTMLDecorator *inner);
//
//    std::string &process(std::string &str) override;
//
//private:
//    std::shared_ptr<IHTMLDecorator> wrapper;
//};
//)***"};

    std::ifstream input;
    input.open ("../main.cpp");
    std::string cpp_code{""};
    std::string buffer;

    while(!input.eof()) {
        getline(input, buffer);
        cpp_code += buffer + '\n';
    }

    while (input >> buffer) {
        cpp_code += buffer + '\n';
    }
    input.close();

//    std::string cpp_code{"If Boost was built using the boost-cmake project it provides a package configuration"};
//    std::string cpp_code{R"(string s = "vv { vv } { ff)"
//    };
    std::string html_code = obj.process(cpp_code);

    std:: cout << "\nWrapped code:\n" << html_code << std::endl;

    std::ofstream output;
    output.open ("example.html");
    output << html_code;
    output.close();

    return 0;
}
