/*
 * Face.hpp
 *
 *  Created on: 31 oct. 2014
 *      Author: remi
 */

#ifndef ROI_HPP_
#define ROI_HPP_

#include <libRacv/Rect.hpp>

namespace racv
{
	class Roi: public racv::Rect
	{
	private:
		cv::Mat image;
		racv::Rect getRoi();
		cv::Size getParentSize();
		void sync();

	public:
		Roi(cv::Mat image);
		cv::Mat &getImage();
		void draw(cv::Scalar color);
	};
}

#endif /* FACE_HPP_ */
