#include "args.hpp"
#include "config.hpp"
#include "trans.hpp"
#include "fmt.hpp"
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/core.hpp>
#include <iostream>
#include <string>
#include <variant>
#include <algorithm>

bool validate_args(args::Args const & arguments);
void trans_by_config(cv::Mat & mat, Config const & cfg);

int main(int argc, char * argv[]) {
    // handle args
    const args::Args arguments{argc, argv};
    if (arguments.ansi) { fmt::init_ansi(); }
    if (!validate_args(arguments)) { return 1; }
    // get config
    Config cfg{Config::from_file(arguments.filename, std::cout)};
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
            cfg = Config::from_file(arguments.filename, std::cout);
            std::cout << std::endl;
        }
    }
    return 0;
}

bool validate_args(args::Args const & arguments) {
    if (arguments.prog.empty()) {
        std::cout << fmt::error("missing positional arguments") << std::endl;
        return false;
    } else if (arguments.filename.empty()) {
        std::cout << fmt::error("missing <filename> positional argument") << std::endl;
        return false;
    } else {
        return true;
    }
}

void trans_by_config(cv::Mat & mat, Config const & cfg) {
    trans::resize_to(mat, cfg.width, cfg.height);
    trans::downsample(mat, cfg.downsample_scale);
    trans::negate(mat, cfg.negate);
    trans::quantize(mat, cfg.range_per_channel);
}
