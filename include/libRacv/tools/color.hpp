/*
 * Copyright (c) 2011 Rémi AUGUSTE
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * Contact: Rémi Auguste <remi.auguste@gmail.com>
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
