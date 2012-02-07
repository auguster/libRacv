/*
 * ellipse.hpp
 *
 *  Created on: 7 juil. 2011
 *      Author: remi
 */

#ifndef ELLIPSE_HPP_
#define ELLIPSE_HPP_

namespace racv {

	/**
	 * Draws a filled ellipse on an image
	 */
	void drawFilledEllipse(cv::Mat &image, cv::Point center, cv::Size size, double angle, double startingAngle, double endingAngle, const cv::Scalar &color);

	void drawFilledEllipse(cv::Mat &image, cv::Point center, cv::Size size, double angle, double startingAngle, double endingAngle, const cv::Scalar &color, double alpha);

}  // namespace racv

#endif /* ELLIPSE_HPP_ */
