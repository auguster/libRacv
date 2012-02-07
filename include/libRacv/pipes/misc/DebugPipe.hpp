/*
 * DebugPipe.hpp
 *
 *  Created on: 31 oct. 2011
 *      Author: foloex
 */

#ifndef DEBUGPIPE_HPP_
#define DEBUGPIPE_HPP_

#include "../core/Pipe.hpp"

#include <string>

namespace racv {

class DebugPipe: public racv::Pipe {
private:
	Pipe::PipeMsg processing(Pipe::PipeMsg msg);
	std::string message;
	Pipe::PipeMsg postprocessing(Pipe::PipeMsg msg);
public:
	DebugPipe(std::string message);
	virtual ~DebugPipe();
};

} /* namespace racv */
#endif /* DEBUGPIPE_HPP_ */
