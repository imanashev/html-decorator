#include <sstream>
#include "utils.h"

std::string paint(const std::string &token, const std::string &color)
{
    return "<font color=" + color + '>' + token + "</font>";
}

std::string randPaint(const std::string &token)
{
    return paint(token, randColor());
}

std::string randColor()
{
    std::stringstream ss;
    ss << std::uppercase << std::hex << rand() % 180;
    ss << std::uppercase << std::hex << rand() % 180;
    ss << std::uppercase << std::hex << rand() % 180;
    return ss.str();
}