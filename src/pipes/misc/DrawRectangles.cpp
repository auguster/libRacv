/*
 * Copyright (c) 2011 Rémi AUGUSTE
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * Contact: Rémi Auguste <remi.auguste@gmail.com>
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
