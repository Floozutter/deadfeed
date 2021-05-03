#include "fmt.hpp"
#include <string>

std::string const DEFAULT{"\033[39;49m"};
std::string const RED{"\033[31m"};
std::string const GREEN{"\033[32m"};
std::string const YELLOW{"\033[33m"};

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
    return YELLOW + "warning: " + text + "!" + DEFAULT;
}

std::string fmt::error(std::string const & text) {
    return RED + "error: " + text + "!" + DEFAULT;
}
