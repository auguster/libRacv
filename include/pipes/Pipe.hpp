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
			std::vector<cv::Mat *> *data;
			std::vector<time_t> *log;
		} PipeMsg;
		Pipe* plugPipe(Pipe* next);
		Pipe::PipeMsg sendPipe(Pipe::PipeMsg msg);
		static void showLogs(Pipe::PipeMsg msg);

	protected:
		Pipe *next;
		virtual Pipe::PipeMsg processing(Pipe::PipeMsg msg);
		virtual void processingSingleFrame(cv::Mat *image);
	};
}

#endif /* PIPE_H_ */
