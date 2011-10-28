/*
 * ExtractRectangles.hpp
 *
 *  Created on: 27 oct. 2011
 *      Author: foloex
 */

#ifndef EXTRACTRECTANGLES_HPP_
#define EXTRACTRECTANGLES_HPP_

#include "Pipe.hpp"

namespace racv {

class ExtractRectangles: public racv::Pipe {
private:
	Pipe::PipeMsg processing(Pipe::PipeMsg msg);
public:
	ExtractRectangles();
	virtual ~ExtractRectangles();
};

} /* namespace racv */
#endif /* EXTRACTRECTANGLES_HPP_ */
