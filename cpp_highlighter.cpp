#include "cpp_highlighter.h"
#include <iostream>
#include <set>
#include "colors.h"
#include "utils.h"

CPPHighlighter::CPPHighlighter(IHTMLDecorator *inner) :
    wrapper(inner)
{};

std::string &CPPHighlighter::process(std::string &str)
{
    std::cout << "CPPHighlight process" << std::endl;

    source.swap(str);
    start = 0;
    current = 0;
    line = 1;
    level = 0;
    colorsTable.clear();
    colorsTable.emplace_back();

    scanTokens();

    str.swap(output);
    return wrapper->process(str);
}

void CPPHighlighter::scanTokens()
{
    while (!isEnd()) {
        start = current;
        scanToken();
    }
}

void CPPHighlighter::scanToken() {
    char c = advance();
    switch (c) {
        case '(':
        case ')':
        case ',':
        case '.':
        case '-':
        case '+':
        case '*':
        case '!':
        case '=':
        case '<':
        case '>':
        case ':':
        case '#':
        case '|':
        case '&':
        case ' ':
        case '\r':
        case '\t':
        case '\\':
            output += c;
            break;
        case '\n':
            ++line;
            output += c;
            break;
        case ';':
            output += paint(";", color::keyword);
            break;
        case '{':
            ++level;
            colorsTable.emplace_back();
            output += c;
            break;
        case '}':
            --level;
            colorsTable.pop_back();
            output += c;
            break;
        case '/':
            if (match('/')) {
                skipComment();
            } else if (match('*')) {
                skipMultilineComment();
            } else {
                output += c;
            }
            break;
        case '\'':
        case '"':
            string();
            break;

        default:
            if (isDigit(c)) {
                number();
            } else if (isAlpha(c)) {
                identifier();
            } else {
                std::cout << "Unexpected character" << c << std::endl;
                break;
            }
    }
}

void CPPHighlighter::string()
{
    while ((peek() != '"' && peek() != '\'') && !isEnd()) {
        if (peek() == '\n') {
            ++line;
        }
        advance();
    }

    // отсутствует закрывающая '"'
    if (isEnd()) {
        std::cout << "Unterminated string" << std::endl;;
        return;
    }

    // пропускаем закрывающую '"'
    advance();

    output += paint(source.substr(start, current - start), color::string);
}

void CPPHighlighter::number()
{
    while (isDigit(peek())) {
        advance();
    }

    if (peek() == '.' && isDigit(peekNext())) {
        // пропускаем '.'
        advance();

        while (isDigit(peek())) {
            advance();
        }
    }

    output += paint(source.substr(start, current - start), color::number);
}

void CPPHighlighter::identifier()
{
    while (isAlphaNumeric(peek())) {
        advance();
    }

    // идентификатор может являться ключевым словом
    std::string identifier = source.substr(start, current - start);
    if (isKeyword(identifier)) {
        output += paint(identifier, color::keyword);
    } else {
        auto res = colorsTable.at(level).emplace(identifier, randColor());
        output += paint(identifier, res.first->second);
    }
}

void CPPHighlighter::skipComment()
{
    while (peek() != '\n' && !isEnd()) {
        peek();
        advance();
    }
    output += paint(source.substr(start, current - start), color::comment);
}

void CPPHighlighter::skipMultilineComment()
{
    while ((peek() != '*' || peekNext() != '/') && !isEnd()) {
        if (peek() == '\n') {
            ++line;
        }
        advance();
    }

    if (isEnd()) {
        std::cout << "Unterminated comment" << std::endl;
    } else {
        // пропускаем поселовательность '*/'
        advance();
        advance();
    }
    output += paint(source.substr(start, current - start), color::comment);
}

bool CPPHighlighter::match(char expected)
{
    if (isEnd()) {
        return false;
    }
    if (source.at(current) != expected) {
        return false;
    }

    current++;
    return true;
}

char CPPHighlighter::peek()
{
    if (isEnd()) {
        return '\0';
    }
    return source.at(current);
}

char CPPHighlighter::peekNext()
{
    if (current + 1 >= source.length()) {
        return '\0';
    }
    return source.at(current + 1);
}

bool CPPHighlighter::isDigit(char c)
{
    return c >= '0' && c <= '9';
}

bool CPPHighlighter::isAlpha(char c)
{
    return (c >= 'a' && c <= 'z') ||
           (c >= 'A' && c <= 'Z') ||
           c == '_';
}

bool CPPHighlighter::isAlphaNumeric(char c)
{
    return isAlpha(c) || isDigit(c);
}

bool CPPHighlighter::isEnd()
{
    return current >= source.length();
}

char CPPHighlighter::advance()
{
    current++;
    return source.at(current - 1);
}

bool CPPHighlighter::isKeyword(std::string &str)
{
    static const std::set<std::string> keywords {
        "alignas", "alignof", "and", "and_eq", "asm", "auto", "bitand", "bitor", "bool", "break",
        "case", "catch", "char", "char16_t", "char32_t", "class", "compl", "const", "constexpr", "const_cast",
        "continue", "decltype", "default", "delete", "do", "double", "dynamic_cast", "else", "enum", "explicit",
        "export", "extern", "false", "float", "for", "friend", "goto", "if", "inline", "int",
        "long", "mutable", "namespace", "new", "noexcept", "not", "not_eq", "nullptr", "operator", "or",
        "or_eq", "private", "protected", "public", "register", "reinterpret_cast", "return", "short", "signed",
        "sizeof", "static", "static_assert", "static_cast", "struct", "switch", "template", "this",
        "thread_local", "throw", "true", "try", "typedef", "typeid", "typename", "union", "unsigned", "using",
        "virtual", "void", "volatile", "wchar_t", "while", "xor", "xor_eq", ";"
    };

    return keywords.find(str) != keywords.end();
}
