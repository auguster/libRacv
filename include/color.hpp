/*
 * color.hpp
 *
 *  Created on: 3 mai 2011
 *      Author: remi
 */

#ifndef COLOR_HPP_
#define COLOR_HPP_

namespace racv
{
#define RED_CHANNEL 0
#define GREEN_CHANNEL 1
#define BLUE_CHANNEL 2

	void showPixelColor(int pixel);
	int getChannel(int pixel, int channel);
}

#endif /* COLOR_HPP_ */
