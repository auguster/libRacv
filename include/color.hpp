/*
 * color.hpp
 *
 *  Created on: 3 mai 2011
 *      Author: remi
 */

#ifndef COLOR_HPP_
#define COLOR_HPP_

#define RACV_RED_CHANNEL 0
#define RACV_GREEN_CHANNEL 1
#define RACV_BLUE_CHANNEL 2

namespace racv
{
	void showPixelColor(int pixel);
	int getChannel(int pixel, int channel);
}

#endif /* COLOR_HPP_ */
