#include "html_wrapper.h"
#include <iostream>
#include "colors.h"

std::string &HTMLWrapper::process(std::string &str)
{
    std::cout << "HTMLDecorator process"<< std::endl;

    const std::string head = "<html>\n<body bgcolor=" + std::string(color::background) +
                             " text=" + std::string(color::default_text) + ">\n<pre>\n";
    const std::string tail{"\n</pre>\n</body>\n</html>\n"};

    str = head + str + tail;
    return str;
}
