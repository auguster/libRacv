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
void showMatrix(const cv::Mat matrix) {
	for (int ligne = 0; ligne < matrix.rows; ligne++) {
		for (int colonne = 0; colonne < matrix.cols; colonne++) {
			std::cout << matrix.at<int> (ligne, colonne) << "\t";
		}
		std::cout << std::endl;
	}

	std::cout << std::endl;
}
}
