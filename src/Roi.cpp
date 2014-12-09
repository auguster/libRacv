/*
 * Copyright (c) 2014 Rémi AUGUSTE
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * Contact: Rémi Auguste <remi.auguste@gmail.com>
 */

#include <libRacv/Roi.hpp>

#include <libRacv/opencv/imgproc.hpp>

racv::Roi::Roi(cv::Mat image) :
		Rect(), image(image)
{
	cv::Point point;
	cv::Size size;
	image.locateROI(size, point);
	this->x = point.x;
	this->y = point.y;
	this->width = image.cols;
	this->height = image.rows;
}

racv::Rect racv::Roi::getRoi()
{
	cv::Point point;
	cv::Size size;
	this->image.locateROI(size, point);
	return racv::Rect(point.x, point.y, this->image.cols, this->image.rows);
}

cv::Mat& racv::Roi::getImage()
{
	this->sync();
	return this->image;
}

void racv::Roi::draw(cv::Scalar color)
{
	this->sync();
	cv::rectangle(this->image, cv::Rect(0, 0, this->image.cols, this->image.rows), color, 2, cv::LINE_AA);
}

cv::Size racv::Roi::getParentSize()
{
	cv::Point point;
	cv::Size size;
	this->image.locateROI(size, point);
	return size;
}

void racv::Roi::sync()
{
	this->fit(this->getParentSize());
	racv::Rect roi = getRoi();
	int top = roi.y - this->y;
	int left = roi.x - this->x;
	int bottom = (this->y + this->height) - (roi.y + roi.height);
	int right = (this->x + this->width) - (roi.x + roi.width);
	this->image.adjustROI(top, bottom, left, right);
}
