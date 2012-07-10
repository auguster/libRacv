/*
 * Copyright (c) 2011 Rémi AUGUSTE
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * Contact: Rémi Auguste <remi.auguste@gmail.com>
 */

#ifndef POINTS_HPP_
#define POINTS_HPP_

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

namespace racv {

	/**
	 * Computes a rectangle fitting the cloud of points
	 */
	cv::Rect computeRectangle(std::vector<cv::Point2f> &points);
	cv::Rect computeRectangle(std::vector<cv::Point> &points);

	/**
	 * Changes the coordinate of a vector of points
	 * origin: new origin relative to the current one
	 * points: the points to modify
	 */
	void changeOrigin(cv::Point origin, cv::vector<cv::Point2f> &points);

	/**
	 * Returns a new vector of points where the points that are not marked in status have been removed.
	 * points: the points
	 * status: check if each status is > 0, the order has to be the same in both parameters
	 * Note: the parameters are not modified
	 */
	cv::vector<cv::Point2f> filterOut(cv::vector<cv::Point2f> &points, std::vector<uchar> &status);

	/**
	 * Draws a cloud of points into the image
	 */
	void drawPoints(cv::Mat image, cv::vector<cv::Point2f> &points, cv::Scalar color = CV_RGB(0, 0, 255));

	/**
	 * returns the horizontal angle between two points included in a rectangle
	 */
	double horizontalAngle(cv::Point p1, cv::Point p2, cv::Rect facer);

}  // namespace racv



#endif /* POINTS_HPP_ */
