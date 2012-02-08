/*
 * Copyright (c) 2011 Rémi AUGUSTE
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * Contact: Rémi Auguste <remi.auguste@gmail.com>
 */

#ifndef WRITEFRAMES_HPP_
#define WRITEFRAMES_HPP_

#include "../core/Pipe.hpp"

namespace racv
{

	class WriteFrames: public Pipe
	{
	private:
		int frameCounter;
		std::string prefix;
	public:
		/**
		 * If this constructor is used then the frames' filename will just be the frame number
		 */
		WriteFrames();

		/**
		 * \param prefix will be put on the frames' filename before the frame number
		 */
		WriteFrames(std::string prefix);
		virtual ~WriteFrames();
		void processingSingleFrame(cv::Mat *image, cv::Mat *data);
	};

}

#endif /* WRITEFRAMES_HPP_ */
