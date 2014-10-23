/*
 * Copyright (c) 2011 Rémi AUGUSTE
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * Contact: Rémi Auguste <remi.auguste@gmail.com>
 */

#include <libRacv/points.hpp>

#include <opencv2/imgproc/imgproc.hpp>

namespace racv
{

	cv::Rect computeRectangleFloat(std::vector<cv::Point2f> &points)
	{
		cv::Point hautGauche = *(points.begin());
		cv::Point basDroit = *(points.begin());
		for (std::vector<cv::Point2f>::iterator point = points.begin(); point < points.end(); point++)
		{
			if (point->x < hautGauche.x) hautGauche.x = point->x;
			if (point->y < hautGauche.y) hautGauche.y = point->y;
			if (point->x > basDroit.x) basDroit.x = point->x;
			if (point->y > basDroit.y) basDroit.y = point->y;
		}
		return cv::Rect(hautGauche, basDroit);
	}

	cv::Rect computeRectangle(std::vector<cv::Point > &points)
	{
		cv::Point hautGauche = *(points.begin());
		cv::Point basDroit = *(points.begin());
		for (std::vector<cv::Point>::iterator point = points.begin(); point < points.end(); point++)
		{
			if (point->x < hautGauche.x) hautGauche.x = point->x;
			if (point->y < hautGauche.y) hautGauche.y = point->y;
			if (point->x > basDroit.x) basDroit.x = point->x;
			if (point->y > basDroit.y) basDroit.y = point->y;
		}
		return cv::Rect(hautGauche, basDroit);
	}

	void changeOrigin(cv::Point origin, std::vector<cv::Point2f> &points)
	{
		for (std::vector<cv::Point2f>::iterator point = points.begin(); point < points.end(); point++)
		{
			point->x += origin.x;
			point->y += origin.y;
		}
	}

	std::vector<cv::Point2f> filterOut(std::vector<cv::Point2f> &points, std::vector<uchar> &status)
	{
		std::vector<cv::Point2f> newPoints;
		std::vector<cv::Point2f>::iterator point = points.begin();
		std::vector<uchar>::iterator statu = status.begin();
		while (point < points.end() && statu < status.end())
		{
			if (*statu) newPoints.push_back(*point);
			point++;
			statu++;
		}
		return newPoints;
	}

	void drawPoints(cv::Mat image, std::vector<cv::Point2f> &points, cv::Scalar color)
	{
		for (std::vector<cv::Point2f>::iterator point = points.begin(); point < points.end(); point++)
		{
			cv::circle(image, *point, 1, color, 1, 2, 8);
		}
	}

	double horizontalAngle(cv::Point p1, cv::Point p2, cv::Rect facer)
	{
		double x1, x2, y1, y2, mL1, mL2, n;
		double midx, midy;
		cv::Point p3, p4;
		x1 = p1.x;
		y1 = p1.y;
		x2 = p2.x;
		y2 = p2.y;
		midx = (x1 + x2) / 2;
		midy = (y1 + y2) / 2;

		mL1 = (y1 - y2) / (x1 - x2);
		if (mL1 == 0)
			mL2 = 0;
		else
			mL2 = -1 / mL1;
		n = midy - mL2 * midx;

		//Y=mL2*x+n;
		if (mL1 == 0)
			p3.x = (int) midx;
		else
			p3.x = (int) ((facer.y - n) / mL2);
		p3.y = facer.y;

		if (mL1 == 0)
			p4.x = (int) midx;
		else
			p4.x = (int) ((facer.y + facer.height - n) / mL2);
		p4.y = facer.y + facer.height;

		double angle = atan2((double) p3.x - p4.x, (double) p3.y - p4.y);

		return (angle * 180. / CV_PI);
	}

} // namespace racv
