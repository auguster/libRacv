/*
 * Detector.cpp
 *
 *  Created on: Oct 24, 2011
 *      Author: remi
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
