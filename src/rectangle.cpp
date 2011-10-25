/*
 * rectangle.cpp
 *
 *  Created on: 14 juin 2011
 *      Author: remi
 */

#include <rectangle.hpp>

#include <iostream>

namespace racv {
bool isOverlapping(cv::Rect A, cv::Rect B) {
	return (((A.x <= B.x) && (B.x <= (A.x + A.width)))
			&& ((A.y <= B.y) && (B.y <= (A.y + A.height))))
			|| (((A.x <= (B.x + B.width))
					&& ((B.x + B.width) <= (A.x + A.width)))
					&& ((A.y <= (B.y + B.height))
							&& ((B.y + B.height) <= (A.y + A.height))));
}

void merge(std::vector<cv::Rect> &source, std::vector<cv::Rect> &destination) {
	for (std::vector<cv::Rect>::iterator A = source.begin(); A < source.end();
			A++) {
		for (std::vector<cv::Rect>::iterator B = destination.begin();
				B < destination.end(); B++) {
			if (isOverlapping(*A, *B)) {
				break;
			}

			if (B == destination.end()) {
				destination.push_back(*A);
				break;
			}
		}
	}
}

void scaleRectangle(cv::Rect &rectangle, double scale) {
	rectangle.x *= scale;
	rectangle.y *= scale;
	rectangle.width *= scale;
	rectangle.height *= scale;
}

void scaleRectangleKeepCenter(cv::Rect &rectangle, double scale) {
	rectangle.x -= (rectangle.width * scale - rectangle.width) / 2;
	rectangle.y -= (rectangle.height * scale - rectangle.height) / 2;
	rectangle.width *= scale;
	rectangle.height *= scale;
}

void fitRectangle(cv::Mat image, cv::Rect& rectangle) {
	rectangle.x = cv::max(0, rectangle.x);
	rectangle.y = cv::max(0, rectangle.y);
	rectangle.width = cv::min(rectangle.width, image.cols - rectangle.x);
	rectangle.height = cv::min(rectangle.height, image.rows - rectangle.y);
}

/**
 * returns true if bRect overlaps an upscaled (10% ?) version of aRect
 */
bool isNear(cv::Rect aRect, cv::Rect bRect, double pourcent) {
	racv::scaleRectangleKeepCenter(aRect, pourcent);
	return racv::isOverlapping(aRect, bRect);
}

/**
 * Displays the properties of a rectangle
 */
void showRectangle(cv::Rect rect) {
	std::cout << "position: (" << rect.x << " , " << rect.y << "); size: "
			<< rect.height << " x " << rect.width << std::endl;
}

/*
 * Converts a cv::Mat(n, 4, CV_32F) into a vector of cv::Rect
 */
std::vector<cv::Rect> *mat2VectRect(cv::Mat mat) {
	std::vector<cv::Rect> *vec = new std::vector<cv::Rect>();
	for (int i = 0; i < mat.rows; i++) {
		cv::Rect *rect = new cv::Rect();
		rect->x = mat.at<float>(i, 0);
		rect->y = mat.at<float>(i, 1);
		rect->height = mat.at<float>(i, 2);
		rect->width = mat.at<float>(i, 3);
		vec->push_back(*rect);
	}

	return vec;
}

/*
 * Converts a vector of cv::Rect info a cv::Mat(n, 4, CV_32F)
 */
cv::Mat *VectRect2mat(std::vector<cv::Rect> vec) {
	cv::Mat *mat = new cv::Mat(0, 4, CV_32F);

	return mat;
}
}
