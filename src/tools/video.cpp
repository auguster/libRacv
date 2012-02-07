/*
 * video.cpp
 *
 *  Created on: 22 sept. 2011
 *      Author: remi
 */

#include <libRacv/tools/video.hpp>

namespace racv
{

	int frameCounter(cv::VideoCapture &capture)
	{
		capture.set(CV_CAP_PROP_POS_FRAMES, 0);
		int counter = 0;
		cv::Mat frame;
		while (capture.grab())
		{
			capture >> frame;
			counter++;
		}
		capture.set(CV_CAP_PROP_POS_FRAMES, 0); //on remet la vidéo à zéro
		return counter;
	}

}
