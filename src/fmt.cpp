#include "fmt.hpp"
#include <string>

namespace {
    bool ansi{false};
    std::string reset() { return ansi ? "\033[39;49m" : std::string{}; }
    std::string red() { return ansi ? "\033[31m" : std::string{}; }
    std::string green() { return ansi ? "\033[32m" : std::string{}; }
    std::string yellow() { return ansi ? "\033[33m" : std::string{}; }
}

void fmt::init_ansi() {
    ansi = true;
}

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
    return yellow() + "warning: " + text + "!" + reset();
}

std::string fmt::error(std::string const & text) {
    return red() + "error: " + text + "!" + reset();
}
