/*
 * matrix.cpp
 *
 *  Created on: 3 mai 2011
 *      Author: remi
 */
#include <matrix.hpp>

#include <iostream>
#include <vector>

namespace racv {
	template < typename typenombre >
	cv::Mat *tab2mat(typenombre *tab, int length)
	{
		cv::Mat *matrice;
		matrice = new cv::Mat(length, 1, CV_64F);
		for (int i = 0; i < length; i++)
		{
			matrice->at<typenombre> (0, i) = tab[i];
		}
		return matrice;
	}
}
