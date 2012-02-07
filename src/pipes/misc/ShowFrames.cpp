/*
 * ShowFrames.cpp
 *
 *  Created on: 17 janv. 2011
 *      Author: auguster
 */

#include <opencv2/highgui/highgui.hpp>
#include <iostream>

#include <libRacv/pipes/misc/ShowFrames.hpp>

namespace racv
{
	ShowFrames::ShowFrames(std::string name) :
		name(name)
	{}

	ShowFrames::~ShowFrames()
	{}

	void ShowFrames::processingSingleFrame(cv::Mat *image, cv::Mat*)
	{
		cv::imshow(this->name.data(), *image);
	}
}
