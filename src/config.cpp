#include "config.hpp"
#include "fmt.hpp"
#include <fstream>
#include <iostream>
#include <map>
#include <string>

Config Config::from_map(std::map<std::string, std::string> const & map, std::ostream & log) {
    log << fmt::header("initializing config from map") << std::endl;
    Config cfg{};
    {
        auto const & it = map.find("feed");
        if (it != map.end()) {
            try {
                cfg.feed = std::stoi(it->second);
            } catch (...) {
                cfg.feed = it->second;
            }
        }
    }
    {
        auto const & it = map.find("width");
        if (it != map.end()) {
            cfg.width = std::stoi(it->second);
        }
    }
    {
        auto const & it = map.find("height");
        if (it != map.end()) {
            cfg.height = std::stoi(it->second);
        }
    }
    {
        auto const & it = map.find("downsample_scale");
        if (it != map.end()) {
            cfg.downsample_scale = std::stoi(it->second);
        }
    }
    {
        auto const & it = map.find("negate");
        if (it != map.end()) {
            cfg.negate = std::stoi(it->second);
        }
    }
    {
        auto const & it = map.find("range_per_channel");
        if (it != map.end()) {
            cfg.range_per_channel = std::stoi(it->second);
        }

    }
    return cfg;
}

Config Config::from_text(std::istream & text, std::ostream & log) {
    log << fmt::header("reading config map from text stream") << std::endl;
    std::map<std::string, std::string> map{};
    for (std::string line; std::getline(text, line);) {
        auto const & partition = line.find("=");
        if (partition == std::string::npos) {
            log << fmt::item(fmt::warning("no delimiter found")) << std::endl;
        } else {
            std::string const & key{line.substr(0, partition)};
            std::string const & value{line.substr(partition + 1)};
            log << fmt::item(fmt::result("read key-value pair `" + key + "`, `" + value + "`"))
                << std::endl;
            map.insert({key, value});
        }
    }
    return Config::from_map(map, log);
}

Config Config::from_file(std::string const & filename, std::ostream & log) {
    log << fmt::header("opening config file `" + filename + "` as text stream") << std::endl;
    std::ifstream ifile{filename};
    if (ifile) {
        return Config::from_text(ifile, log);
    } else {
        log << fmt::error("can't open file") << std::endl;
        return Config{};
    }
}
