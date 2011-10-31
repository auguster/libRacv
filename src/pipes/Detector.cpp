/*
 * Detector.cpp
 *
 *  Created on: Oct 24, 2011
 *      Author: remi
 */

#include <pipes/Detector.hpp>

#include <detection.hpp>

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
			cv::Mat *line = new cv::Mat(1, 4, CV_32F);
			line->at<float>(0, 0) = rect->x;
			line->at<float>(0, 1) = rect->y;
			line->at<float>(0, 2) = rect->height;
			line->at<float>(0, 3) = rect->width;
			if (!(*msg.data)[0])
					(*msg.data)[0] = new cv::Mat(0, 4, CV_32F);
			(*msg.data)[0]->push_back(*line);
		}
	}

	return msg;
}

} /* namespace racv */
