/*
 * matrix.hpp
 *
 *  Created on: 3 mai 2011
 *      Author: remi
 */

#ifndef MATRIX_HPP_
#define MATRIX_HPP_

#include <opencv2/core/core.hpp>

namespace racv {
	template < typename typenombre >
	cv::Mat *tab2mat(typenombre *tab, int length);
}

#endif /* MATRIX_HPP_ */
