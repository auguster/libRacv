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
	typedef enum
	{
		RED_CHANNEL, GREEN_CHANNEL, BLUE_CHANNEL
	} COLOR;
	void showPixelColor(int pixel);
	int getChannel(int pixel, COLOR channel);
}

#endif /* COLOR_HPP_ */
