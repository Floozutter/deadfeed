#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <iostream>
#include <map>
#include <string>
#include <bitset>
#include <variant>

struct Config {
    std::variant<int, std::string> feed{0};
    unsigned int width{0};
    unsigned int height{0};
    unsigned int downsample_scale{1};
    std::bitset<3> negate{0};
    unsigned int range_per_channel{256};
    static Config from_map(std::map<std::string, std::string> const & map, std::ostream & log);
    static Config from_text(std::istream & text, std::ostream & log);
    static Config from_file(std::string const & filename, std::ostream & log);
};

#endif
