/*
 * Gray.h
 *
 *  Created on: 17 janv. 2011
 *      Author: auguster
 */

#ifndef GRAY_H_
#define GRAY_H_

#include "Pipe.hpp"

namespace racv
{
	class Gray: virtual public Pipe
	{
	public:
		Gray();
		virtual ~Gray();
	private:
		void processingSingleFrame(cv::Mat *image);
	};
}

#endif /* GRAY_H_ */
