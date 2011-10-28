/*
 * DataSaviour.hpp
 *
 *  Created on: 27 oct. 2011
 *      Author: foloex
 */

#ifndef DATASAVIOUR_HPP_
#define DATASAVIOUR_HPP_

#include "Pipe.hpp"

namespace racv {

class DataSaviour: public racv::Pipe {
private:
	virtual Pipe::PipeMsg processing(Pipe::PipeMsg msg);
	virtual Pipe::PipeMsg postprocessing(Pipe::PipeMsg msg);
	std::vector<cv::Mat *> *savedData;
public:
	DataSaviour();
	virtual ~DataSaviour();
};

} /* namespace racv */
#endif /* DATASAVIOUR_HPP_ */
