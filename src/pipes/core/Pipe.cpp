/*
 * Copyright (c) 2011 Rémi AUGUSTE
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * Contact: Rémi Auguste <remi.auguste@gmail.com>
 */

#include <iostream>
#include <libRacv/pipes/core/Pipe.hpp>

namespace racv
{
	Pipe::Pipe()
	{
		this->next = NULL;
	}

	Pipe::~Pipe()
	{

	}

	Pipe *Pipe::plugPipe(Pipe *next)
	{
		if (next == this)
		{
			std::cerr << "Pipe cannot be plugged to itself !" << std::endl; //TODO lever une exception serait mieux
			exit(EXIT_FAILURE);
		}
		else
		{
			this->next = next;
		}
		return next;
	}

	Pipe::PipeMsg Pipe::sendPipe(Pipe::PipeMsg msg)
	{
		Pipe::PipeMsg temp = this->processing(msg);
		temp.log->push_back(time(NULL));
		if (this->next) //Forwards only if the end of the pipe has not been reached
		{
			return this->postprocessing(this->next->sendPipe(temp));
		}
		else
		{
			return this->postprocessing(temp);
		}
	}

	void Pipe::showLogs(Pipe::PipeMsg msg)
	{
		int i = 0;
		for (std::vector<time_t>::iterator time = msg.log->begin(); time < msg.log->end(); time++, i++)
		{
			std::cout << "step " << i << " at " << *time << std::endl;
		}
	}

	Pipe::PipeMsg Pipe::processing(Pipe::PipeMsg msg)
	{
		std::vector<cv::Mat *>::iterator data = msg.data->begin();
		for (std::vector<cv::Mat *>::iterator image = msg.imgs->begin(); image < msg.imgs->end(); image++, data++)
		{
			this->processingSingleFrame(*image, *data);
		}

		return msg;
	}

	void Pipe::processingSingleFrame(cv::Mat *image, cv::Mat *data)
	{
	}

	Pipe::PipeMsg Pipe::postprocessing(Pipe::PipeMsg msg)
	{
		return msg;
	}
}
