#include <opencv2/imgproc.hpp>
#include <opencv2/core.hpp>
#include <bitset>

void downsample(cv::Mat & mat, unsigned int scale) {
    if (scale <= 1) { return; }
    cv::resize(mat, mat, cv::Size(), 1.0/scale, 1.0/scale, cv::INTER_AREA);
    cv::resize(mat, mat, cv::Size(), scale, scale, cv::INTER_NEAREST);
}

void negate(cv::Mat & mat, std::bitset<3> const & channels) {
    for (auto it = mat.begin<cv::Vec3b>(); it != mat.end<cv::Vec3b>(); ++it) {
        for (char c = 0; c < 3; ++c) {
            if (channels[c]) {
                (*it)[c] = 255 - (*it)[c];
            }
        }
    }
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
