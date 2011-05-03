/*
 * color.cpp
 *
 *  Created on: 3 mai 2011
 *      Author: remi
 */

#include <color.hpp>

#include <iostream>

namespace racv {

int getChannel(int color, int channel) {
	return (color >> ((2 - channel) * 8) & 255);
}

void showPixelColor(int color) {
	std::cout << "RGB(" << getChannel(color, RACV_RED_CHANNEL) << ", " << getChannel(color, RACV_BLUE_CHANNEL)
			<< ", " << getChannel(color, RACV_GREEN_CHANNEL) << ")" << std::endl;
}

}

