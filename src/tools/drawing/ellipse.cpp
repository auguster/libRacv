/*
 * ellipse.cpp
 *
 *  Created on: 7 juil. 2011
 *      Author: remi
 */

#include <opencv2/core/core.hpp>

#include <libRacv/tools/drawing/ellipse.hpp>

namespace racv
{
	void drawFilledEllipse(cv::Mat &image, cv::Point center, cv::Size size, double angle, double startingAngle, double endingAngle, const cv::Scalar &color)
	{
		std::vector<cv::Point> pts;
		cv::ellipse2Poly(center, size, angle, startingAngle, endingAngle, 1, pts);

		cv::Point *points;
		points = &pts[0];
		int nbtab = pts.size();

		cv::fillPoly(image, (const cv::Point **) &points, &nbtab, 1, color, 16);
	}

	void drawFilledEllipse(cv::Mat &image, cv::Point center, cv::Size size, double angle, double startingAngle, double endingAngle, const cv::Scalar &color, double alpha)
	{
		cv::Mat tempImage(image.rows, image.cols, image.type());
		drawFilledEllipse(tempImage, center, size, angle, startingAngle, endingAngle, color);
		cv::addWeighted(tempImage, alpha, image, 1, 0, image);
	}
} // namespace racv
