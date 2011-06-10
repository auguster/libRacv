/*
 * BackgroundSubstraction.h
 *
 *  Created on: 17 janv. 2011
 *      Author: auguster
 */

#ifndef BACKGROUNDSUBSTRACTION_H_
#define BACKGROUNDSUBSTRACTION_H_

#include "Pipe.hpp"
#include <opencv2/video/background_segm.hpp>

namespace racv
{
	class BackgroundSubstraction: public Pipe
	{
	public:
		BackgroundSubstraction(cv::Size size);
		virtual ~BackgroundSubstraction();
	private:
		cv::BackgroundSubtractorMOG2 bgs;
		void processingSingleFrame(cv::Mat *image);
	};
}

#endif /* BACKGROUNDSUBSTRACTION_H_ */
