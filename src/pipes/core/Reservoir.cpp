/*
 * Copyright (c) 2011 Rémi AUGUSTE
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * Contact: Rémi Auguste <remi.auguste@gmail.com>
 */

#include <libRacv/pipes/core/Reservoir.hpp>

#include <iostream>
#include <vector>

namespace racv
{
	Reservoir::Reservoir(cv::VideoCapture *capture)
	{
		this->capture = capture;
		this->next = NULL;
	}

	Reservoir::Reservoir(std::string filename)
	{
		this->next = NULL;
		if (filename.empty())
		{
			this->capture = new cv::VideoCapture(0);
		}
		else
		{
			this->capture = new cv::VideoCapture(filename);
		}

		if (!capture) //TODO Lever une exception !
		{
			std::cerr << "No capture !" << std::endl;
			exit(EXIT_FAILURE);
		}
	}

	Reservoir::~Reservoir()
	{
	}

	Pipe *Reservoir::plugPipe(Pipe* next)
	{
		return this->next = next;
	}

	void Reservoir::flood()
	{
		if (!this->next)
		{
			std::cerr << "Reservoir is not plugged to any pipe !" << std::endl; //TODO lever une exception serait mieux
			return;
		}

		cv::Mat *frame = new cv::Mat();
		char key;

		while (this->capture->grab())
		{
			this->capture->retrieve(*frame);

			Pipe::PipeMsg msg;
			msg.imgs = new std::vector<cv::Mat *>();
			msg.data = new std::vector<cv::Mat *>();
			msg.log = new std::vector<time_t>();

			msg.imgs->push_back(frame);
			msg.data->push_back(NULL);
			msg.log->push_back(time(NULL));

			this->next->sendPipe(msg);

			key = cv::waitKey(20);
			if (key == 27)
			{
				std::cerr << "Esc Key Pressed" << std::endl;
				return;
			}

			delete msg.data;
			delete msg.log;
		}
	}

	cv::Size Reservoir::frameSize()
	{
		cv::Mat frame;
		*this->capture >> frame;
		cv::Size size(frame.cols, frame.rows);
		this->capture->set(CV_CAP_PROP_POS_FRAMES, this->capture->get(CV_CAP_PROP_POS_FRAMES)-1);
		return size;
	}

	cv::VideoCapture *Reservoir::getCapture()
	{
		return this->capture;
	}
}


