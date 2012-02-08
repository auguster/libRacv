/*
 * Copyright (c) 2011 Rémi AUGUSTE
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * Contact: Rémi Auguste <remi.auguste@gmail.com>
 */

#include <libRacv/pipes/misc/Detector.hpp>

#include <libRacv/tools/detection.hpp>
#include <libRacv/tools/rectangle.hpp>

#include <vector>
#include <iostream>

namespace racv {

Detector::Detector(cv::CascadeClassifier *classifier) {
	this->classifier = classifier;
}

Detector::Detector(std::string classifierFile) {
	this->classifier = new cv::CascadeClassifier(classifierFile);
}

Detector::~Detector() {
}

Pipe::PipeMsg Detector::processing(Pipe::PipeMsg msg) {
	for (std::vector<cv::Mat *>::iterator image = msg.imgs->begin();
			image < msg.imgs->end(); image++) {
		racv::smartDetect(*this->classifier, **image, detectList);

		for (std::vector<cv::Rect>::iterator rect = detectList.begin();	rect < detectList.end(); rect++) {
			if (!(*msg.data)[0])
					(*msg.data)[0] = new cv::Mat(0, 4, CV_32F);
			(*msg.data)[0]->push_back(*racv::rect2mat(*rect));
		}
	}

	return msg;
}

} /* namespace racv */
