#include "utils.h"
#include <sstream>
#include "colors.h"

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
    static_assert(color::lower_bound < color::upper_bound);
    static_assert(0 <= color::lower_bound <= 255);
    static_assert(0 <= color::upper_bound <= 255);

    std::stringstream ss;

    for (int i = 0; i < 3; ++i) {
        // [color::lower_bound, color::upper_bound)
        int c = color::lower_bound + rand() % (color::upper_bound - color::lower_bound + 1);
        if (c < 16) {
            ss << '0';
        }
        ss << std::uppercase << std::hex << c;
    }
    return ss.str();
}
