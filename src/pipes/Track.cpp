/*
 * Track.cpp
 *
 *  Created on: 28 oct. 2011
 *      Author: foloex
 */

#include <pipes/Track.hpp>
#include <points.hpp>
#include <rectangle.hpp>

#include <opencv2/video/tracking.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <iostream>

namespace racv {

Track::Track() {
}

Pipe::PipeMsg Track::processing(Pipe::PipeMsg msg) {
	//si pas de souvenir et data dans msg on sauv et on return
	if ((this->savedData.size() == 0) || (this->savedImgs.size() != msg.imgs->size())) {
		if ((*msg.data)[0]) {
			this->savedData = *msg.data;
			this->savedImgs = *msg.imgs;
		}
		return msg;
	}

	bool hasTracked = false;

	for (int i = 0; i < msg.imgs->size(); i++) {

		cv::Mat *image = (*msg.imgs)[i];
		cv::Mat *oldImage = this->savedImgs[i];

		cv::Mat inGray(cv::Size(image->cols, image->rows), CV_8U); //on fait une copie en niveau de gris
		cv::cvtColor(*image, inGray, CV_RGB2GRAY, 1);

		cv::Mat searchMask(cv::Size(image->cols, image->rows), CV_8U); //on créé un masque de recherche

		std::vector<cv::Rect> *rects = racv::mat2VectRect(*this->savedData[i]);

		for (std::vector<cv::Rect>::iterator roi = rects->begin(); roi < rects->end(); roi++)
		{
			searchMask.setTo(false);
			searchMask(*roi).setTo(true);

			std::vector<cv::Point2f> corners; //recherche des points d'intérêts
			cv::goodFeaturesToTrack(inGray, corners, 200, 0.01, 5, searchMask);

			cv::Mat newImage;
			image->copyTo(newImage);
			racv::drawPoints(newImage, corners, cv::Scalar(255,0,0));


			std::vector<cv::Point2f> nextPts;
			std::vector<uchar> status;
			std::vector<float> err; //suivi de ces points d'intérêts
			cv::calcOpticalFlowPyrLK(*oldImage, *image, corners, nextPts, status, err);

			std::vector<cv::Point2f> points = racv::filterOut(nextPts, status);
			racv::drawPoints(*image, points, cv::Scalar(0,255,0));
			cv::imshow("Selected Points", newImage);

			int nbFound = points.size();

			if (nbFound > 15) { //FIXME vérifier la pertinence de ce seuil
				cv::Rect newDetection = racv::computeRectangle(points);
				std::cout << "<< ";
				racv::showRectangle(newDetection);
				cv::rectangle(newImage, newDetection, cv::Scalar(255,0,0), 1, CV_AA, 0);
				cv::Mat *line = new cv::Mat(1, 4, CV_32F);
				line->at<float>(0, 0) = newDetection.x;
				line->at<float>(0, 1) = newDetection.y;
				line->at<float>(0, 2) = newDetection.height;
				line->at<float>(0, 3) = newDetection.width;
				if (!(*msg.data)[i])
					(*msg.data)[i] = new cv::Mat();
				(*msg.data)[i]->push_back(line);
				hasTracked = true;
			}
		}
	}

	if (!hasTracked)
	{
		this->savedData.clear();
		this->savedImgs.clear();
	}

	msg.data->clear();

	return msg;
}

Track::~Track() {
}

} /* namespace racv */
