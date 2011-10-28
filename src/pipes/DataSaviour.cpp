/*
 * DataSaviour.cpp
 *
 *  Created on: 27 oct. 2011
 *      Author: foloex
 */

#include <pipes/DataSaviour.hpp>

namespace racv {

DataSaviour::DataSaviour() {
}

DataSaviour::~DataSaviour() {
}

Pipe::PipeMsg DataSaviour::processing(Pipe::PipeMsg msg)
{
	this->savedData = new std::vector<cv::Mat *>();
	*this->savedData = *msg.data;
	return msg;
}

Pipe::PipeMsg DataSaviour::postprocessing(Pipe::PipeMsg msg)
{
	for (std::vector<cv::Mat *>::iterator data = msg.data->begin(); data < msg.data->end(); data++)
	{
		this->savedData->push_back(*data);
	}
	msg.data = this->savedData;
	return msg;
}

} /* namespace racv */
