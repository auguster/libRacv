/*
 * points.hpp
 *
 *  Created on: 11 avr. 2011
 *      Author: auguster
 */

#ifndef POINTS_HPP_
#define POINTS_HPP_

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

namespace racv {

	/**
	 * Computes a rectangle fitting the cloud of points
	 */
	cv::Rect computeRectangle(std::vector<cv::Point2f> points);

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
