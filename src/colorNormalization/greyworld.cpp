/*
 * greyworld.cpp
 *
 *  Created on: 11 avr. 2011
 *      Author: auguster
 */

#include <colorNormalization/greyworld.hpp>

#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <iostream>

namespace racv
{

	cv::Mat greyworld(cv::Mat image)
	{
		cv::Scalar rgb = cv::mean(image);

		cv::Mat expanded;

		cv::Mat tiny(cvSize(1, 1), image.type());
		tiny.data[0] = rgb[0];
		tiny.data[1] = rgb[1];
		tiny.data[2] = rgb[2];

		std::cout << rgb[0] << " " << rgb[1] << " " << rgb[2] << std::endl;

		cv::resize(tiny, expanded, image.size());

		cv::Mat *result = new cv::Mat(image.size(), image.type());

		for (int i = 0; i < image.rows; i++)
			for (int j = 0; j < image .cols * 3; j += 3)
			{
				result->data[i * image.cols * 3 + j] = (int) (image.data[i * image.cols * 3 + j] /  rgb[0] * 100) % 255; //FIXME / par la moyenne RGB
				result->data[i * image.cols * 3 + j + 1] = (int) (image.data[i * image.cols * 3 + j + 1] / rgb[1] * 100) % 255;
				result->data[i * image.cols * 3 + j + 2] = (int) (image.data[i * image.cols * 3 + j + 2] / rgb[2] * 100) % 255;
			}

		//cv::divide(image, expanded, *result);

		cv::imshow("result", expanded);

		return *result;
	}

} // namespace racv
