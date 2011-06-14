/*
 * Person.cpp
 *
 *  Created on: 14 juin 2011
 *      Author: remi
 */

#include <Person.hpp>

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

	cv::Rect *Person::getLeftEye() const
	{
		return leftEye;
	}

	cv::Rect *Person::getRightEye() const
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

	void Person::setLeftEye(cv::Rect *leftEye)
	{
		this->leftEye = leftEye;
	}

	void Person::setRightEye(cv::Rect *rightEye)
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

		TiXmlElement *angle = new TiXmlElement("angle");
		angle->SetDoubleAttribute("value", this->angle);
		person->LinkEndChild(angle);

		if (this->leftEye || this->rightEye)
		{
			TiXmlElement *eyes = new TiXmlElement("eyes");

			if (this->leftEye)
			{
				TiXmlElement *leftEye = new TiXmlElement("left");
				leftEye->SetAttribute("x1", this->leftEye->x);
				leftEye->SetAttribute("y1", this->leftEye->y);
				leftEye->SetAttribute("x2", this->leftEye->x + this->leftEye->width);
				leftEye->SetAttribute("y2", this->leftEye->y + this->leftEye->height);
				eyes->LinkEndChild(leftEye);
			}

			if (this->rightEye)
			{
				TiXmlElement *rightEye = new TiXmlElement("right");
				rightEye->SetAttribute("x1", this->rightEye->x);
				rightEye->SetAttribute("y1", this->rightEye->y);
				rightEye->SetAttribute("x2", this->rightEye->x + this->rightEye->width);
				rightEye->SetAttribute("y2", this->rightEye->y + this->rightEye->height);
				eyes->LinkEndChild(rightEye);
			}

			person->LinkEndChild(eyes);
		}

		return person;
	}

}
