/*
 * ShowFrames.cpp
 *
 *  Created on: 17 janv. 2011
 *      Author: auguster
 */

#include <opencv2/highgui/highgui.hpp>
#include <iostream>

#include <pipes/ShowFrames.hpp>

namespace racv
{
	ShowFrames::ShowFrames(std::string name)
	{
		this->name = name;
	}

	ShowFrames::~ShowFrames()
	{
	}

	void ShowFrames::processingSingleFrame(cv::Mat *image)
	{
		cv::imshow(this->name.data(), *image);
	}
}
