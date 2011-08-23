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
	/**
	 * Returns the pixel value corresponding to the RGB values
	 */
	int getColor(int r, int g, int b);

	/**
	 * Displays with std::cout the pixel's RGB values
	 */
	void showPixelColor(int pixel);

	/**
	 * Returns the value from a given channel (use RACV_<color>_CHANNEL)
	 */
	int getChannel(int pixel, int channel);
}

#endif /* COLOR_HPP_ */
