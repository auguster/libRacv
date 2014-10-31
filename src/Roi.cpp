/*
 * Face.cpp
 *
 *  Created on: 31 oct. 2014
 *      Author: remi
 */

#include <libRacv/Roi.hpp>
#include <libRacv/skinprop.hpp>

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
