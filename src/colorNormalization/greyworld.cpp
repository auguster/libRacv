/*
 * Copyright (c) 2011 Rémi AUGUSTE
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * Contact: Rémi Auguste <remi.auguste@gmail.com>
 */

#include <libRacv/colorNormalization/greyworld.hpp>

#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <iostream>

namespace racv
{

	cv::Mat greyworld(cv::Mat image)
	{
		cv::Scalar rgb = cv::mean(image);

		cv::Mat expanded;

		cv::Mat tiny(cv::Size(1, 1), image.type());
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
