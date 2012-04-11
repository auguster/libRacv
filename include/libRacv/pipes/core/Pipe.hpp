/*
 * Copyright (c) 2011 Rémi AUGUSTE
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * Contact: Rémi Auguste <remi.auguste@gmail.com>
 */

#ifndef PIPE_H_
#define PIPE_H_

#include <vector>
#include <opencv2/core/core.hpp>

#include "Reservoir.hpp"

namespace racv
{
	class Reservoir; //forward reference (for mutual inclusion)

	class Pipe
	{
	private:
		Reservoir *reservoir;

	public:
		Pipe();
		virtual ~Pipe();
		typedef struct
		{
			std::vector<cv::Mat *> *imgs;
			std::vector<cv::Mat *> *data; //CV_32F matrices
			std::vector<time_t> *log;
		} PipeMsg;
		Pipe* plugPipe(Pipe* next);

		virtual Pipe::PipeMsg sendPipe(Pipe::PipeMsg msg);

		static void showLogs(Pipe::PipeMsg msg);

		/**
		 * Send the data to the next Pipe (Threaded !)
		 */
		//virtual void sendPipe(cv::Mat *image, cv::Mat *data);

		/**
		 * Sets a pointer to the Reservoir
		 * If a pipe is plugged the pointer gets propagated
		 */
		virtual void *setReservoir(Reservoir *reservoir);

	protected:
		Pipe *next;

		/**
		 * Process to apply to all the data coming forward through this pipe
		 * Note: overloading this method avoids calling processingSingleFrame
		 */
		virtual Pipe::PipeMsg processing(Pipe::PipeMsg msg);

		/**
		 * Process to apply to each piece of data
		 * Note: when processing() is not overloaded it automatically calls processingSingleFrame with each piece of data
		 */
		virtual void processingSingleFrame(cv::Mat *image, cv::Mat *data);

		/**
		 * Process to apply to all the data coming backward through this pipe
		 */
		virtual Pipe::PipeMsg postprocessing(Pipe::PipeMsg msg);

	};
}

#endif /* PIPE_H_ */
