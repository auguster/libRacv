/*
 * rectangle.hpp
 *
 *  Created on: 14 juin 2011
 *  Last Modification: 19/09/2011
 *      Author: remi
 */

#ifndef RECTANGLE_HPP_
#define RECTANGLE_HPP_

#include <opencv2/core/core.hpp>

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
	std::vector<cv::Rect > *mat2VectRect(cv::Mat mat);

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

} // namespace racv

#endif /* RECTANGLE_HPP_ */
