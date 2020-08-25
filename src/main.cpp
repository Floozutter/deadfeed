#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <string>

using namespace cv;

int main(int argc, char** argv) {
	if (argc < 2) {
		std::cout << "Please enter a filename argument!" << std::endl;
		return 1;
	}
	VideoCapture cap;
	cap.open(std::string(argv[1]));
	if (!cap.isOpened()) {
		std::cout << "Error! Could not open capture." << std::endl;
		return 1;
	}
	Mat frame;
	while (true) {
		cap.read(frame);
		if (frame.empty()) {
			std::cout << "Error! Empty frame." << std::endl;
			break;
		}
		imshow("Live", frame);
		if (waitKey(5) >= 0) {
			break;
		}
	}
	return 0;
}
