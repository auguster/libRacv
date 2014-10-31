/*
 * Point.hpp
 *
 *  Created on: 31 oct. 2014
 *      Author: remi
 */

#ifndef POINT_HPP_
#define POINT_HPP_

#include <opencv2/core.hpp>

#include <libRacv/Rect.hpp>

namespace racv
{

	/**
	 * This class provides an extension of OpenCV's Rect
	 */
	class Point: public cv::Point_<int>
	{
	public:
		Point(const cv::Point &point);

		/**
		 * Change the referential of the point
		 */
		void changeSpace(const racv::Rect &from, const racv::Rect &to);

		/**
		 * Returns a copy of the point whose referential was changed
		 */
		Point & changedSpace(const racv::Rect &from, const racv::Rect &to) const;
	};
}

#endif /* POINT_HPP_ */
