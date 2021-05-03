#include "fmt.hpp"
#include <string>

std::string fmt::header(std::string const & text) {   
    return text + "...";
}

std::string fmt::item(unsigned int depth, std::string const & text) {
    return std::string(2 * depth - 1, '-') + " " + text;
}

std::string fmt::item(std::string const & text) {
    return item(1, text);
}

std::string fmt::result(std::string const & text) {
    return text + ".";
}

std::string fmt::warning(std::string const & text) {
    return "warning: " + text + "!";
}

std::string fmt::error(std::string const & text) {
    return "error: " + text + "!";
}
