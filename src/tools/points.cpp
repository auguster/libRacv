/*
 * points.cpp
 *
 *  Created on: 11 avr. 2011
 *      Author: auguster
 */
#include <libRacv/tools/points.hpp>

namespace racv
{

	cv::Rect computeRectangle(std::vector<cv::Point2f> points)
	{
		cv::Point hautGauche = *(points.begin());
		cv::Point basDroit = *(points.begin());
		for (std::vector<cv::Point2f>::iterator point = points.begin(); point < points.end(); point++)
		{
			if (point->x < hautGauche.x)
				hautGauche.x = point->x;
			if (point->y < hautGauche.y)
				hautGauche.y = point->y;
			if (point->x > basDroit.x)
				basDroit.x = point->x;
			if (point->y > basDroit.y)
				basDroit.y = point->y;
		}
		return cv::Rect(hautGauche, basDroit);
	}

	void changeOrigin(cv::Point origin, cv::vector<cv::Point2f> &points)
	{
		for (std::vector<cv::Point2f>::iterator point = points.begin(); point < points.end(); point++)
		{
			point->x += origin.x;
			point->y += origin.y;
		}
	}

	cv::vector<cv::Point2f> filterOut(cv::vector<cv::Point2f> &points, std::vector<uchar> &status)
	{
		cv::vector<cv::Point2f> newPoints;
		cv::vector<cv::Point2f>::iterator point = points.begin();
		std::vector<uchar>::iterator statu = status.begin();
		while (point < points.end() && statu < status.end())
		{
			if (*statu)
				newPoints.push_back(*point);
			point++;
			statu++;
		}
		return newPoints;
	}

	void drawPoints(cv::Mat image, cv::vector<cv::Point2f> &points, cv::Scalar color)
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
