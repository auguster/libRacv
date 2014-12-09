/*
 * Copyright (c) 2012 Rémi AUGUSTE
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * Contact: Rémi Auguste <remi.auguste@gmail.com>
 */

#ifndef GRABCUT_HPP_
#define GRABCUT_HPP_

#include <libRacv/opencv/core.hpp>
#include <libRacv/opencv/imgproc.hpp>

namespace racv
{

	class Grabcut
	{
	private:
		bool isFirstFrame;
		cv::Mat mask;
		cv::Size *scaledSize;
		cv::Mat globalMask;
		//règle le ratio vitesse/qualité (quoique la qualité est parfois meilleure elle aussi ^^)
		double scale;
		bool keepBody;

		cv::Rect initNeckForegroundMask(cv::Mat &mask, cv::Rect faceRect);
		cv::Rect initTorsoForegroundMask(cv::Mat &mask, cv::Rect faceRect);
		cv::Rect initFaceForegroundMask(cv::Mat &mask, cv::Rect faceRect);
		cv::Rect initForegroundMask(cv::Mat &mask, cv::Rect faceRect);
		cv::Rect initNeckProbablyForegroundMask(cv::Mat &mask, cv::Rect faceRect);
		cv::Rect initTorsoProbablyForegroundMask(cv::Mat &mask, cv::Rect faceRect);
		cv::Rect initFaceProbablyForegroundMask(cv::Mat &mask, cv::Rect faceRect);
		cv::Rect initProbablyForegroundMask(cv::Mat &mask, cv::Rect faceRect);
		cv::Rect initNeckProbablyBackgroundMask(cv::Mat &mask, cv::Rect faceRect);
		cv::Rect initTorsoProbablyBackgroundMask(cv::Mat &mask, cv::Rect faceRect);
		cv::Rect initFaceProbablyBackgroundMask(cv::Mat &mask, cv::Rect faceRect);
		cv::Rect initProbablyBackgroundMask(cv::Mat &mask, cv::Rect faceRect);
		cv::Rect initBackground(cv::Mat &mask, cv::Rect faceRect);
		cv::Rect initMask(cv::Mat &mask, cv::Rect faceRect);
		void smartGrabcut(cv::Mat &image, cv::Mat &mask, cv::Rect rect);

	public:
		/**
		 * Scale == Quality
		 * 1.0 is slow but precise
		 * 0.1 is fast but sloppy
		 * 0.2 is usually a good compromise
		 *
		 * keepBody select whether the whole upper body should be segmented or only the head
		 * true: whole body
		 * false: only the head
		 */
		Grabcut(double scale = 0.2, bool keepBody = true);
		virtual ~Grabcut();

		/*
		 * Segments the person using a given detected face
		 * returns the region of interest
		 */
		cv::Rect process(cv::Mat &image, cv::Rect rect);
	};

}

#endif /* GRABCUT_HPP_ */
