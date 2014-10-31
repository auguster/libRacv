/*
 * Point.cpp
 *
 *  Created on: 31 oct. 2014
 *      Author: remi
 */

#include <libRacv/Point.hpp>

racv::Point::Point(const cv::Point& point) :
		cv::Point_<int>(point)
{
}

void racv::Point::changeSpace(const racv::Rect& from, const racv::Rect& to)
{
	this->x += from.x - to.x;
	this->y += from.y - to.y;
}

racv::Point& racv::Point::changedSpace(const racv::Rect& from, const racv::Rect& to) const
{
	racv::Point *temp = new racv::Point(*this);
	temp->changeSpace(from, to);
	return *temp;
}
