#include "config.hpp"
#include "trans.hpp"
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/core.hpp>
#include <iostream>
#include <variant>

void trans_by_config(cv::Mat & mat, Config const & cfg);

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
        trans_by_config(frame, cfg);
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

void trans_by_config(cv::Mat & mat, Config const & cfg) {
    downsample(mat, cfg.downsample_scale);
    negate(mat, cfg.negate);
    quantize(mat, cfg.range_per_channel);
}
