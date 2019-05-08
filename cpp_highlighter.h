#pragma once
#include "ihtml_decorator.h"
#include <map>
#include <vector>

class CPPHighlighter: public IHTMLDecorator {
public:
    explicit CPPHighlighter(IHTMLDecorator *inner);

    std::string &process(std::string &str) override;

private:
    void scanTokens();

    void scanToken();

    void string();

    void number();

    void identifier();

    void skipComment();

    void skipMultilineComment();

    bool match(char expected);

    char peek();

    char peekNext();

    bool isKeyword(std::string &str);

    bool isDigit(char c);

    bool isAlpha(char c);

    bool isAlphaNumeric(char c);

    bool isEnd();

    char advance();

    std::string source;
    std::string output;
    int start;
    int current;
    int line;
    int level;
    std::vector<std::map<std::string, std::string>> colorsTable;

    std::shared_ptr<IHTMLDecorator> wrapper;
};
