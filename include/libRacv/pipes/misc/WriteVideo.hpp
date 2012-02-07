/*
 * WriteVideo.hpp
 *
 *  Created on: Oct 27, 2011
 *      Author: remi
 */

#ifndef WRITEVIDEO_HPP_
#define WRITEVIDEO_HPP_

#include "../core/Pipe.hpp"

#include <opencv2/highgui/highgui.hpp>
#include <string>

namespace racv {

class WriteVideo: public racv::Pipe {
private:
	void processingSingleFrame(cv::Mat *image, cv::Mat *data);
	cv::VideoWriter *writer;
public:
	WriteVideo(std::string filename, cv::Size size);
	WriteVideo(cv::VideoWriter *writer);
	virtual ~WriteVideo();
};

} /* namespace racv */
#endif /* WRITEVIDEO_HPP_ */
