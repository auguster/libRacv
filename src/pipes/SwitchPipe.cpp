/*
 * SwitchPipe.cpp
 *
 *  Created on: 28 oct. 2011
 *      Author: foloex
 */

#include <pipes/SwitchPipe.hpp>

namespace racv {

SwitchPipe::SwitchPipe() {
}

SwitchPipe::~SwitchPipe() {
}

Pipe *SwitchPipe::plugAlternativePipe(Pipe *next) {
	return this->alternative = next;
}

Pipe::PipeMsg SwitchPipe::sendPipe(Pipe::PipeMsg msg) {
	msg.log->push_back(time(NULL));

	if (!this->next)
		return msg;

	Pipe::PipeMsg normMsg;
	if (this->next && this->data && this->data->size() > 0)
	{
		normMsg = this->next->sendPipe(msg);
		if (!normMsg.data || (normMsg.data && normMsg.data->size() == 0))
		{
			if (this->alternative)
			{
				normMsg = this->alternative->sendPipe(msg);
			}
		}
	}

	return this->postprocessing(normMsg);
}

Pipe::PipeMsg SwitchPipe::postprocessing(Pipe::PipeMsg msg)
{
	if (this->data->size() == 0)
	{
		this->sendPipe(msg);
	}
	*this->data = *msg.data;
	return msg;
}

} /* namespace racv */
