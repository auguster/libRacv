/*
 * detect.cpp
 *
 *  Created on: 11 avr. 2011
 *      Author: auguster
 */
#include <detection.hpp>

#include <opencv2/imgproc/imgproc.hpp>

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
