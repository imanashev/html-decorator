#pragma once
#include <string>

class IHTMLDecorator {
public:
    virtual ~IHTMLDecorator() = default;
    virtual std::string &process(std::string &) = 0;
};