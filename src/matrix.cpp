/*
 * matrix.cpp
 *
 *  Created on: 3 mai 2011
 *      Author: remi
 */
#include <matrix.hpp>

#include <vector>

namespace racv {
	template < class typenombre >
	cv::Mat *tab2mat(typenombre *tab, int length) //FIXME l'appel ne fonctionne pas ...
	{
		cv::Mat *matrice;
		matrice = new cv::Mat(length, 1, CV_64F);
		for (int i = 0; i < length; i++)
		{
			matrice->at<typenombre> (0, i) = tab[i];
		}
		return matrice;
	}

	cv::Mat *tab2mat(double *tab, int length)
		{
			cv::Mat *matrice;
			matrice = new cv::Mat(length, 1, CV_64F);
			for (int i = 0; i < length; i++)
			{
				matrice->at<double> (0, i) = tab[i];
			}
			return matrice;
		}
}
