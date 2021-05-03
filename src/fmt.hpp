#ifndef FMT_HPP
#define FMT_HPP

#include <string>

namespace fmt {
    std::string header(std::string const & text);
    std::string item(unsigned int depth, std::string const & text);
    std::string item(std::string const & text);
    std::string result(std::string const & text);
    std::string warning(std::string const & text);
    std::string error(std::string const & text);
}

#endif
