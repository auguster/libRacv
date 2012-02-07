/*
 * drawing.cpp
 *
 *  Created on: 7 juil. 2011
 *      Author: remi
 */

#include <libRacv/tools/drawing/drawing.hpp>

namespace racv {

	void fill(cv::Mat &image, const cv::Scalar &color)
	{
		cv::Point *points = new cv::Point[4];
		points[0] = cv::Point(0,0);
		points[1] = cv::Point(0, image.rows);
		points[2] = cv::Point(image.cols, image.rows);
		points[3] = cv::Point(image.cols, 0);

		int nb = 4;

		cv::fillPoly(image, (const cv::Point **) &points, &nb, 1, color);

	}

}  // namespace racv
