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
	template < class typenombre >
	cv::Mat *tab2mat(typenombre *tab, int length);
	cv::Mat *tab2mat(double *tab, int length);
}

#endif /* MATRIX_HPP_ */
