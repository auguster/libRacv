/*
 * Track.hpp
 *
 *  Created on: 28 oct. 2011
 *      Author: foloex
 */

#ifndef TRACK_HPP_
#define TRACK_HPP_

#include "Pipe.hpp"

namespace racv {

class Track: public racv::Pipe {
private:
	void processingSingleFrame(cv::Mat *image, cv::Mat *data);
	cv::Mat *image;
	cv::Rect *ROI;
public:
	Track(cv::Mat *image, cv::Rect *toTrack);
	cv::Mat *getImage();
	cv::Rect *getROI();
	virtual ~Track();
};

} /* namespace racv */
#endif /* TRACK_HPP_ */
