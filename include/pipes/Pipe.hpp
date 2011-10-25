/*
 * Pipe.h
 *
 *  Created on: 17 janv. 2011
 *      Author: auguster
 */

#ifndef PIPE_H_
#define PIPE_H_

#include <vector>
#include <opencv2/core/core.hpp>

namespace racv
{
	class Pipe
	{
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
		Pipe::PipeMsg sendPipe(Pipe::PipeMsg msg);
		static void showLogs(Pipe::PipeMsg msg);

	protected:
		Pipe *next;

		/**
		 * Process to apply to all the data coming through this pipe
		 */
		virtual Pipe::PipeMsg processing(Pipe::PipeMsg msg);

		/**
		 * Process to apply to each piece of data
		 * Note: when processing() is not overloaded it automatically call processingSingleFrame with each piece of data
		 */
		virtual void processingSingleFrame(cv::Mat *image, cv::Mat *data);
	};
}

#endif /* PIPE_H_ */
