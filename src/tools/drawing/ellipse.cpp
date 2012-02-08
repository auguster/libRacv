/*
 * Copyright (c) 2011 Rémi AUGUSTE
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * Contact: Rémi Auguste <remi.auguste@gmail.com>
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
