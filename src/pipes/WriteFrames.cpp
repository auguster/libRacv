/*
 * WriteFrames.cpp
 *
 *  Created on: 26 sept. 2011
 *      Author: remi
 */

#include <pipes/WriteFrames.hpp>

#include <opencv2/highgui/highgui.hpp>

#include <iostream>

namespace racv
{

	WriteFrames::WriteFrames():
			frameCounter(0)
	{}

	WriteFrames::WriteFrames(std::string prefix):
				frameCounter(0), prefix(prefix)
	{}

	WriteFrames::~WriteFrames()
	{}

	void WriteFrames::processingSingleFrame(cv::Mat *image, cv::Mat *data)
	{
		std::stringstream ss;
		ss << this->prefix << this->frameCounter++ << ".pgm";
		cv::imwrite(ss.str(), *image);
	}

}
