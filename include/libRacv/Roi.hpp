/*
 * Copyright (c) 2014 Rémi AUGUSTE
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * Contact: Rémi Auguste <remi.auguste@gmail.com>
 */

#ifndef ROI_HPP_
#define ROI_HPP_

#include <libRacv/Rect.hpp>

namespace racv
{
	class Roi: public racv::Rect
	{
	private:
		cv::Mat image;
		racv::Rect getRoi();
		cv::Size getParentSize();
		void sync();

	public:
		/**
		 * cv::Mat image must be set using the form: myimage(myroi)
		 * where myimage is a cv::Mat
		 * and myroi is a cv::Rect or a racv::Rect
		 */
		Roi(cv::Mat image);
		cv::Mat &getImage();
		void draw(cv::Scalar color);
	};
}

#endif /* FACE_HPP_ */
