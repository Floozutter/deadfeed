#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>

using namespace cv;

constexpr unsigned int SCALE = 8;

int main(int argc, char** argv) {
	if (argc < 2) { 
		std::cout << "Please enter a filename argument!" << std::endl;
		return 1;
	}
	VideoCapture cap;
	cap.open(argv[1]);
	if (!cap.isOpened()) {
		std::cout << "Error! Could not open capture." << std::endl;
		return 1;
	}
	Mat frameIn;
	Mat frameOut;
	while (true) {
		cap.read(frameIn);
		if (frameIn.empty()) {
			std::cout << "Error! Empty frame." << std::endl;
			break;
		}
		resize(frameIn, frameOut, Size(), 1.0/SCALE, 1.0/SCALE, INTER_AREA);
		resize(frameOut, frameOut, Size(), SCALE, SCALE, INTER_NEAREST);
		imshow("Live", frameOut);
		if (waitKey(5) >= 0) {
			break;
		}
	}
	return 0;
}
