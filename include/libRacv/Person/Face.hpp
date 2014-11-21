/*
 * Face.hpp
 *
 *  Created on: 20 nov. 2014
 *      Author: remi
 */

#ifndef FACE_HPP_
#define FACE_HPP_

#include <libRacv/Roi.hpp>

namespace racv
{

	class Face: public Roi
	{
	public:
		Face(cv::Mat image);
		void optimize();
		virtual ~Face();
	};

} /* namespace racv */

#endif /* FACE_HPP_ */
