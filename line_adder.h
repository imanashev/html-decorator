#pragma once
#include "ihtml_decorator.h"

class LineAdder: public IHTMLDecorator {
public:
    explicit LineAdder(IHTMLDecorator *inner);

    std::string &process(std::string &str) override;

private:
    std::shared_ptr<IHTMLDecorator> wrapper;
};
