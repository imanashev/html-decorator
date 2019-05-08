#pragma once
#include "ihtml_decorator.h"

class HTMLEscaper: public IHTMLDecorator {
public:
    explicit HTMLEscaper(IHTMLDecorator *inner);

    std::string &process(std::string &str) override;

private:
    std::shared_ptr<IHTMLDecorator> wrapper;
};