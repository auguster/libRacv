/*
 *  Created on: 25 mars 2011
 *  Version: 0.1.0
 *
 *  Author: Rémi AUGUSTE
 *  Email: remi.auguste@lifl.fr
 */

#ifndef LIBREMICV_HPP_
#define LIBREMICV_HPP_

#include <vector>

#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

typedef struct
{
		cv::Point left;
		cv::Point right;
} Eyes;

typedef struct
{
		cv::Rect face;
		double angle;
		Eyes eyes;
} Person;

typedef std::vector<Person> Persons;

/**
 * Computes a rectangle fitting the cloud of points
 */
cv::Rect computeRectangle(std::vector<cv::Point2f> points);

/**
 * Changes the coordinate of a vector of points
 * origin: new origin relative to the current one
 * points: the points to modify
 */
void changeOrigin(cv::Point origin, cv::vector<cv::Point2f> &points);

/**
 * Returns a new vector of points where the points that are not marked in status have been removed.
 * points: the points
 * status: check if each status is > 0, the order has to be the same in both parameters
 * Note: the parameters are not modified
 */
cv::vector<cv::Point2f> filterOut(cv::vector<cv::Point2f> &points, std::vector<uchar> &status);

/**
 * Draws a cloud of points into the image
 */
void drawPoints(cv::Mat image, cv::vector<cv::Point2f> &points, cv::Scalar color = CV_RGB(0,0,255));

/**
 * This multiscale detector tries to find the same number of objects as previously in the different scale level
 * Note: it's usually faster than detectMultiScale() but in some cases (lower number of objects it can be much slower)
 */
void smartDetect(cv::CascadeClassifier detector, cv::Mat &frame, std::vector<cv::Rect> &rectList);

#endif /* LIBREMICV_HPP_ */
