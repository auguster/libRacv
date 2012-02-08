/*
 * Copyright (c) 2011 Rémi AUGUSTE
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * Contact: Rémi Auguste <remi.auguste@gmail.com>
 */

#ifndef DETECTOR_HPP_
#define DETECTOR_HPP_

#include "../core/Pipe.hpp"

#include <opencv2/objdetect/objdetect.hpp>

namespace racv {

class Detector: public racv::Pipe {
protected:
	Pipe::PipeMsg processing(Pipe::PipeMsg msg);
	//void processingSingleFrame(cv::Mat *image, cv::Mat *data);
	cv::CascadeClassifier *classifier;
	std::vector<cv::Rect > detectList;
public:
	Detector(cv::CascadeClassifier *classifier);
	Detector(std::string classifierFile);
	virtual ~Detector();
};

} /* namespace racv */
#endif /* DETECTOR_HPP_ */
