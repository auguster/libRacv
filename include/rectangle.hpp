/*
 * rectangle.hpp
 *
 *  Created on: 14 juin 2011
 *      Author: remi
 */

#ifndef RECTANGLE_HPP_
#define RECTANGLE_HPP_

#include <opencv2/core/core.hpp>

namespace racv {

bool isOverlapping(cv::Rect A, cv::Rect B);

/**
 * Merge vector source with vector destination into destination
 */
void merge(std::vector<cv::Rect > &source, std::vector<cv::Rect > &destination);

}  // namespace racv

#endif /* RECTANGLE_HPP_ */
