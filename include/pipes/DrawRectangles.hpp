/*
 * DrawDetections.hpp
 *
 *  Created on: Oct 24, 2011
 *      Author: remi
 */

#ifndef DRAWRECTANGLES_HPP_
#define DRAWRECTANGLES_HPP_

#include <pipes/Pipe.hpp>

namespace racv {

class DrawRectangles: public racv::Pipe {
private:
	void processingSingleFrame(cv::Mat *image, cv::Mat *data);
	bool debug;
public:
	DrawRectangles(bool value = false);
	DrawRectangles();
	virtual ~DrawRectangles();
};

} /* namespace racv */
#endif /* DRAWRECTANGLES_HPP_ */
