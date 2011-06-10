/*
 * BodyDetect.hpp
 *
 *  Created on: 10 juin 2011
 *      Author: remi
 */

#ifndef BODYDETECT_HPP_
#define BODYDETECT_HPP_

#include "Pipe.hpp"
#include "detection.hpp"

namespace racv
{
	class BodyDetect: public Pipe
	{
	public:
		BodyDetect();
		virtual ~BodyDetect();
	private:
		cv::CascadeClassifier *detector;
		Pipe::PipeMsg processing(Pipe::PipeMsg msg);
	};
}

#endif /* BODYDETECT_HPP_ */
