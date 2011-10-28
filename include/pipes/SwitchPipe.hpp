/*
 * SwitchPipe.hpp
 *
 *  Created on: 28 oct. 2011
 *      Author: foloex
 */

#ifndef SWITCHPIPE_HPP_
#define SWITCHPIPE_HPP_

#include "Pipe.hpp"

namespace racv {

class SwitchPipe: public racv::Pipe {
private:
	Pipe *alternative;
	std::vector<cv::Mat *> *data;
	Pipe::PipeMsg postprocessing(Pipe::PipeMsg msg);
public:
	SwitchPipe();
	Pipe *plugAlternativePipe(Pipe *next);
	Pipe::PipeMsg sendPipe(Pipe::PipeMsg msg);
	virtual ~SwitchPipe();
};

} /* namespace racv */
#endif /* SWITCHPIPE_HPP_ */
