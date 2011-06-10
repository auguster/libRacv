/*
 * Gray.cpp
 *
 *  Created on: 17 janv. 2011
 *      Author: auguster
 */

#include <pipes/Gray.hpp>
#include <opencv2/imgproc/imgproc.hpp>

namespace racv
{

	Gray::Gray()
	{
		this->next = NULL;
	}

	Gray::~Gray()
	{
	}

	void Gray::processingSingleFrame(cv::Mat *image)
	{
		int width = image->cols;
		int height = image->rows;

		cv::Mat *dst = new cv::Mat(cvSize(width, height), IPL_DEPTH_8U, 1);

		cv::cvtColor((*image), *dst, CV_RGB2GRAY);
		dst->copyTo(*image);
		delete dst;
	}

}
