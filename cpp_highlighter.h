#pragma once
#include "ihtml_decorator.h"

class CPPHighlighter: public IHTMLDecorator {
public:
    explicit CPPHighlighter(IHTMLDecorator *inner);

    std::string &process(std::string &str) override;

private:
    bool isKeyword(const std::string &str) const;
    bool isOpenBracket(const std::string &str) const;
    bool isCloseBracket(const std::string &str) const;

    std::shared_ptr<IHTMLDecorator> wrapper;
};
