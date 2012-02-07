/*
 * DrawDetections.cpp
 *
 *  Created on: Oct 24, 2011
 *      Author: remi
 */

#include <libRacv/tools/rectangle.hpp>

#include <libRacv/pipes/misc/DrawRectangles.hpp>

#include <opencv2/core/core.hpp>

#include <iostream>

namespace racv
{

DrawRectangles::DrawRectangles() :
		debug(false)
{
}

DrawRectangles::DrawRectangles(bool value) :
		debug(value)
{
}

DrawRectangles::~DrawRectangles()
{
}

void DrawRectangles::processingSingleFrame(cv::Mat *image, cv::Mat *data)
{
	if (data)
	{
		std::vector<cv::Rect> *rects = racv::mat2VectRect(*data);

		for (std::vector<cv::Rect>::iterator rect = rects->begin();
				rect < rects->end(); rect++)
		{
			if (this->debug)
			{
				racv::showRectangle(*rect);
			}
			cv::rectangle(*image, *rect, cv::Scalar(0, 255, 0), 1, 8, 0);
		}
	}
}

} /* namespace racv */
