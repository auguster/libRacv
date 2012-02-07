/*
 * detection.hpp
 *
 *  Created on: 11 avr. 2011
 *      Author: auguster
 */

#ifndef DETECTION_HPP_
#define DETECTION_HPP_

#include <opencv2/objdetect/objdetect.hpp>

namespace racv {

	/**
	 * This multiscale detector tries to find the same number of objects as previously in the different scale level
	 * Note: it's usually faster than detectMultiScale() but in some cases (lower number of objects it can be much slower)
	 */
	void smartDetect(cv::CascadeClassifier detector, cv::Mat &frame, std::vector<cv::Rect> &rectList);

}  // namespace racv


#endif /* DETECTION_HPP_ */
