/*
 * Person.hpp
 *
 *  Created on: 14 juin 2011
 *      Author: remi
 */

#ifndef PERSON_HPP_
#define PERSON_HPP_

#include <opencv2/core/core.hpp>

#include <tinyxml.h>

namespace racv
{
	class Person
	{
		cv::Rect *face;
		double angle;
		cv::Rect *leftEye;
		cv::Rect *rightEye;

	public:
		Person();
		virtual ~Person();

		double getAngle() const;
		cv::Rect *getFace() const;
		cv::Rect *getLeftEye() const;
		cv::Rect *getRightEye() const;

		void setAngle(double angle);
		void setFace(cv::Rect *face);
		void setLeftEye(cv::Rect *leftEye);
		void setRightEye(cv::Rect *rightEye);

		/**
		 * Saves the Person to an XML file
		 */
		bool saveXml(std::string filename);

		/**
		 * Creates a TinyXML structure of the Person
		 * This function can be used to append multiple Persons in a single XML file
		 */
		TiXmlElement *generateXml();
	};

}

#endif /* PERSON_HPP_ */
