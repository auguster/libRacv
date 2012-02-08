/*
 * Copyright (c) 2011 Rémi AUGUSTE
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * Contact: Rémi Auguste <remi.auguste@gmail.com>
 */

#include <libRacv/tools/matrix.hpp>

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
