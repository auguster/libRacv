/*
 * DrawDetections.cpp
 *
 *  Created on: Oct 24, 2011
 *      Author: remi
 */

#include <rectangle.hpp>

#include <pipes/DrawRectangles.hpp>

#include <opencv2/core/core.hpp>

#include <iostream>

namespace racv {

DrawRectangles::DrawRectangles() {
	// TODO Auto-generated constructor stub

}

DrawRectangles::~DrawRectangles() {
	// TODO Auto-generated destructor stub
}

void DrawRectangles::processingSingleFrame(cv::Mat *image, cv::Mat *data)
{
	std::vector<cv::Rect > *rects = racv::mat2VectRect(*data);

	for (std::vector<cv::Rect >::iterator rect = rects->begin(); rect < rects->end(); rect++)
	{
		cv::rectangle(*image, *rect, cv::Scalar(0, 255, 0), 1, 8, 0);
	}
}

} /* namespace racv */
