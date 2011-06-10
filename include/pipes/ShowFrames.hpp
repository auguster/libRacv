/*
 * ShowFrames.h
 *
 *  Created on: 17 janv. 2011
 *      Author: auguster
 */

#ifndef SHOWFRAMES_H_
#define SHOWFRAMES_H_

#include <string>

#include "Pipe.hpp"

namespace racv
{
	class ShowFrames: virtual public Pipe
	{
	public:
		ShowFrames(std::string name);
		virtual ~ShowFrames();
	private:
		std::string name;
		void processingSingleFrame(cv::Mat *image);
	};
}

#endif /* SHOWFRAMES_H_ */
