/*
 * Track.hpp
 *
 *  Created on: 28 oct. 2011
 *      Author: foloex
 */

#ifndef TRACK_HPP_
#define TRACK_HPP_

#include "Pipe.hpp"

namespace racv {

class Track: public racv::Pipe {
private:
	Pipe::PipeMsg processing(Pipe::PipeMsg msg);
	std::vector<cv::Mat *> savedImgs;
	std::vector<cv::Mat *> savedData;
public:
	Track();
	virtual ~Track();
};

} /* namespace racv */
#endif /* TRACK_HPP_ */
