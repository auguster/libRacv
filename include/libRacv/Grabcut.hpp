/*
 * Copyright (c) 2012 Rémi AUGUSTE
 * Contact: Rémi Auguste <remi.auguste@lifl.com>
 */

#ifndef GRABCUT_HPP_
#define GRABCUT_HPP_

#include <opencv2/imgproc/imgproc.hpp>

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

#endif /* GRABCUT_HPP_ */
