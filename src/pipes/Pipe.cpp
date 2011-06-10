/*
 * Pipe.cpp
 *
 *  Created on: 17 janv. 2011
 *      Author: auguster
 */

#include <iostream>
#include <pipes/Pipe.hpp>

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
			return this->next->sendPipe(temp);
		}
		else
		{
			return temp;
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
		for (std::vector<cv::Mat *>::iterator image = msg.data->begin(); image < msg.data->end(); image++)
		{
			this->processingSingleFrame(*image);
		}

		return msg;
	}

	void Pipe::processingSingleFrame(cv::Mat *image)
	{
	}
}
