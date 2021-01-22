#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <string>

const unsigned int DEFAULT_SCALE = 4;

int main(int argc, char * argv[]) {
    if (argc < 2) { 
        std::cout << "error: no filename argument!" << std::endl;
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
        std::cout << "error: can't open capture!" << std::endl;
        return 1;
    }
    cv::Mat frameIn;
    cv::Mat frameOut;
    while (true) {
        cap.read(frameIn);
        if (frameIn.empty()) {
            std::cout << "error: empty frame!" << std::endl;
            break;
        }
        cv::resize(frameIn, frameOut, cv::Size(), 1.0/scale, 1.0/scale, cv::INTER_AREA);
        cv::resize(frameOut, frameOut, cv::Size(), scale, scale, cv::INTER_NEAREST);
        cv::imshow("camfx", frameOut);
        if (cv::waitKey(5) >= 0) {
            break;
        }
    }
    return 0;
}
