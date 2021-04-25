#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/core.hpp>
#include <fstream>
#include <iostream>
#include <string>
#include <map>
#include <algorithm>
#include <variant>

struct Config {
    std::variant<int, std::string> feed{0};
    unsigned int downsample_scale{1};
    unsigned int range_per_channel{256};
    static Config from_map(std::map<std::string, std::string> const & map, std::ostream & log) {
        log << "initializing config from map..." << std::endl;
        //auto const & init_from_key = [&map](std::string const & key, auto & speak] -> void {}
        Config cfg{};
        {
            auto const & it = map.find("downsample_scale");
            if (it != map.end()) {
                cfg.downsample_scale = std::stoi(it->second);
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
    static Config from_text(std::istream & text, std::ostream & log) {
        log << "reading config map from text stream..." << std::endl;
        std::map<std::string, std::string> map{};
        for (std::string line; std::getline(text, line);) {
            auto const & partition = line.find("=");
            if (partition == std::string::npos) {
                log << "- warning: no delimiter found!" << std::endl;
            } else {
                std::string const & key{line.substr(0, partition)};
                std::string const & value{line.substr(partition + 1)};
                log << "- read key-value pair `" << key << "`, `" << value << "`." << std::endl;
                map.insert({key, value});
            }
        }
        return Config::from_map(map, log);
    }
    static Config from_file(std::string const & filename, std::ostream & log) {
        log << "opening config file `" << filename << "` as text stream..." << std::endl;
        std::ifstream ifile{filename};
        if (ifile) {
            return Config::from_text(ifile, log);
        } else {
            log << "error: can't open file!" << std::endl;
            return Config{};
        }
    }
};

void downsample(cv::Mat & mat, unsigned int scale) {
    if (scale <= 1) { return; }
    cv::resize(mat, mat, cv::Size(), 1.0/scale, 1.0/scale, cv::INTER_AREA);
    cv::resize(mat, mat, cv::Size(), scale, scale, cv::INTER_NEAREST);
}

void quantize(cv::Mat & mat, unsigned int range_per_channel) {
    if (range_per_channel <= 1) { return; }
    unsigned int const divisor{256 / range_per_channel};
    unsigned int const factor{255 / (range_per_channel - 1)};
    unsigned int const max_index{range_per_channel - 1};
    for (auto it = mat.begin<cv::Vec3b>(); it != mat.end<cv::Vec3b>(); ++it) {
        for (char c = 0; c < 3; ++c) {
            (*it)[c] = factor * std::min((*it)[c] / divisor, max_index);
        }
    }
}

int main(int argc, char * argv[]) {
    // get config
    if (argc < 2) {
        std::cerr << "error: no config filename argument!" << std::endl;
        return 1;
    }
    Config cfg{Config::from_file(argv[1], std::cout)};
    std::cout << std::endl;
    // open feed
    cv::VideoCapture cap;
    if (std::holds_alternative<int>(cfg.feed)) {
        cap.open(std::get<int>(cfg.feed));
    } else {
        cap.open(std::get<std::string>(cfg.feed));
    }
    if (!cap.isOpened()) {
        std::cerr << "error: can't open capture!" << std::endl;
        return 1;
    }
    // enter loop
    while (true) {
        // get frame
        cv::Mat frame;
        cap.read(frame);
        if (frame.empty()) {
            std::cerr << "error: empty frame!" << std::endl;
            break;
        }
        // transform frame
        downsample(frame, cfg.downsample_scale);
        quantize(frame, cfg.range_per_channel);
        // show frame
        cv::imshow("deadfeed", frame);
        // handle key events
        int key{cv::waitKey(5)};
        if (key == 27) {
            break;
        } else if (key == 'r') {
            // reload config
            cfg = Config::from_file(argv[1], std::cout);
            std::cout << std::endl;
        }

    }
    return 0;
}
