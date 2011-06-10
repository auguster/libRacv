/*
 * color.cpp
 *
 *  Created on: 3 mai 2011
 *      Author: remi
 */

#include <color.hpp>

#include <iostream>

namespace racv
{

	int getChannel(int color, int channel)
	{
		return (color >> ((2 - channel) * 8) & 255);
	}

	void showPixelColor(int pixel)
	{
		std::cout << "RGB(" << getChannel(pixel, RACV_RED_CHANNEL) << ", " << getChannel(pixel, RACV_GREEN_CHANNEL) << ", " << getChannel(pixel, RACV_BLUE_CHANNEL) << ")" << std::endl;
	}

}

