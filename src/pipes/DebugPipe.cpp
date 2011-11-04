/*
 * DebugPipe.cpp
 *
 *  Created on: 31 oct. 2011
 *      Author: foloex
 */

#include <pipes/DebugPipe.hpp>

#include <iostream>

namespace racv {

DebugPipe::DebugPipe(std::string message) {
	this->message = message;
}

DebugPipe::~DebugPipe() {
}

Pipe::PipeMsg DebugPipe::processing(Pipe::PipeMsg msg)
{
	std::cout << ">> " << this->message << std::endl;
	return msg;
}

Pipe::PipeMsg DebugPipe::postprocessing(Pipe::PipeMsg msg)
{
    std::cout << "<< " << this->message << std::endl;
    return msg;
}

} /* namespace racv */
