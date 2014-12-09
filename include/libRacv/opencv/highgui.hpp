/*
 * highgui.hpp
 *
 *  Created on: 9 déc. 2014
 *      Author: remi
 */

#ifndef INCLUDE_LIBRACV_OPENCV_HIGHGUI_HPP_
#define INCLUDE_LIBRACV_OPENCV_HIGHGUI_HPP_

#include <opencv2/core/version.hpp>

#if CV_MAJOR_VERSION>2
#include <opencv2/highgui.hpp>
#else
#include <opencv2/highgui/highgui.hpp>
namespace cv
{
	enum
	{
		CAP_PROP_POS_FRAMES = 1
	};
}
#endif

#endif /* INCLUDE_LIBRACV_OPENCV_HIGHGUI_HPP_ */
