/*
 * Detector.hpp
 *
 *  Created on: Oct 24, 2011
 *      Author: remi
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
