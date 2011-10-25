/*
 * Reservoir.cpp
 *
 *  Created on: 17 janv. 2011
 *      Author: auguster
 */

#include <pipes/Reservoir.hpp>

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

			Pipe::PipeMsg reponse = this->next->sendPipe(msg);

			key = cv::waitKey(2);
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
		cv::Mat *frame = new cv::Mat();
		this->capture->retrieve(*frame);
		cv::Size size(frame->cols, frame->rows);
		delete frame;
		return size;
	}

	cv::VideoCapture *Reservoir::getCapture()
	{
		return this->capture;
	}
}


