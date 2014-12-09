/*
 * core.hpp
 *
 *  Created on: 9 déc. 2014
 *      Author: remi
 */

#ifndef INCLUDE_LIBRACV_OPENCV_CORE_HPP_
#define INCLUDE_LIBRACV_OPENCV_CORE_HPP_

#include <opencv2/core/version.hpp>

#if CV_MAJOR_VERSION>2
#include <opencv2/core.hpp>
#else
#include <opencv2/core/core.hpp>
namespace cv{
#define LINE_AA CV_LINE_AA
}
#endif

#endif /* INCLUDE_LIBRACV_OPENCV_CORE_HPP_ */
