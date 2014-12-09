/*
 * Copyright (c) 2012 Rémi AUGUSTE
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 * 
 * Contact: Rémi Auguste <remi.auguste@gmail.com>
 */

#ifndef RECT_HPP_
#define RECT_HPP_

#include <libRacv/opencv/core.hpp>
#include <libRacv/Point.hpp>

namespace racv
{
	class Point;

	/**
	 * This class provides an extension of OpenCV's Rect
	 */
	class Rect: public cv::Rect_<int>
	{
	public:
		Rect();
		Rect(const cv::Rect &other);
		Rect(int x, int y, int width, int height);
		Rect(const cv::Point& org, const cv::Size& sz);
		Rect(const cv::Point& pt1, const cv::Point& pt2);
		Rect(std::vector<cv::Point> &points);
		Rect(const cv::Mat &image);

		/**
		 * Scales the height or width of the current rectangle but keeps the center in the same position
		 */
		void scaleWidth(double scale);
		void scaleHeight(double scale);
		void scale(double widthScale, double heightScale);
		void scale(double scale);

		/**
		 * Returns a scaled copy of the current rectangle
		 */
		Rect & scaledWidth(double scale) const;
		Rect & scaledHeight(double scale) const;
		Rect & scaled(double widthScale, double heightScale) const;
		Rect & scaled(double scale) const;

		/**
		 * Returns the position of the center of the rectangle
		 */
		racv::Point center() const;

		/**
		 * Change the referential of the rectangle
		 */
		void changeSpace(const racv::Rect &from, const racv::Rect &to);

		/**
		 * Returns a copy of the rectangle whose referential was changed
		 */
		Rect & changedSpace(const racv::Rect &from, const racv::Rect &to) const;

		void fit(const racv::Rect &container);
		void fit(const cv::Mat &container);
		void fit(const cv::Size &size);

		/**
		 * Returns the center point of the side
		 */
		cv::Point getLeft();
		cv::Point getRight();
		cv::Point getTop();
		cv::Point getBottom();

		/**
		 * Compares the area of rectangle with another one
		 */
		bool operator<(const racv::Rect &other) const;

		/**
		 * Merges two rectangle using their combined min x,y and max x,y
		 */
		Rect &operator+(const racv::Rect &other) const;
		Rect &operator+=(const racv::Rect &other);

		virtual ~Rect();
	};

}

#endif /* RECT_HPP_ */
