/*
 * WriteFrames.cpp
 *
 *  Created on: 26 sept. 2011
 *      Author: remi
 */

#include <pipes/WriteFrames.hpp>

#include <opencv2/highgui/highgui.hpp>

namespace racv
{

	WriteFrames::WriteFrames():
			frameCounter(0)
	{}

	WriteFrames::WriteFrames(std::string prefix):
				prefix(prefix), frameCounter(0)
	{}

	WriteFrames::~WriteFrames()
	{}

	void WriteFrames::processingSingleFrame(cv::Mat *image)
	{
		std::stringstream ss;
		ss << this->prefix << this->frameCounter++ << ".png";
		cv::imwrite(ss.str(), *image);
	}

}
