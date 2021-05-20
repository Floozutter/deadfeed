#include "args.hpp"
#include <string>
#include <string_view>
#include <vector>
#include <set>
#include <utility>

args::Args::Args(int argc, char const * const argv[]) {
    // separate arguments into keyword and positional
    std::set<std::string_view> keywords{};
    std::vector<std::string_view> positionals{};
    for (auto const & arg : std::vector<std::string_view>{argv, argv + argc}) {
        if (arg.rfind('-', 0) == 0) {
            keywords.insert(arg);
        } else {
            positionals.push_back(arg);
        }
    }
    // handle keyword arguments
    auto const & keyword_exists = [
        &keywords = std::as_const(keywords)
    ] (auto const & kwarg) -> bool {
        return keywords.find(kwarg) != keywords.end();
    };
    this->ansi = !keyword_exists("--noansi");
    // handle positional arguments
    auto const & positional_at = [
        &positionals = std::as_const(positionals)
    ] (auto const & index) -> std::string_view {
        if (index < positionals.size()) {
            return positionals.at(index);
        } else {
            return "";
        }
    };
    this->prog = positional_at(0);
    this->filename = positional_at(1);
}
