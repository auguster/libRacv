/*
 * Copyright (c) 2013 Rémi AUGUSTE
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * Contact: Rémi Auguste <remi.auguste@gmail.com>
 */

#include <libRacv/tools/skinprop.hpp>

namespace racv
{
	double skinprop(const cv::Mat &image)
	{
		cv::Mat hsv;
		cv::cvtColor(image, hsv, cv::COLOR_BGR2HSV);
		cv::Mat hue(image.size(), CV_8UC1), saturation(image.size(), CV_8UC1), value(image.size(), CV_8UC1);
		std::vector<cv::Mat> channels;
		channels.push_back(hue);
		channels.push_back(saturation);
		channels.push_back(value);
		cv::split(hsv, channels);
		cv::threshold(hue, hue, 18, 255, cv::THRESH_BINARY_INV);
		cv::threshold(saturation, saturation, 50, 255, cv::THRESH_BINARY_INV);
		cv::threshold(value, value, 80, 255, cv::THRESH_BINARY_INV);
		cv::Mat output;
		cv::bitwise_and(hue, saturation, output);
		cv::bitwise_and(output, value, output);
		cv::Scalar sums = cv::sum(output);
		double result = sums[0] / (output.rows * output.cols * 255);
		return result;
	}
}
