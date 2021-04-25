#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/core.hpp>
#include <iostream>
#include <string>

const unsigned int DEFAULT_SCALE = 4;

int main(int argc, char * argv[]) {
    if (argc < 2) { 
        std::cerr << "error: no filename argument!" << std::endl;
        return 1;
    }
    const unsigned int scale = argc < 3 ? DEFAULT_SCALE : std::stoi(argv[2]);
    cv::VideoCapture cap;
    if (std::string(argv[1]) == "0") {
        cap.open(0);
    } else {
        cap.open(argv[1]);
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
        cv::resize(frameIn, frameOut, cv::Size(), 1.0/scale, 1.0/scale, cv::INTER_AREA);
        cv::resize(frameOut, frameOut, cv::Size(), scale, scale, cv::INTER_NEAREST);
        // quantize colors
        for (auto it = frameOut.begin<cv::Vec3b>(); it != frameOut.end<cv::Vec3b>(); ++it) {
            for (char c = 0; c < 3; ++c) {
                (*it)[c] = ((*it)[c] / 128) * 255;
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
