#include "cpp_highlighter.h"
#include <iostream>
#include <set>
#include <regex>
#include <map>
#include <boost/tokenizer.hpp>
#include "colors.h"
#include "utils.h"

CPPHighlighter::CPPHighlighter(IHTMLDecorator *inner) :
    wrapper(inner)
{};

std::string &CPPHighlighter::process(std::string &str)
{
    std::cout << "CPPHighlight process" << std::endl;

    boost::char_separator<char> sep("", " ,\n*&;:<>(){}[]", boost::keep_empty_tokens);
    boost::tokenizer<boost::char_separator<char>> tokens(str, sep);

    int lvl = 0;
    std::vector<std::map<std::string, std::string>> colorsTable;
    colorsTable.emplace_back();

    std::string new_str;
    for (auto& t : tokens) {
        if(isKeyword(t)) {
            new_str += paint(t, color::keyword);

        } else if (isOpenBracket(t)) {
            ++lvl;
            colorsTable.emplace_back();
            new_str += '{';

        } else if (isCloseBracket(t)) {
            --lvl;
            colorsTable.pop_back();
            new_str += '}';

        } else {
            auto res = colorsTable.at(lvl).emplace(t, randColor());
            new_str += paint(t, res.first->second);
//            new_str += t;
        }
        std::cout << t << std::endl;
    }
    str.swap(new_str);

    return wrapper->process(str);
}

bool CPPHighlighter::isKeyword(const std::string &str) const
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

bool CPPHighlighter::isOpenBracket(const std::string &str) const
{
    static const std::string v{"{"};
    return str == v;
}

bool CPPHighlighter::isCloseBracket(const std::string &str) const
{
    static const std::string v{"}"};
    return str == v;
}
