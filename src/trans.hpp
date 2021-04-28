#ifndef TRANS_HPP
#define TRANS_HPP

#include <opencv2/core.hpp>
#include <bitset>

void downsample(cv::Mat & mat, unsigned int scale);
void negate(cv::Mat & mat, std::bitset<3> const & channels = 7);
void quantize(cv::Mat & mat, unsigned int range_per_channel);

#endif
