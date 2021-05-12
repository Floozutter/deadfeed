#include "config.hpp"
#include "trans.hpp"
#include "fmt.hpp"
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/core.hpp>
#include <iostream>
#include <string>
#include <variant>
#include <vector>
#include <algorithm>

void trans_by_config(cv::Mat & mat, Config const & cfg);

int main(int argc, char * argv[]) {
    // handle args
    std::vector<std::string> const args{argv + 1, argv + argc};
    if (std::any_of(args.begin(), args.end(), [](auto const & s){ return s == "--ansi"; })) {
        if (fmt::init_ansi()) {
            std::cout << fmt::success("enabled ANSI") << std::endl;
        } else {
            std::cout << fmt::warning("failed to enable ANSI") << std::endl;
        }
    }
    if (args.size() < 1) {  // this ain't good lol
        std::cout << fmt::error("no config filename argument") << std::endl;
        return 1;
    }
    // get config
    Config cfg{Config::from_file(args.at(0), std::cout)};
    std::cout << std::endl;
    // open feed
    cv::VideoCapture cap;
    if (std::holds_alternative<int>(cfg.feed)) {
        cap.open(std::get<int>(cfg.feed));
    } else {
        cap.open(std::get<std::string>(cfg.feed));
    }
    if (!cap.isOpened()) {
        std::cout << fmt::error("can't open capture") << std::endl;
        return 1;
    }
    // enter loop
    while (true) {
        // get frame
        cv::Mat frame;
        cap.read(frame);
        if (frame.empty()) {
            std::cout << fmt::error("empty frame") << std::endl;
        } else {
            // transform frame
            trans_by_config(frame, cfg);
            // show frame
            cv::imshow("deadfeed", frame);
        }
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

void trans_by_config(cv::Mat & mat, Config const & cfg) {
    downsample(mat, cfg.downsample_scale);
    negate(mat, cfg.negate);
    quantize(mat, cfg.range_per_channel);
}
