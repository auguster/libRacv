/*
 * Copyright (c) 2012 Rémi AUGUSTE
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 * 
 * Contact: Rémi Auguste <remi.auguste@gmail.com>
 */

#include <libRacv/Rect.hpp>

namespace racv
{
	Rect::Rect() :
		cv::Rect_<int>()
	{

	}

	Rect::Rect(const cv::Point & pt1, const cv::Point & pt2) :
		cv::Rect_<int>(pt1, pt2)
	{
	}

	Rect::Rect(int x, int y, int width, int height) :
		cv::Rect_<int>(x, y, width, height)
	{
	}

	Rect::Rect(const cv::Point & org, const cv::Size & sz) :
		cv::Rect_<int>(org, sz)
	{
	}

	Rect::~Rect()
	{
	}

	bool Rect::operator<(const racv::Rect &other) const
	{
		return (this->area()) < (other.area());
	}

	const Rect &Rect::operator+=(const racv::Rect &other)
	{
		if (other.x < this->x)
			this->x = other.x;

		if (other.y < this->y)
			this->y = other.y;

		/*FIXME modifier width et height au lieu de br()
		if (other.br().x > this->br().x)
			this->br().x = other.br().x;

		if (other.br().y > this->br().y)
			this->br().y = other.br().y;
		*/

		return *this;
	}

}
