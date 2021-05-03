#include "fmt.hpp"
#include <string>

#ifdef _WIN32
    #include <windows.h>
#endif

namespace {
    bool ansi{false};
    std::string reset() { return ansi ? "\033[39;49m" : std::string{}; }
    std::string red() { return ansi ? "\033[31m" : std::string{}; }
    std::string green() { return ansi ? "\033[32m" : std::string{}; }
    std::string yellow() { return ansi ? "\033[33m" : std::string{}; }
}

bool fmt::init_ansi() {
    #ifdef _WIN32
    {
        auto const & enable_virt = [](auto const & std_handle) -> bool {
            HANDLE handle = GetStdHandle(std_handle);
            if (handle == INVALID_HANDLE_VALUE) { return false; }
            DWORD mode{};
            if (!GetConsoleMode(handle, &mode)) { return false; }
            return SetConsoleMode(handle, mode | ENABLE_VIRTUAL_TERMINAL_PROCESSING);
        };
        if (!enable_virt(STD_OUTPUT_HANDLE)) { return false; }
        if (!enable_virt(STD_INPUT_HANDLE)) { return false; }
    }
    #endif
    ansi = true;
    return ansi;
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

std::string fmt::success(std::string const & text) {
    return green() + text + "." + reset();
}

std::string fmt::warning(std::string const & text) {
    return yellow() + "warning: " + text + "!" + reset();
}

std::string fmt::error(std::string const & text) {
    return red() + "error: " + text + "!" + reset();
}
