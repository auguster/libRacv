/*
 * Copyright (c) 2011 Rémi AUGUSTE
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * Contact: Rémi Auguste <remi.auguste@gmail.com>
 */

#include <libRacv/video.hpp>

#include <iostream>

namespace racv
{

	int frameCounter(cv::VideoCapture &capture)
	{
		capture.set(cv::CAP_PROP_POS_FRAMES, 0);
		int counter = 0;
		cv::Mat frame;
		while (capture.grab())
		{
			capture.retrieve(frame);
			counter++;
		}
		capture.set(cv::CAP_PROP_POS_FRAMES, 0); //on remet la vidéo à zéro
		return counter;
	}

	bool fastforward(cv::VideoCapture &capture, int stopFrame)
	{
		int counter = capture.get(cv::CAP_PROP_POS_FRAMES);
		std::cout << counter << std::endl;
		cv::Mat frame;
		while (capture.grab() && counter < stopFrame)
		{
			counter++;
		}
		return (counter == stopFrame);
	}

}
