/*
 * person.hpp
 *
 *  Created on: 11 avr. 2011
 *      Author: auguster
 */

#ifndef PERSON_HPP_
#define PERSON_HPP_

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

#endif /* PERSON_HPP_ */
