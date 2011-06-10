/*
 * BackgroundSubstraction.cpp
 *
 *  Created on: 17 janv. 2011
 *      Author: auguster
 */

#include <pipes/BackgroundSubstraction.hpp>

#include <opencv2/imgproc/imgproc.hpp>

namespace racv
{
	BackgroundSubstraction::BackgroundSubstraction(cv::Size size)
	{
		//this->bgs.initialize(size, 0.5, 15, 5, true, 15, false, false, 16, 9, 0.9, 0.05, 127, 0.5); //FIXME apparement l'appel à changer dans OpenCV ...
		/*initialize(Size frameSize,
		 double alphaT,
		 double sigma=15,
		 int nmixtures=5,
		 bool postFiltering=false,
		 double minArea=15,
		 bool detectShadows=true,
		 bool removeForeground=false,

		 double Tb=16,
		 double Tg=9,
		 double TB=0.9,
		 double CT=0.05,

		 int nShadowDetection=127,
		 double tau=0.5)*/
	}

	BackgroundSubstraction::~BackgroundSubstraction()
	{
	}

	void BackgroundSubstraction::processingSingleFrame(cv::Mat *image)
	{
		cv::Mat *fgmask = new cv::Mat(cvSize(image->cols, image->rows), IPL_DEPTH_1U, 0);
		//cv::Mat A;
		//A = cv::Mat::ones(image->rows, image->cols, IPL_DEPTH_8U);
		this->bgs(*image, *fgmask);

		fgmask->copyTo(*image);
		//image->copyTo(*image, A);

		delete fgmask;
	}
}
