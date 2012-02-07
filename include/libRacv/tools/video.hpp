/*
 * video.hpp
 *
 *  Created on: 22 sept. 2011
 *      Author: remi
 */

#ifndef VIDEO_HPP_
#define VIDEO_HPP_

#include <opencv2/highgui/highgui.hpp>

namespace racv {

	/**
	 * When CV_CAP_PROP_FRAME_COUNT fails to retrieve de number of frames ...
	 */
	int frameCounter(cv::VideoCapture &capture);

}

#endif /* VIDEO_HPP_ */
