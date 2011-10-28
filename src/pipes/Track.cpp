/*
 * Track.cpp
 *
 *  Created on: 28 oct. 2011
 *      Author: foloex
 */

#include <pipes/Track.hpp>
#include <points.hpp>

#include <opencv2/video/tracking.hpp>
#include <opencv2/imgproc/imgproc.hpp>

namespace racv {

Track::Track(cv::Mat *image, cv::Rect *toTrack) {
	this->image = image;
	this->ROI = toTrack;
}

cv::Mat *Track::getImage() {
	return this->image;
}

cv::Rect *Track::getROI() {
	return this->ROI;
}

void Track::processingSingleFrame(cv::Mat *image, cv::Mat *data) {
	if (!data)
		data = new cv::Mat();

	cv::Mat inGray(cv::Size(image->cols, image->rows), CV_8U); //on fait une copie en niveau de gris
	cv::cvtColor(*image, inGray, CV_RGB2GRAY, 1);

	cv::Mat searchMask(cv::Size(image->cols, image->rows), CV_8U); //on créé un masque de recherche
	searchMask.setTo(false);
	searchMask(*this->ROI).setTo(true);

	std::vector<cv::Point2f> corners; //recherche des points d'intérêts
	cv::goodFeaturesToTrack(inGray, corners, 200, 0.01, 5, searchMask);

	std::vector<cv::Point2f> nextPts;
	std::vector<uchar> status;
	std::vector<float> err; //suivi de ces points d'intérêts
	cv::calcOpticalFlowPyrLK(*this->image, *image, corners, nextPts, status,
			err);

	int nbFound = 0;
	for (std::vector<uchar>::iterator found = status.begin();
			found < status.end(); found++) {
		if (*found) {
			nbFound++; //comptage des points retrouvés
		}
	}

	if (nbFound > 50) { //FIXME vérifier la pertinence de ce seuil
		cv::Rect newDetection = racv::computeRectangle(nextPts);
		cv::Mat *line = new cv::Mat(1, 4, CV_32F);
		line->at<float>(0, 0) = newDetection.x;
		line->at<float>(0, 1) = newDetection.y;
		line->at<float>(0, 2) = newDetection.height;
		line->at<float>(0, 3) = newDetection.width;
		data->push_back(line);
	}
}

Track::~Track() {
}

} /* namespace racv */
