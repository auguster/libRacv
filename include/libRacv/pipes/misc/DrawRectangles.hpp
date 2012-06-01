/*
 * Copyright (c) 2011 Rémi AUGUSTE
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * Contact: Rémi Auguste <remi.auguste@gmail.com>
 */

#ifndef DRAWRECTANGLES_HPP_
#define DRAWRECTANGLES_HPP_

#include "../core/Pipe.hpp"

#include <opencv2/core/core.hpp>

namespace racv {

class DrawRectangles: public racv::Pipe {
private:
	void processingSingleFrame(cv::Mat *image, cv::Mat *data);
	bool debug;
	cv::Scalar color;
public:
	DrawRectangles(bool value = false, cv::Scalar color = CV_RGB(255, 0, 0));
	DrawRectangles();
	virtual ~DrawRectangles();
};

} /* namespace racv */
#endif /* DRAWRECTANGLES_HPP_ */
