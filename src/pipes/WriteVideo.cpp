/*
 * WriteVideo.cpp
 *
 *  Created on: Oct 27, 2011
 *      Author: remi
 */

#include <pipes/WriteVideo.hpp>

namespace racv {

WriteVideo::WriteVideo(std::string filename, cv::Size size) {
	this->writer = new cv::VideoWriter(filename, CV_FOURCC('M','P','E','G'), 25, size, true);
}

WriteVideo::WriteVideo(cv::VideoWriter *writer)
{
	this->writer = writer;
}

WriteVideo::~WriteVideo() {
	// TODO Auto-generated destructor stub
}

void WriteVideo::processingSingleFrame(cv::Mat *image, cv::Mat *data)
{
	*this->writer << *image;
}

} /* namespace racv */
