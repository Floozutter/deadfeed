#include "log.hpp"
#include <string>

std::string header(std::string const & text) {   
    return text + "...";
}

std::string item(unsigned int depth, std::string const & text) {
    return std::string(2 * depth - 1, '-') + " " + text;
}

std::string item(std::string const & text) {
    return item(1, text);
}

std::string result(std::string const & text) {
    return text + ".";
}

std::string warning(std::string const & text) {
    return "warning: " + text + "!";
}

std::string error(std::string const & text) {
    return "error: " + text + "!";
}
