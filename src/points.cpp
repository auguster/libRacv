/*
 * points.cpp
 *
 *  Created on: 11 avr. 2011
 *      Author: auguster
 */
#include <points.hpp>

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
