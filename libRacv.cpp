/*
 * libRemi.cpp
 *
 *  Created on: 25 mars 2011
 *      Author: auguster
 */
#include "include/libRacv.hpp"

#include <opencv2/imgproc/imgproc.hpp>

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

void smartDetect(cv::CascadeClassifier detector, cv::Mat &frame, std::vector<cv::Rect> &rectList)
{
	cv::Mat smallerFrame;
	std::vector<cv::Rect> list;
	double scaleLevel = 0.125;
	//tries to find at least the same number of object as before at the same scalelevel
	while (scaleLevel <= 1 && list.size() < ((rectList.size() > 0) ? rectList.size() : 1))
	{
		cv::resize(frame, smallerFrame, cv::Size(), scaleLevel, scaleLevel);
		detector.detectMultiScale(smallerFrame, list, 1.3);
		scaleLevel *= 2;
	}
	scaleLevel /= 2;

	rectList.clear();

	for (std::vector<cv::Rect>::iterator rect = list.begin(); rect < list.end(); rect++)
	{
		cv::Rect fullSize = *rect;
		fullSize.x /= scaleLevel;
		fullSize.y /= scaleLevel;
		fullSize.height /= scaleLevel;
		fullSize.width /= scaleLevel;
		rectList.push_back(fullSize);
	}
}
