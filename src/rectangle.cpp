/*
 * Copyright (c) 2011 Rémi AUGUSTE
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * Contact: Rémi Auguste <remi.auguste@gmail.com>
 */

#include <libRacv/rectangle.hpp>
#include <libRacv/points.hpp>

#include <iostream>

#include <math.h>

namespace racv
{
	bool inSegment(int a, int bstart, int bend)
	{
		return ((a >= bstart) && (a <= bend));
	}

	//FIXME this function only works with rectangles which edges are
	//parallel to the X and Y axis.
	//--> should not be used on rotated rectangles
	bool isOverlapping(cv::Rect A, cv::Rect B)
	{
		bool axdansb = inSegment(A.x, B.x, B.br().x);
		bool abrxdansb = inSegment(A.br().x, B.x, B.br().x);
		bool bxdansa = inSegment(B.x, A.x, A.br().x);
		bool bbrxdansa = inSegment(B.br().x, A.x, A.br().x);
		bool xoverlap = axdansb || abrxdansb || bxdansa || bbrxdansa;

		bool aydansb = inSegment(A.y, B.y, B.br().y);
		bool abrydansb = inSegment(A.br().y, B.y, B.br().y);
		bool bydansa = inSegment(B.y, A.y, A.br().y);
		bool bbrydansa = inSegment(B.br().y, A.y, A.br().y);
		bool yoverlap = aydansb || abrydansb || bydansa || bbrydansa;

		return xoverlap && yoverlap;
	}

	void merge(std::vector<cv::Rect> &source, std::vector<cv::Rect> &destination)
	{
		for (std::vector<cv::Rect>::iterator A = source.begin(); A < source.end(); A++)
		{
			std::vector<cv::Rect>::iterator B = destination.begin();
			for (; B < destination.end(); B++)
			{
				if (isOverlapping(*A, *B))
				{
					break;
				}
			}

			if (B == destination.end())
			{
				destination.push_back(*A);
				break;
			}
		}
	}

	void scaleRectangle(cv::Rect &rectangle, double scale)
	{
		rectangle.x *= scale;
		rectangle.y *= scale;
		rectangle.width *= scale;
		rectangle.height *= scale;
	}

	void scaleRectangleKeepCenter(cv::Rect &rectangle, double scale)
	{
		rectangle.x -= (rectangle.width * scale - rectangle.width) / 2;
		rectangle.y -= (rectangle.height * scale - rectangle.height) / 2;
		rectangle.width *= scale;
		rectangle.height *= scale;
	}

	void fitRectangle(cv::Mat image, cv::Rect& rectangle)
	{
		rectangle.x = cv::max(0, rectangle.x);
		rectangle.y = cv::max(0, rectangle.y);
		rectangle.width = cv::min(rectangle.width, image.cols - rectangle.x);
		rectangle.height = cv::min(rectangle.height, image.rows - rectangle.y);
		rectangle.width = cv::max(0, rectangle.width);
		rectangle.height = cv::max(0, rectangle.height);
	}

	/**
	 * returns true if bRect overlaps an upscaled (10% ?) version of aRect
	 */
	bool isNear(cv::Rect aRect, cv::Rect bRect, double pourcent)
	{
		racv::scaleRectangleKeepCenter(aRect, pourcent);
		return racv::isOverlapping(aRect, bRect);
	}

	/**
	 * Displays the properties of a rectangle
	 */
	void showRectangle(cv::Rect rect)
	{
		std::cout << "position: (" << rect.x << " , " << rect.y << "); size: " << rect.height << " x " << rect.width << std::endl;
	}

	/*
	 * Converts a cv::Mat(n, 4, CV_32F) into a vector of cv::Rect
	 */
	std::vector<racv::Rect> *mat2VectRect(cv::Mat mat)
	{
		std::vector<racv::Rect> *vec = new std::vector<racv::Rect>();
		for (int i = 0; i < mat.rows; i++)
		{
			racv::Rect *rect = new racv::Rect();
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
	cv::Mat *VectRect2mat(std::vector<cv::Rect> vec)
	{
		cv::Mat *mat = new cv::Mat(0, 4, CV_32F);

		return mat;
	}

	cv::Mat *rect2mat(cv::Rect rect)
	{
		cv::Mat *mat = new cv::Mat(1, 4, CV_32F);
		mat->at<float>(0, 0) = rect.x;
		mat->at<float>(0, 1) = rect.y;
		mat->at<float>(0, 2) = rect.height;
		mat->at<float>(0, 3) = rect.width;
		return mat;
	}

	cv::Rect *mat2rect(cv::Mat mat)
	{
		cv::Rect *rect = new cv::Rect();
		rect->x = mat.at<float>(0, 0);
		rect->x = mat.at<float>(0, 1);
		rect->x = mat.at<float>(0, 2);
		rect->x = mat.at<float>(0, 3);
		return rect;
	}

	void rotatePoint(cv::Point &point, cv::Point center, double angle)
	{
		double AngCrad;
		AngCrad = (M_PI * angle) / 180;
		point.x = ((point.x - center.x) * cos(AngCrad) - (point.y - center.y) * sin(AngCrad) + center.x);
		point.y = ((point.x - center.x) * sin(AngCrad) + (point.y - center.y) * cos(AngCrad) + center.y);
	}

	void rotateRectangle(cv::Rect &rect, cv::Point center, double angle)
	{
		cv::Point mass;
		mass.x = rect.x + rect.width / 2;
		mass.y = rect.y + rect.height / 2;
		rotatePoint(mass, center, angle);
		cv::RotatedRect rrect(mass, rect.size(), angle);
		rect = rrect.boundingRect();
	}

	void rotateRectangles(std::vector<cv::Rect> &rects, cv::Point center, double angle)
	{
		for (std::vector<cv::Rect>::iterator rect = rects.begin(); rect < rects.end(); rect++)
		{
			rotateRectangle(*rect, center, angle);
		}
	}

	cv::Rect mergeRect(cv::Rect aRect, cv::Rect bRect)
	{
		cv::Rect temp;
		temp.x = cv::min(aRect.x, bRect.x);
		temp.y = cv::min(aRect.y, bRect.y);
		temp.width = cv::max(aRect.br().x, bRect.br().x) - temp.x;
		temp.height = cv::max(aRect.br().y, bRect.br().y) - temp.y;
		return temp;
	}

}
