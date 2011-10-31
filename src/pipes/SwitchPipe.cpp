/*
 * SwitchPipe.cpp
 *
 *  Created on: 28 oct. 2011
 *      Author: foloex
 */

#include <pipes/SwitchPipe.hpp>

#include <iostream>

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

	if (this->next)
	{
		Pipe::PipeMsg normMsg = this->next->sendPipe(msg);

		if (!(*normMsg.data)[0])
		{
			if (this->alternative)
			{
				normMsg = this->alternative->sendPipe(msg);
			}
		}

		return this->postprocessing(normMsg);
	}
	else
	{
		return msg;
	}
}

Pipe::PipeMsg SwitchPipe::postprocessing(Pipe::PipeMsg msg)
{
	if ((*msg.data)[0])
	{
		this->next->sendPipe(msg);
	}
	return msg;
}

} /* namespace racv */
