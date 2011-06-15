/*
 * Person.cpp
 *
 *  Created on: 14 juin 2011
 *      Author: remi
 */

#include <person.hpp>

namespace racv
{

	Person::Person()
	{
		this->angle = 0.0;
		this->face = NULL;
		this->leftEye = NULL;
		this->rightEye = NULL;
	}

	Person::~Person()
	{
	}

	double Person::getAngle() const
	{
		return angle;
	}

	cv::Rect *Person::getFace() const
	{
		return face;
	}

	cv::Point *Person::getLeftEye() const
	{
		return leftEye;
	}

	cv::Point *Person::getRightEye() const
	{
		return rightEye;
	}

	void Person::setAngle(double angle)
	{
		this->angle = angle;
	}

	void Person::setFace(cv::Rect *face)
	{
		this->face = face;
	}

	void Person::setLeftEye(cv::Point *leftEye)
	{
		this->leftEye = leftEye;
	}

	void Person::setRightEye(cv::Point *rightEye)
	{
		this->rightEye = rightEye;
	}

	bool Person::saveXml(std::string filename)
	{
		TiXmlDocument doc;
		TiXmlDeclaration *decl = new TiXmlDeclaration("1.0", "utf-8", "");
		doc.LinkEndChild(decl);
		doc.LinkEndChild(this->generateXml());
		return doc.SaveFile(filename);
	}

	TiXmlElement *Person::generateXml()
	{
		TiXmlElement *person = new TiXmlElement("person");
		person->SetAttribute("x1", this->face->x);
		person->SetAttribute("y1", this->face->y);
		person->SetAttribute("x2", this->face->x + this->face->width);
		person->SetAttribute("y2", this->face->y + this->face->height);

		if (this->angle != 0)
		{
			TiXmlElement *angle = new TiXmlElement("angle");
			angle->SetDoubleAttribute("value", this->angle);
			person->LinkEndChild(angle);
		}

		if (this->leftEye || this->rightEye)
		{
			TiXmlElement *eyes = new TiXmlElement("eyes");

			if (this->leftEye)
			{
				TiXmlElement *leftEye = new TiXmlElement("left");
				leftEye->SetAttribute("x", this->leftEye->x);
				leftEye->SetAttribute("y", this->leftEye->y);
				eyes->LinkEndChild(leftEye);
			}

			if (this->rightEye)
			{
				TiXmlElement *rightEye = new TiXmlElement("right");
				rightEye->SetAttribute("x", this->rightEye->x);
				rightEye->SetAttribute("y", this->rightEye->y);
				eyes->LinkEndChild(rightEye);
			}

			person->LinkEndChild(eyes);
		}

		return person;
	}

	std::string Person::generateXmlCode()
	{
		std::stringstream ss;
		ss << "<person x1=\"" << this->face->x << "\" y1=\"" << this->face->y << "\" x2=\"" << this->face->x + this->face->width << "\" y2=\"" << this->face->y
				+ this->face->height << "\">" << std::endl;

		if (this->angle != 0)
		{
			ss << "<angle value=\"" << this->angle << "\" />" << std::endl;
		}

		if (this->leftEye || this->rightEye)
		{
			ss << "<eyes>" << std::endl;

			if (this->leftEye)
			{
				ss << "<left x=\"" << this->leftEye->x << "\" y=\"" << this->leftEye->y << "\" />" << std::endl;
			}

			if (this->rightEye)
			{
				ss << "<right x=\"" << this->rightEye->x << "\" y=\"" << this->rightEye->y << "\" />" << std::endl;
			}

			ss << "</eyes>" << std::endl;
		}
		ss << "</person>" << std::endl;

		return ss.str();
	}
}
