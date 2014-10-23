#ifndef SKINPROP_HPP_
#define SKINPROP_HPP_

#include <opencv2/core/core.hpp>

namespace racv
{
	/**
	 * Returns the proportion of skin color in the image
	 */
	double skinprop(const cv::Mat &image);

}

#endif /* SKINPROP_HPP_ */
