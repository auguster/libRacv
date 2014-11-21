/*
 * Face.cpp
 *
 *  Created on: 20 nov. 2014
 *      Author: remi
 */

#include <libRacv/Person/Face.hpp>

#include <libRacv/tools/skinprop.hpp>

#include <iostream>

namespace racv
{

	Face::Face(cv::Mat face) :
			Roi(face)
	{

	}

	Face::~Face()
	{
	}

	void Face::optimize()
	{
		cv::Rect originalFace = *this;

		double skinp = racv::skinprop(this->getImage());
		double oldskinp = 0;

		//reduces the right border to maximize the skin color proportion
		do
		{
			oldskinp = skinp;
			this->width--;
			skinp = skinprop(this->getImage());

		} while (skinp > oldskinp);
		this->width++;

		//reduces the left border to maximize the skin color proportion
		do
		{
			oldskinp = skinp;
			this->x++;
			this->width--;
			skinp = skinprop(this->getImage());

		} while (skinp > oldskinp);
		this->x--;
		this->width++;

		//augment the bottom border to maximize the skin color proportion
		do
		{
			oldskinp = skinp;
			this->height++;
			skinp = skinprop(this->getImage());

		} while (skinp >= oldskinp);
		this->height--;

		//augment the upper border to maximize the skin color proportion
		do
		{
			oldskinp = skinp;
			this->y--;
			this->height++;
			skinp = skinprop(this->getImage());

		} while (skinp >= oldskinp);
		this->y++;
		this->height--;
	}

} /* namespace racv */
