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

#include <opencv2/core.hpp>

namespace racv
{

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

		/**
		 * Compares the area of rectangle with another one
		 */
		bool operator<(const racv::Rect &other) const;

		/**
		 * Merges two rectangle using their combined min x,y and max x,y
		 */
		const Rect &operator+(const racv::Rect &other) const;
		const Rect &operator+=(const racv::Rect &other);

		virtual ~Rect();
	};

}

#endif /* RECT_HPP_ */
