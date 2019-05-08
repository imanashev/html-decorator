#include "html_wrapper.h"
#include <iostream>

std::string &HTMLWrapper::process(std::string &str)
{
    std::cout << "HTMLDecorator process"<< std::endl;
    static const std::string head{"<html>\n<body>\n<pre>\n"};
    static const std::string tail{"\n</pre>\n</body>\n</html>\n"};

    str = head + str + tail;
    return str;
}


