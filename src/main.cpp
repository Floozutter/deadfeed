#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/core.hpp>
#include <iostream>
#include <sstream>
#include <string>
#include <map>
#include <variant>

struct Config {
    std::variant<int, std::string> feed{0};
    unsigned int downsample_scale{1};
    unsigned int range_per_channel{256};
    static Config from_map(std::map<std::string, std::string> const & map, std::ostream & log) {
        log << "initializing config from map..." << std::endl;
        return Config{};
    }
    static Config from_text(std::istream & text, std::ostream & log) {
        log << "reading config map from text stream..." << std::endl;
        return Config::from_map({}, log);
    }
    static Config from_file(std::string const & filename, std::ostream & log) {
        log << "opening config file as text stream..." << std::endl;
        return Config::from_text(std::istringstream{}, log);
    }
};

int main(int argc, char * argv[]) {
    if (argc < 2) {
        std::cerr << "error: no config filename argument!" << std::endl;
        return 1;
    }
    Config const cfg{Config::from_file(argv[1], std::cout)};
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
    cv::Mat frameIn;
    cv::Mat frameOut;
    while (true) {
        // get frame
        cap.read(frameIn);
        if (frameIn.empty()) {
            std::cerr << "error: empty frame!" << std::endl;
            break;
        }
        // under-sample (?)
        cv::resize(frameIn, frameOut, cv::Size(), 1.0/cfg.downsample_scale, 1.0/cfg.downsample_scale, cv::INTER_AREA);
        cv::resize(frameOut, frameOut, cv::Size(), cfg.downsample_scale, cfg.downsample_scale, cv::INTER_NEAREST);
        // quantize colors
        for (auto it = frameOut.begin<cv::Vec3b>(); it != frameOut.end<cv::Vec3b>(); ++it) {
            for (char c = 0; c < 3; ++c) {
                (*it)[c] = ((*it)[c] / (256 / cfg.range_per_channel)) * (255 / (cfg.range_per_channel - 1));
            }
        }
        // show
        cv::imshow("deadfeed", frameOut);
        if (cv::waitKey(5) == 27) {
            break;
        }
    }
    return 0;
}
