#pragma once
#include "ihtml_decorator.h"

class HTMLWrapper : public IHTMLDecorator {
    std::string &process(std::string &str) override;
};
