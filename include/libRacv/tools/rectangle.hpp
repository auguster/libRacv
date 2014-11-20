/*
 * Copyright (c) 2011 Rémi AUGUSTE
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * Contact: Rémi Auguste <remi.auguste@gmail.com>
 */

#ifndef RECTANGLE_HPP_
#define RECTANGLE_HPP_

#include <opencv2/core/core.hpp> //FIXME remove all reference to cv::Rect and replace them by racv::Rect
#include <libRacv/Rect.hpp>

namespace racv
{

	/**
	 * this function checks if two rectangles are overlapping
	 */
	bool isOverlapping(cv::Rect A, cv::Rect B);

	/**
	 * Merge vector source with vector destination into destination
	 */
	void merge(std::vector<cv::Rect> &source, std::vector<cv::Rect> &destination);

	/**
	 * this function transforms the rectangle into a scaled version of itself
	 * even the origins are scaled
	 * this function is for space change
	 */
	void scaleRectangle(cv::Rect &rectangle, double scale);

	/**
	 * this function transforms the rectangle into a scaled version of itself
	 * the center of the rectangle remains the same
	 */
	void scaleRectangleKeepCenter(cv::Rect &rectangle, double scale);

	/**
	 * this function makes sure that a rectangle doesn't go outside the image boundaries
	 */
	void fitRectangle(cv::Mat image, cv::Rect& rectangle);

	/**
	 * returns true if bRect overlaps an upscaled (10% by default) version of aRect
	 * NB: if pourcent == 1, just call isOverlapping
	 */
	bool isNear(cv::Rect aRect, cv::Rect bRect, double pourcent = 1.1);

	/**
	 * Displays the properties of a rectangle
	 */
	void showRectangle(cv::Rect rect);

	/*
	 * Converts a cv::Mat(n, 4, CV_32F) into a vector of cv::Rect
	 */
	std::vector<racv::Rect > *mat2VectRect(cv::Mat mat);

	/*
	 * Converts a vector of cv::Rect info a cv::Mat(n, 4, CV_32F)
	 */
	cv::Mat *vectRect2Mat(std::vector<cv::Rect > vec);

	/*
	 * Converts a cv::Rect into a single line cv::Mat(1, 4, CV_32F)
	 */
	cv::Mat *rect2mat(cv::Rect rect);

	/*
	 * Converts the first line of a cv::Mat(n, 4, CV_32F) into a cv::Rect
	 */
	cv::Rect *mat2rect(cv::Mat mat);

	/*
	 * Rotates a rectangle around a point given an angle
	 */
	void rotateRectangle(cv::Rect &rect, cv::Point center, double angle);

	/*
	 * Rotates a whole vector of rectangle around a single point given an angle
	 */
	void rotateRectangles(std::vector<cv::Rect > &rects, cv::Point center, double angle);

	/**
	 * Returns a rectangle that contains both rectangle
	 */
	cv::Rect mergeRect(cv::Rect aRect, cv::Rect bRect);

} // namespace racv

#endif /* RECTANGLE_HPP_ */
