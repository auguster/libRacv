/*
 * Copyright (c) 2012 Rémi AUGUSTE
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 * 
 * Contact: Rémi Auguste <remi.auguste@gmail.com>
 */

#include <libRacv/Rect.hpp>

#include <libRacv/points.hpp>

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

	Rect::Rect(const cv::Rect &other) :
			cv::Rect_<int>(other)
	{
	}

	Rect::Rect(std::vector<cv::Point>& points) :
			cv::Rect_<int>(racv::computeRectangle(points))
	{
	}

	Rect::Rect(const cv::Mat& image) :
			cv::Rect_<int>(0, 0, image.cols, image.rows)
	{
	}

	Rect::~Rect()
	{
	}

	bool Rect::operator<(const Rect &other) const
	{
		return (this->area()) < (other.area());
	}

	racv::Rect &Rect::operator+(const racv::Rect &other) const
	{
		racv::Rect *temp = new racv::Rect();
		temp->x = cv::min(this->x, other.x);
		temp->y = cv::min(this->y, other.y);
		temp->width = cv::max(this->br().x, other.br().x) - temp->x;
		temp->height = cv::max(this->br().y, other.br().y) - temp->y;
		return *temp;
	}

	racv::Rect &Rect::operator+=(const racv::Rect &other)
	{
		*this = *this + other;
		return *this;
	}

	void Rect::scaleWidth(double scale)
	{
		this->scale(scale, 1);
	}

	void Rect::scaleHeight(double scale)
	{
		this->scale(1, scale);
	}

	racv::Point Rect::center() const
	{
		return cv::Point(this->x + this->width / 2, this->y + this->height / 2);
	}

	void Rect::scale(double widthScale, double heightScale)
	{
		int oldwith = this->width;
		this->width *= widthScale;
		this->x = this->x + (oldwith - this->width) / 2;
		int oldHeight = this->height;
		this->height *= heightScale;
		this->y = this->y + (oldHeight - this->height) / 2;
	}

	void Rect::scale(double scale)
	{
		this->scale(scale, scale);
	}

	racv::Rect& Rect::scaledWidth(double scale) const
	{
		return this->scaled(scale, 1);
	}

	racv::Rect& Rect::scaledHeight(double scale) const
	{
		return this->scaled(1, scale);
	}

	racv::Rect& Rect::scaled(double widthScale, double heightScale) const
	{
		Rect *temp = new Rect(*this);
		temp->scale(widthScale, heightScale);
		return *temp;
	}

	racv::Rect& Rect::scaled(double scale) const
	{
		return this->scaled(scale, scale);
	}

	void Rect::changeSpace(const racv::Rect& from, const racv::Rect& to)
	{
		this->x += from.x - to.x;
		this->y += from.y - to.y;
	}

	Rect& Rect::changedSpace(const racv::Rect& from, const racv::Rect& to) const
	{
		Rect *temp = new Rect(*this);
		temp->changeSpace(from, to);
		return *temp;
	}

}
